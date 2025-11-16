/********************************************************************************
** Form generated from reading UI file 'ButtonSettingColorDifferenceForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONSETTINGCOLORDIFFERENCEFORM_H
#define UI_BUTTONSETTINGCOLORDIFFERENCEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ButtonSettingColorDifferenceForm
{
public:
    QPushButton *PushButtonThreshold;

    void setupUi(GUIFormBase *ButtonSettingColorDifferenceForm)
    {
        if (ButtonSettingColorDifferenceForm->objectName().isEmpty())
            ButtonSettingColorDifferenceForm->setObjectName("ButtonSettingColorDifferenceForm");
        ButtonSettingColorDifferenceForm->resize(190, 55);
        PushButtonThreshold = new QPushButton(ButtonSettingColorDifferenceForm);
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

        retranslateUi(ButtonSettingColorDifferenceForm);

        PushButtonThreshold->setDefault(false);


        QMetaObject::connectSlotsByName(ButtonSettingColorDifferenceForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonSettingColorDifferenceForm)
    {
        ButtonSettingColorDifferenceForm->setWindowTitle(QCoreApplication::translate("ButtonSettingColorDifferenceForm", "Form", nullptr));
        PushButtonThreshold->setText(QCoreApplication::translate("ButtonSettingColorDifferenceForm", "Set threshold", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonSettingColorDifferenceForm: public Ui_ButtonSettingColorDifferenceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONSETTINGCOLORDIFFERENCEFORM_H
