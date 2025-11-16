/********************************************************************************
** Form generated from reading UI file 'AlertDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALERTDIALOG_H
#define UI_ALERTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AlertDialog
{
public:
    QPushButton *pushButtonOK;
    QLabel *label;

    void setupUi(QDialog *AlertDialog)
    {
        if (AlertDialog->objectName().isEmpty())
            AlertDialog->setObjectName("AlertDialog");
        AlertDialog->resize(226, 123);
        pushButtonOK = new QPushButton(AlertDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(80, 70, 81, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        label = new QLabel(AlertDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 201, 31));
        label->setWordWrap(true);

        retranslateUi(AlertDialog);

        QMetaObject::connectSlotsByName(AlertDialog);
    } // setupUi

    void retranslateUi(QDialog *AlertDialog)
    {
        AlertDialog->setWindowTitle(QCoreApplication::translate("AlertDialog", "Alert", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AlertDialog", "OK", nullptr));
        label->setText(QCoreApplication::translate("AlertDialog", "XXX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlertDialog: public Ui_AlertDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALERTDIALOG_H
