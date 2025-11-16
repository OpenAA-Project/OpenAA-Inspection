/********************************************************************************
** Form generated from reading UI file 'SetLevelTableDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETLEVELTABLEDIALOG_H
#define UI_SETLEVELTABLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SetLevelTableDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSaveClose;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SetLevelTableDialog)
    {
        if (SetLevelTableDialog->objectName().isEmpty())
            SetLevelTableDialog->setObjectName("SetLevelTableDialog");
        SetLevelTableDialog->resize(858, 425);
        tableWidget = new QTableWidget(SetLevelTableDialog);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
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
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 0, 841, 361));
        pushButtonSaveClose = new QPushButton(SetLevelTableDialog);
        pushButtonSaveClose->setObjectName("pushButtonSaveClose");
        pushButtonSaveClose->setGeometry(QRect(720, 370, 131, 41));
        pushButtonCancel = new QPushButton(SetLevelTableDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(10, 370, 131, 41));

        retranslateUi(SetLevelTableDialog);

        QMetaObject::connectSlotsByName(SetLevelTableDialog);
    } // setupUi

    void retranslateUi(QDialog *SetLevelTableDialog)
    {
        SetLevelTableDialog->setWindowTitle(QCoreApplication::translate("SetLevelTableDialog", "\343\203\254\343\203\231\343\203\253\350\250\255\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SetLevelTableDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SetLevelTableDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SetLevelTableDialog", "\351\240\205\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SetLevelTableDialog", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SetLevelTableDialog", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SetLevelTableDialog", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SetLevelTableDialog", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SetLevelTableDialog", "5", nullptr));
        pushButtonSaveClose->setText(QCoreApplication::translate("SetLevelTableDialog", "\344\277\235\345\255\230\343\201\227\343\201\246\351\226\211\343\201\230\343\202\213", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetLevelTableDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetLevelTableDialog: public Ui_SetLevelTableDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETLEVELTABLEDIALOG_H
