/********************************************************************************
** Form generated from reading UI file 'ShowSwitchPhaseResultListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSWITCHPHASERESULTLISTFORM_H
#define UI_SHOWSWITCHPHASERESULTLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowSwitchPhaseResultListForm
{
public:
    QStackedWidget *stackedWidget;
    QWidget *Horizontal;
    QTableWidget *tableWidgetHorizontal;
    QWidget *Vertical;
    QTableWidget *tableWidgetVertical;
    QPushButton *pushButtonClear;

    void setupUi(GUIFormBase *ShowSwitchPhaseResultListForm)
    {
        if (ShowSwitchPhaseResultListForm->objectName().isEmpty())
            ShowSwitchPhaseResultListForm->setObjectName("ShowSwitchPhaseResultListForm");
        ShowSwitchPhaseResultListForm->resize(400, 300);
        stackedWidget = new QStackedWidget(ShowSwitchPhaseResultListForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 391, 211));
        Horizontal = new QWidget();
        Horizontal->setObjectName("Horizontal");
        tableWidgetHorizontal = new QTableWidget(Horizontal);
        if (tableWidgetHorizontal->columnCount() < 3)
            tableWidgetHorizontal->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetHorizontal->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetHorizontal->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetHorizontal->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetHorizontal->setObjectName("tableWidgetHorizontal");
        tableWidgetHorizontal->setGeometry(QRect(0, 0, 361, 71));
        stackedWidget->addWidget(Horizontal);
        Vertical = new QWidget();
        Vertical->setObjectName("Vertical");
        tableWidgetVertical = new QTableWidget(Vertical);
        if (tableWidgetVertical->columnCount() < 2)
            tableWidgetVertical->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetVertical->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetVertical->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetVertical->setObjectName("tableWidgetVertical");
        tableWidgetVertical->setGeometry(QRect(10, 10, 211, 181));
        stackedWidget->addWidget(Vertical);
        pushButtonClear = new QPushButton(ShowSwitchPhaseResultListForm);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(0, 270, 112, 34));

        retranslateUi(ShowSwitchPhaseResultListForm);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ShowSwitchPhaseResultListForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowSwitchPhaseResultListForm)
    {
        ShowSwitchPhaseResultListForm->setWindowTitle(QCoreApplication::translate("ShowSwitchPhaseResultListForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetHorizontal->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowSwitchPhaseResultListForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetHorizontal->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowSwitchPhaseResultListForm", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetHorizontal->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowSwitchPhaseResultListForm", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetVertical->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowSwitchPhaseResultListForm", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetVertical->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowSwitchPhaseResultListForm", "Count", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("ShowSwitchPhaseResultListForm", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowSwitchPhaseResultListForm: public Ui_ShowSwitchPhaseResultListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSWITCHPHASERESULTLISTFORM_H
