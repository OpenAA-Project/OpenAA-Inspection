/********************************************************************************
** Form generated from reading UI file 'SimulateSequence.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATESEQUENCE_H
#define UI_SIMULATESEQUENCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulateSequence
{
public:
    QPushButton *ShowButton;
    QLabel *label;
    QTableWidget *SGridSeq;
    QPushButton *ViewButton;
    QPushButton *BreakPointButton;
    QPushButton *StopButton;
    QCheckBox *CheckBoxFlag;
    QPushButton *DLLHistButton;
    QTableWidget *SeqGrid;
    QPushButton *TimingButton;
    QPushButton *GoButton;
    QPushButton *StepButton;
    QPushButton *CloseButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTabWidget *tabWidget_2;
    QWidget *tab_5;
    QTableWidget *SGridSystemReg;
    QWidget *tab_6;
    QTableWidget *SGridSystemBReg;
    QWidget *tab_7;
    QTableWidget *SGridSystemQReg;
    QWidget *tab_8;
    QTableWidget *SGridSystemRReg;
    QWidget *tab_2;
    QTabWidget *tabWidget_3;
    QWidget *tab_9;
    QTableWidget *SGridWReg;
    QWidget *tab_10;
    QTableWidget *SGridFReg;
    QWidget *tab_11;
    QTableWidget *SGridBReg;
    QWidget *tab_12;
    QTableWidget *SGridCReg;
    QWidget *tab_15;
    QTableWidget *SGridGReg;
    QWidget *tab_13;
    QTableWidget *LanGrid;
    QWidget *tab_14;
    QTableWidget *SGridFifo;
    QListWidget *ListBFifo;
    QWidget *tab_3;
    QTabWidget *tabWidget_4;
    QWidget *tab_16;
    QTableWidget *SGridLBReg;
    QWidget *tab_17;
    QTableWidget *SGridLWReg;
    QWidget *tab_18;
    QTableWidget *SGridLFReg;
    QWidget *tab_19;
    QTableWidget *SGridLCReg;
    QWidget *tab_4;
    QTableWidget *tableWidgetCOMReg;
    QWidget *tab_20;
    QTableWidget *IOGrid;

    void setupUi(QWidget *SimulateSequence)
    {
        if (SimulateSequence->objectName().isEmpty())
            SimulateSequence->setObjectName("SimulateSequence");
        SimulateSequence->resize(1269, 538);
        ShowButton = new QPushButton(SimulateSequence);
        ShowButton->setObjectName("ShowButton");
        ShowButton->setGeometry(QRect(534, 10, 75, 25));
        label = new QLabel(SimulateSequence);
        label->setObjectName("label");
        label->setGeometry(QRect(630, 502, 321, 16));
        SGridSeq = new QTableWidget(SimulateSequence);
        if (SGridSeq->columnCount() < 2)
            SGridSeq->setColumnCount(2);
        if (SGridSeq->rowCount() < 2)
            SGridSeq->setRowCount(2);
        SGridSeq->setObjectName("SGridSeq");
        SGridSeq->setGeometry(QRect(530, 70, 181, 381));
        SGridSeq->setRowCount(2);
        SGridSeq->setColumnCount(2);
        ViewButton = new QPushButton(SimulateSequence);
        ViewButton->setObjectName("ViewButton");
        ViewButton->setGeometry(QRect(6, 10, 75, 25));
        BreakPointButton = new QPushButton(SimulateSequence);
        BreakPointButton->setObjectName("BreakPointButton");
        BreakPointButton->setGeometry(QRect(94, 10, 75, 25));
        StopButton = new QPushButton(SimulateSequence);
        StopButton->setObjectName("StopButton");
        StopButton->setGeometry(QRect(358, 10, 75, 25));
        CheckBoxFlag = new QCheckBox(SimulateSequence);
        CheckBoxFlag->setObjectName("CheckBoxFlag");
        CheckBoxFlag->setGeometry(QRect(94, 482, 75, 21));
        DLLHistButton = new QPushButton(SimulateSequence);
        DLLHistButton->setObjectName("DLLHistButton");
        DLLHistButton->setGeometry(QRect(622, 10, 75, 25));
        SeqGrid = new QTableWidget(SimulateSequence);
        if (SeqGrid->columnCount() < 8)
            SeqGrid->setColumnCount(8);
        if (SeqGrid->rowCount() < 10)
            SeqGrid->setRowCount(10);
        SeqGrid->setObjectName("SeqGrid");
        SeqGrid->setGeometry(QRect(10, 60, 511, 393));
        QFont font;
        font.setFamilies({QString::fromUtf8("lr")});
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        SeqGrid->setFont(font);
        SeqGrid->setSelectionMode(QAbstractItemView::SingleSelection);
        SeqGrid->setSelectionBehavior(QAbstractItemView::SelectRows);
        SeqGrid->setRowCount(10);
        SeqGrid->setColumnCount(8);
        TimingButton = new QPushButton(SimulateSequence);
        TimingButton->setObjectName("TimingButton");
        TimingButton->setGeometry(QRect(446, 10, 75, 25));
        GoButton = new QPushButton(SimulateSequence);
        GoButton->setObjectName("GoButton");
        GoButton->setGeometry(QRect(182, 10, 75, 25));
        StepButton = new QPushButton(SimulateSequence);
        StepButton->setObjectName("StepButton");
        StepButton->setGeometry(QRect(270, 10, 75, 25));
        CloseButton = new QPushButton(SimulateSequence);
        CloseButton->setObjectName("CloseButton");
        CloseButton->setGeometry(QRect(710, 10, 75, 25));
        tabWidget = new QTabWidget(SimulateSequence);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(720, 50, 541, 441));
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget_2 = new QTabWidget(tab);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(0, 0, 531, 401));
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        SGridSystemReg = new QTableWidget(tab_5);
        if (SGridSystemReg->columnCount() < 3)
            SGridSystemReg->setColumnCount(3);
        if (SGridSystemReg->rowCount() < 2)
            SGridSystemReg->setRowCount(2);
        SGridSystemReg->setObjectName("SGridSystemReg");
        SGridSystemReg->setGeometry(QRect(0, 0, 521, 381));
        SGridSystemReg->setRowCount(2);
        SGridSystemReg->setColumnCount(3);
        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        SGridSystemBReg = new QTableWidget(tab_6);
        if (SGridSystemBReg->columnCount() < 3)
            SGridSystemBReg->setColumnCount(3);
        if (SGridSystemBReg->rowCount() < 2)
            SGridSystemBReg->setRowCount(2);
        SGridSystemBReg->setObjectName("SGridSystemBReg");
        SGridSystemBReg->setGeometry(QRect(0, 0, 551, 381));
        SGridSystemBReg->setRowCount(2);
        SGridSystemBReg->setColumnCount(3);
        tabWidget_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        SGridSystemQReg = new QTableWidget(tab_7);
        if (SGridSystemQReg->columnCount() < 3)
            SGridSystemQReg->setColumnCount(3);
        if (SGridSystemQReg->rowCount() < 2)
            SGridSystemQReg->setRowCount(2);
        SGridSystemQReg->setObjectName("SGridSystemQReg");
        SGridSystemQReg->setGeometry(QRect(0, 0, 551, 381));
        SGridSystemQReg->setRowCount(2);
        SGridSystemQReg->setColumnCount(3);
        tabWidget_2->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        SGridSystemRReg = new QTableWidget(tab_8);
        if (SGridSystemRReg->columnCount() < 3)
            SGridSystemRReg->setColumnCount(3);
        if (SGridSystemRReg->rowCount() < 2)
            SGridSystemRReg->setRowCount(2);
        SGridSystemRReg->setObjectName("SGridSystemRReg");
        SGridSystemRReg->setGeometry(QRect(0, 0, 551, 381));
        SGridSystemRReg->setRowCount(2);
        SGridSystemRReg->setColumnCount(3);
        tabWidget_2->addTab(tab_8, QString());
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget_3 = new QTabWidget(tab_2);
        tabWidget_3->setObjectName("tabWidget_3");
        tabWidget_3->setGeometry(QRect(0, 0, 531, 421));
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        SGridWReg = new QTableWidget(tab_9);
        if (SGridWReg->columnCount() < 2)
            SGridWReg->setColumnCount(2);
        if (SGridWReg->rowCount() < 2)
            SGridWReg->setRowCount(2);
        SGridWReg->setObjectName("SGridWReg");
        SGridWReg->setGeometry(QRect(0, 0, 241, 391));
        SGridWReg->setRowCount(2);
        SGridWReg->setColumnCount(2);
        tabWidget_3->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        SGridFReg = new QTableWidget(tab_10);
        if (SGridFReg->columnCount() < 2)
            SGridFReg->setColumnCount(2);
        if (SGridFReg->rowCount() < 2)
            SGridFReg->setRowCount(2);
        SGridFReg->setObjectName("SGridFReg");
        SGridFReg->setGeometry(QRect(0, 0, 241, 391));
        SGridFReg->setRowCount(2);
        SGridFReg->setColumnCount(2);
        tabWidget_3->addTab(tab_10, QString());
        tab_11 = new QWidget();
        tab_11->setObjectName("tab_11");
        SGridBReg = new QTableWidget(tab_11);
        if (SGridBReg->columnCount() < 2)
            SGridBReg->setColumnCount(2);
        if (SGridBReg->rowCount() < 2)
            SGridBReg->setRowCount(2);
        SGridBReg->setObjectName("SGridBReg");
        SGridBReg->setGeometry(QRect(0, 0, 241, 391));
        SGridBReg->setRowCount(2);
        SGridBReg->setColumnCount(2);
        tabWidget_3->addTab(tab_11, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName("tab_12");
        SGridCReg = new QTableWidget(tab_12);
        if (SGridCReg->columnCount() < 3)
            SGridCReg->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        SGridCReg->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (SGridCReg->rowCount() < 2)
            SGridCReg->setRowCount(2);
        SGridCReg->setObjectName("SGridCReg");
        SGridCReg->setGeometry(QRect(0, 0, 521, 391));
        SGridCReg->setRowCount(2);
        SGridCReg->setColumnCount(3);
        tabWidget_3->addTab(tab_12, QString());
        tab_15 = new QWidget();
        tab_15->setObjectName("tab_15");
        SGridGReg = new QTableWidget(tab_15);
        if (SGridGReg->columnCount() < 2)
            SGridGReg->setColumnCount(2);
        if (SGridGReg->rowCount() < 2)
            SGridGReg->setRowCount(2);
        SGridGReg->setObjectName("SGridGReg");
        SGridGReg->setGeometry(QRect(0, 0, 241, 391));
        SGridGReg->setRowCount(2);
        SGridGReg->setColumnCount(2);
        tabWidget_3->addTab(tab_15, QString());
        tab_13 = new QWidget();
        tab_13->setObjectName("tab_13");
        LanGrid = new QTableWidget(tab_13);
        if (LanGrid->columnCount() < 2)
            LanGrid->setColumnCount(2);
        if (LanGrid->rowCount() < 2)
            LanGrid->setRowCount(2);
        LanGrid->setObjectName("LanGrid");
        LanGrid->setGeometry(QRect(0, 0, 241, 391));
        LanGrid->setRowCount(2);
        LanGrid->setColumnCount(2);
        tabWidget_3->addTab(tab_13, QString());
        tab_14 = new QWidget();
        tab_14->setObjectName("tab_14");
        SGridFifo = new QTableWidget(tab_14);
        if (SGridFifo->columnCount() < 2)
            SGridFifo->setColumnCount(2);
        if (SGridFifo->rowCount() < 2)
            SGridFifo->setRowCount(2);
        SGridFifo->setObjectName("SGridFifo");
        SGridFifo->setGeometry(QRect(0, 0, 241, 191));
        SGridFifo->setRowCount(2);
        SGridFifo->setColumnCount(2);
        ListBFifo = new QListWidget(tab_14);
        ListBFifo->setObjectName("ListBFifo");
        ListBFifo->setGeometry(QRect(0, 190, 241, 191));
        tabWidget_3->addTab(tab_14, QString());
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget_4 = new QTabWidget(tab_3);
        tabWidget_4->setObjectName("tabWidget_4");
        tabWidget_4->setGeometry(QRect(0, 0, 531, 381));
        tab_16 = new QWidget();
        tab_16->setObjectName("tab_16");
        SGridLBReg = new QTableWidget(tab_16);
        if (SGridLBReg->columnCount() < 2)
            SGridLBReg->setColumnCount(2);
        if (SGridLBReg->rowCount() < 2)
            SGridLBReg->setRowCount(2);
        SGridLBReg->setObjectName("SGridLBReg");
        SGridLBReg->setGeometry(QRect(0, 0, 241, 391));
        SGridLBReg->setRowCount(2);
        SGridLBReg->setColumnCount(2);
        tabWidget_4->addTab(tab_16, QString());
        tab_17 = new QWidget();
        tab_17->setObjectName("tab_17");
        SGridLWReg = new QTableWidget(tab_17);
        if (SGridLWReg->columnCount() < 2)
            SGridLWReg->setColumnCount(2);
        if (SGridLWReg->rowCount() < 2)
            SGridLWReg->setRowCount(2);
        SGridLWReg->setObjectName("SGridLWReg");
        SGridLWReg->setGeometry(QRect(0, 0, 241, 391));
        SGridLWReg->setRowCount(2);
        SGridLWReg->setColumnCount(2);
        tabWidget_4->addTab(tab_17, QString());
        tab_18 = new QWidget();
        tab_18->setObjectName("tab_18");
        SGridLFReg = new QTableWidget(tab_18);
        if (SGridLFReg->columnCount() < 2)
            SGridLFReg->setColumnCount(2);
        if (SGridLFReg->rowCount() < 2)
            SGridLFReg->setRowCount(2);
        SGridLFReg->setObjectName("SGridLFReg");
        SGridLFReg->setGeometry(QRect(0, 0, 241, 391));
        SGridLFReg->setRowCount(2);
        SGridLFReg->setColumnCount(2);
        tabWidget_4->addTab(tab_18, QString());
        tab_19 = new QWidget();
        tab_19->setObjectName("tab_19");
        SGridLCReg = new QTableWidget(tab_19);
        if (SGridLCReg->columnCount() < 2)
            SGridLCReg->setColumnCount(2);
        if (SGridLCReg->rowCount() < 2)
            SGridLCReg->setRowCount(2);
        SGridLCReg->setObjectName("SGridLCReg");
        SGridLCReg->setGeometry(QRect(0, 0, 521, 361));
        SGridLCReg->setRowCount(2);
        SGridLCReg->setColumnCount(2);
        tabWidget_4->addTab(tab_19, QString());
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tableWidgetCOMReg = new QTableWidget(tab_4);
        if (tableWidgetCOMReg->columnCount() < 7)
            tableWidgetCOMReg->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetCOMReg->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetCOMReg->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetCOMReg->setHorizontalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetCOMReg->setHorizontalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetCOMReg->setHorizontalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetCOMReg->setHorizontalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetCOMReg->setHorizontalHeaderItem(6, __qtablewidgetitem7);
        tableWidgetCOMReg->setObjectName("tableWidgetCOMReg");
        tableWidgetCOMReg->setGeometry(QRect(0, 0, 531, 401));
        tableWidgetCOMReg->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetCOMReg->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabWidget->addTab(tab_4, QString());
        tab_20 = new QWidget();
        tab_20->setObjectName("tab_20");
        IOGrid = new QTableWidget(tab_20);
        if (IOGrid->columnCount() < 2)
            IOGrid->setColumnCount(2);
        if (IOGrid->rowCount() < 2)
            IOGrid->setRowCount(2);
        IOGrid->setObjectName("IOGrid");
        IOGrid->setGeometry(QRect(0, 0, 241, 411));
        IOGrid->setRowCount(2);
        IOGrid->setColumnCount(2);
        tabWidget->addTab(tab_20, QString());

        retranslateUi(SimulateSequence);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);
        tabWidget_3->setCurrentIndex(6);
        tabWidget_4->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SimulateSequence);
    } // setupUi

    void retranslateUi(QWidget *SimulateSequence)
    {
        SimulateSequence->setWindowTitle(QCoreApplication::translate("SimulateSequence", "Form", nullptr));
        ShowButton->setText(QCoreApplication::translate("SimulateSequence", "Show", nullptr));
        label->setText(QCoreApplication::translate("SimulateSequence", "The value is changed by right-clicking", nullptr));
        ViewButton->setText(QCoreApplication::translate("SimulateSequence", "View", nullptr));
        BreakPointButton->setText(QCoreApplication::translate("SimulateSequence", "BreakPoint", nullptr));
        StopButton->setText(QCoreApplication::translate("SimulateSequence", "Stop", nullptr));
        CheckBoxFlag->setText(QCoreApplication::translate("SimulateSequence", "Flag", nullptr));
        DLLHistButton->setText(QCoreApplication::translate("SimulateSequence", "DLL Hist", nullptr));
        TimingButton->setText(QCoreApplication::translate("SimulateSequence", "Timing", nullptr));
        GoButton->setText(QCoreApplication::translate("SimulateSequence", "Go", nullptr));
        StepButton->setText(QCoreApplication::translate("SimulateSequence", "Step", nullptr));
        CloseButton->setText(QCoreApplication::translate("SimulateSequence", "Close", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QCoreApplication::translate("SimulateSequence", "System Register", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QCoreApplication::translate("SimulateSequence", "SystemBit", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QCoreApplication::translate("SimulateSequence", "System String", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_8), QCoreApplication::translate("SimulateSequence", "System Float", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SimulateSequence", "System", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_9), QCoreApplication::translate("SimulateSequence", "W-Reg", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_10), QCoreApplication::translate("SimulateSequence", "F-Reg", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_11), QCoreApplication::translate("SimulateSequence", "B-Reg", nullptr));
        QTableWidgetItem *___qtablewidgetitem = SGridCReg->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SimulateSequence", "1", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_12), QCoreApplication::translate("SimulateSequence", "C-Reg", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_15), QCoreApplication::translate("SimulateSequence", "G-Reg", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_13), QCoreApplication::translate("SimulateSequence", "Common Variable", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_14), QCoreApplication::translate("SimulateSequence", "FIFO", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SimulateSequence", "Global", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_16), QCoreApplication::translate("SimulateSequence", "LB-Reg", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_17), QCoreApplication::translate("SimulateSequence", "LW-Reg", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_18), QCoreApplication::translate("SimulateSequence", "LF-Reg", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_19), QCoreApplication::translate("SimulateSequence", "LC-Reg", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("SimulateSequence", "Local", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetCOMReg->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SimulateSequence", "COM port name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetCOMReg->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SimulateSequence", "COM port", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetCOMReg->horizontalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SimulateSequence", "Baud rate", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetCOMReg->horizontalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SimulateSequence", "Character", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetCOMReg->horizontalHeaderItem(4);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SimulateSequence", "Parity", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetCOMReg->horizontalHeaderItem(5);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("SimulateSequence", "StopBot", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetCOMReg->horizontalHeaderItem(6);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("SimulateSequence", "Open", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("SimulateSequence", "COM", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_20), QCoreApplication::translate("SimulateSequence", "I/O", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulateSequence: public Ui_SimulateSequence {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATESEQUENCE_H
