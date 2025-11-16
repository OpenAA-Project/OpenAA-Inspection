/********************************************************************************
** Form generated from reading UI file 'SelectDatabaseForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDATABASEFORM_H
#define UI_SELECTDATABASEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectDatabaseFormClass
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonEdit;

    void setupUi(QDialog *SelectDatabaseFormClass)
    {
        if (SelectDatabaseFormClass->objectName().isEmpty())
            SelectDatabaseFormClass->setObjectName("SelectDatabaseFormClass");
        SelectDatabaseFormClass->resize(421, 252);
        tableWidget = new QTableWidget(SelectDatabaseFormClass);
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
        tableWidget->setGeometry(QRect(10, 10, 321, 192));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOk = new QPushButton(SelectDatabaseFormClass);
        pushButtonOk->setObjectName("pushButtonOk");
        pushButtonOk->setGeometry(QRect(30, 210, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOk->setIcon(icon);
        pushButtonCancel = new QPushButton(SelectDatabaseFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(200, 210, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        pushButtonEdit = new QPushButton(SelectDatabaseFormClass);
        pushButtonEdit->setObjectName("pushButtonEdit");
        pushButtonEdit->setGeometry(QRect(340, 100, 75, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEdit->setIcon(icon2);

        retranslateUi(SelectDatabaseFormClass);

        pushButtonOk->setDefault(true);


        QMetaObject::connectSlotsByName(SelectDatabaseFormClass);
    } // setupUi

    void retranslateUi(QDialog *SelectDatabaseFormClass)
    {
        SelectDatabaseFormClass->setWindowTitle(QCoreApplication::translate("SelectDatabaseFormClass", "SelectDatabaseForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectDatabaseFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectDatabaseFormClass", "IP/Server", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectDatabaseFormClass", "File", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectDatabaseFormClass", "Port", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("SelectDatabaseFormClass", "\351\201\270\346\212\236", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectDatabaseFormClass", "Cancel", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("SelectDatabaseFormClass", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDatabaseFormClass: public Ui_SelectDatabaseFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDATABASEFORM_H
