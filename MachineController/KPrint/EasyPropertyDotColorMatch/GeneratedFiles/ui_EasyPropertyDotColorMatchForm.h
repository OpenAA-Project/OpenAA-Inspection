/********************************************************************************
** Form generated from reading UI file 'EasyPropertyDotColorMatchForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYPROPERTYDOTCOLORMATCHFORM_H
#define UI_EASYPROPERTYDOTCOLORMATCHFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyPropertyDotColorMatchForm
{
public:
    QToolButton *toolButtonDeleteAll;
    QToolButton *toolButtonAutoGenerate;
    QToolButton *toolButtonShrinkOutline;
    QLabel *label_Unit;
    QLabel *label_2;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxShrinkDotForCADMM;
    QSpinBox *spinBoxShrinkDotForCAD;

    void setupUi(GUIFormBase *EasyPropertyDotColorMatchForm)
    {
        if (EasyPropertyDotColorMatchForm->objectName().isEmpty())
            EasyPropertyDotColorMatchForm->setObjectName("EasyPropertyDotColorMatchForm");
        EasyPropertyDotColorMatchForm->resize(203, 584);
        toolButtonDeleteAll = new QToolButton(EasyPropertyDotColorMatchForm);
        toolButtonDeleteAll->setObjectName("toolButtonDeleteAll");
        toolButtonDeleteAll->setGeometry(QRect(10, 110, 161, 91));
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
        toolButtonAutoGenerate = new QToolButton(EasyPropertyDotColorMatchForm);
        toolButtonAutoGenerate->setObjectName("toolButtonAutoGenerate");
        toolButtonAutoGenerate->setGeometry(QRect(10, 10, 161, 91));
        toolButtonAutoGenerate->setFont(font);
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
        toolButtonShrinkOutline = new QToolButton(EasyPropertyDotColorMatchForm);
        toolButtonShrinkOutline->setObjectName("toolButtonShrinkOutline");
        toolButtonShrinkOutline->setGeometry(QRect(10, 330, 161, 91));
        toolButtonShrinkOutline->setFont(font);
        toolButtonShrinkOutline->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(220, 220, 255, 255), stop:1 rgba(120, 120, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 0, 255, 255), stop:1 rgba(0, 0, 141, 255));\n"
"}"));
        toolButtonShrinkOutline->setCheckable(false);
        toolButtonShrinkOutline->setChecked(false);
        label_Unit = new QLabel(EasyPropertyDotColorMatchForm);
        label_Unit->setObjectName("label_Unit");
        label_Unit->setGeometry(QRect(160, 460, 81, 31));
        label_2 = new QLabel(EasyPropertyDotColorMatchForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 430, 81, 31));
        label = new QLabel(EasyPropertyDotColorMatchForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 430, 61, 31));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxShrinkDotForCADMM = new QDoubleSpinBox(EasyPropertyDotColorMatchForm);
        doubleSpinBoxShrinkDotForCADMM->setObjectName("doubleSpinBoxShrinkDotForCADMM");
        doubleSpinBoxShrinkDotForCADMM->setGeometry(QRect(76, 460, 81, 31));
        QFont font1;
        font1.setPointSize(11);
        doubleSpinBoxShrinkDotForCADMM->setFont(font1);
        doubleSpinBoxShrinkDotForCADMM->setMinimum(-9999.000000000000000);
        doubleSpinBoxShrinkDotForCADMM->setMaximum(9999.000000000000000);
        spinBoxShrinkDotForCAD = new QSpinBox(EasyPropertyDotColorMatchForm);
        spinBoxShrinkDotForCAD->setObjectName("spinBoxShrinkDotForCAD");
        spinBoxShrinkDotForCAD->setGeometry(QRect(76, 430, 81, 31));
        spinBoxShrinkDotForCAD->setFont(font1);
        spinBoxShrinkDotForCAD->setMinimum(-100);
        spinBoxShrinkDotForCAD->setMaximum(100);
        spinBoxShrinkDotForCAD->setValue(20);

        retranslateUi(EasyPropertyDotColorMatchForm);

        QMetaObject::connectSlotsByName(EasyPropertyDotColorMatchForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyPropertyDotColorMatchForm)
    {
        EasyPropertyDotColorMatchForm->setWindowTitle(QCoreApplication::translate("EasyPropertyDotColorMatchForm", "Form", nullptr));
        toolButtonDeleteAll->setText(QCoreApplication::translate("EasyPropertyDotColorMatchForm", "\345\205\250\351\203\250\345\211\212\351\231\244", nullptr));
        toolButtonAutoGenerate->setText(QCoreApplication::translate("EasyPropertyDotColorMatchForm", "\350\207\252\345\213\225\347\224\237\346\210\220", nullptr));
        toolButtonShrinkOutline->setText(QCoreApplication::translate("EasyPropertyDotColorMatchForm", "\343\202\250\343\203\203\343\202\270\345\217\216\347\270\256\343\203\273\350\206\250\345\274\265", nullptr));
        label_Unit->setText(QCoreApplication::translate("EasyPropertyDotColorMatchForm", "mm", nullptr));
        label_2->setText(QCoreApplication::translate("EasyPropertyDotColorMatchForm", "Dot", nullptr));
        label->setText(QCoreApplication::translate("EasyPropertyDotColorMatchForm", "\345\217\216\347\270\256\351\207\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyPropertyDotColorMatchForm: public Ui_EasyPropertyDotColorMatchForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYPROPERTYDOTCOLORMATCHFORM_H
