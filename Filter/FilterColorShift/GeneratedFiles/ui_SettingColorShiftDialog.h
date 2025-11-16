/********************************************************************************
** Form generated from reading UI file 'SettingColorShiftDialog.ui'
**
** Created: Thu May 24 12:40:13 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGCOLORSHIFTDIALOG_H
#define UI_SETTINGCOLORSHIFTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingColorShiftDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingColorShiftDialog)
    {
        if (SettingColorShiftDialog->objectName().isEmpty())
            SettingColorShiftDialog->setObjectName(QString::fromUtf8("SettingColorShiftDialog"));
        SettingColorShiftDialog->resize(337, 253);
        tableWidget = new QTableWidget(SettingColorShiftDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 311, 192));
        pushButtonOK = new QPushButton(SettingColorShiftDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(60, 210, 81, 31));
        pushButtonCancel = new QPushButton(SettingColorShiftDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(190, 210, 81, 31));

        retranslateUi(SettingColorShiftDialog);

        QMetaObject::connectSlotsByName(SettingColorShiftDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingColorShiftDialog)
    {
        SettingColorShiftDialog->setWindowTitle(QApplication::translate("SettingColorShiftDialog", "Setting", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SettingColorShiftDialog", "\347\253\257\351\203\250\343\201\247\343\201\256\350\211\262\343\201\232\343\202\214\343\203\211\343\203\203\343\203\210\346\225\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SettingColorShiftDialog", "\350\243\234\346\255\243\345\274\267\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("SettingColorShiftDialog", "Layer0", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("SettingColorShiftDialog", "1", 0, QApplication::UnicodeUTF8));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButtonOK->setText(QApplication::translate("SettingColorShiftDialog", "OK", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("SettingColorShiftDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingColorShiftDialog: public Ui_SettingColorShiftDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGCOLORSHIFTDIALOG_H
