/********************************************************************************
** Form generated from reading UI file 'EasyGenerateAlignmentForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYGENERATEALIGNMENTFORM_H
#define UI_EASYGENERATEALIGNMENTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyGenerateAlignmentForm
{
public:
    QToolButton *toolButtonAutoGenerate;

    void setupUi(GUIFormBase *EasyGenerateAlignmentForm)
    {
        if (EasyGenerateAlignmentForm->objectName().isEmpty())
            EasyGenerateAlignmentForm->setObjectName("EasyGenerateAlignmentForm");
        EasyGenerateAlignmentForm->resize(226, 113);
        toolButtonAutoGenerate = new QToolButton(EasyGenerateAlignmentForm);
        toolButtonAutoGenerate->setObjectName("toolButtonAutoGenerate");
        toolButtonAutoGenerate->setGeometry(QRect(10, 0, 191, 111));
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

        retranslateUi(EasyGenerateAlignmentForm);

        QMetaObject::connectSlotsByName(EasyGenerateAlignmentForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyGenerateAlignmentForm)
    {
        EasyGenerateAlignmentForm->setWindowTitle(QCoreApplication::translate("EasyGenerateAlignmentForm", "Form", nullptr));
        toolButtonAutoGenerate->setText(QCoreApplication::translate("EasyGenerateAlignmentForm", "\344\270\241\351\235\242\350\207\252\345\213\225\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyGenerateAlignmentForm: public Ui_EasyGenerateAlignmentForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYGENERATEALIGNMENTFORM_H
