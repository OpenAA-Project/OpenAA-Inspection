/********************************************************************************
** Form generated from reading UI file 'DockNGPiece.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKNGPIECE_H
#define UI_DOCKNGPIECE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockNGPieceClass
{
public:
    QWidget *widget;

    void setupUi(QDockWidget *DockNGPieceClass)
    {
        if (DockNGPieceClass->objectName().isEmpty())
            DockNGPieceClass->setObjectName(QString::fromUtf8("DockNGPieceClass"));
        DockNGPieceClass->resize(326, 648);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        DockNGPieceClass->setWidget(widget);

        retranslateUi(DockNGPieceClass);

        QMetaObject::connectSlotsByName(DockNGPieceClass);
    } // setupUi

    void retranslateUi(QDockWidget *DockNGPieceClass)
    {
        Q_UNUSED(DockNGPieceClass);
    } // retranslateUi

};

namespace Ui {
    class DockNGPieceClass: public Ui_DockNGPieceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKNGPIECE_H
