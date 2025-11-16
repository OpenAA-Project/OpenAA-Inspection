/********************************************************************************
** Form generated from reading UI file 'ShowMatchShiftRotationForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWMATCHSHIFTROTATIONFORM_H
#define UI_SHOWMATCHSHIFTROTATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowMatchShiftRotationForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditAngle;
    QLineEdit *lineEditShift;

    void setupUi(GUIFormBase *ShowMatchShiftRotationForm)
    {
        if (ShowMatchShiftRotationForm->objectName().isEmpty())
            ShowMatchShiftRotationForm->setObjectName("ShowMatchShiftRotationForm");
        ShowMatchShiftRotationForm->resize(193, 54);
        label = new QLabel(ShowMatchShiftRotationForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 75, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowMatchShiftRotationForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 30, 75, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditAngle = new QLineEdit(ShowMatchShiftRotationForm);
        lineEditAngle->setObjectName("lineEditAngle");
        lineEditAngle->setGeometry(QRect(80, 0, 113, 24));
        lineEditAngle->setReadOnly(true);
        lineEditShift = new QLineEdit(ShowMatchShiftRotationForm);
        lineEditShift->setObjectName("lineEditShift");
        lineEditShift->setGeometry(QRect(80, 30, 113, 24));
        lineEditShift->setReadOnly(true);

        retranslateUi(ShowMatchShiftRotationForm);

        QMetaObject::connectSlotsByName(ShowMatchShiftRotationForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowMatchShiftRotationForm)
    {
        ShowMatchShiftRotationForm->setWindowTitle(QCoreApplication::translate("ShowMatchShiftRotationForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("ShowMatchShiftRotationForm", "\350\247\222\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("ShowMatchShiftRotationForm", "\343\202\272\343\203\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowMatchShiftRotationForm: public Ui_ShowMatchShiftRotationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWMATCHSHIFTROTATIONFORM_H
