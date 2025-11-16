/********************************************************************************
** Form generated from reading UI file 'ShowResultFrameForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULTFRAMEFORM_H
#define UI_SHOWRESULTFRAMEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ShowResultFrameForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *ShowResultFrameForm)
    {
        if (ShowResultFrameForm->objectName().isEmpty())
            ShowResultFrameForm->setObjectName("ShowResultFrameForm");
        ShowResultFrameForm->resize(460, 188);
        tableWidget = new QTableWidget(ShowResultFrameForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 461, 191));

        retranslateUi(ShowResultFrameForm);

        QMetaObject::connectSlotsByName(ShowResultFrameForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowResultFrameForm)
    {
        ShowResultFrameForm->setWindowTitle(QCoreApplication::translate("ShowResultFrameForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowResultFrameForm", "Group No", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowResultFrameForm", "Frame No", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowResultFrameForm", "NG Count", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowResultFrameForm: public Ui_ShowResultFrameForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULTFRAMEFORM_H
