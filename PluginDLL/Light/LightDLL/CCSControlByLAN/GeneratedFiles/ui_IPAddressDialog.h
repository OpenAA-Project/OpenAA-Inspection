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
    QLabel *label;
    QLineEdit *lineEditCurrentIP;
    QLineEdit *lineEditNewIP;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditNewSubnetMask;
    QLineEdit *lineEditNewDefaultGateway;
    QLabel *label_4;
    QLineEdit *lineEditNewReturnIP;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *spinBoxCurrentPort;
    QSpinBox *spinBoxNewPort;
    QLabel *label_7;
    QSpinBox *spinBoxNewReturnPort;
    QLabel *label_8;
    QPushButton *pushButtonSet;
    QPushButton *pushButtonCancel;
    QLabel *label_9;

    void setupUi(QDialog *IPAddressDialog)
    {
        if (IPAddressDialog->objectName().isEmpty())
            IPAddressDialog->setObjectName("IPAddressDialog");
        IPAddressDialog->resize(349, 371);
        label = new QLabel(IPAddressDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 121, 21));
        lineEditCurrentIP = new QLineEdit(IPAddressDialog);
        lineEditCurrentIP->setObjectName("lineEditCurrentIP");
        lineEditCurrentIP->setGeometry(QRect(150, 10, 181, 24));
        lineEditNewIP = new QLineEdit(IPAddressDialog);
        lineEditNewIP->setObjectName("lineEditNewIP");
        lineEditNewIP->setGeometry(QRect(150, 80, 181, 24));
        label_2 = new QLabel(IPAddressDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 131, 21));
        label_3 = new QLabel(IPAddressDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 170, 141, 21));
        lineEditNewSubnetMask = new QLineEdit(IPAddressDialog);
        lineEditNewSubnetMask->setObjectName("lineEditNewSubnetMask");
        lineEditNewSubnetMask->setGeometry(QRect(150, 170, 181, 24));
        lineEditNewDefaultGateway = new QLineEdit(IPAddressDialog);
        lineEditNewDefaultGateway->setObjectName("lineEditNewDefaultGateway");
        lineEditNewDefaultGateway->setGeometry(QRect(150, 200, 181, 24));
        label_4 = new QLabel(IPAddressDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 200, 141, 21));
        lineEditNewReturnIP = new QLineEdit(IPAddressDialog);
        lineEditNewReturnIP->setObjectName("lineEditNewReturnIP");
        lineEditNewReturnIP->setGeometry(QRect(150, 230, 181, 24));
        label_5 = new QLabel(IPAddressDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 230, 141, 21));
        label_6 = new QLabel(IPAddressDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 40, 131, 21));
        spinBoxCurrentPort = new QSpinBox(IPAddressDialog);
        spinBoxCurrentPort->setObjectName("spinBoxCurrentPort");
        spinBoxCurrentPort->setGeometry(QRect(150, 40, 101, 24));
        spinBoxCurrentPort->setMaximum(65535);
        spinBoxNewPort = new QSpinBox(IPAddressDialog);
        spinBoxNewPort->setObjectName("spinBoxNewPort");
        spinBoxNewPort->setGeometry(QRect(150, 140, 101, 24));
        spinBoxNewPort->setMaximum(65535);
        label_7 = new QLabel(IPAddressDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 140, 131, 21));
        spinBoxNewReturnPort = new QSpinBox(IPAddressDialog);
        spinBoxNewReturnPort->setObjectName("spinBoxNewReturnPort");
        spinBoxNewReturnPort->setGeometry(QRect(150, 260, 101, 24));
        spinBoxNewReturnPort->setMaximum(65535);
        label_8 = new QLabel(IPAddressDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 260, 131, 21));
        pushButtonSet = new QPushButton(IPAddressDialog);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(60, 300, 112, 34));
        pushButtonCancel = new QPushButton(IPAddressDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(190, 300, 112, 34));
        label_9 = new QLabel(IPAddressDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(150, 110, 131, 21));

        retranslateUi(IPAddressDialog);

        pushButtonSet->setDefault(true);


        QMetaObject::connectSlotsByName(IPAddressDialog);
    } // setupUi

    void retranslateUi(QDialog *IPAddressDialog)
    {
        IPAddressDialog->setWindowTitle(QCoreApplication::translate("IPAddressDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("IPAddressDialog", "Current IP", nullptr));
        label_2->setText(QCoreApplication::translate("IPAddressDialog", "New IP address", nullptr));
        label_3->setText(QCoreApplication::translate("IPAddressDialog", "New Subnet mask", nullptr));
        label_4->setText(QCoreApplication::translate("IPAddressDialog", "Default gateway", nullptr));
        label_5->setText(QCoreApplication::translate("IPAddressDialog", "Reruen to IP addr", nullptr));
        label_6->setText(QCoreApplication::translate("IPAddressDialog", "Current port No", nullptr));
        label_7->setText(QCoreApplication::translate("IPAddressDialog", "New port No", nullptr));
        label_8->setText(QCoreApplication::translate("IPAddressDialog", "Return to port No", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("IPAddressDialog", "Set", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("IPAddressDialog", "Cancel", nullptr));
        label_9->setText(QCoreApplication::translate("IPAddressDialog", "Ex: 192.168.000.003", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IPAddressDialog: public Ui_IPAddressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPADDRESSDIALOG_H
