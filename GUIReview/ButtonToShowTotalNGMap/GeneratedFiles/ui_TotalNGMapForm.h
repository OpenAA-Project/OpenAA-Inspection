/********************************************************************************
** Form generated from reading UI file 'TotalNGMapForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOTALNGMAPFORM_H
#define UI_TOTALNGMAPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include "stretchimagegraphics.h"

QT_BEGIN_NAMESPACE

class Ui_TotalNGMapClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbClose;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *cbSide;
    QLabel *label;
    QComboBox *cbPhase;
    StretchImageGraphics *gvImageView;
    QTableWidget *twVautTable;

    void setupUi(QDialog *TotalNGMapClass)
    {
        if (TotalNGMapClass->objectName().isEmpty())
            TotalNGMapClass->setObjectName(QString::fromUtf8("TotalNGMapClass"));
        TotalNGMapClass->resize(1054, 702);
        TotalNGMapClass->setMinimumSize(QSize(281, 139));
        gridLayout = new QGridLayout(TotalNGMapClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pbClose = new QPushButton(TotalNGMapClass);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));

        horizontalLayout->addWidget(pbClose);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(TotalNGMapClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        cbSide = new QComboBox(TotalNGMapClass);
        cbSide->addItem(QString());
        cbSide->addItem(QString());
        cbSide->setObjectName(QString::fromUtf8("cbSide"));

        horizontalLayout->addWidget(cbSide);

        label = new QLabel(TotalNGMapClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        cbPhase = new QComboBox(TotalNGMapClass);
        cbPhase->addItem(QString());
        cbPhase->setObjectName(QString::fromUtf8("cbPhase"));

        horizontalLayout->addWidget(cbPhase);


        verticalLayout->addLayout(horizontalLayout);

        gvImageView = new StretchImageGraphics(TotalNGMapClass);
        gvImageView->setObjectName(QString::fromUtf8("gvImageView"));
        gvImageView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        gvImageView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout->addWidget(gvImageView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        twVautTable = new QTableWidget(TotalNGMapClass);
        if (twVautTable->columnCount() < 2)
            twVautTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twVautTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twVautTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (twVautTable->rowCount() < 2)
            twVautTable->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twVautTable->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        twVautTable->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        twVautTable->setItem(0, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        twVautTable->setItem(0, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        twVautTable->setItem(1, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        twVautTable->setItem(1, 1, __qtablewidgetitem7);
        twVautTable->setObjectName(QString::fromUtf8("twVautTable"));
        twVautTable->setMinimumSize(QSize(400, 0));
        twVautTable->setMaximumSize(QSize(16777215, 16777215));
        twVautTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        twVautTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        twVautTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twVautTable->setDragDropOverwriteMode(true);
        twVautTable->setSelectionMode(QAbstractItemView::MultiSelection);
        twVautTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        twVautTable->horizontalHeader()->setVisible(true);
        twVautTable->horizontalHeader()->setCascadingSectionResizes(false);
        twVautTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        twVautTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(twVautTable, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);

        retranslateUi(TotalNGMapClass);

        QMetaObject::connectSlotsByName(TotalNGMapClass);
    } // setupUi

    void retranslateUi(QDialog *TotalNGMapClass)
    {
        TotalNGMapClass->setWindowTitle(QCoreApplication::translate("TotalNGMapClass", "TotalNGMap", nullptr));
        pbClose->setText(QCoreApplication::translate("TotalNGMapClass", "Close", nullptr));
        label_2->setText(QCoreApplication::translate("TotalNGMapClass", "Side", nullptr));
        cbSide->setItemText(0, QCoreApplication::translate("TotalNGMapClass", "Front", nullptr));
        cbSide->setItemText(1, QCoreApplication::translate("TotalNGMapClass", "Back", nullptr));

        label->setText(QCoreApplication::translate("TotalNGMapClass", "Phase", nullptr));
        cbPhase->setItemText(0, QCoreApplication::translate("TotalNGMapClass", "0", nullptr));

        QTableWidgetItem *___qtablewidgetitem = twVautTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TotalNGMapClass", "NGCount", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twVautTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TotalNGMapClass", "Area", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = twVautTable->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TotalNGMapClass", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = twVautTable->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TotalNGMapClass", "2", nullptr));

        const bool __sortingEnabled = twVautTable->isSortingEnabled();
        twVautTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem4 = twVautTable->item(0, 0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TotalNGMapClass", "1000", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = twVautTable->item(0, 1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("TotalNGMapClass", "(100000,100000)-(150000,150000)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = twVautTable->item(1, 0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("TotalNGMapClass", "2000", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = twVautTable->item(1, 1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("TotalNGMapClass", "()", nullptr));
        twVautTable->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class TotalNGMapClass: public Ui_TotalNGMapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOTALNGMAPFORM_H
