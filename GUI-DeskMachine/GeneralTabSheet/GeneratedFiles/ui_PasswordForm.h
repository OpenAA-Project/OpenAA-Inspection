/********************************************************************************
** Form generated from reading UI file 'PasswordForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDFORM_H
#define UI_PASSWORDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PasswordFormClass
{
public:
    QPushButton *pbOK;
    QLineEdit *lePassword;
    QPushButton *pbCancel;
    QLabel *label;

    void setupUi(QDialog *PasswordFormClass)
    {
        if (PasswordFormClass->objectName().isEmpty())
            PasswordFormClass->setObjectName(QString::fromUtf8("PasswordFormClass"));
        PasswordFormClass->resize(212, 109);
        pbOK = new QPushButton(PasswordFormClass);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));
        pbOK->setGeometry(QRect(10, 70, 75, 31));
        lePassword = new QLineEdit(PasswordFormClass);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));
        lePassword->setGeometry(QRect(10, 40, 191, 20));
        lePassword->setEchoMode(QLineEdit::Password);
        pbCancel = new QPushButton(PasswordFormClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        pbCancel->setGeometry(QRect(130, 70, 75, 31));
        pbCancel->setAutoDefault(false);
        label = new QLabel(PasswordFormClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 191, 21));

        retranslateUi(PasswordFormClass);

        QMetaObject::connectSlotsByName(PasswordFormClass);
    } // setupUi

    void retranslateUi(QDialog *PasswordFormClass)
    {
        PasswordFormClass->setWindowTitle(QCoreApplication::translate("PasswordFormClass", "PasswordForm", nullptr));
        pbOK->setText(QCoreApplication::translate("PasswordFormClass", "OK", nullptr));
        pbCancel->setText(QCoreApplication::translate("PasswordFormClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("PasswordFormClass", "Please input password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasswordFormClass: public Ui_PasswordFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDFORM_H
