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

#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Processing/rgb1darray.h"
#include "Core/Processing/convkernel1darray.h"

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
    QLabel *m_origImg;
    QLabel *m_prcdImg;
    QLabel *m_labelDevice;
    QMenu *m_fileMenu;
    QMenu *m_processMenu;
    QAction *m_openFileAction;
    QAction *m_exitAction;
    QAction *m_runAction;

private:
    OCLWrapper *m_wrapper;
    QString m_deviceName;
    QPixmap m_pixmap;
};
#endif // MAINWINDOW_H
