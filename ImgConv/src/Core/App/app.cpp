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

using namespace Core;

App::App(QObject *parent)
    : Logger{parent} {

}

App::~App() {
    if(m_ocl) {
        delete m_ocl;
    }
}

bool App::init() {
    m_devices = OCLWrapper::getDevices();

    if(m_devices.count() == 0) {
        emit showCriticalError(tr("No OpenCL compatible device found !"));

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
        emit showCriticalError(tr("OCL backend error (%1)").arg(m_ocl->ret()));

        return;
    }
}

bool App::createOCLProgram(const QString &fn, const QString &options) {
    QFileDevice::FileError e = m_ocl->createProgramFromFile(fn, "pixelKernel", options);

    if(e != QFileDevice::NoError) {
        m_ocl->releaseKernel();
        m_ocl->releaseProgram();

        emit showCriticalError(tr("File error (%1)").arg(e));

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
            emit showCriticalError(tr("OCL backend error (%1)").arg(m_ocl->ret()));

            m_ocl->releaseKernel();
            m_ocl->releaseProgram();
            break;
        }

        return false;
    }

    return true;
}

QUuid App::startConv2DProcess(Processing::ConvKernels::ConvKernel *k) {
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

    Threads::Conv2D *process = new Threads::Conv2D(m_ocl, m_originalImage, mat);
    QUuid pid = process->getUUID();

    std::unique_ptr<QMetaObject::Connection> pconn{new QMetaObject::Connection};
    QMetaObject::Connection &conn = *pconn;

    conn = connect(m_ocl, &OCLWrapper::progress, this, [this, pid](size_t percentage) {
        emit processProgress(pid, percentage);
    });

    connect(process, &Threads::Conv2D::finished, this, [this, pid, conn](const QImage &img, qint64 et, bool res) {
        if(!res) {
            disconnect(conn);
            emit processError();
            emit conv2DDone(pid, et);

            return;
        }

        disconnect(conn);
        setProcessedImage(img);
        emit conv2DDone(pid, et);
    }, Qt::QueuedConnection);

    logOutput(tr("%1 - Running kernel ...").arg(pid.toString(QUuid::WithBraces)));

    QThreadPool::globalInstance()->start(process);

    return pid;
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
    QUuid pid = process->getUUID();

    connect(process, &Threads::Histogram::finished, this, [this, pid](const Processing::Algorithms::Histogram &hist, qint64 et, bool res) {
        Q_UNUSED(et)

        if(!res) {
            emit processError();
            emit histogramComputingDone(pid, et, hist);
            return;
        }

        emit histogramComputingDone(pid, et, hist);
    }, Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(process);

    return pid;
}

QUuid App::startImageCorrection(const QString &kernelPath, const Processing::Algorithms::Histogram &hist) {
    if(m_ocl->isRunning()) {
        logInfo(tr("Kernel already running ! Please wait."));

        return QUuid();
    }

    if(m_originalImage.isNull()) {
        return QUuid();
    }

    if(!hist.isValid()) {
        logError(tr("Invalid histogram."));

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

    Threads::Correction *process = new Threads::Correction(m_ocl, m_originalImage, hist);
    QUuid pid = process->getUUID();

    std::unique_ptr<QMetaObject::Connection> pconn{new QMetaObject::Connection};
    QMetaObject::Connection &conn = *pconn;

    conn = connect(m_ocl, &OCLWrapper::progress, this, [this, pid](size_t percentage) {
        emit processProgress(pid, percentage);
    });

    connect(process, &Threads::Correction::finished, this, [this, pid, conn](const QImage &img, qint64 et, bool res) {
        if(!res) {
            disconnect(conn);
            emit processError();
            emit imageCorrectionDone(pid, et);
            return;
        }

        disconnect(conn);
        setProcessedImage(img);
        emit imageCorrectionDone(pid, et);
    }, Qt::QueuedConnection);

    logOutput(tr("%1 - Running kernel ...").arg(pid.toString(QUuid::WithBraces)));

    QThreadPool::globalInstance()->start(process);

    return pid;
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

void App::setProcessedImage(const QImage &newProcessedImage) {
    m_processedImage = newProcessedImage;

    emit processedImageChanged();
}

Processing::ConvKernels::ConvKernel *App::getConvKernelAt(qsizetype i) const {
    return m_convKernels.at(i);
}

void App::setOriginalImage(const QImage &image) {
    m_originalImage = image;

    emit originalImageChanged();
}

QList<Processing::ConvKernels::ConvKernel *> App::convKernels() const {
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
