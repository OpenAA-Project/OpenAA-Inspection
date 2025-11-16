/********************************************************************************
** Form generated from reading UI file 'settingform.ui'
**
** Created: Mon Oct 1 16:13:18 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFORM_H
#define UI_SETTINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingFormClass
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLineEdit *LEPort;
    QSpinBox *LETime;

    void setupUi(QWidget *SettingFormClass)
    {
        if (SettingFormClass->objectName().isEmpty())
            SettingFormClass->setObjectName(QString::fromUtf8("SettingFormClass"));
        SettingFormClass->resize(232, 187);
        label = new QLabel(SettingFormClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 50, 13));
        label_2 = new QLabel(SettingFormClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 50, 13));
        pushButton = new QPushButton(SettingFormClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 140, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/XmlServer/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton_2 = new QPushButton(SettingFormClass);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(130, 140, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/XmlServer/Qtres/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);
        label_3 = new QLabel(SettingFormClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(170, 110, 50, 13));
        LEPort = new QLineEdit(SettingFormClass);
        LEPort->setObjectName(QString::fromUtf8("LEPort"));
        LEPort->setGeometry(QRect(50, 40, 113, 20));
        LEPort->setMaxLength(5);
        LETime = new QSpinBox(SettingFormClass);
        LETime->setObjectName(QString::fromUtf8("LETime"));
        LETime->setGeometry(QRect(80, 100, 71, 22));
        LETime->setMinimum(1);
        LETime->setMaximum(480);

        retranslateUi(SettingFormClass);

        QMetaObject::connectSlotsByName(SettingFormClass);
    } // setupUi

    void retranslateUi(QWidget *SettingFormClass)
    {
        SettingFormClass->setWindowTitle(QApplication::translate("SettingFormClass", "SettingForm", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SettingFormClass", "Port", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SettingFormClass", "TimeOut", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SettingFormClass", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("SettingFormClass", "Cancel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SettingFormClass", "(hour)", 0, QApplication::UnicodeUTF8));
        LEPort->setInputMask(QApplication::translate("SettingFormClass", "00000; ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingFormClass: public Ui_SettingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFORM_H
