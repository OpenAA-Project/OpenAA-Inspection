/********************************************************************************
** Form generated from reading UI file 'ShowBladeSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWBLADESETTINGFORM_H
#define UI_SHOWBLADESETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowBladeSettingForm
{
public:
    QTableWidget *tableWidgetBladeWidth;
    QLabel *label;
    QLabel *label_2;
    QTableWidget *tableWidgetBladeY;
    QLabel *label_3;
    QTableWidget *tableWidgetBladeX;
    QTableWidget *tableWidgetBladeR;
    QLabel *label_4;

    void setupUi(GUIFormBase *ShowBladeSettingForm)
    {
        if (ShowBladeSettingForm->objectName().isEmpty())
            ShowBladeSettingForm->setObjectName("ShowBladeSettingForm");
        ShowBladeSettingForm->resize(278, 326);
        tableWidgetBladeWidth = new QTableWidget(ShowBladeSettingForm);
        if (tableWidgetBladeWidth->columnCount() < 2)
            tableWidgetBladeWidth->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetBladeWidth->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetBladeWidth->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidgetBladeWidth->rowCount() < 2)
            tableWidgetBladeWidth->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetBladeWidth->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetBladeWidth->setVerticalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetBladeWidth->setObjectName("tableWidgetBladeWidth");
        tableWidgetBladeWidth->setGeometry(QRect(40, 0, 231, 81));
        QFont font;
        font.setPointSize(16);
        tableWidgetBladeWidth->setFont(font);
        tableWidgetBladeWidth->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBladeWidth->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBladeWidth->setSelectionMode(QAbstractItemView::SingleSelection);
        label = new QLabel(ShowBladeSettingForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 31, 81));
        QFont font1;
        font1.setPointSize(18);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowBladeSettingForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 90, 31, 81));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        tableWidgetBladeY = new QTableWidget(ShowBladeSettingForm);
        if (tableWidgetBladeY->columnCount() < 2)
            tableWidgetBladeY->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetBladeY->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetBladeY->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        if (tableWidgetBladeY->rowCount() < 3)
            tableWidgetBladeY->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBladeY->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetBladeY->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetBladeY->setVerticalHeaderItem(2, __qtablewidgetitem8);
        tableWidgetBladeY->setObjectName("tableWidgetBladeY");
        tableWidgetBladeY->setGeometry(QRect(40, 90, 231, 91));
        tableWidgetBladeY->setFont(font);
        tableWidgetBladeY->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBladeY->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBladeY->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBladeY->horizontalHeader()->setVisible(false);
        label_3 = new QLabel(ShowBladeSettingForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 180, 31, 71));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);
        tableWidgetBladeX = new QTableWidget(ShowBladeSettingForm);
        if (tableWidgetBladeX->columnCount() < 2)
            tableWidgetBladeX->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetBladeX->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetBladeX->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        if (tableWidgetBladeX->rowCount() < 2)
            tableWidgetBladeX->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetBladeX->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetBladeX->setVerticalHeaderItem(1, __qtablewidgetitem12);
        tableWidgetBladeX->setObjectName("tableWidgetBladeX");
        tableWidgetBladeX->setGeometry(QRect(40, 190, 231, 61));
        tableWidgetBladeX->setFont(font);
        tableWidgetBladeX->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBladeX->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBladeX->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBladeX->horizontalHeader()->setVisible(false);
        tableWidgetBladeR = new QTableWidget(ShowBladeSettingForm);
        if (tableWidgetBladeR->columnCount() < 2)
            tableWidgetBladeR->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetBladeR->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetBladeR->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        if (tableWidgetBladeR->rowCount() < 2)
            tableWidgetBladeR->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetBladeR->setVerticalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetBladeR->setVerticalHeaderItem(1, __qtablewidgetitem16);
        tableWidgetBladeR->setObjectName("tableWidgetBladeR");
        tableWidgetBladeR->setGeometry(QRect(40, 260, 231, 61));
        tableWidgetBladeR->setFont(font);
        tableWidgetBladeR->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBladeR->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBladeR->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBladeR->horizontalHeader()->setVisible(false);
        label_4 = new QLabel(ShowBladeSettingForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 270, 41, 41));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);

        retranslateUi(ShowBladeSettingForm);

        QMetaObject::connectSlotsByName(ShowBladeSettingForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowBladeSettingForm)
    {
        ShowBladeSettingForm->setWindowTitle(QCoreApplication::translate("ShowBladeSettingForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetBladeWidth->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowBladeSettingForm", "\344\270\213\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBladeWidth->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowBladeSettingForm", "\344\270\212\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetBladeWidth->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowBladeSettingForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetBladeWidth->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowBladeSettingForm", "2", nullptr));
        label->setText(QCoreApplication::translate("ShowBladeSettingForm", "<html><head/><body><p>\345\210\203</p><p>\345\267\276</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("ShowBladeSettingForm", "<html><head/><body><p>\351\253\230</p><p>\344\275\216</p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBladeY->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowBladeSettingForm", "\344\270\213\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBladeY->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowBladeSettingForm", "\344\270\212\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBladeY->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ShowBladeSettingForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetBladeY->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ShowBladeSettingForm", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetBladeY->verticalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ShowBladeSettingForm", "C", nullptr));
        label_3->setText(QCoreApplication::translate("ShowBladeSettingForm", "<html><head/><body><p>\345\257\204</p><p>\345\210\203</p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetBladeX->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("ShowBladeSettingForm", "\344\270\213\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetBladeX->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("ShowBladeSettingForm", "\344\270\212\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetBladeX->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("ShowBladeSettingForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetBladeX->verticalHeaderItem(1);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("ShowBladeSettingForm", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetBladeR->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("ShowBladeSettingForm", "\344\270\213\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetBladeR->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("ShowBladeSettingForm", "\344\270\212\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetBladeR->verticalHeaderItem(0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("ShowBladeSettingForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetBladeR->verticalHeaderItem(1);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("ShowBladeSettingForm", "2", nullptr));
        label_4->setText(QCoreApplication::translate("ShowBladeSettingForm", "<html><head/><body><p>Pet</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowBladeSettingForm: public Ui_ShowBladeSettingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWBLADESETTINGFORM_H
