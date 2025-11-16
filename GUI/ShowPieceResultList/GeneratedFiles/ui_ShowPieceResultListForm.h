/********************************************************************************
** Form generated from reading UI file 'ShowPieceResultListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWPIECERESULTLISTFORM_H
#define UI_SHOWPIECERESULTLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_ShowPieceResultListForm
{
public:
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *ShowPieceResultListForm)
    {
        if (ShowPieceResultListForm->objectName().isEmpty())
            ShowPieceResultListForm->setObjectName("ShowPieceResultListForm");
        ShowPieceResultListForm->resize(400, 300);
        tableWidget = new QTableWidget(ShowPieceResultListForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 401, 161));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        tableWidget->setFont(font);

        retranslateUi(ShowPieceResultListForm);

        QMetaObject::connectSlotsByName(ShowPieceResultListForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowPieceResultListForm)
    {
        ShowPieceResultListForm->setWindowTitle(QCoreApplication::translate("ShowPieceResultListForm", "Show PieceResult list", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowPieceResultListForm", "Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowPieceResultListForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowPieceResultListForm", "Result", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowPieceResultListForm: public Ui_ShowPieceResultListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWPIECERESULTLISTFORM_H
