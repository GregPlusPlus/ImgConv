#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    initOpenCL();

    buildMenus();
    buildView();

    setMinimumSize(QSize(500, 500));
}

MainWindow::~MainWindow() {
    delete m_wrapper;
}

void MainWindow::openFile() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open image file"), QString(),
                                              tr("Image files (*.png *.jpg *.bmp)"));

    if(fn.isEmpty()) {
        return;
    }

    QPixmap pix = QPixmap(fn);
    m_original = pix.toImage();
    m_original = m_original.convertToFormat(QImage::Format_RGB888);

    m_origImgView->setPixmap(pix);

    m_labelImgInfo->setText(tr("%1x%2 (%3 bytes)").arg(m_original.width()).arg(m_original.height()).arg(m_original.sizeInBytes()));
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

    if(!processImg(k)) {
        QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error (%1)").arg(m_wrapper->ret()));
    }

    m_labelElapsedTime->setText(tr("Done in %1 ms.").arg(tm.elapsed()));

    m_prcdImgView->setPixmap(QPixmap::fromImage(m_processed));
}

void MainWindow::initOpenCL() {
    m_wrapper = new OCLWrapper();

    if(m_wrapper->ret() != CL_SUCCESS) {
        QMessageBox::critical(this, tr("OCL init error"), tr("OCL backend error (%1)").arg(m_wrapper->ret()));

        return;
    }

    QFileDevice::FileError e = m_wrapper->createProgramFromFile(":/ocl/conv2D.cl", "conv2D");

    if(e != QFileDevice::NoError) {
        QMessageBox::critical(this, tr("Filesystem error"), tr("File error (%1)").arg(e));

        return;
    }

    if(m_wrapper->ret() != CL_SUCCESS) {
        switch(m_wrapper->ret()) {
        case CL_BUILD_PROGRAM_FAILURE :
        {QMessageBox msg;
            qDebug() << m_wrapper->getBuildLog();
            msg.setWindowTitle(tr("OCL error"));
            msg.setText(tr("OCL build program error (%1)")
                        .arg(m_wrapper->ret()));
            msg.setDetailedText(m_wrapper->getBuildLog());
            msg.setIcon(QMessageBox::Critical);
            msg.exec();}
            break;
        default:
            QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error (%1)").arg(m_wrapper->ret()));
            break;
        }

        return;
    }
}

void MainWindow::buildMenus() {
    m_fileMenu = menuBar()->addMenu(tr("&File"));

    m_openFileAction = m_fileMenu->addAction(tr("&Open"), tr("Ctrl+O"), this, &MainWindow::openFile);
    m_exportAction = m_fileMenu->addAction(tr("Export processed image"), tr("Ctrl+E"), this, &MainWindow::exportFile);
    m_fileMenu->addSeparator();
    m_exitAction = m_fileMenu->addAction(tr("&Exit"), tr("Ctrl+W"), this, [](){qApp->exit();});

    m_processMenu = menuBar()->addMenu(tr("&Process"));
    m_runAction = m_processMenu->addAction(tr("&Run"), tr("Ctrl+R"), this, &MainWindow::startProcess);

    m_labelDevice = new QLabel(m_wrapper->getDeviceName(), this);
    m_labelImgInfo = new QLabel(this);
    m_labelElapsedTime = new QLabel(this);

    statusBar()->addWidget(m_labelDevice);
    statusBar()->addWidget(m_labelImgInfo);
    statusBar()->addWidget(m_labelElapsedTime);
}

void MainWindow::buildView() {
    m_layout = new QHBoxLayout();

    m_centralWidget = new QWidget(this);

    m_origImgView = new ImageViewer(tr("Original image"), this);
    m_prcdImgView = new ImageViewer(tr("Processed image"), this);

    m_layout->addWidget(m_origImgView, 10);
    m_layout->addWidget(m_prcdImgView, 10);

    m_centralWidget->setLayout(m_layout);
    setCentralWidget(m_centralWidget);
}

bool MainWindow::processImg(const QVector<QVector<float>> &k) {
    int imgW = m_original.width();
    int imgH = m_original.height();
    size_t inSize = m_original.sizeInBytes();
    int kW = k[0].size();
    int kH = k.size();

    // Convolution kernel buffer
    ConvKernel1DArray kernel1DArray(k);

    // Output buffer
    uint8_t *outImg = nullptr;
    size_t outSize = 0;

    // Create INPUT RGB buffer
    if(m_wrapper->addBuffer(inSize, CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Create OUTPUT RGB buffer
    if(m_wrapper->addBuffer(inSize, CL_MEM_READ_WRITE) < 0) {
        return false;
    }

    // Create convolution kernel buffer
    if(m_wrapper->addBuffer(kernel1DArray.buffSize(), CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Write INPUT buffer
    if(!m_wrapper->writeBuffer(0, m_original.bits(), inSize)) {
        return false;
    }

    // Write convolution kernel buffer
    if(!m_wrapper->writeBuffer(2, (uint8_t*)kernel1DArray.getKArray(), kernel1DArray.buffSize())) {
        return false;
    }

    // Create Kernel parameters
    //   First set all the buffers
    for(size_t i = 0; i < m_wrapper->getNumberOfBuffers(); i ++) {
        m_wrapper->setKernelArg(i, i);

        if(m_wrapper->ret() != CL_SUCCESS) {
            return false;
        }
    }
    //   Set image size
    m_wrapper->setKernelArg(3, sizeof(cl_uint), (const uint8_t*)&imgW);
    m_wrapper->setKernelArg(4, sizeof(cl_uint), (const uint8_t*)&imgH);
    //   Set convolution kernel size
    m_wrapper->setKernelArg(5, sizeof(cl_uint), (const uint8_t*)&kW);
    m_wrapper->setKernelArg(6, sizeof(cl_uint), (const uint8_t*)&kH);

    // Run kernel
    m_wrapper->runKernel(imgW, imgH);
    if(m_wrapper->ret() != CL_SUCCESS) {
        return false;
    }

    // Read OUTPUT buffer
    if(!m_wrapper->readBuffer(1, &outImg, &outSize)) {
        return false;
    }

    // Convert back buffer to image
    m_processed = QImage((const uchar *)outImg, imgW, imgH, QImage::Format_RGB888);

    m_wrapper->releaseAll();

    return true;
}

