/********************************************************************************
** Form generated from reading UI file 'InputGroupDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTGROUPDIALOG_H
#define UI_INPUTGROUPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputGroupDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditGroupName;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputGroupDialog)
    {
        if (InputGroupDialog->objectName().isEmpty())
            InputGroupDialog->setObjectName("InputGroupDialog");
        InputGroupDialog->resize(247, 103);
        label = new QLabel(InputGroupDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 221, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        lineEditGroupName = new QLineEdit(InputGroupDialog);
        lineEditGroupName->setObjectName("lineEditGroupName");
        lineEditGroupName->setGeometry(QRect(10, 30, 221, 20));
        pushButtonOK = new QPushButton(InputGroupDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 60, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(InputGroupDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(160, 60, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(InputGroupDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputGroupDialog);
    } // setupUi

    void retranslateUi(QDialog *InputGroupDialog)
    {
        InputGroupDialog->setWindowTitle(QCoreApplication::translate("InputGroupDialog", "Input Group", nullptr));
        label->setText(QCoreApplication::translate("InputGroupDialog", "\343\202\260\343\203\253\343\203\274\343\203\227\345\220\215", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputGroupDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputGroupDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputGroupDialog: public Ui_InputGroupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTGROUPDIALOG_H
