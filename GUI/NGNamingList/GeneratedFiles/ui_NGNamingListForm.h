/********************************************************************************
** Form generated from reading UI file 'NGNamingListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NGNAMINGLISTFORM_H
#define UI_NGNAMINGLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_NGNamingListFormClass
{
public:
    QTableWidget *tableWidget;
    QFrame *frameAmount;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(GUIFormBase *NGNamingListFormClass)
    {
        if (NGNamingListFormClass->objectName().isEmpty())
            NGNamingListFormClass->setObjectName("NGNamingListFormClass");
        NGNamingListFormClass->resize(202, 304);
        tableWidget = new QTableWidget(NGNamingListFormClass);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 201, 281));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameAmount = new QFrame(NGNamingListFormClass);
        frameAmount->setObjectName("frameAmount");
        frameAmount->setGeometry(QRect(0, 280, 201, 25));
        frameAmount->setFrameShape(QFrame::StyledPanel);
        frameAmount->setFrameShadow(QFrame::Raised);
        label = new QLabel(frameAmount);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 131, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit = new QLineEdit(frameAmount);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(130, 0, 61, 20));
        lineEdit->setMaxLength(10);
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit->setReadOnly(true);

        retranslateUi(NGNamingListFormClass);

        QMetaObject::connectSlotsByName(NGNamingListFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *NGNamingListFormClass)
    {
        NGNamingListFormClass->setWindowTitle(QCoreApplication::translate("NGNamingListFormClass", "NGNamingListForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("NGNamingListFormClass", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("NGNamingListFormClass", "Area", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("NGNamingListFormClass", "NG", nullptr));
        label->setText(QCoreApplication::translate("NGNamingListFormClass", "NG\343\202\250\343\203\252\343\202\242\345\220\210\350\250\210\346\225\260", nullptr));
        lineEdit->setText(QCoreApplication::translate("NGNamingListFormClass", "12345678", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NGNamingListFormClass: public Ui_NGNamingListFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NGNAMINGLISTFORM_H
