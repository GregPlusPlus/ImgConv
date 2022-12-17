#include "mainwindow.h"
#include "Core/Processing/processing.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    initOpenCL();

    buildMenus();
    buildView();

    setMinimumSize(QSize(500, 500));
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
    m_original = r.read().convertToFormat(QImage::Format_RGB888);
    mw_origImgView->setPixmap(QPixmap::fromImage(m_original));

    mw_labelElapsedTime->setText(tr("Image loaded in %1 ms.").arg(tm.elapsed()));

    mw_labelImgInfo->setText(tr("%1x%2 (%3 bytes)").arg(m_original.width()).arg(m_original.height()).arg(m_original.sizeInBytes()));
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
    // Ridge
    /*QVector<QVector<float>> k = {
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };
    float c = 1;*/

    // Sobel V
    /*QVector<QVector<float>> k = {
        {1, 0, -1},
        {2, 0, -2},
        {1, 0, -1}
    };
    float c = 1;*/

    // Sobel H
    /*QVector<QVector<float>> k = {
        {1,   2,  1},
        {0,   0,  0},
        {-1, -2, -1}
    };
    float c = 1;*/

    // Emboss
    QVector<QVector<float>> k = {
        {-2, -1, 0},
        {-1,  1, 1},
        {0,   1, 2}
    };
    float c = 1;

    // 5x5 Gaussian blur
    /*QVector<QVector<float>> k = {
        {1,  4,  6,  4, 1},
        {4, 16, 24, 16, 4},
        {6, 24, 36, 24, 6},
        {4, 16, 24, 16, 4},
        {1,  4,  6,  4, 1}
    };
    float c = 1.f/256.f;*/

    // Unsharp masking
    /*QVector<QVector<float>> k = {
        {1,  4,    6,  4, 1},
        {4, 16,   24, 16, 4},
        {6, 24, -476, 24, 6},
        {4, 16,   24, 16, 4},
        {1,  4,    6,  4, 1}
    };
    float c = -1.f/256.f;*/

    // Sharpen
    /*QVector<QVector<float>> k = {
        {0, -1,  0},
        {-1, 5, -1},
        {0, -1,  0}
    };
    float c = 1;*/

    Utils::scaleMatrix(k, c);

    QElapsedTimer tm;
    tm.start();

    if(!Processing::processImg(m_ocl, m_original, m_processed, k)) {
        QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error (%1)").arg(m_ocl->ret()));
    }

    mw_labelElapsedTime->setText(tr("Processing done in %1 ms.").arg(tm.elapsed()));

    mw_prcdImgView->setPixmap(QPixmap::fromImage(m_processed));
}

void MainWindow::initOpenCL() {
    m_ocl = new OCLWrapper();

    if(m_ocl->ret() != CL_SUCCESS) {
        QMessageBox::critical(this, tr("OCL init error"), tr("OCL backend error (%1)").arg(m_ocl->ret()));

        return;
    }

    QFileDevice::FileError e = m_ocl->createProgramFromFile(":/ocl/conv2D.cl", "conv2D");

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

void MainWindow::buildMenus() {
    mw_fileMenu = menuBar()->addMenu(tr("&File"));

    m_openFileAction = mw_fileMenu->addAction(tr("&Open"), tr("Ctrl+O"), this, &MainWindow::openFile);
    m_exportAction = mw_fileMenu->addAction(tr("Export processed image"), tr("Ctrl+E"), this, &MainWindow::exportFile);
    mw_fileMenu->addSeparator();
    m_exitAction = mw_fileMenu->addAction(tr("&Exit"), tr("Ctrl+W"), this, [](){qApp->exit();});

    mw_processMenu = menuBar()->addMenu(tr("&Process"));
    m_runAction = mw_processMenu->addAction(tr("&Run"), tr("Ctrl+R"), this, &MainWindow::startProcess);

    mw_labelDevice = new QLabel(m_ocl->getDeviceName(), this);
    mw_labelImgInfo = new QLabel(this);
    mw_labelElapsedTime = new QLabel(this);

    statusBar()->addWidget(mw_labelDevice);
    statusBar()->addWidget(mw_labelImgInfo);
    statusBar()->addWidget(mw_labelElapsedTime);
}

void MainWindow::buildView() {
    m_layout = new QHBoxLayout();

    mw_centralWidget = new QWidget(this);

    mw_origImgView = new ImageViewer(tr("Original image"), this);
    mw_prcdImgView = new ImageViewer(tr("Processed image"), this);

    m_layout->addWidget(mw_origImgView, 10);
    m_layout->addWidget(mw_prcdImgView, 10);

    mw_centralWidget->setLayout(m_layout);
    setCentralWidget(mw_centralWidget);
}
