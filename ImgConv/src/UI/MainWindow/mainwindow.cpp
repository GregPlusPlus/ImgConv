/**
 ** This file is part of the ImgConv project.
 ** Copyright 2022-2023 Grégoire BOST <bostgregoire@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "mainwindow.h"
#include "Core/Processing/processing.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowIcon(QIcon(":/icons/icon.png"));
    setWindowTitle(APP_NAME);


    if(!initCore()) {
        exit(EXIT_FAILURE);
    }

    buildUI();

    setMinimumSize(QSize(1200, 800));
}

MainWindow::~MainWindow() {
}

void MainWindow::openFile() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open image file"), QString(),
                                              tr("Image files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(fn.isEmpty()) {
        return;
    }

    WaitDialog *dialog = new WaitDialog(tr("Opening image..."));
    Threads::ImgLoader *imgLoader = new Threads::ImgLoader(fn);

    connect(imgLoader, &Threads::ImgLoader::loaded, this, [this, dialog, fn](QImage img, qint64 et) {
        mw_labelElapsedTime->setText(tr("Image loaded in %1 ms.").arg(et));
        mw_logPanel->logInfo(tr("[%1] Image loaded in %2 ms.").arg(fn).arg(et));
        showOriginalImage(img);

        m_openFileAction->setDisabled(false);
        delete dialog;
    });

    m_openFileAction->setDisabled(true);
    dialog->show();

    QThreadPool::globalInstance()->start(imgLoader);
}

void MainWindow::createImage() {
    CreateImageDialog *dialog = new CreateImageDialog(this);
    dialog->exec();

    if(dialog->result() != QMessageBox::Accepted) {
        return;
    }

    CreateImageDialog::ImageSettings_t settings = dialog->getImageSettings();

    if((settings.width == 0) || (settings.height == 0)) {
        return;
    }

    QImage img(settings.width, settings.height, QImage::Format_RGB888);
    img.fill(settings.fillColor);

    mw_logPanel->logInfo(tr("Created image of size %1x%2.").arg(settings.width).arg(settings.height));

    showOriginalImage(img);
}

void MainWindow::showOriginalImage(const QImage &img) {
    m_original = img;

    mw_tabWidget->setCurrentWidget(mw_origImgView);
    mw_origImgView->setPixmap(QPixmap::fromImage(m_original));
    mw_processedImgView->setPixmap(QPixmap());

    mw_labelImgInfo->setText(tr("%1x%2 (%3 bytes)")
                             .arg(m_original.width()).arg(m_original.height()).arg(m_original.sizeInBytes()));

    mw_imgCorrectionPanel->originalImageHistogramWidget()->clear();
    mw_imgCorrectionPanel->processedImageHistogramWidget()->clear();
    startComputeHistogram(m_original, mw_imgCorrectionPanel->originalImageHistogramWidget());
}

void MainWindow::showProcessedImage(const QImage &img) {
    m_processed = img;

    mw_tabWidget->setCurrentWidget(mw_processedImgView);
    mw_processedImgView->setPixmap(QPixmap::fromImage(m_processed));

    mw_imgCorrectionPanel->processedImageHistogramWidget()->clear();
    startComputeHistogram(m_processed, mw_imgCorrectionPanel->processedImageHistogramWidget());
}

void MainWindow::logConvMatrix(const QVector<QVector<float> > &mat) {
    QString str;

    str += tr("\n%1x%2 Convolution matrix :\n").arg(mat[0].size()).arg(mat.size());

    if((mat.size() > 16) || (mat[0].size() > 16)) {
        str += tr("Matrix is too large to be printed.");
    } else {
        str += Utils::matrixToBoxString(mat);
    }

    str += "\n";

    mw_logPanel->logOutput(str);
}

void MainWindow::exportFile() {
    QString fn = QFileDialog::getSaveFileName(this, tr("Save image file"), QString(),
                                              tr("Image files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(fn.isEmpty()) {
        return;
    }

    QPixmap pix = QPixmap::fromImage(m_processed);
    pix.save(fn);

    mw_logPanel->logInfo(tr("[%1] Image saved.").arg(fn));
}

void MainWindow::startConv2DProcess() {
    if(m_ocl->isRunning()) {
        mw_logPanel->logInfo(tr("Kernel already running ! Please wait."));

        return;
    }

    if(m_original.isNull()) {
        return;
    }

    ConvKernels::ConvKernel *k = m_convKernels.at(mw_convKernelComboBox->currentIndex());
    QVector<QVector<float>> mat = k->getMat();
    QSize matSize = k->getMatSize();

    if(!matSize.width() || !matSize.height()) {
        return;
    }

    QString options = Processing::createOCLProgramOptionsConv2D(m_original.size(), matSize);

    mw_logPanel->logOutput(tr("\n[%1] Creating program - opts. : `%2`")
                        .arg(k->getSourceFilePath())
                        .arg(options));

    if(!createOCLProgram(k->getSourceFilePath(), options)) {
        return;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        return;
    }

    Utils::scaleMatrix(mat, k->getScalar());

    logConvMatrix(mat);

    mw_logPanel->logOutput(tr("Running kernel..."));

    WaitDialog *dialog = new WaitDialog(tr("Processing image..."));
    Threads::Conv2D *process = new Threads::Conv2D(m_ocl, m_original, mat);

    connect(process, &Threads::Conv2D::finished, this, [this, dialog](const QImage &img, qint64 et, bool res) {
        float pixPerSec = 0;

        if(!res) {
            QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error"));

            m_runAction->setDisabled(false);
            delete dialog;

            return;
        }

        pixPerSec = 1000.f * (img.size().width() * img.size().height()) / et;

        QString logStr = tr("Processing done in %1 ms. - Approx %2 px/sec.")
                            .arg(et)
                            .arg(pixPerSec);

        mw_labelElapsedTime->setText(logStr);
        mw_logPanel->logOutput(logStr);

        showProcessedImage(img);

        m_runAction->setDisabled(false);
        m_selectDeviceAction->setDisabled(false);
        delete dialog;
    });

    m_runAction->setDisabled(true);
    m_selectDeviceAction->setDisabled(true);
    dialog->show();

    QThreadPool::globalInstance()->start(process);
}

void MainWindow::startComputeHistogram(const QImage &img, HistogramWidget *widget) {
    const QString programPath = ":/ocl/histogram.cl";

    if(m_ocl->isRunning()) {
        mw_logPanel->logInfo(tr("Kernel already running ! Please wait."));

        return;
    }

    if(img.isNull()) {
        return;
    }

    QString options = Processing::createOCLProgramOptionsComputeHistogram(img.size());

    mw_logPanel->logOutput(tr("\n[%1] Creating program - opts. : `%2`")
                        .arg(programPath)
                        .arg(options));

    if(!createOCLProgram(programPath, options)) {
        return;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        return;
    }

    mw_logPanel->logOutput(tr("Running kernel..."));

    WaitDialog *dialog = new WaitDialog(tr("Computing histogram..."));
    Threads::Histogram *process = new Threads::Histogram(m_ocl, img);

    connect(process, &Threads::Histogram::finished, this, [=](const Processing::Algorithms::Histogram &hist, qint64 et, bool res) {
        float pixPerSec = 0;

        if(!res) {
            QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error"));

            m_runAction->setDisabled(false);
            delete dialog;

            return;
        }

        pixPerSec = 1000.f * (img.size().width() * img.size().height()) / et;

        QString logStr = tr("Processing done in %1 ms. - Approx %2 px/sec.")
                            .arg(et)
                            .arg(pixPerSec);

        mw_labelElapsedTime->setText(logStr);
        mw_logPanel->logOutput(logStr);

        widget->setHistogram(hist);

        m_runAction->setDisabled(false);
        m_selectDeviceAction->setDisabled(false);
        delete dialog;
    });

    m_runAction->setDisabled(true);
    m_selectDeviceAction->setDisabled(true);
    dialog->show();

    QThreadPool::globalInstance()->start(process);
}

void MainWindow::startImageCorrection(const QString &kernelPath) {
    if(m_ocl->isRunning()) {
        mw_logPanel->logInfo(tr("Kernel already running ! Please wait."));

        return;
    }

    if(m_original.isNull()) {
        return;
    }

    QString options = Processing::createOCLProgramOptionsCorrection(m_original.size());

    mw_logPanel->logOutput(tr("\n[%1] Creating program - opts. : `%2`")
                        .arg(kernelPath)
                        .arg(options));

    if(!createOCLProgram(kernelPath, options)) {
        return;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        return;
    }

    mw_logPanel->logOutput(tr("Running kernel..."));

    WaitDialog *dialog = new WaitDialog(tr("Correcting image..."));
    Threads::Correction *process = new Threads::Correction(m_ocl, m_original);

    connect(process, &Threads::Correction::finished, this, [this, dialog](const QImage &img, qint64 et, bool res) {
        float pixPerSec = 0;

        if(!res) {
            QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error"));

            m_runAction->setDisabled(false);
            delete dialog;

            return;
        }

        pixPerSec = 1000.f * (img.size().width() * img.size().height()) / et;

        QString logStr = tr("Processing done in %1 ms. - Approx %2 px/sec.")
                            .arg(et)
                            .arg(pixPerSec);

        mw_labelElapsedTime->setText(logStr);
        mw_logPanel->logOutput(logStr);

        showProcessedImage(img);

        m_runAction->setDisabled(false);
        m_selectDeviceAction->setDisabled(false);
        delete dialog;
    });

    m_runAction->setDisabled(true);
    m_selectDeviceAction->setDisabled(true);
    dialog->show();

    QThreadPool::globalInstance()->start(process);
}

void MainWindow::filterSelected(int index) {
    ConvKernels::ConvKernel *k = m_convKernels.at(index);
    k->select();

    mw_dockFilterSettings->setConvKernel(k);
}

void MainWindow::showAboutDialog() {
    QMessageBox::about(this, tr("About this program"),
                       tr("<h1>%1</h1> " \
                          "[Rev. %2]<br><br>" \
                          "Some icons are provided under a " \
                          "<a href='https://creativecommons.org/licenses/by/3.0/'>Creative Commons Attribution 3.0 License</a> " \
                          "by Yusuke Kamiyamane <a href='https://p.yusukekamiyamane.com/'>(Fugue Icons)</a>.<br><br>"\
                          "%3"\
                          "<hr>%4")
                       .arg(APP_NAME)
                       .arg(GIT_VERSION)
                       .arg(COPYRIGHT)
                       .arg(LGPL_STR));
}

bool MainWindow::initCore() {
    m_devices = OCLWrapper::getDevices();

    if(m_devices.count() == 0) {
        QMessageBox::critical(nullptr, tr("OCL init error"), tr("No OpenCL compatible device found !"));

        return false;
    }

    initOpenCL(m_devices[0]);
    Processing::registerConvKernels(&m_convKernels, this);

    return true;
}

void MainWindow::initOpenCL(const OCLWrapper::Device &device) {
    if(m_ocl) {
        delete m_ocl;
    }

    m_ocl = new OCLWrapper(device, this);

    if(m_ocl->ret() != CL_SUCCESS) {
        QMessageBox::critical(this, tr("OCL init error"), tr("OCL backend error (%1)").arg(m_ocl->ret()));

        return;
    }
}

bool MainWindow::createOCLProgram(const QString &fn, const QString &options) {
    QFileDevice::FileError e = m_ocl->createProgramFromFile(fn, "pixelKernel", options);

    if(e != QFileDevice::NoError) {
        m_ocl->releaseKernel();
        m_ocl->releaseProgram();

        QMessageBox::critical(this, tr("Filesystem error"), tr("File error (%1)").arg(e));

        return false;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        switch(m_ocl->ret()) {
        case CL_BUILD_PROGRAM_FAILURE :
            displayOCLProgramError();

            m_ocl->releaseKernel();
            m_ocl->releaseProgram();
            break;
        default:
            QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error (%1)").arg(m_ocl->ret()));

            m_ocl->releaseKernel();
            m_ocl->releaseProgram();
            break;
        }

        return false;
    }

    return true;
}

void MainWindow::displayOCLProgramError() {
    qDebug() << m_ocl->getBuildLog();

    mw_logPanel->logError(tr("OCL build program error (%1)\n______________________________\n%2")
                          .arg(m_ocl->ret())
                          .arg(m_ocl->getBuildLog()));
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
    m_createImageAction = mw_fileMenu->addAction(QIcon(":/icons/image-new.png"), tr("&Create image"), tr("Ctrl+N"), this, &MainWindow::createImage);
    m_exportAction = mw_fileMenu->addAction(QIcon(":/icons/disk.png"), tr("Export processed image"), tr("Ctrl+E"), this, &MainWindow::exportFile);
    mw_fileMenu->addSeparator();
    m_selectDeviceAction = mw_fileMenu->addAction(QIcon(":/icons/graphic-card.png"), tr("Select &device"), this, [this]() {
        SelectDeviceDialog dialog(m_devices);
        if(dialog.exec() == QDialog::Accepted) {
            initOpenCL(dialog.getDevice());
            displayDeviceName();
        }
    });
    mw_fileMenu->addSeparator();
    m_exitAction = mw_fileMenu->addAction(QIcon(":/icons/door-open-in.png"), tr("&Exit"), tr("Ctrl+W"), this, [](){qApp->exit();});

    mw_processMenu = menuBar()->addMenu(tr("&Process"));
    m_reloadKernelAction = mw_processMenu->addAction(QIcon(":/icons/arrow-circle-double.png"), tr("Reload current &kernel"), tr("F5"), this, [this]() {
        filterSelected(mw_convKernelComboBox->currentIndex());
    });
    m_runAction = mw_processMenu->addAction(QIcon(":/icons/control.png"), tr("&Run"), tr("Ctrl+R"), this, &MainWindow::startConv2DProcess);
    m_backfeedAction = mw_processMenu->addAction(QIcon(":/icons/arrow-transition-180.png"), tr("&Backfeed"), tr("Ctrl+B"), this, [this](){
        if(!m_processed.isNull()) {
            showOriginalImage(m_processed);
        }
    });

    mw_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_aboutAction = mw_helpMenu->addAction(tr("&About this program"), this, &MainWindow::showAboutDialog);
    m_aboutQtAction = mw_helpMenu->addAction(tr("About &Qt"), this, [this]() {
        QMessageBox::aboutQt(this);
    });

    m_openCLDevices = mw_helpMenu->addAction(tr("Open&CL Devices"), this, [this]() {
        QMessageBox::information(this, tr("OpenCL Devices"), OCLWrapper::getDevicesInfoStr());
    });

    mw_toolBar = new QToolBar(tr("Tools"), this);
    mw_toolBar->addAction(m_openFileAction);
    mw_toolBar->addAction(m_createImageAction);
    mw_toolBar->addAction(m_exportAction);
    mw_toolBar->addSeparator();
    mw_toolBar->addWidget(new QLabel(tr("Filter : "), this));
    mw_toolBar->addWidget(mw_convKernelComboBox);
    mw_toolBar->addAction(m_reloadKernelAction);
    mw_toolBar->addAction(m_runAction);
    mw_toolBar->addAction(m_backfeedAction);
    addToolBar(mw_toolBar);

    mw_labelDevice = new QLabel(this);
    mw_labelImgInfo = new QLabel(this);
    mw_labelElapsedTime = new QLabel(this);

    displayDeviceName();

    statusBar()->addWidget(mw_labelDevice);
    statusBar()->addWidget(mw_labelImgInfo);
    statusBar()->addWidget(mw_labelElapsedTime);
}

void MainWindow::displayDeviceName() {
    mw_labelDevice->setText(m_ocl->getDeviceName());
    mw_logPanel->logInfo(tr("Selected device : %1").arg(m_ocl->getDeviceName()));
}

void MainWindow::buildUI() {
    buildFilterSettingsView();
    buildPanels();

    buildKernelComboBox();
    buildMenus();
    buildView();
}

void MainWindow::buildPanels() {
    mw_logPanel = new LogPanel(this);
    addDockWidget(Qt::BottomDockWidgetArea, mw_logPanel);

    mw_imgCorrectionPanel = new ImageCorrectionPanel(this);
    addDockWidget(Qt::RightDockWidgetArea, mw_imgCorrectionPanel);

    connect(mw_imgCorrectionPanel, &ImageCorrectionPanel::convertToGrayscale, this, [=]() {
        startImageCorrection(":/ocl/convertGrayscale.cl");
    });

    connect(mw_imgCorrectionPanel, &ImageCorrectionPanel::invertColors, this, [=]() {
        startImageCorrection(":/ocl/invertColors.cl");
    });
}

void MainWindow::buildView() {
    mw_tabWidget = new QTabWidget(this);

    mw_origImgView = new ImageViewerContainer(tr("Original image"), this);
    mw_processedImgView = new ImageViewerContainer(tr("Processed image"), this);

    mw_codeEditor = new CodeEditorContainter(this);
    connect(mw_codeEditor, &CodeEditorContainter::useFile, this, [=](const QString &fn) {
        m_convKernels.at(mw_convKernelComboBox->currentIndex())->setSourceFilePath(fn);
        filterSelected(mw_convKernelComboBox->currentIndex());
        startConv2DProcess();
    });

    mw_tabWidget->addTab(mw_origImgView, tr("Original"));
    mw_tabWidget->addTab(mw_processedImgView, tr("Processed"));
    mw_tabWidget->addTab(mw_codeEditor, tr("Code editor"));

    setCentralWidget(mw_tabWidget);
}

void MainWindow::buildFilterSettingsView() {
    mw_dockFilterSettings = new FilterSettingsDock(this);

    addDockWidget(Qt::LeftDockWidgetArea, mw_dockFilterSettings);
}

void MainWindow::closeEvent(QCloseEvent *ev) {
    if(m_ocl->isRunning()) {
        ev->ignore();
        return;
    }

    ev->accept();
}
