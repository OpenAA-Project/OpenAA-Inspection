/********************************************************************************
** Form generated from reading UI file 'CartonMenuForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARTONMENUFORM_H
#define UI_CARTONMENUFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_CartonMenuForm
{
public:
    QSlider *horizontalSliderLevel;
    QLabel *label_Level;
    QFrame *frame;
    QPushButton *PushButtonRun;
    QPushButton *pushButtonSetLevel;
    QLabel *label_Level2;
    QSlider *horizontalSliderLevel2;
    QLabel *label_Level_3;
    QLabel *label_Level_4;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *PushButtonAutoGenerate;
    QPushButton *PushButtonInspection;
    QPushButton *PushButtonBlade;
    QPushButton *PushButtonSwitchPhase;
    QPushButton *PushButtonMask;
    QPushButton *PushButtonAlignment;
    QPushButton *PushButtonSetting;
    QPushButton *PushButtonThresholdTop;
    QPushButton *PushButtonThresholdBottom;
    QPushButton *PushButtonLotList2;
    QWidget *page_2;
    QPushButton *PushButtonEachSetting;
    QPushButton *PushButtonLotList;
    QPushButton *PushButtonOther;
    QStackedWidget *stackedWidgetDetail;
    QWidget *Camera2;
    QPushButton *PushButtonBottomDetail;
    QPushButton *PushButtonTopDetail;
    QWidget *Camera3;
    QPushButton *PushButtonTopDetail3;
    QPushButton *PushButtonBottomDetail3;
    QPushButton *PushButtonMonoDetail3;
    QWidget *page_3;
    QPushButton *PushButtonColorDifference;
    QPushButton *PushButtonBCode;
    QProgressBar *progressBarTimer;
    QPushButton *PushButtonCheck;

    void setupUi(GUIFormBase *CartonMenuForm)
    {
        if (CartonMenuForm->objectName().isEmpty())
            CartonMenuForm->setObjectName("CartonMenuForm");
        CartonMenuForm->resize(235, 1024);
        horizontalSliderLevel = new QSlider(CartonMenuForm);
        horizontalSliderLevel->setObjectName("horizontalSliderLevel");
        horizontalSliderLevel->setGeometry(QRect(540, 590, 141, 41));
        horizontalSliderLevel->setMaximum(10);
        horizontalSliderLevel->setPageStep(2);
        horizontalSliderLevel->setSliderPosition(5);
        horizontalSliderLevel->setOrientation(Qt::Horizontal);
        horizontalSliderLevel->setTickPosition(QSlider::TicksBelow);
        label_Level = new QLabel(CartonMenuForm);
        label_Level->setObjectName("label_Level");
        label_Level->setGeometry(QRect(690, 590, 31, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252")});
        font.setPointSize(18);
        font.setBold(false);
        label_Level->setFont(font);
        frame = new QFrame(CartonMenuForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 231, 471));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        PushButtonRun = new QPushButton(frame);
        PushButtonRun->setObjectName("PushButtonRun");
        PushButtonRun->setGeometry(QRect(10, 2, 211, 91));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font1.setPointSize(24);
        PushButtonRun->setFont(font1);
        PushButtonRun->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonRun->setCheckable(true);
        PushButtonRun->setChecked(true);
        PushButtonRun->setAutoExclusive(true);
        PushButtonRun->setAutoDefault(false);
        PushButtonRun->setFlat(false);
        pushButtonSetLevel = new QPushButton(CartonMenuForm);
        pushButtonSetLevel->setObjectName("pushButtonSetLevel");
        pushButtonSetLevel->setGeometry(QRect(520, 540, 191, 41));
        QFont font2;
        font2.setPointSize(18);
        font2.setBold(false);
        pushButtonSetLevel->setFont(font2);
        label_Level2 = new QLabel(CartonMenuForm);
        label_Level2->setObjectName("label_Level2");
        label_Level2->setGeometry(QRect(690, 640, 31, 41));
        label_Level2->setFont(font);
        horizontalSliderLevel2 = new QSlider(CartonMenuForm);
        horizontalSliderLevel2->setObjectName("horizontalSliderLevel2");
        horizontalSliderLevel2->setGeometry(QRect(540, 640, 141, 41));
        horizontalSliderLevel2->setMaximum(10);
        horizontalSliderLevel2->setPageStep(2);
        horizontalSliderLevel2->setSliderPosition(5);
        horizontalSliderLevel2->setOrientation(Qt::Horizontal);
        horizontalSliderLevel2->setTickPosition(QSlider::TicksBelow);
        label_Level_3 = new QLabel(CartonMenuForm);
        label_Level_3->setObjectName("label_Level_3");
        label_Level_3->setGeometry(QRect(510, 590, 31, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252")});
        font3.setPointSize(12);
        font3.setBold(false);
        label_Level_3->setFont(font3);
        label_Level_4 = new QLabel(CartonMenuForm);
        label_Level_4->setObjectName("label_Level_4");
        label_Level_4->setGeometry(QRect(510, 640, 31, 41));
        label_Level_4->setFont(font3);
        stackedWidget = new QStackedWidget(CartonMenuForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 180, 231, 701));
        page = new QWidget();
        page->setObjectName("page");
        PushButtonAutoGenerate = new QPushButton(page);
        PushButtonAutoGenerate->setObjectName("PushButtonAutoGenerate");
        PushButtonAutoGenerate->setGeometry(QRect(10, 310, 211, 71));
        PushButtonAutoGenerate->setFont(font1);
        PushButtonAutoGenerate->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(120, 254, 180, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonAutoGenerate->setCheckable(true);
        PushButtonAutoGenerate->setAutoDefault(false);
        PushButtonAutoGenerate->setFlat(false);
        PushButtonInspection = new QPushButton(page);
        PushButtonInspection->setObjectName("PushButtonInspection");
        PushButtonInspection->setGeometry(QRect(10, 180, 211, 61));
        PushButtonInspection->setFont(font1);
        PushButtonInspection->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonInspection->setCheckable(true);
        PushButtonInspection->setAutoExclusive(true);
        PushButtonInspection->setAutoDefault(false);
        PushButtonInspection->setFlat(false);
        PushButtonBlade = new QPushButton(page);
        PushButtonBlade->setObjectName("PushButtonBlade");
        PushButtonBlade->setGeometry(QRect(10, 240, 211, 61));
        PushButtonBlade->setFont(font1);
        PushButtonBlade->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonBlade->setCheckable(true);
        PushButtonBlade->setAutoExclusive(true);
        PushButtonBlade->setAutoDefault(false);
        PushButtonBlade->setFlat(false);
        PushButtonSwitchPhase = new QPushButton(page);
        PushButtonSwitchPhase->setObjectName("PushButtonSwitchPhase");
        PushButtonSwitchPhase->setGeometry(QRect(10, 0, 211, 61));
        PushButtonSwitchPhase->setFont(font1);
        PushButtonSwitchPhase->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSwitchPhase->setCheckable(true);
        PushButtonSwitchPhase->setAutoExclusive(true);
        PushButtonSwitchPhase->setAutoDefault(false);
        PushButtonSwitchPhase->setFlat(false);
        PushButtonMask = new QPushButton(page);
        PushButtonMask->setObjectName("PushButtonMask");
        PushButtonMask->setGeometry(QRect(10, 60, 211, 61));
        PushButtonMask->setFont(font1);
        PushButtonMask->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonMask->setCheckable(true);
        PushButtonMask->setAutoExclusive(true);
        PushButtonMask->setAutoDefault(false);
        PushButtonMask->setFlat(false);
        PushButtonAlignment = new QPushButton(page);
        PushButtonAlignment->setObjectName("PushButtonAlignment");
        PushButtonAlignment->setGeometry(QRect(10, 120, 211, 61));
        PushButtonAlignment->setFont(font1);
        PushButtonAlignment->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonAlignment->setCheckable(true);
        PushButtonAlignment->setAutoExclusive(true);
        PushButtonAlignment->setAutoDefault(false);
        PushButtonAlignment->setFlat(false);
        PushButtonSetting = new QPushButton(page);
        PushButtonSetting->setObjectName("PushButtonSetting");
        PushButtonSetting->setGeometry(QRect(10, 610, 211, 50));
        PushButtonSetting->setFont(font1);
        PushButtonSetting->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonSetting->setCheckable(false);
        PushButtonSetting->setAutoDefault(false);
        PushButtonSetting->setFlat(false);
        PushButtonThresholdTop = new QPushButton(page);
        PushButtonThresholdTop->setObjectName("PushButtonThresholdTop");
        PushButtonThresholdTop->setGeometry(QRect(20, 390, 191, 51));
        PushButtonThresholdTop->setFont(font1);
        PushButtonThresholdTop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonThresholdTop->setCheckable(false);
        PushButtonThresholdTop->setAutoDefault(false);
        PushButtonThresholdTop->setFlat(false);
        PushButtonThresholdBottom = new QPushButton(page);
        PushButtonThresholdBottom->setObjectName("PushButtonThresholdBottom");
        PushButtonThresholdBottom->setGeometry(QRect(20, 450, 191, 51));
        PushButtonThresholdBottom->setFont(font1);
        PushButtonThresholdBottom->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonThresholdBottom->setCheckable(false);
        PushButtonThresholdBottom->setAutoDefault(false);
        PushButtonThresholdBottom->setFlat(false);
        PushButtonLotList2 = new QPushButton(page);
        PushButtonLotList2->setObjectName("PushButtonLotList2");
        PushButtonLotList2->setGeometry(QRect(10, 310, 211, 76));
        PushButtonLotList2->setFont(font1);
        PushButtonLotList2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonLotList2->setCheckable(false);
        PushButtonLotList2->setAutoExclusive(false);
        PushButtonLotList2->setAutoDefault(false);
        PushButtonLotList2->setFlat(false);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        PushButtonEachSetting = new QPushButton(page_2);
        PushButtonEachSetting->setObjectName("PushButtonEachSetting");
        PushButtonEachSetting->setGeometry(QRect(10, 10, 211, 76));
        PushButtonEachSetting->setFont(font1);
        PushButtonEachSetting->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonEachSetting->setCheckable(false);
        PushButtonEachSetting->setAutoExclusive(false);
        PushButtonEachSetting->setAutoDefault(false);
        PushButtonEachSetting->setFlat(false);
        PushButtonLotList = new QPushButton(page_2);
        PushButtonLotList->setObjectName("PushButtonLotList");
        PushButtonLotList->setGeometry(QRect(10, 88, 211, 76));
        PushButtonLotList->setFont(font1);
        PushButtonLotList->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonLotList->setCheckable(false);
        PushButtonLotList->setAutoExclusive(false);
        PushButtonLotList->setAutoDefault(false);
        PushButtonLotList->setFlat(false);
        PushButtonOther = new QPushButton(page_2);
        PushButtonOther->setObjectName("PushButtonOther");
        PushButtonOther->setGeometry(QRect(10, 166, 211, 76));
        PushButtonOther->setFont(font1);
        PushButtonOther->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonOther->setCheckable(false);
        PushButtonOther->setAutoExclusive(false);
        PushButtonOther->setAutoDefault(false);
        PushButtonOther->setFlat(false);
        stackedWidgetDetail = new QStackedWidget(page_2);
        stackedWidgetDetail->setObjectName("stackedWidgetDetail");
        stackedWidgetDetail->setGeometry(QRect(10, 240, 221, 186));
        Camera2 = new QWidget();
        Camera2->setObjectName("Camera2");
        PushButtonBottomDetail = new QPushButton(Camera2);
        PushButtonBottomDetail->setObjectName("PushButtonBottomDetail");
        PushButtonBottomDetail->setGeometry(QRect(0, 90, 211, 81));
        PushButtonBottomDetail->setFont(font1);
        PushButtonBottomDetail->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonBottomDetail->setCheckable(false);
        PushButtonBottomDetail->setAutoExclusive(false);
        PushButtonBottomDetail->setAutoDefault(false);
        PushButtonBottomDetail->setFlat(false);
        PushButtonTopDetail = new QPushButton(Camera2);
        PushButtonTopDetail->setObjectName("PushButtonTopDetail");
        PushButtonTopDetail->setGeometry(QRect(0, 10, 211, 81));
        PushButtonTopDetail->setFont(font1);
        PushButtonTopDetail->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonTopDetail->setCheckable(false);
        PushButtonTopDetail->setAutoExclusive(false);
        PushButtonTopDetail->setAutoDefault(false);
        PushButtonTopDetail->setFlat(false);
        stackedWidgetDetail->addWidget(Camera2);
        Camera3 = new QWidget();
        Camera3->setObjectName("Camera3");
        PushButtonTopDetail3 = new QPushButton(Camera3);
        PushButtonTopDetail3->setObjectName("PushButtonTopDetail3");
        PushButtonTopDetail3->setGeometry(QRect(0, 0, 211, 61));
        PushButtonTopDetail3->setFont(font1);
        PushButtonTopDetail3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonTopDetail3->setCheckable(false);
        PushButtonTopDetail3->setAutoExclusive(false);
        PushButtonTopDetail3->setAutoDefault(false);
        PushButtonTopDetail3->setFlat(false);
        PushButtonBottomDetail3 = new QPushButton(Camera3);
        PushButtonBottomDetail3->setObjectName("PushButtonBottomDetail3");
        PushButtonBottomDetail3->setGeometry(QRect(0, 60, 211, 61));
        PushButtonBottomDetail3->setFont(font1);
        PushButtonBottomDetail3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonBottomDetail3->setCheckable(false);
        PushButtonBottomDetail3->setAutoExclusive(false);
        PushButtonBottomDetail3->setAutoDefault(false);
        PushButtonBottomDetail3->setFlat(false);
        PushButtonMonoDetail3 = new QPushButton(Camera3);
        PushButtonMonoDetail3->setObjectName("PushButtonMonoDetail3");
        PushButtonMonoDetail3->setGeometry(QRect(0, 120, 211, 61));
        PushButtonMonoDetail3->setFont(font1);
        PushButtonMonoDetail3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonMonoDetail3->setCheckable(false);
        PushButtonMonoDetail3->setAutoExclusive(false);
        PushButtonMonoDetail3->setAutoDefault(false);
        PushButtonMonoDetail3->setFlat(false);
        stackedWidgetDetail->addWidget(Camera3);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        PushButtonColorDifference = new QPushButton(page_3);
        PushButtonColorDifference->setObjectName("PushButtonColorDifference");
        PushButtonColorDifference->setGeometry(QRect(10, 270, 211, 61));
        PushButtonColorDifference->setFont(font1);
        PushButtonColorDifference->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonColorDifference->setCheckable(true);
        PushButtonColorDifference->setAutoExclusive(true);
        PushButtonColorDifference->setAutoDefault(false);
        PushButtonColorDifference->setFlat(false);
        stackedWidget->addWidget(page_3);
        PushButtonBCode = new QPushButton(CartonMenuForm);
        PushButtonBCode->setObjectName("PushButtonBCode");
        PushButtonBCode->setGeometry(QRect(570, 830, 211, 76));
        PushButtonBCode->setFont(font1);
        PushButtonBCode->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonBCode->setCheckable(false);
        PushButtonBCode->setAutoExclusive(false);
        PushButtonBCode->setAutoDefault(false);
        PushButtonBCode->setFlat(false);
        progressBarTimer = new QProgressBar(CartonMenuForm);
        progressBarTimer->setObjectName("progressBarTimer");
        progressBarTimer->setGeometry(QRect(0, 1010, 231, 10));
        progressBarTimer->setValue(0);
        progressBarTimer->setTextVisible(false);
        PushButtonCheck = new QPushButton(CartonMenuForm);
        PushButtonCheck->setObjectName("PushButtonCheck");
        PushButtonCheck->setGeometry(QRect(550, 760, 211, 50));
        PushButtonCheck->setFont(font1);
        PushButtonCheck->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonCheck->setCheckable(false);
        PushButtonCheck->setAutoDefault(false);
        PushButtonCheck->setFlat(false);

        retranslateUi(CartonMenuForm);

        PushButtonRun->setDefault(false);
        stackedWidget->setCurrentIndex(0);
        PushButtonAutoGenerate->setDefault(false);
        PushButtonInspection->setDefault(false);
        PushButtonBlade->setDefault(false);
        PushButtonSwitchPhase->setDefault(false);
        PushButtonMask->setDefault(false);
        PushButtonAlignment->setDefault(false);
        PushButtonSetting->setDefault(false);
        PushButtonThresholdTop->setDefault(false);
        PushButtonThresholdBottom->setDefault(false);
        PushButtonLotList2->setDefault(false);
        PushButtonEachSetting->setDefault(false);
        PushButtonLotList->setDefault(false);
        PushButtonOther->setDefault(false);
        stackedWidgetDetail->setCurrentIndex(0);
        PushButtonBottomDetail->setDefault(false);
        PushButtonTopDetail->setDefault(false);
        PushButtonTopDetail3->setDefault(false);
        PushButtonBottomDetail3->setDefault(false);
        PushButtonMonoDetail3->setDefault(false);
        PushButtonColorDifference->setDefault(false);
        PushButtonBCode->setDefault(false);
        PushButtonCheck->setDefault(false);


        QMetaObject::connectSlotsByName(CartonMenuForm);
    } // setupUi

    void retranslateUi(GUIFormBase *CartonMenuForm)
    {
        CartonMenuForm->setWindowTitle(QCoreApplication::translate("CartonMenuForm", "Form", nullptr));
        label_Level->setText(QCoreApplication::translate("CartonMenuForm", "5", nullptr));
        PushButtonRun->setText(QCoreApplication::translate("CartonMenuForm", "\351\201\213\350\273\242", nullptr));
        pushButtonSetLevel->setText(QCoreApplication::translate("CartonMenuForm", "\346\244\234\346\237\273\345\237\272\346\272\226", nullptr));
        label_Level2->setText(QCoreApplication::translate("CartonMenuForm", "5", nullptr));
        label_Level_3->setText(QCoreApplication::translate("CartonMenuForm", "\344\270\212", nullptr));
        label_Level_4->setText(QCoreApplication::translate("CartonMenuForm", "\344\270\213", nullptr));
        PushButtonAutoGenerate->setText(QCoreApplication::translate("CartonMenuForm", "\350\207\252\345\213\225\347\224\237\346\210\220", nullptr));
        PushButtonInspection->setText(QCoreApplication::translate("CartonMenuForm", "\346\244\234\346\237\273\351\240\230\345\237\237", nullptr));
        PushButtonBlade->setText(QCoreApplication::translate("CartonMenuForm", "\345\210\203", nullptr));
        PushButtonSwitchPhase->setText(QCoreApplication::translate("CartonMenuForm", "\351\235\242\347\225\252\345\217\267", nullptr));
        PushButtonMask->setText(QCoreApplication::translate("CartonMenuForm", "\343\203\236\343\202\271\343\202\257/CAD", nullptr));
        PushButtonAlignment->setText(QCoreApplication::translate("CartonMenuForm", "\344\275\215\347\275\256\343\201\202\343\202\217\343\201\233", nullptr));
        PushButtonSetting->setText(QCoreApplication::translate("CartonMenuForm", "\350\250\255\345\256\232", nullptr));
        PushButtonThresholdTop->setText(QCoreApplication::translate("CartonMenuForm", "\344\270\212\346\265\201\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        PushButtonThresholdBottom->setText(QCoreApplication::translate("CartonMenuForm", "\344\270\213\346\265\201\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        PushButtonLotList2->setText(QCoreApplication::translate("CartonMenuForm", "\343\203\255\343\203\203\343\203\210\343\203\252\343\202\271\343\203\210", nullptr));
        PushButtonEachSetting->setText(QCoreApplication::translate("CartonMenuForm", "\345\200\213\345\210\245\350\250\255\345\256\232", nullptr));
        PushButtonLotList->setText(QCoreApplication::translate("CartonMenuForm", "\343\203\255\343\203\203\343\203\210\343\203\252\343\202\271\343\203\210", nullptr));
        PushButtonOther->setText(QCoreApplication::translate("CartonMenuForm", "\343\201\235\343\201\256\344\273\226", nullptr));
        PushButtonBottomDetail->setText(QCoreApplication::translate("CartonMenuForm", "\345\276\214\350\251\263\347\264\260", nullptr));
        PushButtonTopDetail->setText(QCoreApplication::translate("CartonMenuForm", "\345\211\215\350\251\263\347\264\260", nullptr));
        PushButtonTopDetail3->setText(QCoreApplication::translate("CartonMenuForm", "\345\211\215\350\251\263\347\264\260", nullptr));
        PushButtonBottomDetail3->setText(QCoreApplication::translate("CartonMenuForm", "\345\276\214\350\251\263\347\264\260", nullptr));
        PushButtonMonoDetail3->setText(QCoreApplication::translate("CartonMenuForm", "\343\203\242\343\203\216\343\202\257\343\203\255\350\251\263\347\264\260", nullptr));
        PushButtonColorDifference->setText(QCoreApplication::translate("CartonMenuForm", "\350\211\262\345\267\256", nullptr));
        PushButtonBCode->setText(QCoreApplication::translate("CartonMenuForm", "\343\203\220\343\203\274\343\202\263\343\203\274\343\203\211", nullptr));
        PushButtonCheck->setText(QCoreApplication::translate("CartonMenuForm", "\343\203\201\343\202\247\343\203\203\343\202\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CartonMenuForm: public Ui_CartonMenuForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARTONMENUFORM_H
