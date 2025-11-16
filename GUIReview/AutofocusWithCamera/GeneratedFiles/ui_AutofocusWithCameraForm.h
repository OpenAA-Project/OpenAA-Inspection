/********************************************************************************
** Form generated from reading UI file 'AutofocusWithCameraForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOFOCUSWITHCAMERAFORM_H
#define UI_AUTOFOCUSWITHCAMERAFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_AutofocusWithCameraForm
{
public:
    QPushButton *pushButtonStart;
    QSlider *horizontalSlider;
    QPushButton *pushButtonSettingArea;
    QPushButton *pushButtonScanNEAR;
    QLabel *label;

    void setupUi(GUIFormBase *AutofocusWithCameraForm)
    {
        if (AutofocusWithCameraForm->objectName().isEmpty())
            AutofocusWithCameraForm->setObjectName(QString::fromUtf8("AutofocusWithCameraForm"));
        AutofocusWithCameraForm->resize(139, 144);
        pushButtonStart = new QPushButton(AutofocusWithCameraForm);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        pushButtonStart->setGeometry(QRect(10, 30, 91, 41));
        horizontalSlider = new QSlider(AutofocusWithCameraForm);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 120, 121, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButtonSettingArea = new QPushButton(AutofocusWithCameraForm);
        pushButtonSettingArea->setObjectName(QString::fromUtf8("pushButtonSettingArea"));
        pushButtonSettingArea->setGeometry(QRect(100, 30, 31, 41));
        pushButtonScanNEAR = new QPushButton(AutofocusWithCameraForm);
        pushButtonScanNEAR->setObjectName(QString::fromUtf8("pushButtonScanNEAR"));
        pushButtonScanNEAR->setGeometry(QRect(10, 70, 91, 41));
        label = new QLabel(AutofocusWithCameraForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 141, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(AutofocusWithCameraForm);

        QMetaObject::connectSlotsByName(AutofocusWithCameraForm);
    } // setupUi

    void retranslateUi(GUIFormBase *AutofocusWithCameraForm)
    {
        AutofocusWithCameraForm->setWindowTitle(QCoreApplication::translate("AutofocusWithCameraForm", "Form", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("AutofocusWithCameraForm", "Scan all", nullptr));
        pushButtonSettingArea->setText(QCoreApplication::translate("AutofocusWithCameraForm", "...", nullptr));
        pushButtonScanNEAR->setText(QCoreApplication::translate("AutofocusWithCameraForm", "Scan NEAR", nullptr));
        label->setText(QCoreApplication::translate("AutofocusWithCameraForm", "Auto focus", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutofocusWithCameraForm: public Ui_AutofocusWithCameraForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOFOCUSWITHCAMERAFORM_H
