/********************************************************************************
** Form generated from reading UI file 'ExecuteBatchForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXECUTEBATCHFORM_H
#define UI_EXECUTEBATCHFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ExecuteBatchForm
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonInsert;
    QPushButton *pushButtonExecuteAll;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonDown;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonModify;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonExecuteOne;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonAppend;

    void setupUi(GUIFormBase *ExecuteBatchForm)
    {
        if (ExecuteBatchForm->objectName().isEmpty())
            ExecuteBatchForm->setObjectName("ExecuteBatchForm");
        ExecuteBatchForm->resize(751, 534);
        tableWidget = new QTableWidget(ExecuteBatchForm);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
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
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 621, 531));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(ExecuteBatchForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(620, 10, 131, 501));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        pushButtonSave = new QPushButton(frame);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(10, 450, 111, 28));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSave->setIcon(icon);
        pushButtonInsert = new QPushButton(frame);
        pushButtonInsert->setObjectName("pushButtonInsert");
        pushButtonInsert->setGeometry(QRect(10, 90, 111, 28));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonInsert->setIcon(icon1);
        pushButtonExecuteAll = new QPushButton(frame);
        pushButtonExecuteAll->setObjectName("pushButtonExecuteAll");
        pushButtonExecuteAll->setGeometry(QRect(10, 220, 111, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonExecuteAll->setIcon(icon2);
        pushButtonUp = new QPushButton(frame);
        pushButtonUp->setObjectName("pushButtonUp");
        pushButtonUp->setGeometry(QRect(10, 10, 111, 28));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Up.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUp->setIcon(icon3);
        pushButtonDown = new QPushButton(frame);
        pushButtonDown->setObjectName("pushButtonDown");
        pushButtonDown->setGeometry(QRect(10, 40, 111, 28));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Down.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDown->setIcon(icon4);
        pushButtonDelete = new QPushButton(frame);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(10, 160, 111, 28));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon5);
        pushButtonModify = new QPushButton(frame);
        pushButtonModify->setObjectName("pushButtonModify");
        pushButtonModify->setGeometry(QRect(10, 120, 111, 28));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonModify->setIcon(icon6);
        pushButtonLoad = new QPushButton(frame);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(10, 380, 111, 28));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoad->setIcon(icon7);
        pushButtonExecuteOne = new QPushButton(frame);
        pushButtonExecuteOne->setObjectName("pushButtonExecuteOne");
        pushButtonExecuteOne->setGeometry(QRect(10, 270, 111, 28));
        pushButtonExecuteOne->setIcon(icon2);
        pushButtonStop = new QPushButton(frame);
        pushButtonStop->setObjectName("pushButtonStop");
        pushButtonStop->setGeometry(QRect(10, 310, 111, 28));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Qtres/Stop.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStop->setIcon(icon8);
        pushButtonAppend = new QPushButton(frame);
        pushButtonAppend->setObjectName("pushButtonAppend");
        pushButtonAppend->setGeometry(QRect(10, 410, 111, 28));
        pushButtonAppend->setIcon(icon1);

        retranslateUi(ExecuteBatchForm);

        QMetaObject::connectSlotsByName(ExecuteBatchForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ExecuteBatchForm)
    {
        ExecuteBatchForm->setWindowTitle(QCoreApplication::translate("ExecuteBatchForm", "Execute Batch", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ExecuteBatchForm", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ExecuteBatchForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ExecuteBatchForm", "Command", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ExecuteBatchForm", "Arg1", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ExecuteBatchForm", "Arg2", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ExecuteBatchForm", "Arg3", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("ExecuteBatchForm", "Save", nullptr));
        pushButtonInsert->setText(QCoreApplication::translate("ExecuteBatchForm", "Insert new", nullptr));
        pushButtonExecuteAll->setText(QCoreApplication::translate("ExecuteBatchForm", "Execute all", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("ExecuteBatchForm", "Up", nullptr));
        pushButtonDown->setText(QCoreApplication::translate("ExecuteBatchForm", "Down", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("ExecuteBatchForm", "Delete", nullptr));
        pushButtonModify->setText(QCoreApplication::translate("ExecuteBatchForm", "Modify", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("ExecuteBatchForm", "Load", nullptr));
        pushButtonExecuteOne->setText(QCoreApplication::translate("ExecuteBatchForm", "Execute one", nullptr));
        pushButtonStop->setText(QCoreApplication::translate("ExecuteBatchForm", "Stop", nullptr));
        pushButtonAppend->setText(QCoreApplication::translate("ExecuteBatchForm", "Append", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExecuteBatchForm: public Ui_ExecuteBatchForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXECUTEBATCHFORM_H
