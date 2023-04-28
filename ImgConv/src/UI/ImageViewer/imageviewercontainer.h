#ifndef IMAGEVIEWERCONTAINER_H
#define IMAGEVIEWERCONTAINER_H

#include <QWidget>
#include <QPushButton>
#include <QStatusBar>

#include <QVBoxLayout>

#include "imageviewer.h"

class ImageViewerContainer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewerContainer(const QString &title = QString(), QWidget *parent = nullptr);

    QPixmap pixmap() const;
    QString title() const;

public slots:
    void setPixmap(const QPixmap &pixmap);
    void setTitle(const QString &title);

signals:

private:
    QVBoxLayout *m_layout;

    QStatusBar *mw_status;
    QPushButton *mw_fitButton;

    ImageViewer *mw_viewer;

};

#endif // IMAGEVIEWERCONTAINER_H
