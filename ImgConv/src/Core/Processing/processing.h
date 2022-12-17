#ifndef PROCESSING_H
#define PROCESSING_H

#include <QPixmap>
#include <QImage>

#include "Core/Processing/convkernel1darray.h"
#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/Utils/utils.h"

namespace Processing {
    bool processImg(OCLWrapper *ocl, const QImage &in, QImage &out, const QVector<QVector<float>> &k);
};

#endif // PROCESSING_H
