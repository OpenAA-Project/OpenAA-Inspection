/********************************************************************************
** Form generated from reading UI file 'LogListDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGLISTDIALOG_H
#define UI_LOGLISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_LogListDialog
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonExcel;

    void setupUi(QDialog *LogListDialog)
    {
        if (LogListDialog->objectName().isEmpty())
            LogListDialog->setObjectName("LogListDialog");
        LogListDialog->resize(1082, 571);
        tableWidget = new QTableWidget(LogListDialog);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 1061, 501));
        frame = new QFrame(LogListDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 500, 1061, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonClose = new QPushButton(frame);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(850, 10, 191, 51));
        pushButtonExcel = new QPushButton(frame);
        pushButtonExcel->setObjectName("pushButtonExcel");
        pushButtonExcel->setGeometry(QRect(10, 10, 191, 51));

        retranslateUi(LogListDialog);

        QMetaObject::connectSlotsByName(LogListDialog);
    } // setupUi

    void retranslateUi(QDialog *LogListDialog)
    {
        LogListDialog->setWindowTitle(QCoreApplication::translate("LogListDialog", "\350\211\262\345\267\256\346\244\234\346\237\273\343\201\256\343\203\210\343\203\254\343\203\263\343\203\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LogListDialog", "\346\231\202\345\210\273", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("LogListDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        pushButtonExcel->setText(QCoreApplication::translate("LogListDialog", "EXCEL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogListDialog: public Ui_LogListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGLISTDIALOG_H
