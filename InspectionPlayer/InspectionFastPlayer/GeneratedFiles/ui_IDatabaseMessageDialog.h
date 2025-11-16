/********************************************************************************
** Form generated from reading UI file 'IDatabaseMessageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDATABASEMESSAGEDIALOG_H
#define UI_IDATABASEMESSAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_IDatabaseMessageDialogClass
{
public:
    QPushButton *OKButton;
    QTextEdit *textMessage;

    void setupUi(QDialog *IDatabaseMessageDialogClass)
    {
        if (IDatabaseMessageDialogClass->objectName().isEmpty())
            IDatabaseMessageDialogClass->setObjectName("IDatabaseMessageDialogClass");
        IDatabaseMessageDialogClass->resize(400, 241);
        OKButton = new QPushButton(IDatabaseMessageDialogClass);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(130, 190, 151, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        OKButton->setIcon(icon);
        textMessage = new QTextEdit(IDatabaseMessageDialogClass);
        textMessage->setObjectName("textMessage");
        textMessage->setEnabled(false);
        textMessage->setGeometry(QRect(30, 20, 351, 161));

        retranslateUi(IDatabaseMessageDialogClass);
        QObject::connect(OKButton, &QPushButton::clicked, IDatabaseMessageDialogClass, qOverload<>(&QDialog::close));

        OKButton->setDefault(true);


        QMetaObject::connectSlotsByName(IDatabaseMessageDialogClass);
    } // setupUi

    void retranslateUi(QDialog *IDatabaseMessageDialogClass)
    {
        IDatabaseMessageDialogClass->setWindowTitle(QCoreApplication::translate("IDatabaseMessageDialogClass", "IDatabaseMessageDialog", nullptr));
        OKButton->setText(QCoreApplication::translate("IDatabaseMessageDialogClass", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IDatabaseMessageDialogClass: public Ui_IDatabaseMessageDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDATABASEMESSAGEDIALOG_H
