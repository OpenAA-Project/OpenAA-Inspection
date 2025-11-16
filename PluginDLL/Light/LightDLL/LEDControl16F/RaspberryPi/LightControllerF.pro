#-------------------------------------------------
#
# Project created by QtCreator 2020-08-09T00:18:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LightControllerF
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += ENABLE_PRECOMPILED_HEADERS=OFF

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    ControlFIOForm.cpp \
    ControlLightFForm.cpp \
    XDateTime.cpp \
    devicestruct.cpp \
    XGeneralFunc.cpp \
    XIntClass.cpp

HEADERS += \
        MainWindow.h \
    ControlFIOForm.h \
    ControlLightFForm.h \
    LightDeviceStruct.h \
    DeviceStruct.h \
    NListRPi.h \
    XGeneralFunc.h \
    XIntClass.h \
    XDateTime.h \
    swap.h

FORMS += \
        MainWindow.ui \
    ControlFIOForm.ui \
    ControlLightFForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/arm-linux-gnueabihf/release/ -lQtNetwork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/arm-linux-gnueabihf/debug/ -lQtNetwork
else:unix: LIBS += -L$$PWD/../../../usr/lib/arm-linux-gnueabihf/ -lQtNetwork

INCLUDEPATH += $$PWD/../../../usr/include/arm-linux-gnueabihf/qt5/QtNetwork
DEPENDPATH += $$PWD/../../../usr/include/arm-linux-gnueabihf/qt5/QtNetwork

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include
