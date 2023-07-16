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
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QTabWidget>
#include <QComboBox>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QVector>
#include <QMap>
#include <QList>
#include <QImageReader>
#include <QCloseEvent>

#include "app_strings.h"

#include "UI/ImageViewer/imageviewercontainer.h"
#include "UI/Panels/FilterSettingsPanel/filtersettingsdock.h"
#include "UI/Panels/LogPanel/logpanel.h"
#include "UI/Panels/ImageCorrectionPanel/imagecorrectionpanel.h"
#include "UI/WaitDialogMgr/waitdialogmgr.h"
#include "UI/Dialogs/SelectDeviceDialog/selectdevicedialog.h"
#include "UI/Dialogs/CreateImageDialog/createimagedialog.h"
#include "UI/Dialogs/ProcessOptionsDialog/processoptionsdialog.h"
#include "UI/CodeEditor/codeeditorcontainer.h"

#include "Core/App/app.h"

namespace UI {
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Core::App *coreApp);
    ~MainWindow();

private slots:
    void connectCoreApp();
    void processError();
    void conv2DDone(const QUuid &pid, qint64 elapsedTime);
    void histogramComputed(const QUuid &pid, qint64 elapsedTime, const Core::Processing::Algorithms::Histogram &histogram);
    void imageCorrected(const QUuid &pid, qint64 elapsedTime);
    void logProcessFinished(const QUuid &pid, qint64 elapsedTime);
    void showOriginalImage();
    void showProcessedImage();
    void startConv2D();
    void startComputeHistogram(const QImage &img, Panels::ImageCorrectionPanel::HistogramRole histRole);
    void startImageCorrection(const QString &kernelPath);
    void openImage();
    void createImage();
    void exportProcessedImage(bool closeWhenFinished = false);
    void filterSelected(int index);
    void chooseProcessingOptions();
    void showAboutDialog();
    bool saveOnExit();
    void buildMenus();
    void displayDeviceName();
    void buildUI();
    void buildPanels();
    void buildView();
    void buildFilterSettingsView();
    void buildKernelComboBox();

private:
    QTabWidget *mw_tabWidget;
    ImageViewerContainer *mw_origImgView;
    ImageViewerContainer *mw_processedImgView;
    CodeEditorContainter *mw_codeEditor;
    QComboBox *mw_convKernelComboBox;
    Panels::FilterSettingsDock *mw_dockFilterSettings;
    Panels::LogPanel *mw_logPanel;
    Panels::ImageCorrectionPanel *mw_imgCorrectionPanel;
    QLabel *mw_labelDevice;
    QLabel *mw_labelImgInfo;
    QLabel *mw_labelElapsedTime;
    QMenu *mw_fileMenu;
    QMenu *mw_processMenu;
    QMenu *mw_helpMenu;
    QToolBar *mw_toolBar;
    QAction *m_openFileAction;
    QAction *m_createImageAction;
    QAction *m_exportAction;
    QAction *m_selectDeviceAction;
    QAction *m_exitAction;
    QAction *m_processOptionsAction;
    QAction *m_reloadKernelAction;
    QAction *m_runAction;
    QAction *m_backfeedAction;
    QAction *m_aboutAction;
    QAction *m_aboutQtAction;
    QAction *m_openCLDevices;

private:
    Core::App *m_coreApp;

    Panels::ImageCorrectionPanel::HistogramRole m_histRole;
    WaitDialogMgr m_waitDialogMgr;

private:
    Core::Processing::Options m_processingOptions;
    bool m_closeAfterKernelCanceled = false;

protected:
    void closeEvent(QCloseEvent *ev);
};
}

#endif // MAINWINDOW_H
