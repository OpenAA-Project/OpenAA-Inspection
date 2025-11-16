#-------------------------------------------------
#
# Project created by QtCreator 2021-12-24T17:45:01
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LEDControl16GPrnRasPi
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
        LEDControl16GPrnRasPi.cpp \
    GioTestModeDialog.cpp \
    ShowLEDControl16GForm.cpp \
    XLightControlToPC.cpp \
    XBoardAccess.cpp \
    ./GeneralSource/XIntClass.cpp \
    ./GeneralSource/XGeneralFunc.cpp \
    ./GeneralSource/XDateTime.cpp \
    devicestruct.cpp \
    lightdevicestruct.cpp \
    ./GeneralSource/XCritialFunc.cpp \
    TimingChartForm.cpp \
    XGioDefineSignal.cpp

HEADERS += \
        LEDControl16GPrnRasPi.h \
    GioTestModeDialog.h \
    ShowLEDControl16GForm.h \
    XLightControlToPC.h \
    XYCross.h \
    XTypeDef.h \
    XIntClass.h \
    XGeneralFunc.h \
    XDateTime.h \
    swap.h \
    NListRPi.h \
    NListComp.h \
    DeviceStruct.h \
    LightDeviceStruct.h \
    XCommToTrigger.h \
    XCriticalFunc.h \
    TimingChartForm.h \
    XGioDefineSignal.h

FORMS += \
        LEDControl16GPrnRasPi.ui \
   ShowLEDControl16GForm.ui \
    GioTestModeDialog.ui \
    TimingChartForm.ui

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

INCLUDEPATH += $$PWD/./Open
DEPENDPATH += $$PWD/./Open

