/********************************************************************************
** Form generated from reading UI file 'ShowResultImageCheckerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULTIMAGECHECKERFORM_H
#define UI_SHOWRESULTIMAGECHECKERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowResultImageCheckerFormClass
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonUpdate;

    void setupUi(GUIFormBase *ShowResultImageCheckerFormClass)
    {
        if (ShowResultImageCheckerFormClass->objectName().isEmpty())
            ShowResultImageCheckerFormClass->setObjectName("ShowResultImageCheckerFormClass");
        ShowResultImageCheckerFormClass->resize(495, 108);
        tableWidget = new QTableWidget(ShowResultImageCheckerFormClass);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 30, 491, 71));
        tableWidget->setRowCount(1);
        tableWidget->setColumnCount(1);
        pushButtonUpdate = new QPushButton(ShowResultImageCheckerFormClass);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(170, 0, 151, 23));

        retranslateUi(ShowResultImageCheckerFormClass);

        QMetaObject::connectSlotsByName(ShowResultImageCheckerFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowResultImageCheckerFormClass)
    {
        ShowResultImageCheckerFormClass->setWindowTitle(QCoreApplication::translate("ShowResultImageCheckerFormClass", "ShowResultImageCheckerForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowResultImageCheckerFormClass", "\345\256\237\346\270\254/\345\210\244\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowResultImageCheckerFormClass", "\347\205\247\346\230\216\347\205\247\345\272\246", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("ShowResultImageCheckerFormClass", "\346\233\264\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowResultImageCheckerFormClass: public Ui_ShowResultImageCheckerFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULTIMAGECHECKERFORM_H
