#include "imageviewercontainer.h"

ImageViewerContainer::ImageViewerContainer(const QString &title, QWidget *parent)
    : QWidget{parent} {

    m_layout = new QVBoxLayout;

    mw_status = new QStatusBar(this);
    mw_status->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    mw_status->setSizeGripEnabled(false);

    mw_viewer = new ImageViewer(title, this);

    mw_fitButton = new QPushButton(QIcon(":/icons/magnifier-zoom-fit.png"), QString(), this);
    mw_fitButton->setToolTip(tr("Fit image"));
    connect(mw_fitButton, &QPushButton::clicked, mw_viewer, &ImageViewer::fitImage);

    mw_status->addPermanentWidget(mw_fitButton);

    m_layout->addWidget(mw_viewer);
    m_layout->addWidget(mw_status);

    setLayout(m_layout);
}

QPixmap ImageViewerContainer::pixmap() const {
    return mw_viewer->pixmap();
}

QString ImageViewerContainer::title() const {
    return mw_viewer->title();
}

void ImageViewerContainer::setPixmap(const QPixmap &pixmap) {
    mw_viewer->setPixmap(pixmap);
}

void ImageViewerContainer::setTitle(const QString &title) {
    mw_viewer->setTitle(title);
}
