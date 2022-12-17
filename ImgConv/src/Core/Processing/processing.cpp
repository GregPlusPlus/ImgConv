#include "Core/Processing/processing.h"

bool Processing::processImg(OCLWrapper *ocl, const QImage &in, QImage &out, const QVector<QVector<float>> &k) {
    int imgW = in.width();
    int imgH = in.height();
    size_t inSize = in.sizeInBytes();
    int kW = k[0].size();
    int kH = k.size();

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
    //   Set image size
    ocl->setKernelArg(3, sizeof(cl_uint), (const uint8_t*)&imgW);
    ocl->setKernelArg(4, sizeof(cl_uint), (const uint8_t*)&imgH);
    //   Set convolution kernel size
    ocl->setKernelArg(5, sizeof(cl_uint), (const uint8_t*)&kW);
    ocl->setKernelArg(6, sizeof(cl_uint), (const uint8_t*)&kH);

    // Run kernel
    ocl->runKernel(imgW, imgH);
    if(ocl->ret() != CL_SUCCESS) {
        return false;
    }

    // Read OUTPUT buffer
    if(!ocl->readBuffer(1, &outImg, &outSize)) {
        return false;
    }

    // Convert back buffer to image
    out = QImage((const uchar *)outImg, imgW, imgH, QImage::Format_RGB888);

    ocl->releaseAll();

    return true;
}
