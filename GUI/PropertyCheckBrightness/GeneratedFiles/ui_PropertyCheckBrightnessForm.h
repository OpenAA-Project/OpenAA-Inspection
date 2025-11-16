/********************************************************************************
** Form generated from reading UI file 'PropertyCheckBrightnessForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYCHECKBRIGHTNESSFORM_H
#define UI_PROPERTYCHECKBRIGHTNESSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyCheckBrightnessForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *PropertyCheckBrightnessForm)
    {
        if (PropertyCheckBrightnessForm->objectName().isEmpty())
            PropertyCheckBrightnessForm->setObjectName("PropertyCheckBrightnessForm");
        PropertyCheckBrightnessForm->resize(381, 589);
        tableWidget = new QTableWidget(PropertyCheckBrightnessForm);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
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
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 361, 571));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PropertyCheckBrightnessForm);

        QMetaObject::connectSlotsByName(PropertyCheckBrightnessForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyCheckBrightnessForm)
    {
        PropertyCheckBrightnessForm->setWindowTitle(QCoreApplication::translate("PropertyCheckBrightnessForm", "Property CheckBrightness", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyCheckBrightnessForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyCheckBrightnessForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyCheckBrightnessForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyCheckBrightnessForm", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyCheckBrightnessForm", "Condition", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyCheckBrightnessForm", "L", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyCheckBrightnessForm", "H", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyCheckBrightnessForm: public Ui_PropertyCheckBrightnessForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYCHECKBRIGHTNESSFORM_H
