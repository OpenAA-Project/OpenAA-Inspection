/********************************************************************************
** Form generated from reading UI file 'VirtualPIOServer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIRTUALPIOSERVER_H
#define UI_VIRTUALPIOSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VirtualPIOServerClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QListWidget *listWidgetClientList;
    QLabel *label;
    QTableWidget *tableWidgetIn;
    QTableWidget *tableWidgetOut;
    QLabel *label_2;
    QFrame *frame_2;
    QTableWidget *tableWidgetIntegrated;

    void setupUi(QMainWindow *VirtualPIOServerClass)
    {
        if (VirtualPIOServerClass->objectName().isEmpty())
            VirtualPIOServerClass->setObjectName("VirtualPIOServerClass");
        VirtualPIOServerClass->resize(686, 741);
        centralWidget = new QWidget(VirtualPIOServerClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 370, 671, 361));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        listWidgetClientList = new QListWidget(frame);
        listWidgetClientList->setObjectName("listWidgetClientList");
        listWidgetClientList->setGeometry(QRect(10, 10, 171, 341));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 10, 231, 31));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        tableWidgetIn = new QTableWidget(frame);
        if (tableWidgetIn->columnCount() < 2)
            tableWidgetIn->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetIn->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetIn->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetIn->setObjectName("tableWidgetIn");
        tableWidgetIn->setGeometry(QRect(430, 40, 231, 311));
        tableWidgetOut = new QTableWidget(frame);
        if (tableWidgetOut->columnCount() < 2)
            tableWidgetOut->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetOut->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetOut->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetOut->setObjectName("tableWidgetOut");
        tableWidgetOut->setGeometry(QRect(190, 40, 231, 311));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(430, 10, 231, 31));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 461, 351));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        tableWidgetIntegrated = new QTableWidget(frame_2);
        if (tableWidgetIntegrated->columnCount() < 3)
            tableWidgetIntegrated->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetIntegrated->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetIntegrated->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetIntegrated->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetIntegrated->setObjectName("tableWidgetIntegrated");
        tableWidgetIntegrated->setGeometry(QRect(10, 10, 441, 331));
        VirtualPIOServerClass->setCentralWidget(centralWidget);

        retranslateUi(VirtualPIOServerClass);

        QMetaObject::connectSlotsByName(VirtualPIOServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *VirtualPIOServerClass)
    {
        VirtualPIOServerClass->setWindowTitle(QCoreApplication::translate("VirtualPIOServerClass", "VirtualPIOServer", nullptr));
        label->setText(QCoreApplication::translate("VirtualPIOServerClass", "Output", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetIn->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("VirtualPIOServerClass", "Bit", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetIn->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("VirtualPIOServerClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetOut->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("VirtualPIOServerClass", "Bit", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetOut->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("VirtualPIOServerClass", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("VirtualPIOServerClass", "Input", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetIntegrated->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("VirtualPIOServerClass", "WhoOutput", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetIntegrated->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("VirtualPIOServerClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetIntegrated->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("VirtualPIOServerClass", "Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VirtualPIOServerClass: public Ui_VirtualPIOServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIRTUALPIOSERVER_H
