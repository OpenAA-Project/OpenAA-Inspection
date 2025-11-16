/********************************************************************************
** Form generated from reading UI file 'DockNGList.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKNGLIST_H
#define UI_DOCKNGLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSplitter>
#include <QtGui/QTableWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockNGListClass
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTableWidget *dwTableList;
    QWidget *layoutWidget;
    QGridLayout *gridLayout1;
    QLabel *label;
    QLineEdit *leNGCount;

    void setupUi(QDockWidget *DockNGListClass)
    {
        if (DockNGListClass->objectName().isEmpty())
            DockNGListClass->setObjectName(QString::fromUtf8("DockNGListClass"));
        DockNGListClass->resize(259, 465);
        DockNGListClass->setFeatures(QDockWidget::AllDockWidgetFeatures);
        DockNGListClass->setAllowedAreas(Qt::AllDockWidgetAreas);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(widget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        dwTableList = new QTableWidget(splitter);
        dwTableList->setObjectName(QString::fromUtf8("dwTableList"));
        splitter->addWidget(dwTableList);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout1 = new QGridLayout(layoutWidget);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(label, 0, 0, 1, 1);

        leNGCount = new QLineEdit(layoutWidget);
        leNGCount->setObjectName(QString::fromUtf8("leNGCount"));
        leNGCount->setReadOnly(true);

        gridLayout1->addWidget(leNGCount, 0, 1, 1, 1);

        splitter->addWidget(layoutWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        DockNGListClass->setWidget(widget);

        retranslateUi(DockNGListClass);

        QMetaObject::connectSlotsByName(DockNGListClass);
    } // setupUi

    void retranslateUi(QDockWidget *DockNGListClass)
    {
        label->setText(QApplication::translate("DockNGListClass", "NG Count", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DockNGListClass);
    } // retranslateUi

};

namespace Ui {
    class DockNGListClass: public Ui_DockNGListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKNGLIST_H
