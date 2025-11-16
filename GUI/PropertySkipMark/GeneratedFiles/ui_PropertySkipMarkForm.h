/********************************************************************************
** Form generated from reading UI file 'PropertySkipMarkForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYSKIPMARKFORM_H
#define UI_PROPERTYSKIPMARKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_PropertySkipMarkForm
{
public:
    QTableWidget *tableWidgetList;

    void setupUi(GUIFormBase *PropertySkipMarkForm)
    {
        if (PropertySkipMarkForm->objectName().isEmpty())
            PropertySkipMarkForm->setObjectName("PropertySkipMarkForm");
        PropertySkipMarkForm->resize(400, 700);
        tableWidgetList = new QTableWidget(PropertySkipMarkForm);
        if (tableWidgetList->columnCount() < 5)
            tableWidgetList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetList->setObjectName("tableWidgetList");
        tableWidgetList->setGeometry(QRect(10, 10, 381, 681));
        tableWidgetList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PropertySkipMarkForm);

        QMetaObject::connectSlotsByName(PropertySkipMarkForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertySkipMarkForm)
    {
        PropertySkipMarkForm->setWindowTitle(QCoreApplication::translate("PropertySkipMarkForm", "Property SkipMark", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertySkipMarkForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertySkipMarkForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertySkipMarkForm", "Naming", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertySkipMarkForm", "NamingName", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertySkipMarkForm", "NamingID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertySkipMarkForm: public Ui_PropertySkipMarkForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYSKIPMARKFORM_H
