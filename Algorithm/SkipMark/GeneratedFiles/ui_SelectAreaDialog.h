/********************************************************************************
** Form generated from reading UI file 'SelectAreaDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTAREADIALOG_H
#define UI_SELECTAREADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectAreaDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectAreaDialog)
    {
        if (SelectAreaDialog->objectName().isEmpty())
            SelectAreaDialog->setObjectName("SelectAreaDialog");
        SelectAreaDialog->resize(323, 311);
        tableWidget = new QTableWidget(SelectAreaDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 10, 321, 241));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(SelectAreaDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(40, 267, 93, 31));
        pushButtonCancel = new QPushButton(SelectAreaDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(210, 267, 93, 31));

        retranslateUi(SelectAreaDialog);

        QMetaObject::connectSlotsByName(SelectAreaDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectAreaDialog)
    {
        SelectAreaDialog->setWindowTitle(QCoreApplication::translate("SelectAreaDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectAreaDialog", "ItemName", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectAreaDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectAreaDialog", "Position", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectAreaDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectAreaDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectAreaDialog: public Ui_SelectAreaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTAREADIALOG_H
