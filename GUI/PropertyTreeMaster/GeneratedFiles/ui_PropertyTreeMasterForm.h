/********************************************************************************
** Form generated from reading UI file 'PropertyTreeMasterForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYTREEMASTERFORM_H
#define UI_PROPERTYTREEMASTERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyTreeMasterForm
{
public:
    QTableWidget *tableWidgetCatList;
    QPushButton *pushButtonAddNewCat;
    QLabel *label;

    void setupUi(GUIFormBase *PropertyTreeMasterForm)
    {
        if (PropertyTreeMasterForm->objectName().isEmpty())
            PropertyTreeMasterForm->setObjectName("PropertyTreeMasterForm");
        PropertyTreeMasterForm->resize(400, 700);
        tableWidgetCatList = new QTableWidget(PropertyTreeMasterForm);
        if (tableWidgetCatList->columnCount() < 5)
            tableWidgetCatList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetCatList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetCatList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetCatList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetCatList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetCatList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetCatList->setObjectName("tableWidgetCatList");
        tableWidgetCatList->setGeometry(QRect(10, 80, 381, 611));
        tableWidgetCatList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetCatList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddNewCat = new QPushButton(PropertyTreeMasterForm);
        pushButtonAddNewCat->setObjectName("pushButtonAddNewCat");
        pushButtonAddNewCat->setGeometry(QRect(10, 10, 151, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddNewCat->setIcon(icon);
        label = new QLabel(PropertyTreeMasterForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 381, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(PropertyTreeMasterForm);

        QMetaObject::connectSlotsByName(PropertyTreeMasterForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyTreeMasterForm)
    {
        PropertyTreeMasterForm->setWindowTitle(QCoreApplication::translate("PropertyTreeMasterForm", "Property TreeMaster", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetCatList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyTreeMasterForm", "CatID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetCatList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyTreeMasterForm", "CatName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetCatList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyTreeMasterForm", "Master", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetCatList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyTreeMasterForm", "MasterName", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetCatList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyTreeMasterForm", "Alert", nullptr));
        pushButtonAddNewCat->setText(QCoreApplication::translate("PropertyTreeMasterForm", "Edit", nullptr));
        label->setText(QCoreApplication::translate("PropertyTreeMasterForm", "Category list", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyTreeMasterForm: public Ui_PropertyTreeMasterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYTREEMASTERFORM_H
