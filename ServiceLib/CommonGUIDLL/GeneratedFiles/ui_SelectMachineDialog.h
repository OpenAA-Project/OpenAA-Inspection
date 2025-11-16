/********************************************************************************
** Form generated from reading UI file 'SelectMachineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMACHINEDIALOG_H
#define UI_SELECTMACHINEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectMachineDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SelectMachineDialog)
    {
        if (SelectMachineDialog->objectName().isEmpty())
            SelectMachineDialog->setObjectName("SelectMachineDialog");
        SelectMachineDialog->resize(321, 207);
        tableWidget = new QTableWidget(SelectMachineDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 301, 151));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonCancel = new QPushButton(SelectMachineDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(180, 170, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonOK = new QPushButton(SelectMachineDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 170, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(SelectMachineDialog);

        QMetaObject::connectSlotsByName(SelectMachineDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectMachineDialog)
    {
        SelectMachineDialog->setWindowTitle(QCoreApplication::translate("SelectMachineDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectMachineDialog", "Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectMachineDialog", "Name", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectMachineDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectMachineDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMachineDialog: public Ui_SelectMachineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMACHINEDIALOG_H
