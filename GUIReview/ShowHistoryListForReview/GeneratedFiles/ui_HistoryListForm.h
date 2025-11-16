/********************************************************************************
** Form generated from reading UI file 'HistoryListForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYLISTFORM_H
#define UI_HISTORYLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "TableWidgetWithoutKey.h"

QT_BEGIN_NAMESPACE

class Ui_HistoryListClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    TableWidgetWithoutKey *twHistoryList;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *lbOKBoardCount;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_5;
    QLabel *lbNGBoardCount;
    QSpacerItem *horizontalSpacer;
    QCheckBox *cbOKVisible;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *leHistoryCount;
    QPushButton *pbShowErrrorDialog;
    QPushButton *pbReload;

    void setupUi(QWidget *HistoryListClass)
    {
        if (HistoryListClass->objectName().isEmpty())
            HistoryListClass->setObjectName(QString::fromUtf8("HistoryListClass"));
        HistoryListClass->resize(453, 424);
        gridLayout = new QGridLayout(HistoryListClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(HistoryListClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFrameShape(QFrame::Box);
        label_2->setFrameShadow(QFrame::Plain);
        label_2->setLineWidth(1);
        label_2->setMidLineWidth(0);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        twHistoryList = new TableWidgetWithoutKey(HistoryListClass);
        if (twHistoryList->columnCount() < 4)
            twHistoryList->setColumnCount(4);
        if (twHistoryList->rowCount() < 5)
            twHistoryList->setRowCount(5);
        twHistoryList->setObjectName(QString::fromUtf8("twHistoryList"));
        twHistoryList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twHistoryList->setTabKeyNavigation(false);
        twHistoryList->setProperty("showDropIndicator", QVariant(false));
        twHistoryList->setDragDropOverwriteMode(false);
        twHistoryList->setAlternatingRowColors(false);
        twHistoryList->setSelectionMode(QAbstractItemView::SingleSelection);
        twHistoryList->setSelectionBehavior(QAbstractItemView::SelectRows);
        twHistoryList->setTextElideMode(Qt::ElideMiddle);
        twHistoryList->setGridStyle(Qt::SolidLine);
        twHistoryList->setRowCount(5);
        twHistoryList->setColumnCount(4);
        twHistoryList->horizontalHeader()->setCascadingSectionResizes(true);
        twHistoryList->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(twHistoryList);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(HistoryListClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lbOKBoardCount = new QLabel(HistoryListClass);
        lbOKBoardCount->setObjectName(QString::fromUtf8("lbOKBoardCount"));

        horizontalLayout_2->addWidget(lbOKBoardCount);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_5 = new QLabel(HistoryListClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lbNGBoardCount = new QLabel(HistoryListClass);
        lbNGBoardCount->setObjectName(QString::fromUtf8("lbNGBoardCount"));

        horizontalLayout_2->addWidget(lbNGBoardCount);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cbOKVisible = new QCheckBox(HistoryListClass);
        cbOKVisible->setObjectName(QString::fromUtf8("cbOKVisible"));
        cbOKVisible->setFocusPolicy(Qt::TabFocus);

        horizontalLayout_2->addWidget(cbOKVisible);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(HistoryListClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        leHistoryCount = new QLineEdit(HistoryListClass);
        leHistoryCount->setObjectName(QString::fromUtf8("leHistoryCount"));
        leHistoryCount->setFocusPolicy(Qt::NoFocus);
        leHistoryCount->setLayoutDirection(Qt::LeftToRight);
        leHistoryCount->setFrame(false);
        leHistoryCount->setAlignment(Qt::AlignCenter);
        leHistoryCount->setReadOnly(true);

        horizontalLayout->addWidget(leHistoryCount);

        pbShowErrrorDialog = new QPushButton(HistoryListClass);
        pbShowErrrorDialog->setObjectName(QString::fromUtf8("pbShowErrrorDialog"));
        pbShowErrrorDialog->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pbShowErrrorDialog);

        pbReload = new QPushButton(HistoryListClass);
        pbReload->setObjectName(QString::fromUtf8("pbReload"));
        pbReload->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pbReload);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(HistoryListClass);

        QMetaObject::connectSlotsByName(HistoryListClass);
    } // setupUi

    void retranslateUi(QWidget *HistoryListClass)
    {
        HistoryListClass->setWindowTitle(QCoreApplication::translate("HistoryListClass", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("HistoryListClass", "History List", nullptr));
        label_3->setText(QCoreApplication::translate("HistoryListClass", "OK Count\357\274\232", nullptr));
        lbOKBoardCount->setText(QCoreApplication::translate("HistoryListClass", "-", nullptr));
        label_5->setText(QCoreApplication::translate("HistoryListClass", "NG Count\357\274\232", nullptr));
        lbNGBoardCount->setText(QCoreApplication::translate("HistoryListClass", "-", nullptr));
        cbOKVisible->setText(QCoreApplication::translate("HistoryListClass", "view OK", nullptr));
        label->setText(QCoreApplication::translate("HistoryListClass", "Sum", nullptr));
        leHistoryCount->setText(QCoreApplication::translate("HistoryListClass", "-", nullptr));
        pbShowErrrorDialog->setText(QCoreApplication::translate("HistoryListClass", "ShowError", nullptr));
        pbReload->setText(QCoreApplication::translate("HistoryListClass", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoryListClass: public Ui_HistoryListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYLISTFORM_H
