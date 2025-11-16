/********************************************************************************
** Form generated from reading UI file 'SettingFormSmoothLarge.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFORMSMOOTHLARGE_H
#define UI_SETTINGFORMSMOOTHLARGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingFormSmoothLarge
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxWindowSize;
    QLabel *label;

    void setupUi(QDialog *SettingFormSmoothLarge)
    {
        if (SettingFormSmoothLarge->objectName().isEmpty())
            SettingFormSmoothLarge->setObjectName("SettingFormSmoothLarge");
        SettingFormSmoothLarge->resize(196, 122);
        pushButtonOK = new QPushButton(SettingFormSmoothLarge);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 80, 75, 23));
        pushButtonCancel = new QPushButton(SettingFormSmoothLarge);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 80, 75, 23));
        spinBoxWindowSize = new QSpinBox(SettingFormSmoothLarge);
        spinBoxWindowSize->setObjectName("spinBoxWindowSize");
        spinBoxWindowSize->setGeometry(QRect(50, 40, 81, 21));
        label = new QLabel(SettingFormSmoothLarge);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 101, 16));

        retranslateUi(SettingFormSmoothLarge);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingFormSmoothLarge);
    } // setupUi

    void retranslateUi(QDialog *SettingFormSmoothLarge)
    {
        SettingFormSmoothLarge->setWindowTitle(QCoreApplication::translate("SettingFormSmoothLarge", "Setting SmoothLarge", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingFormSmoothLarge", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingFormSmoothLarge", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingFormSmoothLarge", "WindowSize", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingFormSmoothLarge: public Ui_SettingFormSmoothLarge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFORMSMOOTHLARGE_H
