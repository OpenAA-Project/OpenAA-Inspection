/********************************************************************************
** Form generated from reading UI file 'SetLineWidthDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETLINEWIDTHDIALOG_H
#define UI_SETLINEWIDTHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SetLineWidthDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxLineWidth;
    QDoubleSpinBox *doubleSpinBoxLineWidthMM;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SetLineWidthDialog)
    {
        if (SetLineWidthDialog->objectName().isEmpty())
            SetLineWidthDialog->setObjectName("SetLineWidthDialog");
        SetLineWidthDialog->resize(369, 160);
        label = new QLabel(SetLineWidthDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 351, 31));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(SetLineWidthDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 60, 37, 21));
        label_3 = new QLabel(SetLineWidthDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(340, 60, 37, 21));
        spinBoxLineWidth = new QSpinBox(SetLineWidthDialog);
        spinBoxLineWidth->setObjectName("spinBoxLineWidth");
        spinBoxLineWidth->setGeometry(QRect(10, 50, 121, 31));
        spinBoxLineWidth->setMaximum(10000);
        doubleSpinBoxLineWidthMM = new QDoubleSpinBox(SetLineWidthDialog);
        doubleSpinBoxLineWidthMM->setObjectName("doubleSpinBoxLineWidthMM");
        doubleSpinBoxLineWidthMM->setGeometry(QRect(200, 50, 131, 31));
        doubleSpinBoxLineWidthMM->setMaximum(1000.000000000000000);
        pushButtonOK = new QPushButton(SetLineWidthDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 100, 121, 41));
        pushButtonCancel = new QPushButton(SetLineWidthDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(190, 100, 121, 41));

        retranslateUi(SetLineWidthDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SetLineWidthDialog);
    } // setupUi

    void retranslateUi(QDialog *SetLineWidthDialog)
    {
        SetLineWidthDialog->setWindowTitle(QCoreApplication::translate("SetLineWidthDialog", "Line width", nullptr));
        label->setText(QCoreApplication::translate("SetLineWidthDialog", "\347\267\232\343\201\256\345\244\252\343\201\225", nullptr));
        label_2->setText(QCoreApplication::translate("SetLineWidthDialog", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        label_3->setText(QCoreApplication::translate("SetLineWidthDialog", "mm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetLineWidthDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetLineWidthDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetLineWidthDialog: public Ui_SetLineWidthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETLINEWIDTHDIALOG_H
