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

#include "algorithms.h"

bool Processing::Algorithms::conv2D(OCLWrapper *ocl, const QImage &in, QImage &out, const QVector<QVector<float>> &k) {
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

bool Processing::Algorithms::computeHistogram(OCLWrapper *ocl, const QImage &in, Histogram &hist) {
    const size_t inSize = in.sizeInBytes();
    const size_t numberOfLevels = 256;
    const size_t histBuffSize = numberOfLevels * sizeof(size_t);

    ocl->releaseAll();

    // Create INPUT RGB buffer
    if(ocl->addBuffer(inSize, CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Create OUTPUT R histogram buffer
    if(ocl->addBuffer(histBuffSize, CL_MEM_READ_WRITE) < 0) {
        return false;
    }

    // Create OUTPUT G histogram buffer
    if(ocl->addBuffer(histBuffSize, CL_MEM_READ_WRITE) < 0) {
        return false;
    }

    // Create OUTPUT B histogram buffer
    if(ocl->addBuffer(histBuffSize, CL_MEM_READ_WRITE) < 0) {
        return false;
    }

    // Init R,G,B histogram buffers to zero
    static const size_t zeroes[numberOfLevels] = {0};

    if(!ocl->writeBuffer(1, (uint8_t*)zeroes, histBuffSize)) {
        return false;
    }

    if(!ocl->writeBuffer(2, (uint8_t*)zeroes, histBuffSize)) {
        return false;
    }

    if(!ocl->writeBuffer(3, (uint8_t*)zeroes, histBuffSize)) {
        return false;
    }

    // Write INPUT buffer
    if(!ocl->writeBuffer(0, in.bits(), inSize)) {
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

    size_t* histBuffer[3] = {nullptr, nullptr, nullptr};
    size_t histSize = 0;

    // Read OUTPUT R histogram buffer
    if(!ocl->readBuffer(1, (uint8_t**)&(histBuffer[0]), &histSize)) {
        return false;
    }

    // Read OUTPUT G histogram buffer
    if(!ocl->readBuffer(2, (uint8_t**)&(histBuffer[1]), &histSize)) {
        return false;
    }

    // Read OUTPUT B histogram buffer
    if(!ocl->readBuffer(3, (uint8_t**)&(histBuffer[2]), &histSize)) {
        return false;
    }

    hist.r.clear();
    hist.g.clear();
    hist.b.clear();

    for(size_t i = 0; i < numberOfLevels; i ++) {
        hist.r.append(histBuffer[0][i]);
        hist.g.append(histBuffer[1][i]);
        hist.b.append(histBuffer[2][i]);
    }

    delete[] histBuffer[0];
    delete[] histBuffer[1];
    delete[] histBuffer[2];

    ocl->releaseAll();

    return true;
}

bool Processing::Algorithms::applyCorrection(OCLWrapper *ocl, const QImage &in, QImage &out, const Histogram &cdf) {
    int imgW = in.width();
    int imgH = in.height();
    size_t inSize = in.sizeInBytes();

    const size_t numberOfLevels = 256;
    const size_t cdfBuffSize = numberOfLevels * sizeof(size_t);

    ocl->releaseAll();

    // Output buffer
    uint8_t *outImg = nullptr;
    size_t outSize = 0;

    // Create INPUT RGB buffer
    if(ocl->addBuffer(inSize, CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Create INPUT CDF R buffer
    if(ocl->addBuffer(cdfBuffSize, CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Create INPUT CDF G buffer
    if(ocl->addBuffer(cdfBuffSize, CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Create INPUT CDF B buffer
    if(ocl->addBuffer(cdfBuffSize, CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Create OUTPUT RGB buffer
    if(ocl->addBuffer(inSize, CL_MEM_READ_WRITE) < 0) {
        return false;
    }

    // Write INPUT buffer
    if(!ocl->writeBuffer(0, in.bits(), inSize)) {
        return false;
    }

    // Fill CDF buffer
    size_t histBuffer[3][numberOfLevels];

    for(size_t i = 0; i < numberOfLevels; i ++) {
        histBuffer[0][i] = cdf.r[i];
        histBuffer[1][i] = cdf.g[i];
        histBuffer[2][i] = cdf.b[i];
    }

    // Write INPUT CDF R buffer
    if(!ocl->writeBuffer(1, (uint8_t*)histBuffer[0], cdfBuffSize)) {
        return false;
    }

    // Write INPUT CDF G buffer
    if(!ocl->writeBuffer(2, (uint8_t*)histBuffer[1], cdfBuffSize)) {
        return false;
    }

    // Write INPUT CDF B buffer
    if(!ocl->writeBuffer(3, (uint8_t*)histBuffer[2], cdfBuffSize)) {
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
    if(!ocl->readBuffer(4, &outImg, &outSize)) {
        return false;
    }

    // Convert back buffer to image
    out = QImage((const uchar *)outImg, imgW, imgH, QImage::Format_RGB888).copy();
    delete[] outImg;

    ocl->releaseAll();

    return true;
}

Processing::Algorithms::Histogram Processing::Algorithms::computeCDF(const Algorithms::Histogram &hist) {
    Algorithms::Histogram cdf = hist;

    for(size_t i = 1; i < 256; i ++) {
        cdf.r[i] = cdf.r[i] + cdf.r[i - 1];
        cdf.g[i] = cdf.g[i] + cdf.g[i - 1];
        cdf.b[i] = cdf.b[i] + cdf.b[i - 1];
    }

    return cdf;
}
