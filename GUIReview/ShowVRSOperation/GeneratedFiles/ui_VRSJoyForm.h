/********************************************************************************
** Form generated from reading UI file 'VRSJoyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VRSJOYFORM_H
#define UI_VRSJOYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VRSJoyClass
{
public:

    void setupUi(QWidget *VRSJoyClass)
    {
        if (VRSJoyClass->objectName().isEmpty())
            VRSJoyClass->setObjectName(QString::fromUtf8("VRSJoyClass"));
        VRSJoyClass->resize(290, 273);

        retranslateUi(VRSJoyClass);

        QMetaObject::connectSlotsByName(VRSJoyClass);
    } // setupUi

    void retranslateUi(QWidget *VRSJoyClass)
    {
        VRSJoyClass->setWindowTitle(QCoreApplication::translate("VRSJoyClass", "VRSJoyForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VRSJoyClass: public Ui_VRSJoyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VRSJOYFORM_H
