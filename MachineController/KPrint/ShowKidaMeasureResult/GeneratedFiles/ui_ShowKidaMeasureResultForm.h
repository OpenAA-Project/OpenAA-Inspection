/********************************************************************************
** Form generated from reading UI file 'ShowKidaMeasureResultForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWKIDAMEASURERESULTFORM_H
#define UI_SHOWKIDAMEASURERESULTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowKidaMeasureResultForm
{
public:
    QLabel *label;
    QTableWidget *tableWidgetW;
    QTableWidget *tableWidgetY;
    QTableWidget *tableWidgetX;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QTableWidget *tableWidgetR;
    QLabel *label_5;

    void setupUi(GUIFormBase *ShowKidaMeasureResultForm)
    {
        if (ShowKidaMeasureResultForm->objectName().isEmpty())
            ShowKidaMeasureResultForm->setObjectName("ShowKidaMeasureResultForm");
        ShowKidaMeasureResultForm->resize(253, 331);
        label = new QLabel(ShowKidaMeasureResultForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 256, 30));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        tableWidgetW = new QTableWidget(ShowKidaMeasureResultForm);
        if (tableWidgetW->columnCount() < 1)
            tableWidgetW->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetW->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidgetW->rowCount() < 2)
            tableWidgetW->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetW->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetW->setVerticalHeaderItem(1, __qtablewidgetitem2);
        tableWidgetW->setObjectName("tableWidgetW");
        tableWidgetW->setGeometry(QRect(50, 30, 201, 61));
        QFont font1;
        font1.setPointSize(12);
        tableWidgetW->setFont(font1);
        tableWidgetW->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetW->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetW->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidgetW->horizontalHeader()->setVisible(false);
        tableWidgetY = new QTableWidget(ShowKidaMeasureResultForm);
        if (tableWidgetY->columnCount() < 1)
            tableWidgetY->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetY->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        if (tableWidgetY->rowCount() < 3)
            tableWidgetY->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetY->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetY->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetY->setVerticalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetY->setObjectName("tableWidgetY");
        tableWidgetY->setGeometry(QRect(50, 100, 201, 91));
        tableWidgetY->setFont(font1);
        tableWidgetY->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetY->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetY->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidgetY->horizontalHeader()->setVisible(false);
        tableWidgetX = new QTableWidget(ShowKidaMeasureResultForm);
        if (tableWidgetX->columnCount() < 1)
            tableWidgetX->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetX->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        if (tableWidgetX->rowCount() < 2)
            tableWidgetX->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetX->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetX->setVerticalHeaderItem(1, __qtablewidgetitem9);
        tableWidgetX->setObjectName("tableWidgetX");
        tableWidgetX->setGeometry(QRect(50, 200, 201, 61));
        tableWidgetX->setFont(font1);
        tableWidgetX->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetX->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetX->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidgetX->horizontalHeader()->setVisible(false);
        label_3 = new QLabel(ShowKidaMeasureResultForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 200, 31, 61));
        QFont font2;
        font2.setPointSize(14);
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowKidaMeasureResultForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 30, 31, 71));
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(ShowKidaMeasureResultForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 100, 31, 91));
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignCenter);
        tableWidgetR = new QTableWidget(ShowKidaMeasureResultForm);
        if (tableWidgetR->columnCount() < 1)
            tableWidgetR->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetR->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        if (tableWidgetR->rowCount() < 2)
            tableWidgetR->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetR->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetR->setVerticalHeaderItem(1, __qtablewidgetitem12);
        tableWidgetR->setObjectName("tableWidgetR");
        tableWidgetR->setGeometry(QRect(50, 270, 201, 61));
        tableWidgetR->setFont(font1);
        tableWidgetR->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetR->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetR->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidgetR->horizontalHeader()->setVisible(false);
        label_5 = new QLabel(ShowKidaMeasureResultForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 270, 41, 61));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        retranslateUi(ShowKidaMeasureResultForm);

        QMetaObject::connectSlotsByName(ShowKidaMeasureResultForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowKidaMeasureResultForm)
    {
        ShowKidaMeasureResultForm->setWindowTitle(QCoreApplication::translate("ShowKidaMeasureResultForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "\345\210\203 \346\244\234\346\237\273\346\203\205\345\240\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetW->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "\345\210\203\345\267\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetW->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetW->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetY->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "\351\253\230\344\275\216", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetY->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetY->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetY->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "C", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetX->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "\345\257\204\345\210\203", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetX->verticalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetX->verticalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "2", nullptr));
        label_3->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "<html><head/><body><p>\345\257\204</p><p>\345\210\203</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "<html><head/><body><p>\345\210\203</p><p>\345\267\276</p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "<html><head/><body><p>\351\253\230</p><p>\344\275\216</p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetR->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "\345\257\204\345\210\203", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetR->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetR->verticalHeaderItem(1);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "2", nullptr));
        label_5->setText(QCoreApplication::translate("ShowKidaMeasureResultForm", "<html><head/><body><p>Pet</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowKidaMeasureResultForm: public Ui_ShowKidaMeasureResultForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWKIDAMEASURERESULTFORM_H
