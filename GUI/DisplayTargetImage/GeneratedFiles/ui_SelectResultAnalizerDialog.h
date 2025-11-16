/********************************************************************************
** Form generated from reading UI file 'SelectResultAnalizerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTRESULTANALIZERDIALOG_H
#define UI_SELECTRESULTANALIZERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectResultAnalizerDialog
{
public:
    QWidget *widget;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSelect;
    QTableWidget *tableWidgetResultAnalizerItemBase;

    void setupUi(QDialog *SelectResultAnalizerDialog)
    {
        if (SelectResultAnalizerDialog->objectName().isEmpty())
            SelectResultAnalizerDialog->setObjectName("SelectResultAnalizerDialog");
        SelectResultAnalizerDialog->resize(400, 241);
        widget = new QWidget(SelectResultAnalizerDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 190, 401, 51));
        pushButtonCancel = new QPushButton(widget);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(250, 10, 112, 34));
        pushButtonSelect = new QPushButton(widget);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(20, 10, 112, 34));
        tableWidgetResultAnalizerItemBase = new QTableWidget(SelectResultAnalizerDialog);
        if (tableWidgetResultAnalizerItemBase->columnCount() < 3)
            tableWidgetResultAnalizerItemBase->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetResultAnalizerItemBase->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetResultAnalizerItemBase->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetResultAnalizerItemBase->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetResultAnalizerItemBase->setObjectName("tableWidgetResultAnalizerItemBase");
        tableWidgetResultAnalizerItemBase->setGeometry(QRect(0, -10, 401, 192));

        retranslateUi(SelectResultAnalizerDialog);

        QMetaObject::connectSlotsByName(SelectResultAnalizerDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectResultAnalizerDialog)
    {
        SelectResultAnalizerDialog->setWindowTitle(QCoreApplication::translate("SelectResultAnalizerDialog", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectResultAnalizerDialog", "Cancel", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectResultAnalizerDialog", "\351\201\270\346\212\236", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetResultAnalizerItemBase->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectResultAnalizerDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetResultAnalizerItemBase->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectResultAnalizerDialog", "Comp name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetResultAnalizerItemBase->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectResultAnalizerDialog", "Usage name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectResultAnalizerDialog: public Ui_SelectResultAnalizerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTRESULTANALIZERDIALOG_H
