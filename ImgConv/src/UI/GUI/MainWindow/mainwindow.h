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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QTabWidget>
#include <QComboBox>
#include <QDockWidget>
#include <QUndoView>
#include <QHBoxLayout>

#include <QVector>
#include <QMap>
#include <QList>
#include <QImageReader>
#include <QCloseEvent>
#include <QUndoStack>

#include "UI/Translator/translator.h"
#include "UI/GUI/Components/ImageViewer/imageviewer.h"
#include "UI/GUI/Panels/FilterSettingsPanel/filtersettingspanel.h"
#include "UI/GUI/Panels/LogPanel/logpanel.h"
#include "UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.h"
#include "UI/GUI/WaitDialogMgr/waitdialogmanager.h"
#include "UI/GUI/Dialogs/SelectDeviceDialog/selectdevicedialog.h"
#include "UI/GUI/Dialogs/CreateImageDialog/createimagedialog.h"
#include "UI/GUI/Dialogs/ProcessOptionsDialog/processoptionsdialog.h"
#include "UI/GUI/Components/CodeEditor/codeeditorcontainer.h"

#include "Core/App/app.h"
#include "Core/Settings/SettingsMgr/settingsmgr.h"

#include "UI/UndoRedo/Commands/undoredocommands.h"

namespace UI::GUI {
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Core::App *coreApp, Core::Settings::SettingsMgr *settingsMgr);
    ~MainWindow();

    bool doReload() const;

private slots:
    void connectCoreApp();
    void processError();
    void conv2DDone(const QUuid &pid, qint64 elapsedTime);
    void histogramComputed(const QUuid &pid, qint64 elapsedTime);
    void imageCorrected(const QUuid &pid, qint64 elapsedTime);
    void logProcessFinished(const QUuid &pid, qint64 elapsedTime);
    void showOriginalImage();
    void showProcessedImage();
    void startConv2DUserCode(const QString &fn);
    void startConv2D();
    void startComputeHistogram(const QImage &img, Panels::ImageCorrectionPanel::HistogramRole histRole);
    void startImageCorrection(const QString &kernelPath, const QString &name);
    void openImageGui();
    void loadImage(const QString &path);
    void createImage();
    void exportProcessedImage(bool closeWhenFinished = false);
    void filterSelected(int index);
    void chooseProcessingOptions();
    void selectDevice();
    void showAboutDialog();
    void listOpenCLDevices();
    bool saveOnExit();
    void buildMenus();
    void buildLangMenu();
    void langSelected(QAction *langAction);
    void displayDeviceName();
    void buildUI();
    void buildPanels();
    void buildUndoView();

    void buildView();
    void buildFilterSettingsView();
    void buildKernelComboBox();
    void restoreConvKernel(Core::Processing::ConvKernels::ConvKernel *convKernel);
    void setCloseAfterKernelCanceled();
    void clearCloseAfterKernelCanceled();
    bool getCloseAfterKernelCanceled();

private:
    QTabWidget *mw_tabWidget;
    Components::ImageViewer *mw_origImgView;
    Components::ImageViewer *mw_processedImgView;
    Components::CodeEditorView *mw_codeEditor;
    QComboBox *mw_convKernelComboBox;
    Panels::FilterSettingsPanel *mw_FilterSettingsPanel;
    Panels::LogPanel *mw_logPanel;
    Panels::ImageCorrectionPanel *mw_imgCorrectionPanel;
    QLabel *mw_labelDevice;
    QLabel *mw_labelImgInfo;
    QLabel *mw_labelElapsedTime;
    QMenu *mw_fileMenu;
    QMenu *mw_editMenu;
    QMenu *mw_processMenu;
    QMenu *mw_helpMenu;
    QToolBar *mw_toolBar;
    QAction *m_openFileAction;
    QAction *m_createImageAction;
    QAction *m_exportAction;
    QAction *m_selectDeviceAction;
    QAction *m_exitAction;
    QAction *m_undoAction;
    QAction *m_redoAction;
    QAction *m_processOptionsAction;
    QAction *m_reloadKernelAction;
    QAction *m_runAction;
    QAction *m_backfeedAction;
    QAction *m_aboutAction;
    QAction *m_langAction;
    QAction *m_aboutQtAction;
    QAction *m_openCLDevices;

private:
    Core::App *m_coreApp;
    Core::Settings::SettingsMgr *m_settingsMgr;
    QUndoStack *m_undoStack;

    Panels::ImageCorrectionPanel::HistogramRole m_histRole;
    WaitDialogManager m_waitDialogMgr;

private:
    bool m_closeAfterKernelCanceled = false;
    bool m_reload = false;

protected:
    void closeEvent(QCloseEvent *ev);
    void changeEvent(QEvent *ev);
    void moveEvent(QMoveEvent *ev);
};
}

#endif // MAINWINDOW_H
