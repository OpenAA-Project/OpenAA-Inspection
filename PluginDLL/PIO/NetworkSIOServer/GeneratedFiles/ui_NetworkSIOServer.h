/********************************************************************************
** Form generated from reading UI file 'NetworkSIOServer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKSIOSERVER_H
#define UI_NETWORKSIOSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkSIOServerClass
{
public:
    QWidget *centralWidget;
    QComboBox *comboBoxCOM;
    QLabel *label;
    QPushButton *pushButtonReOpen;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NetworkSIOServerClass)
    {
        if (NetworkSIOServerClass->objectName().isEmpty())
            NetworkSIOServerClass->setObjectName("NetworkSIOServerClass");
        NetworkSIOServerClass->resize(241, 104);
        centralWidget = new QWidget(NetworkSIOServerClass);
        centralWidget->setObjectName("centralWidget");
        comboBoxCOM = new QComboBox(centralWidget);
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->addItem(QString());
        comboBoxCOM->setObjectName("comboBoxCOM");
        comboBoxCOM->setGeometry(QRect(100, 10, 111, 24));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 75, 21));
        pushButtonReOpen = new QPushButton(centralWidget);
        pushButtonReOpen->setObjectName("pushButtonReOpen");
        pushButtonReOpen->setGeometry(QRect(100, 40, 112, 34));
        NetworkSIOServerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(NetworkSIOServerClass);
        statusBar->setObjectName("statusBar");
        NetworkSIOServerClass->setStatusBar(statusBar);

        retranslateUi(NetworkSIOServerClass);

        QMetaObject::connectSlotsByName(NetworkSIOServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *NetworkSIOServerClass)
    {
        NetworkSIOServerClass->setWindowTitle(QCoreApplication::translate("NetworkSIOServerClass", "SIO:", nullptr));
        comboBoxCOM->setItemText(0, QCoreApplication::translate("NetworkSIOServerClass", "COM1", nullptr));
        comboBoxCOM->setItemText(1, QCoreApplication::translate("NetworkSIOServerClass", "COM1", nullptr));
        comboBoxCOM->setItemText(2, QCoreApplication::translate("NetworkSIOServerClass", "COM2", nullptr));
        comboBoxCOM->setItemText(3, QCoreApplication::translate("NetworkSIOServerClass", "COM3", nullptr));
        comboBoxCOM->setItemText(4, QCoreApplication::translate("NetworkSIOServerClass", "COM4", nullptr));
        comboBoxCOM->setItemText(5, QCoreApplication::translate("NetworkSIOServerClass", "COM5", nullptr));
        comboBoxCOM->setItemText(6, QCoreApplication::translate("NetworkSIOServerClass", "COM6", nullptr));
        comboBoxCOM->setItemText(7, QCoreApplication::translate("NetworkSIOServerClass", "COM7", nullptr));
        comboBoxCOM->setItemText(8, QCoreApplication::translate("NetworkSIOServerClass", "COM8", nullptr));
        comboBoxCOM->setItemText(9, QCoreApplication::translate("NetworkSIOServerClass", "COM9", nullptr));
        comboBoxCOM->setItemText(10, QCoreApplication::translate("NetworkSIOServerClass", "COM10", nullptr));
        comboBoxCOM->setItemText(11, QCoreApplication::translate("NetworkSIOServerClass", "COM11", nullptr));
        comboBoxCOM->setItemText(12, QCoreApplication::translate("NetworkSIOServerClass", "COM12", nullptr));
        comboBoxCOM->setItemText(13, QCoreApplication::translate("NetworkSIOServerClass", "COM13", nullptr));
        comboBoxCOM->setItemText(14, QCoreApplication::translate("NetworkSIOServerClass", "COM14", nullptr));
        comboBoxCOM->setItemText(15, QCoreApplication::translate("NetworkSIOServerClass", "COM15", nullptr));

        label->setText(QCoreApplication::translate("NetworkSIOServerClass", "COM", nullptr));
        pushButtonReOpen->setText(QCoreApplication::translate("NetworkSIOServerClass", "ReOpen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetworkSIOServerClass: public Ui_NetworkSIOServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKSIOSERVER_H
