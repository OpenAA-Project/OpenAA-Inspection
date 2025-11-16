/********************************************************************************
** Form generated from reading UI file 'CompressImgeListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPRESSIMGELISTFORM_H
#define UI_COMPRESSIMGELISTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_CompressImgeListFormClass
{
public:
    QPushButton *pushButtonUpdate;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTableWidget *tableWidget;
    QWidget *Scroller;

    void setupUi(GUIFormBase *CompressImgeListFormClass)
    {
        if (CompressImgeListFormClass->objectName().isEmpty())
            CompressImgeListFormClass->setObjectName("CompressImgeListFormClass");
        CompressImgeListFormClass->resize(212, 363);
        pushButtonUpdate = new QPushButton(CompressImgeListFormClass);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(0, 0, 211, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);
        stackedWidget = new QStackedWidget(CompressImgeListFormClass);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 20, 211, 341));
        page = new QWidget();
        page->setObjectName("page");
        tableWidget = new QTableWidget(page);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 211, 340));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget->addWidget(page);
        Scroller = new QWidget();
        Scroller->setObjectName("Scroller");
        stackedWidget->addWidget(Scroller);

        retranslateUi(CompressImgeListFormClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CompressImgeListFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *CompressImgeListFormClass)
    {
        CompressImgeListFormClass->setWindowTitle(QCoreApplication::translate("CompressImgeListFormClass", "CompressImgeListForm", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("CompressImgeListFormClass", "\346\233\264\346\226\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CompressImgeListFormClass", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CompressImgeListFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CompressImgeListFormClass", "Date/Time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CompressImgeListFormClass: public Ui_CompressImgeListFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPRESSIMGELISTFORM_H
