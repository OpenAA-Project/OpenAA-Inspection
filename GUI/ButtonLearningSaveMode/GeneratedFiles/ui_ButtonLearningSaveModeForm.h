/********************************************************************************
** Form generated from reading UI file 'ButtonLearningSaveModeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONLEARNINGSAVEMODEFORM_H
#define UI_BUTTONLEARNINGSAVEMODEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonLearningSaveModeFormClass
{
public:
    QToolButton *toolButton;

    void setupUi(GUIFormBase *ButtonLearningSaveModeFormClass)
    {
        if (ButtonLearningSaveModeFormClass->objectName().isEmpty())
            ButtonLearningSaveModeFormClass->setObjectName("ButtonLearningSaveModeFormClass");
        ButtonLearningSaveModeFormClass->resize(110, 41);
        toolButton = new QToolButton(ButtonLearningSaveModeFormClass);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(0, 0, 111, 31));
        toolButton->setCheckable(true);
        toolButton->setAutoExclusive(true);

        retranslateUi(ButtonLearningSaveModeFormClass);

        QMetaObject::connectSlotsByName(ButtonLearningSaveModeFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonLearningSaveModeFormClass)
    {
        ButtonLearningSaveModeFormClass->setWindowTitle(QCoreApplication::translate("ButtonLearningSaveModeFormClass", "ButtonLearningSaveModeForm", nullptr));
        toolButton->setText(QCoreApplication::translate("ButtonLearningSaveModeFormClass", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonLearningSaveModeFormClass: public Ui_ButtonLearningSaveModeFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONLEARNINGSAVEMODEFORM_H
