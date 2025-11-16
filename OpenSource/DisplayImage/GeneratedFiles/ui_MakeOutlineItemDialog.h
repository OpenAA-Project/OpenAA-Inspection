/********************************************************************************
** Form generated from reading UI file 'MakeOutlineItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKEOUTLINEITEMDIALOG_H
#define UI_MAKEOUTLINEITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_MakeOutlineItemDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxOutlineWidth;
    QPushButton *pushButtonGenerate;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *MakeOutlineItemDialog)
    {
        if (MakeOutlineItemDialog->objectName().isEmpty())
            MakeOutlineItemDialog->setObjectName("MakeOutlineItemDialog");
        MakeOutlineItemDialog->resize(264, 129);
        label = new QLabel(MakeOutlineItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 101, 31));
        spinBoxOutlineWidth = new QSpinBox(MakeOutlineItemDialog);
        spinBoxOutlineWidth->setObjectName("spinBoxOutlineWidth");
        spinBoxOutlineWidth->setGeometry(QRect(120, 10, 101, 31));
        spinBoxOutlineWidth->setMaximum(100);
        pushButtonGenerate = new QPushButton(MakeOutlineItemDialog);
        pushButtonGenerate->setObjectName("pushButtonGenerate");
        pushButtonGenerate->setGeometry(QRect(20, 70, 111, 41));
        pushButtonCancel = new QPushButton(MakeOutlineItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 70, 111, 41));

        retranslateUi(MakeOutlineItemDialog);

        pushButtonGenerate->setDefault(true);


        QMetaObject::connectSlotsByName(MakeOutlineItemDialog);
    } // setupUi

    void retranslateUi(QDialog *MakeOutlineItemDialog)
    {
        MakeOutlineItemDialog->setWindowTitle(QCoreApplication::translate("MakeOutlineItemDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("MakeOutlineItemDialog", "Outline width", nullptr));
        pushButtonGenerate->setText(QCoreApplication::translate("MakeOutlineItemDialog", "Generate", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("MakeOutlineItemDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeOutlineItemDialog: public Ui_MakeOutlineItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKEOUTLINEITEMDIALOG_H
