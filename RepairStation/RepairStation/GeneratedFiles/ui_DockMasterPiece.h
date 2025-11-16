/********************************************************************************
** Form generated from reading UI file 'DockMasterPiece.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKMASTERPIECE_H
#define UI_DOCKMASTERPIECE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockMasterPieceClass
{
public:
    QWidget *widget;

    void setupUi(QDockWidget *DockMasterPieceClass)
    {
        if (DockMasterPieceClass->objectName().isEmpty())
            DockMasterPieceClass->setObjectName(QString::fromUtf8("DockMasterPieceClass"));
        DockMasterPieceClass->resize(326, 648);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        DockMasterPieceClass->setWidget(widget);

        retranslateUi(DockMasterPieceClass);

        QMetaObject::connectSlotsByName(DockMasterPieceClass);
    } // setupUi

    void retranslateUi(QDockWidget *DockMasterPieceClass)
    {
        Q_UNUSED(DockMasterPieceClass);
    } // retranslateUi

};

namespace Ui {
    class DockMasterPieceClass: public Ui_DockMasterPieceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKMASTERPIECE_H
