/********************************************************************************
** Form generated from reading UI file 'ForceRebootSettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORCEREBOOTSETTINGDIALOG_H
#define UI_FORCEREBOOTSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ForceRebootSettingDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonAddPartner;
    QPushButton *pushButtonDelPartner;
    QListWidget *listWidget;
    QPushButton *pushButtonAddProgram;
    QPushButton *pushButtonDelProgram;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxOwnPort;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *ForceRebootSettingDialog)
    {
        if (ForceRebootSettingDialog->objectName().isEmpty())
            ForceRebootSettingDialog->setObjectName("ForceRebootSettingDialog");
        ForceRebootSettingDialog->resize(400, 436);
        tableWidget = new QTableWidget(ForceRebootSettingDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 341, 151));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddPartner = new QPushButton(ForceRebootSettingDialog);
        pushButtonAddPartner->setObjectName("pushButtonAddPartner");
        pushButtonAddPartner->setGeometry(QRect(360, 40, 31, 23));
        pushButtonDelPartner = new QPushButton(ForceRebootSettingDialog);
        pushButtonDelPartner->setObjectName("pushButtonDelPartner");
        pushButtonDelPartner->setGeometry(QRect(360, 70, 31, 23));
        listWidget = new QListWidget(ForceRebootSettingDialog);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 190, 341, 131));
        pushButtonAddProgram = new QPushButton(ForceRebootSettingDialog);
        pushButtonAddProgram->setObjectName("pushButtonAddProgram");
        pushButtonAddProgram->setGeometry(QRect(360, 230, 31, 23));
        pushButtonDelProgram = new QPushButton(ForceRebootSettingDialog);
        pushButtonDelProgram->setObjectName("pushButtonDelProgram");
        pushButtonDelProgram->setGeometry(QRect(360, 260, 31, 23));
        label = new QLabel(ForceRebootSettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 170, 341, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ForceRebootSettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 330, 91, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxOwnPort = new QSpinBox(ForceRebootSettingDialog);
        spinBoxOwnPort->setObjectName("spinBoxOwnPort");
        spinBoxOwnPort->setGeometry(QRect(10, 350, 91, 22));
        spinBoxOwnPort->setMaximum(65535);
        pushButtonOK = new QPushButton(ForceRebootSettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 390, 111, 41));
        pushButtonCancel = new QPushButton(ForceRebootSettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(220, 390, 111, 41));

        retranslateUi(ForceRebootSettingDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ForceRebootSettingDialog);
    } // setupUi

    void retranslateUi(QDialog *ForceRebootSettingDialog)
    {
        ForceRebootSettingDialog->setWindowTitle(QCoreApplication::translate("ForceRebootSettingDialog", "Force Reboot Setting", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ForceRebootSettingDialog", "IP/Host", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ForceRebootSettingDialog", "Port", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ForceRebootSettingDialog", "Remark", nullptr));
        pushButtonAddPartner->setText(QCoreApplication::translate("ForceRebootSettingDialog", "+", nullptr));
        pushButtonDelPartner->setText(QCoreApplication::translate("ForceRebootSettingDialog", "-", nullptr));
        pushButtonAddProgram->setText(QCoreApplication::translate("ForceRebootSettingDialog", "+", nullptr));
        pushButtonDelProgram->setText(QCoreApplication::translate("ForceRebootSettingDialog", "-", nullptr));
        label->setText(QCoreApplication::translate("ForceRebootSettingDialog", "Rebooted Programs", nullptr));
        label_2->setText(QCoreApplication::translate("ForceRebootSettingDialog", "Own port", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ForceRebootSettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ForceRebootSettingDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ForceRebootSettingDialog: public Ui_ForceRebootSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORCEREBOOTSETTINGDIALOG_H
