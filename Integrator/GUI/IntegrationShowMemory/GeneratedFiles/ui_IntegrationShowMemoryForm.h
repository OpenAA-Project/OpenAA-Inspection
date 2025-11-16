/********************************************************************************
** Form generated from reading UI file 'IntegrationShowMemoryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONSHOWMEMORYFORM_H
#define UI_INTEGRATIONSHOWMEMORYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_IntegrationShowMemoryForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *IntegrationShowMemoryForm)
    {
        if (IntegrationShowMemoryForm->objectName().isEmpty())
            IntegrationShowMemoryForm->setObjectName("IntegrationShowMemoryForm");
        IntegrationShowMemoryForm->resize(380, 161);
        tableWidget = new QTableWidget(IntegrationShowMemoryForm);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 4)
            tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 381, 161));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        retranslateUi(IntegrationShowMemoryForm);

        QMetaObject::connectSlotsByName(IntegrationShowMemoryForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationShowMemoryForm)
    {
        IntegrationShowMemoryForm->setWindowTitle(QCoreApplication::translate("IntegrationShowMemoryForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("IntegrationShowMemoryForm", "Page0", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("IntegrationShowMemoryForm", "\344\275\277\347\224\250\347\216\207", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("IntegrationShowMemoryForm", "\347\211\251\347\220\206\343\203\241\343\203\242\343\203\252\343\201\256\347\251\272\343\201\215\345\256\271\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("IntegrationShowMemoryForm", "\343\203\232\343\203\274\343\202\270\343\203\263\343\202\260\343\201\256\347\251\272\343\201\215\345\256\271\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("IntegrationShowMemoryForm", "\344\273\256\346\203\263\343\203\241\343\203\242\343\203\252\343\201\256\347\251\272\343\201\215\345\256\271\351\207\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationShowMemoryForm: public Ui_IntegrationShowMemoryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONSHOWMEMORYFORM_H
