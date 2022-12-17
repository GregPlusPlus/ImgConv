#ifndef RGB1DARRAY_H
#define RGB1DARRAY_H

#include <QObject>
#include <QImage>
#include <QPicture>

class RGB1DArray : public QObject
{
    Q_OBJECT
public:
    explicit RGB1DArray();
    explicit RGB1DArray(const QImage &i);
    explicit RGB1DArray(size_t s);
    virtual ~RGB1DArray();

    uint8_t *getR() const;
    uint8_t *getG() const;
    uint8_t *getB() const;
    size_t size() const;

    void fromImage(const QImage &i);

    void freeAll();
signals:

public:
    uint8_t *m_R = nullptr;
    uint8_t *m_G = nullptr;
    uint8_t *m_B = nullptr;

    size_t m_s = 0;

};

#endif // RGB1DARRAY_H
