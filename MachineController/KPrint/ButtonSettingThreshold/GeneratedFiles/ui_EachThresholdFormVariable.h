/********************************************************************************
** Form generated from reading UI file 'EachThresholdFormVariable.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EACHTHRESHOLDFORMVARIABLE_H
#define UI_EACHTHRESHOLDFORMVARIABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EachThresholdFormVariable
{
public:
    QToolButton *toolButtonCancel;
    QFrame *frameMarkerImage;
    QToolButton *toolButtonOK;
    QPushButton *PushButtonMarker;
    QLabel *label;
    QPushButton *PushButtonShowWhole;
    QToolButton *toolButtonRegOK;
    QToolButton *toolButtonRegNG;
    QToolButton *toolButtonOKSize;
    QFrame *frame_2;
    QLabel *labelK_15;
    QLabel *labelK_16;
    QLabel *labelK_17;
    QToolButton *toolButtonBrightnessDarkStrict;
    QToolButton *toolButtonBrightnessLightStrict;
    QToolButton *toolButtonShiftStrict;
    QLabel *labelK_18;
    QSpinBox *spinBoxBrightnessDark;
    QSpinBox *spinBoxBrightnessLight;
    QSpinBox *spinBoxShift;
    QToolButton *toolButtonShiftLoose;
    QToolButton *toolButtonBrightnessLightLoose;
    QLabel *labelK_19;
    QToolButton *toolButtonBrightnessDarkStrictLoose;
    QFrame *frameThresholdLevel;
    QLabel *labelK_8;
    QFrame *frame_5;
    QToolButton *toolButtonNarrow;
    QToolButton *toolButtonBroad;
    QStackedWidget *stackedWidget;
    QWidget *Broad;
    QFrame *frame_3;
    QLabel *labelK_5;
    QSlider *horizontalSliderSizeB;
    QDoubleSpinBox *doubleSpinBoxSizeBMM;
    QLabel *labelK_4;
    QLabel *labelK_3;
    QSpinBox *spinBoxSizeB;
    QSpinBox *spinBoxLengthB;
    QDoubleSpinBox *doubleSpinBoxLengthBMM;
    QLabel *labelK_12;
    QLabel *labelK_13;
    QSlider *horizontalSliderLengthB;
    QLabel *labelK_14;
    QFrame *frame_4;
    QLabel *labelK_6;
    QLabel *labelK_9;
    QSpinBox *spinBoxBCL;
    QLabel *labelK_7;
    QSpinBox *spinBoxBYH;
    QSpinBox *spinBoxBCH;
    QSpinBox *spinBoxBMH;
    QSlider *horizontalSliderBYH;
    QSlider *horizontalSliderBCH;
    QSlider *horizontalSliderBMH;
    QSlider *horizontalSliderBML;
    QSlider *horizontalSliderBYL;
    QLabel *labelK_2;
    QSpinBox *spinBoxBYL;
    QSlider *horizontalSliderBCL;
    QSpinBox *spinBoxBML;
    QLabel *labelK_10;
    QLabel *labelK_11;
    QWidget *Narrow;
    QFrame *frame_6;
    QLabel *labelK_20;
    QSlider *horizontalSliderSizeN;
    QDoubleSpinBox *doubleSpinBoxSizeNMM;
    QLabel *labelK_21;
    QLabel *labelK_22;
    QSpinBox *spinBoxSizeN;
    QSpinBox *spinBoxLengthN;
    QDoubleSpinBox *doubleSpinBoxLengthNMM;
    QLabel *labelK_23;
    QLabel *labelK_24;
    QSlider *horizontalSliderLengthN;
    QLabel *labelK_25;
    QFrame *frame_7;
    QLabel *labelK_26;
    QLabel *labelK_27;
    QSpinBox *spinBoxNCL;
    QLabel *labelK_28;
    QSpinBox *spinBoxNYH;
    QSpinBox *spinBoxNCH;
    QSpinBox *spinBoxNMH;
    QSlider *horizontalSliderNYH;
    QSlider *horizontalSliderNCH;
    QSlider *horizontalSliderNMH;
    QSlider *horizontalSliderNML;
    QSlider *horizontalSliderNYL;
    QLabel *labelK_29;
    QSpinBox *spinBoxNYL;
    QSlider *horizontalSliderNCL;
    QSpinBox *spinBoxNML;
    QLabel *labelK_30;
    QLabel *labelK_31;

    void setupUi(QWidget *EachThresholdFormVariable)
    {
        if (EachThresholdFormVariable->objectName().isEmpty())
            EachThresholdFormVariable->setObjectName("EachThresholdFormVariable");
        EachThresholdFormVariable->resize(1151, 922);
        toolButtonCancel = new QToolButton(EachThresholdFormVariable);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(980, 820, 161, 81));
        QFont font;
        font.setPointSize(16);
        toolButtonCancel->setFont(font);
        toolButtonCancel->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        frameMarkerImage = new QFrame(EachThresholdFormVariable);
        frameMarkerImage->setObjectName("frameMarkerImage");
        frameMarkerImage->setGeometry(QRect(580, 103, 561, 431));
        frameMarkerImage->setFrameShape(QFrame::StyledPanel);
        frameMarkerImage->setFrameShadow(QFrame::Raised);
        toolButtonOK = new QToolButton(EachThresholdFormVariable);
        toolButtonOK->setObjectName("toolButtonOK");
        toolButtonOK->setGeometry(QRect(30, 740, 501, 81));
        toolButtonOK->setFont(font);
        toolButtonOK->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonMarker = new QPushButton(EachThresholdFormVariable);
        PushButtonMarker->setObjectName("PushButtonMarker");
        PushButtonMarker->setGeometry(QRect(590, 10, 261, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font1.setPointSize(24);
        PushButtonMarker->setFont(font1);
        PushButtonMarker->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed{ 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(160, 225, 160, 255), stop:1 rgba(80, 141, 80, 255));\n"
"}"));
        PushButtonMarker->setCheckable(false);
        PushButtonMarker->setChecked(false);
        PushButtonMarker->setAutoDefault(false);
        PushButtonMarker->setFlat(false);
        label = new QLabel(EachThresholdFormVariable);
        label->setObjectName("label");
        label->setGeometry(QRect(580, 70, 561, 31));
        QFont font2;
        font2.setPointSize(12);
        label->setFont(font2);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        PushButtonShowWhole = new QPushButton(EachThresholdFormVariable);
        PushButtonShowWhole->setObjectName("PushButtonShowWhole");
        PushButtonShowWhole->setGeometry(QRect(870, 10, 261, 51));
        PushButtonShowWhole->setFont(font1);
        PushButtonShowWhole->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed{ 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(160, 225, 160, 255), stop:1 rgba(80, 141, 80, 255));\n"
"}"));
        PushButtonShowWhole->setCheckable(false);
        PushButtonShowWhole->setChecked(false);
        PushButtonShowWhole->setAutoDefault(false);
        PushButtonShowWhole->setFlat(false);
        toolButtonRegOK = new QToolButton(EachThresholdFormVariable);
        toolButtonRegOK->setObjectName("toolButtonRegOK");
        toolButtonRegOK->setGeometry(QRect(610, 820, 161, 81));
        toolButtonRegOK->setFont(font);
        toolButtonRegOK->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonRegNG = new QToolButton(EachThresholdFormVariable);
        toolButtonRegNG->setObjectName("toolButtonRegNG");
        toolButtonRegNG->setGeometry(QRect(790, 820, 161, 81));
        toolButtonRegNG->setFont(font);
        toolButtonRegNG->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonOKSize = new QToolButton(EachThresholdFormVariable);
        toolButtonOKSize->setObjectName("toolButtonOKSize");
        toolButtonOKSize->setGeometry(QRect(30, 830, 501, 81));
        toolButtonOKSize->setFont(font);
        toolButtonOKSize->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        frame_2 = new QFrame(EachThresholdFormVariable);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(630, 540, 501, 271));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        labelK_15 = new QLabel(frame_2);
        labelK_15->setObjectName("labelK_15");
        labelK_15->setGeometry(QRect(10, 60, 251, 51));
        QFont font3;
        font3.setPointSize(18);
        labelK_15->setFont(font3);
        labelK_15->setAlignment(Qt::AlignCenter);
        labelK_16 = new QLabel(frame_2);
        labelK_16->setObjectName("labelK_16");
        labelK_16->setGeometry(QRect(10, 130, 251, 51));
        labelK_16->setFont(font3);
        labelK_16->setAlignment(Qt::AlignCenter);
        labelK_17 = new QLabel(frame_2);
        labelK_17->setObjectName("labelK_17");
        labelK_17->setGeometry(QRect(10, 200, 241, 51));
        labelK_17->setFont(font3);
        labelK_17->setAlignment(Qt::AlignCenter);
        toolButtonBrightnessDarkStrict = new QToolButton(frame_2);
        toolButtonBrightnessDarkStrict->setObjectName("toolButtonBrightnessDarkStrict");
        toolButtonBrightnessDarkStrict->setGeometry(QRect(420, 60, 65, 64));
        toolButtonBrightnessDarkStrict->setFont(font2);
        toolButtonBrightnessLightStrict = new QToolButton(frame_2);
        toolButtonBrightnessLightStrict->setObjectName("toolButtonBrightnessLightStrict");
        toolButtonBrightnessLightStrict->setGeometry(QRect(420, 130, 65, 64));
        toolButtonBrightnessLightStrict->setFont(font2);
        toolButtonShiftStrict = new QToolButton(frame_2);
        toolButtonShiftStrict->setObjectName("toolButtonShiftStrict");
        toolButtonShiftStrict->setGeometry(QRect(420, 200, 65, 64));
        toolButtonShiftStrict->setFont(font2);
        labelK_18 = new QLabel(frame_2);
        labelK_18->setObjectName("labelK_18");
        labelK_18->setGeometry(QRect(400, 0, 101, 51));
        labelK_18->setFont(font3);
        labelK_18->setAlignment(Qt::AlignCenter);
        spinBoxBrightnessDark = new QSpinBox(frame_2);
        spinBoxBrightnessDark->setObjectName("spinBoxBrightnessDark");
        spinBoxBrightnessDark->setGeometry(QRect(343, 60, 71, 61));
        QFont font4;
        font4.setPointSize(20);
        spinBoxBrightnessDark->setFont(font4);
        spinBoxBrightnessDark->setFrame(true);
        spinBoxBrightnessDark->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxBrightnessDark->setMinimum(-10);
        spinBoxBrightnessDark->setMaximum(10);
        spinBoxBrightnessLight = new QSpinBox(frame_2);
        spinBoxBrightnessLight->setObjectName("spinBoxBrightnessLight");
        spinBoxBrightnessLight->setGeometry(QRect(343, 130, 71, 61));
        spinBoxBrightnessLight->setFont(font4);
        spinBoxBrightnessLight->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxBrightnessLight->setMinimum(-10);
        spinBoxBrightnessLight->setMaximum(10);
        spinBoxShift = new QSpinBox(frame_2);
        spinBoxShift->setObjectName("spinBoxShift");
        spinBoxShift->setGeometry(QRect(343, 200, 71, 61));
        spinBoxShift->setFont(font4);
        spinBoxShift->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxShift->setMinimum(-10);
        spinBoxShift->setMaximum(10);
        toolButtonShiftLoose = new QToolButton(frame_2);
        toolButtonShiftLoose->setObjectName("toolButtonShiftLoose");
        toolButtonShiftLoose->setGeometry(QRect(270, 200, 65, 64));
        toolButtonShiftLoose->setFont(font2);
        toolButtonBrightnessLightLoose = new QToolButton(frame_2);
        toolButtonBrightnessLightLoose->setObjectName("toolButtonBrightnessLightLoose");
        toolButtonBrightnessLightLoose->setGeometry(QRect(270, 130, 65, 64));
        toolButtonBrightnessLightLoose->setFont(font2);
        labelK_19 = new QLabel(frame_2);
        labelK_19->setObjectName("labelK_19");
        labelK_19->setGeometry(QRect(250, 0, 101, 51));
        labelK_19->setFont(font3);
        labelK_19->setAlignment(Qt::AlignCenter);
        toolButtonBrightnessDarkStrictLoose = new QToolButton(frame_2);
        toolButtonBrightnessDarkStrictLoose->setObjectName("toolButtonBrightnessDarkStrictLoose");
        toolButtonBrightnessDarkStrictLoose->setGeometry(QRect(270, 60, 65, 64));
        toolButtonBrightnessDarkStrictLoose->setFont(font2);
        frameThresholdLevel = new QFrame(EachThresholdFormVariable);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(10, 0, 551, 151));
        frameThresholdLevel->setFrameShape(QFrame::Panel);
        frameThresholdLevel->setFrameShadow(QFrame::Sunken);
        labelK_8 = new QLabel(frameThresholdLevel);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(0, 0, 551, 31));
        QFont font5;
        font5.setPointSize(14);
        labelK_8->setFont(font5);
        labelK_8->setAlignment(Qt::AlignCenter);
        frame_5 = new QFrame(EachThresholdFormVariable);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(70, 170, 401, 71));
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Raised);
        toolButtonNarrow = new QToolButton(frame_5);
        toolButtonNarrow->setObjectName("toolButtonNarrow");
        toolButtonNarrow->setGeometry(QRect(210, 0, 181, 51));
        toolButtonNarrow->setFont(font);
        toolButtonNarrow->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonNarrow->setCheckable(true);
        toolButtonNarrow->setAutoExclusive(true);
        toolButtonBroad = new QToolButton(frame_5);
        toolButtonBroad->setObjectName("toolButtonBroad");
        toolButtonBroad->setGeometry(QRect(10, 0, 191, 51));
        toolButtonBroad->setFont(font);
        toolButtonBroad->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonBroad->setCheckable(true);
        toolButtonBroad->setChecked(true);
        toolButtonBroad->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(EachThresholdFormVariable);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 230, 571, 501));
        Broad = new QWidget();
        Broad->setObjectName("Broad");
        frame_3 = new QFrame(Broad);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 310, 551, 181));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        labelK_5 = new QLabel(frame_3);
        labelK_5->setObjectName("labelK_5");
        labelK_5->setGeometry(QRect(480, 50, 71, 36));
        QFont font6;
        font6.setPointSize(11);
        labelK_5->setFont(font6);
        labelK_5->setAlignment(Qt::AlignCenter);
        horizontalSliderSizeB = new QSlider(frame_3);
        horizontalSliderSizeB->setObjectName("horizontalSliderSizeB");
        horizontalSliderSizeB->setGeometry(QRect(170, 20, 181, 51));
        horizontalSliderSizeB->setMaximum(10000);
        horizontalSliderSizeB->setOrientation(Qt::Horizontal);
        doubleSpinBoxSizeBMM = new QDoubleSpinBox(frame_3);
        doubleSpinBoxSizeBMM->setObjectName("doubleSpinBoxSizeBMM");
        doubleSpinBoxSizeBMM->setGeometry(QRect(360, 10, 111, 36));
        doubleSpinBoxSizeBMM->setFont(font);
        doubleSpinBoxSizeBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeBMM->setValue(0.500000000000000);
        labelK_4 = new QLabel(frame_3);
        labelK_4->setObjectName("labelK_4");
        labelK_4->setGeometry(QRect(480, 10, 61, 36));
        labelK_4->setFont(font5);
        labelK_4->setAlignment(Qt::AlignCenter);
        labelK_3 = new QLabel(frame_3);
        labelK_3->setObjectName("labelK_3");
        labelK_3->setGeometry(QRect(10, 20, 161, 51));
        labelK_3->setFont(font3);
        labelK_3->setAlignment(Qt::AlignCenter);
        spinBoxSizeB = new QSpinBox(frame_3);
        spinBoxSizeB->setObjectName("spinBoxSizeB");
        spinBoxSizeB->setGeometry(QRect(360, 50, 111, 36));
        spinBoxSizeB->setFont(font);
        spinBoxSizeB->setMaximum(99999999);
        spinBoxSizeB->setValue(2000);
        spinBoxLengthB = new QSpinBox(frame_3);
        spinBoxLengthB->setObjectName("spinBoxLengthB");
        spinBoxLengthB->setGeometry(QRect(360, 130, 111, 36));
        spinBoxLengthB->setFont(font);
        spinBoxLengthB->setMaximum(99999999);
        spinBoxLengthB->setValue(2000);
        doubleSpinBoxLengthBMM = new QDoubleSpinBox(frame_3);
        doubleSpinBoxLengthBMM->setObjectName("doubleSpinBoxLengthBMM");
        doubleSpinBoxLengthBMM->setGeometry(QRect(360, 90, 111, 36));
        doubleSpinBoxLengthBMM->setFont(font);
        doubleSpinBoxLengthBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthBMM->setValue(0.500000000000000);
        labelK_12 = new QLabel(frame_3);
        labelK_12->setObjectName("labelK_12");
        labelK_12->setGeometry(QRect(480, 130, 71, 36));
        labelK_12->setFont(font6);
        labelK_12->setAlignment(Qt::AlignCenter);
        labelK_13 = new QLabel(frame_3);
        labelK_13->setObjectName("labelK_13");
        labelK_13->setGeometry(QRect(480, 90, 61, 36));
        labelK_13->setFont(font5);
        labelK_13->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthB = new QSlider(frame_3);
        horizontalSliderLengthB->setObjectName("horizontalSliderLengthB");
        horizontalSliderLengthB->setGeometry(QRect(170, 100, 181, 51));
        horizontalSliderLengthB->setMaximum(10000);
        horizontalSliderLengthB->setOrientation(Qt::Horizontal);
        labelK_14 = new QLabel(frame_3);
        labelK_14->setObjectName("labelK_14");
        labelK_14->setGeometry(QRect(10, 100, 161, 51));
        labelK_14->setFont(font3);
        labelK_14->setAlignment(Qt::AlignCenter);
        frame_4 = new QFrame(Broad);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 10, 551, 291));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        labelK_6 = new QLabel(frame_4);
        labelK_6->setObjectName("labelK_6");
        labelK_6->setGeometry(QRect(0, 0, 441, 51));
        labelK_6->setFont(font3);
        labelK_6->setAlignment(Qt::AlignCenter);
        labelK_9 = new QLabel(frame_4);
        labelK_9->setObjectName("labelK_9");
        labelK_9->setGeometry(QRect(0, 230, 131, 41));
        QPalette palette;
        QBrush brush(QColor(255, 170, 127, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_9->setPalette(palette);
        labelK_9->setFont(font2);
        labelK_9->setAlignment(Qt::AlignCenter);
        spinBoxBCL = new QSpinBox(frame_4);
        spinBoxBCL->setObjectName("spinBoxBCL");
        spinBoxBCL->setGeometry(QRect(190, 110, 81, 31));
        QPalette palette1;
        QBrush brush2(QColor(0, 255, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBCL->setPalette(palette1);
        spinBoxBCL->setFont(font2);
        spinBoxBCL->setAutoFillBackground(true);
        spinBoxBCL->setMaximum(360);
        spinBoxBCL->setValue(10);
        labelK_7 = new QLabel(frame_4);
        labelK_7->setObjectName("labelK_7");
        labelK_7->setGeometry(QRect(0, 160, 131, 41));
        QPalette palette2;
        QBrush brush4(QColor(255, 0, 255, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush4);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush4);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_7->setPalette(palette2);
        labelK_7->setFont(font2);
        labelK_7->setAlignment(Qt::AlignCenter);
        spinBoxBYH = new QSpinBox(frame_4);
        spinBoxBYH->setObjectName("spinBoxBYH");
        spinBoxBYH->setGeometry(QRect(360, 250, 81, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBYH->setPalette(palette3);
        spinBoxBYH->setFont(font2);
        spinBoxBYH->setAutoFillBackground(true);
        spinBoxBYH->setMaximum(255);
        spinBoxBYH->setValue(10);
        spinBoxBCH = new QSpinBox(frame_4);
        spinBoxBCH->setObjectName("spinBoxBCH");
        spinBoxBCH->setGeometry(QRect(360, 110, 81, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBCH->setPalette(palette4);
        spinBoxBCH->setFont(font2);
        spinBoxBCH->setAutoFillBackground(true);
        spinBoxBCH->setMaximum(360);
        spinBoxBCH->setValue(10);
        spinBoxBMH = new QSpinBox(frame_4);
        spinBoxBMH->setObjectName("spinBoxBMH");
        spinBoxBMH->setGeometry(QRect(360, 180, 81, 31));
        QPalette palette5;
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBMH->setPalette(palette5);
        spinBoxBMH->setFont(font2);
        spinBoxBMH->setAutoFillBackground(true);
        spinBoxBMH->setMaximum(255);
        spinBoxBMH->setValue(10);
        horizontalSliderBYH = new QSlider(frame_4);
        horizontalSliderBYH->setObjectName("horizontalSliderBYH");
        horizontalSliderBYH->setGeometry(QRect(330, 220, 181, 41));
        horizontalSliderBYH->setMaximum(255);
        horizontalSliderBYH->setOrientation(Qt::Horizontal);
        horizontalSliderBCH = new QSlider(frame_4);
        horizontalSliderBCH->setObjectName("horizontalSliderBCH");
        horizontalSliderBCH->setGeometry(QRect(330, 80, 181, 41));
        horizontalSliderBCH->setMaximum(360);
        horizontalSliderBCH->setOrientation(Qt::Horizontal);
        horizontalSliderBMH = new QSlider(frame_4);
        horizontalSliderBMH->setObjectName("horizontalSliderBMH");
        horizontalSliderBMH->setGeometry(QRect(330, 150, 181, 41));
        horizontalSliderBMH->setMaximum(255);
        horizontalSliderBMH->setOrientation(Qt::Horizontal);
        horizontalSliderBML = new QSlider(frame_4);
        horizontalSliderBML->setObjectName("horizontalSliderBML");
        horizontalSliderBML->setGeometry(QRect(140, 150, 181, 41));
        horizontalSliderBML->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderBML->setMaximum(255);
        horizontalSliderBML->setOrientation(Qt::Horizontal);
        horizontalSliderBYL = new QSlider(frame_4);
        horizontalSliderBYL->setObjectName("horizontalSliderBYL");
        horizontalSliderBYL->setGeometry(QRect(140, 220, 181, 41));
        horizontalSliderBYL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderBYL->setMaximum(255);
        horizontalSliderBYL->setOrientation(Qt::Horizontal);
        labelK_2 = new QLabel(frame_4);
        labelK_2->setObjectName("labelK_2");
        labelK_2->setGeometry(QRect(0, 90, 131, 41));
        QPalette palette6;
        QBrush brush5(QColor(85, 255, 255, 255));
        brush5.setStyle(Qt::BrushStyle::SolidPattern);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush5);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush5);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_2->setPalette(palette6);
        labelK_2->setFont(font2);
        labelK_2->setAlignment(Qt::AlignCenter);
        spinBoxBYL = new QSpinBox(frame_4);
        spinBoxBYL->setObjectName("spinBoxBYL");
        spinBoxBYL->setGeometry(QRect(190, 250, 81, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBYL->setPalette(palette7);
        spinBoxBYL->setFont(font2);
        spinBoxBYL->setAutoFillBackground(true);
        spinBoxBYL->setMaximum(255);
        spinBoxBYL->setValue(10);
        horizontalSliderBCL = new QSlider(frame_4);
        horizontalSliderBCL->setObjectName("horizontalSliderBCL");
        horizontalSliderBCL->setGeometry(QRect(140, 80, 181, 41));
        horizontalSliderBCL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderBCL->setMaximum(360);
        horizontalSliderBCL->setOrientation(Qt::Horizontal);
        spinBoxBML = new QSpinBox(frame_4);
        spinBoxBML->setObjectName("spinBoxBML");
        spinBoxBML->setGeometry(QRect(190, 180, 81, 31));
        QPalette palette8;
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxBML->setPalette(palette8);
        spinBoxBML->setFont(font2);
        spinBoxBML->setAutoFillBackground(true);
        spinBoxBML->setMaximum(255);
        spinBoxBML->setValue(10);
        labelK_10 = new QLabel(frame_4);
        labelK_10->setObjectName("labelK_10");
        labelK_10->setGeometry(QRect(150, 50, 151, 31));
        labelK_10->setFont(font5);
        labelK_10->setAlignment(Qt::AlignCenter);
        labelK_11 = new QLabel(frame_4);
        labelK_11->setObjectName("labelK_11");
        labelK_11->setGeometry(QRect(350, 50, 151, 31));
        labelK_11->setFont(font5);
        labelK_11->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(Broad);
        Narrow = new QWidget();
        Narrow->setObjectName("Narrow");
        frame_6 = new QFrame(Narrow);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 310, 551, 181));
        frame_6->setFrameShape(QFrame::Panel);
        frame_6->setFrameShadow(QFrame::Sunken);
        labelK_20 = new QLabel(frame_6);
        labelK_20->setObjectName("labelK_20");
        labelK_20->setGeometry(QRect(480, 50, 71, 36));
        labelK_20->setFont(font6);
        labelK_20->setAlignment(Qt::AlignCenter);
        horizontalSliderSizeN = new QSlider(frame_6);
        horizontalSliderSizeN->setObjectName("horizontalSliderSizeN");
        horizontalSliderSizeN->setGeometry(QRect(170, 20, 181, 51));
        horizontalSliderSizeN->setMaximum(10000);
        horizontalSliderSizeN->setOrientation(Qt::Horizontal);
        doubleSpinBoxSizeNMM = new QDoubleSpinBox(frame_6);
        doubleSpinBoxSizeNMM->setObjectName("doubleSpinBoxSizeNMM");
        doubleSpinBoxSizeNMM->setGeometry(QRect(360, 10, 111, 36));
        doubleSpinBoxSizeNMM->setFont(font);
        doubleSpinBoxSizeNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeNMM->setValue(0.500000000000000);
        labelK_21 = new QLabel(frame_6);
        labelK_21->setObjectName("labelK_21");
        labelK_21->setGeometry(QRect(480, 10, 61, 36));
        labelK_21->setFont(font5);
        labelK_21->setAlignment(Qt::AlignCenter);
        labelK_22 = new QLabel(frame_6);
        labelK_22->setObjectName("labelK_22");
        labelK_22->setGeometry(QRect(10, 20, 161, 51));
        labelK_22->setFont(font3);
        labelK_22->setAlignment(Qt::AlignCenter);
        spinBoxSizeN = new QSpinBox(frame_6);
        spinBoxSizeN->setObjectName("spinBoxSizeN");
        spinBoxSizeN->setGeometry(QRect(360, 50, 111, 36));
        spinBoxSizeN->setFont(font);
        spinBoxSizeN->setMaximum(99999999);
        spinBoxSizeN->setValue(2000);
        spinBoxLengthN = new QSpinBox(frame_6);
        spinBoxLengthN->setObjectName("spinBoxLengthN");
        spinBoxLengthN->setGeometry(QRect(360, 130, 111, 36));
        spinBoxLengthN->setFont(font);
        spinBoxLengthN->setMaximum(99999999);
        spinBoxLengthN->setValue(2000);
        doubleSpinBoxLengthNMM = new QDoubleSpinBox(frame_6);
        doubleSpinBoxLengthNMM->setObjectName("doubleSpinBoxLengthNMM");
        doubleSpinBoxLengthNMM->setGeometry(QRect(360, 90, 111, 36));
        doubleSpinBoxLengthNMM->setFont(font);
        doubleSpinBoxLengthNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthNMM->setValue(0.500000000000000);
        labelK_23 = new QLabel(frame_6);
        labelK_23->setObjectName("labelK_23");
        labelK_23->setGeometry(QRect(480, 130, 71, 36));
        labelK_23->setFont(font6);
        labelK_23->setAlignment(Qt::AlignCenter);
        labelK_24 = new QLabel(frame_6);
        labelK_24->setObjectName("labelK_24");
        labelK_24->setGeometry(QRect(480, 90, 61, 36));
        labelK_24->setFont(font5);
        labelK_24->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthN = new QSlider(frame_6);
        horizontalSliderLengthN->setObjectName("horizontalSliderLengthN");
        horizontalSliderLengthN->setGeometry(QRect(170, 100, 181, 51));
        horizontalSliderLengthN->setMaximum(10000);
        horizontalSliderLengthN->setOrientation(Qt::Horizontal);
        labelK_25 = new QLabel(frame_6);
        labelK_25->setObjectName("labelK_25");
        labelK_25->setGeometry(QRect(10, 100, 161, 51));
        labelK_25->setFont(font3);
        labelK_25->setAlignment(Qt::AlignCenter);
        frame_7 = new QFrame(Narrow);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(10, 10, 551, 291));
        frame_7->setFrameShape(QFrame::Panel);
        frame_7->setFrameShadow(QFrame::Sunken);
        labelK_26 = new QLabel(frame_7);
        labelK_26->setObjectName("labelK_26");
        labelK_26->setGeometry(QRect(0, 0, 441, 51));
        labelK_26->setFont(font3);
        labelK_26->setAlignment(Qt::AlignCenter);
        labelK_27 = new QLabel(frame_7);
        labelK_27->setObjectName("labelK_27");
        labelK_27->setGeometry(QRect(0, 230, 131, 41));
        QPalette palette9;
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_27->setPalette(palette9);
        labelK_27->setFont(font2);
        labelK_27->setAlignment(Qt::AlignCenter);
        spinBoxNCL = new QSpinBox(frame_7);
        spinBoxNCL->setObjectName("spinBoxNCL");
        spinBoxNCL->setGeometry(QRect(190, 110, 81, 31));
        QPalette palette10;
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette10.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNCL->setPalette(palette10);
        spinBoxNCL->setFont(font2);
        spinBoxNCL->setAutoFillBackground(true);
        spinBoxNCL->setMaximum(360);
        spinBoxNCL->setValue(10);
        labelK_28 = new QLabel(frame_7);
        labelK_28->setObjectName("labelK_28");
        labelK_28->setGeometry(QRect(0, 160, 131, 41));
        QPalette palette11;
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush4);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush4);
        palette11.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_28->setPalette(palette11);
        labelK_28->setFont(font2);
        labelK_28->setAlignment(Qt::AlignCenter);
        spinBoxNYH = new QSpinBox(frame_7);
        spinBoxNYH->setObjectName("spinBoxNYH");
        spinBoxNYH->setGeometry(QRect(360, 250, 81, 31));
        QPalette palette12;
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette12.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNYH->setPalette(palette12);
        spinBoxNYH->setFont(font2);
        spinBoxNYH->setAutoFillBackground(true);
        spinBoxNYH->setMaximum(255);
        spinBoxNYH->setValue(10);
        spinBoxNCH = new QSpinBox(frame_7);
        spinBoxNCH->setObjectName("spinBoxNCH");
        spinBoxNCH->setGeometry(QRect(360, 110, 81, 31));
        QPalette palette13;
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette13.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNCH->setPalette(palette13);
        spinBoxNCH->setFont(font2);
        spinBoxNCH->setAutoFillBackground(true);
        spinBoxNCH->setMaximum(360);
        spinBoxNCH->setValue(10);
        spinBoxNMH = new QSpinBox(frame_7);
        spinBoxNMH->setObjectName("spinBoxNMH");
        spinBoxNMH->setGeometry(QRect(360, 180, 81, 31));
        QPalette palette14;
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNMH->setPalette(palette14);
        spinBoxNMH->setFont(font2);
        spinBoxNMH->setAutoFillBackground(true);
        spinBoxNMH->setMaximum(255);
        spinBoxNMH->setValue(10);
        horizontalSliderNYH = new QSlider(frame_7);
        horizontalSliderNYH->setObjectName("horizontalSliderNYH");
        horizontalSliderNYH->setGeometry(QRect(330, 220, 181, 41));
        horizontalSliderNYH->setMaximum(255);
        horizontalSliderNYH->setOrientation(Qt::Horizontal);
        horizontalSliderNCH = new QSlider(frame_7);
        horizontalSliderNCH->setObjectName("horizontalSliderNCH");
        horizontalSliderNCH->setGeometry(QRect(330, 80, 181, 41));
        horizontalSliderNCH->setMaximum(360);
        horizontalSliderNCH->setOrientation(Qt::Horizontal);
        horizontalSliderNMH = new QSlider(frame_7);
        horizontalSliderNMH->setObjectName("horizontalSliderNMH");
        horizontalSliderNMH->setGeometry(QRect(330, 150, 181, 41));
        horizontalSliderNMH->setMaximum(255);
        horizontalSliderNMH->setOrientation(Qt::Horizontal);
        horizontalSliderNML = new QSlider(frame_7);
        horizontalSliderNML->setObjectName("horizontalSliderNML");
        horizontalSliderNML->setGeometry(QRect(140, 150, 181, 41));
        horizontalSliderNML->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderNML->setMaximum(255);
        horizontalSliderNML->setOrientation(Qt::Horizontal);
        horizontalSliderNYL = new QSlider(frame_7);
        horizontalSliderNYL->setObjectName("horizontalSliderNYL");
        horizontalSliderNYL->setGeometry(QRect(140, 220, 181, 41));
        horizontalSliderNYL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderNYL->setMaximum(255);
        horizontalSliderNYL->setOrientation(Qt::Horizontal);
        labelK_29 = new QLabel(frame_7);
        labelK_29->setObjectName("labelK_29");
        labelK_29->setGeometry(QRect(0, 90, 131, 41));
        QPalette palette15;
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush5);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush5);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush1);
        labelK_29->setPalette(palette15);
        labelK_29->setFont(font2);
        labelK_29->setAlignment(Qt::AlignCenter);
        spinBoxNYL = new QSpinBox(frame_7);
        spinBoxNYL->setObjectName("spinBoxNYL");
        spinBoxNYL->setGeometry(QRect(190, 250, 81, 31));
        QPalette palette16;
        palette16.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette16.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette16.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNYL->setPalette(palette16);
        spinBoxNYL->setFont(font2);
        spinBoxNYL->setAutoFillBackground(true);
        spinBoxNYL->setMaximum(255);
        spinBoxNYL->setValue(10);
        horizontalSliderNCL = new QSlider(frame_7);
        horizontalSliderNCL->setObjectName("horizontalSliderNCL");
        horizontalSliderNCL->setGeometry(QRect(140, 80, 181, 41));
        horizontalSliderNCL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderNCL->setMaximum(360);
        horizontalSliderNCL->setOrientation(Qt::Horizontal);
        spinBoxNML = new QSpinBox(frame_7);
        spinBoxNML->setObjectName("spinBoxNML");
        spinBoxNML->setGeometry(QRect(190, 180, 81, 31));
        QPalette palette17;
        palette17.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette17.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette17.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        spinBoxNML->setPalette(palette17);
        spinBoxNML->setFont(font2);
        spinBoxNML->setAutoFillBackground(true);
        spinBoxNML->setMaximum(255);
        spinBoxNML->setValue(10);
        labelK_30 = new QLabel(frame_7);
        labelK_30->setObjectName("labelK_30");
        labelK_30->setGeometry(QRect(150, 50, 151, 31));
        labelK_30->setFont(font5);
        labelK_30->setAlignment(Qt::AlignCenter);
        labelK_31 = new QLabel(frame_7);
        labelK_31->setObjectName("labelK_31");
        labelK_31->setGeometry(QRect(350, 50, 151, 31));
        labelK_31->setFont(font5);
        labelK_31->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(Narrow);

        retranslateUi(EachThresholdFormVariable);

        PushButtonMarker->setDefault(false);
        PushButtonShowWhole->setDefault(false);
        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EachThresholdFormVariable);
    } // setupUi

    void retranslateUi(QWidget *EachThresholdFormVariable)
    {
        EachThresholdFormVariable->setWindowTitle(QCoreApplication::translate("EachThresholdFormVariable", "Setting", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        toolButtonOK->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\201\223\343\201\256\350\274\235\345\272\246\345\244\211\345\214\226\343\201\250\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272\343\202\222\350\250\255\345\256\232", nullptr));
        PushButtonMarker->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\203\236\343\203\274\343\202\253\343\203\274", nullptr));
        label->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\203\236\343\203\274\343\202\253\343\203\274\347\256\207\346\211\200", nullptr));
        PushButtonShowWhole->setText(QCoreApplication::translate("EachThresholdFormVariable", "\345\205\250\344\275\223\350\241\250\347\244\272", nullptr));
        toolButtonRegOK->setText(QCoreApplication::translate("EachThresholdFormVariable", "OK\347\231\273\351\214\262", nullptr));
        toolButtonRegNG->setText(QCoreApplication::translate("EachThresholdFormVariable", "NG\347\231\273\351\214\262", nullptr));
        toolButtonOKSize->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\202\265\343\202\244\343\202\272\343\201\256\343\201\277\343\202\222\350\250\255\345\256\232", nullptr));
        labelK_15->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\232\227\343\201\204\351\203\250\345\210\206\343\201\256\346\277\203\346\267\241", nullptr));
        labelK_16->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\230\216\343\202\213\343\201\204\351\203\250\345\210\206\343\201\256\346\277\203\346\267\241", nullptr));
        labelK_17->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\202\272\343\203\254\350\250\261\345\256\271", nullptr));
        toolButtonBrightnessDarkStrict->setText(QCoreApplication::translate("EachThresholdFormVariable", "\342\226\262", nullptr));
        toolButtonBrightnessLightStrict->setText(QCoreApplication::translate("EachThresholdFormVariable", "\342\226\262", nullptr));
        toolButtonShiftStrict->setText(QCoreApplication::translate("EachThresholdFormVariable", "\342\226\262", nullptr));
        labelK_18->setText(QCoreApplication::translate("EachThresholdFormVariable", "\345\216\263\343\201\227\343\201\204", nullptr));
        toolButtonShiftLoose->setText(QCoreApplication::translate("EachThresholdFormVariable", "\342\226\274", nullptr));
        toolButtonBrightnessLightLoose->setText(QCoreApplication::translate("EachThresholdFormVariable", "\342\226\274", nullptr));
        labelK_19->setText(QCoreApplication::translate("EachThresholdFormVariable", "\347\267\251\343\201\204", nullptr));
        toolButtonBrightnessDarkStrictLoose->setText(QCoreApplication::translate("EachThresholdFormVariable", "\342\226\274", nullptr));
        labelK_8->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\203\254\343\203\231\343\203\253\347\242\272\350\252\215\357\274\217\350\250\255\345\256\232", nullptr));
        toolButtonNarrow->setText(QCoreApplication::translate("EachThresholdFormVariable", "\347\213\255\345\237\237", nullptr));
        toolButtonBroad->setText(QCoreApplication::translate("EachThresholdFormVariable", "\345\272\203\345\237\237\357\274\217\344\270\200\350\210\254", nullptr));
        labelK_5->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_4->setText(QCoreApplication::translate("EachThresholdFormVariable", "mm2", nullptr));
        labelK_3->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_12->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_13->setText(QCoreApplication::translate("EachThresholdFormVariable", "mm", nullptr));
        labelK_14->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
        labelK_6->setText(QCoreApplication::translate("EachThresholdFormVariable", "\350\274\235\345\272\246\345\244\211\345\214\226\343\201\256\346\244\234\345\207\272", nullptr));
        labelK_9->setText(QCoreApplication::translate("EachThresholdFormVariable", "V\343\200\200\357\274\210\346\230\216\345\272\246\357\274\211", nullptr));
        labelK_7->setText(QCoreApplication::translate("EachThresholdFormVariable", "S\343\200\200\357\274\210\345\275\251\345\272\246\357\274\211", nullptr));
        labelK_2->setText(QCoreApplication::translate("EachThresholdFormVariable", "H\343\200\200\357\274\210\350\211\262\347\233\270\357\274\211", nullptr));
        labelK_10->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\232\227\345\201\264", nullptr));
        labelK_11->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\230\216\345\201\264", nullptr));
        labelK_20->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_21->setText(QCoreApplication::translate("EachThresholdFormVariable", "mm2", nullptr));
        labelK_22->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_23->setText(QCoreApplication::translate("EachThresholdFormVariable", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_24->setText(QCoreApplication::translate("EachThresholdFormVariable", "mm", nullptr));
        labelK_25->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
        labelK_26->setText(QCoreApplication::translate("EachThresholdFormVariable", "\350\274\235\345\272\246\345\244\211\345\214\226\343\201\256\346\244\234\345\207\272", nullptr));
        labelK_27->setText(QCoreApplication::translate("EachThresholdFormVariable", "V\343\200\200\357\274\210\346\230\216\345\272\246\357\274\211", nullptr));
        labelK_28->setText(QCoreApplication::translate("EachThresholdFormVariable", "S\343\200\200\357\274\210\345\275\251\345\272\246\357\274\211", nullptr));
        labelK_29->setText(QCoreApplication::translate("EachThresholdFormVariable", "H\343\200\200\357\274\210\350\211\262\347\233\270\357\274\211", nullptr));
        labelK_30->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\232\227\345\201\264", nullptr));
        labelK_31->setText(QCoreApplication::translate("EachThresholdFormVariable", "\346\230\216\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EachThresholdFormVariable: public Ui_EachThresholdFormVariable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EACHTHRESHOLDFORMVARIABLE_H
