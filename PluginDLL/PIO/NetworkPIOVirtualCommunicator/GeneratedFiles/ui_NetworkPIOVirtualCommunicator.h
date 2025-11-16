/********************************************************************************
** Form generated from reading UI file 'NetworkPIOVirtualCommunicator.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKPIOVIRTUALCOMMUNICATOR_H
#define UI_NETWORKPIOVIRTUALCOMMUNICATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkPIOVirtualCommunicatorClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *NetworkPIOVirtualCommunicatorClass)
    {
        if (NetworkPIOVirtualCommunicatorClass->objectName().isEmpty())
            NetworkPIOVirtualCommunicatorClass->setObjectName("NetworkPIOVirtualCommunicatorClass");
        NetworkPIOVirtualCommunicatorClass->resize(287, 75);
        centralWidget = new QWidget(NetworkPIOVirtualCommunicatorClass);
        centralWidget->setObjectName("centralWidget");
        NetworkPIOVirtualCommunicatorClass->setCentralWidget(centralWidget);

        retranslateUi(NetworkPIOVirtualCommunicatorClass);

        QMetaObject::connectSlotsByName(NetworkPIOVirtualCommunicatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *NetworkPIOVirtualCommunicatorClass)
    {
        NetworkPIOVirtualCommunicatorClass->setWindowTitle(QCoreApplication::translate("NetworkPIOVirtualCommunicatorClass", "NetworkPIOVirtualCommunicator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetworkPIOVirtualCommunicatorClass: public Ui_NetworkPIOVirtualCommunicatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKPIOVIRTUALCOMMUNICATOR_H
