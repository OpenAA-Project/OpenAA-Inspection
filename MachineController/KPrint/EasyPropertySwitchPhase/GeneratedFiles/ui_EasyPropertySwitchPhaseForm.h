/********************************************************************************
** Form generated from reading UI file 'EasyPropertySwitchPhaseForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYPROPERTYSWITCHPHASEFORM_H
#define UI_EASYPROPERTYSWITCHPHASEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyPropertySwitchPhaseForm
{
public:
    QPushButton *PushButtonSetPhaseCount;
    QToolButton *toolButtonCaptureFrom1;
    QToolButton *toolButtonFinishCalc;
    QToolButton *toolButtonDeleteAllAddition;
    QPushButton *PushButtonAutoGeneration;

    void setupUi(GUIFormBase *EasyPropertySwitchPhaseForm)
    {
        if (EasyPropertySwitchPhaseForm->objectName().isEmpty())
            EasyPropertySwitchPhaseForm->setObjectName("EasyPropertySwitchPhaseForm");
        EasyPropertySwitchPhaseForm->resize(202, 325);
        PushButtonSetPhaseCount = new QPushButton(EasyPropertySwitchPhaseForm);
        PushButtonSetPhaseCount->setObjectName("PushButtonSetPhaseCount");
        PushButtonSetPhaseCount->setGeometry(QRect(10, 10, 171, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(18);
        PushButtonSetPhaseCount->setFont(font);
        PushButtonSetPhaseCount->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonSetPhaseCount->setCheckable(false);
        PushButtonSetPhaseCount->setAutoDefault(false);
        PushButtonSetPhaseCount->setFlat(false);
        toolButtonCaptureFrom1 = new QToolButton(EasyPropertySwitchPhaseForm);
        toolButtonCaptureFrom1->setObjectName("toolButtonCaptureFrom1");
        toolButtonCaptureFrom1->setGeometry(QRect(10, 70, 171, 91));
        QFont font1;
        font1.setPointSize(18);
        toolButtonCaptureFrom1->setFont(font1);
        toolButtonCaptureFrom1->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(160, 100, 100, 255), stop:1 rgba(255, 170, 170, 255));\n"
"}"));
        toolButtonCaptureFrom1->setCheckable(true);
        toolButtonCaptureFrom1->setChecked(false);
        toolButtonFinishCalc = new QToolButton(EasyPropertySwitchPhaseForm);
        toolButtonFinishCalc->setObjectName("toolButtonFinishCalc");
        toolButtonFinishCalc->setGeometry(QRect(10, 170, 171, 61));
        toolButtonFinishCalc->setFont(font1);
        toolButtonFinishCalc->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(220, 254, 220, 255), stop:1 rgba(134, 165, 134, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(70, 100, 70, 255), stop:1 rgba(140, 170, 140, 255));\n"
"}"));
        toolButtonFinishCalc->setCheckable(false);
        toolButtonFinishCalc->setChecked(false);
        toolButtonDeleteAllAddition = new QToolButton(EasyPropertySwitchPhaseForm);
        toolButtonDeleteAllAddition->setObjectName("toolButtonDeleteAllAddition");
        toolButtonDeleteAllAddition->setGeometry(QRect(10, 170, 171, 61));
        QFont font2;
        font2.setPointSize(20);
        toolButtonDeleteAllAddition->setFont(font2);
        toolButtonDeleteAllAddition->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 220, 220, 255), stop:1 rgba(165, 120, 120, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonAutoGeneration = new QPushButton(EasyPropertySwitchPhaseForm);
        PushButtonAutoGeneration->setObjectName("PushButtonAutoGeneration");
        PushButtonAutoGeneration->setGeometry(QRect(10, 260, 171, 51));
        PushButtonAutoGeneration->setFont(font);
        PushButtonAutoGeneration->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonAutoGeneration->setCheckable(false);
        PushButtonAutoGeneration->setAutoDefault(false);
        PushButtonAutoGeneration->setFlat(false);

        retranslateUi(EasyPropertySwitchPhaseForm);

        PushButtonSetPhaseCount->setDefault(false);
        PushButtonAutoGeneration->setDefault(false);


        QMetaObject::connectSlotsByName(EasyPropertySwitchPhaseForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyPropertySwitchPhaseForm)
    {
        EasyPropertySwitchPhaseForm->setWindowTitle(QCoreApplication::translate("EasyPropertySwitchPhaseForm", "Form", nullptr));
        PushButtonSetPhaseCount->setText(QCoreApplication::translate("EasyPropertySwitchPhaseForm", "\345\210\207\343\202\212\346\233\277\343\201\210\346\225\260\346\214\207\345\256\232", nullptr));
        toolButtonCaptureFrom1->setText(QCoreApplication::translate("EasyPropertySwitchPhaseForm", "2\343\201\213\343\202\211\346\222\256\345\275\261", nullptr));
        toolButtonFinishCalc->setText(QCoreApplication::translate("EasyPropertySwitchPhaseForm", "\350\250\255\345\256\232\347\242\272\345\256\232", nullptr));
        toolButtonDeleteAllAddition->setText(QCoreApplication::translate("EasyPropertySwitchPhaseForm", "\350\277\275\345\212\240\345\205\250\345\211\212\351\231\244", nullptr));
        PushButtonAutoGeneration->setText(QCoreApplication::translate("EasyPropertySwitchPhaseForm", "\350\207\252\345\213\225\346\212\275\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyPropertySwitchPhaseForm: public Ui_EasyPropertySwitchPhaseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYPROPERTYSWITCHPHASEFORM_H
