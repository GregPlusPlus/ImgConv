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

#ifndef IMGLOADER_H
#define IMGLOADER_H

#include <QRunnable>
#include <QImage>
#include <QImageReader>
#include <QElapsedTimer>

namespace Threads {
class ImgLoader : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ImgLoader(const QString &fn);

    void run() override;

signals:
    void loaded(const QImage &img, qint64 et);

private:
    QString m_fn;
    QImage *m_img;
};
}

#endif // IMGLOADER_H
