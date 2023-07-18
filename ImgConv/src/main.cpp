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

#include "UI/GUI/MainWindow/mainwindow.h"
#include "Core/App/app.h"

#include <QApplication>

#include <QTranslator>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    if (translator.load(QLocale::system(), "ImgConv", "_", ":/translations")) {
        a.installTranslator(&translator);
    }

    Core::App coreApp;

    if(!coreApp.init()) {
        exit(EXIT_FAILURE);
    }

    UI::GUI::MainWindow window(&coreApp);
    window.show();

    return a.exec();
}
