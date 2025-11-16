/********************************************************************************
** Form generated from reading UI file 'PropertyFrameDefForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYFRAMEDEFFORM_H
#define UI_PROPERTYFRAMEDEFFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyFrameDefForm
{
public:
    QTableWidget *tableWidget;
    QToolButton *toolButtonOverlap;

    void setupUi(GUIFormBase *PropertyFrameDefForm)
    {
        if (PropertyFrameDefForm->objectName().isEmpty())
            PropertyFrameDefForm->setObjectName("PropertyFrameDefForm");
        PropertyFrameDefForm->resize(400, 700);
        tableWidget = new QTableWidget(PropertyFrameDefForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 50, 381, 641));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        toolButtonOverlap = new QToolButton(PropertyFrameDefForm);
        toolButtonOverlap->setObjectName("toolButtonOverlap");
        toolButtonOverlap->setGeometry(QRect(50, 10, 311, 31));
        toolButtonOverlap->setCheckable(true);
        toolButtonOverlap->setChecked(true);

        retranslateUi(PropertyFrameDefForm);

        QMetaObject::connectSlotsByName(PropertyFrameDefForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyFrameDefForm)
    {
        PropertyFrameDefForm->setWindowTitle(QCoreApplication::translate("PropertyFrameDefForm", "Property FrameDef", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyFrameDefForm", "GroupNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyFrameDefForm", "FrameNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyFrameDefForm", "Position", nullptr));
        toolButtonOverlap->setText(QCoreApplication::translate("PropertyFrameDefForm", "Overlap", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyFrameDefForm: public Ui_PropertyFrameDefForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYFRAMEDEFFORM_H
