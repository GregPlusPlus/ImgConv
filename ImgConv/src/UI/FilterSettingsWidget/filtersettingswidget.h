#ifndef FILTERSETTINGSWIDGET_H
#define FILTERSETTINGSWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFormLayout>

#include "Core/Processing/convkernel.h"

class FilterSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterSettingsWidget(ConvKernels::ConvKenrelSetting *setting, QWidget *parent = nullptr);

    ConvKernels::ConvKenrelSetting *setting() const;

signals:

private:
    QFormLayout *m_layout;

    ConvKernels::ConvKenrelSetting  *m_setting;

};

#endif // FILTERSETTINGSWIDGET_H
