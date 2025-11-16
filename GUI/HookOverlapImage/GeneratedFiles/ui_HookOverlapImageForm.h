/********************************************************************************
** Form generated from reading UI file 'HookOverlapImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOOKOVERLAPIMAGEFORM_H
#define UI_HOOKOVERLAPIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_HookOverlapImageForm
{
public:
    QSlider *horizontalSlider;
    QLabel *labelValue;
    QLabel *labelPeercentage;

    void setupUi(GUIFormBase *HookOverlapImageForm)
    {
        if (HookOverlapImageForm->objectName().isEmpty())
            HookOverlapImageForm->setObjectName("HookOverlapImageForm");
        HookOverlapImageForm->resize(233, 45);
        horizontalSlider = new QSlider(HookOverlapImageForm);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(10, 10, 161, 22));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setPageStep(8);
        horizontalSlider->setValue(50);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::NoTicks);
        labelValue = new QLabel(HookOverlapImageForm);
        labelValue->setObjectName("labelValue");
        labelValue->setGeometry(QRect(180, 10, 31, 21));
        labelPeercentage = new QLabel(HookOverlapImageForm);
        labelPeercentage->setObjectName("labelPeercentage");
        labelPeercentage->setGeometry(QRect(210, 10, 16, 21));

        retranslateUi(HookOverlapImageForm);

        QMetaObject::connectSlotsByName(HookOverlapImageForm);
    } // setupUi

    void retranslateUi(GUIFormBase *HookOverlapImageForm)
    {
        HookOverlapImageForm->setWindowTitle(QCoreApplication::translate("HookOverlapImageForm", "Form", nullptr));
        labelValue->setText(QCoreApplication::translate("HookOverlapImageForm", "100", nullptr));
        labelPeercentage->setText(QCoreApplication::translate("HookOverlapImageForm", "%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HookOverlapImageForm: public Ui_HookOverlapImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOOKOVERLAPIMAGEFORM_H
