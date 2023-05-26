/**
 ** This file is part of the ImgConv project.
 ** Copyright 2022-2023 Grégoire BOST <bostgregoire@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "Core/Processing/processing.h"

bool Processing::processImg(OCLWrapper *ocl, const QImage &in, QImage &out, const QVector<QVector<float>> &k) {
    int imgW = in.width();
    int imgH = in.height();
    size_t inSize = in.sizeInBytes();

    ocl->releaseAll();

    // Convolution kernel buffer
    ConvKernel1DArray kernel1DArray(k);

    // Output buffer
    uint8_t *outImg = nullptr;
    size_t outSize = 0;

    // Create INPUT RGB buffer
    if(ocl->addBuffer(inSize, CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Create OUTPUT RGB buffer
    if(ocl->addBuffer(inSize, CL_MEM_READ_WRITE) < 0) {
        return false;
    }

    // Create convolution kernel buffer
    if(ocl->addBuffer(kernel1DArray.buffSize(), CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Write INPUT buffer
    if(!ocl->writeBuffer(0, in.bits(), inSize)) {
        return false;
    }

    // Write convolution kernel buffer
    if(!ocl->writeBuffer(2, (uint8_t*)kernel1DArray.getKArray(), kernel1DArray.buffSize())) {
        return false;
    }

    // Create Kernel parameters
    //   First set all the buffers
    for(size_t i = 0; i < ocl->getNumberOfBuffers(); i ++) {
        ocl->setKernelArg(i, i);

        if(ocl->ret() != CL_SUCCESS) {
            return false;
        }
    }

    // Run kernel
    ocl->runKernel(in.size());
    if(ocl->ret() != CL_SUCCESS) {
        return false;
    }

    // Read OUTPUT buffer
    if(!ocl->readBuffer(1, &outImg, &outSize)) {
        return false;
    }

    // Convert back buffer to image
    out = QImage((const uchar *)outImg, imgW, imgH, QImage::Format_RGB888).copy();
    delete[] outImg;

    ocl->releaseAll();

    return true;
}

void Processing::registerConvKernels(QList<ConvKernels::ConvKernel *> *l, QObject *parent) {
    l->append(new ConvKernels::GaussianBlur(parent));
    l->append(new ConvKernels::Emboss(parent));
    l->append(new ConvKernels::Ridge(parent));
    l->append(new ConvKernels::Sobel(parent));
    l->append(new ConvKernels::Sharpen(parent));
    l->append(new ConvKernels::UnsharpMasking(parent));
    l->append(new ConvKernels::MotionBlur(parent));
    l->append(new ConvKernels::Unity(parent));
    l->append(new ConvKernels::Custom(parent));
}

QString Processing::createOCLProgramOptions(const QSize &imgSize, const QSize &matSize) {
    return QString("-DW=%1 -DH=%2 -DKW=%3 -DKH=%4 -DVRSEED=\"{%5, %6, %7, %8}\" -I%9")
                    .arg(imgSize.width())
                    .arg(imgSize.height())
                    .arg(matSize.width())
                    .arg(matSize.height())
                    .arg(QRandomGenerator::global()->generate())
                    .arg(QRandomGenerator::global()->generate())
                    .arg(QRandomGenerator::global()->generate())
                    .arg(QRandomGenerator::global()->generate())
                    .arg(QCoreApplication::applicationDirPath() + "/kCLinclude");
}
