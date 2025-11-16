/********************************************************************************
** Form generated from reading UI file 'SettingArrayShiftMulInPageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGARRAYSHIFTMULINPAGEDIALOG_H
#define UI_SETTINGARRAYSHIFTMULINPAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingArrayShiftMulInPageDialog
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QToolButton *toolButtonOK;
    QToolButton *toolButtonCancel;

    void setupUi(QDialog *SettingArrayShiftMulInPageDialog)
    {
        if (SettingArrayShiftMulInPageDialog->objectName().isEmpty())
            SettingArrayShiftMulInPageDialog->setObjectName("SettingArrayShiftMulInPageDialog");
        SettingArrayShiftMulInPageDialog->resize(645, 402);
        tableWidget = new QTableWidget(SettingArrayShiftMulInPageDialog);
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
        tableWidget->setGeometry(QRect(0, 0, 641, 351));
        frame = new QFrame(SettingArrayShiftMulInPageDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 350, 641, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonOK = new QToolButton(frame);
        toolButtonOK->setObjectName("toolButtonOK");
        toolButtonOK->setGeometry(QRect(80, 10, 91, 31));
        toolButtonCancel = new QToolButton(frame);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(500, 10, 101, 31));

        retranslateUi(SettingArrayShiftMulInPageDialog);

        QMetaObject::connectSlotsByName(SettingArrayShiftMulInPageDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingArrayShiftMulInPageDialog)
    {
        SettingArrayShiftMulInPageDialog->setWindowTitle(QCoreApplication::translate("SettingArrayShiftMulInPageDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SettingArrayShiftMulInPageDialog", "Page-Side", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SettingArrayShiftMulInPageDialog", "a[0]", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SettingArrayShiftMulInPageDialog", "a[1]", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SettingArrayShiftMulInPageDialog", "a[2]", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SettingArrayShiftMulInPageDialog", "a[3]", nullptr));
        toolButtonOK->setText(QCoreApplication::translate("SettingArrayShiftMulInPageDialog", "OK", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("SettingArrayShiftMulInPageDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingArrayShiftMulInPageDialog: public Ui_SettingArrayShiftMulInPageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGARRAYSHIFTMULINPAGEDIALOG_H
