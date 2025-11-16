/********************************************************************************
** Form generated from reading UI file 'PropertyDotRegulationForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYDOTREGULATIONFORM_H
#define UI_PROPERTYDOTREGULATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyDotRegulationFormClass
{
public:
    QPushButton *pushButtonPickup;
    QLabel *label;
    QSpinBox *spinBoxThreshold;
    QPushButton *pushButtonXPosList;
    QPushButton *pushButtonYPosList;
    QPushButton *pushButtonBrightness;

    void setupUi(GUIFormBase *PropertyDotRegulationFormClass)
    {
        if (PropertyDotRegulationFormClass->objectName().isEmpty())
            PropertyDotRegulationFormClass->setObjectName(QString::fromUtf8("PropertyDotRegulationFormClass"));
        PropertyDotRegulationFormClass->resize(209, 300);
        pushButtonPickup = new QPushButton(PropertyDotRegulationFormClass);
        pushButtonPickup->setObjectName(QString::fromUtf8("pushButtonPickup"));
        pushButtonPickup->setGeometry(QRect(10, 60, 161, 31));
        label = new QLabel(PropertyDotRegulationFormClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 12, 50, 20));
        spinBoxThreshold = new QSpinBox(PropertyDotRegulationFormClass);
        spinBoxThreshold->setObjectName(QString::fromUtf8("spinBoxThreshold"));
        spinBoxThreshold->setGeometry(QRect(105, 10, 61, 22));
        spinBoxThreshold->setMaximum(255);
        pushButtonXPosList = new QPushButton(PropertyDotRegulationFormClass);
        pushButtonXPosList->setObjectName(QString::fromUtf8("pushButtonXPosList"));
        pushButtonXPosList->setGeometry(QRect(10, 100, 161, 31));
        pushButtonYPosList = new QPushButton(PropertyDotRegulationFormClass);
        pushButtonYPosList->setObjectName(QString::fromUtf8("pushButtonYPosList"));
        pushButtonYPosList->setGeometry(QRect(10, 140, 161, 31));
        pushButtonBrightness = new QPushButton(PropertyDotRegulationFormClass);
        pushButtonBrightness->setObjectName(QString::fromUtf8("pushButtonBrightness"));
        pushButtonBrightness->setGeometry(QRect(10, 180, 161, 31));

        retranslateUi(PropertyDotRegulationFormClass);

        QMetaObject::connectSlotsByName(PropertyDotRegulationFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyDotRegulationFormClass)
    {
        PropertyDotRegulationFormClass->setWindowTitle(QCoreApplication::translate("PropertyDotRegulationFormClass", "PropertyDotRegulationForm", nullptr));
        pushButtonPickup->setText(QCoreApplication::translate("PropertyDotRegulationFormClass", "\346\212\275\345\207\272", nullptr));
        label->setText(QCoreApplication::translate("PropertyDotRegulationFormClass", "\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        pushButtonXPosList->setText(QCoreApplication::translate("PropertyDotRegulationFormClass", "X\345\272\247\346\250\231\343\203\252\343\202\271\343\203\210CSV\347\224\237\346\210\220", nullptr));
        pushButtonYPosList->setText(QCoreApplication::translate("PropertyDotRegulationFormClass", "Y\345\272\247\346\250\231\343\203\252\343\202\271\343\203\210CSV\347\224\237\346\210\220", nullptr));
        pushButtonBrightness->setText(QCoreApplication::translate("PropertyDotRegulationFormClass", "\350\274\235\345\272\246\343\203\252\343\202\271\343\203\210CSV\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyDotRegulationFormClass: public Ui_PropertyDotRegulationFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYDOTREGULATIONFORM_H
