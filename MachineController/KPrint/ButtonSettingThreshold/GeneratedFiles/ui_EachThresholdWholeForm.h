/********************************************************************************
** Form generated from reading UI file 'EachThresholdWholeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EACHTHRESHOLDWHOLEFORM_H
#define UI_EACHTHRESHOLDWHOLEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EachThresholdWholeForm
{
public:
    QToolButton *toolButtonOKSize;
    QFrame *frame_4;
    QLabel *labelK_6;
    QSlider *horizontalSliderOozing;
    QDoubleSpinBox *doubleSpinBoxOozingMM;
    QLabel *labelK_8;
    QSpinBox *spinBoxOozing;
    QLabel *labelK_29;
    QLabel *labelK_31;
    QDoubleSpinBox *doubleSpinBoxSearchAreaXMM;
    QSlider *horizontalSliderSearchAreaX;
    QSpinBox *spinBoxSearchAreaX;
    QLabel *labelK_32;
    QLabel *labelK_33;
    QLabel *labelK_34;
    QLabel *labelK_35;
    QDoubleSpinBox *doubleSpinBoxSearchAreaYMM;
    QSpinBox *spinBoxSearchAreaY;
    QLabel *labelK_36;
    QSlider *horizontalSliderSearchAreaY;
    QFrame *frame_3;
    QLabel *labelK_5;
    QLabel *labelK_4;
    QLabel *labelK_7;
    QLabel *labelK_9;
    QLabel *labelK_20;
    QFrame *frame_7;
    QToolButton *toolButtonNarrow;
    QToolButton *toolButtonBroad;
    QStackedWidget *stackedWidget;
    QWidget *Broad;
    QSpinBox *spinBoxLengthB;
    QLabel *labelK_3;
    QSlider *horizontalSliderLengthB;
    QSlider *horizontalSliderSizeB;
    QLabel *labelK_10;
    QDoubleSpinBox *doubleSpinBoxSizeBMM;
    QSpinBox *spinBoxSizeB;
    QDoubleSpinBox *doubleSpinBoxLengthBMM;
    QWidget *Narrow;
    QLabel *labelK_37;
    QSlider *horizontalSliderLengthN;
    QSlider *horizontalSliderSizeN;
    QSpinBox *spinBoxLengthN;
    QLabel *labelK_38;
    QDoubleSpinBox *doubleSpinBoxSizeNMM;
    QSpinBox *spinBoxSizeN;
    QDoubleSpinBox *doubleSpinBoxLengthNMM;
    QFrame *frame_6;
    QLabel *labelK_22;
    QSlider *horizontalSliderSIze;
    QDoubleSpinBox *doubleSpinBoxMultiSizeMM;
    QLabel *labelK_23;
    QSpinBox *spinBoxMultiSize;
    QSlider *horizontalSliderNGCount;
    QLabel *labelK_25;
    QSpinBox *spinBoxMultiNGCount;
    QLabel *labelK_26;
    QLabel *labelK_27;
    QLabel *labelK_28;
    QLabel *labelK_30;
    QFrame *frameThresholdLevel;
    QLabel *labelK_16;
    QFrame *frame_2;
    QLabel *labelK_11;
    QLabel *labelK_14;
    QLabel *labelK_15;
    QToolButton *toolButtonBrightnessDarkStrict;
    QToolButton *toolButtonBrightnessLightStrict;
    QToolButton *toolButtonShiftStrict;
    QLabel *labelK_12;
    QSpinBox *spinBoxBrightnessDark;
    QSpinBox *spinBoxBrightnessLight;
    QSpinBox *spinBoxShift;
    QToolButton *toolButtonShiftLoose;
    QLabel *labelK_13;
    QToolButton *toolButtonBrightnessLightLoose;
    QToolButton *toolButtonBrightnessDarkStrictLoose;
    QFrame *frame_5;
    QLabel *labelK_17;
    QSlider *horizontalSliderRedOKDot;
    QDoubleSpinBox *doubleSpinBoxRedOKDotMM;
    QLabel *labelK_18;
    QLabel *labelK_19;
    QSpinBox *spinBoxRedOKDot;
    QLabel *labelK_21;
    QToolButton *toolButtonClose;
    QFrame *frameImagePanel;
    QLabel *labelK_24;
    QSpinBox *spinBoxLibID;
    QLineEdit *lineEditLibName;
    QToolButton *toolButtonEnable;
    QListWidget *listWidgetOperationHistory;

    void setupUi(QWidget *EachThresholdWholeForm)
    {
        if (EachThresholdWholeForm->objectName().isEmpty())
            EachThresholdWholeForm->setObjectName("EachThresholdWholeForm");
        EachThresholdWholeForm->resize(1600, 1050);
        toolButtonOKSize = new QToolButton(EachThresholdWholeForm);
        toolButtonOKSize->setObjectName("toolButtonOKSize");
        toolButtonOKSize->setGeometry(QRect(920, 960, 341, 81));
        QFont font;
        font.setPointSize(16);
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
        frame_4 = new QFrame(EachThresholdWholeForm);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 530, 661, 231));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        labelK_6 = new QLabel(frame_4);
        labelK_6->setObjectName("labelK_6");
        labelK_6->setGeometry(QRect(580, 40, 81, 36));
        QFont font1;
        font1.setPointSize(11);
        labelK_6->setFont(font1);
        labelK_6->setAlignment(Qt::AlignCenter);
        horizontalSliderOozing = new QSlider(frame_4);
        horizontalSliderOozing->setObjectName("horizontalSliderOozing");
        horizontalSliderOozing->setGeometry(QRect(210, 20, 241, 51));
        horizontalSliderOozing->setOrientation(Qt::Horizontal);
        doubleSpinBoxOozingMM = new QDoubleSpinBox(frame_4);
        doubleSpinBoxOozingMM->setObjectName("doubleSpinBoxOozingMM");
        doubleSpinBoxOozingMM->setGeometry(QRect(460, 10, 111, 36));
        doubleSpinBoxOozingMM->setFont(font);
        doubleSpinBoxOozingMM->setMaximum(10000.000000000000000);
        doubleSpinBoxOozingMM->setValue(0.500000000000000);
        labelK_8 = new QLabel(frame_4);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(580, 10, 61, 36));
        QFont font2;
        font2.setPointSize(14);
        labelK_8->setFont(font2);
        labelK_8->setAlignment(Qt::AlignCenter);
        spinBoxOozing = new QSpinBox(frame_4);
        spinBoxOozing->setObjectName("spinBoxOozing");
        spinBoxOozing->setGeometry(QRect(460, 42, 111, 36));
        spinBoxOozing->setFont(font);
        spinBoxOozing->setMaximum(99999999);
        spinBoxOozing->setValue(2000);
        labelK_29 = new QLabel(frame_4);
        labelK_29->setObjectName("labelK_29");
        labelK_29->setGeometry(QRect(50, 20, 141, 41));
        QFont font3;
        font3.setPointSize(18);
        labelK_29->setFont(font3);
        labelK_29->setAlignment(Qt::AlignCenter);
        labelK_31 = new QLabel(frame_4);
        labelK_31->setObjectName("labelK_31");
        labelK_31->setGeometry(QRect(580, 80, 61, 36));
        labelK_31->setFont(font2);
        labelK_31->setAlignment(Qt::AlignCenter);
        doubleSpinBoxSearchAreaXMM = new QDoubleSpinBox(frame_4);
        doubleSpinBoxSearchAreaXMM->setObjectName("doubleSpinBoxSearchAreaXMM");
        doubleSpinBoxSearchAreaXMM->setGeometry(QRect(460, 80, 111, 36));
        doubleSpinBoxSearchAreaXMM->setFont(font);
        doubleSpinBoxSearchAreaXMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSearchAreaXMM->setValue(0.500000000000000);
        horizontalSliderSearchAreaX = new QSlider(frame_4);
        horizontalSliderSearchAreaX->setObjectName("horizontalSliderSearchAreaX");
        horizontalSliderSearchAreaX->setGeometry(QRect(210, 90, 241, 51));
        horizontalSliderSearchAreaX->setOrientation(Qt::Horizontal);
        spinBoxSearchAreaX = new QSpinBox(frame_4);
        spinBoxSearchAreaX->setObjectName("spinBoxSearchAreaX");
        spinBoxSearchAreaX->setGeometry(QRect(460, 112, 111, 36));
        spinBoxSearchAreaX->setFont(font);
        spinBoxSearchAreaX->setMaximum(99999999);
        spinBoxSearchAreaX->setValue(2000);
        labelK_32 = new QLabel(frame_4);
        labelK_32->setObjectName("labelK_32");
        labelK_32->setGeometry(QRect(580, 110, 81, 36));
        labelK_32->setFont(font1);
        labelK_32->setAlignment(Qt::AlignCenter);
        labelK_33 = new QLabel(frame_4);
        labelK_33->setObjectName("labelK_33");
        labelK_33->setGeometry(QRect(10, 90, 191, 41));
        labelK_33->setFont(font3);
        labelK_33->setAlignment(Qt::AlignCenter);
        labelK_34 = new QLabel(frame_4);
        labelK_34->setObjectName("labelK_34");
        labelK_34->setGeometry(QRect(580, 150, 61, 36));
        labelK_34->setFont(font2);
        labelK_34->setAlignment(Qt::AlignCenter);
        labelK_35 = new QLabel(frame_4);
        labelK_35->setObjectName("labelK_35");
        labelK_35->setGeometry(QRect(580, 180, 81, 36));
        labelK_35->setFont(font1);
        labelK_35->setAlignment(Qt::AlignCenter);
        doubleSpinBoxSearchAreaYMM = new QDoubleSpinBox(frame_4);
        doubleSpinBoxSearchAreaYMM->setObjectName("doubleSpinBoxSearchAreaYMM");
        doubleSpinBoxSearchAreaYMM->setGeometry(QRect(460, 150, 111, 36));
        doubleSpinBoxSearchAreaYMM->setFont(font);
        doubleSpinBoxSearchAreaYMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSearchAreaYMM->setValue(0.500000000000000);
        spinBoxSearchAreaY = new QSpinBox(frame_4);
        spinBoxSearchAreaY->setObjectName("spinBoxSearchAreaY");
        spinBoxSearchAreaY->setGeometry(QRect(460, 182, 111, 36));
        spinBoxSearchAreaY->setFont(font);
        spinBoxSearchAreaY->setMaximum(99999999);
        spinBoxSearchAreaY->setValue(2000);
        labelK_36 = new QLabel(frame_4);
        labelK_36->setObjectName("labelK_36");
        labelK_36->setGeometry(QRect(10, 160, 191, 41));
        labelK_36->setFont(font3);
        labelK_36->setAlignment(Qt::AlignCenter);
        horizontalSliderSearchAreaY = new QSlider(frame_4);
        horizontalSliderSearchAreaY->setObjectName("horizontalSliderSearchAreaY");
        horizontalSliderSearchAreaY->setGeometry(QRect(210, 160, 241, 51));
        horizontalSliderSearchAreaY->setOrientation(Qt::Horizontal);
        frame_3 = new QFrame(EachThresholdWholeForm);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 130, 661, 151));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        labelK_5 = new QLabel(frame_3);
        labelK_5->setObjectName("labelK_5");
        labelK_5->setGeometry(QRect(580, 40, 71, 36));
        labelK_5->setFont(font1);
        labelK_5->setAlignment(Qt::AlignCenter);
        labelK_4 = new QLabel(frame_3);
        labelK_4->setObjectName("labelK_4");
        labelK_4->setGeometry(QRect(580, 10, 61, 36));
        labelK_4->setFont(font2);
        labelK_4->setAlignment(Qt::AlignCenter);
        labelK_7 = new QLabel(frame_3);
        labelK_7->setObjectName("labelK_7");
        labelK_7->setGeometry(QRect(580, 110, 71, 36));
        labelK_7->setFont(font1);
        labelK_7->setAlignment(Qt::AlignCenter);
        labelK_9 = new QLabel(frame_3);
        labelK_9->setObjectName("labelK_9");
        labelK_9->setGeometry(QRect(580, 80, 61, 36));
        labelK_9->setFont(font2);
        labelK_9->setAlignment(Qt::AlignCenter);
        labelK_20 = new QLabel(frame_3);
        labelK_20->setObjectName("labelK_20");
        labelK_20->setGeometry(QRect(0, 0, 41, 151));
        labelK_20->setFont(font2);
        labelK_20->setFrameShape(QFrame::Panel);
        labelK_20->setFrameShadow(QFrame::Sunken);
        labelK_20->setAlignment(Qt::AlignCenter);
        frame_7 = new QFrame(frame_3);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(40, 20, 161, 111));
        frame_7->setFrameShape(QFrame::NoFrame);
        frame_7->setFrameShadow(QFrame::Raised);
        toolButtonNarrow = new QToolButton(frame_7);
        toolButtonNarrow->setObjectName("toolButtonNarrow");
        toolButtonNarrow->setGeometry(QRect(10, 60, 151, 51));
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
        toolButtonBroad = new QToolButton(frame_7);
        toolButtonBroad->setObjectName("toolButtonBroad");
        toolButtonBroad->setGeometry(QRect(10, 0, 151, 51));
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
        stackedWidget = new QStackedWidget(frame_3);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(250, 10, 341, 141));
        Broad = new QWidget();
        Broad->setObjectName("Broad");
        spinBoxLengthB = new QSpinBox(Broad);
        spinBoxLengthB->setObjectName("spinBoxLengthB");
        spinBoxLengthB->setGeometry(QRect(210, 102, 111, 36));
        spinBoxLengthB->setFont(font);
        spinBoxLengthB->setMaximum(99999999);
        spinBoxLengthB->setValue(2000);
        labelK_3 = new QLabel(Broad);
        labelK_3->setObjectName("labelK_3");
        labelK_3->setGeometry(QRect(40, 10, 141, 31));
        labelK_3->setFont(font3);
        labelK_3->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthB = new QSlider(Broad);
        horizontalSliderLengthB->setObjectName("horizontalSliderLengthB");
        horizontalSliderLengthB->setGeometry(QRect(10, 100, 191, 51));
        horizontalSliderLengthB->setMaximum(10000);
        horizontalSliderLengthB->setOrientation(Qt::Horizontal);
        horizontalSliderSizeB = new QSlider(Broad);
        horizontalSliderSizeB->setObjectName("horizontalSliderSizeB");
        horizontalSliderSizeB->setGeometry(QRect(10, 30, 191, 51));
        horizontalSliderSizeB->setMaximum(10000);
        horizontalSliderSizeB->setOrientation(Qt::Horizontal);
        labelK_10 = new QLabel(Broad);
        labelK_10->setObjectName("labelK_10");
        labelK_10->setGeometry(QRect(40, 80, 141, 31));
        labelK_10->setFont(font3);
        labelK_10->setAlignment(Qt::AlignCenter);
        doubleSpinBoxSizeBMM = new QDoubleSpinBox(Broad);
        doubleSpinBoxSizeBMM->setObjectName("doubleSpinBoxSizeBMM");
        doubleSpinBoxSizeBMM->setGeometry(QRect(210, 0, 111, 36));
        doubleSpinBoxSizeBMM->setFont(font);
        doubleSpinBoxSizeBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeBMM->setValue(0.500000000000000);
        spinBoxSizeB = new QSpinBox(Broad);
        spinBoxSizeB->setObjectName("spinBoxSizeB");
        spinBoxSizeB->setGeometry(QRect(210, 32, 111, 36));
        spinBoxSizeB->setFont(font);
        spinBoxSizeB->setMaximum(99999999);
        spinBoxSizeB->setValue(2000);
        doubleSpinBoxLengthBMM = new QDoubleSpinBox(Broad);
        doubleSpinBoxLengthBMM->setObjectName("doubleSpinBoxLengthBMM");
        doubleSpinBoxLengthBMM->setGeometry(QRect(210, 70, 111, 36));
        doubleSpinBoxLengthBMM->setFont(font);
        doubleSpinBoxLengthBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthBMM->setValue(0.500000000000000);
        stackedWidget->addWidget(Broad);
        Narrow = new QWidget();
        Narrow->setObjectName("Narrow");
        labelK_37 = new QLabel(Narrow);
        labelK_37->setObjectName("labelK_37");
        labelK_37->setGeometry(QRect(40, 10, 141, 31));
        labelK_37->setFont(font3);
        labelK_37->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthN = new QSlider(Narrow);
        horizontalSliderLengthN->setObjectName("horizontalSliderLengthN");
        horizontalSliderLengthN->setGeometry(QRect(10, 100, 191, 51));
        horizontalSliderLengthN->setMaximum(10000);
        horizontalSliderLengthN->setOrientation(Qt::Horizontal);
        horizontalSliderSizeN = new QSlider(Narrow);
        horizontalSliderSizeN->setObjectName("horizontalSliderSizeN");
        horizontalSliderSizeN->setGeometry(QRect(10, 30, 191, 51));
        horizontalSliderSizeN->setMaximum(10000);
        horizontalSliderSizeN->setOrientation(Qt::Horizontal);
        spinBoxLengthN = new QSpinBox(Narrow);
        spinBoxLengthN->setObjectName("spinBoxLengthN");
        spinBoxLengthN->setGeometry(QRect(210, 102, 111, 36));
        spinBoxLengthN->setFont(font);
        spinBoxLengthN->setMaximum(99999999);
        spinBoxLengthN->setValue(2000);
        labelK_38 = new QLabel(Narrow);
        labelK_38->setObjectName("labelK_38");
        labelK_38->setGeometry(QRect(40, 80, 141, 31));
        labelK_38->setFont(font3);
        labelK_38->setAlignment(Qt::AlignCenter);
        doubleSpinBoxSizeNMM = new QDoubleSpinBox(Narrow);
        doubleSpinBoxSizeNMM->setObjectName("doubleSpinBoxSizeNMM");
        doubleSpinBoxSizeNMM->setGeometry(QRect(210, 0, 111, 36));
        doubleSpinBoxSizeNMM->setFont(font);
        doubleSpinBoxSizeNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeNMM->setValue(0.500000000000000);
        spinBoxSizeN = new QSpinBox(Narrow);
        spinBoxSizeN->setObjectName("spinBoxSizeN");
        spinBoxSizeN->setGeometry(QRect(210, 32, 111, 36));
        spinBoxSizeN->setFont(font);
        spinBoxSizeN->setMaximum(99999999);
        spinBoxSizeN->setValue(2000);
        doubleSpinBoxLengthNMM = new QDoubleSpinBox(Narrow);
        doubleSpinBoxLengthNMM->setObjectName("doubleSpinBoxLengthNMM");
        doubleSpinBoxLengthNMM->setGeometry(QRect(210, 70, 111, 36));
        doubleSpinBoxLengthNMM->setFont(font);
        doubleSpinBoxLengthNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthNMM->setValue(0.500000000000000);
        stackedWidget->addWidget(Narrow);
        frame_6 = new QFrame(EachThresholdWholeForm);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 380, 661, 141));
        frame_6->setFrameShape(QFrame::Panel);
        frame_6->setFrameShadow(QFrame::Sunken);
        labelK_22 = new QLabel(frame_6);
        labelK_22->setObjectName("labelK_22");
        labelK_22->setGeometry(QRect(580, 40, 81, 36));
        labelK_22->setFont(font1);
        labelK_22->setAlignment(Qt::AlignCenter);
        horizontalSliderSIze = new QSlider(frame_6);
        horizontalSliderSIze->setObjectName("horizontalSliderSIze");
        horizontalSliderSIze->setGeometry(QRect(210, 20, 241, 51));
        horizontalSliderSIze->setOrientation(Qt::Horizontal);
        doubleSpinBoxMultiSizeMM = new QDoubleSpinBox(frame_6);
        doubleSpinBoxMultiSizeMM->setObjectName("doubleSpinBoxMultiSizeMM");
        doubleSpinBoxMultiSizeMM->setGeometry(QRect(460, 10, 111, 36));
        doubleSpinBoxMultiSizeMM->setFont(font);
        doubleSpinBoxMultiSizeMM->setMaximum(10000.000000000000000);
        doubleSpinBoxMultiSizeMM->setValue(0.500000000000000);
        labelK_23 = new QLabel(frame_6);
        labelK_23->setObjectName("labelK_23");
        labelK_23->setGeometry(QRect(580, 10, 71, 36));
        labelK_23->setFont(font2);
        labelK_23->setAlignment(Qt::AlignCenter);
        spinBoxMultiSize = new QSpinBox(frame_6);
        spinBoxMultiSize->setObjectName("spinBoxMultiSize");
        spinBoxMultiSize->setGeometry(QRect(460, 42, 111, 36));
        spinBoxMultiSize->setFont(font);
        spinBoxMultiSize->setMaximum(99999999);
        spinBoxMultiSize->setValue(2000);
        horizontalSliderNGCount = new QSlider(frame_6);
        horizontalSliderNGCount->setObjectName("horizontalSliderNGCount");
        horizontalSliderNGCount->setGeometry(QRect(210, 80, 241, 51));
        horizontalSliderNGCount->setOrientation(Qt::Horizontal);
        labelK_25 = new QLabel(frame_6);
        labelK_25->setObjectName("labelK_25");
        labelK_25->setGeometry(QRect(580, 90, 41, 41));
        labelK_25->setFont(font1);
        labelK_25->setAlignment(Qt::AlignCenter);
        spinBoxMultiNGCount = new QSpinBox(frame_6);
        spinBoxMultiNGCount->setObjectName("spinBoxMultiNGCount");
        spinBoxMultiNGCount->setGeometry(QRect(460, 90, 111, 41));
        spinBoxMultiNGCount->setFont(font);
        spinBoxMultiNGCount->setMaximum(99999999);
        spinBoxMultiNGCount->setValue(2000);
        labelK_26 = new QLabel(frame_6);
        labelK_26->setObjectName("labelK_26");
        labelK_26->setGeometry(QRect(60, 20, 141, 41));
        labelK_26->setFont(font2);
        labelK_26->setFrameShape(QFrame::NoFrame);
        labelK_26->setFrameShadow(QFrame::Sunken);
        labelK_26->setAlignment(Qt::AlignCenter);
        labelK_27 = new QLabel(frame_6);
        labelK_27->setObjectName("labelK_27");
        labelK_27->setGeometry(QRect(60, 80, 141, 41));
        labelK_27->setFont(font2);
        labelK_27->setFrameShape(QFrame::NoFrame);
        labelK_27->setFrameShadow(QFrame::Sunken);
        labelK_27->setAlignment(Qt::AlignCenter);
        labelK_28 = new QLabel(frame_6);
        labelK_28->setObjectName("labelK_28");
        labelK_28->setGeometry(QRect(0, 0, 41, 141));
        labelK_28->setFont(font2);
        labelK_28->setFrameShape(QFrame::Panel);
        labelK_28->setFrameShadow(QFrame::Sunken);
        labelK_28->setAlignment(Qt::AlignCenter);
        labelK_30 = new QLabel(EachThresholdWholeForm);
        labelK_30->setObjectName("labelK_30");
        labelK_30->setGeometry(QRect(30, 790, 71, 241));
        labelK_30->setFont(font3);
        labelK_30->setAlignment(Qt::AlignCenter);
        frameThresholdLevel = new QFrame(EachThresholdWholeForm);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(10, 10, 381, 111));
        frameThresholdLevel->setFrameShape(QFrame::Panel);
        frameThresholdLevel->setFrameShadow(QFrame::Sunken);
        labelK_16 = new QLabel(frameThresholdLevel);
        labelK_16->setObjectName("labelK_16");
        labelK_16->setGeometry(QRect(0, 0, 371, 31));
        labelK_16->setFont(font2);
        labelK_16->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(EachThresholdWholeForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(110, 790, 521, 251));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        labelK_11 = new QLabel(frame_2);
        labelK_11->setObjectName("labelK_11");
        labelK_11->setGeometry(QRect(10, 40, 241, 51));
        labelK_11->setFont(font3);
        labelK_11->setAlignment(Qt::AlignCenter);
        labelK_14 = new QLabel(frame_2);
        labelK_14->setObjectName("labelK_14");
        labelK_14->setGeometry(QRect(10, 110, 241, 51));
        labelK_14->setFont(font3);
        labelK_14->setAlignment(Qt::AlignCenter);
        labelK_15 = new QLabel(frame_2);
        labelK_15->setObjectName("labelK_15");
        labelK_15->setGeometry(QRect(10, 180, 241, 51));
        labelK_15->setFont(font3);
        labelK_15->setAlignment(Qt::AlignCenter);
        toolButtonBrightnessDarkStrict = new QToolButton(frame_2);
        toolButtonBrightnessDarkStrict->setObjectName("toolButtonBrightnessDarkStrict");
        toolButtonBrightnessDarkStrict->setGeometry(QRect(440, 40, 65, 64));
        QFont font4;
        font4.setPointSize(12);
        toolButtonBrightnessDarkStrict->setFont(font4);
        toolButtonBrightnessLightStrict = new QToolButton(frame_2);
        toolButtonBrightnessLightStrict->setObjectName("toolButtonBrightnessLightStrict");
        toolButtonBrightnessLightStrict->setGeometry(QRect(440, 110, 65, 64));
        toolButtonBrightnessLightStrict->setFont(font4);
        toolButtonShiftStrict = new QToolButton(frame_2);
        toolButtonShiftStrict->setObjectName("toolButtonShiftStrict");
        toolButtonShiftStrict->setGeometry(QRect(440, 180, 65, 64));
        toolButtonShiftStrict->setFont(font4);
        labelK_12 = new QLabel(frame_2);
        labelK_12->setObjectName("labelK_12");
        labelK_12->setGeometry(QRect(420, 0, 101, 41));
        labelK_12->setFont(font3);
        labelK_12->setAlignment(Qt::AlignCenter);
        spinBoxBrightnessDark = new QSpinBox(frame_2);
        spinBoxBrightnessDark->setObjectName("spinBoxBrightnessDark");
        spinBoxBrightnessDark->setGeometry(QRect(353, 40, 71, 61));
        QFont font5;
        font5.setPointSize(20);
        spinBoxBrightnessDark->setFont(font5);
        spinBoxBrightnessDark->setFrame(true);
        spinBoxBrightnessDark->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxBrightnessDark->setMinimum(-10);
        spinBoxBrightnessDark->setMaximum(10);
        spinBoxBrightnessLight = new QSpinBox(frame_2);
        spinBoxBrightnessLight->setObjectName("spinBoxBrightnessLight");
        spinBoxBrightnessLight->setGeometry(QRect(353, 110, 71, 61));
        spinBoxBrightnessLight->setFont(font5);
        spinBoxBrightnessLight->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxBrightnessLight->setMinimum(-10);
        spinBoxBrightnessLight->setMaximum(10);
        spinBoxShift = new QSpinBox(frame_2);
        spinBoxShift->setObjectName("spinBoxShift");
        spinBoxShift->setGeometry(QRect(353, 180, 71, 61));
        spinBoxShift->setFont(font5);
        spinBoxShift->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxShift->setMinimum(-10);
        spinBoxShift->setMaximum(10);
        toolButtonShiftLoose = new QToolButton(frame_2);
        toolButtonShiftLoose->setObjectName("toolButtonShiftLoose");
        toolButtonShiftLoose->setGeometry(QRect(270, 180, 65, 64));
        toolButtonShiftLoose->setFont(font4);
        labelK_13 = new QLabel(frame_2);
        labelK_13->setObjectName("labelK_13");
        labelK_13->setGeometry(QRect(250, 0, 101, 41));
        labelK_13->setFont(font3);
        labelK_13->setAlignment(Qt::AlignCenter);
        toolButtonBrightnessLightLoose = new QToolButton(frame_2);
        toolButtonBrightnessLightLoose->setObjectName("toolButtonBrightnessLightLoose");
        toolButtonBrightnessLightLoose->setGeometry(QRect(270, 110, 65, 64));
        toolButtonBrightnessLightLoose->setFont(font4);
        toolButtonBrightnessDarkStrictLoose = new QToolButton(frame_2);
        toolButtonBrightnessDarkStrictLoose->setObjectName("toolButtonBrightnessDarkStrictLoose");
        toolButtonBrightnessDarkStrictLoose->setGeometry(QRect(270, 40, 65, 64));
        toolButtonBrightnessDarkStrictLoose->setFont(font4);
        frame_5 = new QFrame(EachThresholdWholeForm);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 290, 661, 81));
        frame_5->setFrameShape(QFrame::Panel);
        frame_5->setFrameShadow(QFrame::Sunken);
        labelK_17 = new QLabel(frame_5);
        labelK_17->setObjectName("labelK_17");
        labelK_17->setGeometry(QRect(580, 40, 81, 36));
        labelK_17->setFont(font1);
        labelK_17->setAlignment(Qt::AlignCenter);
        horizontalSliderRedOKDot = new QSlider(frame_5);
        horizontalSliderRedOKDot->setObjectName("horizontalSliderRedOKDot");
        horizontalSliderRedOKDot->setGeometry(QRect(210, 20, 241, 51));
        horizontalSliderRedOKDot->setMaximum(10000);
        horizontalSliderRedOKDot->setOrientation(Qt::Horizontal);
        doubleSpinBoxRedOKDotMM = new QDoubleSpinBox(frame_5);
        doubleSpinBoxRedOKDotMM->setObjectName("doubleSpinBoxRedOKDotMM");
        doubleSpinBoxRedOKDotMM->setGeometry(QRect(460, 10, 111, 36));
        doubleSpinBoxRedOKDotMM->setFont(font);
        doubleSpinBoxRedOKDotMM->setMaximum(10000.000000000000000);
        doubleSpinBoxRedOKDotMM->setValue(0.500000000000000);
        labelK_18 = new QLabel(frame_5);
        labelK_18->setObjectName("labelK_18");
        labelK_18->setGeometry(QRect(580, 10, 61, 36));
        labelK_18->setFont(font2);
        labelK_18->setAlignment(Qt::AlignCenter);
        labelK_19 = new QLabel(frame_5);
        labelK_19->setObjectName("labelK_19");
        labelK_19->setGeometry(QRect(50, 20, 161, 51));
        labelK_19->setFont(font3);
        labelK_19->setAlignment(Qt::AlignCenter);
        spinBoxRedOKDot = new QSpinBox(frame_5);
        spinBoxRedOKDot->setObjectName("spinBoxRedOKDot");
        spinBoxRedOKDot->setGeometry(QRect(460, 42, 111, 36));
        spinBoxRedOKDot->setFont(font);
        spinBoxRedOKDot->setMaximum(99999999);
        spinBoxRedOKDot->setValue(2000);
        labelK_21 = new QLabel(frame_5);
        labelK_21->setObjectName("labelK_21");
        labelK_21->setGeometry(QRect(0, 0, 41, 81));
        labelK_21->setFont(font2);
        labelK_21->setFrameShape(QFrame::Panel);
        labelK_21->setFrameShadow(QFrame::Sunken);
        labelK_21->setAlignment(Qt::AlignCenter);
        toolButtonClose = new QToolButton(EachThresholdWholeForm);
        toolButtonClose->setObjectName("toolButtonClose");
        toolButtonClose->setGeometry(QRect(1350, 960, 241, 81));
        toolButtonClose->setFont(font);
        toolButtonClose->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        frameImagePanel = new QFrame(EachThresholdWholeForm);
        frameImagePanel->setObjectName("frameImagePanel");
        frameImagePanel->setGeometry(QRect(690, 10, 711, 931));
        frameImagePanel->setFrameShape(QFrame::Panel);
        frameImagePanel->setFrameShadow(QFrame::Sunken);
        labelK_24 = new QLabel(EachThresholdWholeForm);
        labelK_24->setObjectName("labelK_24");
        labelK_24->setGeometry(QRect(400, 10, 261, 31));
        labelK_24->setFont(font2);
        labelK_24->setAlignment(Qt::AlignCenter);
        spinBoxLibID = new QSpinBox(EachThresholdWholeForm);
        spinBoxLibID->setObjectName("spinBoxLibID");
        spinBoxLibID->setGeometry(QRect(400, 50, 71, 36));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        spinBoxLibID->setPalette(palette);
        spinBoxLibID->setFont(font2);
        spinBoxLibID->setFrame(true);
        spinBoxLibID->setReadOnly(true);
        spinBoxLibID->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxLibID->setMinimum(0);
        spinBoxLibID->setMaximum(100000000);
        lineEditLibName = new QLineEdit(EachThresholdWholeForm);
        lineEditLibName->setObjectName("lineEditLibName");
        lineEditLibName->setGeometry(QRect(400, 90, 271, 36));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditLibName->setPalette(palette1);
        lineEditLibName->setFont(font4);
        lineEditLibName->setReadOnly(true);
        toolButtonEnable = new QToolButton(EachThresholdWholeForm);
        toolButtonEnable->setObjectName("toolButtonEnable");
        toolButtonEnable->setGeometry(QRect(660, 960, 201, 81));
        toolButtonEnable->setFont(font5);
        toolButtonEnable->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 0, 0, 255), stop:1 rgba(130, 0, 0, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonEnable->setCheckable(true);
        toolButtonEnable->setChecked(true);
        toolButtonEnable->setAutoExclusive(true);
        listWidgetOperationHistory = new QListWidget(EachThresholdWholeForm);
        listWidgetOperationHistory->setObjectName("listWidgetOperationHistory");
        listWidgetOperationHistory->setGeometry(QRect(1410, 10, 181, 931));

        retranslateUi(EachThresholdWholeForm);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EachThresholdWholeForm);
    } // setupUi

    void retranslateUi(QWidget *EachThresholdWholeForm)
    {
        EachThresholdWholeForm->setWindowTitle(QCoreApplication::translate("EachThresholdWholeForm", "Form", nullptr));
        toolButtonOKSize->setText(QCoreApplication::translate("EachThresholdWholeForm", "\350\250\255\345\256\232", nullptr));
        labelK_6->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_8->setText(QCoreApplication::translate("EachThresholdWholeForm", "mm", nullptr));
        labelK_29->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\201\253\343\201\230\343\201\277\351\207\217", nullptr));
        labelK_31->setText(QCoreApplication::translate("EachThresholdWholeForm", "mm", nullptr));
        labelK_32->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_33->setText(QCoreApplication::translate("EachThresholdWholeForm", "\351\240\230\345\237\237\346\216\242\347\264\242\351\207\217X", nullptr));
        labelK_34->setText(QCoreApplication::translate("EachThresholdWholeForm", "mm", nullptr));
        labelK_35->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_36->setText(QCoreApplication::translate("EachThresholdWholeForm", "\351\240\230\345\237\237\346\216\242\347\264\242\351\207\217Y", nullptr));
        labelK_5->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_4->setText(QCoreApplication::translate("EachThresholdWholeForm", "mm2", nullptr));
        labelK_7->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_9->setText(QCoreApplication::translate("EachThresholdWholeForm", "mm", nullptr));
        labelK_20->setText(QCoreApplication::translate("EachThresholdWholeForm", "<html><head/><body><p>\351\200\232</p><p>\345\270\270</p><p>\345\210\244</p><p>\345\256\232</p></body></html>", nullptr));
        toolButtonNarrow->setText(QCoreApplication::translate("EachThresholdWholeForm", "\347\213\255\345\237\237", nullptr));
        toolButtonBroad->setText(QCoreApplication::translate("EachThresholdWholeForm", "\345\272\203\345\237\237\357\274\217\344\270\200\350\210\254", nullptr));
        labelK_3->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_10->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
        labelK_37->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_38->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
        labelK_22->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_23->setText(QCoreApplication::translate("EachThresholdWholeForm", "mm2", nullptr));
        labelK_25->setText(QCoreApplication::translate("EachThresholdWholeForm", "\345\200\213", nullptr));
        labelK_26->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_27->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\234\200\345\260\217\345\200\213\346\225\260", nullptr));
        labelK_28->setText(QCoreApplication::translate("EachThresholdWholeForm", "<html><head/><body><p>\345\244\232</p><p>\347\202\271</p><p>\346\244\234</p><p>\346\237\273</p></body></html>", nullptr));
        labelK_30->setText(QCoreApplication::translate("EachThresholdWholeForm", "<html><head/><body><p>\346\204\237</p><p>\345\272\246</p><p>\345\276\256</p><p>\350\252\277</p><p>\346\225\264</p></body></html>", nullptr));
        labelK_16->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\203\254\343\203\231\343\203\253\347\242\272\350\252\215\357\274\217\350\250\255\345\256\232", nullptr));
        labelK_11->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\232\227\343\201\204\351\203\250\345\210\206\343\201\256\346\277\203\346\267\241", nullptr));
        labelK_14->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\230\216\343\202\213\343\201\204\351\203\250\345\210\206\343\201\256\346\277\203\346\267\241", nullptr));
        labelK_15->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\202\272\343\203\254\350\250\261\345\256\271", nullptr));
        toolButtonBrightnessDarkStrict->setText(QCoreApplication::translate("EachThresholdWholeForm", "\342\226\262", nullptr));
        toolButtonBrightnessLightStrict->setText(QCoreApplication::translate("EachThresholdWholeForm", "\342\226\262", nullptr));
        toolButtonShiftStrict->setText(QCoreApplication::translate("EachThresholdWholeForm", "\342\226\262", nullptr));
        labelK_12->setText(QCoreApplication::translate("EachThresholdWholeForm", "\345\216\263\343\201\227\343\201\204", nullptr));
        toolButtonShiftLoose->setText(QCoreApplication::translate("EachThresholdWholeForm", "\342\226\274", nullptr));
        labelK_13->setText(QCoreApplication::translate("EachThresholdWholeForm", "\347\267\251\343\201\204", nullptr));
        toolButtonBrightnessLightLoose->setText(QCoreApplication::translate("EachThresholdWholeForm", "\342\226\274", nullptr));
        toolButtonBrightnessDarkStrictLoose->setText(QCoreApplication::translate("EachThresholdWholeForm", "\342\226\274", nullptr));
        labelK_17->setText(QCoreApplication::translate("EachThresholdWholeForm", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_18->setText(QCoreApplication::translate("EachThresholdWholeForm", "mm2", nullptr));
        labelK_19->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_21->setText(QCoreApplication::translate("EachThresholdWholeForm", "<html><head/><body><p>\350\265\244</p><p>\350\211\262</p></body></html>", nullptr));
        toolButtonClose->setText(QCoreApplication::translate("EachThresholdWholeForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        labelK_24->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\244\234\346\237\273\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        toolButtonEnable->setText(QCoreApplication::translate("EachThresholdWholeForm", "\346\244\234\346\237\273\346\234\211\345\212\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EachThresholdWholeForm: public Ui_EachThresholdWholeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EACHTHRESHOLDWHOLEFORM_H
