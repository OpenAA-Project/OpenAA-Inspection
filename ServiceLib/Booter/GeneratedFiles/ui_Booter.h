/********************************************************************************
** Form generated from reading UI file 'Booter.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOTER_H
#define UI_BOOTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BooterClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonOK;
    QLabel *label;
    QPushButton *pushButtonSetting;

    void setupUi(QMainWindow *BooterClass)
    {
        if (BooterClass->objectName().isEmpty())
            BooterClass->setObjectName("BooterClass");
        BooterClass->resize(320, 235);
        centralWidget = new QWidget(BooterClass);
        centralWidget->setObjectName("centralWidget");
        pushButtonOK = new QPushButton(centralWidget);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(60, 130, 201, 71));
        QFont font;
        font.setPointSize(12);
        pushButtonOK->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 50, 291, 51));
        label->setFont(font);
        pushButtonSetting = new QPushButton(centralWidget);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(160, 10, 151, 41));
        BooterClass->setCentralWidget(centralWidget);

        retranslateUi(BooterClass);

        QMetaObject::connectSlotsByName(BooterClass);
    } // setupUi

    void retranslateUi(QMainWindow *BooterClass)
    {
        BooterClass->setWindowTitle(QCoreApplication::translate("BooterClass", "Booter", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("BooterClass", "OK", nullptr));
        label->setText(QCoreApplication::translate("BooterClass", "All power ON , then push button", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("BooterClass", "Setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BooterClass: public Ui_BooterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOTER_H
