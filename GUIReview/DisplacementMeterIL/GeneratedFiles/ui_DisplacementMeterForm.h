/********************************************************************************
** Form generated from reading UI file 'DisplacementMeterForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLACEMENTMETERFORM_H
#define UI_DISPLACEMENTMETERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_DisplacementMeterForm
{
public:
    QPushButton *pushButtonZero;
    QPushButton *pushButtonMeasure;
    QLabel *labelResult;

    void setupUi(GUIFormBase *DisplacementMeterForm)
    {
        if (DisplacementMeterForm->objectName().isEmpty())
            DisplacementMeterForm->setObjectName(QString::fromUtf8("DisplacementMeterForm"));
        DisplacementMeterForm->resize(95, 89);
        pushButtonZero = new QPushButton(DisplacementMeterForm);
        pushButtonZero->setObjectName(QString::fromUtf8("pushButtonZero"));
        pushButtonZero->setGeometry(QRect(10, 10, 75, 23));
        pushButtonMeasure = new QPushButton(DisplacementMeterForm);
        pushButtonMeasure->setObjectName(QString::fromUtf8("pushButtonMeasure"));
        pushButtonMeasure->setGeometry(QRect(10, 40, 75, 23));
        labelResult = new QLabel(DisplacementMeterForm);
        labelResult->setObjectName(QString::fromUtf8("labelResult"));
        labelResult->setGeometry(QRect(30, 70, 50, 12));

        retranslateUi(DisplacementMeterForm);

        QMetaObject::connectSlotsByName(DisplacementMeterForm);
    } // setupUi

    void retranslateUi(GUIFormBase *DisplacementMeterForm)
    {
        DisplacementMeterForm->setWindowTitle(QCoreApplication::translate("DisplacementMeterForm", "Dialog", nullptr));
        pushButtonZero->setText(QCoreApplication::translate("DisplacementMeterForm", "Zero", nullptr));
        pushButtonMeasure->setText(QCoreApplication::translate("DisplacementMeterForm", "Measure", nullptr));
        labelResult->setText(QCoreApplication::translate("DisplacementMeterForm", "0.00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisplacementMeterForm: public Ui_DisplacementMeterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLACEMENTMETERFORM_H
