/********************************************************************************
** Form generated from reading UI file 'IntegrationShowHistoryLoadImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONSHOWHISTORYLOADIMAGEFORM_H
#define UI_INTEGRATIONSHOWHISTORYLOADIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationShowHistoryLoadImageForm
{
public:
    QTableWidget *tableWidget;
    QFrame *frameBottom;
    QLabel *labelS0;
    QLabel *labelFileNameS0;
    QLabel *labelTotalCount;
    QLabel *labelTotal;
    QToolButton *toolButtonOnlyNG;

    void setupUi(GUIFormBase *IntegrationShowHistoryLoadImageForm)
    {
        if (IntegrationShowHistoryLoadImageForm->objectName().isEmpty())
            IntegrationShowHistoryLoadImageForm->setObjectName("IntegrationShowHistoryLoadImageForm");
        IntegrationShowHistoryLoadImageForm->resize(419, 442);
        tableWidget = new QTableWidget(IntegrationShowHistoryLoadImageForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 421, 331));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        frameBottom = new QFrame(IntegrationShowHistoryLoadImageForm);
        frameBottom->setObjectName("frameBottom");
        frameBottom->setGeometry(QRect(0, 330, 421, 111));
        frameBottom->setFrameShape(QFrame::StyledPanel);
        frameBottom->setFrameShadow(QFrame::Raised);
        labelS0 = new QLabel(frameBottom);
        labelS0->setObjectName("labelS0");
        labelS0->setGeometry(QRect(10, 10, 81, 21));
        labelS0->setFrameShape(QFrame::Panel);
        labelS0->setFrameShadow(QFrame::Sunken);
        labelFileNameS0 = new QLabel(frameBottom);
        labelFileNameS0->setObjectName("labelFileNameS0");
        labelFileNameS0->setGeometry(QRect(90, 10, 321, 21));
        labelFileNameS0->setFrameShape(QFrame::Panel);
        labelFileNameS0->setFrameShadow(QFrame::Sunken);
        labelTotalCount = new QLabel(frameBottom);
        labelTotalCount->setObjectName("labelTotalCount");
        labelTotalCount->setGeometry(QRect(310, 90, 100, 21));
        labelTotalCount->setFrameShape(QFrame::Panel);
        labelTotalCount->setFrameShadow(QFrame::Sunken);
        labelTotal = new QLabel(frameBottom);
        labelTotal->setObjectName("labelTotal");
        labelTotal->setGeometry(QRect(80, 90, 221, 21));
        labelTotal->setFrameShape(QFrame::Panel);
        labelTotal->setFrameShadow(QFrame::Sunken);
        labelTotal->setAlignment(Qt::AlignCenter);
        toolButtonOnlyNG = new QToolButton(frameBottom);
        toolButtonOnlyNG->setObjectName("toolButtonOnlyNG");
        toolButtonOnlyNG->setGeometry(QRect(0, 90, 81, 21));
        toolButtonOnlyNG->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: rgb(70, 70, 70);		\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(128, 225, 128, 255), stop:1 rgba(50, 141, 50, 255));\n"
"}"));
        toolButtonOnlyNG->setCheckable(true);
        toolButtonOnlyNG->setChecked(true);

        retranslateUi(IntegrationShowHistoryLoadImageForm);

        QMetaObject::connectSlotsByName(IntegrationShowHistoryLoadImageForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationShowHistoryLoadImageForm)
    {
        IntegrationShowHistoryLoadImageForm->setWindowTitle(QCoreApplication::translate("IntegrationShowHistoryLoadImageForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("IntegrationShowHistoryLoadImageForm", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("IntegrationShowHistoryLoadImageForm", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("IntegrationShowHistoryLoadImageForm", "S0", nullptr));
        labelS0->setText(QCoreApplication::translate("IntegrationShowHistoryLoadImageForm", "TextLabel", nullptr));
        labelFileNameS0->setText(QCoreApplication::translate("IntegrationShowHistoryLoadImageForm", "TextLabel", nullptr));
        labelTotalCount->setText(QCoreApplication::translate("IntegrationShowHistoryLoadImageForm", "TextLabel", nullptr));
        labelTotal->setText(QCoreApplication::translate("IntegrationShowHistoryLoadImageForm", "\346\244\234\346\237\273\345\261\245\346\255\264\346\225\260", nullptr));
        toolButtonOnlyNG->setText(QCoreApplication::translate("IntegrationShowHistoryLoadImageForm", "NG\343\201\256\343\201\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationShowHistoryLoadImageForm: public Ui_IntegrationShowHistoryLoadImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONSHOWHISTORYLOADIMAGEFORM_H
