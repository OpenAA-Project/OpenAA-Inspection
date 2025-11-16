#-------------------------------------------------
#
# Project created by QtCreator 2022-10-02T18:46:21
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LEDControl16JioPrnRasPI
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
        LEDControl16JioPrnRasPIMain.cpp \
    ShowLEDControl16JForm.cpp \
    JioTestModeDialog.cpp \
    devicestruct.cpp \
    lightdevicestruct.cpp \
    XLightControlToPC.cpp \
    GeneralSource/XCritialFunc.cpp \
    GeneralSource/XDateTime.cpp \
    GeneralSource/XGeneralFunc.cpp \
    GeneralSource/XIntClass.cpp \
    AllocateIODialog.cpp \
    TimingChartForm.cpp \
    XJioDefineSignal.cpp

HEADERS += \
        LEDControl16JioPrnRasPIMain.h \
    ShowLEDControl16JForm.h \
    JioTestModeDialog.h \
    LightDeviceStruct.h \
    XCommToTrigger.h \
    XLightControlToPC.h \
    DeviceStruct.h \
    AllocateIODialog.h \
    Open/XGeneralFunc.h \
    Open/NListComp.h \
    Open/NListRPi.h \
    Open/swap.h \
    Open/XCriticalFunc.h \
    Open/XDateTime.h \
    Open/XIntClass.h \
    Open/XTypeDef.h \
    Open/XYCross.h \
    TimingChartForm.h \
    XJioDefineSignal.h

FORMS += \
        LEDControl16JioPrnRasPIMain.ui \
    ShowLEDControl16JForm.ui \
    JioTestModeDialog.ui \
    AllocateIODialog.ui \
    TimingChartForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/arm-linux-gnueabihf/release/ -lQt5Network
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/arm-linux-gnueabihf/debug/ -lQt5Network
else:unix: LIBS += -L$$PWD/../../../usr/lib/arm-linux-gnueabihf/ -lQt5Network

INCLUDEPATH += $$PWD/../../../usr/include/arm-linux-gnueabihf/qt5/QtNetwork
DEPENDPATH += $$PWD/../../../usr/include/arm-linux-gnueabihf/qt5/QtNetwork

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/arm-linux-gnueabihf/release/ -lQt5SerialPort
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/arm-linux-gnueabihf/debug/ -lQt5SerialPort
else:unix: LIBS += -L$$PWD/../../../usr/lib/arm-linux-gnueabihf/ -lQt5SerialPort

INCLUDEPATH += $$PWD/../../../usr/include/arm-linux-gnueabihf/qt5
DEPENDPATH += $$PWD/../../../usr/include/arm-linux-gnueabihf/qt5

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lwiringPi

INCLUDEPATH += $$PWD/./Open
DEPENDPATH += $$PWD/./Open
