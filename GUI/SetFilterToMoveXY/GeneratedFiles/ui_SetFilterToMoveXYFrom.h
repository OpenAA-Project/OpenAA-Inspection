/********************************************************************************
** Form generated from reading UI file 'SetFilterToMoveXYFrom.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETFILTERTOMOVEXYFROM_H
#define UI_SETFILTERTOMOVEXYFROM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_SetFilterToMoveXYFrom
{
public:
    QPushButton *pushButtonSetShftFilter;

    void setupUi(GUIFormBase *SetFilterToMoveXYFrom)
    {
        if (SetFilterToMoveXYFrom->objectName().isEmpty())
            SetFilterToMoveXYFrom->setObjectName("SetFilterToMoveXYFrom");
        SetFilterToMoveXYFrom->resize(101, 29);
        pushButtonSetShftFilter = new QPushButton(SetFilterToMoveXYFrom);
        pushButtonSetShftFilter->setObjectName("pushButtonSetShftFilter");
        pushButtonSetShftFilter->setGeometry(QRect(0, 0, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetShftFilter->setIcon(icon);

        retranslateUi(SetFilterToMoveXYFrom);

        QMetaObject::connectSlotsByName(SetFilterToMoveXYFrom);
    } // setupUi

    void retranslateUi(GUIFormBase *SetFilterToMoveXYFrom)
    {
        SetFilterToMoveXYFrom->setWindowTitle(QCoreApplication::translate("SetFilterToMoveXYFrom", "Set filter to Move XY", nullptr));
        pushButtonSetShftFilter->setText(QCoreApplication::translate("SetFilterToMoveXYFrom", "Set Shift filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetFilterToMoveXYFrom: public Ui_SetFilterToMoveXYFrom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETFILTERTOMOVEXYFROM_H
