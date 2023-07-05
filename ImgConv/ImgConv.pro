QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += GIT_VERSION='"\\\"$(shell git describe --always)\\\""'

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Core/Logger/logger.cpp \
    src/Core/OCLWrapper/oclutils.cpp \
    src/Core/OCLWrapper/oclwrapper.cpp \
    src/Core/Processing/Kernels/custom.cpp \
    src/Core/Processing/Kernels/emboss.cpp \
    src/Core/Processing/Kernels/gaussianblur.cpp \
    src/Core/Processing/Kernels/motionblur.cpp \
    src/Core/Processing/Kernels/ridge.cpp \
    src/Core/Processing/Kernels/sharpen.cpp \
    src/Core/Processing/Kernels/sobel.cpp \
    src/Core/Processing/Kernels/unity.cpp \
    src/Core/Processing/Kernels/unsharpmasking.cpp \
    src/Core/Processing/algorithms.cpp \
    src/Core/Processing/convkernel.cpp \
    src/Core/Processing/convkernel1darray.cpp \
    src/Core/Processing/processing.cpp \
    src/Core/Threads/correction.cpp \
    src/Core/Threads/histogram.cpp \
    src/Core/Threads/imgexport.cpp \
    src/Core/Threads/imgloader.cpp \
    src/Core/Threads/processconv2D.cpp \
    src/Core/Threads/virtualthread.cpp \
    src/Core/Utils/utils.cpp \
    src/Core/App/app.cpp \
    src/UI/CodeEditor/Components/codeeditor.cpp \
    src/UI/CodeEditor/Components/highlighter.cpp \
    src/UI/CodeEditor/Components/interactivetextedit.cpp \
    src/UI/CodeEditor/Components/keycompletion.cpp \
    src/UI/CodeEditor/codeeditorcontainer.cpp \
    src/UI/Components/ButtonColorPicker/buttoncolorpicker.cpp \
    src/UI/Components/HistogramWidget/histogramwidget.cpp \
    src/UI/Dialogs/CreateImageDialog/createimagedialog.cpp \
    src/UI/Dialogs/ProcessOptionsDialog/processoptionsdialog.cpp \
    src/UI/FilterSettingsWidget/filenamepicker.cpp \
    src/UI/Panels/FilterSettingsPanel/filtersettingsdock.cpp \
    src/UI/FilterSettingsWidget/filtersettingswidget.cpp \
    src/UI/ImageViewer/imageviewer.cpp \
    src/UI/ImageViewer/imageviewercontainer.cpp \
    src/UI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp \
    src/UI/Panels/LogPanel/logpanel.cpp \
    src/UI/Panels/LogPanel/logwidget.cpp \
    src/UI/MainWindow/mainwindow.cpp \
    src/UI/Dialogs/SelectDeviceDialog/selectdevicedialog.cpp \
    src/UI/UtilsUI/utilsui.cpp \
    src/UI/Dialogs/WaitDialog/waitdialog.cpp \
    src/UI/WaitDialogMgr/waitdialogmgr.cpp \
    src/main.cpp
HEADERS += \
    src/Core/Logger/logger.h \
    src/Core/OCLWrapper/oclutils.h \
    src/Core/OCLWrapper/oclwrapper.h \
    src/Core/Processing/Kernels/custom.h \
    src/Core/Processing/Kernels/emboss.h \
    src/Core/Processing/Kernels/gaussianblur.h \
    src/Core/Processing/Kernels/kernels.h \
    src/Core/Processing/Kernels/motionblur.h \
    src/Core/Processing/Kernels/ridge.h \
    src/Core/Processing/Kernels/sharpen.h \
    src/Core/Processing/Kernels/sobel.h \
    src/Core/Processing/Kernels/unity.h \
    src/Core/Processing/Kernels/unsharpmasking.h \
    src/Core/Processing/algorithms.h \
    src/Core/Processing/convkernel.h \
    src/Core/Processing/convkernel1darray.h \
    src/Core/Processing/processing.h \
    src/Core/Threads/correction.h \
    src/Core/Threads/histogram.h \
    src/Core/Threads/imgexport.h \
    src/Core/Threads/imgloader.h \
    src/Core/Threads/processconv2D.h \
    src/Core/Threads/threads.h \
    src/Core/Threads/virtualthread.h \
    src/Core/Utils/utils.h \
    src/Core/App/app.h \
    src/UI/CodeEditor/Components/codeeditor.h \
    src/UI/CodeEditor/Components/highlighter.h \
    src/UI/CodeEditor/Components/interactivetextedit.h \
    src/UI/CodeEditor/Components/keycompletion.h \
    src/UI/CodeEditor/codeeditorcontainer.h \
    src/UI/Components/ButtonColorPicker/buttoncolorpicker.h \
    src/UI/Components/HistogramWidget/histogramwidget.h \
    src/UI/Dialogs/CreateImageDialog/createimagedialog.h \
    src/UI/Dialogs/ProcessOptionsDialog/processoptionsdialog.h \
    src/UI/FilterSettingsWidget/filenamepicker.h \
    src/UI/Panels/FilterSettingsPanel/filtersettingsdock.h \
    src/UI/FilterSettingsWidget/filtersettingswidget.h \
    src/UI/ImageViewer/imageviewer.h \
    src/UI/ImageViewer/imageviewercontainer.h \
    src/UI/Panels/ImageCorrectionPanel/imagecorrectionpanel.h \
    src/UI/Panels/LogPanel/logpanel.h \
    src/UI/Panels/LogPanel/logwidget.h \
    src/UI/MainWindow/app_strings.h \
    src/UI/MainWindow/mainwindow.h \
    src/UI/Dialogs/SelectDeviceDialog/selectdevicedialog.h \
    src/UI/UtilsUI/utilsui.h \
    src/UI/Dialogs/WaitDialog/waitdialog.h \
    src/UI/WaitDialogMgr/waitdialogmgr.h

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
