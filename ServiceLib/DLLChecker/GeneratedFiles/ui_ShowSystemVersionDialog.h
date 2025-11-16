/********************************************************************************
** Form generated from reading UI file 'ShowSystemVersionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSYSTEMVERSIONDIALOG_H
#define UI_SHOWSYSTEMVERSIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowSystemVersionDialog
{
public:
    QPushButton *pushButtonSaveCSV;
    QPushButton *pushButtonClose;
    QTableWidget *tableWidget;

    void setupUi(QDialog *ShowSystemVersionDialog)
    {
        if (ShowSystemVersionDialog->objectName().isEmpty())
            ShowSystemVersionDialog->setObjectName("ShowSystemVersionDialog");
        ShowSystemVersionDialog->resize(768, 669);
        pushButtonSaveCSV = new QPushButton(ShowSystemVersionDialog);
        pushButtonSaveCSV->setObjectName("pushButtonSaveCSV");
        pushButtonSaveCSV->setGeometry(QRect(90, 630, 75, 31));
        pushButtonClose = new QPushButton(ShowSystemVersionDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(530, 630, 75, 31));
        tableWidget = new QTableWidget(ShowSystemVersionDialog);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 751, 611));

        retranslateUi(ShowSystemVersionDialog);

        QMetaObject::connectSlotsByName(ShowSystemVersionDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowSystemVersionDialog)
    {
        ShowSystemVersionDialog->setWindowTitle(QCoreApplication::translate("ShowSystemVersionDialog", "Show SystemVersion", nullptr));
        pushButtonSaveCSV->setText(QCoreApplication::translate("ShowSystemVersionDialog", "Save CSV", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowSystemVersionDialog", "Close", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowSystemVersionDialog", "DLL", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowSystemVersionDialog", "FileName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowSystemVersionDialog", "Qt version", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowSystemVersionDialog", "Revision", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowSystemVersionDialog", "Regulus", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowSystemVersionDialog", "Match", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowSystemVersionDialog: public Ui_ShowSystemVersionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSYSTEMVERSIONDIALOG_H
