/********************************************************************************
** Form generated from reading UI file 'DockMasterWhole2.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKMASTERWHOLE2_H
#define UI_DOCKMASTERWHOLE2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockMasterWhole2Class
{
public:
    QWidget *widget;

    void setupUi(QDockWidget *DockMasterWhole2Class)
    {
        if (DockMasterWhole2Class->objectName().isEmpty())
            DockMasterWhole2Class->setObjectName(QString::fromUtf8("DockMasterWhole2Class"));
        DockMasterWhole2Class->resize(326, 648);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        DockMasterWhole2Class->setWidget(widget);

        retranslateUi(DockMasterWhole2Class);

        QMetaObject::connectSlotsByName(DockMasterWhole2Class);
    } // setupUi

    void retranslateUi(QDockWidget *DockMasterWhole2Class)
    {
        Q_UNUSED(DockMasterWhole2Class);
    } // retranslateUi

};

namespace Ui {
    class DockMasterWhole2Class: public Ui_DockMasterWhole2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKMASTERWHOLE2_H
