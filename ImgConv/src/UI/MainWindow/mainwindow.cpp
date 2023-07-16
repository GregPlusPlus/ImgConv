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

using namespace UI;

MainWindow::MainWindow(Core::App *coreApp)
    : QMainWindow{}, m_coreApp{coreApp} {
    setWindowIcon(QIcon(":/icons/icon.png"));
    setWindowTitle(APP_NAME);

    buildUI();

    connectCoreApp();

    setMinimumSize(QSize(1200, 800));
}

MainWindow::~MainWindow() {
}

void MainWindow::connectCoreApp() {
    connect(m_coreApp, &Core::App::originalImageChanged, this, &MainWindow::showOriginalImage);
    connect(m_coreApp, &Core::App::processedImageChanged, this, &MainWindow::showProcessedImage);

    connect(m_coreApp, &Core::App::conv2DDone, this, &MainWindow::conv2DDone);
    connect(m_coreApp, &Core::App::histogramComputingDone, this, &MainWindow::histogramComputed);
    connect(m_coreApp, &Core::App::imageCorrectionDone, this, &MainWindow::imageCorrected);

    connect(m_coreApp, &Core::App::processProgress, &m_waitDialogMgr, &WaitDialogMgr::updateDialogProgress);
    connect(m_coreApp->ocl(), &Core::OCLWrapper::kernelCanceled, this, [this]() {
        m_coreApp->logOutput(tr("Kernel canceled"));

        if(m_closeAfterKernelCanceled) {
            close();
        }
    }, Qt::QueuedConnection);

    connect(m_coreApp, &Core::Logger::showCriticalError, this, [this](const QString &str) {
        QMessageBox::critical(this, tr("Critical error"), str);
    });
}

void MainWindow::processError() {
    QMessageBox::critical(this, tr("OpenCL error"), tr("OpenCL backend error"));
}

void MainWindow::conv2DDone(const QUuid &pid, qint64 elapsedTime) {
    logProcessFinished(pid, elapsedTime);

    m_openFileAction->setDisabled(false);
    m_createImageAction->setDisabled(false);
    m_runAction->setDisabled(false);
    m_selectDeviceAction->setDisabled(false);

    m_waitDialogMgr.closeDialog(pid);
}

void MainWindow::histogramComputed(const QUuid &pid, qint64 elapsedTime, const Core::Processing::Algorithms::Histogram &histogram) {
    Q_UNUSED(elapsedTime)

    mw_imgCorrectionPanel->displayHistogram(histogram, m_histRole);

    m_runAction->setDisabled(false);
    m_selectDeviceAction->setDisabled(false);

    mw_imgCorrectionPanel->displayHistogram(histogram, m_histRole);

    m_waitDialogMgr.closeDialog(pid);
}

void MainWindow::imageCorrected(const QUuid &pid, qint64 elapsedTime) {
    logProcessFinished(pid, elapsedTime);

    m_openFileAction->setDisabled(false);
    m_createImageAction->setDisabled(false);
    m_runAction->setDisabled(false);
    m_selectDeviceAction->setDisabled(false);

    m_waitDialogMgr.closeDialog(pid);
}

void MainWindow::logProcessFinished(const QUuid &pid, qint64 elapsedTime) {
    float pixPerSec = 1000.f * (m_coreApp->originalImage().size().width() * m_coreApp->originalImage().size().height()) / elapsedTime;

    QString logStr = tr("%1 - Processing done in %2 ms. Approx %3 px/sec.")
                        .arg(pid.toString(QUuid::WithBraces))
                        .arg(elapsedTime)
                        .arg(pixPerSec);

    mw_labelElapsedTime->setText(logStr);
    m_coreApp->logOutput(logStr);
}

void MainWindow::showOriginalImage() {
    mw_tabWidget->setCurrentWidget(mw_origImgView);
    mw_origImgView->setPixmap(QPixmap::fromImage(m_coreApp->originalImage()));
    mw_processedImgView->setPixmap(QPixmap());

    mw_labelImgInfo->setText(tr("%1x%2 (%3 bytes)")
                             .arg(m_coreApp->originalImage().width())
                             .arg(m_coreApp->originalImage().height())
                             .arg(m_coreApp->originalImage().sizeInBytes()));

    mw_imgCorrectionPanel->clearOriginalImageHistogram();
    mw_imgCorrectionPanel->clearProcessedImageHistogram();

    startComputeHistogram(m_coreApp->originalImage(), Panels::ImageCorrectionPanel::OriginalImageHistogram);
}

void MainWindow::showProcessedImage() {
    mw_tabWidget->setCurrentWidget(mw_processedImgView);
    mw_processedImgView->setPixmap(QPixmap::fromImage(m_coreApp->processedImage()));

    mw_imgCorrectionPanel->clearProcessedImageHistogram();

    startComputeHistogram(m_coreApp->processedImage(), Panels::ImageCorrectionPanel::ProcessedImageHistogram);
}

void MainWindow::startConv2D() {
    QUuid pid = m_coreApp->startConv2DProcess(m_coreApp->getConvKernelAt(mw_convKernelComboBox->currentIndex()));

    if(pid.isNull()) {
        return;
    }

    m_openFileAction->setDisabled(true);
    m_createImageAction->setDisabled(true);
    m_runAction->setDisabled(true);
    m_selectDeviceAction->setDisabled(true);

    Dialogs::WaitDialog *dialog = m_waitDialogMgr.createWaitDialog(pid, tr("Processing image..."),
                                                                    Dialogs::WaitDialog::Flags::ShowProgress |
                                                                    Dialogs::WaitDialog::Flags::Cancelable);

    connect(dialog, &Dialogs::WaitDialog::cancelProcess, m_coreApp->ocl(), &Core::OCLWrapper::requestKernelCancelation);
    connect(m_coreApp->ocl(), &Core::OCLWrapper::kernelCancelationRequested, dialog, &Dialogs::WaitDialog::cancelProgressPending);
}

void MainWindow::startComputeHistogram(const QImage &img, Panels::ImageCorrectionPanel::HistogramRole histRole) {
    m_histRole = histRole;

    QUuid pid = m_coreApp->startComputeHistogram(img);

    if(pid.isNull()) {
        return;
    }

    m_runAction->setDisabled(true);
    m_selectDeviceAction->setDisabled(true);

    m_waitDialogMgr.createWaitDialog(pid, tr("Computing histogram..."));
}

void MainWindow::startImageCorrection(const QString &kernelPath) {
    QUuid pid = m_coreApp->startImageCorrection(kernelPath, mw_imgCorrectionPanel->originalImageHistogram().getCDF());

    if(pid.isNull()) {
        return;
    }

    m_openFileAction->setDisabled(true);
    m_createImageAction->setDisabled(true);
    m_runAction->setDisabled(true);
    m_selectDeviceAction->setDisabled(true);

    Dialogs::WaitDialog *dialog = m_waitDialogMgr.createWaitDialog(pid, tr("Correcting image..."),
                                                                    Dialogs::WaitDialog::Flags::ShowProgress |
                                                                    Dialogs::WaitDialog::Flags::Cancelable);

    connect(dialog, &Dialogs::WaitDialog::cancelProcess, m_coreApp->ocl(), &Core::OCLWrapper::requestKernelCancelation);
    connect(m_coreApp->ocl(), &Core::OCLWrapper::kernelCancelationRequested, dialog, &Dialogs::WaitDialog::cancelProgressPending);
}

void MainWindow::openImage() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open image file"), QString(),
                                              tr("Image files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(fn.isEmpty()) {
        return;
    }

    Dialogs::WaitDialog *dialog = new Dialogs::WaitDialog(tr("Opening image..."));
    Core::Threads::ImgLoader *imgLoader = new Core::Threads::ImgLoader(fn);

    connect(imgLoader, &Core::Threads::ImgLoader::loaded, this, [this, dialog, fn](QImage img, qint64 et) {
        mw_labelElapsedTime->setText(tr("Image loaded in %1 ms.").arg(et));
        m_coreApp->logInfo(tr("[%1] Image loaded in %2 ms.").arg(fn).arg(et));

        m_coreApp->setOriginalImage(img);

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
    Dialogs::CreateImageDialog *dialog = new Dialogs::CreateImageDialog(this);
    dialog->exec();

    if(dialog->result() != QMessageBox::Accepted) {
        return;
    }

    Dialogs::CreateImageDialog::ImageSettings_t settings = dialog->getImageSettings();

    if((settings.width == 0) || (settings.height == 0)) {
        return;
    }

    QImage img(settings.width, settings.height, QImage::Format_RGB888);
    img.fill(settings.fillColor);

    m_coreApp->logInfo(tr("Created image of size %1x%2.").arg(settings.width).arg(settings.height));

    m_coreApp->setOriginalImage(img);
}

void MainWindow::exportProcessedImage(bool closeWhenFinished) {
    if(m_coreApp->processedImage().isNull()) {
        return;
    }

    QString fn = QFileDialog::getSaveFileName(this, tr("Save image file"), QString(),
                                              tr("Image files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(fn.isEmpty()) {
        return;
    }

    Dialogs::WaitDialog *dialog = new Dialogs::WaitDialog(tr("Exporting image..."));
    Core::Threads::ImgExport *imgExport = new Core::Threads::ImgExport(fn, m_coreApp->processedImage());

    connect(imgExport, &Core::Threads::ImgExport::exported, this, [this, dialog, fn, closeWhenFinished](qint64 et) {
        m_coreApp->logInfo(tr("[%1] Image saved in %2 ms.").arg(fn).arg(et));

        delete dialog;

        if(closeWhenFinished) {
            close();
        }
    });

    dialog->show();

    QThreadPool::globalInstance()->start(imgExport);
}

void MainWindow::filterSelected(int index) {
    Core::Processing::ConvKernels::ConvKernel *k = m_coreApp->getConvKernelAt(index);
    k->select();

    mw_dockFilterSettings->setConvKernel(k);
}

void MainWindow::chooseProcessingOptions() {
    m_processingOptions.chunkFactor = m_coreApp->ocl()->getChunkFactor();

    Dialogs::ProcessOptionsDialog dialog(&m_processingOptions, this);
    dialog.exec();

    if(dialog.result() != QMessageBox::Accepted) {
        return;
    }

    m_coreApp->ocl()->setChunkFactor(m_processingOptions.chunkFactor);
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

bool MainWindow::saveOnExit() {
    static bool firstCall = true;

    if(!firstCall) {
        return false;
    }

    if(m_coreApp->processedImage().isNull()) {
        return false;
    }

    if(QMessageBox::question(this, tr("Unsaved file"), tr("Save processed image before closing ?"),
                             QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return false;
    }

    exportProcessedImage(true);

    firstCall = false;

    return true;
}

void MainWindow::buildKernelComboBox() {
    mw_convKernelComboBox = new QComboBox(this);
    connect(mw_convKernelComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::filterSelected);

    for(Core::Processing::ConvKernels::ConvKernel *k : m_coreApp->convKernels()) {
        mw_convKernelComboBox->addItem(k->getName());
    }
}

void MainWindow::buildMenus() {
    mw_fileMenu = menuBar()->addMenu(tr("&File"));

    m_openFileAction = mw_fileMenu->addAction(QIcon(":/icons/folder-horizontal-open.png"), tr("&Open"), tr("Ctrl+O"), this, &MainWindow::openImage);
    m_createImageAction = mw_fileMenu->addAction(QIcon(":/icons/image-new.png"), tr("&Create image"), tr("Ctrl+N"), this, &MainWindow::createImage);
    m_exportAction = mw_fileMenu->addAction(QIcon(":/icons/disk.png"), tr("Export processed image"), tr("Ctrl+E"), this, &MainWindow::exportProcessedImage);
    mw_fileMenu->addSeparator();
    m_selectDeviceAction = mw_fileMenu->addAction(QIcon(":/icons/graphic-card.png"), tr("Select &device"), this, [this]() {
        Dialogs::SelectDeviceDialog dialog(m_coreApp->devices());
        if(dialog.exec() == QDialog::Accepted) {
            if(!m_coreApp->ocl()->isRunning()) {
                m_coreApp->initOpenCL(dialog.getDevice());
                displayDeviceName();
            }
        }
    });
    mw_fileMenu->addSeparator();
    m_exitAction = mw_fileMenu->addAction(QIcon(":/icons/door-open-in.png"), tr("&Exit"), tr("Ctrl+W"), this, [](){qApp->exit();});

    mw_processMenu = menuBar()->addMenu(tr("&Process"));
    m_processOptionsAction = mw_processMenu->addAction(QIcon(":/icons/gear.png"), tr("Process &options"), this, &MainWindow::chooseProcessingOptions);
    mw_processMenu->addSeparator();
    m_reloadKernelAction = mw_processMenu->addAction(QIcon(":/icons/arrow-circle-double.png"), tr("Reload current &kernel"), tr("F5"), this, [this]() {
        filterSelected(mw_convKernelComboBox->currentIndex());
    });
    m_runAction = mw_processMenu->addAction(QIcon(":/icons/control.png"), tr("&Run"), tr("Ctrl+R"), this, &MainWindow::startConv2D);
    m_backfeedAction = mw_processMenu->addAction(QIcon(":/icons/arrow-transition-180.png"), tr("&Backfeed"), tr("Ctrl+B"), this, [this](){
        if(!m_coreApp->processedImage().isNull()) {
            m_coreApp->setOriginalImage(m_coreApp->processedImage());
        }
    });

    mw_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_aboutAction = mw_helpMenu->addAction(QIcon(":/icons/information-balloon.png"), tr("&About this program"), this, &MainWindow::showAboutDialog);
    m_aboutQtAction = mw_helpMenu->addAction(tr("About &Qt"), this, [this]() {
        QMessageBox::aboutQt(this);
    });

    m_openCLDevices = mw_helpMenu->addAction(tr("Open&CL Devices"), this, [this]() {
        QMessageBox::information(this, tr("OpenCL Devices"), Core::OCLUtils::getDevicesInfoStr());
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
    mw_labelDevice->setText(m_coreApp->ocl()->getDeviceName());
    m_coreApp->logInfo(tr("Selected device : %1").arg(m_coreApp->ocl()->getDeviceName()));
}

void MainWindow::buildUI() {
    buildFilterSettingsView();
    buildPanels();

    buildKernelComboBox();
    buildMenus();
    buildView();
}

void MainWindow::buildPanels() {
    mw_logPanel = new Panels::LogPanel(this);
    mw_logPanel->addLogger(m_coreApp);
    addDockWidget(Qt::BottomDockWidgetArea, mw_logPanel);

    mw_imgCorrectionPanel = new Panels::ImageCorrectionPanel(this);
    addDockWidget(Qt::RightDockWidgetArea, mw_imgCorrectionPanel);

    connect(mw_imgCorrectionPanel, &Panels::ImageCorrectionPanel::convertToGrayscale, this, [=]() {
        startImageCorrection(":/ocl/convertGrayscale.cl");
    });

    connect(mw_imgCorrectionPanel, &Panels::ImageCorrectionPanel::invertColors, this, [=]() {
        startImageCorrection(":/ocl/invertColors.cl");
    });

    connect(mw_imgCorrectionPanel, &Panels::ImageCorrectionPanel::equalizeHistogram, this, [=]() {
        startImageCorrection(":/ocl/equalizeHistogram.cl");
    });
}

void MainWindow::buildView() {
    mw_tabWidget = new QTabWidget(this);

    mw_origImgView = new ImageViewerContainer(tr("Original image"), this);
    mw_processedImgView = new ImageViewerContainer(tr("Processed image"), this);

    mw_codeEditor = new CodeEditorContainter(this);
    connect(mw_codeEditor, &CodeEditorContainter::useFile, this, [=](const QString &fn) {
        m_coreApp->convKernels().at(mw_convKernelComboBox->currentIndex())->setSourceFilePath(fn);
        filterSelected(mw_convKernelComboBox->currentIndex());
        m_coreApp->startConv2DProcess(m_coreApp->getConvKernelAt(mw_convKernelComboBox->currentIndex()));
    });

    mw_tabWidget->addTab(mw_origImgView, tr("Original"));
    mw_tabWidget->addTab(mw_processedImgView, tr("Processed"));
    mw_tabWidget->addTab(mw_codeEditor, tr("Code editor"));

    setCentralWidget(mw_tabWidget);
}

void MainWindow::buildFilterSettingsView() {
    mw_dockFilterSettings = new Panels::FilterSettingsDock(this);

    addDockWidget(Qt::LeftDockWidgetArea, mw_dockFilterSettings);
}

void MainWindow::closeEvent(QCloseEvent *ev) {
    if(m_coreApp->ocl()->isRunning()) {
        ev->ignore();

        if(QMessageBox::question(this, tr("Cancel work in progress"), tr("A kernel is currently running. \nDo you want to abort it then close the propgram ?"),
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {

            m_coreApp->ocl()->requestKernelCancelation();

            m_closeAfterKernelCanceled = true;
        }

        return;
    }

    if(saveOnExit()) {
        ev->ignore();

        return;
    }

    ev->accept();
}
