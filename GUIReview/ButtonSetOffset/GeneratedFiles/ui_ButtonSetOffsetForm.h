/********************************************************************************
** Form generated from reading UI file 'ButtonSetOffsetForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONSETOFFSETFORM_H
#define UI_BUTTONSETOFFSETFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonSetOffsetForm
{
public:
    QPushButton *pushButtonSetOffset;

    void setupUi(GUIFormBase *ButtonSetOffsetForm)
    {
        if (ButtonSetOffsetForm->objectName().isEmpty())
            ButtonSetOffsetForm->setObjectName(QString::fromUtf8("ButtonSetOffsetForm"));
        ButtonSetOffsetForm->resize(110, 40);
        pushButtonSetOffset = new QPushButton(ButtonSetOffsetForm);
        pushButtonSetOffset->setObjectName(QString::fromUtf8("pushButtonSetOffset"));
        pushButtonSetOffset->setGeometry(QRect(0, 0, 111, 41));

        retranslateUi(ButtonSetOffsetForm);

        QMetaObject::connectSlotsByName(ButtonSetOffsetForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonSetOffsetForm)
    {
        ButtonSetOffsetForm->setWindowTitle(QCoreApplication::translate("ButtonSetOffsetForm", "Form", nullptr));
        pushButtonSetOffset->setText(QCoreApplication::translate("ButtonSetOffsetForm", "Set Offset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonSetOffsetForm: public Ui_ButtonSetOffsetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONSETOFFSETFORM_H
