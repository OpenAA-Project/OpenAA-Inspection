/********************************************************************************
** Form generated from reading UI file 'WatchdogRebooter.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WATCHDOGREBOOTER_H
#define UI_WATCHDOGREBOOTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WatchdogRebooterClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QFrame *frame;
    QPushButton *pushButtonDeleteProgram;
    QPushButton *pushButtonAddProgram;
    QPushButton *pushButtonClose;
    QTableWidget *tableWidgetLog;

    void setupUi(QMainWindow *WatchdogRebooterClass)
    {
        if (WatchdogRebooterClass->objectName().isEmpty())
            WatchdogRebooterClass->setObjectName("WatchdogRebooterClass");
        WatchdogRebooterClass->resize(1041, 420);
        centralWidget = new QWidget(WatchdogRebooterClass);
        centralWidget->setObjectName("centralWidget");
        tableWidget = new QTableWidget(centralWidget);
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
        tableWidget->setGeometry(QRect(0, 0, 691, 361));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 370, 1041, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonDeleteProgram = new QPushButton(frame);
        pushButtonDeleteProgram->setObjectName("pushButtonDeleteProgram");
        pushButtonDeleteProgram->setGeometry(QRect(130, 10, 111, 31));
        pushButtonAddProgram = new QPushButton(frame);
        pushButtonAddProgram->setObjectName("pushButtonAddProgram");
        pushButtonAddProgram->setGeometry(QRect(10, 10, 101, 31));
        pushButtonClose = new QPushButton(frame);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(910, 10, 121, 31));
        tableWidgetLog = new QTableWidget(centralWidget);
        if (tableWidgetLog->columnCount() < 4)
            tableWidgetLog->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLog->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLog->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetLog->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetLog->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        tableWidgetLog->setObjectName("tableWidgetLog");
        tableWidgetLog->setGeometry(QRect(690, 0, 351, 361));
        WatchdogRebooterClass->setCentralWidget(centralWidget);

        retranslateUi(WatchdogRebooterClass);

        QMetaObject::connectSlotsByName(WatchdogRebooterClass);
    } // setupUi

    void retranslateUi(QMainWindow *WatchdogRebooterClass)
    {
        WatchdogRebooterClass->setWindowTitle(QCoreApplication::translate("WatchdogRebooterClass", "WatchdogRebooter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("WatchdogRebooterClass", "Path", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("WatchdogRebooterClass", "FileName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("WatchdogRebooterClass", "Arg", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("WatchdogRebooterClass", "PID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("WatchdogRebooterClass", "Alive", nullptr));
        pushButtonDeleteProgram->setText(QCoreApplication::translate("WatchdogRebooterClass", "Delete", nullptr));
        pushButtonAddProgram->setText(QCoreApplication::translate("WatchdogRebooterClass", "Add program", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("WatchdogRebooterClass", "Close", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLog->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("WatchdogRebooterClass", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLog->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("WatchdogRebooterClass", "Date/Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetLog->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("WatchdogRebooterClass", "FileName", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetLog->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("WatchdogRebooterClass", "PID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WatchdogRebooterClass: public Ui_WatchdogRebooterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WATCHDOGREBOOTER_H
