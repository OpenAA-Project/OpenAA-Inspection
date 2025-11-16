/********************************************************************************
** Form generated from reading UI file 'FilterSettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERSETTINGDIALOG_H
#define UI_FILTERSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_FilterSettingDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxStrength;
    QLabel *label_2;
    QSpinBox *spinBoxPosition;

    void setupUi(QDialog *FilterSettingDialog)
    {
        if (FilterSettingDialog->objectName().isEmpty())
            FilterSettingDialog->setObjectName("FilterSettingDialog");
        FilterSettingDialog->resize(400, 140);
        pushButtonOK = new QPushButton(FilterSettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(80, 80, 112, 34));
        pushButtonCancel = new QPushButton(FilterSettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(220, 80, 112, 34));
        label = new QLabel(FilterSettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(230, 10, 171, 18));
        doubleSpinBoxStrength = new QDoubleSpinBox(FilterSettingDialog);
        doubleSpinBoxStrength->setObjectName("doubleSpinBoxStrength");
        doubleSpinBoxStrength->setGeometry(QRect(230, 30, 141, 24));
        doubleSpinBoxStrength->setMinimum(-99.900000000000006);
        label_2 = new QLabel(FilterSettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 191, 18));
        spinBoxPosition = new QSpinBox(FilterSettingDialog);
        spinBoxPosition->setObjectName("spinBoxPosition");
        spinBoxPosition->setGeometry(QRect(50, 30, 111, 24));
        spinBoxPosition->setMaximum(255);
        spinBoxPosition->setValue(128);

        retranslateUi(FilterSettingDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(FilterSettingDialog);
    } // setupUi

    void retranslateUi(QDialog *FilterSettingDialog)
    {
        FilterSettingDialog->setWindowTitle(QCoreApplication::translate("FilterSettingDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("FilterSettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("FilterSettingDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("FilterSettingDialog", "Log filter strength", nullptr));
        label_2->setText(QCoreApplication::translate("FilterSettingDialog", "Max conversion position", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterSettingDialog: public Ui_FilterSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERSETTINGDIALOG_H
