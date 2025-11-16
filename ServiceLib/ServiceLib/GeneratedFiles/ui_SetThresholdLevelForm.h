/********************************************************************************
** Form generated from reading UI file 'SetThresholdLevelForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTHRESHOLDLEVELFORM_H
#define UI_SETTHRESHOLDLEVELFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetThresholdLevelForm
{
public:
    QSlider *horizontalSlider;
    QLabel *label;
    QPushButton *pushButtonParent;

    void setupUi(QWidget *SetThresholdLevelForm)
    {
        if (SetThresholdLevelForm->objectName().isEmpty())
            SetThresholdLevelForm->setObjectName("SetThresholdLevelForm");
        SetThresholdLevelForm->resize(170, 80);
        horizontalSlider = new QSlider(SetThresholdLevelForm);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(0, 30, 171, 40));
        horizontalSlider->setMaximum(5);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBothSides);
        label = new QLabel(SetThresholdLevelForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 60, 171, 21));
        label->setAlignment(Qt::AlignCenter);
        pushButtonParent = new QPushButton(SetThresholdLevelForm);
        pushButtonParent->setObjectName("pushButtonParent");
        pushButtonParent->setGeometry(QRect(10, 0, 151, 28));

        retranslateUi(SetThresholdLevelForm);

        QMetaObject::connectSlotsByName(SetThresholdLevelForm);
    } // setupUi

    void retranslateUi(QWidget *SetThresholdLevelForm)
    {
        SetThresholdLevelForm->setWindowTitle(QCoreApplication::translate("SetThresholdLevelForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("SetThresholdLevelForm", "1", nullptr));
        pushButtonParent->setText(QCoreApplication::translate("SetThresholdLevelForm", "Top root", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetThresholdLevelForm: public Ui_SetThresholdLevelForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTHRESHOLDLEVELFORM_H
