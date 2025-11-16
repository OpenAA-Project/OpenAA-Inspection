/********************************************************************************
** Form generated from reading UI file 'SettingMedianForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGMEDIANFORM_H
#define UI_SETTINGMEDIANFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingMedianFormClass
{
public:
    QLabel *label_2;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;
    QLabel *label;
    QSpinBox *spinBoxFilterDot;

    void setupUi(QDialog *SettingMedianFormClass)
    {
        if (SettingMedianFormClass->objectName().isEmpty())
            SettingMedianFormClass->setObjectName("SettingMedianFormClass");
        SettingMedianFormClass->resize(257, 130);
        label_2 = new QLabel(SettingMedianFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(150, 42, 21, 20));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(SettingMedianFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 70, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonOK = new QPushButton(SettingMedianFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 70, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        label = new QLabel(SettingMedianFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 16, 181, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxFilterDot = new QSpinBox(SettingMedianFormClass);
        spinBoxFilterDot->setObjectName("spinBoxFilterDot");
        spinBoxFilterDot->setGeometry(QRect(90, 40, 51, 22));
        spinBoxFilterDot->setMinimum(1);
        spinBoxFilterDot->setMaximum(100);
        spinBoxFilterDot->setValue(50);

        retranslateUi(SettingMedianFormClass);

        QMetaObject::connectSlotsByName(SettingMedianFormClass);
    } // setupUi

    void retranslateUi(QDialog *SettingMedianFormClass)
    {
        SettingMedianFormClass->setWindowTitle(QCoreApplication::translate("SettingMedianFormClass", "SettingMedianForm", nullptr));
        label_2->setText(QCoreApplication::translate("SettingMedianFormClass", "Dot", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingMedianFormClass", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingMedianFormClass", "OK", nullptr));
        label->setText(QCoreApplication::translate("SettingMedianFormClass", "\343\203\225\343\202\243\343\203\253\343\202\277\343\203\274\347\237\251\345\275\242\343\202\265\343\202\244\343\202\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingMedianFormClass: public Ui_SettingMedianFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGMEDIANFORM_H
