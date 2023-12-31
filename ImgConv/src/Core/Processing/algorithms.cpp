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

namespace Core::Processing::Algorithms {
bool conv2D(OCLWrapper *ocl, const QImage &in, QImage &out, const QVector<QVector<float>> &k) {
    const QSize imgSize = in.size();
    const size_t buffRGB888Size = in.width() * in.height() * 3;

    const uint8_t *inImgBuff = Utils::imageToArray(in);

    ocl->releaseAll();

    // Convolution kernel buffer
    ConvKernel1DArray kernel1DArray(k);

    // Output buffer
    uint8_t *outImgBuff = nullptr;
    size_t outSize = 0;

    // Create INPUT RGB buffer
    if(ocl->addBuffer(buffRGB888Size, CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Create OUTPUT RGB buffer
    if(ocl->addBuffer(buffRGB888Size, CL_MEM_READ_WRITE) < 0) {
        return false;
    }

    // Create convolution kernel buffer
    if(ocl->addBuffer(kernel1DArray.buffSize(), CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Write INPUT buffer
    if(!ocl->writeBuffer(BufferOrderIndex::Input, inImgBuff, buffRGB888Size)) {
        return false;
    }

    // Write convolution kernel buffer
    if(!ocl->writeBuffer(BufferOrderIndex::Kernel, (uint8_t*)kernel1DArray.getKArray(), kernel1DArray.buffSize())) {
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
    if(!ocl->readBuffer(BufferOrderIndex::Output, &outImgBuff, &outSize)) {
        return false;
    }

    // Convert back buffer to image
    out = Utils::arrayToImage(outImgBuff, imgSize);

    delete[] outImgBuff;
    delete[] inImgBuff;

    ocl->releaseAll();

    return true;
}

bool computeHistogram(OCLWrapper *ocl, const QImage &in, Histogram &hist) {
    const size_t buffRGB888Size = in.width() * in.height() * 3;
    const size_t numberOfLevels = 256;
    const size_t histBuffSize = numberOfLevels * sizeof(size_t);

    const uint8_t *inImgBuff = Utils::imageToArray(in);

    ocl->releaseAll();

    // Create INPUT RGB buffer
    if(ocl->addBuffer(buffRGB888Size, CL_MEM_READ_ONLY) < 0) {
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

    if(!ocl->writeBuffer(BufferOrderIndex::OutputHistR, (uint8_t*)zeroes, histBuffSize)) {
        return false;
    }

    if(!ocl->writeBuffer(BufferOrderIndex::OutputHistG, (uint8_t*)zeroes, histBuffSize)) {
        return false;
    }

    if(!ocl->writeBuffer(BufferOrderIndex::OutputHistB, (uint8_t*)zeroes, histBuffSize)) {
        return false;
    }

    // Write INPUT buffer
    if(!ocl->writeBuffer(BufferOrderIndex::Input, inImgBuff, buffRGB888Size)) {
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
    if(!ocl->readBuffer(BufferOrderIndex::OutputHistR, (uint8_t**)&(histBuffer[0]), &histSize)) {
        return false;
    }

    // Read OUTPUT G histogram buffer
    if(!ocl->readBuffer(BufferOrderIndex::OutputHistG, (uint8_t**)&(histBuffer[1]), &histSize)) {
        return false;
    }

    // Read OUTPUT B histogram buffer
    if(!ocl->readBuffer(BufferOrderIndex::OutputHistB, (uint8_t**)&(histBuffer[2]), &histSize)) {
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
    delete[] inImgBuff;

    ocl->releaseAll();

    return true;
}

bool applyCorrection(OCLWrapper *ocl, const QImage &in, QImage &out, const Histogram &cdf) {
    const QSize imgSize = in.size();
    const size_t buffRGB888Size = in.width() * in.height() * 3;

    const size_t numberOfLevels = 256;
    const size_t cdfBuffSize = numberOfLevels * sizeof(size_t);

    uint8_t *inImgBuff = Utils::imageToArray(in);

    ocl->releaseAll();

    // Output buffer
    uint8_t *outImgBuff = nullptr;
    size_t outSize = 0;

    // Create INPUT RGB buffer
    if(ocl->addBuffer(buffRGB888Size, CL_MEM_READ_ONLY) < 0) {
        return false;
    }

    // Create OUTPUT RGB buffer
    if(ocl->addBuffer(buffRGB888Size, CL_MEM_READ_WRITE) < 0) {
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

    // Write INPUT buffer
    if(!ocl->writeBuffer(BufferOrderIndex::Input, inImgBuff, buffRGB888Size)) {
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
    if(!ocl->writeBuffer(BufferOrderIndex::InputCdfR, (uint8_t*)histBuffer[0], cdfBuffSize)) {
        return false;
    }

    // Write INPUT CDF G buffer
    if(!ocl->writeBuffer(BufferOrderIndex::InputCdfG, (uint8_t*)histBuffer[1], cdfBuffSize)) {
        return false;
    }

    // Write INPUT CDF B buffer
    if(!ocl->writeBuffer(BufferOrderIndex::InputCdfB, (uint8_t*)histBuffer[2], cdfBuffSize)) {
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
    if(!ocl->readBuffer(BufferOrderIndex::Output, &outImgBuff, &outSize)) {
        return false;
    }

    // Convert back buffer to image
    out = Utils::arrayToImage(outImgBuff, imgSize);

    delete[] outImgBuff;
    delete[] inImgBuff;

    ocl->releaseAll();

    return true;
}
}
