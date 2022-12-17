#include "convkernel1darray.h"

ConvKernel1DArray::ConvKernel1DArray(const QVector<QVector<float> > &k) {
    m_s = k.size() * k[0].size();
    m_k = new float[m_s];

    for(int y = 0; y < k.size(); y ++) {
        for(int x = 0; x < k[0].size(); x ++) {
            size_t i = (y * k[0].size()) + x;

            m_k[i] = k[y][x];
        }
    }
}

ConvKernel1DArray::~ConvKernel1DArray() {
    if(m_k) {
        delete[] m_k;
    }
}

size_t ConvKernel1DArray::size() const {
    return m_s;
}

float *ConvKernel1DArray::getK() const {
    return m_k;
}
