/********************************************************************************
** Form generated from reading UI file 'FormAutoSaveImageSelectLot.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMAUTOSAVEIMAGESELECTLOT_H
#define UI_FORMAUTOSAVEIMAGESELECTLOT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_FormAutoSaveImageSelectLotClass
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *FormAutoSaveImageSelectLotClass)
    {
        if (FormAutoSaveImageSelectLotClass->objectName().isEmpty())
            FormAutoSaveImageSelectLotClass->setObjectName("FormAutoSaveImageSelectLotClass");
        FormAutoSaveImageSelectLotClass->resize(356, 250);
        tableWidget = new QTableWidget(FormAutoSaveImageSelectLotClass);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 331, 192));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(FormAutoSaveImageSelectLotClass);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(50, 210, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        pushButtonCancel = new QPushButton(FormAutoSaveImageSelectLotClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(200, 210, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(FormAutoSaveImageSelectLotClass);

        QMetaObject::connectSlotsByName(FormAutoSaveImageSelectLotClass);
    } // setupUi

    void retranslateUi(QDialog *FormAutoSaveImageSelectLotClass)
    {
        FormAutoSaveImageSelectLotClass->setWindowTitle(QCoreApplication::translate("FormAutoSaveImageSelectLotClass", "FormAutoSaveImageSelectLot", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("FormAutoSaveImageSelectLotClass", "Lot", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("FormAutoSaveImageSelectLotClass", "\351\201\270\346\212\236", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("FormAutoSaveImageSelectLotClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormAutoSaveImageSelectLotClass: public Ui_FormAutoSaveImageSelectLotClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMAUTOSAVEIMAGESELECTLOT_H
