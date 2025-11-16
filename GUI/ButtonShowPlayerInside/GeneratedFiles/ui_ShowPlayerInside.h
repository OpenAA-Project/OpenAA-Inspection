/********************************************************************************
** Form generated from reading UI file 'ShowPlayerInside.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWPLAYERINSIDE_H
#define UI_SHOWPLAYERINSIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowPlayerInside
{
public:
    QTableWidget *tableWidgetLayersBase;
    QLabel *label;
    QListWidget *listWidgetCurrentStrategicQueue;
    QTableWidget *tableWidgetReceivedFlag;
    QLabel *label_2;

    void setupUi(QWidget *ShowPlayerInside)
    {
        if (ShowPlayerInside->objectName().isEmpty())
            ShowPlayerInside->setObjectName("ShowPlayerInside");
        ShowPlayerInside->resize(858, 516);
        tableWidgetLayersBase = new QTableWidget(ShowPlayerInside);
        if (tableWidgetLayersBase->columnCount() < 1)
            tableWidgetLayersBase->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLayersBase->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidgetLayersBase->rowCount() < 13)
            tableWidgetLayersBase->setRowCount(13);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(6, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(7, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(8, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(9, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(10, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(11, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetLayersBase->setVerticalHeaderItem(12, __qtablewidgetitem13);
        tableWidgetLayersBase->setObjectName("tableWidgetLayersBase");
        tableWidgetLayersBase->setGeometry(QRect(10, 20, 311, 491));
        tableWidgetLayersBase->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetLayersBase->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label = new QLabel(ShowPlayerInside);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 20, 141, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        listWidgetCurrentStrategicQueue = new QListWidget(ShowPlayerInside);
        listWidgetCurrentStrategicQueue->setObjectName("listWidgetCurrentStrategicQueue");
        listWidgetCurrentStrategicQueue->setGeometry(QRect(330, 40, 141, 311));
        tableWidgetReceivedFlag = new QTableWidget(ShowPlayerInside);
        if (tableWidgetReceivedFlag->columnCount() < 2)
            tableWidgetReceivedFlag->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetReceivedFlag->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetReceivedFlag->setHorizontalHeaderItem(1, __qtablewidgetitem15);
        tableWidgetReceivedFlag->setObjectName("tableWidgetReceivedFlag");
        tableWidgetReceivedFlag->setGeometry(QRect(480, 40, 361, 311));
        label_2 = new QLabel(ShowPlayerInside);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(480, 20, 361, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(ShowPlayerInside);

        QMetaObject::connectSlotsByName(ShowPlayerInside);
    } // setupUi

    void retranslateUi(QWidget *ShowPlayerInside)
    {
        ShowPlayerInside->setWindowTitle(QCoreApplication::translate("ShowPlayerInside", "PlayerInside", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLayersBase->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowPlayerInside", "Value", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLayersBase->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowPlayerInside", "CurrentStrategicNumber", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLayersBase->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowPlayerInside", "CurrentStrategicNumberForSeq", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLayersBase->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowPlayerInside", "CurrentStrategicNumberForCalc", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLayersBase->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowPlayerInside", "GetCurrentInspectIDForDisplay", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLayersBase->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowPlayerInside", "GetCurrentInspectIDForDExecute", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLayersBase->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ShowPlayerInside", "CurrentCalcPoint", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetLayersBase->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ShowPlayerInside", "CurrentDrawPoint", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetLayersBase->verticalHeaderItem(7);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ShowPlayerInside", "LastCurrentCalcPoint", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetLayersBase->verticalHeaderItem(8);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("ShowPlayerInside", "CurrentPhase", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetLayersBase->verticalHeaderItem(9);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("ShowPlayerInside", "_CurrentInspectID(Execute)", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetLayersBase->verticalHeaderItem(10);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("ShowPlayerInside", "_LastInspectID(Display)", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetLayersBase->verticalHeaderItem(11);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("ShowPlayerInside", "ResultWrittenID", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetLayersBase->verticalHeaderItem(12);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("ShowPlayerInside", "CurrentScanPhaseNumber", nullptr));
        label->setText(QCoreApplication::translate("ShowPlayerInside", "CurrentStrategicQueue", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetReceivedFlag->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("ShowPlayerInside", "Executer", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetReceivedFlag->horizontalHeaderItem(1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("ShowPlayerInside", "Pg0", nullptr));
        label_2->setText(QCoreApplication::translate("ShowPlayerInside", "ReceivedFlag", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowPlayerInside: public Ui_ShowPlayerInside {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWPLAYERINSIDE_H
