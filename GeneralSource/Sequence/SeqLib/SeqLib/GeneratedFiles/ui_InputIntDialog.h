/********************************************************************************
** Form generated from reading UI file 'InputIntDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTINTDIALOG_H
#define UI_INPUTINTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_InputIntDialog
{
public:
    QPushButton *pushButtonCancel;
    QSpinBox *spinBox;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *InputIntDialog)
    {
        if (InputIntDialog->objectName().isEmpty())
            InputIntDialog->setObjectName("InputIntDialog");
        InputIntDialog->resize(224, 82);
        pushButtonCancel = new QPushButton(InputIntDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 40, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        spinBox = new QSpinBox(InputIntDialog);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(50, 10, 111, 22));
        spinBox->setMinimum(-99999999);
        spinBox->setMaximum(99999999);
        pushButtonOK = new QPushButton(InputIntDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 40, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(InputIntDialog);

        QMetaObject::connectSlotsByName(InputIntDialog);
    } // setupUi

    void retranslateUi(QDialog *InputIntDialog)
    {
        InputIntDialog->setWindowTitle(QCoreApplication::translate("InputIntDialog", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputIntDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputIntDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputIntDialog: public Ui_InputIntDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTINTDIALOG_H
