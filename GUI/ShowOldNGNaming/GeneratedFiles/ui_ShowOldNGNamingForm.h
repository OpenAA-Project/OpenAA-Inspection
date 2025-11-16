/********************************************************************************
** Form generated from reading UI file 'ShowOldNGNamingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWOLDNGNAMINGFORM_H
#define UI_SHOWOLDNGNAMINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowOldNGNamingForm
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonGetNow;

    void setupUi(GUIFormBase *ShowOldNGNamingForm)
    {
        if (ShowOldNGNamingForm->objectName().isEmpty())
            ShowOldNGNamingForm->setObjectName("ShowOldNGNamingForm");
        ShowOldNGNamingForm->resize(354, 562);
        tableWidget = new QTableWidget(ShowOldNGNamingForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 22, 321, 521));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonGetNow = new QPushButton(ShowOldNGNamingForm);
        pushButtonGetNow->setObjectName("pushButtonGetNow");
        pushButtonGetNow->setGeometry(QRect(0, 0, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGetNow->setIcon(icon);

        retranslateUi(ShowOldNGNamingForm);

        QMetaObject::connectSlotsByName(ShowOldNGNamingForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowOldNGNamingForm)
    {
        ShowOldNGNamingForm->setWindowTitle(QCoreApplication::translate("ShowOldNGNamingForm", "Show old NG Naming", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowOldNGNamingForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowOldNGNamingForm", "Center Pos", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowOldNGNamingForm", "NG", nullptr));
        pushButtonGetNow->setText(QCoreApplication::translate("ShowOldNGNamingForm", "Get Now", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowOldNGNamingForm: public Ui_ShowOldNGNamingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWOLDNGNAMINGFORM_H
