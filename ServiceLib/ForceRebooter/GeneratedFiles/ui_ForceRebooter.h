/********************************************************************************
** Form generated from reading UI file 'ForceRebooter.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORCEREBOOTER_H
#define UI_FORCEREBOOTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ForceRebooterClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonRebootPrograms;
    QPushButton *pushButtonRebootPC;
    QPushButton *pushButtonSetting;
    QPushButton *pushButtonShutdownPC;

    void setupUi(QMainWindow *ForceRebooterClass)
    {
        if (ForceRebooterClass->objectName().isEmpty())
            ForceRebooterClass->setObjectName("ForceRebooterClass");
        ForceRebooterClass->resize(128, 170);
        centralWidget = new QWidget(ForceRebooterClass);
        centralWidget->setObjectName("centralWidget");
        pushButtonRebootPrograms = new QPushButton(centralWidget);
        pushButtonRebootPrograms->setObjectName("pushButtonRebootPrograms");
        pushButtonRebootPrograms->setGeometry(QRect(10, 10, 111, 31));
        pushButtonRebootPC = new QPushButton(centralWidget);
        pushButtonRebootPC->setObjectName("pushButtonRebootPC");
        pushButtonRebootPC->setGeometry(QRect(10, 50, 111, 31));
        pushButtonSetting = new QPushButton(centralWidget);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(50, 140, 71, 23));
        pushButtonShutdownPC = new QPushButton(centralWidget);
        pushButtonShutdownPC->setObjectName("pushButtonShutdownPC");
        pushButtonShutdownPC->setGeometry(QRect(10, 90, 111, 31));
        ForceRebooterClass->setCentralWidget(centralWidget);

        retranslateUi(ForceRebooterClass);

        QMetaObject::connectSlotsByName(ForceRebooterClass);
    } // setupUi

    void retranslateUi(QMainWindow *ForceRebooterClass)
    {
        ForceRebooterClass->setWindowTitle(QCoreApplication::translate("ForceRebooterClass", "ForceRebooter", nullptr));
        pushButtonRebootPrograms->setText(QCoreApplication::translate("ForceRebooterClass", "Reboot programs", nullptr));
        pushButtonRebootPC->setText(QCoreApplication::translate("ForceRebooterClass", "Reboot PC", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("ForceRebooterClass", "Setting", nullptr));
        pushButtonShutdownPC->setText(QCoreApplication::translate("ForceRebooterClass", "Shutdown PC", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ForceRebooterClass: public Ui_ForceRebooterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORCEREBOOTER_H
