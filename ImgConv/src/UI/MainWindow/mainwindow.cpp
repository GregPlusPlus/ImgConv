#include "mainwindow.h"
#include "Core/Processing/processing.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowIcon(QIcon(":/icons/icon.png"));
    setWindowTitle(tr("Accelerated Image Convolution Filtering"));

    buildFilterSettingsView();
    initCore();

    buildKernelComboBox();
    buildMenus();
    buildView();

    setMinimumSize(QSize(700, 500));
}

MainWindow::~MainWindow() {
    delete m_ocl;
}

void MainWindow::openFile() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open image file"), QString(),
                                              tr("Image files (*.png *.jpg *.bmp)"));

    if(fn.isEmpty()) {
        return;
    }

    QElapsedTimer tm;
    tm.start();

    QImageReader r;
    r.setAllocationLimit(0);
    r.setFileName(fn);
    QImage img = r.read().convertToFormat(QImage::Format_RGB888);

    mw_labelElapsedTime->setText(tr("Image loaded in %1 ms.").arg(tm.elapsed()));

    loadImage(img);
}

void MainWindow::loadImage(const QImage &img) {
    m_original = img;

    mw_origImgView->setPixmap(QPixmap::fromImage(m_original));
    mw_prcdImgView->setPixmap(QPixmap());

    mw_labelImgInfo->setText(tr("%1x%2 (%3 bytes)")
                             .arg(m_original.width()).arg(m_original.height()).arg(m_original.sizeInBytes()));
    mw_tabWidget->setCurrentWidget(mw_origImgView);
}

void MainWindow::exportFile() {
    QString fn = QFileDialog::getSaveFileName(this, tr("Save image file"), QString(),
                                              tr("Image files (*.png)"));

    if(fn.isEmpty()) {
        return;
    }

    QPixmap pix = QPixmap::fromImage(m_processed);
    pix.save(fn);
}

void MainWindow::startProcess() {
    if(m_original.isNull()) {
        return;
    }

    ConvKernels::ConvKernel *k = m_convKernels.at(mw_convKernelComboBox->currentIndex());
    QVector<QVector<float>> mat = k->getMat();
    QSize matSize = k->getMatSize();

    if(!matSize.width() || !matSize.height()) {
        return;
    }

    createOCLProgram(QString("-DW=%1 -DH=%2 -DKW=%3 -DKH=%4")
                     .arg(m_original.width())
                     .arg(m_original.height())
                     .arg(matSize.width())
                     .arg(matSize.height()));
    if(m_ocl->ret() != CL_SUCCESS) {
        return;
    }

    Utils::scaleMatrix(mat, k->getScalar());

    QElapsedTimer tm;
    tm.start();

    if(!Processing::processImg(m_ocl, m_original, m_processed, mat)) {
        QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error (%1)").arg(m_ocl->ret()));
    }

    qint64 elapsed = tm.elapsed();

    mw_labelElapsedTime->setText(tr("Processing done in %1 ms. - Approx %2 px/sec.")
                                 .arg(elapsed).arg(1000.f*(m_processed.size().width()*m_processed.size().height())/elapsed));

    mw_prcdImgView->setPixmap(QPixmap::fromImage(m_processed));

    mw_tabWidget->setCurrentWidget(mw_prcdImgView);
}

void MainWindow::filterSelected(int index) {
    ConvKernels::ConvKernel *k = m_convKernels.at(index);
    k->select();

    mw_dockFilterSettings->setConvKernel(k);
}

void MainWindow::initCore() {
    initOpenCL();
    Processing::registerConvKernels(&m_convKernels, this);
}

void MainWindow::initOpenCL() {
    m_ocl = new OCLWrapper();

    if(m_ocl->ret() != CL_SUCCESS) {
        QMessageBox::critical(this, tr("OCL init error"), tr("OCL backend error (%1)").arg(m_ocl->ret()));

        return;
    }
}

void MainWindow::createOCLProgram(const QString &options) {
    QFileDevice::FileError e = m_ocl->createProgramFromFile(":/ocl/conv2D.cl", "conv2D", options);

    if(e != QFileDevice::NoError) {
        QMessageBox::critical(this, tr("Filesystem error"), tr("File error (%1)").arg(e));

        return;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        switch(m_ocl->ret()) {
        case CL_BUILD_PROGRAM_FAILURE :
        {QMessageBox msg;
            qDebug() << m_ocl->getBuildLog();
            msg.setWindowTitle(tr("OCL error"));
            msg.setText(tr("OCL build program error (%1)")
                        .arg(m_ocl->ret()));
            msg.setDetailedText(m_ocl->getBuildLog());
            msg.setIcon(QMessageBox::Critical);
            msg.exec();}
            break;
        default:
            QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error (%1)").arg(m_ocl->ret()));
            break;
        }

        return;
    }
}

void MainWindow::buildKernelComboBox() {
    mw_convKernelComboBox = new QComboBox(this);
    connect(mw_convKernelComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::filterSelected);

    for(ConvKernels::ConvKernel *k : m_convKernels) {
        mw_convKernelComboBox->addItem(k->getName());
    }
}

void MainWindow::buildMenus() {
    mw_fileMenu = menuBar()->addMenu(tr("&File"));

    m_openFileAction = mw_fileMenu->addAction(QIcon(":/icons/folder-horizontal-open.png"), tr("&Open"), tr("Ctrl+O"), this, &MainWindow::openFile);
    m_exportAction = mw_fileMenu->addAction(QIcon(":/icons/disk.png"), tr("Export processed image"), tr("Ctrl+E"), this, &MainWindow::exportFile);
    mw_fileMenu->addSeparator();
    m_exitAction = mw_fileMenu->addAction(QIcon(":/icons/door-open-in.png"), tr("&Exit"), tr("Ctrl+W"), this, [](){qApp->exit();});

    mw_processMenu = menuBar()->addMenu(tr("&Process"));
    m_reloadKernelAction = mw_processMenu->addAction(QIcon(":/icons/arrow-circle-double.png"), tr("Reload current &kernel"), tr("F5"), this, [this]() {
        filterSelected(mw_convKernelComboBox->currentIndex());
    });
    m_runAction = mw_processMenu->addAction(QIcon(":/icons/control.png"), tr("&Run"), tr("Ctrl+R"), this, &MainWindow::startProcess);
    m_backfeedAction = mw_processMenu->addAction(QIcon(":/icons/arrow-transition-180.png"), tr("&Backfeed"), tr("Ctrl+B"), this, [this](){
        if(!m_processed.isNull()) {
            loadImage(m_processed);
        }
    });

    mw_toolBar = new QToolBar(tr("Tools"), this);
    mw_toolBar->addAction(m_openFileAction);
    mw_toolBar->addAction(m_exportAction);
    mw_toolBar->addSeparator();
    mw_toolBar->addWidget(new QLabel(tr("Filter : "), this));
    mw_toolBar->addWidget(mw_convKernelComboBox);
    mw_toolBar->addAction(m_reloadKernelAction);
    mw_toolBar->addAction(m_runAction);
    mw_toolBar->addAction(m_backfeedAction);
    addToolBar(mw_toolBar);

    mw_labelDevice = new QLabel(m_ocl->getDeviceName(), this);
    mw_labelImgInfo = new QLabel(this);
    mw_labelElapsedTime = new QLabel(this);

    statusBar()->addWidget(mw_labelDevice);
    statusBar()->addWidget(mw_labelImgInfo);
    statusBar()->addWidget(mw_labelElapsedTime);
}

void MainWindow::buildView() {
    mw_tabWidget = new QTabWidget(this);

    mw_origImgView = new ImageViewer(tr("Original image"));
    mw_prcdImgView = new ImageViewer(tr("Processed image"));

    mw_tabWidget->addTab(mw_origImgView, tr("Original"));
    mw_tabWidget->addTab(mw_prcdImgView, tr("Processed"));

    setCentralWidget(mw_tabWidget);
}

void MainWindow::buildFilterSettingsView() {
    mw_dockFilterSettings = new FilterSettingsDock(this);

    addDockWidget(Qt::LeftDockWidgetArea, mw_dockFilterSettings);
}

