/********************************************************************************
** Form generated from reading UI file 'SendMessagerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDMESSAGERFORM_H
#define UI_SENDMESSAGERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_SendMessagerFormClass
{
public:
    QLineEdit *lineEditMessage;
    QComboBox *comboBoxPage;
    QPushButton *pushButtonSend;

    void setupUi(GUIFormBase *SendMessagerFormClass)
    {
        if (SendMessagerFormClass->objectName().isEmpty())
            SendMessagerFormClass->setObjectName("SendMessagerFormClass");
        SendMessagerFormClass->resize(265, 22);
        lineEditMessage = new QLineEdit(SendMessagerFormClass);
        lineEditMessage->setObjectName("lineEditMessage");
        lineEditMessage->setGeometry(QRect(80, 0, 113, 21));
        comboBoxPage = new QComboBox(SendMessagerFormClass);
        comboBoxPage->setObjectName("comboBoxPage");
        comboBoxPage->setGeometry(QRect(0, 0, 81, 22));
        pushButtonSend = new QPushButton(SendMessagerFormClass);
        pushButtonSend->setObjectName("pushButtonSend");
        pushButtonSend->setGeometry(QRect(190, 0, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Message.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSend->setIcon(icon);

        retranslateUi(SendMessagerFormClass);

        QMetaObject::connectSlotsByName(SendMessagerFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *SendMessagerFormClass)
    {
        SendMessagerFormClass->setWindowTitle(QCoreApplication::translate("SendMessagerFormClass", "SendMessagerForm", nullptr));
        pushButtonSend->setText(QCoreApplication::translate("SendMessagerFormClass", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SendMessagerFormClass: public Ui_SendMessagerFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDMESSAGERFORM_H
