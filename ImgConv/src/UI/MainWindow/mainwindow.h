#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QList>
#include <QElapsedTimer>
#include <QImageReader>
#include <QThreadPool>

#include "app_strings.h"

#include "UI/ImageViewer/imageviewer.h"
#include "UI/FilterSettingsWidget/filtersettingsdock.h"
#include "UI/WaitDialog/waitdialog.h"
#include "UI/SelectDeviceDialog/selectdevicedialog.h"
#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Processing/convkernel1darray.h"
#include "Core/Processing/Kernels/kernels.h"
#include "Core/Threads/threads.h"
#include "Core/Utils/utils.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void exportFile();
    void startProcess();
    void filterSelected(int index);

private:
    void initCore();
    void initOpenCL(const OCLWrapper::Device &device);
    void createOCLProgram(const QString &options);
    void buildMenus();
    void updateDeviceNameStatusBar();
    void buildView();
    void buildFilterSettingsView();
    void buildKernelComboBox();
    void showOriginalImage(const QImage &img);

private:
    QTabWidget *mw_tabWidget;
    ImageViewer *mw_origImgView;
    ImageViewer *mw_prcdImgView;
    QComboBox *mw_convKernelComboBox;
    FilterSettingsDock *mw_dockFilterSettings;
    QLabel *mw_labelDevice;
    QLabel *mw_labelImgInfo;
    QLabel *mw_labelElapsedTime;
    QMenu *mw_fileMenu;
    QMenu *mw_processMenu;
    QMenu *mw_helpMenu;
    QToolBar *mw_toolBar;
    QAction *m_openFileAction;
    QAction *m_exportAction;
    QAction *m_selectDeviceAction;
    QAction *m_exitAction;
    QAction *m_reloadKernelAction;
    QAction *m_runAction;
    QAction *m_backfeedAction;
    QAction *m_aboutAction;
    QAction *m_aboutQtAction;
    QAction *m_openCLDevices;

private:
    OCLWrapper *m_ocl = nullptr;
    QList<OCLWrapper::Device> m_devices;
    QImage m_original;
    QImage m_processed;
    QList<ConvKernels::ConvKernel*> m_convKernels;
};
#endif // MAINWINDOW_H
