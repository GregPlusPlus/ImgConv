#include "rgb1darray.h"

RGB1DArray::RGB1DArray()
    : QObject{} {

}

RGB1DArray::RGB1DArray(const QImage &i) {
    fromImage(i);
}

RGB1DArray::RGB1DArray(size_t s)
    : m_R{new uint8_t[s]}, m_G{new uint8_t[s]}, m_B{new uint8_t[s]}, m_s{s} {

}

RGB1DArray::~RGB1DArray() {
    freeAll();
}

uint8_t *RGB1DArray::getR() const {
    return m_R;
}

uint8_t *RGB1DArray::getG() const {
    return m_G;
}

uint8_t *RGB1DArray::getB() const {
    return m_B;
}

size_t RGB1DArray::size() const {
    return m_s;
}

void RGB1DArray::fromImage(const QImage &img) {
    freeAll();

    int imgW = img.width();
    int imgH = img.height();

    m_s = imgW * imgH;

    m_R = new uint8_t[m_s];
    m_G = new uint8_t[m_s];
    m_B = new uint8_t[m_s];

    for(int y = 0; y < imgH; y ++) {
        for (int x = 0; x < imgW; x ++) {
            size_t i = (y * imgW) + x;

            m_R[i] = qRed(img.pixel(x, y));
            m_G[i] = qGreen(img.pixel(x, y));
            m_B[i] = qBlue(img.pixel(x, y));
        }
    }
}

void RGB1DArray::freeAll() {
    m_s = 0;
    if(m_R) {
        delete[] m_R;
    }
    if(m_G) {
        delete[] m_G;
    }
    if(m_B) {
        delete[] m_B;
    }
}
