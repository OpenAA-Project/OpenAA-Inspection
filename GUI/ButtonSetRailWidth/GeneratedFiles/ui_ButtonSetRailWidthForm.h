/********************************************************************************
** Form generated from reading UI file 'ButtonSetRailWidthForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONSETRAILWIDTHFORM_H
#define UI_BUTTONSETRAILWIDTHFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonSetRailWidthFormClass
{
public:
    QPushButton *pushButtonSet;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxRailWidth;

    void setupUi(GUIFormBase *ButtonSetRailWidthFormClass)
    {
        if (ButtonSetRailWidthFormClass->objectName().isEmpty())
            ButtonSetRailWidthFormClass->setObjectName("ButtonSetRailWidthFormClass");
        ButtonSetRailWidthFormClass->resize(230, 22);
        pushButtonSet = new QPushButton(ButtonSetRailWidthFormClass);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(180, 0, 51, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);
        label = new QLabel(ButtonSetRailWidthFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 111, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxRailWidth = new QDoubleSpinBox(ButtonSetRailWidthFormClass);
        doubleSpinBoxRailWidth->setObjectName("doubleSpinBoxRailWidth");
        doubleSpinBoxRailWidth->setGeometry(QRect(110, 0, 71, 22));
        doubleSpinBoxRailWidth->setDecimals(1);
        doubleSpinBoxRailWidth->setMinimum(50.000000000000000);
        doubleSpinBoxRailWidth->setMaximum(251.000000000000000);
        doubleSpinBoxRailWidth->setValue(100.000000000000000);

        retranslateUi(ButtonSetRailWidthFormClass);

        QMetaObject::connectSlotsByName(ButtonSetRailWidthFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonSetRailWidthFormClass)
    {
        ButtonSetRailWidthFormClass->setWindowTitle(QCoreApplication::translate("ButtonSetRailWidthFormClass", "ButtonSetRailWidthForm", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("ButtonSetRailWidthFormClass", "Set", nullptr));
        label->setText(QCoreApplication::translate("ButtonSetRailWidthFormClass", "Rail width(mm)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonSetRailWidthFormClass: public Ui_ButtonSetRailWidthFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONSETRAILWIDTHFORM_H
