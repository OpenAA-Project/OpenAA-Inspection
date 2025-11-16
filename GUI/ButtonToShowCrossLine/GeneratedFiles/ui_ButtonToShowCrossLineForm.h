/********************************************************************************
** Form generated from reading UI file 'ButtonToShowCrossLineForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONTOSHOWCROSSLINEFORM_H
#define UI_BUTTONTOSHOWCROSSLINEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QToolButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ButtonToShowCrossLineForm
{
public:
    QToolButton *toolButtonCrossLine;

    void setupUi(GUIFormBase *ButtonToShowCrossLineForm)
    {
        if (ButtonToShowCrossLineForm->objectName().isEmpty())
            ButtonToShowCrossLineForm->setObjectName("ButtonToShowCrossLineForm");
        ButtonToShowCrossLineForm->resize(33, 33);
        toolButtonCrossLine = new QToolButton(ButtonToShowCrossLineForm);
        toolButtonCrossLine->setObjectName("toolButtonCrossLine");
        toolButtonCrossLine->setGeometry(QRect(0, 0, 31, 31));
        toolButtonCrossLine->setCheckable(true);

        retranslateUi(ButtonToShowCrossLineForm);

        QMetaObject::connectSlotsByName(ButtonToShowCrossLineForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonToShowCrossLineForm)
    {
        ButtonToShowCrossLineForm->setWindowTitle(QCoreApplication::translate("ButtonToShowCrossLineForm", "Form", nullptr));
        toolButtonCrossLine->setText(QCoreApplication::translate("ButtonToShowCrossLineForm", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonToShowCrossLineForm: public Ui_ButtonToShowCrossLineForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONTOSHOWCROSSLINEFORM_H
