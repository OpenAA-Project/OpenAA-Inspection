/********************************************************************************
** Form generated from reading UI file 'EasyPropertyDXFOperationForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYPROPERTYDXFOPERATIONFORM_H
#define UI_EASYPROPERTYDXFOPERATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyPropertyDXFOperationForm
{
public:
    QToolButton *toolButtonDeleteAll;
    QToolButton *toolButtonAutoGenerate;
    QToolButton *toolButtonRotate;
    QToolButton *toolButtonMove;
    QToolButton *toolButtonYMirror;
    QToolButton *toolButtonXMirror;
    QToolButton *toolButtonEnfatLine;
    QLabel *label;
    QLabel *label_3;
    QToolButton *toolButtonTiltR;
    QToolButton *toolButtonTiltL;
    QToolButton *toolButtonDelBlade;
    QLabel *label_4;
    QToolButton *toolButtonSlightShrinkY;
    QToolButton *toolButtonSlightExtend;
    QToolButton *toolButtonLoadDXF;
    QToolButton *toolButtonAllocList;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QToolButton *toolButtonShrinkY;
    QToolButton *toolButtonExtend;
    QLabel *label_2;
    QWidget *page_2;
    QToolButton *toolButtonShrinkX;
    QLabel *label_5;
    QToolButton *toolButtonExtendX;
    QFrame *frameSelectPage;
    QToolButton *toolButtonPage0;
    QToolButton *toolButtonPage1;

    void setupUi(GUIFormBase *EasyPropertyDXFOperationForm)
    {
        if (EasyPropertyDXFOperationForm->objectName().isEmpty())
            EasyPropertyDXFOperationForm->setObjectName("EasyPropertyDXFOperationForm");
        EasyPropertyDXFOperationForm->resize(175, 928);
        toolButtonDeleteAll = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonDeleteAll->setObjectName("toolButtonDeleteAll");
        toolButtonDeleteAll->setGeometry(QRect(10, 160, 161, 61));
        QFont font;
        font.setPointSize(20);
        toolButtonDeleteAll->setFont(font);
        toolButtonDeleteAll->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 220, 220, 255), stop:1 rgba(165, 120, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonAutoGenerate = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonAutoGenerate->setObjectName("toolButtonAutoGenerate");
        toolButtonAutoGenerate->setGeometry(QRect(750, 80, 161, 71));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        toolButtonAutoGenerate->setFont(font1);
        toolButtonAutoGenerate->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(220, 254, 220, 255), stop:1 rgba(120, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonAutoGenerate->setCheckable(false);
        toolButtonAutoGenerate->setChecked(false);
        toolButtonRotate = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonRotate->setObjectName("toolButtonRotate");
        toolButtonRotate->setGeometry(QRect(10, 225, 161, 71));
        toolButtonRotate->setFont(font);
        toolButtonRotate->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonRotate->setCheckable(false);
        toolButtonRotate->setChecked(false);
        toolButtonMove = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonMove->setObjectName("toolButtonMove");
        toolButtonMove->setGeometry(QRect(10, 660, 161, 64));
        toolButtonMove->setFont(font);
        toolButtonMove->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonMove->setCheckable(true);
        toolButtonMove->setChecked(false);
        toolButtonYMirror = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonYMirror->setObjectName("toolButtonYMirror");
        toolButtonYMirror->setGeometry(QRect(10, 320, 81, 65));
        QFont font2;
        font2.setPointSize(16);
        toolButtonYMirror->setFont(font2);
        toolButtonYMirror->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonYMirror->setCheckable(false);
        toolButtonYMirror->setChecked(false);
        toolButtonXMirror = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonXMirror->setObjectName("toolButtonXMirror");
        toolButtonXMirror->setGeometry(QRect(90, 320, 81, 65));
        toolButtonXMirror->setFont(font2);
        toolButtonXMirror->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonXMirror->setCheckable(false);
        toolButtonXMirror->setChecked(false);
        toolButtonEnfatLine = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonEnfatLine->setObjectName("toolButtonEnfatLine");
        toolButtonEnfatLine->setGeometry(QRect(10, 725, 161, 64));
        toolButtonEnfatLine->setFont(font);
        toolButtonEnfatLine->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonEnfatLine->setCheckable(true);
        toolButtonEnfatLine->setChecked(false);
        label = new QLabel(EasyPropertyDXFOperationForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 300, 161, 20));
        QFont font3;
        font3.setPointSize(12);
        label->setFont(font3);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(EasyPropertyDXFOperationForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 390, 161, 20));
        label_3->setFont(font3);
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        toolButtonTiltR = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonTiltR->setObjectName("toolButtonTiltR");
        toolButtonTiltR->setGeometry(QRect(90, 410, 81, 64));
        toolButtonTiltR->setFont(font2);
        toolButtonTiltR->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonTiltR->setCheckable(false);
        toolButtonTiltR->setChecked(false);
        toolButtonTiltL = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonTiltL->setObjectName("toolButtonTiltL");
        toolButtonTiltL->setGeometry(QRect(10, 410, 81, 64));
        toolButtonTiltL->setFont(font2);
        toolButtonTiltL->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonTiltL->setCheckable(false);
        toolButtonTiltL->setChecked(false);
        toolButtonDelBlade = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonDelBlade->setObjectName("toolButtonDelBlade");
        toolButtonDelBlade->setGeometry(QRect(10, 790, 161, 64));
        toolButtonDelBlade->setFont(font);
        toolButtonDelBlade->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonDelBlade->setCheckable(false);
        toolButtonDelBlade->setChecked(false);
        label_4 = new QLabel(EasyPropertyDXFOperationForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 480, 161, 20));
        label_4->setFont(font3);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        toolButtonSlightShrinkY = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonSlightShrinkY->setObjectName("toolButtonSlightShrinkY");
        toolButtonSlightShrinkY->setGeometry(QRect(90, 500, 81, 65));
        toolButtonSlightShrinkY->setFont(font2);
        toolButtonSlightShrinkY->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonSlightShrinkY->setCheckable(false);
        toolButtonSlightShrinkY->setChecked(false);
        toolButtonSlightExtend = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonSlightExtend->setObjectName("toolButtonSlightExtend");
        toolButtonSlightExtend->setGeometry(QRect(10, 500, 81, 65));
        toolButtonSlightExtend->setFont(font2);
        toolButtonSlightExtend->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonSlightExtend->setCheckable(false);
        toolButtonSlightExtend->setChecked(false);
        toolButtonLoadDXF = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonLoadDXF->setObjectName("toolButtonLoadDXF");
        toolButtonLoadDXF->setGeometry(QRect(10, 10, 161, 81));
        toolButtonLoadDXF->setFont(font);
        toolButtonLoadDXF->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(220, 254, 220, 255), stop:1 rgba(120, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        toolButtonLoadDXF->setCheckable(false);
        toolButtonLoadDXF->setChecked(false);
        toolButtonAllocList = new QToolButton(EasyPropertyDXFOperationForm);
        toolButtonAllocList->setObjectName("toolButtonAllocList");
        toolButtonAllocList->setGeometry(QRect(10, 95, 161, 61));
        toolButtonAllocList->setFont(font);
        toolButtonAllocList->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonAllocList->setCheckable(false);
        toolButtonAllocList->setChecked(false);
        stackedWidget = new QStackedWidget(EasyPropertyDXFOperationForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 570, 161, 91));
        page = new QWidget();
        page->setObjectName("page");
        toolButtonShrinkY = new QToolButton(page);
        toolButtonShrinkY->setObjectName("toolButtonShrinkY");
        toolButtonShrinkY->setGeometry(QRect(80, 20, 81, 65));
        toolButtonShrinkY->setFont(font);
        toolButtonShrinkY->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonShrinkY->setCheckable(false);
        toolButtonShrinkY->setChecked(false);
        toolButtonExtend = new QToolButton(page);
        toolButtonExtend->setObjectName("toolButtonExtend");
        toolButtonExtend->setGeometry(QRect(0, 20, 81, 65));
        toolButtonExtend->setFont(font);
        toolButtonExtend->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonExtend->setCheckable(false);
        toolButtonExtend->setChecked(false);
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 161, 20));
        label_2->setFont(font3);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        toolButtonShrinkX = new QToolButton(page_2);
        toolButtonShrinkX->setObjectName("toolButtonShrinkX");
        toolButtonShrinkX->setGeometry(QRect(80, 20, 81, 65));
        toolButtonShrinkX->setFont(font2);
        toolButtonShrinkX->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonShrinkX->setCheckable(false);
        toolButtonShrinkX->setChecked(false);
        label_5 = new QLabel(page_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 161, 20));
        label_5->setFont(font3);
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        toolButtonExtendX = new QToolButton(page_2);
        toolButtonExtendX->setObjectName("toolButtonExtendX");
        toolButtonExtendX->setGeometry(QRect(0, 20, 81, 65));
        toolButtonExtendX->setFont(font2);
        toolButtonExtendX->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonExtendX->setCheckable(false);
        toolButtonExtendX->setChecked(false);
        stackedWidget->addWidget(page_2);
        frameSelectPage = new QFrame(EasyPropertyDXFOperationForm);
        frameSelectPage->setObjectName("frameSelectPage");
        frameSelectPage->setGeometry(QRect(0, 860, 171, 71));
        frameSelectPage->setFrameShape(QFrame::StyledPanel);
        frameSelectPage->setFrameShadow(QFrame::Raised);
        toolButtonPage0 = new QToolButton(frameSelectPage);
        toolButtonPage0->setObjectName("toolButtonPage0");
        toolButtonPage0->setGeometry(QRect(10, 0, 80, 64));
        toolButtonPage0->setFont(font);
        toolButtonPage0->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonPage0->setCheckable(true);
        toolButtonPage0->setChecked(true);
        toolButtonPage0->setAutoExclusive(true);
        toolButtonPage1 = new QToolButton(frameSelectPage);
        toolButtonPage1->setObjectName("toolButtonPage1");
        toolButtonPage1->setGeometry(QRect(90, 0, 80, 64));
        toolButtonPage1->setFont(font);
        toolButtonPage1->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 220, 255), stop:1 rgba(165, 165, 120, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 0, 255), stop:1 rgba(141, 141, 0, 255));\n"
"}"));
        toolButtonPage1->setCheckable(true);
        toolButtonPage1->setChecked(false);
        toolButtonPage1->setAutoExclusive(true);

        retranslateUi(EasyPropertyDXFOperationForm);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EasyPropertyDXFOperationForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyPropertyDXFOperationForm)
    {
        EasyPropertyDXFOperationForm->setWindowTitle(QCoreApplication::translate("EasyPropertyDXFOperationForm", "Form", nullptr));
        toolButtonDeleteAll->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\205\250\351\203\250\345\211\212\351\231\244", nullptr));
        toolButtonAutoGenerate->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\343\203\236\343\202\271\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        toolButtonRotate->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "90\345\272\246\345\233\236\350\273\242", nullptr));
        toolButtonMove->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\347\247\273\345\213\225", nullptr));
        toolButtonYMirror->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\347\270\246", nullptr));
        toolButtonXMirror->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\346\250\252", nullptr));
        toolButtonEnfatLine->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\347\267\232\350\206\250\345\274\265", nullptr));
        label->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\217\215\350\273\242", nullptr));
        label_3->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\276\256\345\260\217\345\233\236\350\273\242", nullptr));
        toolButtonTiltR->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\217\263", nullptr));
        toolButtonTiltL->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\267\246", nullptr));
        toolButtonDelBlade->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\210\203\345\211\212\351\231\244", nullptr));
        label_4->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\276\256\345\260\217\343\200\200\347\270\246\344\274\270\347\270\256", nullptr));
        toolButtonSlightShrinkY->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\347\270\256", nullptr));
        toolButtonSlightExtend->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\344\274\270", nullptr));
        toolButtonLoadDXF->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "DXF\350\252\255\350\276\274", nullptr));
        toolButtonAllocList->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\211\262\345\275\223\343\203\252\343\202\271\343\203\210", nullptr));
        toolButtonShrinkY->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\347\270\256", nullptr));
        toolButtonExtend->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\344\274\270", nullptr));
        label_2->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\344\274\270\347\270\256", nullptr));
        toolButtonShrinkX->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\347\270\256", nullptr));
        label_5->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\276\256\345\260\217\343\200\200\346\250\252\344\274\270\347\270\256", nullptr));
        toolButtonExtendX->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\344\274\270", nullptr));
        toolButtonPage0->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\267\246", nullptr));
        toolButtonPage1->setText(QCoreApplication::translate("EasyPropertyDXFOperationForm", "\345\217\263", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyPropertyDXFOperationForm: public Ui_EasyPropertyDXFOperationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYPROPERTYDXFOPERATIONFORM_H
