/********************************************************************************
** Form generated from reading UI file 'SelectMasterNoDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMASTERNODIALOG_H
#define UI_SELECTMASTERNODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectMasterNoDialog
{
public:
    QGroupBox *groupBoxMasterNo;
    QLabel *label;
    QSpinBox *spinBoxMasterNo;
    QGroupBox *groupBoxAlgorithm;
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectMasterNoDialog)
    {
        if (SelectMasterNoDialog->objectName().isEmpty())
            SelectMasterNoDialog->setObjectName("SelectMasterNoDialog");
        SelectMasterNoDialog->resize(570, 475);
        groupBoxMasterNo = new QGroupBox(SelectMasterNoDialog);
        groupBoxMasterNo->setObjectName("groupBoxMasterNo");
        groupBoxMasterNo->setGeometry(QRect(10, 10, 321, 61));
        groupBoxMasterNo->setCheckable(true);
        label = new QLabel(groupBoxMasterNo);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 22, 121, 31));
        spinBoxMasterNo = new QSpinBox(groupBoxMasterNo);
        spinBoxMasterNo->setObjectName("spinBoxMasterNo");
        spinBoxMasterNo->setGeometry(QRect(140, 21, 81, 31));
        groupBoxAlgorithm = new QGroupBox(SelectMasterNoDialog);
        groupBoxAlgorithm->setObjectName("groupBoxAlgorithm");
        groupBoxAlgorithm->setGeometry(QRect(10, 80, 551, 341));
        groupBoxAlgorithm->setCheckable(true);
        groupBoxAlgorithm->setChecked(false);
        tableWidget = new QTableWidget(groupBoxAlgorithm);
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
        tableWidget->setGeometry(QRect(10, 20, 531, 311));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(SelectMasterNoDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 430, 141, 31));
        pushButtonCancel = new QPushButton(SelectMasterNoDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(360, 430, 141, 31));

        retranslateUi(SelectMasterNoDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectMasterNoDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectMasterNoDialog)
    {
        SelectMasterNoDialog->setWindowTitle(QCoreApplication::translate("SelectMasterNoDialog", "Select Master number", nullptr));
        groupBoxMasterNo->setTitle(QCoreApplication::translate("SelectMasterNoDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        label->setText(QCoreApplication::translate("SelectMasterNoDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\347\225\252\345\217\267", nullptr));
        groupBoxAlgorithm->setTitle(QCoreApplication::translate("SelectMasterNoDialog", "\343\202\242\343\203\253\343\202\264\343\203\252\343\202\272\343\203\240\343\201\213\343\202\211\343\201\256\347\224\273\345\203\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectMasterNoDialog", "LibType", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectMasterNoDialog", "DLLRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectMasterNoDialog", "DLLName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectMasterNoDialog", "LibName", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectMasterNoDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectMasterNoDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMasterNoDialog: public Ui_SelectMasterNoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMASTERNODIALOG_H
