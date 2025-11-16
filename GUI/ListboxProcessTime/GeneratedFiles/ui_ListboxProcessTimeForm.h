/********************************************************************************
** Form generated from reading UI file 'ListboxProcessTimeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTBOXPROCESSTIMEFORM_H
#define UI_LISTBOXPROCESSTIMEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListboxProcessTimeFormClass
{
public:
    QTableWidget *tableWidget;
    QTableWidget *tableWidgetAlgorithm;
    QFrame *frameBottom;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonView;

    void setupUi(GUIFormBase *ListboxProcessTimeFormClass)
    {
        if (ListboxProcessTimeFormClass->objectName().isEmpty())
            ListboxProcessTimeFormClass->setObjectName("ListboxProcessTimeFormClass");
        ListboxProcessTimeFormClass->resize(272, 629);
        tableWidget = new QTableWidget(ListboxProcessTimeFormClass);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 12)
            tableWidget->setRowCount(12);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem12);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 190, 271, 391));
        tableWidgetAlgorithm = new QTableWidget(ListboxProcessTimeFormClass);
        if (tableWidgetAlgorithm->columnCount() < 2)
            tableWidgetAlgorithm->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        tableWidgetAlgorithm->setObjectName("tableWidgetAlgorithm");
        tableWidgetAlgorithm->setGeometry(QRect(0, 1, 271, 191));
        tableWidgetAlgorithm->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAlgorithm->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameBottom = new QFrame(ListboxProcessTimeFormClass);
        frameBottom->setObjectName("frameBottom");
        frameBottom->setGeometry(QRect(0, 580, 271, 51));
        frameBottom->setFrameShape(QFrame::StyledPanel);
        frameBottom->setFrameShadow(QFrame::Raised);
        pushButtonClear = new QPushButton(frameBottom);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(130, 10, 131, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClear->setIcon(icon);
        pushButtonView = new QPushButton(frameBottom);
        pushButtonView->setObjectName("pushButtonView");
        pushButtonView->setGeometry(QRect(10, 10, 111, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ListView.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonView->setIcon(icon1);

        retranslateUi(ListboxProcessTimeFormClass);

        QMetaObject::connectSlotsByName(ListboxProcessTimeFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ListboxProcessTimeFormClass)
    {
        ListboxProcessTimeFormClass->setWindowTitle(QCoreApplication::translate("ListboxProcessTimeFormClass", "ListboxProcessTimeForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "Page0", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "Filter", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "InitialAfterEdit", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "StartByInspection", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "PreAlignment", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "Alignment", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "PreProcessing", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "Processing", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "PostProcessing", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "PreScanning", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "Scanning", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "PostScanning", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "Total process time", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetAlgorithm->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetAlgorithm->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "Name", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "Clear", nullptr));
        pushButtonView->setText(QCoreApplication::translate("ListboxProcessTimeFormClass", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListboxProcessTimeFormClass: public Ui_ListboxProcessTimeFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTBOXPROCESSTIMEFORM_H
