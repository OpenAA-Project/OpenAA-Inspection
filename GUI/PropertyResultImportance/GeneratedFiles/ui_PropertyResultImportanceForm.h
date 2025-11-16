/********************************************************************************
** Form generated from reading UI file 'PropertyResultImportanceForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYRESULTIMPORTANCEFORM_H
#define UI_PROPERTYRESULTIMPORTANCEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyResultImportanceForm
{
public:
    QTableWidget *tableWidgetAreaList;
    QTableWidget *tableWidgetImportanceList;
    QPushButton *pushButtonSelectLines;
    QLabel *label;
    QToolButton *tbImportanceColor;

    void setupUi(GUIFormBase *PropertyResultImportanceForm)
    {
        if (PropertyResultImportanceForm->objectName().isEmpty())
            PropertyResultImportanceForm->setObjectName("PropertyResultImportanceForm");
        PropertyResultImportanceForm->resize(400, 700);
        tableWidgetAreaList = new QTableWidget(PropertyResultImportanceForm);
        if (tableWidgetAreaList->columnCount() < 3)
            tableWidgetAreaList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAreaList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetAreaList->setObjectName("tableWidgetAreaList");
        tableWidgetAreaList->setGeometry(QRect(10, 300, 381, 391));
        tableWidgetAreaList->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetAreaList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetImportanceList = new QTableWidget(PropertyResultImportanceForm);
        if (tableWidgetImportanceList->columnCount() < 2)
            tableWidgetImportanceList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetImportanceList->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetImportanceList->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetImportanceList->setObjectName("tableWidgetImportanceList");
        tableWidgetImportanceList->setGeometry(QRect(10, 10, 381, 191));
        tableWidgetImportanceList->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetImportanceList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelectLines = new QPushButton(PropertyResultImportanceForm);
        pushButtonSelectLines->setObjectName("pushButtonSelectLines");
        pushButtonSelectLines->setGeometry(QRect(100, 210, 211, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelectLines->setIcon(icon);
        label = new QLabel(PropertyResultImportanceForm);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 265, 141, 21));
        tbImportanceColor = new QToolButton(PropertyResultImportanceForm);
        tbImportanceColor->setObjectName("tbImportanceColor");
        tbImportanceColor->setGeometry(QRect(200, 260, 111, 31));

        retranslateUi(PropertyResultImportanceForm);

        QMetaObject::connectSlotsByName(PropertyResultImportanceForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyResultImportanceForm)
    {
        PropertyResultImportanceForm->setWindowTitle(QCoreApplication::translate("PropertyResultImportanceForm", "Property ResultImportance", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAreaList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyResultImportanceForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAreaList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyResultImportanceForm", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAreaList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyResultImportanceForm", "Importance", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetImportanceList->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyResultImportanceForm", "Importance", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetImportanceList->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyResultImportanceForm", "Count", nullptr));
        pushButtonSelectLines->setText(QCoreApplication::translate("PropertyResultImportanceForm", "Select Items with selected line", nullptr));
        label->setText(QCoreApplication::translate("PropertyResultImportanceForm", "Importance Color", nullptr));
        tbImportanceColor->setText(QCoreApplication::translate("PropertyResultImportanceForm", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyResultImportanceForm: public Ui_PropertyResultImportanceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYRESULTIMPORTANCEFORM_H
