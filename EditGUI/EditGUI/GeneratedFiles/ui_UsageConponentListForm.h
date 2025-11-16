/********************************************************************************
** Form generated from reading UI file 'UsageConponentListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USAGECONPONENTLISTFORM_H
#define UI_USAGECONPONENTLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UsageConponentListForm
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonMakeCopyBAT;
    QPushButton *pushButtonExcludedListOut;

    void setupUi(QWidget *UsageConponentListForm)
    {
        if (UsageConponentListForm->objectName().isEmpty())
            UsageConponentListForm->setObjectName("UsageConponentListForm");
        UsageConponentListForm->resize(611, 439);
        tableWidget = new QTableWidget(UsageConponentListForm);
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
        tableWidget->setGeometry(QRect(0, 0, 611, 391));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(UsageConponentListForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 390, 611, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonClose = new QPushButton(frame);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(510, 10, 91, 31));
        pushButtonDelete = new QPushButton(frame);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(10, 10, 81, 31));
        pushButtonMakeCopyBAT = new QPushButton(frame);
        pushButtonMakeCopyBAT->setObjectName("pushButtonMakeCopyBAT");
        pushButtonMakeCopyBAT->setGeometry(QRect(270, 10, 141, 34));
        pushButtonExcludedListOut = new QPushButton(frame);
        pushButtonExcludedListOut->setObjectName("pushButtonExcludedListOut");
        pushButtonExcludedListOut->setGeometry(QRect(110, 10, 141, 31));

        retranslateUi(UsageConponentListForm);

        QMetaObject::connectSlotsByName(UsageConponentListForm);
    } // setupUi

    void retranslateUi(QWidget *UsageConponentListForm)
    {
        UsageConponentListForm->setWindowTitle(QCoreApplication::translate("UsageConponentListForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("UsageConponentListForm", "DLLRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("UsageConponentListForm", "DLLName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UsageConponentListForm", "InstName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("UsageConponentListForm", "Algorithm", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("UsageConponentListForm", "Close", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("UsageConponentListForm", "Delete", nullptr));
        pushButtonMakeCopyBAT->setText(QCoreApplication::translate("UsageConponentListForm", "Make copy BAT", nullptr));
        pushButtonExcludedListOut->setText(QCoreApplication::translate("UsageConponentListForm", "Excluded List", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UsageConponentListForm: public Ui_UsageConponentListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USAGECONPONENTLISTFORM_H
