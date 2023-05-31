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
#include "Core/Processing/processing.h"
#include "Core/Threads/threads.h"
#include "Core/Utils/utils.h"

#include <QThreadPool>
#include <QElapsedTimer>

namespace Core {
class App : public QObject
{
    Q_OBJECT

public:
    enum ProcessClass {
        None,
        Conv2D,
        ComputeHistogram,
        ImageCorrection
    };
public:
    explicit App(QObject *parent);

    QImage originalImage() const;
    QImage processedImage() const;

    OCLWrapper *ocl() const;

    QList<OCLWrapper::Device> devices() const;

    QList<ConvKernels::ConvKernel *> convKernels() const;

    void setOriginalImage(const QImage &img);
    void setProcessedImage(const QImage &img);

    ConvKernels::ConvKernel *getConvKernelAt(qsizetype i) const;

    ProcessClass processClass() const;

public slots:
    bool init();
    void initOpenCL(const OCLWrapper::Device &device);
    bool createOCLProgram(const QString &fn, const QString &options);

    QUuid startConv2DProcess(ConvKernels::ConvKernel *k);
    QUuid startComputeHistogram(const QImage &img);
    QUuid startImageCorrection(const QString &kernelPath);

    void logConvMatrix(const QVector<QVector<float> > &mat);

signals:
    void imageProcessingDone(const QImage &img);
    void histogramComputingDone(const Processing::Algorithms::Histogram &histogram);
    void processFinished(Core::App::ProcessClass pclass, QUuid pid, qint64 elapsedTime);
    void originalImageChanged();
    void processedImageChanged();

    void createOCLProgramError();
    void processError();

private:
    OCLWrapper *m_ocl = nullptr;
    QList<OCLWrapper::Device> m_devices;
    QImage m_originalImage;
    QImage m_processedImage;
    QList<ConvKernels::ConvKernel*> m_convKernels;
    ProcessClass m_pclass = None;

};
}

#endif // APP_H
