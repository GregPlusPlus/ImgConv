#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QPainter>

class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(const QString &title = QString(), QWidget *parent = nullptr);

    QPixmap pixmap() const;
    void setPixmap(const QPixmap &newPixmap);

    QString title() const;
    void setTitle(const QString &newTitle);

signals:

private:
    QString m_title;
    QPixmap m_pixmap;

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // IMAGEVIEWER_H
