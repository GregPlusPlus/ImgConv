#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVector>
#include <QElapsedTimer>
#include <QImageReader>

#include "UI/ImageViewer/imageviewer.h"
#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Processing/convkernel1darray.h"
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

private:
    void initOpenCL();
    void buildMenus();
    void buildView();

private:
    QHBoxLayout *m_layout;
    QWidget *mw_centralWidget;
    ImageViewer *mw_origImgView;
    ImageViewer *mw_prcdImgView;
    QLabel *mw_labelDevice;
    QLabel *mw_labelImgInfo;
    QLabel *mw_labelElapsedTime;
    QMenu *mw_fileMenu;
    QMenu *mw_processMenu;
    QAction *m_openFileAction;
    QAction *m_exportAction;
    QAction *m_exitAction;
    QAction *m_runAction;

private:
    OCLWrapper *m_ocl;
    QString m_deviceName;
    QImage m_original;
    QImage m_processed;
};
#endif // MAINWINDOW_H
