/********************************************************************************
** Form generated from reading UI file 'WizardMasterMenuForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIZARDMASTERMENUFORM_H
#define UI_WIZARDMASTERMENUFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WizardMasterMenuForm
{
public:
    QPushButton *PushButtonMasterData;

    void setupUi(QWidget *WizardMasterMenuForm)
    {
        if (WizardMasterMenuForm->objectName().isEmpty())
            WizardMasterMenuForm->setObjectName("WizardMasterMenuForm");
        WizardMasterMenuForm->resize(211, 54);
        PushButtonMasterData = new QPushButton(WizardMasterMenuForm);
        PushButtonMasterData->setObjectName("PushButtonMasterData");
        PushButtonMasterData->setGeometry(QRect(0, 0, 211, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(20);
        PushButtonMasterData->setFont(font);
        PushButtonMasterData->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(120, 200, 254, 255), stop:1 rgba(120, 120, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(100, 160, 225, 255), stop:1 rgba(75, 100, 141, 255));\n"
"}"));
        PushButtonMasterData->setCheckable(false);
        PushButtonMasterData->setChecked(false);
        PushButtonMasterData->setAutoDefault(false);
        PushButtonMasterData->setFlat(false);

        retranslateUi(WizardMasterMenuForm);

        PushButtonMasterData->setDefault(false);


        QMetaObject::connectSlotsByName(WizardMasterMenuForm);
    } // setupUi

    void retranslateUi(QWidget *WizardMasterMenuForm)
    {
        WizardMasterMenuForm->setWindowTitle(QCoreApplication::translate("WizardMasterMenuForm", "Form", nullptr));
        PushButtonMasterData->setText(QCoreApplication::translate("WizardMasterMenuForm", "\343\203\236\343\202\271\343\202\277\343\203\274\343\203\207\343\203\274\343\202\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WizardMasterMenuForm: public Ui_WizardMasterMenuForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIZARDMASTERMENUFORM_H
