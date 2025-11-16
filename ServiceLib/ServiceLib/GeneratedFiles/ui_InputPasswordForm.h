/********************************************************************************
** Form generated from reading UI file 'InputPasswordForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTPASSWORDFORM_H
#define UI_INPUTPASSWORDFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputPasswordForm
{
public:
    QPushButton *pushButtonCancel;
    QLabel *label;
    QPushButton *pushButtonOK;
    QLineEdit *lineEditPassword;

    void setupUi(QDialog *InputPasswordForm)
    {
        if (InputPasswordForm->objectName().isEmpty())
            InputPasswordForm->setObjectName("InputPasswordForm");
        InputPasswordForm->resize(344, 101);
        pushButtonCancel = new QPushButton(InputPasswordForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(220, 60, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonCancel->setAutoDefault(false);
        label = new QLabel(InputPasswordForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 321, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(InputPasswordForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 60, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        lineEditPassword = new QLineEdit(InputPasswordForm);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setGeometry(QRect(10, 30, 321, 20));
        lineEditPassword->setEchoMode(QLineEdit::Password);

        retranslateUi(InputPasswordForm);

        QMetaObject::connectSlotsByName(InputPasswordForm);
    } // setupUi

    void retranslateUi(QDialog *InputPasswordForm)
    {
        InputPasswordForm->setWindowTitle(QCoreApplication::translate("InputPasswordForm", "Input password", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputPasswordForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("InputPasswordForm", "Password", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputPasswordForm", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputPasswordForm: public Ui_InputPasswordForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTPASSWORDFORM_H
