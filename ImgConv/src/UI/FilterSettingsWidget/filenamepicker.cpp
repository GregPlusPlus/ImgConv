#include "filenamepicker.h"

FileNamePicker::FileNamePicker(const QString &title, const QString &filters, QWidget *parent)
    : QWidget{parent} {
    setContentsMargins(0, 0, 0, 0);

    m_layout = new QHBoxLayout;
    m_layout->setSpacing(0);

    mw_fileName = new QLineEdit(this);
    connect(mw_fileName, &QLineEdit::textChanged, this, &FileNamePicker::fileNameChanged);

    mw_browse = new QPushButton(tr("..."), this);
    mw_browse->setMaximumWidth(40);
    connect(mw_browse, &QPushButton::clicked, [=]() {
        QString fn = QFileDialog::getOpenFileName(this, title, QString(), filters);
        if(!fn.isEmpty()) {
            setFileName(fn);
        }
    });

    m_layout->addWidget(mw_fileName);
    m_layout->addWidget(mw_browse);

    setLayout(m_layout);
}

QString FileNamePicker::getFileName() const {
    return mw_fileName->text();
}

void FileNamePicker::setFileName(const QString &fn) {
    mw_fileName->setText(fn);
}
