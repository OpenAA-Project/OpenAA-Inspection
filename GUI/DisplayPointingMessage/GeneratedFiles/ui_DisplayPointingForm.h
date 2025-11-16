/********************************************************************************
** Form generated from reading UI file 'DisplayPointingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYPOINTINGFORM_H
#define UI_DISPLAYPOINTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_DisplayPointingFormClass
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *DisplayPointingFormClass)
    {
        if (DisplayPointingFormClass->objectName().isEmpty())
            DisplayPointingFormClass->setObjectName("DisplayPointingFormClass");
        DisplayPointingFormClass->resize(363, 51);
        tableWidget = new QTableWidget(DisplayPointingFormClass);
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
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 361, 51));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setWordWrap(false);
        tableWidget->setCornerButtonEnabled(false);
        tableWidget->setRowCount(1);

        retranslateUi(DisplayPointingFormClass);

        QMetaObject::connectSlotsByName(DisplayPointingFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *DisplayPointingFormClass)
    {
        DisplayPointingFormClass->setWindowTitle(QCoreApplication::translate("DisplayPointingFormClass", "DisplayPointingForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DisplayPointingFormClass", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DisplayPointingFormClass", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DisplayPointingFormClass", "a", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DisplayPointingFormClass", "b", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DisplayPointingFormClass", "c", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisplayPointingFormClass: public Ui_DisplayPointingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYPOINTINGFORM_H
