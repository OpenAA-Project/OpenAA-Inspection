/********************************************************************************
** Form generated from reading UI file 'DFSProvider.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DFSPROVIDER_H
#define UI_DFSPROVIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DFSProviderClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonDeleteRoute;
    QFrame *frame_2;
    QLabel *label_2;
    QTableWidget *tableWidgetRoute;
    QPushButton *pushButtonAddRoute;
    QFrame *frame_3;
    QLabel *Execution;
    QListWidget *listWidgetCommandList;

    void setupUi(QMainWindow *DFSProviderClass)
    {
        if (DFSProviderClass->objectName().isEmpty())
            DFSProviderClass->setObjectName("DFSProviderClass");
        DFSProviderClass->resize(613, 910);
        centralWidget = new QWidget(DFSProviderClass);
        centralWidget->setObjectName("centralWidget");
        pushButtonDeleteRoute = new QPushButton(centralWidget);
        pushButtonDeleteRoute->setObjectName("pushButtonDeleteRoute");
        pushButtonDeleteRoute->setGeometry(QRect(290, 460, 101, 28));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 0, 611, 451));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 611, 21));
        label_2->setAlignment(Qt::AlignCenter);
        tableWidgetRoute = new QTableWidget(frame_2);
        if (tableWidgetRoute->columnCount() < 2)
            tableWidgetRoute->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetRoute->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetRoute->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetRoute->setObjectName("tableWidgetRoute");
        tableWidgetRoute->setGeometry(QRect(0, 20, 611, 431));
        tableWidgetRoute->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetRoute->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddRoute = new QPushButton(centralWidget);
        pushButtonAddRoute->setObjectName("pushButtonAddRoute");
        pushButtonAddRoute->setGeometry(QRect(170, 460, 111, 28));
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(0, 510, 611, 411));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        Execution = new QLabel(frame_3);
        Execution->setObjectName("Execution");
        Execution->setGeometry(QRect(0, 0, 611, 21));
        Execution->setAlignment(Qt::AlignCenter);
        listWidgetCommandList = new QListWidget(frame_3);
        listWidgetCommandList->setObjectName("listWidgetCommandList");
        listWidgetCommandList->setGeometry(QRect(0, 20, 611, 381));
        DFSProviderClass->setCentralWidget(centralWidget);

        retranslateUi(DFSProviderClass);

        QMetaObject::connectSlotsByName(DFSProviderClass);
    } // setupUi

    void retranslateUi(QMainWindow *DFSProviderClass)
    {
        DFSProviderClass->setWindowTitle(QCoreApplication::translate("DFSProviderClass", "DFSProvider", nullptr));
        pushButtonDeleteRoute->setText(QCoreApplication::translate("DFSProviderClass", "Delete route", nullptr));
        label_2->setText(QCoreApplication::translate("DFSProviderClass", "Path routes", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetRoute->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DFSProviderClass", "Path", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetRoute->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DFSProviderClass", "Priority", nullptr));
        pushButtonAddRoute->setText(QCoreApplication::translate("DFSProviderClass", "Add route", nullptr));
        Execution->setText(QCoreApplication::translate("DFSProviderClass", "Execution", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DFSProviderClass: public Ui_DFSProviderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DFSPROVIDER_H
