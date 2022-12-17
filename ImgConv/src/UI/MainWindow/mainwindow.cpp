#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    initOpenCL();

    buildMenus();
    buildView();

    setMinimumSize(QSize(500, 500));
}

MainWindow::~MainWindow() {
}

void MainWindow::openFile() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open image file"), QString(),
                                              tr("Image files (*.png *.jpg *.bmp)"));

    if(fn.isEmpty()) {
        return;
    }

    m_pixmap = QPixmap(fn);

    m_origImg->setPixmap(m_pixmap);
}

void MainWindow::startProcess() {
    // Ridge
    QVector<QVector<float>> k = {
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
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
    m_fileMenu->addSeparator();
    m_exitAction = m_fileMenu->addAction(tr("&Exit"), tr("Ctrl+W"), this, [](){qApp->exit();});

    m_processMenu = menuBar()->addMenu(tr("&Process"));
    m_runAction = m_processMenu->addAction(tr("&Run"), tr("Ctrl+R"), this, &MainWindow::startProcess);

    m_labelDevice = new QLabel(m_wrapper->getDeviceName(), this);
    m_labelElapsedTime = new QLabel(this);

    statusBar()->addWidget(m_labelDevice);
    statusBar()->addWidget(m_labelElapsedTime);
}

void MainWindow::buildView() {
    m_layout = new QHBoxLayout();

    m_centralWidget = new QWidget(this);

    m_origImg = new QLabel(tr("Original image"), this);
    m_prcdImg = new QLabel(tr("Processed image"), this);

    m_layout->addWidget(m_origImg, 0, Qt::AlignLeft);
    m_layout->addWidget(m_prcdImg, 0, Qt::AlignRight);

    m_centralWidget->setLayout(m_layout);
    setCentralWidget(m_centralWidget);
}

bool MainWindow::processImg(const QVector<QVector<float>> &k) {
    QImage img = m_pixmap.toImage();
    img = img.convertToFormat(QImage::Format_RGB32);

    int imgW = img.width();
    int imgH = img.height();
    int kW = k[0].size();
    int kH = k.size();

    // Convolution kernel buffer
    ConvKernel1DArray k1d(k);

    // Input RGB buffers
    RGB1DArray inputRGB1DArray(img);
    // Output RGB buffers
    RGB1DArray outputRGB1DArray;

    // Create INPUT RGB buffers
    for(int i = 0; i < 3; i ++) {
        if(m_wrapper->addBuffer(inputRGB1DArray.size(), CL_MEM_READ_ONLY) < 0) {
            return false;
        }
    }

    // Create OUTPUT RGB buffers
    for(int i = 0; i < 3; i ++) {
        if(m_wrapper->addBuffer(inputRGB1DArray.size(), CL_MEM_READ_ONLY) < 0) {
            return false;
        }
    }

    // Create convolution kernel buffer
    if(m_wrapper->addBuffer(k1d.size() * sizeof(float), CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Write INPUT buffers
    if(!m_wrapper->writeBuffer(0, inputRGB1DArray.getR(), inputRGB1DArray.size())) {
        return false;
    }
    if(!m_wrapper->writeBuffer(1, inputRGB1DArray.getG(), inputRGB1DArray.size())) {
        return false;
    }
    if(!m_wrapper->writeBuffer(2, inputRGB1DArray.getB(), inputRGB1DArray.size())) {
        return false;
    }

    // Write convolution kernel buffer
    if(!m_wrapper->writeBuffer(6, (uint8_t*)k1d.getK(), k1d.size() * sizeof(float))) {
        return false;
    }

    // Create Kernel parameters
    //   First 6 R,G,B arrays then the Convolution kernel
    for(size_t i = 0; i < m_wrapper->getNumberOfBuffers(); i ++) {
        m_wrapper->setKernelArg(i, i);

        if(m_wrapper->ret() != CL_SUCCESS) {
            return false;
        }
    }
    //   Image size
    m_wrapper->setKernelArg(7, sizeof(cl_uint), (const uint8_t*)&imgW);
    m_wrapper->setKernelArg(8, sizeof(cl_uint), (const uint8_t*)&imgH);
    //   Set convolution kernel size
    m_wrapper->setKernelArg(9, sizeof(cl_float), (const uint8_t*)&kW);
    m_wrapper->setKernelArg(10, sizeof(cl_float), (const uint8_t*)&kH);

    // Run kernel
    QElapsedTimer tm;
    tm.start();
    m_wrapper->runKernel(imgW, imgH);
    qDebug() << tm.elapsed();
    if(m_wrapper->ret() != CL_SUCCESS) {
        return false;
    }

    // Read OUTPUT buffers
    if(!m_wrapper->readBuffer(3, &outputRGB1DArray.m_R, &outputRGB1DArray.m_s)) {
        return false;
    }
    if(!m_wrapper->readBuffer(4, &outputRGB1DArray.m_G, &outputRGB1DArray.m_s)) {
        return false;
    }
    if(!m_wrapper->readBuffer(5, &outputRGB1DArray.m_B, &outputRGB1DArray.m_s)) {
        return false;
    }

    // Display new image
    QImage outImg(imgW, imgH, QImage::Format_RGB32);

    for(int y = 0; y < imgH; y ++) {
        for (int x = 0; x < imgW; x ++) {
            size_t i = (y * imgW) + x;

            outImg.setPixel(x, y, QColor(outputRGB1DArray.getR()[i],
                                         outputRGB1DArray.getG()[i],
                                         outputRGB1DArray.getB()[i]).rgb());
        }
    }

    m_prcdImg->setPixmap(QPixmap::fromImage(outImg));

    m_wrapper->releaseAll();

    return true;
}

