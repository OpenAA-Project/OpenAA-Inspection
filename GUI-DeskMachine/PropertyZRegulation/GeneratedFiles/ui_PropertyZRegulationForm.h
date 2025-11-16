/********************************************************************************
** Form generated from reading UI file 'PropertyZRegulationForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYZREGULATIONFORM_H
#define UI_PROPERTYZREGULATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyZRegulationFormClass
{
public:
    QTableWidget *tableWidget;
    QLabel *label;
    QPushButton *pushButtonCalc;

    void setupUi(GUIFormBase *PropertyZRegulationFormClass)
    {
        if (PropertyZRegulationFormClass->objectName().isEmpty())
            PropertyZRegulationFormClass->setObjectName(QString::fromUtf8("PropertyZRegulationFormClass"));
        PropertyZRegulationFormClass->resize(430, 573);
        tableWidget = new QTableWidget(PropertyZRegulationFormClass);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
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
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 70, 411, 451));
        label = new QLabel(PropertyZRegulationFormClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 530, 201, 16));
        pushButtonCalc = new QPushButton(PropertyZRegulationFormClass);
        pushButtonCalc->setObjectName(QString::fromUtf8("pushButtonCalc"));
        pushButtonCalc->setGeometry(QRect(10, 10, 411, 51));

        retranslateUi(PropertyZRegulationFormClass);

        QMetaObject::connectSlotsByName(PropertyZRegulationFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyZRegulationFormClass)
    {
        PropertyZRegulationFormClass->setWindowTitle(QCoreApplication::translate("PropertyZRegulationFormClass", "PropertyZRegulationForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "\345\272\247\346\250\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "\347\204\246\347\202\271\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "OK\347\257\204\345\233\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "\350\250\210\346\270\254\345\200\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "\347\265\220\346\236\234", nullptr));
        label->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "\343\203\200\343\203\226\343\203\253\343\202\257\343\203\252\343\203\203\343\202\257\343\201\247\343\202\260\343\203\251\343\203\225\350\241\250\347\244\272", nullptr));
        pushButtonCalc->setText(QCoreApplication::translate("PropertyZRegulationFormClass", "\350\250\210\347\256\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyZRegulationFormClass: public Ui_PropertyZRegulationFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYZREGULATIONFORM_H
