/********************************************************************************
** Form generated from reading UI file 'RealtimeGraphMeasure1Form.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMEGRAPHMEASURE1FORM_H
#define UI_REALTIMEGRAPHMEASURE1FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_RealtimeGraphMeasure1FormClass
{
public:
    QLabel *label;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QTableWidget *tableWidgetBrightness;

    void setupUi(GUIFormBase *RealtimeGraphMeasure1FormClass)
    {
        if (RealtimeGraphMeasure1FormClass->objectName().isEmpty())
            RealtimeGraphMeasure1FormClass->setObjectName("RealtimeGraphMeasure1FormClass");
        RealtimeGraphMeasure1FormClass->resize(781, 160);
        label = new QLabel(RealtimeGraphMeasure1FormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 381, 24));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        tableWidget = new QTableWidget(RealtimeGraphMeasure1FormClass);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 30, 381, 131));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_2 = new QLabel(RealtimeGraphMeasure1FormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(400, 0, 381, 24));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        tableWidgetBrightness = new QTableWidget(RealtimeGraphMeasure1FormClass);
        if (tableWidgetBrightness->columnCount() < 3)
            tableWidgetBrightness->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBrightness->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetBrightness->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetBrightness->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        if (tableWidgetBrightness->rowCount() < 3)
            tableWidgetBrightness->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetBrightness->setVerticalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetBrightness->setVerticalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetBrightness->setVerticalHeaderItem(2, __qtablewidgetitem11);
        tableWidgetBrightness->setObjectName("tableWidgetBrightness");
        tableWidgetBrightness->setGeometry(QRect(400, 30, 381, 131));
        tableWidgetBrightness->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBrightness->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        retranslateUi(RealtimeGraphMeasure1FormClass);

        QMetaObject::connectSlotsByName(RealtimeGraphMeasure1FormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *RealtimeGraphMeasure1FormClass)
    {
        RealtimeGraphMeasure1FormClass->setWindowTitle(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "RealtimeGraphMeasure1Form", nullptr));
        label->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "\347\204\246\347\202\271\343\203\254\343\203\231\343\203\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Left", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Center", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Right", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Top", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Center", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Bottom", nullptr));
        label_2->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "\350\274\235\345\272\246\343\203\254\343\203\231\343\203\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBrightness->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Left", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBrightness->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Center", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetBrightness->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Right", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetBrightness->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Top", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetBrightness->verticalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Center", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetBrightness->verticalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("RealtimeGraphMeasure1FormClass", "Bottom", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RealtimeGraphMeasure1FormClass: public Ui_RealtimeGraphMeasure1FormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMEGRAPHMEASURE1FORM_H
