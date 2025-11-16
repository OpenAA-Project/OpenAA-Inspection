/********************************************************************************
** Form generated from reading UI file 'WhichImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHICHIMAGEFORM_H
#define UI_WHICHIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QRadioButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_WhichImageFormClass
{
public:
    QRadioButton *radioButtonMaster;
    QRadioButton *radioButtonTarget;
    QRadioButton *radioButtonDark;
    QRadioButton *radioButtonLight;

    void setupUi(GUIFormBase *WhichImageFormClass)
    {
        if (WhichImageFormClass->objectName().isEmpty())
            WhichImageFormClass->setObjectName("WhichImageFormClass");
        WhichImageFormClass->resize(396, 20);
        radioButtonMaster = new QRadioButton(WhichImageFormClass);
        radioButtonMaster->setObjectName("radioButtonMaster");
        radioButtonMaster->setGeometry(QRect(0, 0, 85, 18));
        radioButtonMaster->setChecked(true);
        radioButtonMaster->setAutoExclusive(true);
        radioButtonTarget = new QRadioButton(WhichImageFormClass);
        radioButtonTarget->setObjectName("radioButtonTarget");
        radioButtonTarget->setGeometry(QRect(100, 0, 85, 18));
        radioButtonTarget->setAutoExclusive(true);
        radioButtonDark = new QRadioButton(WhichImageFormClass);
        radioButtonDark->setObjectName("radioButtonDark");
        radioButtonDark->setGeometry(QRect(200, 0, 85, 18));
        radioButtonDark->setAutoExclusive(true);
        radioButtonLight = new QRadioButton(WhichImageFormClass);
        radioButtonLight->setObjectName("radioButtonLight");
        radioButtonLight->setGeometry(QRect(300, 0, 85, 18));

        retranslateUi(WhichImageFormClass);

        QMetaObject::connectSlotsByName(WhichImageFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *WhichImageFormClass)
    {
        WhichImageFormClass->setWindowTitle(QCoreApplication::translate("WhichImageFormClass", "WhichImageForm", nullptr));
        radioButtonMaster->setText(QCoreApplication::translate("WhichImageFormClass", "Master", nullptr));
        radioButtonTarget->setText(QCoreApplication::translate("WhichImageFormClass", "Target", nullptr));
        radioButtonDark->setText(QCoreApplication::translate("WhichImageFormClass", "Dark", nullptr));
        radioButtonLight->setText(QCoreApplication::translate("WhichImageFormClass", "Light", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WhichImageFormClass: public Ui_WhichImageFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHICHIMAGEFORM_H
