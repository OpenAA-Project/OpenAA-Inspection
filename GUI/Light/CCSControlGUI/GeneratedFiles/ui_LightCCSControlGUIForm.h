/********************************************************************************
** Form generated from reading UI file 'LightCCSControlGUIForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHTCCSCONTROLGUIFORM_H
#define UI_LIGHTCCSCONTROLGUIFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_LightCCSControlGUIForm
{
public:
    QDial *dialBrightness;
    QSpinBox *spinBoxBrightness;
    QToolButton *toolButtonON;

    void setupUi(GUIFormBase *LightCCSControlGUIForm)
    {
        if (LightCCSControlGUIForm->objectName().isEmpty())
            LightCCSControlGUIForm->setObjectName("LightCCSControlGUIForm");
        LightCCSControlGUIForm->resize(70, 149);
        dialBrightness = new QDial(LightCCSControlGUIForm);
        dialBrightness->setObjectName("dialBrightness");
        dialBrightness->setGeometry(QRect(0, 0, 71, 71));
        dialBrightness->setMaximum(255);
        dialBrightness->setValue(255);
        dialBrightness->setInvertedControls(false);
        spinBoxBrightness = new QSpinBox(LightCCSControlGUIForm);
        spinBoxBrightness->setObjectName("spinBoxBrightness");
        spinBoxBrightness->setGeometry(QRect(10, 80, 51, 22));
        spinBoxBrightness->setMaximum(255);
        spinBoxBrightness->setValue(255);
        toolButtonON = new QToolButton(LightCCSControlGUIForm);
        toolButtonON->setObjectName("toolButtonON");
        toolButtonON->setGeometry(QRect(10, 110, 51, 31));
        toolButtonON->setCheckable(true);

        retranslateUi(LightCCSControlGUIForm);

        QMetaObject::connectSlotsByName(LightCCSControlGUIForm);
    } // setupUi

    void retranslateUi(GUIFormBase *LightCCSControlGUIForm)
    {
        LightCCSControlGUIForm->setWindowTitle(QCoreApplication::translate("LightCCSControlGUIForm", "Light CCS Control GUI", nullptr));
        toolButtonON->setText(QCoreApplication::translate("LightCCSControlGUIForm", "ON", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LightCCSControlGUIForm: public Ui_LightCCSControlGUIForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHTCCSCONTROLGUIFORM_H
