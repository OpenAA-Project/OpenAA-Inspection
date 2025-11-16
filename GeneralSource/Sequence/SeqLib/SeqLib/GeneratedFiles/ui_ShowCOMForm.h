/********************************************************************************
** Form generated from reading UI file 'ShowCOMForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWCOMFORM_H
#define UI_SHOWCOMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowCOMForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(QWidget *ShowCOMForm)
    {
        if (ShowCOMForm->objectName().isEmpty())
            ShowCOMForm->setObjectName("ShowCOMForm");
        ShowCOMForm->resize(533, 414);
        tableWidget = new QTableWidget(ShowCOMForm);
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
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 531, 411));

        retranslateUi(ShowCOMForm);

        QMetaObject::connectSlotsByName(ShowCOMForm);
    } // setupUi

    void retranslateUi(QWidget *ShowCOMForm)
    {
        ShowCOMForm->setWindowTitle(QCoreApplication::translate("ShowCOMForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowCOMForm", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowCOMForm", "Send(Bin)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowCOMForm", "Send(Text)", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowCOMForm", "Receive(Bin)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowCOMForm", "Receive(Text)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowCOMForm: public Ui_ShowCOMForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCOMFORM_H
