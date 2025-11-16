/********************************************************************************
** Form generated from reading UI file 'ButtonSwapInForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONSWAPINFORM_H
#define UI_BUTTONSWAPINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ButtonSwapInForm
{
public:
    QPushButton *pushButton;

    void setupUi(GUIFormBase *ButtonSwapInForm)
    {
        if (ButtonSwapInForm->objectName().isEmpty())
            ButtonSwapInForm->setObjectName("ButtonSwapInForm");
        ButtonSwapInForm->resize(131, 36);
        pushButton = new QPushButton(ButtonSwapInForm);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 131, 34));

        retranslateUi(ButtonSwapInForm);

        QMetaObject::connectSlotsByName(ButtonSwapInForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonSwapInForm)
    {
        ButtonSwapInForm->setWindowTitle(QCoreApplication::translate("ButtonSwapInForm", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("ButtonSwapInForm", "SwapIn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonSwapInForm: public Ui_ButtonSwapInForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONSWAPINFORM_H
