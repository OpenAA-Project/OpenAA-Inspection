/********************************************************************************
** Form generated from reading UI file 'PropertyRealtimeGraphForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYREALTIMEGRAPHFORM_H
#define UI_PROPERTYREALTIMEGRAPHFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyRealtimeGraphFormClass
{
public:
    QToolButton *toolButtonStartCapture;
    QComboBox *comboBoxCamera;

    void setupUi(GUIFormBase *PropertyRealtimeGraphFormClass)
    {
        if (PropertyRealtimeGraphFormClass->objectName().isEmpty())
            PropertyRealtimeGraphFormClass->setObjectName("PropertyRealtimeGraphFormClass");
        PropertyRealtimeGraphFormClass->resize(140, 89);
        toolButtonStartCapture = new QToolButton(PropertyRealtimeGraphFormClass);
        toolButtonStartCapture->setObjectName("toolButtonStartCapture");
        toolButtonStartCapture->setGeometry(QRect(10, 40, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonStartCapture->setIcon(icon);
        toolButtonStartCapture->setCheckable(true);
        toolButtonStartCapture->setChecked(false);
        toolButtonStartCapture->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        comboBoxCamera = new QComboBox(PropertyRealtimeGraphFormClass);
        comboBoxCamera->setObjectName("comboBoxCamera");
        comboBoxCamera->setGeometry(QRect(10, 10, 121, 24));

        retranslateUi(PropertyRealtimeGraphFormClass);

        QMetaObject::connectSlotsByName(PropertyRealtimeGraphFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyRealtimeGraphFormClass)
    {
        PropertyRealtimeGraphFormClass->setWindowTitle(QCoreApplication::translate("PropertyRealtimeGraphFormClass", "PropertyRealtimeGraphForm", nullptr));
        toolButtonStartCapture->setText(QCoreApplication::translate("PropertyRealtimeGraphFormClass", "\346\222\256\345\203\217\351\226\213\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyRealtimeGraphFormClass: public Ui_PropertyRealtimeGraphFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYREALTIMEGRAPHFORM_H
