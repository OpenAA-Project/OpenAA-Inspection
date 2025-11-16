/********************************************************************************
** Form generated from reading UI file 'InputBoolDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTBOOLDIALOG_H
#define UI_INPUTBOOLDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputBoolDialog
{
public:
    QPushButton *pushButtonCancel;
    QCheckBox *checkBox;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *InputBoolDialog)
    {
        if (InputBoolDialog->objectName().isEmpty())
            InputBoolDialog->setObjectName("InputBoolDialog");
        InputBoolDialog->resize(220, 84);
        pushButtonCancel = new QPushButton(InputBoolDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 40, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        checkBox = new QCheckBox(InputBoolDialog);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(105, 10, 81, 21));
        checkBox->setChecked(false);
        pushButtonOK = new QPushButton(InputBoolDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 40, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(InputBoolDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputBoolDialog);
    } // setupUi

    void retranslateUi(QDialog *InputBoolDialog)
    {
        InputBoolDialog->setWindowTitle(QCoreApplication::translate("InputBoolDialog", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputBoolDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputBoolDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputBoolDialog: public Ui_InputBoolDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTBOOLDIALOG_H
