/********************************************************************************
** Form generated from reading UI file 'ControlHayashiTokeiGUIForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLHAYASHITOKEIGUIFORM_H
#define UI_CONTROLHAYASHITOKEIGUIFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ControlHayashiTokeiGUIForm
{
public:
    QDial *dialValue;
    QSpinBox *spinBoxValue;
    QToolButton *toolButtonON;

    void setupUi(GUIFormBase *ControlHayashiTokeiGUIForm)
    {
        if (ControlHayashiTokeiGUIForm->objectName().isEmpty())
            ControlHayashiTokeiGUIForm->setObjectName("ControlHayashiTokeiGUIForm");
        ControlHayashiTokeiGUIForm->resize(70, 149);
        dialValue = new QDial(ControlHayashiTokeiGUIForm);
        dialValue->setObjectName("dialValue");
        dialValue->setGeometry(QRect(0, 0, 71, 71));
        dialValue->setMaximum(255);
        spinBoxValue = new QSpinBox(ControlHayashiTokeiGUIForm);
        spinBoxValue->setObjectName("spinBoxValue");
        spinBoxValue->setGeometry(QRect(10, 80, 51, 22));
        spinBoxValue->setMaximum(255);
        spinBoxValue->setValue(255);
        toolButtonON = new QToolButton(ControlHayashiTokeiGUIForm);
        toolButtonON->setObjectName("toolButtonON");
        toolButtonON->setGeometry(QRect(10, 110, 51, 31));
        toolButtonON->setCheckable(true);

        retranslateUi(ControlHayashiTokeiGUIForm);

        QMetaObject::connectSlotsByName(ControlHayashiTokeiGUIForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ControlHayashiTokeiGUIForm)
    {
        ControlHayashiTokeiGUIForm->setWindowTitle(QCoreApplication::translate("ControlHayashiTokeiGUIForm", "Control HayashiTokei GUI", nullptr));
        toolButtonON->setText(QCoreApplication::translate("ControlHayashiTokeiGUIForm", "ON", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlHayashiTokeiGUIForm: public Ui_ControlHayashiTokeiGUIForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLHAYASHITOKEIGUIFORM_H
