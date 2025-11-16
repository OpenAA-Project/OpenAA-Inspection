/********************************************************************************
** Form generated from reading UI file 'SelectTransferHostDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTTRANSFERHOSTDIALOG_H
#define UI_SELECTTRANSFERHOSTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectTransferHostDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectTransferHostDialog)
    {
        if (SelectTransferHostDialog->objectName().isEmpty())
            SelectTransferHostDialog->setObjectName("SelectTransferHostDialog");
        SelectTransferHostDialog->resize(514, 275);
        tableWidget = new QTableWidget(SelectTransferHostDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 491, 211));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SelectTransferHostDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(200, 230, 112, 34));
        pushButtonCancel = new QPushButton(SelectTransferHostDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(390, 230, 112, 34));

        retranslateUi(SelectTransferHostDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectTransferHostDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectTransferHostDialog)
    {
        SelectTransferHostDialog->setWindowTitle(QCoreApplication::translate("SelectTransferHostDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectTransferHostDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectTransferHostDialog", "Host", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectTransferHostDialog", "Port", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectTransferHostDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectTransferHostDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectTransferHostDialog: public Ui_SelectTransferHostDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTTRANSFERHOSTDIALOG_H
