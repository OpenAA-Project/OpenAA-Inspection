/********************************************************************************
** Form generated from reading UI file 'CreatePasswordForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEPASSWORDFORM_H
#define UI_CREATEPASSWORDFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreatePasswordForm
{
public:
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *CreatePasswordForm)
    {
        if (CreatePasswordForm->objectName().isEmpty())
            CreatePasswordForm->setObjectName("CreatePasswordForm");
        CreatePasswordForm->resize(339, 98);
        lineEditPassword = new QLineEdit(CreatePasswordForm);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setGeometry(QRect(10, 30, 321, 20));
        pushButtonCancel = new QPushButton(CreatePasswordForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(220, 60, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        label = new QLabel(CreatePasswordForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 321, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(CreatePasswordForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 60, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(CreatePasswordForm);

        QMetaObject::connectSlotsByName(CreatePasswordForm);
    } // setupUi

    void retranslateUi(QDialog *CreatePasswordForm)
    {
        CreatePasswordForm->setWindowTitle(QCoreApplication::translate("CreatePasswordForm", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreatePasswordForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("CreatePasswordForm", "Password", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CreatePasswordForm", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreatePasswordForm: public Ui_CreatePasswordForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPASSWORDFORM_H
