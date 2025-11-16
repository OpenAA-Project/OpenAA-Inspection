/********************************************************************************
** Form generated from reading UI file 'EachThresholdFormBlade.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EACHTHRESHOLDFORMBLADE_H
#define UI_EACHTHRESHOLDFORMBLADE_H

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

class Ui_EachThresholdFormBlade
{
public:
    QToolButton *toolButtonCancel;
    QToolButton *toolButtonOKSize;
    QToolButton *toolButtonSet;
    QLabel *label;
    QFrame *frameMarkerImage;
    QPushButton *PushButtonShowWhole;
    QPushButton *PushButtonMarker;
    QFrame *frameThresholdLevel;
    QLabel *labelK_8;
    QStackedWidget *stackedWidget;
    QWidget *Broad;
    QLabel *labelK_12;
    QDoubleSpinBox *doubleSpinBoxLengthBMM;
    QDoubleSpinBox *doubleSpinBoxSizeBMM;
    QLabel *labelK_3;
    QSlider *horizontalSliderLengthB;
    QSpinBox *spinBoxLengthB;
    QSlider *horizontalSliderSizeB;
    QFrame *frame_4;
    QLabel *labelK_6;
    QSpinBox *spinBoxBRL;
    QSpinBox *spinBoxBRH;
    QSlider *horizontalSliderBRH;
    QSlider *horizontalSliderBRL;
    QLabel *labelK_10;
    QLabel *labelK_11;
    QLabel *labelK_14;
    QLabel *labelK_4;
    QSpinBox *spinBoxSizeB;
    QLabel *labelK_5;
    QLabel *labelK_13;
    QWidget *Narrow;
    QDoubleSpinBox *doubleSpinBoxLengthNMM;
    QDoubleSpinBox *doubleSpinBoxSizeNMM;
    QLabel *labelK_7;
    QSlider *horizontalSliderLengthN;
    QSpinBox *spinBoxLengthN;
    QSlider *horizontalSliderSizeN;
    QLabel *labelK_17;
    QFrame *frame_5;
    QLabel *labelK_9;
    QLabel *labelK_19;
    QLabel *labelK_20;
    QSlider *horizontalSliderNRH;
    QSpinBox *spinBoxNRH;
    QSpinBox *spinBoxNRL;
    QSlider *horizontalSliderNRL;
    QLabel *labelK_21;
    QLabel *labelK_22;
    QSpinBox *spinBoxSizeN;
    QLabel *labelK_23;
    QLabel *labelK_24;
    QFrame *frame_6;
    QToolButton *toolButtonNarrow;
    QToolButton *toolButtonBroad;

    void setupUi(QWidget *EachThresholdFormBlade)
    {
        if (EachThresholdFormBlade->objectName().isEmpty())
            EachThresholdFormBlade->setObjectName("EachThresholdFormBlade");
        EachThresholdFormBlade->resize(1285, 819);
        toolButtonCancel = new QToolButton(EachThresholdFormBlade);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(540, 730, 161, 81));
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
        toolButtonOKSize = new QToolButton(EachThresholdFormBlade);
        toolButtonOKSize->setObjectName("toolButtonOKSize");
        toolButtonOKSize->setGeometry(QRect(30, 730, 481, 81));
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
        toolButtonSet = new QToolButton(EachThresholdFormBlade);
        toolButtonSet->setObjectName("toolButtonSet");
        toolButtonSet->setGeometry(QRect(30, 640, 481, 81));
        toolButtonSet->setFont(font);
        toolButtonSet->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        label = new QLabel(EachThresholdFormBlade);
        label->setObjectName("label");
        label->setGeometry(QRect(710, 80, 561, 31));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        frameMarkerImage = new QFrame(EachThresholdFormBlade);
        frameMarkerImage->setObjectName("frameMarkerImage");
        frameMarkerImage->setGeometry(QRect(710, 110, 561, 701));
        frameMarkerImage->setFrameShape(QFrame::StyledPanel);
        frameMarkerImage->setFrameShadow(QFrame::Raised);
        PushButtonShowWhole = new QPushButton(EachThresholdFormBlade);
        PushButtonShowWhole->setObjectName("PushButtonShowWhole");
        PushButtonShowWhole->setGeometry(QRect(1000, 10, 261, 51));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font2.setPointSize(24);
        PushButtonShowWhole->setFont(font2);
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
        PushButtonMarker = new QPushButton(EachThresholdFormBlade);
        PushButtonMarker->setObjectName("PushButtonMarker");
        PushButtonMarker->setGeometry(QRect(730, 10, 261, 51));
        PushButtonMarker->setFont(font2);
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
        frameThresholdLevel = new QFrame(EachThresholdFormBlade);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(10, 0, 551, 151));
        frameThresholdLevel->setFrameShape(QFrame::Panel);
        frameThresholdLevel->setFrameShadow(QFrame::Sunken);
        labelK_8 = new QLabel(frameThresholdLevel);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(0, 0, 551, 31));
        QFont font3;
        font3.setPointSize(14);
        labelK_8->setFont(font3);
        labelK_8->setAlignment(Qt::AlignCenter);
        stackedWidget = new QStackedWidget(EachThresholdFormBlade);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 280, 691, 341));
        Broad = new QWidget();
        Broad->setObjectName("Broad");
        labelK_12 = new QLabel(Broad);
        labelK_12->setObjectName("labelK_12");
        labelK_12->setGeometry(QRect(600, 290, 81, 36));
        QFont font4;
        font4.setPointSize(11);
        labelK_12->setFont(font4);
        labelK_12->setAlignment(Qt::AlignCenter);
        doubleSpinBoxLengthBMM = new QDoubleSpinBox(Broad);
        doubleSpinBoxLengthBMM->setObjectName("doubleSpinBoxLengthBMM");
        doubleSpinBoxLengthBMM->setGeometry(QRect(480, 250, 111, 36));
        doubleSpinBoxLengthBMM->setFont(font);
        doubleSpinBoxLengthBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthBMM->setValue(0.500000000000000);
        doubleSpinBoxSizeBMM = new QDoubleSpinBox(Broad);
        doubleSpinBoxSizeBMM->setObjectName("doubleSpinBoxSizeBMM");
        doubleSpinBoxSizeBMM->setGeometry(QRect(480, 160, 111, 36));
        doubleSpinBoxSizeBMM->setFont(font);
        doubleSpinBoxSizeBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeBMM->setValue(0.500000000000000);
        labelK_3 = new QLabel(Broad);
        labelK_3->setObjectName("labelK_3");
        labelK_3->setGeometry(QRect(10, 170, 181, 51));
        QFont font5;
        font5.setPointSize(18);
        labelK_3->setFont(font5);
        labelK_3->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthB = new QSlider(Broad);
        horizontalSliderLengthB->setObjectName("horizontalSliderLengthB");
        horizontalSliderLengthB->setGeometry(QRect(200, 260, 261, 51));
        horizontalSliderLengthB->setMaximum(10000);
        horizontalSliderLengthB->setOrientation(Qt::Horizontal);
        spinBoxLengthB = new QSpinBox(Broad);
        spinBoxLengthB->setObjectName("spinBoxLengthB");
        spinBoxLengthB->setGeometry(QRect(480, 290, 111, 36));
        spinBoxLengthB->setFont(font);
        spinBoxLengthB->setMaximum(99999999);
        spinBoxLengthB->setValue(2000);
        horizontalSliderSizeB = new QSlider(Broad);
        horizontalSliderSizeB->setObjectName("horizontalSliderSizeB");
        horizontalSliderSizeB->setGeometry(QRect(200, 170, 261, 51));
        horizontalSliderSizeB->setMaximum(10000);
        horizontalSliderSizeB->setOrientation(Qt::Horizontal);
        frame_4 = new QFrame(Broad);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(0, 0, 671, 151));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        labelK_6 = new QLabel(frame_4);
        labelK_6->setObjectName("labelK_6");
        labelK_6->setGeometry(QRect(0, 0, 441, 51));
        labelK_6->setFont(font5);
        labelK_6->setAlignment(Qt::AlignCenter);
        spinBoxBRL = new QSpinBox(frame_4);
        spinBoxBRL->setObjectName("spinBoxBRL");
        spinBoxBRL->setGeometry(QRect(240, 90, 81, 31));
        spinBoxBRL->setFont(font1);
        spinBoxBRL->setMinimum(-100);
        spinBoxBRL->setMaximum(100);
        spinBoxBRL->setValue(10);
        spinBoxBRH = new QSpinBox(frame_4);
        spinBoxBRH->setObjectName("spinBoxBRH");
        spinBoxBRH->setGeometry(QRect(560, 90, 81, 31));
        spinBoxBRH->setFont(font1);
        spinBoxBRH->setMinimum(-100);
        spinBoxBRH->setMaximum(100);
        spinBoxBRH->setValue(10);
        horizontalSliderBRH = new QSlider(frame_4);
        horizontalSliderBRH->setObjectName("horizontalSliderBRH");
        horizontalSliderBRH->setGeometry(QRect(360, 80, 181, 41));
        horizontalSliderBRH->setMinimum(-100);
        horizontalSliderBRH->setMaximum(100);
        horizontalSliderBRH->setOrientation(Qt::Horizontal);
        horizontalSliderBRL = new QSlider(frame_4);
        horizontalSliderBRL->setObjectName("horizontalSliderBRL");
        horizontalSliderBRL->setGeometry(QRect(50, 80, 181, 41));
        horizontalSliderBRL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderBRL->setMinimum(-100);
        horizontalSliderBRL->setMaximum(100);
        horizontalSliderBRL->setOrientation(Qt::Horizontal);
        labelK_10 = new QLabel(frame_4);
        labelK_10->setObjectName("labelK_10");
        labelK_10->setGeometry(QRect(60, 60, 151, 31));
        labelK_10->setFont(font3);
        labelK_10->setAlignment(Qt::AlignCenter);
        labelK_11 = new QLabel(frame_4);
        labelK_11->setObjectName("labelK_11");
        labelK_11->setGeometry(QRect(370, 60, 151, 31));
        labelK_11->setFont(font3);
        labelK_11->setAlignment(Qt::AlignCenter);
        labelK_14 = new QLabel(Broad);
        labelK_14->setObjectName("labelK_14");
        labelK_14->setGeometry(QRect(10, 260, 181, 51));
        labelK_14->setFont(font5);
        labelK_14->setAlignment(Qt::AlignCenter);
        labelK_4 = new QLabel(Broad);
        labelK_4->setObjectName("labelK_4");
        labelK_4->setGeometry(QRect(600, 160, 61, 36));
        labelK_4->setFont(font3);
        labelK_4->setAlignment(Qt::AlignCenter);
        spinBoxSizeB = new QSpinBox(Broad);
        spinBoxSizeB->setObjectName("spinBoxSizeB");
        spinBoxSizeB->setGeometry(QRect(480, 200, 111, 36));
        spinBoxSizeB->setFont(font);
        spinBoxSizeB->setMaximum(99999999);
        spinBoxSizeB->setValue(2000);
        labelK_5 = new QLabel(Broad);
        labelK_5->setObjectName("labelK_5");
        labelK_5->setGeometry(QRect(600, 200, 81, 36));
        labelK_5->setFont(font4);
        labelK_5->setAlignment(Qt::AlignCenter);
        labelK_13 = new QLabel(Broad);
        labelK_13->setObjectName("labelK_13");
        labelK_13->setGeometry(QRect(600, 250, 61, 36));
        labelK_13->setFont(font3);
        labelK_13->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(Broad);
        Narrow = new QWidget();
        Narrow->setObjectName("Narrow");
        doubleSpinBoxLengthNMM = new QDoubleSpinBox(Narrow);
        doubleSpinBoxLengthNMM->setObjectName("doubleSpinBoxLengthNMM");
        doubleSpinBoxLengthNMM->setGeometry(QRect(480, 250, 111, 36));
        doubleSpinBoxLengthNMM->setFont(font);
        doubleSpinBoxLengthNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthNMM->setValue(0.500000000000000);
        doubleSpinBoxSizeNMM = new QDoubleSpinBox(Narrow);
        doubleSpinBoxSizeNMM->setObjectName("doubleSpinBoxSizeNMM");
        doubleSpinBoxSizeNMM->setGeometry(QRect(480, 160, 111, 36));
        doubleSpinBoxSizeNMM->setFont(font);
        doubleSpinBoxSizeNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeNMM->setValue(0.500000000000000);
        labelK_7 = new QLabel(Narrow);
        labelK_7->setObjectName("labelK_7");
        labelK_7->setGeometry(QRect(10, 170, 181, 51));
        labelK_7->setFont(font5);
        labelK_7->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthN = new QSlider(Narrow);
        horizontalSliderLengthN->setObjectName("horizontalSliderLengthN");
        horizontalSliderLengthN->setGeometry(QRect(200, 260, 261, 51));
        horizontalSliderLengthN->setMaximum(10000);
        horizontalSliderLengthN->setOrientation(Qt::Horizontal);
        spinBoxLengthN = new QSpinBox(Narrow);
        spinBoxLengthN->setObjectName("spinBoxLengthN");
        spinBoxLengthN->setGeometry(QRect(480, 290, 111, 36));
        spinBoxLengthN->setFont(font);
        spinBoxLengthN->setMaximum(99999999);
        spinBoxLengthN->setValue(2000);
        horizontalSliderSizeN = new QSlider(Narrow);
        horizontalSliderSizeN->setObjectName("horizontalSliderSizeN");
        horizontalSliderSizeN->setGeometry(QRect(200, 170, 261, 51));
        horizontalSliderSizeN->setMaximum(10000);
        horizontalSliderSizeN->setOrientation(Qt::Horizontal);
        labelK_17 = new QLabel(Narrow);
        labelK_17->setObjectName("labelK_17");
        labelK_17->setGeometry(QRect(600, 290, 81, 36));
        labelK_17->setFont(font4);
        labelK_17->setAlignment(Qt::AlignCenter);
        frame_5 = new QFrame(Narrow);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(0, 0, 671, 151));
        frame_5->setFrameShape(QFrame::Panel);
        frame_5->setFrameShadow(QFrame::Sunken);
        labelK_9 = new QLabel(frame_5);
        labelK_9->setObjectName("labelK_9");
        labelK_9->setGeometry(QRect(0, 0, 441, 51));
        labelK_9->setFont(font5);
        labelK_9->setAlignment(Qt::AlignCenter);
        labelK_19 = new QLabel(frame_5);
        labelK_19->setObjectName("labelK_19");
        labelK_19->setGeometry(QRect(60, 60, 151, 31));
        labelK_19->setFont(font3);
        labelK_19->setAlignment(Qt::AlignCenter);
        labelK_20 = new QLabel(frame_5);
        labelK_20->setObjectName("labelK_20");
        labelK_20->setGeometry(QRect(370, 60, 151, 31));
        labelK_20->setFont(font3);
        labelK_20->setAlignment(Qt::AlignCenter);
        horizontalSliderNRH = new QSlider(frame_5);
        horizontalSliderNRH->setObjectName("horizontalSliderNRH");
        horizontalSliderNRH->setGeometry(QRect(350, 80, 181, 41));
        horizontalSliderNRH->setMinimum(-100);
        horizontalSliderNRH->setMaximum(100);
        horizontalSliderNRH->setOrientation(Qt::Horizontal);
        spinBoxNRH = new QSpinBox(frame_5);
        spinBoxNRH->setObjectName("spinBoxNRH");
        spinBoxNRH->setGeometry(QRect(550, 90, 81, 31));
        spinBoxNRH->setFont(font1);
        spinBoxNRH->setMinimum(-100);
        spinBoxNRH->setMaximum(100);
        spinBoxNRH->setValue(10);
        spinBoxNRL = new QSpinBox(frame_5);
        spinBoxNRL->setObjectName("spinBoxNRL");
        spinBoxNRL->setGeometry(QRect(230, 90, 81, 31));
        spinBoxNRL->setFont(font1);
        spinBoxNRL->setMinimum(-100);
        spinBoxNRL->setMaximum(100);
        spinBoxNRL->setValue(10);
        horizontalSliderNRL = new QSlider(frame_5);
        horizontalSliderNRL->setObjectName("horizontalSliderNRL");
        horizontalSliderNRL->setGeometry(QRect(40, 80, 181, 41));
        horizontalSliderNRL->setLayoutDirection(Qt::RightToLeft);
        horizontalSliderNRL->setMinimum(-100);
        horizontalSliderNRL->setMaximum(100);
        horizontalSliderNRL->setOrientation(Qt::Horizontal);
        labelK_21 = new QLabel(Narrow);
        labelK_21->setObjectName("labelK_21");
        labelK_21->setGeometry(QRect(10, 260, 181, 51));
        labelK_21->setFont(font5);
        labelK_21->setAlignment(Qt::AlignCenter);
        labelK_22 = new QLabel(Narrow);
        labelK_22->setObjectName("labelK_22");
        labelK_22->setGeometry(QRect(600, 160, 61, 36));
        labelK_22->setFont(font3);
        labelK_22->setAlignment(Qt::AlignCenter);
        spinBoxSizeN = new QSpinBox(Narrow);
        spinBoxSizeN->setObjectName("spinBoxSizeN");
        spinBoxSizeN->setGeometry(QRect(480, 200, 111, 36));
        spinBoxSizeN->setFont(font);
        spinBoxSizeN->setMaximum(99999999);
        spinBoxSizeN->setValue(2000);
        labelK_23 = new QLabel(Narrow);
        labelK_23->setObjectName("labelK_23");
        labelK_23->setGeometry(QRect(600, 200, 81, 36));
        labelK_23->setFont(font4);
        labelK_23->setAlignment(Qt::AlignCenter);
        labelK_24 = new QLabel(Narrow);
        labelK_24->setObjectName("labelK_24");
        labelK_24->setGeometry(QRect(600, 250, 61, 36));
        labelK_24->setFont(font3);
        labelK_24->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(Narrow);
        frame_6 = new QFrame(EachThresholdFormBlade);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(120, 200, 401, 71));
        frame_6->setFrameShape(QFrame::NoFrame);
        frame_6->setFrameShadow(QFrame::Raised);
        toolButtonNarrow = new QToolButton(frame_6);
        toolButtonNarrow->setObjectName("toolButtonNarrow");
        toolButtonNarrow->setGeometry(QRect(210, 0, 181, 61));
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
        toolButtonBroad = new QToolButton(frame_6);
        toolButtonBroad->setObjectName("toolButtonBroad");
        toolButtonBroad->setGeometry(QRect(10, 0, 191, 61));
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

        retranslateUi(EachThresholdFormBlade);

        PushButtonShowWhole->setDefault(false);
        PushButtonMarker->setDefault(false);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EachThresholdFormBlade);
    } // setupUi

    void retranslateUi(QWidget *EachThresholdFormBlade)
    {
        EachThresholdFormBlade->setWindowTitle(QCoreApplication::translate("EachThresholdFormBlade", "Setting", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("EachThresholdFormBlade", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        toolButtonOKSize->setText(QCoreApplication::translate("EachThresholdFormBlade", "\343\202\265\343\202\244\343\202\272\343\201\256\343\201\277\343\202\222\350\250\255\345\256\232", nullptr));
        toolButtonSet->setText(QCoreApplication::translate("EachThresholdFormBlade", "\350\211\262\347\257\204\345\233\262\343\200\201\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272\343\202\222\350\250\255\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("EachThresholdFormBlade", "\343\203\236\343\203\274\343\202\253\343\203\274\347\256\207\346\211\200", nullptr));
        PushButtonShowWhole->setText(QCoreApplication::translate("EachThresholdFormBlade", "\345\205\250\344\275\223\350\241\250\347\244\272", nullptr));
        PushButtonMarker->setText(QCoreApplication::translate("EachThresholdFormBlade", "\343\203\236\343\203\274\343\202\253\343\203\274", nullptr));
        labelK_8->setText(QCoreApplication::translate("EachThresholdFormBlade", "\343\203\254\343\203\231\343\203\253\347\242\272\350\252\215\357\274\217\350\250\255\345\256\232", nullptr));
        labelK_12->setText(QCoreApplication::translate("EachThresholdFormBlade", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_3->setText(QCoreApplication::translate("EachThresholdFormBlade", "\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272", nullptr));
        labelK_6->setText(QCoreApplication::translate("EachThresholdFormBlade", "\350\274\235\345\272\246\345\244\211\345\214\226\343\201\256\346\244\234\345\207\272", nullptr));
        labelK_10->setText(QCoreApplication::translate("EachThresholdFormBlade", "\346\232\227\345\201\264", nullptr));
        labelK_11->setText(QCoreApplication::translate("EachThresholdFormBlade", "\346\230\216\345\201\264", nullptr));
        labelK_14->setText(QCoreApplication::translate("EachThresholdFormBlade", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
        labelK_4->setText(QCoreApplication::translate("EachThresholdFormBlade", "mm2", nullptr));
        labelK_5->setText(QCoreApplication::translate("EachThresholdFormBlade", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_13->setText(QCoreApplication::translate("EachThresholdFormBlade", "mm", nullptr));
        labelK_7->setText(QCoreApplication::translate("EachThresholdFormBlade", "\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272", nullptr));
        labelK_17->setText(QCoreApplication::translate("EachThresholdFormBlade", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_9->setText(QCoreApplication::translate("EachThresholdFormBlade", "\350\274\235\345\272\246\345\244\211\345\214\226\343\201\256\346\244\234\345\207\272", nullptr));
        labelK_19->setText(QCoreApplication::translate("EachThresholdFormBlade", "\346\232\227\345\201\264", nullptr));
        labelK_20->setText(QCoreApplication::translate("EachThresholdFormBlade", "\346\230\216\345\201\264", nullptr));
        labelK_21->setText(QCoreApplication::translate("EachThresholdFormBlade", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
        labelK_22->setText(QCoreApplication::translate("EachThresholdFormBlade", "mm2", nullptr));
        labelK_23->setText(QCoreApplication::translate("EachThresholdFormBlade", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_24->setText(QCoreApplication::translate("EachThresholdFormBlade", "mm", nullptr));
        toolButtonNarrow->setText(QCoreApplication::translate("EachThresholdFormBlade", "\347\213\255\345\237\237", nullptr));
        toolButtonBroad->setText(QCoreApplication::translate("EachThresholdFormBlade", "\345\272\203\345\237\237\357\274\217\344\270\200\350\210\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EachThresholdFormBlade: public Ui_EachThresholdFormBlade {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EACHTHRESHOLDFORMBLADE_H
