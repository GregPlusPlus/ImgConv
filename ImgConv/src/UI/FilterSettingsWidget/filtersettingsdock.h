#ifndef FILTERSETTINGSDOCK_H
#define FILTERSETTINGSDOCK_H

#include <QDockWidget>
#include <QList>

#include "UI/FilterSettingsWidget/filtersettingswidget.h"

class FilterSettingsDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit FilterSettingsDock(QWidget *parent = 0);

public slots:
    void setConvKernel(ConvKernels::ConvKernel *k);

private:
    QWidget *mw_container;
    QVBoxLayout *m_layout = nullptr;

private:
    QList<FilterSettingsWidget*> m_FilterSettingsWidgets;
};

#endif // FILTERSETTINGSDOCK_H
