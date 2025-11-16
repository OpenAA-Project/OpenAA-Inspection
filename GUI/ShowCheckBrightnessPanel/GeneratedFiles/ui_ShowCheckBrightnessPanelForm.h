/********************************************************************************
** Form generated from reading UI file 'ShowCheckBrightnessPanelForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWCHECKBRIGHTNESSPANELFORM_H
#define UI_SHOWCHECKBRIGHTNESSPANELFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowCheckBrightnessPanelForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *ShowCheckBrightnessPanelForm)
    {
        if (ShowCheckBrightnessPanelForm->objectName().isEmpty())
            ShowCheckBrightnessPanelForm->setObjectName("ShowCheckBrightnessPanelForm");
        ShowCheckBrightnessPanelForm->resize(402, 51);
        tableWidget = new QTableWidget(ShowCheckBrightnessPanelForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 361, 51));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        retranslateUi(ShowCheckBrightnessPanelForm);

        QMetaObject::connectSlotsByName(ShowCheckBrightnessPanelForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowCheckBrightnessPanelForm)
    {
        ShowCheckBrightnessPanelForm->setWindowTitle(QCoreApplication::translate("ShowCheckBrightnessPanelForm", "Show Check Brightness Panel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowCheckBrightnessPanelForm", "XXX", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowCheckBrightnessPanelForm", "YYY", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowCheckBrightnessPanelForm", "Res", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowCheckBrightnessPanelForm: public Ui_ShowCheckBrightnessPanelForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCHECKBRIGHTNESSPANELFORM_H
