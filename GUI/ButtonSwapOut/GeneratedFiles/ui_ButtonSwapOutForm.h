/********************************************************************************
** Form generated from reading UI file 'ButtonSwapOutForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONSWAPOUTFORM_H
#define UI_BUTTONSWAPOUTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ButtonSwapOutForm
{
public:
    QPushButton *pushButton;

    void setupUi(GUIFormBase *ButtonSwapOutForm)
    {
        if (ButtonSwapOutForm->objectName().isEmpty())
            ButtonSwapOutForm->setObjectName("ButtonSwapOutForm");
        ButtonSwapOutForm->resize(113, 38);
        pushButton = new QPushButton(ButtonSwapOutForm);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 112, 34));

        retranslateUi(ButtonSwapOutForm);

        QMetaObject::connectSlotsByName(ButtonSwapOutForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonSwapOutForm)
    {
        ButtonSwapOutForm->setWindowTitle(QCoreApplication::translate("ButtonSwapOutForm", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("ButtonSwapOutForm", "Swap out", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonSwapOutForm: public Ui_ButtonSwapOutForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONSWAPOUTFORM_H
