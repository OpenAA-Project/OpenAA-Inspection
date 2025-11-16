/********************************************************************************
** Form generated from reading UI file 'ListboxErrorMessageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTBOXERRORMESSAGEFORM_H
#define UI_LISTBOXERRORMESSAGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListboxErrorMessageFormClass
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonClear;
    QLineEdit *lineEditCount;
    QLabel *label;
    QTableWidget *tableWidgetPageStatus;
    QPushButton *pushButtonUpdate;

    void setupUi(GUIFormBase *ListboxErrorMessageFormClass)
    {
        if (ListboxErrorMessageFormClass->objectName().isEmpty())
            ListboxErrorMessageFormClass->setObjectName("ListboxErrorMessageFormClass");
        ListboxErrorMessageFormClass->resize(411, 212);
        tableWidget = new QTableWidget(ListboxErrorMessageFormClass);
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
        tableWidget->setGeometry(QRect(0, 0, 411, 101));
        pushButtonClear = new QPushButton(ListboxErrorMessageFormClass);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(40, 110, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClear->setIcon(icon);
        lineEditCount = new QLineEdit(ListboxErrorMessageFormClass);
        lineEditCount->setObjectName("lineEditCount");
        lineEditCount->setGeometry(QRect(332, 110, 61, 20));
        label = new QLabel(ListboxErrorMessageFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(270, 110, 50, 21));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tableWidgetPageStatus = new QTableWidget(ListboxErrorMessageFormClass);
        if (tableWidgetPageStatus->columnCount() < 4)
            tableWidgetPageStatus->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetPageStatus->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetPageStatus->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetPageStatus->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetPageStatus->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        if (tableWidgetPageStatus->rowCount() < 1)
            tableWidgetPageStatus->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetPageStatus->setVerticalHeaderItem(0, __qtablewidgetitem9);
        tableWidgetPageStatus->setObjectName("tableWidgetPageStatus");
        tableWidgetPageStatus->setGeometry(QRect(0, 140, 411, 55));
        tableWidgetPageStatus->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetPageStatus->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetPageStatus->setAutoScroll(true);
        tableWidgetPageStatus->verticalHeader()->setDefaultSectionSize(30);
        pushButtonUpdate = new QPushButton(ListboxErrorMessageFormClass);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(180, 110, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon1);

        retranslateUi(ListboxErrorMessageFormClass);

        QMetaObject::connectSlotsByName(ListboxErrorMessageFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ListboxErrorMessageFormClass)
    {
        ListboxErrorMessageFormClass->setWindowTitle(QCoreApplication::translate("ListboxErrorMessageFormClass", "ListboxErrorMessageForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Date/Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Level", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Message", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Clear", nullptr));
        label->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "\345\200\213\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetPageStatus->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Page0", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetPageStatus->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Page1", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetPageStatus->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Page2", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetPageStatus->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "Page3", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("ListboxErrorMessageFormClass", "\346\233\264\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListboxErrorMessageFormClass: public Ui_ListboxErrorMessageFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTBOXERRORMESSAGEFORM_H
