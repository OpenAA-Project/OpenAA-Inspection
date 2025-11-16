/********************************************************************************
** Form generated from reading UI file 'PropertyPartialImagingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYPARTIALIMAGINGFORM_H
#define UI_PROPERTYPARTIALIMAGINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyPartialImagingForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *PropertyPartialImagingForm)
    {
        if (PropertyPartialImagingForm->objectName().isEmpty())
            PropertyPartialImagingForm->setObjectName("PropertyPartialImagingForm");
        PropertyPartialImagingForm->resize(400, 440);
        tableWidget = new QTableWidget(PropertyPartialImagingForm);
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
        tableWidget->setGeometry(QRect(10, 10, 381, 421));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PropertyPartialImagingForm);

        QMetaObject::connectSlotsByName(PropertyPartialImagingForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyPartialImagingForm)
    {
        PropertyPartialImagingForm->setWindowTitle(QCoreApplication::translate("PropertyPartialImagingForm", "Property PartialImaging", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyPartialImagingForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyPartialImagingForm", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyPartialImagingForm", "ItemName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyPartialImagingForm", "Priority", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyPartialImagingForm", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyPartialImagingForm: public Ui_PropertyPartialImagingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYPARTIALIMAGINGFORM_H
