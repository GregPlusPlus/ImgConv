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

#ifndef APP_H
#define APP_H

#include "Core/OCLWrapper/oclwrapper.h"
#include "Core/OCLWrapper/oclutils.h"
#include "Core/Processing/processing.h"
#include "Core/Threads/threads.h"
#include "Core/Utils/utils.h"
#include "Core/Logger/logger.h"
#include "Core/Settings/SettingsMgr/settingsmgr.h"

#include <QThreadPool>
#include <QElapsedTimer>

namespace Core {
class App : public Logger
{
    Q_OBJECT

public:
    explicit App(Settings::SettingsMgr *settingsMgr, QObject *parent = nullptr);
    virtual ~App();

    QImage originalImage() const;
    QImage processedImage() const;

    OCLWrapper *ocl() const;

    QList<OCLWrapper::Device> devices() const;
    OCLWrapper::Device getDeviceByName(const QString &name);

    QList<Processing::ConvKernels::ConvKernel *> convKernels() const;

    void setOriginalImage(const QImage &img);
    void setProcessedImage(const QImage &img);

    Processing::ConvKernels::ConvKernel *getConvKernelAt(qsizetype i) const;

    Settings::SettingsMgr *settingsMgr() const;

    Processing::Options getProcessingOptions() const;
    void setProcessingOptions(const Processing::Options &processingOptions);

    Core::Processing::Algorithms::Histogram lastHistogramComputed() const;
    void setLastHistogramComputed(const Core::Processing::Algorithms::Histogram &newLastHistogramComputed);

    Core::Processing::Algorithms::Histogram originalImageHistogram() const;
    void setOriginalImageHistogram(const Core::Processing::Algorithms::Histogram &newOriginalImageHistogram);

public slots:
    bool init();
    void initOpenCL(const OCLWrapper::Device &device);
    bool createOCLProgram(const QString &fn, const QString &options);
    void loadConvKernels();

    QUuid startConv2DProcess(Processing::ConvKernels::ConvKernel *k);
    QUuid startComputeHistogram(const QImage &img);
    QUuid startImageCorrection(const QString &kernelPath, const Processing::Algorithms::Histogram &hist);

    void logConvMatrix(const QVector<QVector<float> > &mat);

signals:
    void conv2DDone(const QUuid &pid, qint64 elapsedTime);
    void histogramComputingDone(const QUuid &pid, qint64 elapsedTime);
    void imageCorrectionDone(const QUuid &pid, qint64 elapsedTime);
    void originalImageChanged();
    void processedImageChanged();

    void createOCLProgramError();
    void processError();

    void processProgress(const QUuid &pid, size_t percentage);

private:
    OCLWrapper *m_ocl = nullptr;
    Settings::SettingsMgr *m_settingsMgr;
    QList<OCLWrapper::Device> m_devices;
    QImage m_originalImage;
    QImage m_processedImage;
    QList<Processing::ConvKernels::ConvKernel*> m_convKernels;
    Processing::Options m_processingOptions;
    Core::Processing::Algorithms::Histogram m_lastHistogramComputed;
    Core::Processing::Algorithms::Histogram m_originalImageHistogram;

};
}

#endif // APP_H
