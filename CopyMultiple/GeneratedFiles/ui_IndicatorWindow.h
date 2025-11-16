/********************************************************************************
** Form generated from reading UI file 'IndicatorWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDICATORWINDOW_H
#define UI_INDICATORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IndicatorWindow
{
public:
    QTableWidget *tableWidget;

    void setupUi(QWidget *IndicatorWindow)
    {
        if (IndicatorWindow->objectName().isEmpty())
            IndicatorWindow->setObjectName("IndicatorWindow");
        IndicatorWindow->resize(660, 900);
        IndicatorWindow->setMinimumSize(QSize(660, 900));
        IndicatorWindow->setMaximumSize(QSize(660, 900));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        IndicatorWindow->setFont(font);
        tableWidget = new QTableWidget(IndicatorWindow);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 660, 900));
        tableWidget->setMinimumSize(QSize(660, 900));
        tableWidget->setMaximumSize(QSize(660, 900));
        tableWidget->setSizeIncrement(QSize(0, 0));
        tableWidget->setFont(font);

        retranslateUi(IndicatorWindow);

        QMetaObject::connectSlotsByName(IndicatorWindow);
    } // setupUi

    void retranslateUi(QWidget *IndicatorWindow)
    {
        IndicatorWindow->setWindowTitle(QCoreApplication::translate("IndicatorWindow", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("IndicatorWindow", "File", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("IndicatorWindow", "Dest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IndicatorWindow: public Ui_IndicatorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDICATORWINDOW_H
