/********************************************************************************
** Form generated from reading UI file 'DFSServer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DFSSERVER_H
#define UI_DFSSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DFSServerClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QLabel *label;
    QTableWidget *tableWidgetClients;
    QFrame *frame_2;
    QLabel *label_2;
    QTableWidget *tableWidgetDFSProviderList;
    QPushButton *pushButtonAddDFSProvider;
    QPushButton *pushButtonDeleteDFSProvider;

    void setupUi(QMainWindow *DFSServerClass)
    {
        if (DFSServerClass->objectName().isEmpty())
            DFSServerClass->setObjectName("DFSServerClass");
        DFSServerClass->resize(669, 441);
        centralWidget = new QWidget(DFSServerClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 331, 381));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(1, 0, 331, 21));
        label->setAlignment(Qt::AlignCenter);
        tableWidgetClients = new QTableWidget(frame);
        if (tableWidgetClients->columnCount() < 2)
            tableWidgetClients->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetClients->setObjectName("tableWidgetClients");
        tableWidgetClients->setGeometry(QRect(0, 20, 331, 361));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(330, 0, 331, 391));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 331, 21));
        label_2->setAlignment(Qt::AlignCenter);
        tableWidgetDFSProviderList = new QTableWidget(frame_2);
        if (tableWidgetDFSProviderList->columnCount() < 2)
            tableWidgetDFSProviderList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetDFSProviderList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetDFSProviderList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetDFSProviderList->setObjectName("tableWidgetDFSProviderList");
        tableWidgetDFSProviderList->setGeometry(QRect(0, 20, 331, 361));
        tableWidgetDFSProviderList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetDFSProviderList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddDFSProvider = new QPushButton(centralWidget);
        pushButtonAddDFSProvider->setObjectName("pushButtonAddDFSProvider");
        pushButtonAddDFSProvider->setGeometry(QRect(340, 400, 131, 28));
        pushButtonDeleteDFSProvider = new QPushButton(centralWidget);
        pushButtonDeleteDFSProvider->setObjectName("pushButtonDeleteDFSProvider");
        pushButtonDeleteDFSProvider->setGeometry(QRect(480, 400, 101, 28));
        DFSServerClass->setCentralWidget(centralWidget);

        retranslateUi(DFSServerClass);

        QMetaObject::connectSlotsByName(DFSServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *DFSServerClass)
    {
        DFSServerClass->setWindowTitle(QCoreApplication::translate("DFSServerClass", "DFSServer", nullptr));
        label->setText(QCoreApplication::translate("DFSServerClass", "Client", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetClients->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DFSServerClass", "Client address", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetClients->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DFSServerClass", "Port", nullptr));
        label_2->setText(QCoreApplication::translate("DFSServerClass", "DFS privider", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetDFSProviderList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DFSServerClass", "IP address", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetDFSProviderList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DFSServerClass", "Port", nullptr));
        pushButtonAddDFSProvider->setText(QCoreApplication::translate("DFSServerClass", "Add DFSProvider", nullptr));
        pushButtonDeleteDFSProvider->setText(QCoreApplication::translate("DFSServerClass", "Delete route", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DFSServerClass: public Ui_DFSServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DFSSERVER_H
