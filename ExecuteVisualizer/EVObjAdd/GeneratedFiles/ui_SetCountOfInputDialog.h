/********************************************************************************
** Form generated from reading UI file 'SetCountOfInputDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETCOUNTOFINPUTDIALOG_H
#define UI_SETCOUNTOFINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SetCountOfInputDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxCountOfInput;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SetCountOfInputDialog)
    {
        if (SetCountOfInputDialog->objectName().isEmpty())
            SetCountOfInputDialog->setObjectName(QString::fromUtf8("SetCountOfInputDialog"));
        SetCountOfInputDialog->resize(114, 113);
        label = new QLabel(SetCountOfInputDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxCountOfInput = new QSpinBox(SetCountOfInputDialog);
        spinBoxCountOfInput->setObjectName(QString::fromUtf8("spinBoxCountOfInput"));
        spinBoxCountOfInput->setGeometry(QRect(10, 30, 91, 22));
        pushButtonOK = new QPushButton(SetCountOfInputDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(10, 60, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonOK->setIcon(icon);

        retranslateUi(SetCountOfInputDialog);

        QMetaObject::connectSlotsByName(SetCountOfInputDialog);
    } // setupUi

    void retranslateUi(QDialog *SetCountOfInputDialog)
    {
        SetCountOfInputDialog->setWindowTitle(QCoreApplication::translate("SetCountOfInputDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SetCountOfInputDialog", "Count of Input ", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetCountOfInputDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetCountOfInputDialog: public Ui_SetCountOfInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCOUNTOFINPUTDIALOG_H
