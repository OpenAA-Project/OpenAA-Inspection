/********************************************************************************
** Form generated from reading UI file 'SetMechanicalOffsetForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETMECHANICALOFFSETFORM_H
#define UI_SETMECHANICALOFFSETFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_SetMechanicalOffsetForm
{
public:
    QSpinBox *spinBox;
    QPushButton *pushButtonSet;

    void setupUi(GUIFormBase *SetMechanicalOffsetForm)
    {
        if (SetMechanicalOffsetForm->objectName().isEmpty())
            SetMechanicalOffsetForm->setObjectName("SetMechanicalOffsetForm");
        SetMechanicalOffsetForm->resize(160, 32);
        spinBox = new QSpinBox(SetMechanicalOffsetForm);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(0, 0, 101, 31));
        QFont font;
        font.setPointSize(14);
        spinBox->setFont(font);
        spinBox->setMinimum(-99999999);
        spinBox->setMaximum(99999999);
        pushButtonSet = new QPushButton(SetMechanicalOffsetForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(110, 0, 51, 33));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);

        retranslateUi(SetMechanicalOffsetForm);

        QMetaObject::connectSlotsByName(SetMechanicalOffsetForm);
    } // setupUi

    void retranslateUi(GUIFormBase *SetMechanicalOffsetForm)
    {
        SetMechanicalOffsetForm->setWindowTitle(QCoreApplication::translate("SetMechanicalOffsetForm", "Set Mechanical Offset", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("SetMechanicalOffsetForm", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetMechanicalOffsetForm: public Ui_SetMechanicalOffsetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETMECHANICALOFFSETFORM_H
