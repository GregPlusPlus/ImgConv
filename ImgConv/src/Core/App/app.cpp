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
    : QObject{parent} {

}

bool App::init() {
    m_devices = OCLWrapper::getDevices();

    if(m_devices.count() == 0) {
        QMessageBox::critical(nullptr, tr("OCL init error"), tr("No OpenCL compatible device found !"));

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
        QMessageBox::critical(this, tr("OCL init error"), tr("OCL backend error (%1)").arg(m_ocl->ret()));

        return;
    }
}

bool App::createOCLProgram(const QString &fn, const QString &options) {
    QFileDevice::FileError e = m_ocl->createProgramFromFile(fn, "pixelKernel", options);

    if(e != QFileDevice::NoError) {
        m_ocl->releaseKernel();
        m_ocl->releaseProgram();

        QMessageBox::critical(this, tr("Filesystem error"), tr("File error (%1)").arg(e));

        return false;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        switch(m_ocl->ret()) {
        case CL_BUILD_PROGRAM_FAILURE :
            mw_logPanel->logError(tr("OCL build program error (%1)\n______________________________\n%2")
                                  .arg(m_coreApp->ocl()->ret())
                                  .arg(m_coreApp->ocl()->getBuildLog()));

            m_ocl->releaseKernel();
            m_ocl->releaseProgram();
            break;
        default:
            QMessageBox::critical(this, tr("OCL error"), tr("OCL backend error (%1)").arg(m_ocl->ret()));

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
        mw_logPanel->logInfo(tr("Kernel already running ! Please wait."));

        return;
    }

    if(m_originalImage.isNull()) {
        return;
    }

    QVector<QVector<float>> mat = k->getMat();
    QSize matSize = k->getMatSize();

    if(!matSize.width() || !matSize.height()) {
        return;
    }

    QString options = Processing::createOCLProgramOptionsConv2D(m_originalImage.size(), matSize);

    mw_logPanel->logOutput(tr("\n[%1] Creating program - opts. : `%2`")
                        .arg(k->getSourceFilePath())
                        .arg(options));

    if(!createOCLProgram(k->getSourceFilePath(), options)) {
        return;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        return;
    }

    Utils::scaleMatrix(mat, k->getScalar());

    logConvMatrix(mat);

    mw_logPanel->logOutput(tr("Running kernel..."));

    WaitDialog *dialog = new WaitDialog(tr("Processing image..."));

    m_pclass = Conv2D;

    Threads::Conv2D *process = new Threads::Conv2D(m_ocl, m_originalImage, mat);

    connect(process, &Threads::Conv2D::finished, this, [this, process](const QImage &img, qint64 et, bool res) {
        if(!res) {
            delete dialog;

            emit processError();
            emit processFinished(m_pclass, process->getUUID(), et);

            return;
        }

        setProcessedImage(img);
        emit processFinished(m_pclass, process->getUUID(), et);
    });

    QThreadPool::globalInstance()->start(process);

    return process->getUUID();
}

QUuid App::startComputeHistogram(const QImage &img) {
    const QString programPath = ":/ocl/histogram.cl";

    if(m_ocl->isRunning()) {
        mw_logPanel->logInfo(tr("Kernel already running ! Please wait."));

        return;
    }

    if(img.isNull()) {
        return;
    }

    QString options = Processing::createOCLProgramOptionsComputeHistogram(img.size());

    if(!createOCLProgram(programPath, options)) {
        return;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        return;
    }

    WaitDialog *dialog = new WaitDialog(tr("Computing histogram..."));
    Threads::Histogram *process = new Threads::Histogram(m_ocl, img);

    connect(process, &Threads::Histogram::finished, this, [this, process](const Processing::Algorithms::Histogram &hist, qint64 et, bool res) {
        Q_UNUSED(et)

        if(!res) {
            emit processError();
            emit processFinished(m_pclass, process->getUUID(), et);

            return;

            return;
        }

        histogramComputingDone(hist);
        emit processFinished(m_pclass, process->getUUID(), et);
    });

    QThreadPool::globalInstance()->start(process);

    return process->getUUID();
}

QUuid App::startImageCorrection(const QString &kernelPath) {
    if(m_ocl->isRunning()) {
        mw_logPanel->logInfo(tr("Kernel already running ! Please wait."));

        return;
    }

    if(m_original.isNull()) {
        return;
    }

    QString options = Processing::createOCLProgramOptionsCorrection(m_original.size());

    mw_logPanel->logOutput(tr("\n[%1] Creating program - opts. : `%2`")
                        .arg(kernelPath)
                        .arg(options));

    if(!createOCLProgram(kernelPath, options)) {
        return;
    }

    if(m_ocl->ret() != CL_SUCCESS) {
        return;
    }

    mw_logPanel->logOutput(tr("Running kernel..."));

    WaitDialog *dialog = new WaitDialog(tr("Correcting image..."));
    Threads::Correction *process = new Threads::Correction(m_ocl, m_originalImage,
                                                           mw_imgCorrectionPanel->originalImageHistogram().getCDF());

    connect(process, &Threads::Correction::finished, this, [this, process](const QImage &img, qint64 et, bool res) {
        if(!res) {
            emit processError();
            emit processFinished(m_pclass, process->getUUID(), et);

            return;

            return;
        }

        setProcessedImage(img);
        emit processFinished(m_pclass, process->getUUID(), et);
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

    mw_logPanel->logOutput(str);
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
