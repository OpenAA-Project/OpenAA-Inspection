/********************************************************************************
** Form generated from reading UI file 'DockMasterWhole.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKMASTERWHOLE_H
#define UI_DOCKMASTERWHOLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockMasterWholeClass
{
public:
    QWidget *widget;

    void setupUi(QDockWidget *DockMasterWholeClass)
    {
        if (DockMasterWholeClass->objectName().isEmpty())
            DockMasterWholeClass->setObjectName(QString::fromUtf8("DockMasterWholeClass"));
        DockMasterWholeClass->resize(326, 648);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        DockMasterWholeClass->setWidget(widget);

        retranslateUi(DockMasterWholeClass);

        QMetaObject::connectSlotsByName(DockMasterWholeClass);
    } // setupUi

    void retranslateUi(QDockWidget *DockMasterWholeClass)
    {
        Q_UNUSED(DockMasterWholeClass);
    } // retranslateUi

};

namespace Ui {
    class DockMasterWholeClass: public Ui_DockMasterWholeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKMASTERWHOLE_H
