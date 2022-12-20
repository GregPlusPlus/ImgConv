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
#include <QList>
#include <QElapsedTimer>
#include <QImageReader>

#include "UI/ImageViewer/imageviewer.h"
#include "UI/FilterSettingsWidget/filtersettingsdock.h"
#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Processing/convkernel1darray.h"
#include "Core/Processing/Kernels/kernels.h"
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
    void initOpenCL();
    void createOCLProgram(const QString &options);
    void buildMenus();
    void buildView();
    void buildFilterSettingsView();
    void buildKernelComboBox();
    void loadImage(const QImage &img);

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
    QToolBar *mw_toolBar;
    QAction *m_openFileAction;
    QAction *m_exportAction;
    QAction *m_exitAction;
    QAction *m_reloadKernelAction;
    QAction *m_runAction;
    QAction *m_backfeedAction;

private:
    OCLWrapper *m_ocl;
    QString m_deviceName;
    QImage m_original;
    QImage m_processed;
    QList<ConvKernels::ConvKernel*> m_convKernels;
};
#endif // MAINWINDOW_H
