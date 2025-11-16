/********************************************************************************
** Form generated from reading UI file 'PropertyOCRForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYOCRFORM_H
#define UI_PROPERTYOCRFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyOCRForm
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonTest;
    QLineEdit *lineEditResult;
    QLabel *labelResultMatch;

    void setupUi(GUIFormBase *PropertyOCRForm)
    {
        if (PropertyOCRForm->objectName().isEmpty())
            PropertyOCRForm->setObjectName("PropertyOCRForm");
        PropertyOCRForm->resize(400, 700);
        tableWidget = new QTableWidget(PropertyOCRForm);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 381, 571));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonTest = new QPushButton(PropertyOCRForm);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(120, 590, 141, 41));
        lineEditResult = new QLineEdit(PropertyOCRForm);
        lineEditResult->setObjectName("lineEditResult");
        lineEditResult->setGeometry(QRect(20, 640, 281, 24));
        labelResultMatch = new QLabel(PropertyOCRForm);
        labelResultMatch->setObjectName("labelResultMatch");
        labelResultMatch->setGeometry(QRect(310, 640, 75, 21));

        retranslateUi(PropertyOCRForm);

        QMetaObject::connectSlotsByName(PropertyOCRForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyOCRForm)
    {
        PropertyOCRForm->setWindowTitle(QCoreApplication::translate("PropertyOCRForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyOCRForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyOCRForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyOCRForm", "ItemName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyOCRForm", "Type", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("PropertyOCRForm", "Test", nullptr));
        labelResultMatch->setText(QCoreApplication::translate("PropertyOCRForm", "Match", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyOCRForm: public Ui_PropertyOCRForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYOCRFORM_H
