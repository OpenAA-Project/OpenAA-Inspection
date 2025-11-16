/********************************************************************************
** Form generated from reading UI file 'SetDefinitionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDEFINITIONDIALOG_H
#define UI_SETDEFINITIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SetDefinitionDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QLabel *label;
    QSpinBox *spinBoxCountOfUnit;
    QSpinBox *spinBoxCountOfBoard;
    QLabel *label_2;
    QPushButton *pushButtonSetCount;
    QSpinBox *spinBoxBaseCounter;
    QLabel *label_3;

    void setupUi(QDialog *SetDefinitionDialog)
    {
        if (SetDefinitionDialog->objectName().isEmpty())
            SetDefinitionDialog->setObjectName("SetDefinitionDialog");
        SetDefinitionDialog->resize(734, 739);
        tableWidget = new QTableWidget(SetDefinitionDialog);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 100, 711, 581));
        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButton = new QPushButton(SetDefinitionDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(300, 690, 131, 34));
        label = new QLabel(SetDefinitionDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 151, 31));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        spinBoxCountOfUnit = new QSpinBox(SetDefinitionDialog);
        spinBoxCountOfUnit->setObjectName("spinBoxCountOfUnit");
        spinBoxCountOfUnit->setGeometry(QRect(180, 10, 71, 31));
        spinBoxCountOfUnit->setValue(1);
        spinBoxCountOfBoard = new QSpinBox(SetDefinitionDialog);
        spinBoxCountOfBoard->setObjectName("spinBoxCountOfBoard");
        spinBoxCountOfBoard->setGeometry(QRect(180, 50, 71, 31));
        spinBoxCountOfBoard->setValue(3);
        label_2 = new QLabel(SetDefinitionDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 50, 151, 31));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        pushButtonSetCount = new QPushButton(SetDefinitionDialog);
        pushButtonSetCount->setObjectName("pushButtonSetCount");
        pushButtonSetCount->setGeometry(QRect(270, 40, 112, 34));
        spinBoxBaseCounter = new QSpinBox(SetDefinitionDialog);
        spinBoxBaseCounter->setObjectName("spinBoxBaseCounter");
        spinBoxBaseCounter->setGeometry(QRect(180, 690, 91, 31));
        spinBoxBaseCounter->setMinimum(1024);
        spinBoxBaseCounter->setMaximum(65535);
        spinBoxBaseCounter->setValue(65535);
        label_3 = new QLabel(SetDefinitionDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 690, 151, 31));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);

        retranslateUi(SetDefinitionDialog);

        QMetaObject::connectSlotsByName(SetDefinitionDialog);
    } // setupUi

    void retranslateUi(QDialog *SetDefinitionDialog)
    {
        SetDefinitionDialog->setWindowTitle(QCoreApplication::translate("SetDefinitionDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SetDefinitionDialog", "Unit", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SetDefinitionDialog", "Board", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SetDefinitionDialog", "LineNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SetDefinitionDialog", "Color", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SetDefinitionDialog", "Max", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SetDefinitionDialog", "Comment", nullptr));
        pushButton->setText(QCoreApplication::translate("SetDefinitionDialog", "OK", nullptr));
        label->setText(QCoreApplication::translate("SetDefinitionDialog", "Unit count", nullptr));
        label_2->setText(QCoreApplication::translate("SetDefinitionDialog", "board count in unit", nullptr));
        pushButtonSetCount->setText(QCoreApplication::translate("SetDefinitionDialog", "Set", nullptr));
        label_3->setText(QCoreApplication::translate("SetDefinitionDialog", "Base counter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetDefinitionDialog: public Ui_SetDefinitionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDEFINITIONDIALOG_H
