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

#include "convkernel.h"

using namespace Core::Processing::ConvKernels;

ConvKernel::ConvKernel(QObject *parent)
    : QObject{parent} {
    ConvKernelSetting *sourcePath = new ConvKernelSetting(tr("Source file"), tr("Open source file"),
                                                          tr("OpenCL source (*.cl *.c);;All files (*.*)"),
                                                          QString(":/ocl/conv2D.cl"), this);
    addSetting(sourcePath);
}

QSize ConvKernel::getMatSize() const {
    QSize s(0, 0);

    s.setHeight(getMat().size());

    if(s.height()) {
        s.setWidth(getMat().at(0).size());
    }

    return s;
}

const QList<Core::Processing::ConvKernelSetting *> &ConvKernel::settings() const {
    return m_settings;
}

Core::Processing::ConvKernelSetting *ConvKernel::getSettingByName(const QString &name) const {
    for(ConvKernelSetting *s : settings()) {
        if(s->name() == name) {
            return s;
        }
    }

    return nullptr;
}

void ConvKernel::addSetting(ConvKernelSetting *s) {
    m_settings.append(s);
}

QString ConvKernel::getSourceFilePath() const {
    return getSettingByName(tr("Source file"))->valS();
}

void ConvKernel::setSourceFilePath(const QString &path) {
    getSettingByName(tr("Source file"))->setVal(path);
}

void ConvKernel::reset() {
    for(ConvKernelSetting *s : m_settings) {
        s->reset();
    }
}
