#ifndef SELECTDEVICEDIALOG_H
#define SELECTDEVICEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QList>

#include "Core/OCLWrapper/oclwrapper.h"

class SelectDeviceDialog : public QDialog
{
    Q_OBJECT
public:
    SelectDeviceDialog(QList<OCLWrapper::Device> devices);

    OCLWrapper::Device getDevice();

private:
    QFormLayout *m_layout;
    QDialogButtonBox *mw_buttonBox;
    QComboBox *mw_combo;
private:
    QList<OCLWrapper::Device> m_devices;
};

#endif // SELECTDEVICEDIALOG_H
