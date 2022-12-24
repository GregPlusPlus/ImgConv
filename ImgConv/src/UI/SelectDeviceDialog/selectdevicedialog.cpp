#include "selectdevicedialog.h"

SelectDeviceDialog::SelectDeviceDialog(QList<OCLWrapper::Device> devices)
    : m_devices{devices} {
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    setWindowTitle(tr("Select device"));
    setWindowIcon(QIcon(":/icons/graphic-card.png"));

    m_layout = new QFormLayout;

    mw_combo = new QComboBox(this);
    for(const OCLWrapper::Device &d : m_devices) {
        mw_combo->addItem(d.name);
    }

    m_layout->addRow(tr("Device :"), mw_combo);

    mw_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                        QDialogButtonBox::Cancel,
                                        this);

    connect(mw_buttonBox, &QDialogButtonBox::accepted, this, &SelectDeviceDialog::accept);
    connect(mw_buttonBox, &QDialogButtonBox::rejected, this, &SelectDeviceDialog::reject);

    m_layout->addWidget(mw_buttonBox);

    setLayout(m_layout);
}

OCLWrapper::Device SelectDeviceDialog::getDevice() {
    return m_devices.at(mw_combo->currentIndex());
}
