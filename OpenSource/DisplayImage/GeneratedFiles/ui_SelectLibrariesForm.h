/********************************************************************************
** Form generated from reading UI file 'SelectLibrariesForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARIESFORM_H
#define UI_SELECTLIBRARIESFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibrariesForm
{
public:
    QLabel *label;
    QTableWidget *tableWidgetSelectedList;
    QLabel *label_2;
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;

    void setupUi(QWidget *SelectLibrariesForm)
    {
        if (SelectLibrariesForm->objectName().isEmpty())
            SelectLibrariesForm->setObjectName("SelectLibrariesForm");
        SelectLibrariesForm->resize(442, 342);
        label = new QLabel(SelectLibrariesForm);
        label->setObjectName("label");
        label->setGeometry(QRect(220, 140, 201, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetSelectedList = new QTableWidget(SelectLibrariesForm);
        if (tableWidgetSelectedList->columnCount() < 2)
            tableWidgetSelectedList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetSelectedList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetSelectedList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetSelectedList->setObjectName("tableWidgetSelectedList");
        tableWidgetSelectedList->setGeometry(QRect(220, 160, 201, 141));
        tableWidgetSelectedList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelectedList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(SelectLibrariesForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 299, 201, 41));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(SelectLibrariesForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 160, 201, 141));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(SelectLibrariesForm);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);

        retranslateUi(SelectLibrariesForm);

        QMetaObject::connectSlotsByName(SelectLibrariesForm);
    } // setupUi

    void retranslateUi(QWidget *SelectLibrariesForm)
    {
        SelectLibrariesForm->setWindowTitle(QCoreApplication::translate("SelectLibrariesForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("SelectLibrariesForm", "Selected", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetSelectedList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibrariesForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetSelectedList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibrariesForm", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("SelectLibrariesForm", "Double Click in Set/Reset", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectLibrariesForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectLibrariesForm", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibrariesForm: public Ui_SelectLibrariesForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARIESFORM_H
