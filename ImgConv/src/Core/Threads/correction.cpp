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

#include "correction.h"

Threads::Correction::Correction(OCLWrapper *ocl, const QImage &original, const Processing::Algorithms::Histogram &cdf)
    : VirtualThread{Threads::Classes::ImageCorrection}, m_cdf{cdf}, m_ocl{ocl}, m_original{original} {

}

void Threads::Correction::run() {
    QImage corrected;

    QElapsedTimer tm;
    tm.start();

    bool res = Processing::Algorithms::applyCorrection(m_ocl, m_original, corrected, m_cdf);

    emit finished(corrected, tm.elapsed(), res);
}
