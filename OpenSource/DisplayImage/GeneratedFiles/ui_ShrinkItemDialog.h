/********************************************************************************
** Form generated from reading UI file 'ShrinkItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHRINKITEMDIALOG_H
#define UI_SHRINKITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ShrinkItemDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxExpandRate;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QCheckBox *checkBoxMaskForSameLib;

    void setupUi(QDialog *ShrinkItemDialog)
    {
        if (ShrinkItemDialog->objectName().isEmpty())
            ShrinkItemDialog->setObjectName("ShrinkItemDialog");
        ShrinkItemDialog->resize(323, 184);
        label = new QLabel(ShrinkItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 151, 18));
        spinBoxExpandRate = new QSpinBox(ShrinkItemDialog);
        spinBoxExpandRate->setObjectName("spinBoxExpandRate");
        spinBoxExpandRate->setGeometry(QRect(20, 30, 121, 31));
        spinBoxExpandRate->setMinimum(-1000);
        spinBoxExpandRate->setMaximum(1000);
        label_2 = new QLabel(ShrinkItemDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(170, 20, 111, 18));
        label_3 = new QLabel(ShrinkItemDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(170, 40, 111, 18));
        label_4 = new QLabel(ShrinkItemDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 110, 301, 31));
        pushButtonOK = new QPushButton(ShrinkItemDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 140, 131, 34));
        pushButtonCancel = new QPushButton(ShrinkItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(170, 140, 131, 34));
        checkBoxMaskForSameLib = new QCheckBox(ShrinkItemDialog);
        checkBoxMaskForSameLib->setObjectName("checkBoxMaskForSameLib");
        checkBoxMaskForSameLib->setGeometry(QRect(20, 70, 271, 31));
        checkBoxMaskForSameLib->setChecked(true);

        retranslateUi(ShrinkItemDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ShrinkItemDialog);
    } // setupUi

    void retranslateUi(QDialog *ShrinkItemDialog)
    {
        ShrinkItemDialog->setWindowTitle(QCoreApplication::translate("ShrinkItemDialog", "Shrink/Expand Item", nullptr));
        label->setText(QCoreApplication::translate("ShrinkItemDialog", "Expand pixels", nullptr));
        label_2->setText(QCoreApplication::translate("ShrinkItemDialog", "+ expand", nullptr));
        label_3->setText(QCoreApplication::translate("ShrinkItemDialog", "- shrink", nullptr));
        label_4->setText(QCoreApplication::translate("ShrinkItemDialog", "Execute for Selected , Unlocked items", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ShrinkItemDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ShrinkItemDialog", "Cancel", nullptr));
        checkBoxMaskForSameLib->setText(QCoreApplication::translate("ShrinkItemDialog", "Mask for same Library", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShrinkItemDialog: public Ui_ShrinkItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHRINKITEMDIALOG_H
