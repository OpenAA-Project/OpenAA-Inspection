#-------------------------------------------------
#
# Project created by QtCreator 2021-02-27T23:34:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LEDControl16GRP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        LEDControl16GRP.cpp \
    XIntClass.cpp \
    XGeneralFunc.cpp \
    XDateTime.cpp \
    XCommFromPC.cpp \
    LightDeviceStruct.cpp \
    devicestruct.cpp \
    XBoardAccess.cpp

HEADERS += \
        LEDControl16GRP.h \
    XYCross.h \
    XTypeDef.h \
    XIntClass.h \
    XGeneralFunc.h \
    XDateTime.h \
    XCommFromPC.h \
    swap.h \
    NListRPi.h \
    NListComp.h \
    NList.h \
    LightDeviceStruct.h \
    DeviceStruct.h

FORMS += \
        LEDControl16GRP.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/arm-linux-gnueabihf/release/ -lQt5Network
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/arm-linux-gnueabihf/debug/ -lQt5Network
else:unix: LIBS += -L$$PWD/../../../../usr/lib/arm-linux-gnueabihf/ -lQt5Network

INCLUDEPATH += $$PWD/../../../../usr/include/arm-linux-gnueabihf/qt5/QtNetwork
DEPENDPATH += $$PWD/../../../../usr/include/arm-linux-gnueabihf/qt5/QtNetwork

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../Open
DEPENDPATH += $$PWD/../../Open
