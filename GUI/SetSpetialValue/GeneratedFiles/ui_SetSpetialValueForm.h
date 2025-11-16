/********************************************************************************
** Form generated from reading UI file 'SetSpetialValueForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSPETIALVALUEFORM_H
#define UI_SETSPETIALVALUEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_SetSpetialValueForm
{
public:
    QSpinBox *spinBox;
    QPushButton *pushButtonSet;

    void setupUi(GUIFormBase *SetSpetialValueForm)
    {
        if (SetSpetialValueForm->objectName().isEmpty())
            SetSpetialValueForm->setObjectName("SetSpetialValueForm");
        SetSpetialValueForm->resize(160, 32);
        spinBox = new QSpinBox(SetSpetialValueForm);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(0, 0, 101, 31));
        QFont font;
        font.setPointSize(14);
        spinBox->setFont(font);
        spinBox->setMinimum(-99999999);
        spinBox->setMaximum(99999999);
        pushButtonSet = new QPushButton(SetSpetialValueForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(110, 0, 51, 33));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);

        retranslateUi(SetSpetialValueForm);

        QMetaObject::connectSlotsByName(SetSpetialValueForm);
    } // setupUi

    void retranslateUi(GUIFormBase *SetSpetialValueForm)
    {
        SetSpetialValueForm->setWindowTitle(QCoreApplication::translate("SetSpetialValueForm", "Set spetial value", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("SetSpetialValueForm", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetSpetialValueForm: public Ui_SetSpetialValueForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSPETIALVALUEFORM_H
