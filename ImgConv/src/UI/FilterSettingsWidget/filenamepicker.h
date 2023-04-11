#ifndef FILENAMEPICKER_H
#define FILENAMEPICKER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include <QFileDialog>

#include <QHBoxLayout>

class FileNamePicker : public QWidget
{
    Q_OBJECT
public:
    explicit FileNamePicker(const QString &title, const QString &filters, QWidget *parent = nullptr);

    QString getFileName() const;

public slots:
    void setFileName(const QString &fn);

signals:
    void fileNameChanged(const QString &fn);

private:
    QHBoxLayout *m_layout;

    QLineEdit *mw_fileName;
    QPushButton *mw_browse;

};

#endif // FILENAMEPICKER_H
