/********************************************************************************
** Form generated from reading UI file 'ListResultFrameForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTRESULTFRAMEFORM_H
#define UI_LISTRESULTFRAMEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ListResultFrameForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *ListResultFrameForm)
    {
        if (ListResultFrameForm->objectName().isEmpty())
            ListResultFrameForm->setObjectName(QString::fromUtf8("ListResultFrameForm"));
        ListResultFrameForm->resize(315, 192);
        tableWidget = new QTableWidget(ListResultFrameForm);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 321, 191));

        retranslateUi(ListResultFrameForm);

        QMetaObject::connectSlotsByName(ListResultFrameForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ListResultFrameForm)
    {
        ListResultFrameForm->setWindowTitle(QCoreApplication::translate("ListResultFrameForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ListResultFrameForm", "Group", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ListResultFrameForm", "Size", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListResultFrameForm: public Ui_ListResultFrameForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTRESULTFRAMEFORM_H
