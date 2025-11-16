/********************************************************************************
** Form generated from reading UI file 'StatisticNGForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICNGFORM_H
#define UI_STATISTICNGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatisticNGClass
{
public:
    QGridLayout *gridLayout;
    QPushButton *pbShowDetail;
    QPushButton *pbSaveToFile;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tblMain;

    void setupUi(QWidget *StatisticNGClass)
    {
        if (StatisticNGClass->objectName().isEmpty())
            StatisticNGClass->setObjectName(QString::fromUtf8("StatisticNGClass"));
        StatisticNGClass->resize(455, 191);
        gridLayout = new QGridLayout(StatisticNGClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbShowDetail = new QPushButton(StatisticNGClass);
        pbShowDetail->setObjectName(QString::fromUtf8("pbShowDetail"));

        gridLayout->addWidget(pbShowDetail, 1, 1, 1, 1);

        pbSaveToFile = new QPushButton(StatisticNGClass);
        pbSaveToFile->setObjectName(QString::fromUtf8("pbSaveToFile"));

        gridLayout->addWidget(pbSaveToFile, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        tblMain = new QTableWidget(StatisticNGClass);
        if (tblMain->columnCount() < 14)
            tblMain->setColumnCount(14);
        if (tblMain->rowCount() < 4)
            tblMain->setRowCount(4);
        tblMain->setObjectName(QString::fromUtf8("tblMain"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tblMain->sizePolicy().hasHeightForWidth());
        tblMain->setSizePolicy(sizePolicy);
        tblMain->setLayoutDirection(Qt::LeftToRight);
        tblMain->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tblMain->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tblMain->setAutoScroll(false);
        tblMain->setAutoScrollMargin(8);
        tblMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblMain->setTabKeyNavigation(false);
        tblMain->setProperty("showDropIndicator", QVariant(false));
        tblMain->setDragDropOverwriteMode(false);
        tblMain->setAlternatingRowColors(false);
        tblMain->setSelectionMode(QAbstractItemView::NoSelection);
        tblMain->setTextElideMode(Qt::ElideMiddle);
        tblMain->setGridStyle(Qt::DashLine);
        tblMain->setWordWrap(true);
        tblMain->setCornerButtonEnabled(false);
        tblMain->setRowCount(4);
        tblMain->setColumnCount(14);
        tblMain->horizontalHeader()->setCascadingSectionResizes(true);
        tblMain->horizontalHeader()->setMinimumSectionSize(17);
        tblMain->horizontalHeader()->setDefaultSectionSize(30);
        tblMain->horizontalHeader()->setHighlightSections(false);
        tblMain->horizontalHeader()->setStretchLastSection(true);
        tblMain->verticalHeader()->setCascadingSectionResizes(true);
        tblMain->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tblMain->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tblMain, 0, 0, 1, 3);


        retranslateUi(StatisticNGClass);

        QMetaObject::connectSlotsByName(StatisticNGClass);
    } // setupUi

    void retranslateUi(QWidget *StatisticNGClass)
    {
        StatisticNGClass->setWindowTitle(QCoreApplication::translate("StatisticNGClass", "Form", nullptr));
        pbShowDetail->setText(QCoreApplication::translate("StatisticNGClass", "Show detail", nullptr));
        pbSaveToFile->setText(QCoreApplication::translate("StatisticNGClass", "Save to file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatisticNGClass: public Ui_StatisticNGClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICNGFORM_H
