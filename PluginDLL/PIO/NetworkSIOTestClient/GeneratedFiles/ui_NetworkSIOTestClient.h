/********************************************************************************
** Form generated from reading UI file 'NetworkSIOTestClient.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKSIOTESTCLIENT_H
#define UI_NETWORKSIOTESTCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkSIOTestClientClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QLabel *label;
    QComboBox *comboBoxBaudRate;
    QComboBox *comboBoxCharacter;
    QLabel *label_2;
    QComboBox *comboBoxStopBit;
    QLabel *label_3;
    QComboBox *comboBoxParity;
    QLabel *label_4;
    QToolButton *toolButtonOpen;
    QLabel *label_5;
    QLabel *label_6;
    QTextEdit *textEditTx;
    QTextEdit *textEditRx;
    QPushButton *pushButtonTx;
    QPushButton *pushButtonRx;

    void setupUi(QMainWindow *NetworkSIOTestClientClass)
    {
        if (NetworkSIOTestClientClass->objectName().isEmpty())
            NetworkSIOTestClientClass->setObjectName("NetworkSIOTestClientClass");
        NetworkSIOTestClientClass->resize(600, 346);
        centralWidget = new QWidget(NetworkSIOTestClientClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 181, 341));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 75, 18));
        comboBoxBaudRate = new QComboBox(frame);
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->addItem(QString());
        comboBoxBaudRate->setObjectName("comboBoxBaudRate");
        comboBoxBaudRate->setGeometry(QRect(50, 40, 92, 24));
        comboBoxCharacter = new QComboBox(frame);
        comboBoxCharacter->addItem(QString());
        comboBoxCharacter->addItem(QString());
        comboBoxCharacter->addItem(QString());
        comboBoxCharacter->addItem(QString());
        comboBoxCharacter->setObjectName("comboBoxCharacter");
        comboBoxCharacter->setGeometry(QRect(50, 100, 92, 24));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 80, 101, 18));
        comboBoxStopBit = new QComboBox(frame);
        comboBoxStopBit->addItem(QString());
        comboBoxStopBit->addItem(QString());
        comboBoxStopBit->addItem(QString());
        comboBoxStopBit->setObjectName("comboBoxStopBit");
        comboBoxStopBit->setGeometry(QRect(50, 160, 92, 24));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 140, 111, 18));
        comboBoxParity = new QComboBox(frame);
        comboBoxParity->addItem(QString());
        comboBoxParity->addItem(QString());
        comboBoxParity->addItem(QString());
        comboBoxParity->setObjectName("comboBoxParity");
        comboBoxParity->setGeometry(QRect(50, 220, 92, 24));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 200, 75, 18));
        toolButtonOpen = new QToolButton(frame);
        toolButtonOpen->setObjectName("toolButtonOpen");
        toolButtonOpen->setGeometry(QRect(30, 270, 121, 41));
        toolButtonOpen->setCheckable(true);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(200, 10, 75, 18));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(200, 170, 75, 18));
        textEditTx = new QTextEdit(centralWidget);
        textEditTx->setObjectName("textEditTx");
        textEditTx->setGeometry(QRect(190, 30, 331, 131));
        textEditRx = new QTextEdit(centralWidget);
        textEditRx->setObjectName("textEditRx");
        textEditRx->setGeometry(QRect(190, 190, 331, 131));
        pushButtonTx = new QPushButton(centralWidget);
        pushButtonTx->setObjectName("pushButtonTx");
        pushButtonTx->setGeometry(QRect(530, 80, 61, 34));
        pushButtonRx = new QPushButton(centralWidget);
        pushButtonRx->setObjectName("pushButtonRx");
        pushButtonRx->setGeometry(QRect(530, 230, 61, 34));
        NetworkSIOTestClientClass->setCentralWidget(centralWidget);

        retranslateUi(NetworkSIOTestClientClass);

        QMetaObject::connectSlotsByName(NetworkSIOTestClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *NetworkSIOTestClientClass)
    {
        NetworkSIOTestClientClass->setWindowTitle(QCoreApplication::translate("NetworkSIOTestClientClass", "NetworkSIOTestClient", nullptr));
        label->setText(QCoreApplication::translate("NetworkSIOTestClientClass", "Baud rate", nullptr));
        comboBoxBaudRate->setItemText(0, QCoreApplication::translate("NetworkSIOTestClientClass", "110", nullptr));
        comboBoxBaudRate->setItemText(1, QCoreApplication::translate("NetworkSIOTestClientClass", "300", nullptr));
        comboBoxBaudRate->setItemText(2, QCoreApplication::translate("NetworkSIOTestClientClass", "600", nullptr));
        comboBoxBaudRate->setItemText(3, QCoreApplication::translate("NetworkSIOTestClientClass", "1200", nullptr));
        comboBoxBaudRate->setItemText(4, QCoreApplication::translate("NetworkSIOTestClientClass", "2400", nullptr));
        comboBoxBaudRate->setItemText(5, QCoreApplication::translate("NetworkSIOTestClientClass", "4800", nullptr));
        comboBoxBaudRate->setItemText(6, QCoreApplication::translate("NetworkSIOTestClientClass", "9600", nullptr));
        comboBoxBaudRate->setItemText(7, QCoreApplication::translate("NetworkSIOTestClientClass", "19200", nullptr));
        comboBoxBaudRate->setItemText(8, QCoreApplication::translate("NetworkSIOTestClientClass", "38400", nullptr));
        comboBoxBaudRate->setItemText(9, QCoreApplication::translate("NetworkSIOTestClientClass", "56000", nullptr));
        comboBoxBaudRate->setItemText(10, QCoreApplication::translate("NetworkSIOTestClientClass", "57600", nullptr));
        comboBoxBaudRate->setItemText(11, QCoreApplication::translate("NetworkSIOTestClientClass", "115200", nullptr));

        comboBoxCharacter->setItemText(0, QCoreApplication::translate("NetworkSIOTestClientClass", "5", nullptr));
        comboBoxCharacter->setItemText(1, QCoreApplication::translate("NetworkSIOTestClientClass", "6", nullptr));
        comboBoxCharacter->setItemText(2, QCoreApplication::translate("NetworkSIOTestClientClass", "7", nullptr));
        comboBoxCharacter->setItemText(3, QCoreApplication::translate("NetworkSIOTestClientClass", "8", nullptr));

        label_2->setText(QCoreApplication::translate("NetworkSIOTestClientClass", "Character", nullptr));
        comboBoxStopBit->setItemText(0, QCoreApplication::translate("NetworkSIOTestClientClass", "1", nullptr));
        comboBoxStopBit->setItemText(1, QCoreApplication::translate("NetworkSIOTestClientClass", "2", nullptr));
        comboBoxStopBit->setItemText(2, QCoreApplication::translate("NetworkSIOTestClientClass", "1.5", nullptr));

        label_3->setText(QCoreApplication::translate("NetworkSIOTestClientClass", "Stop bit", nullptr));
        comboBoxParity->setItemText(0, QCoreApplication::translate("NetworkSIOTestClientClass", "None", nullptr));
        comboBoxParity->setItemText(1, QCoreApplication::translate("NetworkSIOTestClientClass", "Odd", nullptr));
        comboBoxParity->setItemText(2, QCoreApplication::translate("NetworkSIOTestClientClass", "Even", nullptr));

        label_4->setText(QCoreApplication::translate("NetworkSIOTestClientClass", "Parity", nullptr));
        toolButtonOpen->setText(QCoreApplication::translate("NetworkSIOTestClientClass", "Open COM", nullptr));
        label_5->setText(QCoreApplication::translate("NetworkSIOTestClientClass", "Tx", nullptr));
        label_6->setText(QCoreApplication::translate("NetworkSIOTestClientClass", "Rx", nullptr));
        pushButtonTx->setText(QCoreApplication::translate("NetworkSIOTestClientClass", "Tx", nullptr));
        pushButtonRx->setText(QCoreApplication::translate("NetworkSIOTestClientClass", "Rx", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetworkSIOTestClientClass: public Ui_NetworkSIOTestClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKSIOTESTCLIENT_H
