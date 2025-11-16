/********************************************************************************
** Form generated from reading UI file 'SelectLibrariesForAnyType.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARIESFORANYTYPE_H
#define UI_SELECTLIBRARIESFORANYTYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibrariesForAnyType
{
public:
    QLabel *label_2;
    QLabel *label;
    QComboBox *comboBLibType;
    QTableWidget *tableWidgetSelectedList;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;

    void setupUi(QWidget *SelectLibrariesForAnyType)
    {
        if (SelectLibrariesForAnyType->objectName().isEmpty())
            SelectLibrariesForAnyType->setObjectName("SelectLibrariesForAnyType");
        SelectLibrariesForAnyType->resize(423, 351);
        label_2 = new QLabel(SelectLibrariesForAnyType);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-10, 330, 211, 20));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(SelectLibrariesForAnyType);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 160, 201, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBLibType = new QComboBox(SelectLibrariesForAnyType);
        comboBLibType->setObjectName("comboBLibType");
        comboBLibType->setGeometry(QRect(0, 0, 201, 22));
        tableWidgetSelectedList = new QTableWidget(SelectLibrariesForAnyType);
        if (tableWidgetSelectedList->columnCount() < 2)
            tableWidgetSelectedList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetSelectedList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetSelectedList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetSelectedList->setObjectName("tableWidgetSelectedList");
        tableWidgetSelectedList->setGeometry(QRect(210, 180, 201, 151));
        tableWidgetSelectedList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelectedList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(SelectLibrariesForAnyType);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(0, 20, 201, 161));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(SelectLibrariesForAnyType);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(0, 180, 201, 151));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(SelectLibrariesForAnyType);

        QMetaObject::connectSlotsByName(SelectLibrariesForAnyType);
    } // setupUi

    void retranslateUi(QWidget *SelectLibrariesForAnyType)
    {
        SelectLibrariesForAnyType->setWindowTitle(QCoreApplication::translate("SelectLibrariesForAnyType", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("SelectLibrariesForAnyType", "Double Click in Set/Reset", nullptr));
        label->setText(QCoreApplication::translate("SelectLibrariesForAnyType", "Selected", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetSelectedList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibrariesForAnyType", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetSelectedList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibrariesForAnyType", "\345\220\215\345\211\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectLibrariesForAnyType", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectLibrariesForAnyType", "\345\220\215\345\211\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibrariesForAnyType: public Ui_SelectLibrariesForAnyType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARIESFORANYTYPE_H
