/********************************************************************************
** Form generated from reading UI file 'IPAddressDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPADDRESSDIALOG_H
#define UI_IPADDRESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_IPAddressDialog
{
public:
    QLabel *label_6;
    QLabel *label;
    QLineEdit *lineEditNewDefaultGateway;
    QPushButton *pushButtonCancel;
    QLineEdit *lineEditCurrentIP;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QSpinBox *spinBoxCurrentPort;
    QPushButton *pushButtonSet;
    QLabel *label_7;
    QLineEdit *lineEditNewIP;
    QSpinBox *spinBoxNewPort;
    QLineEdit *lineEditNewSubnetMask;

    void setupUi(QDialog *IPAddressDialog)
    {
        if (IPAddressDialog->objectName().isEmpty())
            IPAddressDialog->setObjectName("IPAddressDialog");
        IPAddressDialog->resize(344, 245);
        label_6 = new QLabel(IPAddressDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 40, 131, 21));
        label = new QLabel(IPAddressDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 121, 21));
        lineEditNewDefaultGateway = new QLineEdit(IPAddressDialog);
        lineEditNewDefaultGateway->setObjectName("lineEditNewDefaultGateway");
        lineEditNewDefaultGateway->setGeometry(QRect(150, 170, 181, 24));
        pushButtonCancel = new QPushButton(IPAddressDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(190, 200, 112, 34));
        lineEditCurrentIP = new QLineEdit(IPAddressDialog);
        lineEditCurrentIP->setObjectName("lineEditCurrentIP");
        lineEditCurrentIP->setGeometry(QRect(150, 10, 181, 24));
        label_3 = new QLabel(IPAddressDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 140, 141, 21));
        label_2 = new QLabel(IPAddressDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 131, 21));
        label_4 = new QLabel(IPAddressDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 170, 141, 21));
        spinBoxCurrentPort = new QSpinBox(IPAddressDialog);
        spinBoxCurrentPort->setObjectName("spinBoxCurrentPort");
        spinBoxCurrentPort->setGeometry(QRect(150, 40, 101, 24));
        spinBoxCurrentPort->setMaximum(65535);
        pushButtonSet = new QPushButton(IPAddressDialog);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(60, 200, 112, 34));
        label_7 = new QLabel(IPAddressDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 110, 131, 21));
        lineEditNewIP = new QLineEdit(IPAddressDialog);
        lineEditNewIP->setObjectName("lineEditNewIP");
        lineEditNewIP->setGeometry(QRect(150, 80, 181, 24));
        spinBoxNewPort = new QSpinBox(IPAddressDialog);
        spinBoxNewPort->setObjectName("spinBoxNewPort");
        spinBoxNewPort->setGeometry(QRect(150, 110, 101, 24));
        spinBoxNewPort->setMaximum(65535);
        lineEditNewSubnetMask = new QLineEdit(IPAddressDialog);
        lineEditNewSubnetMask->setObjectName("lineEditNewSubnetMask");
        lineEditNewSubnetMask->setGeometry(QRect(150, 140, 181, 24));

        retranslateUi(IPAddressDialog);

        pushButtonSet->setDefault(true);


        QMetaObject::connectSlotsByName(IPAddressDialog);
    } // setupUi

    void retranslateUi(QDialog *IPAddressDialog)
    {
        IPAddressDialog->setWindowTitle(QCoreApplication::translate("IPAddressDialog", "Dialog", nullptr));
        label_6->setText(QCoreApplication::translate("IPAddressDialog", "Current port No", nullptr));
        label->setText(QCoreApplication::translate("IPAddressDialog", "Current IP", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("IPAddressDialog", "Cancel", nullptr));
        label_3->setText(QCoreApplication::translate("IPAddressDialog", "New Subnet mask", nullptr));
        label_2->setText(QCoreApplication::translate("IPAddressDialog", "New IP address", nullptr));
        label_4->setText(QCoreApplication::translate("IPAddressDialog", "Default gateway", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("IPAddressDialog", "Set", nullptr));
        label_7->setText(QCoreApplication::translate("IPAddressDialog", "New port No", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IPAddressDialog: public Ui_IPAddressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPADDRESSDIALOG_H
