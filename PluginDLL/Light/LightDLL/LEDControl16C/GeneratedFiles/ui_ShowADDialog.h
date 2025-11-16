/********************************************************************************
** Form generated from reading UI file 'ShowADDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWADDIALOG_H
#define UI_SHOWADDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShowADDialog
{
public:
    QComboBox *comboBoxBoardNumber;
    QLabel *label;
    QListWidget *listWidgetADValue;
    QPushButton *pushButtonReqAD;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *ShowADDialog)
    {
        if (ShowADDialog->objectName().isEmpty())
            ShowADDialog->setObjectName("ShowADDialog");
        ShowADDialog->resize(230, 472);
        comboBoxBoardNumber = new QComboBox(ShowADDialog);
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->addItem(QString());
        comboBoxBoardNumber->setObjectName("comboBoxBoardNumber");
        comboBoxBoardNumber->setGeometry(QRect(20, 30, 101, 22));
        label = new QLabel(ShowADDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 81, 16));
        listWidgetADValue = new QListWidget(ShowADDialog);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        new QListWidgetItem(listWidgetADValue);
        listWidgetADValue->setObjectName("listWidgetADValue");
        listWidgetADValue->setGeometry(QRect(20, 60, 101, 361));
        pushButtonReqAD = new QPushButton(ShowADDialog);
        pushButtonReqAD->setObjectName("pushButtonReqAD");
        pushButtonReqAD->setGeometry(QRect(140, 190, 71, 61));
        pushButtonClose = new QPushButton(ShowADDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(70, 430, 93, 31));

        retranslateUi(ShowADDialog);

        QMetaObject::connectSlotsByName(ShowADDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowADDialog)
    {
        ShowADDialog->setWindowTitle(QCoreApplication::translate("ShowADDialog", "Dialog", nullptr));
        comboBoxBoardNumber->setItemText(0, QCoreApplication::translate("ShowADDialog", "0", nullptr));
        comboBoxBoardNumber->setItemText(1, QCoreApplication::translate("ShowADDialog", "1", nullptr));
        comboBoxBoardNumber->setItemText(2, QCoreApplication::translate("ShowADDialog", "2", nullptr));
        comboBoxBoardNumber->setItemText(3, QCoreApplication::translate("ShowADDialog", "3", nullptr));
        comboBoxBoardNumber->setItemText(4, QCoreApplication::translate("ShowADDialog", "4", nullptr));
        comboBoxBoardNumber->setItemText(5, QCoreApplication::translate("ShowADDialog", "5", nullptr));
        comboBoxBoardNumber->setItemText(6, QCoreApplication::translate("ShowADDialog", "6", nullptr));
        comboBoxBoardNumber->setItemText(7, QCoreApplication::translate("ShowADDialog", "7", nullptr));

        label->setText(QCoreApplication::translate("ShowADDialog", "Board No", nullptr));

        const bool __sortingEnabled = listWidgetADValue->isSortingEnabled();
        listWidgetADValue->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetADValue->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("ShowADDialog", "0", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidgetADValue->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("ShowADDialog", "1", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidgetADValue->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("ShowADDialog", "2", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidgetADValue->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("ShowADDialog", "3", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidgetADValue->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("ShowADDialog", "4", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidgetADValue->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("ShowADDialog", "5", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidgetADValue->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("ShowADDialog", "6", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidgetADValue->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("ShowADDialog", "7", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidgetADValue->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("ShowADDialog", "8", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidgetADValue->item(9);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("ShowADDialog", "9", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidgetADValue->item(10);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("ShowADDialog", "10", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidgetADValue->item(11);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("ShowADDialog", "11", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidgetADValue->item(12);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("ShowADDialog", "12", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidgetADValue->item(13);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("ShowADDialog", "13", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidgetADValue->item(14);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("ShowADDialog", "14", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidgetADValue->item(15);
        ___qlistwidgetitem15->setText(QCoreApplication::translate("ShowADDialog", "15", nullptr));
        listWidgetADValue->setSortingEnabled(__sortingEnabled);

        pushButtonReqAD->setText(QCoreApplication::translate("ShowADDialog", "Req AD", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowADDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowADDialog: public Ui_ShowADDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWADDIALOG_H
