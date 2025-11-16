/********************************************************************************
** Form generated from reading UI file 'SyncDatabase.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNCDATABASE_H
#define UI_SYNCDATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SyncDatabaseClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QLabel *label_2;
    QLineEdit *lineEditSrcServer;
    QLabel *label;
    QLabel *label_3;
    QSpinBox *spinBoxSrcPort;
    QLineEdit *lineEditSrcFileName;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEditSrcUserName;
    QLineEdit *lineEditSrcPassword;
    QLabel *label_6;
    QPushButton *pushButton;
    QFrame *frame_2;
    QLabel *label_7;
    QLineEdit *lineEditDstServer;
    QLabel *label_8;
    QLabel *label_9;
    QSpinBox *spinBoxDstPort;
    QLineEdit *lineEditDstFileName;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineEditDstUserName;
    QLineEdit *lineEditDstPassword;
    QLabel *label_12;
    QPushButton *pushButtonTestCOnnectionDst;
    QPushButton *pushButtonRegister;
    QToolButton *toolButtonRun;
    QLabel *labelRegisteredFileName;
    QFrame *frame_3;
    QLabel *label_14;
    QTableWidget *tableWidgetAction;
    QLabel *label_13;
    QListWidget *listWidgetSourceTable;
    QProgressBar *progressBar;
    QLabel *label_15;
    QPushButton *pushButtonAddExcluded;
    QListWidget *listWidgetExcluded;
    QPushButton *pushButtonDelExcluded;
    QPushButton *pushButtonForceUpdate;

    void setupUi(QMainWindow *SyncDatabaseClass)
    {
        if (SyncDatabaseClass->objectName().isEmpty())
            SyncDatabaseClass->setObjectName("SyncDatabaseClass");
        SyncDatabaseClass->resize(967, 641);
        centralWidget = new QWidget(SyncDatabaseClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 351, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 351, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditSrcServer = new QLineEdit(frame);
        lineEditSrcServer->setObjectName("lineEditSrcServer");
        lineEditSrcServer->setGeometry(QRect(100, 30, 241, 20));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 31, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 60, 81, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        spinBoxSrcPort = new QSpinBox(frame);
        spinBoxSrcPort->setObjectName("spinBoxSrcPort");
        spinBoxSrcPort->setGeometry(QRect(100, 60, 61, 22));
        spinBoxSrcPort->setMaximum(65535);
        spinBoxSrcPort->setValue(3050);
        lineEditSrcFileName = new QLineEdit(frame);
        lineEditSrcFileName->setObjectName("lineEditSrcFileName");
        lineEditSrcFileName->setGeometry(QRect(100, 89, 241, 20));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 90, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 131, 81, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        lineEditSrcUserName = new QLineEdit(frame);
        lineEditSrcUserName->setObjectName("lineEditSrcUserName");
        lineEditSrcUserName->setGeometry(QRect(100, 130, 241, 20));
        lineEditSrcPassword = new QLineEdit(frame);
        lineEditSrcPassword->setObjectName("lineEditSrcPassword");
        lineEditSrcPassword->setGeometry(QRect(100, 160, 241, 20));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 161, 81, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(210, 60, 101, 23));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(370, 10, 351, 191));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 351, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        lineEditDstServer = new QLineEdit(frame_2);
        lineEditDstServer->setObjectName("lineEditDstServer");
        lineEditDstServer->setGeometry(QRect(100, 30, 241, 20));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 31, 81, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 60, 81, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        spinBoxDstPort = new QSpinBox(frame_2);
        spinBoxDstPort->setObjectName("spinBoxDstPort");
        spinBoxDstPort->setGeometry(QRect(100, 60, 61, 22));
        spinBoxDstPort->setMaximum(65535);
        spinBoxDstPort->setValue(3050);
        lineEditDstFileName = new QLineEdit(frame_2);
        lineEditDstFileName->setObjectName("lineEditDstFileName");
        lineEditDstFileName->setGeometry(QRect(100, 89, 241, 20));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 90, 81, 20));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 131, 81, 20));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter);
        lineEditDstUserName = new QLineEdit(frame_2);
        lineEditDstUserName->setObjectName("lineEditDstUserName");
        lineEditDstUserName->setGeometry(QRect(100, 130, 241, 20));
        lineEditDstPassword = new QLineEdit(frame_2);
        lineEditDstPassword->setObjectName("lineEditDstPassword");
        lineEditDstPassword->setGeometry(QRect(100, 160, 241, 20));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 161, 81, 20));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter);
        pushButtonTestCOnnectionDst = new QPushButton(frame_2);
        pushButtonTestCOnnectionDst->setObjectName("pushButtonTestCOnnectionDst");
        pushButtonTestCOnnectionDst->setGeometry(QRect(210, 60, 101, 23));
        pushButtonRegister = new QPushButton(centralWidget);
        pushButtonRegister->setObjectName("pushButtonRegister");
        pushButtonRegister->setGeometry(QRect(10, 210, 91, 31));
        toolButtonRun = new QToolButton(centralWidget);
        toolButtonRun->setObjectName("toolButtonRun");
        toolButtonRun->setGeometry(QRect(480, 210, 111, 41));
        toolButtonRun->setCheckable(true);
        toolButtonRun->setChecked(false);
        labelRegisteredFileName = new QLabel(centralWidget);
        labelRegisteredFileName->setObjectName("labelRegisteredFileName");
        labelRegisteredFileName->setGeometry(QRect(110, 220, 271, 21));
        labelRegisteredFileName->setFrameShape(QFrame::Panel);
        labelRegisteredFileName->setFrameShadow(QFrame::Sunken);
        labelRegisteredFileName->setAlignment(Qt::AlignCenter);
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 260, 951, 371));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(frame_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(180, 50, 761, 20));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter);
        tableWidgetAction = new QTableWidget(frame_3);
        if (tableWidgetAction->columnCount() < 5)
            tableWidgetAction->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAction->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAction->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAction->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetAction->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetAction->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetAction->setObjectName("tableWidgetAction");
        tableWidgetAction->setGeometry(QRect(180, 71, 761, 291));
        label_13 = new QLabel(frame_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 50, 161, 20));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter);
        listWidgetSourceTable = new QListWidget(frame_3);
        listWidgetSourceTable->setObjectName("listWidgetSourceTable");
        listWidgetSourceTable->setGeometry(QRect(10, 71, 161, 131));
        progressBar = new QProgressBar(frame_3);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 10, 931, 23));
        progressBar->setValue(0);
        label_15 = new QLabel(frame_3);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 210, 71, 16));
        pushButtonAddExcluded = new QPushButton(frame_3);
        pushButtonAddExcluded->setObjectName("pushButtonAddExcluded");
        pushButtonAddExcluded->setGeometry(QRect(20, 240, 51, 23));
        listWidgetExcluded = new QListWidget(frame_3);
        new QListWidgetItem(listWidgetExcluded);
        listWidgetExcluded->setObjectName("listWidgetExcluded");
        listWidgetExcluded->setGeometry(QRect(10, 270, 161, 91));
        pushButtonDelExcluded = new QPushButton(frame_3);
        pushButtonDelExcluded->setObjectName("pushButtonDelExcluded");
        pushButtonDelExcluded->setGeometry(QRect(90, 240, 51, 23));
        pushButtonForceUpdate = new QPushButton(centralWidget);
        pushButtonForceUpdate->setObjectName("pushButtonForceUpdate");
        pushButtonForceUpdate->setGeometry(QRect(600, 210, 121, 41));
        SyncDatabaseClass->setCentralWidget(centralWidget);

        retranslateUi(SyncDatabaseClass);

        QMetaObject::connectSlotsByName(SyncDatabaseClass);
    } // setupUi

    void retranslateUi(QMainWindow *SyncDatabaseClass)
    {
        SyncDatabaseClass->setWindowTitle(QCoreApplication::translate("SyncDatabaseClass", "SyncDatabase", nullptr));
        label_2->setText(QCoreApplication::translate("SyncDatabaseClass", "Source", nullptr));
        label->setText(QCoreApplication::translate("SyncDatabaseClass", "IP/Name", nullptr));
        label_3->setText(QCoreApplication::translate("SyncDatabaseClass", "Port", nullptr));
        label_4->setText(QCoreApplication::translate("SyncDatabaseClass", "DB File name", nullptr));
        label_5->setText(QCoreApplication::translate("SyncDatabaseClass", "User name", nullptr));
        label_6->setText(QCoreApplication::translate("SyncDatabaseClass", "Password", nullptr));
        pushButton->setText(QCoreApplication::translate("SyncDatabaseClass", "Test connection", nullptr));
        label_7->setText(QCoreApplication::translate("SyncDatabaseClass", "Destination", nullptr));
        label_8->setText(QCoreApplication::translate("SyncDatabaseClass", "IP/Name", nullptr));
        label_9->setText(QCoreApplication::translate("SyncDatabaseClass", "Port", nullptr));
        label_10->setText(QCoreApplication::translate("SyncDatabaseClass", "DB File name", nullptr));
        label_11->setText(QCoreApplication::translate("SyncDatabaseClass", "User name", nullptr));
        label_12->setText(QCoreApplication::translate("SyncDatabaseClass", "Password", nullptr));
        pushButtonTestCOnnectionDst->setText(QCoreApplication::translate("SyncDatabaseClass", "Test connection", nullptr));
        pushButtonRegister->setText(QCoreApplication::translate("SyncDatabaseClass", "Register", nullptr));
        toolButtonRun->setText(QCoreApplication::translate("SyncDatabaseClass", "Run", nullptr));
        labelRegisteredFileName->setText(QCoreApplication::translate("SyncDatabaseClass", "XXXX.dat", nullptr));
        label_14->setText(QCoreApplication::translate("SyncDatabaseClass", "Action", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAction->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SyncDatabaseClass", "DayTime", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAction->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SyncDatabaseClass", "Error", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAction->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SyncDatabaseClass", "Table", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetAction->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SyncDatabaseClass", "Key", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetAction->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SyncDatabaseClass", "Action", nullptr));
        label_13->setText(QCoreApplication::translate("SyncDatabaseClass", "Source tables", nullptr));
        label_15->setText(QCoreApplication::translate("SyncDatabaseClass", "Excluded files", nullptr));
        pushButtonAddExcluded->setText(QCoreApplication::translate("SyncDatabaseClass", "+", nullptr));

        const bool __sortingEnabled = listWidgetExcluded->isSortingEnabled();
        listWidgetExcluded->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetExcluded->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("SyncDatabaseClass", "REGULUS64-2.FDB", nullptr));
        listWidgetExcluded->setSortingEnabled(__sortingEnabled);

        pushButtonDelExcluded->setText(QCoreApplication::translate("SyncDatabaseClass", "-", nullptr));
        pushButtonForceUpdate->setText(QCoreApplication::translate("SyncDatabaseClass", "Force update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SyncDatabaseClass: public Ui_SyncDatabaseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCDATABASE_H
