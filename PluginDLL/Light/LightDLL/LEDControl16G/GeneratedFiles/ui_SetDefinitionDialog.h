/********************************************************************************
** Form generated from reading UI file 'SetDefinitionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDEFINITIONDIALOG_H
#define UI_SETDEFINITIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SetDefinitionDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *SetDefinitionDialog)
    {
        if (SetDefinitionDialog->objectName().isEmpty())
            SetDefinitionDialog->setObjectName(QString::fromUtf8("SetDefinitionDialog"));
        SetDefinitionDialog->resize(609, 739);
        tableWidget = new QTableWidget(SetDefinitionDialog);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
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
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 591, 671));
        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButton = new QPushButton(SetDefinitionDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(240, 690, 131, 34));

        retranslateUi(SetDefinitionDialog);

        QMetaObject::connectSlotsByName(SetDefinitionDialog);
    } // setupUi

    void retranslateUi(QDialog *SetDefinitionDialog)
    {
        SetDefinitionDialog->setWindowTitle(QCoreApplication::translate("SetDefinitionDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SetDefinitionDialog", "Board", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SetDefinitionDialog", "LineNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SetDefinitionDialog", "Color", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SetDefinitionDialog", "Max", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SetDefinitionDialog", "Comment", nullptr));
        pushButton->setText(QCoreApplication::translate("SetDefinitionDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetDefinitionDialog: public Ui_SetDefinitionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDEFINITIONDIALOG_H
