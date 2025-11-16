/********************************************************************************
** Form generated from reading UI file 'MainWidget.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QWidget>
#include "passwordpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_MainWidgetClass
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *vboxLayout;
    QLabel *lbMessage;
    QVBoxLayout *vboxLayout1;
    QLabel *lbLotName;
    QLineEdit *leLotName;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout2;
    QLabel *lbProductCount;
    QLineEdit *leProductCount;
    QSpacerItem *spacerItem1;
    QVBoxLayout *vboxLayout3;
    QLabel *lbLotCount;
    QLineEdit *leLotCount;
    QTreeWidget *trMasterList;
    QTableWidget *twMasterList;
    QCheckBox *chNGPoint;
    QCheckBox *chShowPieceLine;
    PasswordPushButton *pbSearch;
    QSpacerItem *spacerItem2;
    PasswordPushButton *pbMasterSelect;

    void setupUi(QDockWidget *MainWidgetClass)
    {
        if (MainWidgetClass->objectName().isEmpty())
            MainWidgetClass->setObjectName(QString::fromUtf8("MainWidgetClass"));
        MainWidgetClass->resize(664, 316);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_2 = new QSplitter(widget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        vboxLayout = new QVBoxLayout(layoutWidget);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        lbMessage = new QLabel(layoutWidget);
        lbMessage->setObjectName(QString::fromUtf8("lbMessage"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbMessage->sizePolicy().hasHeightForWidth());
        lbMessage->setSizePolicy(sizePolicy);
        lbMessage->setAutoFillBackground(true);
        lbMessage->setFrameShape(QFrame::StyledPanel);
        lbMessage->setFrameShadow(QFrame::Sunken);
        lbMessage->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(lbMessage);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        lbLotName = new QLabel(layoutWidget);
        lbLotName->setObjectName(QString::fromUtf8("lbLotName"));
        lbLotName->setFrameShape(QFrame::Panel);
        lbLotName->setFrameShadow(QFrame::Sunken);
        lbLotName->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(lbLotName);

        leLotName = new QLineEdit(layoutWidget);
        leLotName->setObjectName(QString::fromUtf8("leLotName"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leLotName->sizePolicy().hasHeightForWidth());
        leLotName->setSizePolicy(sizePolicy1);
        leLotName->setAlignment(Qt::AlignCenter);
        leLotName->setReadOnly(true);

        vboxLayout1->addWidget(leLotName);


        vboxLayout->addLayout(vboxLayout1);

        spacerItem = new QSpacerItem(356, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        lbProductCount = new QLabel(layoutWidget);
        lbProductCount->setObjectName(QString::fromUtf8("lbProductCount"));
        lbProductCount->setFrameShape(QFrame::Panel);
        lbProductCount->setFrameShadow(QFrame::Sunken);
        lbProductCount->setAlignment(Qt::AlignCenter);

        vboxLayout2->addWidget(lbProductCount);

        leProductCount = new QLineEdit(layoutWidget);
        leProductCount->setObjectName(QString::fromUtf8("leProductCount"));
        sizePolicy1.setHeightForWidth(leProductCount->sizePolicy().hasHeightForWidth());
        leProductCount->setSizePolicy(sizePolicy1);
        leProductCount->setAlignment(Qt::AlignCenter);
        leProductCount->setReadOnly(true);

        vboxLayout2->addWidget(leProductCount);


        vboxLayout->addLayout(vboxLayout2);

        spacerItem1 = new QSpacerItem(356, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem1);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        lbLotCount = new QLabel(layoutWidget);
        lbLotCount->setObjectName(QString::fromUtf8("lbLotCount"));
        lbLotCount->setFrameShape(QFrame::Panel);
        lbLotCount->setFrameShadow(QFrame::Sunken);
        lbLotCount->setAlignment(Qt::AlignCenter);

        vboxLayout3->addWidget(lbLotCount);

        leLotCount = new QLineEdit(layoutWidget);
        leLotCount->setObjectName(QString::fromUtf8("leLotCount"));
        sizePolicy1.setHeightForWidth(leLotCount->sizePolicy().hasHeightForWidth());
        leLotCount->setSizePolicy(sizePolicy1);
        leLotCount->setAlignment(Qt::AlignCenter);
        leLotCount->setReadOnly(true);

        vboxLayout3->addWidget(leLotCount);


        vboxLayout->addLayout(vboxLayout3);

        splitter->addWidget(layoutWidget);
        trMasterList = new QTreeWidget(splitter);
        trMasterList->setObjectName(QString::fromUtf8("trMasterList"));
        splitter->addWidget(trMasterList);
        splitter_2->addWidget(splitter);
        twMasterList = new QTableWidget(splitter_2);
        twMasterList->setObjectName(QString::fromUtf8("twMasterList"));
        splitter_2->addWidget(twMasterList);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 5);

        chNGPoint = new QCheckBox(widget);
        chNGPoint->setObjectName(QString::fromUtf8("chNGPoint"));
        chNGPoint->setChecked(true);

        gridLayout->addWidget(chNGPoint, 1, 0, 1, 1);

        chShowPieceLine = new QCheckBox(widget);
        chShowPieceLine->setObjectName(QString::fromUtf8("chShowPieceLine"));

        gridLayout->addWidget(chShowPieceLine, 1, 1, 1, 1);

        pbSearch = new PasswordPushButton(widget);
        pbSearch->setObjectName(QString::fromUtf8("pbSearch"));
        pbSearch->setMinimumSize(QSize(0, 31));

        gridLayout->addWidget(pbSearch, 1, 2, 1, 1);

        spacerItem2 = new QSpacerItem(251, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem2, 1, 3, 1, 1);

        pbMasterSelect = new PasswordPushButton(widget);
        pbMasterSelect->setObjectName(QString::fromUtf8("pbMasterSelect"));
        pbMasterSelect->setMinimumSize(QSize(0, 31));

        gridLayout->addWidget(pbMasterSelect, 1, 4, 1, 1);

        MainWidgetClass->setWidget(widget);

        retranslateUi(MainWidgetClass);

        QMetaObject::connectSlotsByName(MainWidgetClass);
    } // setupUi

    void retranslateUi(QDockWidget *MainWidgetClass)
    {
        lbLotName->setText(QApplication::translate("MainWidgetClass", "LOT.No", 0, QApplication::UnicodeUTF8));
        lbProductCount->setText(QApplication::translate("MainWidgetClass", "\347\224\237\347\224\243\346\225\260", 0, QApplication::UnicodeUTF8));
        lbLotCount->setText(QApplication::translate("MainWidgetClass", "LOT\346\225\260", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trMasterList->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWidgetClass", "1", 0, QApplication::UnicodeUTF8));
        chNGPoint->setText(QApplication::translate("MainWidgetClass", "NG &Mark Enable", 0, QApplication::UnicodeUTF8));
        chShowPieceLine->setText(QApplication::translate("MainWidgetClass", "Show Piece Line", 0, QApplication::UnicodeUTF8));
        pbSearch->setText(QApplication::translate("MainWidgetClass", "Search", 0, QApplication::UnicodeUTF8));
        pbMasterSelect->setText(QApplication::translate("MainWidgetClass", "Select", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWidgetClass);
    } // retranslateUi

};

namespace Ui {
    class MainWidgetClass: public Ui_MainWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
