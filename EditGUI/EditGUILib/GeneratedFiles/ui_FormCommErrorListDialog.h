/********************************************************************************
** Form generated from reading UI file 'FormCommErrorListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCOMMERRORLISTDIALOG_H
#define UI_FORMCOMMERRORLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_FormCommErrorListDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonSave;

    void setupUi(QDialog *FormCommErrorListDialog)
    {
        if (FormCommErrorListDialog->objectName().isEmpty())
            FormCommErrorListDialog->setObjectName("FormCommErrorListDialog");
        FormCommErrorListDialog->resize(1038, 520);
        tableWidget = new QTableWidget(FormCommErrorListDialog);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 1021, 461));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(FormCommErrorListDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(440, 480, 151, 31));
        pushButtonClear = new QPushButton(FormCommErrorListDialog);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(939, 480, 91, 31));
        pushButtonSave = new QPushButton(FormCommErrorListDialog);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(840, 480, 91, 31));

        retranslateUi(FormCommErrorListDialog);

        QMetaObject::connectSlotsByName(FormCommErrorListDialog);
    } // setupUi

    void retranslateUi(QDialog *FormCommErrorListDialog)
    {
        FormCommErrorListDialog->setWindowTitle(QCoreApplication::translate("FormCommErrorListDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("FormCommErrorListDialog", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("FormCommErrorListDialog", "SlaveNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("FormCommErrorListDialog", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("FormCommErrorListDialog", "ClassName", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("FormCommErrorListDialog", "OK", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("FormCommErrorListDialog", "Clear", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("FormCommErrorListDialog", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormCommErrorListDialog: public Ui_FormCommErrorListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCOMMERRORLISTDIALOG_H
