/********************************************************************************
** Form generated from reading UI file 'ButtonSetTactTimeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONSETTACTTIMEFORM_H
#define UI_BUTTONSETTACTTIMEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonSetTactTimeFormClass
{
public:
    QLabel *label;
    QPushButton *pushButtonSet;
    QSpinBox *spinBoxTactTime;

    void setupUi(GUIFormBase *ButtonSetTactTimeFormClass)
    {
        if (ButtonSetTactTimeFormClass->objectName().isEmpty())
            ButtonSetTactTimeFormClass->setObjectName("ButtonSetTactTimeFormClass");
        ButtonSetTactTimeFormClass->resize(243, 22);
        label = new QLabel(ButtonSetTactTimeFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 111, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSet = new QPushButton(ButtonSetTactTimeFormClass);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(190, 0, 51, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);
        spinBoxTactTime = new QSpinBox(ButtonSetTactTimeFormClass);
        spinBoxTactTime->setObjectName("spinBoxTactTime");
        spinBoxTactTime->setGeometry(QRect(110, 0, 81, 22));
        spinBoxTactTime->setMaximum(1000000);

        retranslateUi(ButtonSetTactTimeFormClass);

        QMetaObject::connectSlotsByName(ButtonSetTactTimeFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonSetTactTimeFormClass)
    {
        ButtonSetTactTimeFormClass->setWindowTitle(QCoreApplication::translate("ButtonSetTactTimeFormClass", "ButtonSetTactTimeForm", nullptr));
        label->setText(QCoreApplication::translate("ButtonSetTactTimeFormClass", "Tact time(ms)", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("ButtonSetTactTimeFormClass", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonSetTactTimeFormClass: public Ui_ButtonSetTactTimeFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONSETTACTTIMEFORM_H
