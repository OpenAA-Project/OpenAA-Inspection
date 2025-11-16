/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditWindowMessage;
    QLineEdit *lineEditButtonMessage;
    QLabel *label_2;
    QListWidget *listWidgetIPAddressList;
    QLabel *label_3;
    QPushButton *pushButtonAddIPAddress;
    QPushButton *pushButtonDelIPAddress;
    QPlainTextEdit *plainTextEditExecuteBeforeBooter;
    QLabel *label_4;
    QPlainTextEdit *plainTextEditExecuteAfterBooter;
    QLabel *label_5;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QTableWidget *tableWidgetBeforeBooter;
    QTableWidget *tableWidgetAfterBooter;
    QPushButton *pushButtonAddProgBefore;
    QPushButton *pushButtonDelProgBefore;
    QPushButton *pushButtonAddProgAfter;
    QPushButton *pushButtonDelProgAfter;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(418, 688);
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 381, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditWindowMessage = new QLineEdit(SettingDialog);
        lineEditWindowMessage->setObjectName("lineEditWindowMessage");
        lineEditWindowMessage->setGeometry(QRect(20, 40, 381, 20));
        lineEditButtonMessage = new QLineEdit(SettingDialog);
        lineEditButtonMessage->setObjectName("lineEditButtonMessage");
        lineEditButtonMessage->setGeometry(QRect(20, 90, 381, 20));
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 70, 381, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        listWidgetIPAddressList = new QListWidget(SettingDialog);
        new QListWidgetItem(listWidgetIPAddressList);
        listWidgetIPAddressList->setObjectName("listWidgetIPAddressList");
        listWidgetIPAddressList->setGeometry(QRect(20, 140, 271, 111));
        label_3 = new QLabel(SettingDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 120, 381, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        pushButtonAddIPAddress = new QPushButton(SettingDialog);
        pushButtonAddIPAddress->setObjectName("pushButtonAddIPAddress");
        pushButtonAddIPAddress->setGeometry(QRect(300, 160, 41, 31));
        pushButtonDelIPAddress = new QPushButton(SettingDialog);
        pushButtonDelIPAddress->setObjectName("pushButtonDelIPAddress");
        pushButtonDelIPAddress->setGeometry(QRect(300, 200, 41, 31));
        plainTextEditExecuteBeforeBooter = new QPlainTextEdit(SettingDialog);
        plainTextEditExecuteBeforeBooter->setObjectName("plainTextEditExecuteBeforeBooter");
        plainTextEditExecuteBeforeBooter->setGeometry(QRect(20, 280, 381, 71));
        label_4 = new QLabel(SettingDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 260, 381, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        plainTextEditExecuteAfterBooter = new QPlainTextEdit(SettingDialog);
        plainTextEditExecuteAfterBooter->setObjectName("plainTextEditExecuteAfterBooter");
        plainTextEditExecuteAfterBooter->setGeometry(QRect(20, 470, 381, 91));
        label_5 = new QLabel(SettingDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 450, 381, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(90, 650, 75, 31));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(260, 650, 75, 31));
        tableWidgetBeforeBooter = new QTableWidget(SettingDialog);
        if (tableWidgetBeforeBooter->columnCount() < 2)
            tableWidgetBeforeBooter->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetBeforeBooter->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetBeforeBooter->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetBeforeBooter->setObjectName("tableWidgetBeforeBooter");
        tableWidgetBeforeBooter->setGeometry(QRect(20, 350, 311, 91));
        tableWidgetBeforeBooter->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBeforeBooter->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetAfterBooter = new QTableWidget(SettingDialog);
        if (tableWidgetAfterBooter->columnCount() < 2)
            tableWidgetAfterBooter->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAfterBooter->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetAfterBooter->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetAfterBooter->setObjectName("tableWidgetAfterBooter");
        tableWidgetAfterBooter->setGeometry(QRect(20, 560, 311, 81));
        tableWidgetAfterBooter->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAfterBooter->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddProgBefore = new QPushButton(SettingDialog);
        pushButtonAddProgBefore->setObjectName("pushButtonAddProgBefore");
        pushButtonAddProgBefore->setGeometry(QRect(340, 360, 41, 31));
        pushButtonDelProgBefore = new QPushButton(SettingDialog);
        pushButtonDelProgBefore->setObjectName("pushButtonDelProgBefore");
        pushButtonDelProgBefore->setGeometry(QRect(340, 400, 41, 31));
        pushButtonAddProgAfter = new QPushButton(SettingDialog);
        pushButtonAddProgAfter->setObjectName("pushButtonAddProgAfter");
        pushButtonAddProgAfter->setGeometry(QRect(340, 570, 41, 31));
        pushButtonDelProgAfter = new QPushButton(SettingDialog);
        pushButtonDelProgAfter->setObjectName("pushButtonDelProgAfter");
        pushButtonDelProgAfter->setGeometry(QRect(340, 610, 41, 31));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Booting window message", nullptr));
        lineEditWindowMessage->setText(QCoreApplication::translate("SettingDialog", "All power ON , then push button", nullptr));
        lineEditButtonMessage->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Button message", nullptr));

        const bool __sortingEnabled = listWidgetIPAddressList->isSortingEnabled();
        listWidgetIPAddressList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetIPAddressList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("SettingDialog", "192.168.0.1", nullptr));
        listWidgetIPAddressList->setSortingEnabled(__sortingEnabled);

        label_3->setText(QCoreApplication::translate("SettingDialog", " IP address List to deliver destination (Remote control)", nullptr));
        pushButtonAddIPAddress->setText(QCoreApplication::translate("SettingDialog", "+", nullptr));
        pushButtonDelIPAddress->setText(QCoreApplication::translate("SettingDialog", "-", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "Execute programs before this booter", nullptr));
        label_5->setText(QCoreApplication::translate("SettingDialog", "Execute programs after this booter", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK & Save", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetBeforeBooter->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SettingDialog", "Program", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBeforeBooter->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SettingDialog", "Parameter", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAfterBooter->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SettingDialog", "Program", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetAfterBooter->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SettingDialog", "Parameter", nullptr));
        pushButtonAddProgBefore->setText(QCoreApplication::translate("SettingDialog", "+", nullptr));
        pushButtonDelProgBefore->setText(QCoreApplication::translate("SettingDialog", "-", nullptr));
        pushButtonAddProgAfter->setText(QCoreApplication::translate("SettingDialog", "+", nullptr));
        pushButtonDelProgAfter->setText(QCoreApplication::translate("SettingDialog", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
