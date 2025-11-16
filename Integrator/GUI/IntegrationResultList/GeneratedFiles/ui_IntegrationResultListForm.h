/********************************************************************************
** Form generated from reading UI file 'IntegrationResultListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONRESULTLISTFORM_H
#define UI_INTEGRATIONRESULTLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationResultListForm
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QLabel *label_3;
    QLineEdit *lineEditTotalCount;

    void setupUi(GUIFormBase *IntegrationResultListForm)
    {
        if (IntegrationResultListForm->objectName().isEmpty())
            IntegrationResultListForm->setObjectName("IntegrationResultListForm");
        IntegrationResultListForm->resize(391, 415);
        tableWidget = new QTableWidget(IntegrationResultListForm);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 391, 391));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(IntegrationResultListForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(90, 390, 231, 21));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 0, 75, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        lineEditTotalCount = new QLineEdit(frame);
        lineEditTotalCount->setObjectName("lineEditTotalCount");
        lineEditTotalCount->setGeometry(QRect(100, 0, 131, 24));
        lineEditTotalCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditTotalCount->setReadOnly(true);

        retranslateUi(IntegrationResultListForm);

        QMetaObject::connectSlotsByName(IntegrationResultListForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationResultListForm)
    {
        IntegrationResultListForm->setWindowTitle(QCoreApplication::translate("IntegrationResultListForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("IntegrationResultListForm", "Mac", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("IntegrationResultListForm", "Pos", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("IntegrationResultListForm", "Cause", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("IntegrationResultListForm", "Value", nullptr));
        label_3->setText(QCoreApplication::translate("IntegrationResultListForm", "Total", nullptr));
        lineEditTotalCount->setText(QCoreApplication::translate("IntegrationResultListForm", "100", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationResultListForm: public Ui_IntegrationResultListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONRESULTLISTFORM_H
