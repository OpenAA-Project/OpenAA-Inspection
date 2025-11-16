/********************************************************************************
** Form generated from reading UI file 'ButtonInspectionIDForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONINSPECTIONIDFORM_H
#define UI_BUTTONINSPECTIONIDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonInspectionIDFormClass
{
public:
    QLabel *label;
    QSpinBox *spinBoxID;

    void setupUi(GUIFormBase *ButtonInspectionIDFormClass)
    {
        if (ButtonInspectionIDFormClass->objectName().isEmpty())
            ButtonInspectionIDFormClass->setObjectName("ButtonInspectionIDFormClass");
        ButtonInspectionIDFormClass->resize(131, 22);
        label = new QLabel(ButtonInspectionIDFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 50, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxID = new QSpinBox(ButtonInspectionIDFormClass);
        spinBoxID->setObjectName("spinBoxID");
        spinBoxID->setGeometry(QRect(50, 0, 81, 22));
        spinBoxID->setMaximum(100000000);

        retranslateUi(ButtonInspectionIDFormClass);

        QMetaObject::connectSlotsByName(ButtonInspectionIDFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonInspectionIDFormClass)
    {
        ButtonInspectionIDFormClass->setWindowTitle(QCoreApplication::translate("ButtonInspectionIDFormClass", "ButtonInspectionIDForm", nullptr));
        label->setText(QCoreApplication::translate("ButtonInspectionIDFormClass", "ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonInspectionIDFormClass: public Ui_ButtonInspectionIDFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONINSPECTIONIDFORM_H
