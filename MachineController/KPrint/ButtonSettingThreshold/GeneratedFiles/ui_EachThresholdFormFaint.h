/********************************************************************************
** Form generated from reading UI file 'EachThresholdFormFaint.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EACHTHRESHOLDFORMFAINT_H
#define UI_EACHTHRESHOLDFORMFAINT_H

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

class Ui_EachThresholdFormFaint
{
public:
    QPushButton *PushButtonMarker;
    QFrame *frameMarkerImage;
    QLabel *label;
    QFrame *frame_4;
    QLabel *labelK_2;
    QLabel *labelK;
    QFrame *frame;
    QLabel *labelK_6;
    QToolButton *toolButtonPickColor;
    QToolButton *toolButtonDrawColor;
    QToolButton *toolButtonDelColor;
    QToolButton *toolButtonAddColor;
    QFrame *frame_5;
    QToolButton *toolButtonNarrow;
    QToolButton *toolButtonBroad;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QSpinBox *spinBoxK;
    QSlider *verticalSliderY;
    QFrame *frameMapCMY;
    QFrame *frameMapK;
    QWidget *page_2;
    QSlider *verticalSliderY_2;
    QSpinBox *spinBoxK_2;
    QFrame *frameMapCMY_2;
    QFrame *frameMapK_2;
    QFrame *frameThresholdLevel;
    QLabel *labelK_8;
    QToolButton *toolButtonOK;
    QToolButton *toolButtonCancel;
    QPushButton *PushButtonShowWhole;
    QToolButton *toolButtonRegOK;
    QToolButton *toolButtonRegNG;
    QToolButton *toolButtonOKSize;
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
    QStackedWidget *stackedWidget_2;
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
    QLabel *labelK_7;
    QLabel *labelK_9;
    QSlider *horizontalSliderLengthB;
    QLabel *labelK_10;
    QWidget *Narrow;
    QFrame *frame_6;
    QLabel *labelK_16;
    QSlider *horizontalSliderSizeN;
    QDoubleSpinBox *doubleSpinBoxSizeNMM;
    QLabel *labelK_17;
    QLabel *labelK_18;
    QSpinBox *spinBoxSizeN;
    QSpinBox *spinBoxLengthN;
    QDoubleSpinBox *doubleSpinBoxLengthNMM;
    QLabel *labelK_19;
    QLabel *labelK_20;
    QSlider *horizontalSliderLengthN;
    QLabel *labelK_21;

    void setupUi(QWidget *EachThresholdFormFaint)
    {
        if (EachThresholdFormFaint->objectName().isEmpty())
            EachThresholdFormFaint->setObjectName("EachThresholdFormFaint");
        EachThresholdFormFaint->resize(1159, 1050);
        EachThresholdFormFaint->setAcceptDrops(false);
        PushButtonMarker = new QPushButton(EachThresholdFormFaint);
        PushButtonMarker->setObjectName("PushButtonMarker");
        PushButtonMarker->setGeometry(QRect(580, 10, 241, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font.setPointSize(24);
        PushButtonMarker->setFont(font);
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
        frameMarkerImage = new QFrame(EachThresholdFormFaint);
        frameMarkerImage->setObjectName("frameMarkerImage");
        frameMarkerImage->setGeometry(QRect(580, 103, 571, 541));
        frameMarkerImage->setFrameShape(QFrame::StyledPanel);
        frameMarkerImage->setFrameShadow(QFrame::Raised);
        label = new QLabel(EachThresholdFormFaint);
        label->setObjectName("label");
        label->setGeometry(QRect(580, 70, 571, 31));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        frame_4 = new QFrame(EachThresholdFormFaint);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 124, 551, 521));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        labelK_2 = new QLabel(frame_4);
        labelK_2->setObjectName("labelK_2");
        labelK_2->setGeometry(QRect(10, 460, 181, 51));
        QFont font2;
        font2.setPointSize(18);
        labelK_2->setFont(font2);
        labelK_2->setAlignment(Qt::AlignCenter);
        labelK = new QLabel(frame_4);
        labelK->setObjectName("labelK");
        labelK->setGeometry(QRect(450, 50, 61, 20));
        labelK->setFont(font1);
        labelK->setAlignment(Qt::AlignCenter);
        frame = new QFrame(frame_4);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(200, 423, 251, 111));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        labelK_6 = new QLabel(frame_4);
        labelK_6->setObjectName("labelK_6");
        labelK_6->setGeometry(QRect(10, 400, 181, 51));
        labelK_6->setFont(font2);
        labelK_6->setAlignment(Qt::AlignCenter);
        toolButtonPickColor = new QToolButton(frame_4);
        toolButtonPickColor->setObjectName("toolButtonPickColor");
        toolButtonPickColor->setGeometry(QRect(430, 404, 111, 51));
        QFont font3;
        font3.setPointSize(20);
        toolButtonPickColor->setFont(font3);
        toolButtonPickColor->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonPickColor->setCheckable(false);
        toolButtonPickColor->setChecked(false);
        toolButtonPickColor->setAutoExclusive(false);
        toolButtonDrawColor = new QToolButton(frame_4);
        toolButtonDrawColor->setObjectName("toolButtonDrawColor");
        toolButtonDrawColor->setGeometry(QRect(200, 403, 201, 51));
        toolButtonDrawColor->setFont(font3);
        toolButtonDrawColor->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonDrawColor->setCheckable(true);
        toolButtonDrawColor->setChecked(true);
        toolButtonDrawColor->setAutoExclusive(true);
        toolButtonDelColor = new QToolButton(frame_4);
        toolButtonDelColor->setObjectName("toolButtonDelColor");
        toolButtonDelColor->setGeometry(QRect(330, 463, 121, 51));
        toolButtonDelColor->setFont(font3);
        toolButtonDelColor->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 230, 230, 255), stop:1 rgba(165, 130, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonDelColor->setCheckable(true);
        toolButtonDelColor->setAutoExclusive(true);
        toolButtonAddColor = new QToolButton(frame_4);
        toolButtonAddColor->setObjectName("toolButtonAddColor");
        toolButtonAddColor->setGeometry(QRect(200, 463, 121, 51));
        toolButtonAddColor->setFont(font3);
        toolButtonAddColor->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonAddColor->setCheckable(true);
        toolButtonAddColor->setChecked(false);
        toolButtonAddColor->setAutoExclusive(true);
        frame_5 = new QFrame(frame_4);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(50, 10, 401, 71));
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Raised);
        toolButtonNarrow = new QToolButton(frame_5);
        toolButtonNarrow->setObjectName("toolButtonNarrow");
        toolButtonNarrow->setGeometry(QRect(210, 0, 181, 61));
        QFont font4;
        font4.setPointSize(16);
        toolButtonNarrow->setFont(font4);
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
        toolButtonBroad->setGeometry(QRect(10, 0, 191, 61));
        toolButtonBroad->setFont(font4);
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
        stackedWidget = new QStackedWidget(frame_4);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(120, 80, 431, 311));
        page = new QWidget();
        page->setObjectName("page");
        spinBoxK = new QSpinBox(page);
        spinBoxK->setObjectName("spinBoxK");
        spinBoxK->setGeometry(QRect(330, 270, 81, 41));
        spinBoxK->setFont(font4);
        spinBoxK->setMaximum(255);
        spinBoxK->setValue(128);
        verticalSliderY = new QSlider(page);
        verticalSliderY->setObjectName("verticalSliderY");
        verticalSliderY->setGeometry(QRect(341, 3, 41, 251));
        verticalSliderY->setMaximum(255);
        verticalSliderY->setValue(128);
        verticalSliderY->setOrientation(Qt::Vertical);
        frameMapCMY = new QFrame(page);
        frameMapCMY->setObjectName("frameMapCMY");
        frameMapCMY->setGeometry(QRect(0, 0, 311, 311));
        frameMapCMY->setFrameShape(QFrame::StyledPanel);
        frameMapCMY->setFrameShadow(QFrame::Raised);
        frameMapK = new QFrame(page);
        frameMapK->setObjectName("frameMapK");
        frameMapK->setGeometry(QRect(390, 0, 31, 261));
        frameMapK->setFrameShape(QFrame::StyledPanel);
        frameMapK->setFrameShadow(QFrame::Raised);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalSliderY_2 = new QSlider(page_2);
        verticalSliderY_2->setObjectName("verticalSliderY_2");
        verticalSliderY_2->setGeometry(QRect(341, 3, 41, 251));
        verticalSliderY_2->setMaximum(255);
        verticalSliderY_2->setValue(128);
        verticalSliderY_2->setOrientation(Qt::Vertical);
        spinBoxK_2 = new QSpinBox(page_2);
        spinBoxK_2->setObjectName("spinBoxK_2");
        spinBoxK_2->setGeometry(QRect(330, 270, 81, 41));
        spinBoxK_2->setFont(font4);
        spinBoxK_2->setMaximum(255);
        spinBoxK_2->setValue(128);
        frameMapCMY_2 = new QFrame(page_2);
        frameMapCMY_2->setObjectName("frameMapCMY_2");
        frameMapCMY_2->setGeometry(QRect(0, 0, 311, 311));
        frameMapCMY_2->setFrameShape(QFrame::StyledPanel);
        frameMapCMY_2->setFrameShadow(QFrame::Raised);
        frameMapK_2 = new QFrame(page_2);
        frameMapK_2->setObjectName("frameMapK_2");
        frameMapK_2->setGeometry(QRect(390, 0, 31, 261));
        frameMapK_2->setFrameShape(QFrame::StyledPanel);
        frameMapK_2->setFrameShadow(QFrame::Raised);
        stackedWidget->addWidget(page_2);
        frameThresholdLevel = new QFrame(EachThresholdFormFaint);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(10, 0, 551, 121));
        frameThresholdLevel->setFrameShape(QFrame::Panel);
        frameThresholdLevel->setFrameShadow(QFrame::Sunken);
        labelK_8 = new QLabel(frameThresholdLevel);
        labelK_8->setObjectName("labelK_8");
        labelK_8->setGeometry(QRect(0, 0, 551, 31));
        QFont font5;
        font5.setPointSize(14);
        labelK_8->setFont(font5);
        labelK_8->setAlignment(Qt::AlignCenter);
        toolButtonOK = new QToolButton(EachThresholdFormFaint);
        toolButtonOK->setObjectName("toolButtonOK");
        toolButtonOK->setGeometry(QRect(20, 860, 481, 81));
        toolButtonOK->setFont(font4);
        toolButtonOK->setAcceptDrops(false);
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
        toolButtonCancel = new QToolButton(EachThresholdFormFaint);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(990, 950, 161, 81));
        toolButtonCancel->setFont(font4);
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
        PushButtonShowWhole = new QPushButton(EachThresholdFormFaint);
        PushButtonShowWhole->setObjectName("PushButtonShowWhole");
        PushButtonShowWhole->setGeometry(QRect(840, 10, 261, 51));
        PushButtonShowWhole->setFont(font);
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
        toolButtonRegOK = new QToolButton(EachThresholdFormFaint);
        toolButtonRegOK->setObjectName("toolButtonRegOK");
        toolButtonRegOK->setGeometry(QRect(600, 950, 161, 81));
        toolButtonRegOK->setFont(font4);
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
        toolButtonRegNG = new QToolButton(EachThresholdFormFaint);
        toolButtonRegNG->setObjectName("toolButtonRegNG");
        toolButtonRegNG->setGeometry(QRect(780, 950, 161, 81));
        toolButtonRegNG->setFont(font4);
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
        toolButtonOKSize = new QToolButton(EachThresholdFormFaint);
        toolButtonOKSize->setObjectName("toolButtonOKSize");
        toolButtonOKSize->setGeometry(QRect(20, 950, 481, 81));
        toolButtonOKSize->setFont(font4);
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
        frame_2 = new QFrame(EachThresholdFormFaint);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(630, 650, 521, 271));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        labelK_11 = new QLabel(frame_2);
        labelK_11->setObjectName("labelK_11");
        labelK_11->setGeometry(QRect(10, 60, 241, 51));
        labelK_11->setFont(font2);
        labelK_11->setAlignment(Qt::AlignCenter);
        labelK_14 = new QLabel(frame_2);
        labelK_14->setObjectName("labelK_14");
        labelK_14->setGeometry(QRect(10, 130, 241, 51));
        labelK_14->setFont(font2);
        labelK_14->setAlignment(Qt::AlignCenter);
        labelK_15 = new QLabel(frame_2);
        labelK_15->setObjectName("labelK_15");
        labelK_15->setGeometry(QRect(10, 200, 241, 51));
        labelK_15->setFont(font2);
        labelK_15->setAlignment(Qt::AlignCenter);
        toolButtonBrightnessDarkStrict = new QToolButton(frame_2);
        toolButtonBrightnessDarkStrict->setObjectName("toolButtonBrightnessDarkStrict");
        toolButtonBrightnessDarkStrict->setGeometry(QRect(440, 60, 65, 64));
        toolButtonBrightnessDarkStrict->setFont(font1);
        toolButtonBrightnessLightStrict = new QToolButton(frame_2);
        toolButtonBrightnessLightStrict->setObjectName("toolButtonBrightnessLightStrict");
        toolButtonBrightnessLightStrict->setGeometry(QRect(440, 130, 65, 64));
        toolButtonBrightnessLightStrict->setFont(font1);
        toolButtonShiftStrict = new QToolButton(frame_2);
        toolButtonShiftStrict->setObjectName("toolButtonShiftStrict");
        toolButtonShiftStrict->setGeometry(QRect(440, 200, 65, 64));
        toolButtonShiftStrict->setFont(font1);
        labelK_12 = new QLabel(frame_2);
        labelK_12->setObjectName("labelK_12");
        labelK_12->setGeometry(QRect(420, 0, 101, 51));
        labelK_12->setFont(font2);
        labelK_12->setAlignment(Qt::AlignCenter);
        spinBoxBrightnessDark = new QSpinBox(frame_2);
        spinBoxBrightnessDark->setObjectName("spinBoxBrightnessDark");
        spinBoxBrightnessDark->setGeometry(QRect(353, 60, 71, 61));
        spinBoxBrightnessDark->setFont(font3);
        spinBoxBrightnessDark->setFrame(true);
        spinBoxBrightnessDark->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxBrightnessDark->setMinimum(-10);
        spinBoxBrightnessDark->setMaximum(10);
        spinBoxBrightnessLight = new QSpinBox(frame_2);
        spinBoxBrightnessLight->setObjectName("spinBoxBrightnessLight");
        spinBoxBrightnessLight->setGeometry(QRect(353, 130, 71, 61));
        spinBoxBrightnessLight->setFont(font3);
        spinBoxBrightnessLight->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxBrightnessLight->setMinimum(-10);
        spinBoxBrightnessLight->setMaximum(10);
        spinBoxShift = new QSpinBox(frame_2);
        spinBoxShift->setObjectName("spinBoxShift");
        spinBoxShift->setGeometry(QRect(353, 200, 71, 61));
        spinBoxShift->setFont(font3);
        spinBoxShift->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxShift->setMinimum(-10);
        spinBoxShift->setMaximum(10);
        toolButtonShiftLoose = new QToolButton(frame_2);
        toolButtonShiftLoose->setObjectName("toolButtonShiftLoose");
        toolButtonShiftLoose->setGeometry(QRect(270, 200, 65, 64));
        toolButtonShiftLoose->setFont(font1);
        labelK_13 = new QLabel(frame_2);
        labelK_13->setObjectName("labelK_13");
        labelK_13->setGeometry(QRect(250, 0, 101, 51));
        labelK_13->setFont(font2);
        labelK_13->setAlignment(Qt::AlignCenter);
        toolButtonBrightnessLightLoose = new QToolButton(frame_2);
        toolButtonBrightnessLightLoose->setObjectName("toolButtonBrightnessLightLoose");
        toolButtonBrightnessLightLoose->setGeometry(QRect(270, 130, 65, 64));
        toolButtonBrightnessLightLoose->setFont(font1);
        toolButtonBrightnessDarkStrictLoose = new QToolButton(frame_2);
        toolButtonBrightnessDarkStrictLoose->setObjectName("toolButtonBrightnessDarkStrictLoose");
        toolButtonBrightnessDarkStrictLoose->setGeometry(QRect(270, 60, 65, 64));
        toolButtonBrightnessDarkStrictLoose->setFont(font1);
        stackedWidget_2 = new QStackedWidget(EachThresholdFormFaint);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setGeometry(QRect(0, 650, 621, 201));
        Broad = new QWidget();
        Broad->setObjectName("Broad");
        frame_3 = new QFrame(Broad);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 10, 611, 181));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        labelK_5 = new QLabel(frame_3);
        labelK_5->setObjectName("labelK_5");
        labelK_5->setGeometry(QRect(530, 50, 71, 36));
        QFont font6;
        font6.setPointSize(11);
        labelK_5->setFont(font6);
        labelK_5->setAlignment(Qt::AlignCenter);
        horizontalSliderSizeB = new QSlider(frame_3);
        horizontalSliderSizeB->setObjectName("horizontalSliderSizeB");
        horizontalSliderSizeB->setGeometry(QRect(160, 20, 241, 51));
        horizontalSliderSizeB->setMaximum(10000);
        horizontalSliderSizeB->setOrientation(Qt::Horizontal);
        doubleSpinBoxSizeBMM = new QDoubleSpinBox(frame_3);
        doubleSpinBoxSizeBMM->setObjectName("doubleSpinBoxSizeBMM");
        doubleSpinBoxSizeBMM->setGeometry(QRect(410, 10, 111, 36));
        doubleSpinBoxSizeBMM->setFont(font4);
        doubleSpinBoxSizeBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeBMM->setValue(0.500000000000000);
        labelK_4 = new QLabel(frame_3);
        labelK_4->setObjectName("labelK_4");
        labelK_4->setGeometry(QRect(530, 10, 61, 36));
        labelK_4->setFont(font5);
        labelK_4->setAlignment(Qt::AlignCenter);
        labelK_3 = new QLabel(frame_3);
        labelK_3->setObjectName("labelK_3");
        labelK_3->setGeometry(QRect(10, 20, 141, 51));
        labelK_3->setFont(font2);
        labelK_3->setAlignment(Qt::AlignCenter);
        spinBoxSizeB = new QSpinBox(frame_3);
        spinBoxSizeB->setObjectName("spinBoxSizeB");
        spinBoxSizeB->setGeometry(QRect(410, 50, 111, 36));
        spinBoxSizeB->setFont(font4);
        spinBoxSizeB->setMaximum(99999999);
        spinBoxSizeB->setValue(2000);
        spinBoxLengthB = new QSpinBox(frame_3);
        spinBoxLengthB->setObjectName("spinBoxLengthB");
        spinBoxLengthB->setGeometry(QRect(410, 130, 111, 36));
        spinBoxLengthB->setFont(font4);
        spinBoxLengthB->setMaximum(99999999);
        spinBoxLengthB->setValue(2000);
        doubleSpinBoxLengthBMM = new QDoubleSpinBox(frame_3);
        doubleSpinBoxLengthBMM->setObjectName("doubleSpinBoxLengthBMM");
        doubleSpinBoxLengthBMM->setGeometry(QRect(410, 90, 111, 36));
        doubleSpinBoxLengthBMM->setFont(font4);
        doubleSpinBoxLengthBMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthBMM->setValue(0.500000000000000);
        labelK_7 = new QLabel(frame_3);
        labelK_7->setObjectName("labelK_7");
        labelK_7->setGeometry(QRect(530, 130, 71, 36));
        labelK_7->setFont(font6);
        labelK_7->setAlignment(Qt::AlignCenter);
        labelK_9 = new QLabel(frame_3);
        labelK_9->setObjectName("labelK_9");
        labelK_9->setGeometry(QRect(530, 90, 61, 36));
        labelK_9->setFont(font5);
        labelK_9->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthB = new QSlider(frame_3);
        horizontalSliderLengthB->setObjectName("horizontalSliderLengthB");
        horizontalSliderLengthB->setGeometry(QRect(160, 100, 241, 51));
        horizontalSliderLengthB->setMaximum(10000);
        horizontalSliderLengthB->setOrientation(Qt::Horizontal);
        labelK_10 = new QLabel(frame_3);
        labelK_10->setObjectName("labelK_10");
        labelK_10->setGeometry(QRect(10, 100, 141, 51));
        labelK_10->setFont(font2);
        labelK_10->setAlignment(Qt::AlignCenter);
        stackedWidget_2->addWidget(Broad);
        Narrow = new QWidget();
        Narrow->setObjectName("Narrow");
        frame_6 = new QFrame(Narrow);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 10, 611, 181));
        frame_6->setFrameShape(QFrame::Panel);
        frame_6->setFrameShadow(QFrame::Sunken);
        labelK_16 = new QLabel(frame_6);
        labelK_16->setObjectName("labelK_16");
        labelK_16->setGeometry(QRect(530, 50, 71, 36));
        labelK_16->setFont(font6);
        labelK_16->setAlignment(Qt::AlignCenter);
        horizontalSliderSizeN = new QSlider(frame_6);
        horizontalSliderSizeN->setObjectName("horizontalSliderSizeN");
        horizontalSliderSizeN->setGeometry(QRect(160, 20, 241, 51));
        horizontalSliderSizeN->setMaximum(10000);
        horizontalSliderSizeN->setOrientation(Qt::Horizontal);
        doubleSpinBoxSizeNMM = new QDoubleSpinBox(frame_6);
        doubleSpinBoxSizeNMM->setObjectName("doubleSpinBoxSizeNMM");
        doubleSpinBoxSizeNMM->setGeometry(QRect(410, 10, 111, 36));
        doubleSpinBoxSizeNMM->setFont(font4);
        doubleSpinBoxSizeNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxSizeNMM->setValue(0.500000000000000);
        labelK_17 = new QLabel(frame_6);
        labelK_17->setObjectName("labelK_17");
        labelK_17->setGeometry(QRect(530, 10, 61, 36));
        labelK_17->setFont(font5);
        labelK_17->setAlignment(Qt::AlignCenter);
        labelK_18 = new QLabel(frame_6);
        labelK_18->setObjectName("labelK_18");
        labelK_18->setGeometry(QRect(10, 20, 141, 51));
        labelK_18->setFont(font2);
        labelK_18->setAlignment(Qt::AlignCenter);
        spinBoxSizeN = new QSpinBox(frame_6);
        spinBoxSizeN->setObjectName("spinBoxSizeN");
        spinBoxSizeN->setGeometry(QRect(410, 50, 111, 36));
        spinBoxSizeN->setFont(font4);
        spinBoxSizeN->setMaximum(99999999);
        spinBoxSizeN->setValue(2000);
        spinBoxLengthN = new QSpinBox(frame_6);
        spinBoxLengthN->setObjectName("spinBoxLengthN");
        spinBoxLengthN->setGeometry(QRect(410, 130, 111, 36));
        spinBoxLengthN->setFont(font4);
        spinBoxLengthN->setMaximum(99999999);
        spinBoxLengthN->setValue(2000);
        doubleSpinBoxLengthNMM = new QDoubleSpinBox(frame_6);
        doubleSpinBoxLengthNMM->setObjectName("doubleSpinBoxLengthNMM");
        doubleSpinBoxLengthNMM->setGeometry(QRect(410, 90, 111, 36));
        doubleSpinBoxLengthNMM->setFont(font4);
        doubleSpinBoxLengthNMM->setMaximum(10000.000000000000000);
        doubleSpinBoxLengthNMM->setValue(0.500000000000000);
        labelK_19 = new QLabel(frame_6);
        labelK_19->setObjectName("labelK_19");
        labelK_19->setGeometry(QRect(530, 130, 71, 36));
        labelK_19->setFont(font6);
        labelK_19->setAlignment(Qt::AlignCenter);
        labelK_20 = new QLabel(frame_6);
        labelK_20->setObjectName("labelK_20");
        labelK_20->setGeometry(QRect(530, 90, 61, 36));
        labelK_20->setFont(font5);
        labelK_20->setAlignment(Qt::AlignCenter);
        horizontalSliderLengthN = new QSlider(frame_6);
        horizontalSliderLengthN->setObjectName("horizontalSliderLengthN");
        horizontalSliderLengthN->setGeometry(QRect(160, 100, 241, 51));
        horizontalSliderLengthN->setMaximum(10000);
        horizontalSliderLengthN->setOrientation(Qt::Horizontal);
        labelK_21 = new QLabel(frame_6);
        labelK_21->setObjectName("labelK_21");
        labelK_21->setGeometry(QRect(10, 100, 141, 51));
        labelK_21->setFont(font2);
        labelK_21->setAlignment(Qt::AlignCenter);
        stackedWidget_2->addWidget(Narrow);

        retranslateUi(EachThresholdFormFaint);

        PushButtonMarker->setDefault(false);
        stackedWidget->setCurrentIndex(1);
        PushButtonShowWhole->setDefault(false);
        stackedWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EachThresholdFormFaint);
    } // setupUi

    void retranslateUi(QWidget *EachThresholdFormFaint)
    {
        EachThresholdFormFaint->setWindowTitle(QCoreApplication::translate("EachThresholdFormFaint", "Setting", nullptr));
        PushButtonMarker->setText(QCoreApplication::translate("EachThresholdFormFaint", "\343\203\236\343\203\274\343\202\253\343\203\274", nullptr));
        label->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        labelK_2->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\244\234\345\207\272\350\211\262\344\277\256\346\255\243", nullptr));
        labelK->setText(QCoreApplication::translate("EachThresholdFormFaint", "Y", nullptr));
        labelK_6->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\214\207\345\256\232\350\211\262\346\217\217\347\224\273", nullptr));
        toolButtonPickColor->setText(QCoreApplication::translate("EachThresholdFormFaint", "<=", nullptr));
        toolButtonDrawColor->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\217\217\347\224\273", nullptr));
        toolButtonDelColor->setText(QCoreApplication::translate("EachThresholdFormFaint", "\345\211\212\351\231\244", nullptr));
        toolButtonAddColor->setText(QCoreApplication::translate("EachThresholdFormFaint", "\350\277\275\345\212\240", nullptr));
        toolButtonNarrow->setText(QCoreApplication::translate("EachThresholdFormFaint", "\347\213\255\345\237\237", nullptr));
        toolButtonBroad->setText(QCoreApplication::translate("EachThresholdFormFaint", "\345\272\203\345\237\237\357\274\217\344\270\200\350\210\254", nullptr));
        labelK_8->setText(QCoreApplication::translate("EachThresholdFormFaint", "\343\203\254\343\203\231\343\203\253\347\242\272\350\252\215\357\274\217\350\250\255\345\256\232", nullptr));
        toolButtonOK->setText(QCoreApplication::translate("EachThresholdFormFaint", "\350\211\262\347\257\204\345\233\262\343\200\201\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272\343\202\222\350\250\255\345\256\232", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("EachThresholdFormFaint", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        PushButtonShowWhole->setText(QCoreApplication::translate("EachThresholdFormFaint", "\345\205\250\344\275\223\350\241\250\347\244\272", nullptr));
        toolButtonRegOK->setText(QCoreApplication::translate("EachThresholdFormFaint", "OK\347\231\273\351\214\262", nullptr));
        toolButtonRegNG->setText(QCoreApplication::translate("EachThresholdFormFaint", "NG\347\231\273\351\214\262", nullptr));
        toolButtonOKSize->setText(QCoreApplication::translate("EachThresholdFormFaint", "\343\202\265\343\202\244\343\202\272\343\201\256\343\201\277\343\202\222\350\250\255\345\256\232", nullptr));
        labelK_11->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\232\227\343\201\204\351\203\250\345\210\206\343\201\256\346\277\203\346\267\241", nullptr));
        labelK_14->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\230\216\343\202\213\343\201\204\351\203\250\345\210\206\343\201\256\346\277\203\346\267\241", nullptr));
        labelK_15->setText(QCoreApplication::translate("EachThresholdFormFaint", "\343\202\272\343\203\254\350\250\261\345\256\271", nullptr));
        toolButtonBrightnessDarkStrict->setText(QCoreApplication::translate("EachThresholdFormFaint", "\342\226\262", nullptr));
        toolButtonBrightnessLightStrict->setText(QCoreApplication::translate("EachThresholdFormFaint", "\342\226\262", nullptr));
        toolButtonShiftStrict->setText(QCoreApplication::translate("EachThresholdFormFaint", "\342\226\262", nullptr));
        labelK_12->setText(QCoreApplication::translate("EachThresholdFormFaint", "\345\216\263\343\201\227\343\201\204", nullptr));
        toolButtonShiftLoose->setText(QCoreApplication::translate("EachThresholdFormFaint", "\342\226\274", nullptr));
        labelK_13->setText(QCoreApplication::translate("EachThresholdFormFaint", "\347\267\251\343\201\204", nullptr));
        toolButtonBrightnessLightLoose->setText(QCoreApplication::translate("EachThresholdFormFaint", "\342\226\274", nullptr));
        toolButtonBrightnessDarkStrictLoose->setText(QCoreApplication::translate("EachThresholdFormFaint", "\342\226\274", nullptr));
        labelK_5->setText(QCoreApplication::translate("EachThresholdFormFaint", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_4->setText(QCoreApplication::translate("EachThresholdFormFaint", "mm2", nullptr));
        labelK_3->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_7->setText(QCoreApplication::translate("EachThresholdFormFaint", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_9->setText(QCoreApplication::translate("EachThresholdFormFaint", "mm", nullptr));
        labelK_10->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
        labelK_16->setText(QCoreApplication::translate("EachThresholdFormFaint", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_17->setText(QCoreApplication::translate("EachThresholdFormFaint", "mm2", nullptr));
        labelK_18->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\244\234\345\207\272\351\235\242\347\251\215", nullptr));
        labelK_19->setText(QCoreApplication::translate("EachThresholdFormFaint", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        labelK_20->setText(QCoreApplication::translate("EachThresholdFormFaint", "mm", nullptr));
        labelK_21->setText(QCoreApplication::translate("EachThresholdFormFaint", "\346\244\234\345\207\272\351\225\267\343\201\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EachThresholdFormFaint: public Ui_EachThresholdFormFaint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EACHTHRESHOLDFORMFAINT_H
