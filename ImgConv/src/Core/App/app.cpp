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

#include "app.h"

namespace Core{

App::App(QObject *parent)
    : Logger{parent} {

}

bool App::init() {
    m_devices = OCLWrapper::getDevices();

    if(m_devices.count() == 0) {
        showCriticalError(tr("No OpenCL compatible device found !"));

        return false;
    }

    initOpenCL(m_devices[0]);
    Processing::registerConvKernels(&m_convKernels, this);

    return true;
}

void App::initOpenCL(const OCLWrapper::Device &device) {
    if(m_ocl) {
        delete m_ocl;
    }

    m_ocl = new OCLWrapper(device, this);

    if(m_ocl->ret() != CL_SUCCESS) {
        showCriticalError(tr("OCL backend error (%1)").arg(m_ocl->ret()));

        return;
    }
}

bool App::createOCLProgram(const QString &fn, const QString &options) {
    QFileDevice::FileError e = m_ocl->createProgramFromFile(fn, "pixelKernel", options);

    if(e != QFileDevice::NoError) {
        m_ocl->releaseKernel();
        m_ocl->releaseProgram();

        showCriticalError(tr("File error (%1)").arg(e));

        return false;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        switch(m_ocl->ret()) {
        case CL_BUILD_PROGRAM_FAILURE :
            logError(tr("OCL build program error (%1)\n______________________________\n%2")
                          .arg(m_ocl->ret())
                          .arg(m_ocl->getBuildLog()));

            m_ocl->releaseKernel();
            m_ocl->releaseProgram();
            break;
        default:
            showCriticalError(tr("OCL backend error (%1)").arg(m_ocl->ret()));

            m_ocl->releaseKernel();
            m_ocl->releaseProgram();
            break;
        }

        return false;
    }

    return true;
}

QUuid App::startConv2DProcess(ConvKernels::ConvKernel *k) {
    if(m_ocl->isRunning()) {
        logInfo(tr("Kernel already running ! Please wait."));

        return QUuid();
    }

    if(m_originalImage.isNull()) {
        return QUuid();
    }

    QVector<QVector<float>> mat = k->getMat();
    QSize matSize = k->getMatSize();

    if(!matSize.width() || !matSize.height()) {
        return QUuid();
    }

    QString options = Processing::createOCLProgramOptionsConv2D(m_originalImage.size(), matSize);

    logOutput(tr("\n[%1] Creating program - opts. : `%2`")
                    .arg(k->getSourceFilePath())
                    .arg(options));

    if(!createOCLProgram(k->getSourceFilePath(), options)) {
        return QUuid();
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        return QUuid();
    }

    Utils::scaleMatrix(mat, k->getScalar());

    logConvMatrix(mat);

    logOutput(tr("Running kernel..."));

    m_pclass = Conv2D;

    Threads::Conv2D *process = new Threads::Conv2D(m_ocl, m_originalImage, mat);

    connect(process, &Threads::Conv2D::finished, this, [this, process](const QImage &img, qint64 et, bool res) {
        if(!res) {
            emit processError();
            emit processFinished(m_pclass, process->getUUID(), et);

            delete process;

            return;
        }

        setProcessedImage(img);
        emit processFinished(m_pclass, process->getUUID(), et);

        delete process;
    });

    QThreadPool::globalInstance()->start(process);

    return process->getUUID();
}

QUuid App::startComputeHistogram(const QImage &img) {
    const QString programPath = ":/ocl/histogram.cl";

    if(m_ocl->isRunning()) {
        logInfo(tr("Kernel already running ! Please wait."));

        return QUuid();
    }

    if(img.isNull()) {
        return QUuid();
    }

    QString options = Processing::createOCLProgramOptionsComputeHistogram(img.size());

    if(!createOCLProgram(programPath, options)) {
        return QUuid();
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        return QUuid();
    }

    Threads::Histogram *process = new Threads::Histogram(m_ocl, img);

    connect(process, &Threads::Histogram::finished, this, [this, process](const Processing::Algorithms::Histogram &hist, qint64 et, bool res) {
        Q_UNUSED(et)

        if(!res) {
            emit processError();
            emit processFinished(m_pclass, process->getUUID(), et);

            delete process;

            return;
        }

        histogramComputingDone(hist);
        emit processFinished(m_pclass, process->getUUID(), et);

        delete process;
    });

    QThreadPool::globalInstance()->start(process);

    return process->getUUID();
}

QUuid App::startImageCorrection(const QString &kernelPath) {
    if(m_ocl->isRunning()) {
        logInfo(tr("Kernel already running ! Please wait."));

        return QUuid();
    }

    if(m_originalImage.isNull()) {
        return QUuid();
    }

    QString options = Processing::createOCLProgramOptionsCorrection(m_originalImage.size());

    logOutput(tr("\n[%1] Creating program - opts. : `%2`")
                    .arg(kernelPath)
                    .arg(options));

    if(!createOCLProgram(kernelPath, options)) {
        return QUuid();
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        return QUuid();
    }

    logOutput(tr("Running kernel..."));

    Threads::Correction *process = new Threads::Correction(m_ocl, m_originalImage,
                                                           mw_imgCorrectionPanel->originalImageHistogram().getCDF());

    connect(process, &Threads::Correction::finished, this, [this, process](const QImage &img, qint64 et, bool res) {
        if(!res) {
            emit processError();
            emit processFinished(m_pclass, process->getUUID(), et);

            delete process;

            return;
        }

        setProcessedImage(img);
        emit processFinished(m_pclass, process->getUUID(), et);

        delete process;
    });

    QThreadPool::globalInstance()->start(process);

    return process->getUUID();
}

void App::logConvMatrix(const QVector<QVector<float> > &mat) {
    QString str;

    str += tr("\n%1x%2 Convolution matrix :\n").arg(mat[0].size()).arg(mat.size());

    if((mat.size() > 16) || (mat[0].size() > 16)) {
        str += tr("Matrix is too large to be printed.");
    } else {
        str += Utils::matrixToBoxString(mat);
    }

    str += "\n";

    logOutput(str);
}

App::ProcessClass App::processClass() const {
    return m_pclass;
}

void App::setProcessedImage(const QImage &newProcessedImage) {
    m_processedImage = newProcessedImage;
}

ConvKernels::ConvKernel *App::getConvKernelAt(qsizetype i) const {
    return m_convKernels.at(i);
}

void App::setOriginalImage(const QImage &image) {
    m_originalImage = image;

    emit originalImageChanged();
}

QList<ConvKernels::ConvKernel *> App::convKernels() const {
    return m_convKernels;
}

QList<OCLWrapper::Device> App::devices() const {
    return m_devices;
}

OCLWrapper *App::ocl() const {
    return m_ocl;
}

QImage App::processedImage() const {
    return m_processedImage;
}

QImage App::originalImage() const {
    return m_originalImage;
}
}
