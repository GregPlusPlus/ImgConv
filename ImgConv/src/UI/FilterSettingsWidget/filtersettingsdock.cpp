#include "filtersettingsdock.h"

FilterSettingsDock::FilterSettingsDock(QWidget *parent)
    : QDockWidget(tr("Filter settings"), parent) {
    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    setMinimumWidth(200);

    mw_container = new QWidget(this);

    setWidget(mw_container);
}

void FilterSettingsDock::setConvKernel(ConvKernels::ConvKernel *k) {
    for(FilterSettingsWidget *w : m_FilterSettingsWidgets) {
        if(w) {
            delete w;
        }
    }

    m_FilterSettingsWidgets.clear();

    if(m_layout) {
        delete m_layout;
    }
    m_layout = new QVBoxLayout;
    mw_container->setLayout(m_layout);

    for(ConvKernels::ConvKenrelSetting *s : k->settings()) {
        FilterSettingsWidget *w = new FilterSettingsWidget(s, mw_container);
        w->show();
        m_FilterSettingsWidgets.append(w);
        m_layout->addWidget(w);
    }

    m_layout->addStretch();
}
