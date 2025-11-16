/********************************************************************************
** Form generated from reading UI file 'ShowStrategicNumberForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSTRATEGICNUMBERFORM_H
#define UI_SHOWSTRATEGICNUMBERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowStrategicNumberFormClass
{
public:
    QLabel *label;
    QSpinBox *spinBoxNumber;

    void setupUi(GUIFormBase *ShowStrategicNumberFormClass)
    {
        if (ShowStrategicNumberFormClass->objectName().isEmpty())
            ShowStrategicNumberFormClass->setObjectName("ShowStrategicNumberFormClass");
        ShowStrategicNumberFormClass->resize(209, 23);
        label = new QLabel(ShowStrategicNumberFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 129, 21));
        spinBoxNumber = new QSpinBox(ShowStrategicNumberFormClass);
        spinBoxNumber->setObjectName("spinBoxNumber");
        spinBoxNumber->setGeometry(QRect(150, 0, 61, 22));

        retranslateUi(ShowStrategicNumberFormClass);

        QMetaObject::connectSlotsByName(ShowStrategicNumberFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowStrategicNumberFormClass)
    {
        ShowStrategicNumberFormClass->setWindowTitle(QCoreApplication::translate("ShowStrategicNumberFormClass", "ShowStrategicNumberForm", nullptr));
        label->setText(QCoreApplication::translate("ShowStrategicNumberFormClass", "Caption strategic number", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowStrategicNumberFormClass: public Ui_ShowStrategicNumberFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSTRATEGICNUMBERFORM_H
