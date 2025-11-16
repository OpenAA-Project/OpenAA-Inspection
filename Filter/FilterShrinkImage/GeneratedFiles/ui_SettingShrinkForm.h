/********************************************************************************
** Form generated from reading UI file 'SettingShrinkForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSHRINKFORM_H
#define UI_SETTINGSHRINKFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingShrinkFormClass
{
public:
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;
    QLabel *label;
    QSpinBox *spinBoxShrinkRate;
    QLabel *label_2;
    QComboBox *comboBoxShrinkMethod;

    void setupUi(QDialog *SettingShrinkFormClass)
    {
        if (SettingShrinkFormClass->objectName().isEmpty())
            SettingShrinkFormClass->setObjectName("SettingShrinkFormClass");
        SettingShrinkFormClass->resize(295, 219);
        pushButtonCancel = new QPushButton(SettingShrinkFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(160, 160, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonOK = new QPushButton(SettingShrinkFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 160, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        label = new QLabel(SettingShrinkFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 26, 181, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxShrinkRate = new QSpinBox(SettingShrinkFormClass);
        spinBoxShrinkRate->setObjectName("spinBoxShrinkRate");
        spinBoxShrinkRate->setGeometry(QRect(110, 50, 51, 22));
        spinBoxShrinkRate->setMinimum(1);
        spinBoxShrinkRate->setMaximum(100);
        spinBoxShrinkRate->setValue(50);
        label_2 = new QLabel(SettingShrinkFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(170, 52, 21, 20));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxShrinkMethod = new QComboBox(SettingShrinkFormClass);
        comboBoxShrinkMethod->addItem(QString());
        comboBoxShrinkMethod->addItem(QString());
        comboBoxShrinkMethod->addItem(QString());
        comboBoxShrinkMethod->addItem(QString());
        comboBoxShrinkMethod->setObjectName("comboBoxShrinkMethod");
        comboBoxShrinkMethod->setGeometry(QRect(100, 90, 101, 22));

        retranslateUi(SettingShrinkFormClass);

        QMetaObject::connectSlotsByName(SettingShrinkFormClass);
    } // setupUi

    void retranslateUi(QDialog *SettingShrinkFormClass)
    {
        SettingShrinkFormClass->setWindowTitle(QCoreApplication::translate("SettingShrinkFormClass", "SettingShrinkForm", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingShrinkFormClass", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingShrinkFormClass", "OK", nullptr));
        label->setText(QCoreApplication::translate("SettingShrinkFormClass", "\347\270\256\345\260\217\347\216\207", nullptr));
        label_2->setText(QCoreApplication::translate("SettingShrinkFormClass", "%", nullptr));
        comboBoxShrinkMethod->setItemText(0, QCoreApplication::translate("SettingShrinkFormClass", "\345\215\230\347\264\224\347\270\256\345\260\217", nullptr));
        comboBoxShrinkMethod->setItemText(1, QCoreApplication::translate("SettingShrinkFormClass", "\351\253\230\350\274\235\345\272\246\346\216\241\347\224\250", nullptr));
        comboBoxShrinkMethod->setItemText(2, QCoreApplication::translate("SettingShrinkFormClass", "\344\275\216\350\274\235\345\272\246\346\216\241\347\224\250", nullptr));
        comboBoxShrinkMethod->setItemText(3, QCoreApplication::translate("SettingShrinkFormClass", "\345\271\263\345\235\207\345\214\226\347\270\256\345\260\217", nullptr));

    } // retranslateUi

};

namespace Ui {
    class SettingShrinkFormClass: public Ui_SettingShrinkFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSHRINKFORM_H
