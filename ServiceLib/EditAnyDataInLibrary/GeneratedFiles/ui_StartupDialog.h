/********************************************************************************
** Form generated from reading UI file 'StartupDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTUPDIALOG_H
#define UI_STARTUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_StartupDialogClass
{
public:
    QLineEdit *lineEditDBHost;
    QLineEdit *lineEditDBFileName;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonOK;
    QLabel *label_3;
    QSpinBox *spinBoxPortNumber;

    void setupUi(QDialog *StartupDialogClass)
    {
        if (StartupDialogClass->objectName().isEmpty())
            StartupDialogClass->setObjectName("StartupDialogClass");
        StartupDialogClass->resize(276, 209);
        lineEditDBHost = new QLineEdit(StartupDialogClass);
        lineEditDBHost->setObjectName("lineEditDBHost");
        lineEditDBHost->setGeometry(QRect(20, 30, 231, 20));
        lineEditDBFileName = new QLineEdit(StartupDialogClass);
        lineEditDBFileName->setObjectName("lineEditDBFileName");
        lineEditDBFileName->setGeometry(QRect(20, 130, 231, 20));
        label = new QLabel(StartupDialogClass);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 231, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(StartupDialogClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 110, 231, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(StartupDialogClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(100, 162, 75, 31));
        label_3 = new QLabel(StartupDialogClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 60, 231, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPortNumber = new QSpinBox(StartupDialogClass);
        spinBoxPortNumber->setObjectName("spinBoxPortNumber");
        spinBoxPortNumber->setGeometry(QRect(20, 80, 91, 22));
        spinBoxPortNumber->setMaximum(65535);
        spinBoxPortNumber->setValue(3051);

        retranslateUi(StartupDialogClass);

        QMetaObject::connectSlotsByName(StartupDialogClass);
    } // setupUi

    void retranslateUi(QDialog *StartupDialogClass)
    {
        StartupDialogClass->setWindowTitle(QCoreApplication::translate("StartupDialogClass", "StartupDialog", nullptr));
        label->setText(QCoreApplication::translate("StartupDialogClass", "Host", nullptr));
        label_2->setText(QCoreApplication::translate("StartupDialogClass", "Database file name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("StartupDialogClass", "OK", nullptr));
        label_3->setText(QCoreApplication::translate("StartupDialogClass", "Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartupDialogClass: public Ui_StartupDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPDIALOG_H
