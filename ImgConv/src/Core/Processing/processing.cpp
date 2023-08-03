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

namespace Core::Processing {
void registerConvKernels(QList<ConvKernels::ConvKernel *> *l, QObject *parent) {
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

QString createOCLProgramOptionsConv2D(const QSize &imgSize, const QSize &matSize, const Options &options) {
    QString pixelBoundFixedColorDefineStr;

    if(options.boundaryMode == Options::Fixed_Color) {
        pixelBoundFixedColorDefineStr = "-DPIXEL_BOUNDARY_COLOR=\"((color_t){.r=255,.g=255,.b=255})\"";
    }

    return QString("-DW=%1 -DH=%2 -DKW=%3 -DKH=%4 -DVRSEED=\"{%5, %6, %7, %8}\" -D%9 %10 -I%11")
                    .arg(imgSize.width())
                    .arg(imgSize.height())
                    .arg(matSize.width())
                    .arg(matSize.height())
                    .arg(QRandomGenerator::global()->generate())
                    .arg(QRandomGenerator::global()->generate())
                    .arg(QRandomGenerator::global()->generate())
                    .arg(QRandomGenerator::global()->generate())
                    .arg(options.boundaryModeAsString())
                    .arg(pixelBoundFixedColorDefineStr)
                    .arg(QCoreApplication::applicationDirPath() + "/kCLinclude");
}

QString createOCLProgramOptionsComputeHistogram(const QSize &imgSize) {
    return QString("-DW=%1 -DH=%2 -I%3")
                    .arg(imgSize.width())
                    .arg(imgSize.height())
                    .arg(QCoreApplication::applicationDirPath() + "/kCLinclude");
}

QString createOCLProgramOptionsCorrection(const QSize &imgSize) {
    return QString("-DW=%1 -DH=%2 -I%3")
                    .arg(imgSize.width())
                    .arg(imgSize.height())
                    .arg(QCoreApplication::applicationDirPath() + "/kCLinclude");
}
}
