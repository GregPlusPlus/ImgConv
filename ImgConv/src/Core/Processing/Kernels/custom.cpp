#include "custom.h"

ConvKernels::Custom::Custom(QObject *parent)
    : ConvKernel{parent} {

}

QVector<QVector<float> > ConvKernels::Custom::getMat() const {
    return m_k;
}

float ConvKernels::Custom::getScalar() const {
    return m_s;
}

QString ConvKernels::Custom::getName() const {
    return tr("Custom kernel");
}

void ConvKernels::Custom::select() {
    QString fn = QFileDialog::getOpenFileName(nullptr, tr("Open kernel as image file"), QString(),
                                              tr("Image files (*.png *.jpg *.bmp)"));

    if(fn.isEmpty()) {
        return;
    }

    QImage kImg(fn);

    Utils::imageToMatrix(m_k, kImg);

    m_s = 1.f/Utils::matrixSumCoef(m_k);
}
