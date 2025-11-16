/********************************************************************************
** Form generated from reading UI file 'SetLanguageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETLANGUAGEFORM_H
#define UI_SETLANGUAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SetLanguageForm
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonDown;
    QPushButton *pushButtonInsertNew;
    QPushButton *pushButtonChange;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SetLanguageForm)
    {
        if (SetLanguageForm->objectName().isEmpty())
            SetLanguageForm->setObjectName("SetLanguageForm");
        SetLanguageForm->resize(600, 268);
        tableWidget = new QTableWidget(SetLanguageForm);
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
        tableWidget->setGeometry(QRect(10, 10, 531, 192));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonUp = new QPushButton(SetLanguageForm);
        pushButtonUp->setObjectName("pushButtonUp");
        pushButtonUp->setGeometry(QRect(550, 60, 41, 31));
        pushButtonDown = new QPushButton(SetLanguageForm);
        pushButtonDown->setObjectName("pushButtonDown");
        pushButtonDown->setGeometry(QRect(550, 140, 41, 31));
        pushButtonInsertNew = new QPushButton(SetLanguageForm);
        pushButtonInsertNew->setObjectName("pushButtonInsertNew");
        pushButtonInsertNew->setGeometry(QRect(50, 222, 91, 31));
        pushButtonChange = new QPushButton(SetLanguageForm);
        pushButtonChange->setObjectName("pushButtonChange");
        pushButtonChange->setGeometry(QRect(170, 222, 91, 31));
        pushButtonDelete = new QPushButton(SetLanguageForm);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(290, 222, 91, 31));
        pushButtonClose = new QPushButton(SetLanguageForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(464, 222, 81, 31));

        retranslateUi(SetLanguageForm);

        QMetaObject::connectSlotsByName(SetLanguageForm);
    } // setupUi

    void retranslateUi(QDialog *SetLanguageForm)
    {
        SetLanguageForm->setWindowTitle(QCoreApplication::translate("SetLanguageForm", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SetLanguageForm", "ColumnNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SetLanguageForm", "Language", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SetLanguageForm", "ExcelFont", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SetLanguageForm", "QtCodec", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("SetLanguageForm", "UP", nullptr));
        pushButtonDown->setText(QCoreApplication::translate("SetLanguageForm", "DOWN", nullptr));
        pushButtonInsertNew->setText(QCoreApplication::translate("SetLanguageForm", "Insert new", nullptr));
        pushButtonChange->setText(QCoreApplication::translate("SetLanguageForm", "Change", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("SetLanguageForm", "Delete", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SetLanguageForm", "Save & Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetLanguageForm: public Ui_SetLanguageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETLANGUAGEFORM_H
