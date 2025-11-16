/********************************************************************************
** Form generated from reading UI file 'ShowLEDControl16GForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWLEDCONTROL16GFORM_H
#define UI_SHOWLEDCONTROL16GFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowLEDControl16GForm
{
public:
    QToolButton *toolButtonAllON;
    QLabel *label_3;
    QTableWidget *tableWidget;
    QLabel *label_4;
    QToolButton *toolButtonSave;
    QListWidget *listWidgetDipSW;
    QPushButton *pushButtonUpdate;
    QSpinBox *spinBoxPatternNo;

    void setupUi(QWidget *ShowLEDControl16GForm)
    {
        if (ShowLEDControl16GForm->objectName().isEmpty())
            ShowLEDControl16GForm->setObjectName(QString::fromUtf8("ShowLEDControl16GForm"));
        ShowLEDControl16GForm->resize(315, 500);
        toolButtonAllON = new QToolButton(ShowLEDControl16GForm);
        toolButtonAllON->setObjectName(QString::fromUtf8("toolButtonAllON"));
        toolButtonAllON->setGeometry(QRect(100, 460, 91, 31));
        toolButtonAllON->setCheckable(true);
        toolButtonAllON->setChecked(false);
        label_3 = new QLabel(ShowLEDControl16GForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 51, 18));
        tableWidget = new QTableWidget(ShowLEDControl16GForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 16)
            tableWidget->setRowCount(16);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(15, __qtablewidgetitem17);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(70, 40, 231, 411));
        QFont font;
        font.setPointSize(8);
        tableWidget->setFont(font);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->verticalHeader()->setMinimumSectionSize(24);
        tableWidget->verticalHeader()->setDefaultSectionSize(23);
        label_4 = new QLabel(ShowLEDControl16GForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 10, 75, 21));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        toolButtonSave = new QToolButton(ShowLEDControl16GForm);
        toolButtonSave->setObjectName(QString::fromUtf8("toolButtonSave"));
        toolButtonSave->setGeometry(QRect(200, 460, 91, 31));
        toolButtonSave->setCheckable(true);
        toolButtonSave->setChecked(false);
        listWidgetDipSW = new QListWidget(ShowLEDControl16GForm);
        listWidgetDipSW->setObjectName(QString::fromUtf8("listWidgetDipSW"));
        listWidgetDipSW->setGeometry(QRect(10, 40, 51, 371));
        pushButtonUpdate = new QPushButton(ShowLEDControl16GForm);
        pushButtonUpdate->setObjectName(QString::fromUtf8("pushButtonUpdate"));
        pushButtonUpdate->setGeometry(QRect(10, 420, 51, 23));
        spinBoxPatternNo = new QSpinBox(ShowLEDControl16GForm);
        spinBoxPatternNo->setObjectName(QString::fromUtf8("spinBoxPatternNo"));
        spinBoxPatternNo->setGeometry(QRect(170, 10, 81, 24));
        spinBoxPatternNo->setMaximum(15);

        retranslateUi(ShowLEDControl16GForm);

        QMetaObject::connectSlotsByName(ShowLEDControl16GForm);
    } // setupUi

    void retranslateUi(QWidget *ShowLEDControl16GForm)
    {
        ShowLEDControl16GForm->setWindowTitle(QCoreApplication::translate("ShowLEDControl16GForm", "Form", nullptr));
        toolButtonAllON->setText(QCoreApplication::translate("ShowLEDControl16GForm", "All ON", nullptr));
        label_3->setText(QCoreApplication::translate("ShowLEDControl16GForm", "DipSW", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowLEDControl16GForm", "Target", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowLEDControl16GForm", "Now", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowLEDControl16GForm", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowLEDControl16GForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowLEDControl16GForm", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowLEDControl16GForm", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ShowLEDControl16GForm", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ShowLEDControl16GForm", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ShowLEDControl16GForm", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("ShowLEDControl16GForm", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("ShowLEDControl16GForm", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("ShowLEDControl16GForm", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("ShowLEDControl16GForm", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("ShowLEDControl16GForm", "11", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("ShowLEDControl16GForm", "12", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("ShowLEDControl16GForm", "13", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("ShowLEDControl16GForm", "14", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("ShowLEDControl16GForm", "15", nullptr));
        label_4->setText(QCoreApplication::translate("ShowLEDControl16GForm", "Pattern", nullptr));
        toolButtonSave->setText(QCoreApplication::translate("ShowLEDControl16GForm", "Save", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("ShowLEDControl16GForm", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowLEDControl16GForm: public Ui_ShowLEDControl16GForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWLEDCONTROL16GFORM_H
