/********************************************************************************
** Form generated from reading UI file 'PropertyMaskingPIForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYMASKINGPIFORM_H
#define UI_PROPERTYMASKINGPIFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyMaskingPIFormClass
{
public:
    QToolButton *toolButtonIneffective;
    QTableWidget *tableWidgetMaskingList;
    QToolButton *toolButtonEffective;
    QPushButton *ButtonGenerateMaskFromSameColor;

    void setupUi(GUIFormBase *PropertyMaskingPIFormClass)
    {
        if (PropertyMaskingPIFormClass->objectName().isEmpty())
            PropertyMaskingPIFormClass->setObjectName("PropertyMaskingPIFormClass");
        PropertyMaskingPIFormClass->resize(400, 700);
        toolButtonIneffective = new QToolButton(PropertyMaskingPIFormClass);
        toolButtonIneffective->setObjectName("toolButtonIneffective");
        toolButtonIneffective->setGeometry(QRect(230, 20, 111, 31));
        toolButtonIneffective->setCheckable(true);
        toolButtonIneffective->setChecked(true);
        toolButtonIneffective->setAutoExclusive(true);
        tableWidgetMaskingList = new QTableWidget(PropertyMaskingPIFormClass);
        if (tableWidgetMaskingList->columnCount() < 4)
            tableWidgetMaskingList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetMaskingList->setObjectName("tableWidgetMaskingList");
        tableWidgetMaskingList->setGeometry(QRect(10, 70, 381, 571));
        tableWidgetMaskingList->setSelectionBehavior(QAbstractItemView::SelectRows);
        toolButtonEffective = new QToolButton(PropertyMaskingPIFormClass);
        toolButtonEffective->setObjectName("toolButtonEffective");
        toolButtonEffective->setGeometry(QRect(50, 20, 111, 31));
        toolButtonEffective->setCheckable(true);
        toolButtonEffective->setChecked(true);
        ButtonGenerateMaskFromSameColor = new QPushButton(PropertyMaskingPIFormClass);
        ButtonGenerateMaskFromSameColor->setObjectName("ButtonGenerateMaskFromSameColor");
        ButtonGenerateMaskFromSameColor->setGeometry(QRect(120, 650, 161, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateMaskFromSameColor->setIcon(icon);

        retranslateUi(PropertyMaskingPIFormClass);

        QMetaObject::connectSlotsByName(PropertyMaskingPIFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyMaskingPIFormClass)
    {
        PropertyMaskingPIFormClass->setWindowTitle(QCoreApplication::translate("PropertyMaskingPIFormClass", "PropertyMaskingPIForm", nullptr));
        toolButtonIneffective->setText(QCoreApplication::translate("PropertyMaskingPIFormClass", "\347\204\241\345\212\271", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetMaskingList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyMaskingPIFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetMaskingList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyMaskingPIFormClass", "Effective", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMaskingList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyMaskingPIFormClass", "Limited", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMaskingList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyMaskingPIFormClass", "Area", nullptr));
        toolButtonEffective->setText(QCoreApplication::translate("PropertyMaskingPIFormClass", "\346\234\211\345\212\271", nullptr));
        ButtonGenerateMaskFromSameColor->setText(QCoreApplication::translate("PropertyMaskingPIFormClass", "\345\220\214\344\270\200\350\274\235\345\272\246\343\201\213\343\202\211\343\201\256\343\203\236\343\202\271\343\202\257\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyMaskingPIFormClass: public Ui_PropertyMaskingPIFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYMASKINGPIFORM_H
