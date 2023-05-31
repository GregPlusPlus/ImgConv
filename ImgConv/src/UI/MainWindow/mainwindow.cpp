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

    m_app = new Core::App(this);

    if(!m_app->init()) {
        exit(EXIT_FAILURE);
    }

    connectCoreApp();

    buildUI();

    setMinimumSize(QSize(1200, 800));
}

MainWindow::~MainWindow() {
}

void MainWindow::connectCoreApp() {
    connect(m_app, &Core::App::originalImageChanged, this, &MainWindow::showOriginalImage);
    connect(m_app, &Core::App::processedImageChanged, this, &MainWindow::showProcessedImage);
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
        m_createImageAction->setDisabled(false);
        m_runAction->setDisabled(false);
        delete dialog;
    });

    m_openFileAction->setDisabled(true);
    m_createImageAction->setDisabled(true);
    m_runAction->setDisabled(true);
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

    m_app->setOriginalImage(img);
}

void MainWindow::showOriginalImage(const QImage &img) {
    mw_tabWidget->setCurrentWidget(mw_origImgView);
    mw_origImgView->setPixmap(QPixmap::fromImage(img));
    mw_processedImgView->setPixmap(QPixmap());

    mw_labelImgInfo->setText(tr("%1x%2 (%3 bytes)")
                             .arg(img.width()).arg(img.height()).arg(img.sizeInBytes()));

    mw_imgCorrectionPanel->clearOriginalImageHistogram();
    mw_imgCorrectionPanel->clearProcessedImageHistogram();
    m_app->startComputeHistogram(img);
}

void MainWindow::showProcessedImage(const QImage &img) {
    mw_tabWidget->setCurrentWidget(mw_processedImgView);
    mw_processedImgView->setPixmap(QPixmap::fromImage(img));

    mw_imgCorrectionPanel->clearProcessedImageHistogram();
    m_app->startComputeHistogram(img);
}

void MainWindow::exportProcessedImage() {
    if(m_app->processedImage().isNull()) {
        return;
    }

    QString fn = QFileDialog::getSaveFileName(this, tr("Save image file"), QString(),
                                              tr("Image files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(fn.isEmpty()) {
        return;
    }

    QPixmap pix = QPixmap::fromImage(m_app->processedImage());
    pix.save(fn);

    mw_logPanel->logInfo(tr("[%1] Image saved.").arg(fn));
}

void MainWindow::filterSelected(int index) {
    ConvKernels::ConvKernel *k = m_app->getConvKernelAt(index);
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

void MainWindow::saveOnExit() {
    if(m_app->processedImage().isNull()) {
        return;
    }

    if(QMessageBox::question(this, tr("Unsaved file"), tr("Save processed image before closing ?"),
                             QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    exportProcessedImage();
}

void MainWindow::displayOCLProgramError() {
    qDebug() << m_app->ocl()->getBuildLog();

    mw_logPanel->logError(tr("OCL build program error (%1)\n______________________________\n%2")
                          .arg(m_app->ocl()->ret())
                          .arg(m_app->ocl()->getBuildLog()));
}

void MainWindow::buildKernelComboBox() {
    mw_convKernelComboBox = new QComboBox(this);
    connect(mw_convKernelComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::filterSelected);

    for(ConvKernels::ConvKernel *k : m_app->convKernels()) {
        mw_convKernelComboBox->addItem(k->getName());
    }
}

void MainWindow::buildMenus() {
    mw_fileMenu = menuBar()->addMenu(tr("&File"));

    m_openFileAction = mw_fileMenu->addAction(QIcon(":/icons/folder-horizontal-open.png"), tr("&Open"), tr("Ctrl+O"), this, &MainWindow::openFile);
    m_createImageAction = mw_fileMenu->addAction(QIcon(":/icons/image-new.png"), tr("&Create image"), tr("Ctrl+N"), this, &MainWindow::createImage);
    m_exportAction = mw_fileMenu->addAction(QIcon(":/icons/disk.png"), tr("Export processed image"), tr("Ctrl+E"), this, &MainWindow::exportProcessedImage);
    mw_fileMenu->addSeparator();
    m_selectDeviceAction = mw_fileMenu->addAction(QIcon(":/icons/graphic-card.png"), tr("Select &device"), this, [this]() {
        SelectDeviceDialog dialog(m_app->devices());
        if(dialog.exec() == QDialog::Accepted) {
            m_app->initOpenCL(dialog.getDevice());
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
        if(!m_app->processedImage().isNull()) {
            m_app->setOriginalImage(m_app->processedImage());
        }
    });

    mw_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_aboutAction = mw_helpMenu->addAction(QIcon(":/icons/information-balloon.png"), tr("&About this program"), this, &MainWindow::showAboutDialog);
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
    mw_labelDevice->setText(m_app->ocl()->getDeviceName());
    mw_logPanel->logInfo(tr("Selected device : %1").arg(m_app->ocl()->getDeviceName()));
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

    connect(mw_imgCorrectionPanel, &ImageCorrectionPanel::equalizeHistogram, this, [=]() {
        startImageCorrection(":/ocl/equalizeHistogram.cl");
    });
}

void MainWindow::buildView() {
    mw_tabWidget = new QTabWidget(this);

    mw_origImgView = new ImageViewerContainer(tr("Original image"), this);
    mw_processedImgView = new ImageViewerContainer(tr("Processed image"), this);

    mw_codeEditor = new CodeEditorContainter(this);
    connect(mw_codeEditor, &CodeEditorContainter::useFile, this, [=](const QString &fn) {
        m_app->convKernels().at(mw_convKernelComboBox->currentIndex())->setSourceFilePath(fn);
        filterSelected(mw_convKernelComboBox->currentIndex());
        m_app->startConv2DProcess(m_app->getConvKernelAt(mw_convKernelComboBox->currentIndex()));
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
    if(m_app->ocl()->isRunning()) {
        ev->ignore();
        return;
    }

    saveOnExit();

    ev->accept();
}
