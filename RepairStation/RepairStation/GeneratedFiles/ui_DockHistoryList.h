/********************************************************************************
** Form generated from reading UI file 'DockHistoryList.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKHISTORYLIST_H
#define UI_DOCKHISTORYLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSplitter>
#include <QtGui/QTableWidget>
#include <QWidget>
#include "PasswordPushButton.h"

QT_BEGIN_NAMESPACE

class Ui_DockHistoryListClass
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTableWidget *twHistoryList;
    QWidget *layoutWidget;
    QGridLayout *gridLayout1;
    QCheckBox *chReverseOrderDisplay;
    PasswordPushButton *pbChangeLot;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *leHistoryNumb;
    PasswordPushButton *pbUpdate;

    void setupUi(QDockWidget *DockHistoryListClass)
    {
        if (DockHistoryListClass->objectName().isEmpty())
            DockHistoryListClass->setObjectName(QString::fromUtf8("DockHistoryListClass"));
        DockHistoryListClass->resize(259, 465);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(widget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        twHistoryList = new QTableWidget(splitter);
        if (twHistoryList->columnCount() < 3)
            twHistoryList->setColumnCount(3);
        twHistoryList->setObjectName(QString::fromUtf8("twHistoryList"));
        twHistoryList->setColumnCount(3);
        splitter->addWidget(twHistoryList);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout1 = new QGridLayout(layoutWidget);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        chReverseOrderDisplay = new QCheckBox(layoutWidget);
        chReverseOrderDisplay->setObjectName(QString::fromUtf8("chReverseOrderDisplay"));

        gridLayout1->addWidget(chReverseOrderDisplay, 0, 0, 1, 1);

        pbChangeLot = new PasswordPushButton(layoutWidget);
        pbChangeLot->setObjectName(QString::fromUtf8("pbChangeLot"));
        pbChangeLot->setMinimumSize(QSize(75, 31));

        gridLayout1->addWidget(pbChangeLot, 0, 1, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        leHistoryNumb = new QLineEdit(layoutWidget);
        leHistoryNumb->setObjectName(QString::fromUtf8("leHistoryNumb"));
        leHistoryNumb->setReadOnly(true);

        hboxLayout->addWidget(leHistoryNumb);


        gridLayout1->addLayout(hboxLayout, 1, 0, 1, 1);

        pbUpdate = new PasswordPushButton(layoutWidget);
        pbUpdate->setObjectName(QString::fromUtf8("pbUpdate"));
        pbUpdate->setMinimumSize(QSize(75, 31));

        gridLayout1->addWidget(pbUpdate, 1, 1, 1, 1);

        splitter->addWidget(layoutWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        DockHistoryListClass->setWidget(widget);

        retranslateUi(DockHistoryListClass);

        QMetaObject::connectSlotsByName(DockHistoryListClass);
    } // setupUi

    void retranslateUi(QDockWidget *DockHistoryListClass)
    {
        chReverseOrderDisplay->setText(QApplication::translate("DockHistoryListClass", "&Reverse Order Display", 0, QApplication::UnicodeUTF8));
        pbChangeLot->setText(QApplication::translate("DockHistoryListClass", "Change Lot", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DockHistoryListClass", "Inspect Count", 0, QApplication::UnicodeUTF8));
        pbUpdate->setText(QApplication::translate("DockHistoryListClass", "Update", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DockHistoryListClass);
    } // retranslateUi

};

namespace Ui {
    class DockHistoryListClass: public Ui_DockHistoryListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKHISTORYLIST_H
