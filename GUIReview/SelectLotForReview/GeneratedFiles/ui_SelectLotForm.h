/********************************************************************************
** Form generated from reading UI file 'SelectLotForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLOTFORM_H
#define UI_SELECTLOTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLotFormClass
{
public:
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTableWidget *twFrontLot;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QTableWidget *twBackLot;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbUpdate;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *SelectLotFormClass)
    {
        if (SelectLotFormClass->objectName().isEmpty())
            SelectLotFormClass->setObjectName(QString::fromUtf8("SelectLotFormClass"));
        SelectLotFormClass->resize(400, 370);
        gridLayout_3 = new QGridLayout(SelectLotFormClass);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tabWidget = new QTabWidget(SelectLotFormClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        twFrontLot = new QTableWidget(tab);
        if (twFrontLot->columnCount() < 2)
            twFrontLot->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twFrontLot->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twFrontLot->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (twFrontLot->rowCount() < 1)
            twFrontLot->setRowCount(1);
        twFrontLot->setObjectName(QString::fromUtf8("twFrontLot"));
        twFrontLot->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twFrontLot->setTabKeyNavigation(false);
        twFrontLot->setProperty("showDropIndicator", QVariant(false));
        twFrontLot->setDragDropOverwriteMode(false);
        twFrontLot->setSelectionMode(QAbstractItemView::SingleSelection);
        twFrontLot->setSelectionBehavior(QAbstractItemView::SelectRows);
        twFrontLot->setTextElideMode(Qt::ElideRight);
        twFrontLot->setRowCount(1);
        twFrontLot->setColumnCount(2);
        twFrontLot->horizontalHeader()->setCascadingSectionResizes(false);
        twFrontLot->horizontalHeader()->setStretchLastSection(true);
        twFrontLot->verticalHeader()->setCascadingSectionResizes(false);
        twFrontLot->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        twFrontLot->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(twFrontLot, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        twBackLot = new QTableWidget(tab_2);
        if (twBackLot->columnCount() < 2)
            twBackLot->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twBackLot->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        twBackLot->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        if (twBackLot->rowCount() < 1)
            twBackLot->setRowCount(1);
        twBackLot->setObjectName(QString::fromUtf8("twBackLot"));
        twBackLot->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twBackLot->setTabKeyNavigation(false);
        twBackLot->setProperty("showDropIndicator", QVariant(false));
        twBackLot->setDragDropOverwriteMode(false);
        twBackLot->setSelectionMode(QAbstractItemView::SingleSelection);
        twBackLot->setSelectionBehavior(QAbstractItemView::SelectRows);
        twBackLot->setRowCount(1);
        twBackLot->setColumnCount(2);
        twBackLot->horizontalHeader()->setStretchLastSection(true);

        gridLayout_2->addWidget(twBackLot, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(148, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbUpdate = new QPushButton(SelectLotFormClass);
        pbUpdate->setObjectName(QString::fromUtf8("pbUpdate"));

        horizontalLayout->addWidget(pbUpdate);

        okButton = new QPushButton(SelectLotFormClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setMinimumSize(QSize(81, 31));
        okButton->setMaximumSize(QSize(81, 31));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(SelectLotFormClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy);
        cancelButton->setMinimumSize(QSize(81, 31));
        cancelButton->setMaximumSize(QSize(81, 31));
        cancelButton->setBaseSize(QSize(0, 0));

        horizontalLayout->addWidget(cancelButton);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(SelectLotFormClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SelectLotFormClass);
    } // setupUi

    void retranslateUi(QWidget *SelectLotFormClass)
    {
        SelectLotFormClass->setWindowTitle(QCoreApplication::translate("SelectLotFormClass", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twFrontLot->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLotFormClass", "Filename", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twFrontLot->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLotFormClass", "Lotname", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SelectLotFormClass", "Front", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = twBackLot->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectLotFormClass", "Filename", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = twBackLot->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectLotFormClass", "Lotname", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SelectLotFormClass", "Back", nullptr));
        pbUpdate->setText(QCoreApplication::translate("SelectLotFormClass", "Update", nullptr));
        okButton->setText(QCoreApplication::translate("SelectLotFormClass", "Select", nullptr));
        cancelButton->setText(QCoreApplication::translate("SelectLotFormClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLotFormClass: public Ui_SelectLotFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLOTFORM_H
