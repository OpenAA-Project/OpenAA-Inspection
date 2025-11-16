/********************************************************************************
** Form generated from reading UI file 'PIODevicer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIODEVICER_H
#define UI_PIODEVICER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PIODevicerClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *PIODevicerClass)
    {
        if (PIODevicerClass->objectName().isEmpty())
            PIODevicerClass->setObjectName("PIODevicerClass");
        PIODevicerClass->resize(599, 400);
        centralWidget = new QWidget(PIODevicerClass);
        centralWidget->setObjectName("centralWidget");
        PIODevicerClass->setCentralWidget(centralWidget);

        retranslateUi(PIODevicerClass);

        QMetaObject::connectSlotsByName(PIODevicerClass);
    } // setupUi

    void retranslateUi(QMainWindow *PIODevicerClass)
    {
        PIODevicerClass->setWindowTitle(QCoreApplication::translate("PIODevicerClass", "PIODevicer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PIODevicerClass: public Ui_PIODevicerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIODEVICER_H
