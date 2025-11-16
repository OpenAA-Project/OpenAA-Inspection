/********************************************************************************
** Form generated from reading UI file 'InputStringDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTSTRINGDIALOG_H
#define UI_INPUTSTRINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputStringDialog
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *InputStringDialog)
    {
        if (InputStringDialog->objectName().isEmpty())
            InputStringDialog->setObjectName("InputStringDialog");
        InputStringDialog->resize(236, 84);
        lineEdit = new QLineEdit(InputStringDialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 10, 211, 20));
        pushButtonCancel = new QPushButton(InputStringDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 40, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonOK = new QPushButton(InputStringDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 40, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(InputStringDialog);

        QMetaObject::connectSlotsByName(InputStringDialog);
    } // setupUi

    void retranslateUi(QDialog *InputStringDialog)
    {
        InputStringDialog->setWindowTitle(QCoreApplication::translate("InputStringDialog", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputStringDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputStringDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputStringDialog: public Ui_InputStringDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTSTRINGDIALOG_H
