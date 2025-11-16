/********************************************************************************
** Form generated from reading UI file 'SelectChangeableDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCHANGEABLEDIALOG_H
#define UI_SELECTCHANGEABLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectChangeableDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectChangeableDialog)
    {
        if (SelectChangeableDialog->objectName().isEmpty())
            SelectChangeableDialog->setObjectName("SelectChangeableDialog");
        SelectChangeableDialog->resize(291, 232);
        tableWidget = new QTableWidget(SelectChangeableDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 291, 161));
        pushButtonOK = new QPushButton(SelectChangeableDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 180, 93, 28));
        pushButtonCancel = new QPushButton(SelectChangeableDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(170, 180, 93, 28));

        retranslateUi(SelectChangeableDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectChangeableDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectChangeableDialog)
    {
        SelectChangeableDialog->setWindowTitle(QCoreApplication::translate("SelectChangeableDialog", "VIaibleDialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectChangeableDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectChangeableDialog", "Visible", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectChangeableDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectChangeableDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectChangeableDialog: public Ui_SelectChangeableDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCHANGEABLEDIALOG_H
