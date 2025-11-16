/********************************************************************************
** Form generated from reading UI file 'ShowIODialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWIODIALOG_H
#define UI_SHOWIODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShowIODialog
{
public:
    QLabel *label;
    QComboBox *comboBoxBoardNumber;
    QCheckBox *checkBoxInput1;
    QCheckBox *checkBoxInput2;
    QPushButton *pushButton;

    void setupUi(QDialog *ShowIODialog)
    {
        if (ShowIODialog->objectName().isEmpty())
            ShowIODialog->setObjectName("ShowIODialog");
        ShowIODialog->resize(134, 179);
        label = new QLabel(ShowIODialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 81, 16));
        comboBoxBoardNumber = new QComboBox(ShowIODialog);
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->setObjectName("comboBoxBoardNumber");
        comboBoxBoardNumber->setGeometry(QRect(10, 30, 101, 22));
        checkBoxInput1 = new QCheckBox(ShowIODialog);
        checkBoxInput1->setObjectName("checkBoxInput1");
        checkBoxInput1->setGeometry(QRect(30, 60, 108, 22));
        checkBoxInput2 = new QCheckBox(ShowIODialog);
        checkBoxInput2->setObjectName("checkBoxInput2");
        checkBoxInput2->setGeometry(QRect(30, 90, 108, 22));
        pushButton = new QPushButton(ShowIODialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 130, 112, 34));

        retranslateUi(ShowIODialog);

        QMetaObject::connectSlotsByName(ShowIODialog);
    } // setupUi

    void retranslateUi(QDialog *ShowIODialog)
    {
        ShowIODialog->setWindowTitle(QCoreApplication::translate("ShowIODialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ShowIODialog", "Board No", nullptr));
        comboBoxBoardNumber->setItemText(0, QCoreApplication::translate("ShowIODialog", "0", nullptr));
        comboBoxBoardNumber->setItemText(1, QCoreApplication::translate("ShowIODialog", "1", nullptr));
        comboBoxBoardNumber->setItemText(2, QCoreApplication::translate("ShowIODialog", "2", nullptr));
        comboBoxBoardNumber->setItemText(3, QCoreApplication::translate("ShowIODialog", "3", nullptr));
        comboBoxBoardNumber->setItemText(4, QCoreApplication::translate("ShowIODialog", "4", nullptr));
        comboBoxBoardNumber->setItemText(5, QCoreApplication::translate("ShowIODialog", "5", nullptr));
        comboBoxBoardNumber->setItemText(6, QCoreApplication::translate("ShowIODialog", "6", nullptr));
        comboBoxBoardNumber->setItemText(7, QCoreApplication::translate("ShowIODialog", "7", nullptr));

        checkBoxInput1->setText(QCoreApplication::translate("ShowIODialog", "Input 1", nullptr));
        checkBoxInput2->setText(QCoreApplication::translate("ShowIODialog", "Input 2", nullptr));
        pushButton->setText(QCoreApplication::translate("ShowIODialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowIODialog: public Ui_ShowIODialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWIODIALOG_H
