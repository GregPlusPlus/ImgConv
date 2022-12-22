#include "waitdialog.h"

WaitDialog::WaitDialog(const QString &text) {
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint |
                   Qt::WindowTitleHint | Qt::Tool | Qt::CustomizeWindowHint);
    setWindowTitle(tr("Work in progress"));
    setWindowIcon(QIcon(":/icons/hourglass.png"));

    m_layout = new QHBoxLayout;

    mw_spinnerLabel = new QLabel(this);
    mw_textLabel = new QLabel(this);

    m_layout->addWidget(mw_spinnerLabel);

    QMovie *mv = new QMovie(":/icons/spinner.gif", "gif", this);
    mv->setScaledSize(QSize(30, 30));
    mv->start();
    mw_spinnerLabel->setMovie(mv);

    m_layout->addWidget(mw_textLabel);

    setText(text);

    setLayout(m_layout);
}

QString WaitDialog::text() const {
    return mw_textLabel->text();
}

void WaitDialog::setText(const QString &text) {
    mw_textLabel->setText(text);
}
