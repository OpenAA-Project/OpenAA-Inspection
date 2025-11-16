/********************************************************************************
** Form generated from reading UI file 'AlgorithmItemPropertyGrid.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGORITHMITEMPROPERTYGRID_H
#define UI_ALGORITHMITEMPROPERTYGRID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlgorithmItemPropertyGrid
{
public:
    QTableWidget *tableWidget;

    void setupUi(QWidget *AlgorithmItemPropertyGrid)
    {
        if (AlgorithmItemPropertyGrid->objectName().isEmpty())
            AlgorithmItemPropertyGrid->setObjectName("AlgorithmItemPropertyGrid");
        AlgorithmItemPropertyGrid->resize(317, 217);
        tableWidget = new QTableWidget(AlgorithmItemPropertyGrid);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 291, 192));

        retranslateUi(AlgorithmItemPropertyGrid);

        QMetaObject::connectSlotsByName(AlgorithmItemPropertyGrid);
    } // setupUi

    void retranslateUi(QWidget *AlgorithmItemPropertyGrid)
    {
        AlgorithmItemPropertyGrid->setWindowTitle(QCoreApplication::translate("AlgorithmItemPropertyGrid", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AlgorithmItemPropertyGrid", "Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AlgorithmItemPropertyGrid", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AlgorithmItemPropertyGrid", "Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlgorithmItemPropertyGrid: public Ui_AlgorithmItemPropertyGrid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGORITHMITEMPROPERTYGRID_H
