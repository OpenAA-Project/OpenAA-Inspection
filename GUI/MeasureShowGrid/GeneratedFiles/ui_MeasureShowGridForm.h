/********************************************************************************
** Form generated from reading UI file 'MeasureShowGridForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASURESHOWGRIDFORM_H
#define UI_MEASURESHOWGRIDFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_MeasureShowGridForm
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSaveCSV;

    void setupUi(GUIFormBase *MeasureShowGridForm)
    {
        if (MeasureShowGridForm->objectName().isEmpty())
            MeasureShowGridForm->setObjectName("MeasureShowGridForm");
        MeasureShowGridForm->resize(352, 493);
        tableWidget = new QTableWidget(MeasureShowGridForm);
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
        tableWidget->setGeometry(QRect(0, 0, 351, 441));
        pushButtonSaveCSV = new QPushButton(MeasureShowGridForm);
        pushButtonSaveCSV->setObjectName("pushButtonSaveCSV");
        pushButtonSaveCSV->setGeometry(QRect(130, 450, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSaveCSV->setIcon(icon);

        retranslateUi(MeasureShowGridForm);

        QMetaObject::connectSlotsByName(MeasureShowGridForm);
    } // setupUi

    void retranslateUi(GUIFormBase *MeasureShowGridForm)
    {
        MeasureShowGridForm->setWindowTitle(QCoreApplication::translate("MeasureShowGridForm", "Measure ShowGrid", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MeasureShowGridForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MeasureShowGridForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MeasureShowGridForm", "Algo/Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MeasureShowGridForm", "Value", nullptr));
        pushButtonSaveCSV->setText(QCoreApplication::translate("MeasureShowGridForm", "Save CSV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeasureShowGridForm: public Ui_MeasureShowGridForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASURESHOWGRIDFORM_H
