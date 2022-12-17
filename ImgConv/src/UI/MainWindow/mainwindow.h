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

#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Processing/rgb1darray.h"
#include "Core/Processing/convkernel1darray.h"
#include "Core/Utils/utils.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void startProcess();

private:
    void initOpenCL();
    void buildMenus();
    void buildView();
    bool processImg(const QVector<QVector<float>> &k);

private:
    QHBoxLayout *m_layout;
    QWidget *m_centralWidget;
    QLabel *m_origImgLabel;
    QLabel *m_prcdImgLabel;
    QLabel *m_labelDevice;
    QLabel *m_labelElapsedTime;
    QMenu *m_fileMenu;
    QMenu *m_processMenu;
    QAction *m_openFileAction;
    QAction *m_exitAction;
    QAction *m_runAction;

private:
    OCLWrapper *m_wrapper;
    QString m_deviceName;
    QImage m_original;
    QImage m_processed;
};
#endif // MAINWINDOW_H
