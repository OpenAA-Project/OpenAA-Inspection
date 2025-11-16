/********************************************************************************
** Form generated from reading UI file 'PropertySpotReducerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYSPOTREDUCERFORM_H
#define UI_PROPERTYSPOTREDUCERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertySpotReducerFormClass
{
public:

    void setupUi(GUIFormBase *PropertySpotReducerFormClass)
    {
        if (PropertySpotReducerFormClass->objectName().isEmpty())
            PropertySpotReducerFormClass->setObjectName("PropertySpotReducerFormClass");
        PropertySpotReducerFormClass->resize(400, 700);

        retranslateUi(PropertySpotReducerFormClass);

        QMetaObject::connectSlotsByName(PropertySpotReducerFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertySpotReducerFormClass)
    {
        PropertySpotReducerFormClass->setWindowTitle(QCoreApplication::translate("PropertySpotReducerFormClass", "PropertySpotReducerForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertySpotReducerFormClass: public Ui_PropertySpotReducerFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYSPOTREDUCERFORM_H
