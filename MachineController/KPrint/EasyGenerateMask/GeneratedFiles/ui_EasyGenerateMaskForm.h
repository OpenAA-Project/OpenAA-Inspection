/********************************************************************************
** Form generated from reading UI file 'EasyGenerateMaskForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYGENERATEMASKFORM_H
#define UI_EASYGENERATEMASKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyGenerateMaskForm
{
public:
    QToolButton *toolButtonAutoGenerate;

    void setupUi(GUIFormBase *EasyGenerateMaskForm)
    {
        if (EasyGenerateMaskForm->objectName().isEmpty())
            EasyGenerateMaskForm->setObjectName("EasyGenerateMaskForm");
        EasyGenerateMaskForm->resize(229, 115);
        toolButtonAutoGenerate = new QToolButton(EasyGenerateMaskForm);
        toolButtonAutoGenerate->setObjectName("toolButtonAutoGenerate");
        toolButtonAutoGenerate->setGeometry(QRect(0, 0, 191, 111));
        QFont font;
        font.setPointSize(20);
        toolButtonAutoGenerate->setFont(font);
        toolButtonAutoGenerate->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 200, 255), stop:1 rgba(165, 165, 125, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonAutoGenerate->setCheckable(false);

        retranslateUi(EasyGenerateMaskForm);

        QMetaObject::connectSlotsByName(EasyGenerateMaskForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyGenerateMaskForm)
    {
        EasyGenerateMaskForm->setWindowTitle(QCoreApplication::translate("EasyGenerateMaskForm", "Form", nullptr));
        toolButtonAutoGenerate->setText(QCoreApplication::translate("EasyGenerateMaskForm", "\344\270\241\351\235\242\350\207\252\345\213\225\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyGenerateMaskForm: public Ui_EasyGenerateMaskForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYGENERATEMASKFORM_H
