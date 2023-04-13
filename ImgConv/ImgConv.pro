QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += GIT_VERSION='"\\\"$(shell git describe --always)\\\""'

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Core/OCLWrapper/oclwrapper.cpp \
    src/Core/Processing/Kernels/custom.cpp \
    src/Core/Processing/Kernels/emboss.cpp \
    src/Core/Processing/Kernels/gaussianblur.cpp \
    src/Core/Processing/Kernels/motionblur.cpp \
    src/Core/Processing/Kernels/ridge.cpp \
    src/Core/Processing/Kernels/sharpen.cpp \
    src/Core/Processing/Kernels/unsharpmasking.cpp \
    src/Core/Processing/convkernel.cpp \
    src/Core/Processing/convkernel1darray.cpp \
    src/Core/Processing/processing.cpp \
    src/Core/Threads/imgloader.cpp \
    src/Core/Threads/process.cpp \
    src/Core/Utils/utils.cpp \
    src/UI/CodeEditor/Components/codeeditor.cpp \
    src/UI/CodeEditor/Components/interactivetextedit.cpp \
    src/UI/CodeEditor/Components/keycompletion.cpp \
    src/UI/CodeEditor/codeeditorcontainer.cpp \
    src/UI/FilterSettingsWidget/filenamepicker.cpp \
    src/UI/FilterSettingsWidget/filtersettingsdock.cpp \
    src/UI/FilterSettingsWidget/filtersettingswidget.cpp \
    src/UI/ImageViewer/imageviewer.cpp \
    src/UI/MainWindow/mainwindow.cpp \
    src/UI/SelectDeviceDialog/selectdevicedialog.cpp \
    src/UI/WaitDialog/waitdialog.cpp \
    src/main.cpp
HEADERS += \
    src/Core/OCLWrapper/oclwrapper.h \
    src/Core/Processing/Kernels/custom.h \
    src/Core/Processing/Kernels/emboss.h \
    src/Core/Processing/Kernels/gaussianblur.h \
    src/Core/Processing/Kernels/kernels.h \
    src/Core/Processing/Kernels/motionblur.h \
    src/Core/Processing/Kernels/ridge.h \
    src/Core/Processing/Kernels/sharpen.h \
    src/Core/Processing/Kernels/unsharpmasking.h \
    src/Core/Processing/convkernel.h \
    src/Core/Processing/convkernel1darray.h \
    src/Core/Processing/processing.h \
    src/Core/Threads/imgloader.h \
    src/Core/Threads/process.h \
    src/Core/Threads/threads.h \
    src/Core/Utils/utils.h \
    src/UI/CodeEditor/Components/codeeditor.h \
    src/UI/CodeEditor/Components/interactivetextedit.h \
    src/UI/CodeEditor/Components/keycompletion.h \
    src/UI/CodeEditor/codeeditorcontainer.h \
    src/UI/FilterSettingsWidget/filenamepicker.h \
    src/UI/FilterSettingsWidget/filtersettingsdock.h \
    src/UI/FilterSettingsWidget/filtersettingswidget.h \
    src/UI/ImageViewer/imageviewer.h \
    src/UI/MainWindow/app_strings.h \
    src/UI/MainWindow/mainwindow.h \
    src/UI/SelectDeviceDialog/selectdevicedialog.h \
    src/UI/WaitDialog/waitdialog.h

INCLUDEPATH += \
    libs/include/ \
    src/

LIBS += \
    -Llibs/lib/ \
    -lOpenCL

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc/rc.qrc
