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

using namespace UI::GUI;

MainWindow::MainWindow(Core::App *coreApp, Core::Settings::SettingsMgr *settingsMgr)
    : QMainWindow{}, m_coreApp{coreApp}, m_settingsMgr{settingsMgr} {
    setWindowIcon(QIcon(":/icons/icon.png"));
    setWindowTitle(APP_NAME);

    m_undoStack = new QUndoStack(this);

    buildUI();

    connectCoreApp();

    setMinimumSize(QSize(1200, 800));

    setGeometry(m_settingsMgr->getWindowGeometry());
}

MainWindow::~MainWindow() {
    m_settingsMgr->setWindowGeometry(geometry());
}

void MainWindow::connectCoreApp() {
    connect(m_coreApp, &Core::App::originalImageChanged, this, &MainWindow::showOriginalImage);
    connect(m_coreApp, &Core::App::processedImageChanged, this, &MainWindow::showProcessedImage);

    connect(m_coreApp, &Core::App::conv2DDone, this, &MainWindow::conv2DDone);
    connect(m_coreApp, &Core::App::histogramComputingDone, this, &MainWindow::histogramComputed);
    connect(m_coreApp, &Core::App::imageCorrectionDone, this, &MainWindow::imageCorrected);

    connect(m_coreApp, &Core::App::processProgress, &m_waitDialogMgr, &WaitDialogManager::updateDialogProgress);
    connect(m_coreApp->ocl(), &Core::OCLWrapper::kernelCanceled, this, [this]() {
        m_coreApp->logOutput(tr("Kernel canceled"));

        if(getCloseAfterKernelCanceled()) {
            clearCloseAfterKernelCanceled();

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

void MainWindow::histogramComputed(const QUuid &pid, qint64 elapsedTime) {
    Q_UNUSED(elapsedTime)

    mw_imgCorrectionPanel->displayHistogram(m_coreApp->lastHistogramComputed(), m_histRole);
    if(m_histRole == Panels::ImageCorrectionPanel::OriginalImageHistogram) {
        m_coreApp->setOriginalImageHistogram(m_coreApp->lastHistogramComputed());
    }

    m_runAction->setDisabled(false);
    m_selectDeviceAction->setDisabled(false);

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

void MainWindow::startConv2DUserCode(const QString &fn) {
    m_coreApp->convKernels().at(mw_convKernelComboBox->currentIndex())->setSourceFilePath(fn);

    startConv2D();
}

void MainWindow::startConv2D() {
    UndoRedo::Commands::RunFilterCommand *command = new UndoRedo::Commands::RunFilterCommand(
                m_coreApp, m_coreApp->getConvKernelAt(mw_convKernelComboBox->currentIndex()));

    connect(command, &UndoRedo::Commands::RunFilterCommand::restoreConvKernel, this, &MainWindow::restoreConvKernel);

    connect(command, &UndoRedo::Commands::RunFilterCommand::processStarted, this, [=](const QUuid &pid){
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
    });

    m_undoStack->push(command);
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

void MainWindow::startImageCorrection(const QString &kernelPath, const QString &name) {
    UndoRedo::Commands::ImageCorrectionCommand *command = new UndoRedo::Commands::ImageCorrectionCommand(
                                m_coreApp, kernelPath, name, m_coreApp->originalImageHistogram().getCDF());

    connect(command, &UndoRedo::Commands::ImageCorrectionCommand::processStarted, this, [=](const QUuid &pid) {
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
    });

    m_undoStack->push(command);
}

void MainWindow::openImage() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open image file"), QString(),
                                              tr("Image files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(fn.isEmpty()) {
        return;
    }

    Core::Threads::ImgLoader *imgLoader = new Core::Threads::ImgLoader(fn);
    QUuid pid = imgLoader->getUUID();

    connect(imgLoader, &Core::Threads::ImgLoader::loaded, this, [this, fn, pid](QImage img, qint64 et) {
        mw_labelElapsedTime->setText(tr("Image loaded in %1 ms.").arg(et));
        m_coreApp->logInfo(tr("[%1] Image loaded in %2 ms.").arg(fn).arg(et));

        m_undoStack->push(new UndoRedo::Commands::OpenImageCommand(m_coreApp, img, fn));

        m_openFileAction->setDisabled(false);
        m_createImageAction->setDisabled(false);
        m_runAction->setDisabled(false);

        m_waitDialogMgr.closeDialog(pid);
    });

    m_openFileAction->setDisabled(true);
    m_createImageAction->setDisabled(true);
    m_runAction->setDisabled(true);

    m_waitDialogMgr.createWaitDialog(pid, tr("Opening image..."),
                                        Dialogs::WaitDialog::Flags::None);

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

    m_undoStack->push(new UndoRedo::Commands::CreateImageCommand(m_coreApp, settings));
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

    Core::Threads::ImgExport *imgExport = new Core::Threads::ImgExport(fn, m_coreApp->processedImage());
    QUuid pid = imgExport->getUUID();

    connect(imgExport, &Core::Threads::ImgExport::exported, this, [this, fn, pid, closeWhenFinished](qint64 et) {
        m_coreApp->logInfo(tr("[%1] Image saved in %2 ms.").arg(fn).arg(et));

        m_waitDialogMgr.closeDialog(pid);

        if(closeWhenFinished) {
            close();
        }
    });

    m_waitDialogMgr.createWaitDialog(pid, tr("Exporting image..."),
                                        Dialogs::WaitDialog::Flags::None);

    QThreadPool::globalInstance()->start(imgExport);
}

void MainWindow::filterSelected(int index) {
    Core::Processing::ConvKernels::ConvKernel *k = m_coreApp->getConvKernelAt(index);
    k->select();

    mw_FilterSettingsPanel->setConvKernel(k);
}

void MainWindow::chooseProcessingOptions() {
    Core::Processing::Options options = m_coreApp->getProcessingOptions();

    options.chunkFactor = m_coreApp->ocl()->getChunkFactor();

    Dialogs::ProcessOptionsDialog dialog(m_settingsMgr, &options, this);
    dialog.exec();

    if(dialog.result() != QMessageBox::Accepted) {
        return;
    }

    m_coreApp->setProcessingOptions(options);
}

void MainWindow::selectDevice() {
    Dialogs::SelectDeviceDialog dialog(m_coreApp->devices());
    connect(&dialog, &Dialogs::SelectDeviceDialog::listOpenCLDevices, this, &MainWindow::listOpenCLDevices);

    if(dialog.exec() == QDialog::Accepted) {
        if(!m_coreApp->ocl()->isRunning()) {
            m_coreApp->initOpenCL(dialog.getDevice());
            displayDeviceName();
        }
    }
}

void MainWindow::showAboutDialog() {
    Utils::showAboutDialog(this);
}

void MainWindow::listOpenCLDevices() {
    Utils::showOpenCLDevicesDialog(this);
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

void MainWindow::restoreConvKernel(Core::Processing::ConvKernels::ConvKernel *convKernel) {
    for(int i = 0; i < mw_convKernelComboBox->count(); i ++) {
        if(mw_convKernelComboBox->itemText(i) == convKernel->getName()) {
            mw_convKernelComboBox->setCurrentIndex(i);

            return;
        }
    }
}

void MainWindow::setCloseAfterKernelCanceled() {
    m_closeAfterKernelCanceled = true;
}

void MainWindow::clearCloseAfterKernelCanceled() {
    m_closeAfterKernelCanceled = false;
}

bool MainWindow::getCloseAfterKernelCanceled() {
    return m_closeAfterKernelCanceled;
}

bool MainWindow::doReload() const {
    return m_reload;
}

void MainWindow::buildMenus() {
    mw_fileMenu = menuBar()->addMenu(tr("&File"));

    m_openFileAction = mw_fileMenu->addAction(QIcon(":/icons/folder-horizontal-open.png"), tr("&Open"), tr("Ctrl+O"), this, &MainWindow::openImage);
    m_createImageAction = mw_fileMenu->addAction(QIcon(":/icons/image-new.png"), tr("&Create image"), tr("Ctrl+N"), this, &MainWindow::createImage);
    m_exportAction = mw_fileMenu->addAction(QIcon(":/icons/disk.png"), tr("&Export processed image"), tr("Ctrl+E"), this, &MainWindow::exportProcessedImage);
    mw_fileMenu->addSeparator();
    m_selectDeviceAction = mw_fileMenu->addAction(QIcon(":/icons/graphic-card.png"), tr("Select &device"), this, &MainWindow::selectDevice);
    mw_fileMenu->addSeparator();
    m_exitAction = mw_fileMenu->addAction(QIcon(":/icons/door-open-in.png"), tr("&Exit"), tr("Ctrl+W"), this, [](){qApp->exit();});

    mw_editMenu = menuBar()->addMenu(tr("&Edit"));
    m_undoAction = m_undoStack->createUndoAction(this, tr("&Undo"));
    m_undoAction->setIcon(QIcon(":/icons/arrow-curve-180-left.png"));
    m_undoAction->setShortcut(QKeySequence::Undo);
    mw_editMenu->addAction(m_undoAction);
    m_redoAction = m_undoStack->createRedoAction(this, tr("&Redo"));
    m_redoAction->setIcon(QIcon(":/icons/arrow-curve.png"));
    m_redoAction->setShortcut(QKeySequence::Redo);
    mw_editMenu->addAction(m_redoAction);

    mw_processMenu = menuBar()->addMenu(tr("&Process"));
    m_processOptionsAction = mw_processMenu->addAction(QIcon(":/icons/gear.png"), tr("Process &options"), this, &MainWindow::chooseProcessingOptions);
    mw_processMenu->addSeparator();
    m_reloadKernelAction = mw_processMenu->addAction(QIcon(":/icons/arrow-circle-double.png"), tr("Reload current &kernel"), tr("F5"), this, [this]() {
        filterSelected(mw_convKernelComboBox->currentIndex());
    });
    m_runAction = mw_processMenu->addAction(QIcon(":/icons/control.png"), tr("&Run"), tr("Ctrl+R"), this, &MainWindow::startConv2D);
    m_backfeedAction = mw_processMenu->addAction(QIcon(":/icons/arrow-transition-180.png"), tr("&Backfeed"), tr("Ctrl+B"), this, [this](){
        if(!m_coreApp->processedImage().isNull()) {
            m_undoStack->push(new UndoRedo::Commands::BackfeedImageCommand(m_coreApp));
        }
    });

    mw_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_aboutAction = mw_helpMenu->addAction(QIcon(":/icons/information-balloon.png"), tr("&About this program"), this, &MainWindow::showAboutDialog);
    m_langAction = mw_helpMenu->addAction(QIcon(":/icons/edit-language.png"), tr("&Language"));
    mw_helpMenu->addSeparator();
    m_aboutQtAction = mw_helpMenu->addAction(tr("About &Qt"), this, [this]() {
        QMessageBox::aboutQt(this);
    });

    m_openCLDevices = mw_helpMenu->addAction(tr("Open&CL Devices"), this, &MainWindow::listOpenCLDevices);

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

    buildLangMenu();
}

void MainWindow::buildLangMenu() {
    QStringList langs;
    langs << "system" << "default";
    langs << UI::Utils::Translator::listLanguages();

    QMenu *langMenu = new QMenu(this);
    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);

    connect(actionGroup, &QActionGroup::triggered, this, &MainWindow::langSelected);

    m_langAction->setMenu(langMenu);

    for(const QString &l : langs) {
        QAction *a = langMenu->addAction(l);
        a->setCheckable(true);

        if(m_settingsMgr->getLang() == l) {
            a->setChecked(true);
        }

        actionGroup->addAction(a);
    }
}

void MainWindow::langSelected(QAction *langAction) {
    if(!langAction) {
        return;
    }

    if(!langAction->isChecked()) {
        return;
    }

    if(QMessageBox::question(this, tr("Window reload"), tr("The window needs to be reloaded for the language selection to take effect. \nReload now ?"),
                             QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {

        m_reload = true;
        close();
    }
    m_settingsMgr->setLang(langAction->text());
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
    buildUndoView();
}

void MainWindow::buildPanels() {
    mw_logPanel = new Panels::LogPanel(this);
    mw_logPanel->addLogger(m_coreApp);
    addDockWidget(Qt::BottomDockWidgetArea, mw_logPanel);

    mw_imgCorrectionPanel = new Panels::ImageCorrectionPanel(this);
    addDockWidget(Qt::RightDockWidgetArea, mw_imgCorrectionPanel);

    connect(mw_imgCorrectionPanel, &Panels::ImageCorrectionPanel::convertToGrayscale, this, [=]() {
        startImageCorrection(":/ocl/convertGrayscale.cl", tr("Grayscale conversion"));
    });

    connect(mw_imgCorrectionPanel, &Panels::ImageCorrectionPanel::invertColors, this, [=]() {
        startImageCorrection(":/ocl/invertColors.cl", tr("Color inversion"));
    });

    connect(mw_imgCorrectionPanel, &Panels::ImageCorrectionPanel::equalizeHistogram, this, [=]() {
        startImageCorrection(":/ocl/equalizeHistogram.cl", tr("Histogram equalization"));
    });
}

void MainWindow::buildUndoView() {
    QDockWidget *undoDockWidget = new QDockWidget(this);
    undoDockWidget->setWindowTitle(tr("Command history"));
    undoDockWidget->setWidget(new QUndoView(m_undoStack));
    undoDockWidget->setMaximumWidth(200);

    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    addDockWidget(Qt::BottomDockWidgetArea, undoDockWidget);
}

void MainWindow::buildView() {
    mw_tabWidget = new QTabWidget(this);

    mw_origImgView = new Components::ImageViewer(tr("Original image"), this);
    mw_processedImgView = new Components::ImageViewer(tr("Processed image"), this);

    mw_codeEditor = new Components::CodeEditorView(this);
    connect(mw_codeEditor, &Components::CodeEditorView::useFile, this, &MainWindow::startConv2DUserCode);

    mw_tabWidget->addTab(mw_origImgView,        tr("Original"));
    mw_tabWidget->addTab(mw_processedImgView,   tr("Processed"));
    mw_tabWidget->addTab(mw_codeEditor,         tr("Code editor"));

    m_coreApp->setOriginalImage(QImage());
    m_coreApp->setProcessedImage(QImage());

    setCentralWidget(mw_tabWidget);
}

void MainWindow::buildFilterSettingsView() {
    mw_FilterSettingsPanel = new Panels::FilterSettingsPanel(this);

    addDockWidget(Qt::LeftDockWidgetArea, mw_FilterSettingsPanel);
}

void MainWindow::closeEvent(QCloseEvent *ev) {
    qsizetype numberOfWaitDialogs = m_waitDialogMgr.getNumberOfOpenDialogs();

    if(m_coreApp->ocl()->isRunning()) {
        ev->ignore();

        if(QMessageBox::question(this, tr("Cancel work in progress"), tr("A kernel is currently running. \nDo you want to abort it then close the propgram ?"),
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {

            m_coreApp->ocl()->requestKernelCancelation();

            setCloseAfterKernelCanceled();
        }

        return;
    } else if(numberOfWaitDialogs) {
        ev->ignore();

        QMessageBox::warning(this, tr("Process is running"), tr("Cannot close window, %1 proccess still running.")
                                                                .arg(numberOfWaitDialogs));

        return;
    }

    if(saveOnExit()) {
        ev->ignore();

        return;
    }

    ev->accept();
}

void MainWindow::changeEvent(QEvent *ev) {
    if(ev->type() == QEvent::WindowStateChange) {
        if(isMinimized()) {
            m_waitDialogMgr.hideAll();
        } else if(isVisible()) {
            m_waitDialogMgr.showAll();
        }
    }
}

void MainWindow::moveEvent(QMoveEvent *ev) {
    m_waitDialogMgr.moveAll(ev->pos() - ev->oldPos(), geometry());
}
