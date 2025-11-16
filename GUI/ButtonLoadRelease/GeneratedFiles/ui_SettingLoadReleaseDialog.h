/********************************************************************************
** Form generated from reading UI file 'SettingLoadReleaseDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGLOADRELEASEDIALOG_H
#define UI_SETTINGLOADRELEASEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingLoadReleaseDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QCheckBox *checkBoxMasterBuff;
    QCheckBox *checkBoxTargetBuff;

    void setupUi(QDialog *SettingLoadReleaseDialog)
    {
        if (SettingLoadReleaseDialog->objectName().isEmpty())
            SettingLoadReleaseDialog->setObjectName("SettingLoadReleaseDialog");
        SettingLoadReleaseDialog->resize(332, 536);
        tableWidget = new QTableWidget(SettingLoadReleaseDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 70, 311, 411));
        pushButtonOK = new QPushButton(SettingLoadReleaseDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(110, 490, 112, 34));
        checkBoxMasterBuff = new QCheckBox(SettingLoadReleaseDialog);
        checkBoxMasterBuff->setObjectName("checkBoxMasterBuff");
        checkBoxMasterBuff->setGeometry(QRect(20, 10, 291, 22));
        checkBoxTargetBuff = new QCheckBox(SettingLoadReleaseDialog);
        checkBoxTargetBuff->setObjectName("checkBoxTargetBuff");
        checkBoxTargetBuff->setGeometry(QRect(20, 40, 291, 22));

        retranslateUi(SettingLoadReleaseDialog);

        QMetaObject::connectSlotsByName(SettingLoadReleaseDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingLoadReleaseDialog)
    {
        SettingLoadReleaseDialog->setWindowTitle(QCoreApplication::translate("SettingLoadReleaseDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SettingLoadReleaseDialog", "Mng", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SettingLoadReleaseDialog", "Algorithm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingLoadReleaseDialog", "OK", nullptr));
        checkBoxMasterBuff->setText(QCoreApplication::translate("SettingLoadReleaseDialog", "Master image buffer", nullptr));
        checkBoxTargetBuff->setText(QCoreApplication::translate("SettingLoadReleaseDialog", "Target image buffer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingLoadReleaseDialog: public Ui_SettingLoadReleaseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGLOADRELEASEDIALOG_H
