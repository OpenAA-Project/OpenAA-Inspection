/********************************************************************************
** Form generated from reading UI file 'ButtonSettingThresholdForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONSETTINGTHRESHOLDFORM_H
#define UI_BUTTONSETTINGTHRESHOLDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonSettingThresholdForm
{
public:
    QPushButton *PushButtonThreshold;

    void setupUi(GUIFormBase *ButtonSettingThresholdForm)
    {
        if (ButtonSettingThresholdForm->objectName().isEmpty())
            ButtonSettingThresholdForm->setObjectName("ButtonSettingThresholdForm");
        ButtonSettingThresholdForm->resize(199, 79);
        PushButtonThreshold = new QPushButton(ButtonSettingThresholdForm);
        PushButtonThreshold->setObjectName("PushButtonThreshold");
        PushButtonThreshold->setGeometry(QRect(0, 0, 191, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(20);
        PushButtonThreshold->setFont(font);
        PushButtonThreshold->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonThreshold->setCheckable(false);
        PushButtonThreshold->setChecked(false);
        PushButtonThreshold->setAutoDefault(false);
        PushButtonThreshold->setFlat(false);

        retranslateUi(ButtonSettingThresholdForm);

        PushButtonThreshold->setDefault(false);


        QMetaObject::connectSlotsByName(ButtonSettingThresholdForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonSettingThresholdForm)
    {
        ButtonSettingThresholdForm->setWindowTitle(QCoreApplication::translate("ButtonSettingThresholdForm", "Form", nullptr));
        PushButtonThreshold->setText(QCoreApplication::translate("ButtonSettingThresholdForm", "Set threshold", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonSettingThresholdForm: public Ui_ButtonSettingThresholdForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONSETTINGTHRESHOLDFORM_H
