/********************************************************************************
** Form generated from reading UI file 'KoreaST8ChGUIForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KOREAST8CHGUIFORM_H
#define UI_KOREAST8CHGUIFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_KoreaST8ChGUIForm
{
public:
    QDial *dialLightValue;
    QSpinBox *spinBoxLightValue;
    QToolButton *toolButtonON;
    QPushButton *pushButtonSet;

    void setupUi(GUIFormBase *KoreaST8ChGUIForm)
    {
        if (KoreaST8ChGUIForm->objectName().isEmpty())
            KoreaST8ChGUIForm->setObjectName("KoreaST8ChGUIForm");
        KoreaST8ChGUIForm->resize(85, 220);
        dialLightValue = new QDial(KoreaST8ChGUIForm);
        dialLightValue->setObjectName("dialLightValue");
        dialLightValue->setGeometry(QRect(0, 0, 81, 81));
        dialLightValue->setMaximum(255);
        spinBoxLightValue = new QSpinBox(KoreaST8ChGUIForm);
        spinBoxLightValue->setObjectName("spinBoxLightValue");
        spinBoxLightValue->setGeometry(QRect(0, 90, 81, 31));
        QFont font;
        font.setPointSize(12);
        spinBoxLightValue->setFont(font);
        spinBoxLightValue->setMaximum(255);
        toolButtonON = new QToolButton(KoreaST8ChGUIForm);
        toolButtonON->setObjectName("toolButtonON");
        toolButtonON->setGeometry(QRect(10, 130, 61, 31));
        toolButtonON->setCheckable(true);
        pushButtonSet = new QPushButton(KoreaST8ChGUIForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(10, 170, 61, 31));

        retranslateUi(KoreaST8ChGUIForm);

        QMetaObject::connectSlotsByName(KoreaST8ChGUIForm);
    } // setupUi

    void retranslateUi(GUIFormBase *KoreaST8ChGUIForm)
    {
        KoreaST8ChGUIForm->setWindowTitle(QCoreApplication::translate("KoreaST8ChGUIForm", "Dialog", nullptr));
        toolButtonON->setText(QCoreApplication::translate("KoreaST8ChGUIForm", "ON", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("KoreaST8ChGUIForm", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KoreaST8ChGUIForm: public Ui_KoreaST8ChGUIForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KOREAST8CHGUIFORM_H
