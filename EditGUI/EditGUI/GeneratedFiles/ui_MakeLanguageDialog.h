/********************************************************************************
** Form generated from reading UI file 'MakeLanguageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKELANGUAGEDIALOG_H
#define UI_MAKELANGUAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_MakeLanguageDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonLoadGUILanguageFile;
    QPushButton *pushButtonSaveLanguageExcel;
    QPushButton *pushButtonLoadLanguageExcel;
    QPushButton *pushButtonSaveGUILanguageFile;

    void setupUi(QDialog *MakeLanguageDialog)
    {
        if (MakeLanguageDialog->objectName().isEmpty())
            MakeLanguageDialog->setObjectName("MakeLanguageDialog");
        MakeLanguageDialog->resize(648, 397);
        tableWidget = new QTableWidget(MakeLanguageDialog);
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
        tableWidget->setGeometry(QRect(10, 10, 631, 291));
        pushButtonLoadGUILanguageFile = new QPushButton(MakeLanguageDialog);
        pushButtonLoadGUILanguageFile->setObjectName("pushButtonLoadGUILanguageFile");
        pushButtonLoadGUILanguageFile->setGeometry(QRect(10, 310, 231, 31));
        pushButtonSaveLanguageExcel = new QPushButton(MakeLanguageDialog);
        pushButtonSaveLanguageExcel->setObjectName("pushButtonSaveLanguageExcel");
        pushButtonSaveLanguageExcel->setGeometry(QRect(270, 350, 231, 31));
        pushButtonLoadLanguageExcel = new QPushButton(MakeLanguageDialog);
        pushButtonLoadLanguageExcel->setObjectName("pushButtonLoadLanguageExcel");
        pushButtonLoadLanguageExcel->setGeometry(QRect(10, 350, 231, 31));
        pushButtonSaveGUILanguageFile = new QPushButton(MakeLanguageDialog);
        pushButtonSaveGUILanguageFile->setObjectName("pushButtonSaveGUILanguageFile");
        pushButtonSaveGUILanguageFile->setGeometry(QRect(270, 310, 231, 31));

        retranslateUi(MakeLanguageDialog);

        QMetaObject::connectSlotsByName(MakeLanguageDialog);
    } // setupUi

    void retranslateUi(QDialog *MakeLanguageDialog)
    {
        MakeLanguageDialog->setWindowTitle(QCoreApplication::translate("MakeLanguageDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MakeLanguageDialog", "DLLRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MakeLanguageDialog", "DLLName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MakeLanguageDialog", "DLLInst", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MakeLanguageDialog", "Member", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MakeLanguageDialog", "Text", nullptr));
        pushButtonLoadGUILanguageFile->setText(QCoreApplication::translate("MakeLanguageDialog", "Load GUILanguageFile", nullptr));
        pushButtonSaveLanguageExcel->setText(QCoreApplication::translate("MakeLanguageDialog", "Save GUI Language Excel file", nullptr));
        pushButtonLoadLanguageExcel->setText(QCoreApplication::translate("MakeLanguageDialog", "Load GUI Language Excel file", nullptr));
        pushButtonSaveGUILanguageFile->setText(QCoreApplication::translate("MakeLanguageDialog", "Save GUILanguageFile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeLanguageDialog: public Ui_MakeLanguageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKELANGUAGEDIALOG_H
