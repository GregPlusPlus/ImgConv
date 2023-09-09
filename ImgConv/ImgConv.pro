QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += GIT_VERSION='"\\\"$(shell git describe --tags)\\\""'

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
    src/Core/Processing/convkernelsetting.cpp \
    src/Core/Processing/processing.cpp \
    src/Core/Settings/Setting/setting.cpp \
    src/Core/Settings/SettingsMgr/abstractsettingsmgr.cpp \
    src/Core/Settings/SettingsMgr/settingsmgr.cpp \
    src/Core/Threads/correction.cpp \
    src/Core/Threads/histogram.cpp \
    src/Core/Threads/imgexport.cpp \
    src/Core/Threads/imgloader.cpp \
    src/Core/Threads/processconv2D.cpp \
    src/Core/Threads/virtualthread.cpp \
    src/Core/Utils/utils.cpp \
    src/Core/App/app.cpp \
    src/UI/GUI/Components/CodeEditor/Components/codeeditor.cpp \
    src/UI/GUI/Components/CodeEditor/Components/highlighter.cpp \
    src/UI/GUI/Components/CodeEditor/Components/interactivetextedit.cpp \
    src/UI/GUI/Components/CodeEditor/Components/keycompletion.cpp \
    src/UI/GUI/Components/CodeEditor/codeeditorcontainer.cpp \
    src/UI/GUI/Components/ButtonColorPicker/buttoncolorpicker.cpp \
    src/UI/GUI/Components/FilenamePicker/filenamepicker.cpp \
    src/UI/GUI/Components/HistogramWidget/histogramwidget.cpp \
    src/UI/GUI/Components/ImageViewer/imagedisplay.cpp \
    src/UI/GUI/Components/ImageViewer/imageviewer.cpp \
    src/UI/GUI/Dialogs/CreateImageDialog/createimagedialog.cpp \
    src/UI/GUI/Dialogs/ProcessOptionsDialog/processoptionsdialog.cpp \
    src/UI/GUI/Panels/FilterSettingsPanel/filtersettingsdock.cpp \
    src/UI/GUI/FilterSettingsWidget/filtersettingswidget.cpp \
    src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.cpp \
    src/UI/GUI/Panels/LogPanel/logpanel.cpp \
    src/UI/GUI/Panels/LogPanel/logwidget.cpp \
    src/UI/GUI/MainWindow/mainwindow.cpp \
    src/UI/GUI/Dialogs/SelectDeviceDialog/selectdevicedialog.cpp \
    src/UI/GUI/Dialogs/WaitDialog/waitdialog.cpp \
    src/UI/GUI/UtilsGUI/utilsgui.cpp \
    src/UI/GUI/WaitDialogMgr/waitdialogmgr.cpp \
    src/UI/Translator/translator.cpp \
    src/UI/UndoRedo/Commands/backfeedimagecommand.cpp \
    src/UI/UndoRedo/Commands/openimagecommand.cpp \
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
    src/Core/Processing/convkernelsetting.h \
    src/Core/Processing/processing.h \
    src/Core/Settings/Setting/setting.h \
    src/Core/Settings/SettingsMgr/abstractsettingsmgr.h \
    src/Core/Settings/SettingsMgr/settingsmgr.h \
    src/Core/Threads/correction.h \
    src/Core/Threads/histogram.h \
    src/Core/Threads/imgexport.h \
    src/Core/Threads/imgloader.h \
    src/Core/Threads/processconv2D.h \
    src/Core/Threads/threads.h \
    src/Core/Threads/virtualthread.h \
    src/Core/Utils/utils.h \
    src/Core/App/app.h \
    src/UI/GUI/Components/CodeEditor/Components/codeeditor.h \
    src/UI/GUI/Components/CodeEditor/Components/highlighter.h \
    src/UI/GUI/Components/CodeEditor/Components/interactivetextedit.h \
    src/UI/GUI/Components/CodeEditor/Components/keycompletion.h \
    src/UI/GUI/Components/CodeEditor/codeeditorcontainer.h \
    src/UI/GUI/Components/ButtonColorPicker/buttoncolorpicker.h \
    src/UI/GUI/Components/FilenamePicker/filenamepicker.h \
    src/UI/GUI/Components/HistogramWidget/histogramwidget.h \
    src/UI/GUI/Components/ImageViewer/imagedisplay.h \
    src/UI/GUI/Components/ImageViewer/imageviewer.h \
    src/UI/GUI/Dialogs/CreateImageDialog/createimagedialog.h \
    src/UI/GUI/Dialogs/ProcessOptionsDialog/processoptionsdialog.h \
    src/UI/GUI/Panels/FilterSettingsPanel/filtersettingsdock.h \
    src/UI/GUI/FilterSettingsWidget/filtersettingswidget.h \
    src/UI/GUI/Panels/ImageCorrectionPanel/imagecorrectionpanel.h \
    src/UI/GUI/Panels/LogPanel/logpanel.h \
    src/UI/GUI/Panels/LogPanel/logwidget.h \
    src/UI/GUI/MainWindow/mainwindow.h \
    src/UI/GUI/Dialogs/SelectDeviceDialog/selectdevicedialog.h \
    src/UI/GUI/Dialogs/WaitDialog/waitdialog.h \
    src/UI/GUI/UtilsGUI/utilsgui.h \
    src/UI/GUI/UtilsGUI/app_strings.h \
    src/UI/GUI/WaitDialogMgr/waitdialogmgr.h \
    src/UI/Translator/translator.h \
    src/UI/UndoRedo/Commands/backfeedimagecommand.h \
    src/UI/UndoRedo/Commands/undoredocommands.h \
    src/UI/UndoRedo/Commands/openimagecommand.h

INCLUDEPATH += \
    libs/include/ \
    src/

win32 {
LIBS += \
    -Llibs/lib/ \
    -lOpenCL
}
unix:!macx {
LIBS += \
    -lOpenCL
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc/rc.qrc

TRANSLATIONS += \
    languages/ImgConv_fr.ts

 CODECFORSRC     = UTF-8
