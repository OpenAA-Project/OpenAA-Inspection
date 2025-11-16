/********************************************************************************
** Form generated from reading UI file 'ErrorMessageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORMESSAGEDIALOG_H
#define UI_ERRORMESSAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ErrorMessageDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *ErrorMessageDialog)
    {
        if (ErrorMessageDialog->objectName().isEmpty())
            ErrorMessageDialog->setObjectName("ErrorMessageDialog");
        ErrorMessageDialog->resize(400, 242);
        tableWidget = new QTableWidget(ErrorMessageDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 401, 192));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(ErrorMessageDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(160, 200, 81, 31));

        retranslateUi(ErrorMessageDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ErrorMessageDialog);
    } // setupUi

    void retranslateUi(QDialog *ErrorMessageDialog)
    {
        ErrorMessageDialog->setWindowTitle(QCoreApplication::translate("ErrorMessageDialog", "Error Message", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ErrorMessageDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ErrorMessageDialog", "Message", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ErrorMessageDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ErrorMessageDialog: public Ui_ErrorMessageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORMESSAGEDIALOG_H
