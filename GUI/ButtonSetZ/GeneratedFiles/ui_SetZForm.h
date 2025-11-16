/********************************************************************************
** Form generated from reading UI file 'SetZForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETZFORM_H
#define UI_SETZFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_SetZFormClass
{
public:
    QPushButton *pushButtonOK;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_2;

    void setupUi(GUIFormBase *SetZFormClass)
    {
        if (SetZFormClass->objectName().isEmpty())
            SetZFormClass->setObjectName("SetZFormClass");
        SetZFormClass->resize(275, 22);
        pushButtonOK = new QPushButton(SetZFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(200, 0, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        label = new QLabel(SetZFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 61, 21));
        doubleSpinBox = new QDoubleSpinBox(SetZFormClass);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(80, 0, 71, 22));
        doubleSpinBox->setDecimals(3);
        doubleSpinBox->setMaximum(9999.998999999999796);
        doubleSpinBox->setValue(1.000000000000000);
        label_2 = new QLabel(SetZFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 0, 31, 20));

        retranslateUi(SetZFormClass);

        QMetaObject::connectSlotsByName(SetZFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *SetZFormClass)
    {
        SetZFormClass->setWindowTitle(QCoreApplication::translate("SetZFormClass", "SetZForm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetZFormClass", "\350\250\255\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("SetZFormClass", "\357\274\272\343\200\200\350\250\255\345\256\232\345\200\244", nullptr));
        label_2->setText(QCoreApplication::translate("SetZFormClass", "mm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetZFormClass: public Ui_SetZFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETZFORM_H
