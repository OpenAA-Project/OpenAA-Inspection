/********************************************************************************
** Form generated from reading UI file 'SettingSmoothingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSMOOTHINGFORM_H
#define UI_SETTINGSMOOTHINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingSmoothingFormClass
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QComboBox *comboBoxMethod;

    void setupUi(QDialog *SettingSmoothingFormClass)
    {
        if (SettingSmoothingFormClass->objectName().isEmpty())
            SettingSmoothingFormClass->setObjectName("SettingSmoothingFormClass");
        SettingSmoothingFormClass->resize(291, 167);
        pushButtonOK = new QPushButton(SettingSmoothingFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 100, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(SettingSmoothingFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(160, 100, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        comboBoxMethod = new QComboBox(SettingSmoothingFormClass);
        comboBoxMethod->addItem(QString());
        comboBoxMethod->addItem(QString());
        comboBoxMethod->setObjectName("comboBoxMethod");
        comboBoxMethod->setGeometry(QRect(30, 40, 231, 22));

        retranslateUi(SettingSmoothingFormClass);

        QMetaObject::connectSlotsByName(SettingSmoothingFormClass);
    } // setupUi

    void retranslateUi(QDialog *SettingSmoothingFormClass)
    {
        SettingSmoothingFormClass->setWindowTitle(QCoreApplication::translate("SettingSmoothingFormClass", "SettingSmoothingForm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingSmoothingFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingSmoothingFormClass", "Cancel", nullptr));
        comboBoxMethod->setItemText(0, QCoreApplication::translate("SettingSmoothingFormClass", "\347\270\246\346\226\271\345\220\221\343\203\225\343\202\243\343\203\253\343\202\277", nullptr));
        comboBoxMethod->setItemText(1, QCoreApplication::translate("SettingSmoothingFormClass", "\347\237\251\345\275\242\343\203\225\343\202\243\343\203\253\343\202\277", nullptr));

    } // retranslateUi

};

namespace Ui {
    class SettingSmoothingFormClass: public Ui_SettingSmoothingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSMOOTHINGFORM_H
