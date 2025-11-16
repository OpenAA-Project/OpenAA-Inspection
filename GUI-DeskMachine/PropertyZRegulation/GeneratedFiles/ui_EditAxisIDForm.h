/********************************************************************************
** Form generated from reading UI file 'EditAxisIDForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITAXISIDFORM_H
#define UI_EDITAXISIDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditAxisIDFormClass
{
public:
    QSpinBox *spinBoxAxisID;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxCenterInMaster;
    QLabel *label_3;
    QSpinBox *spinBoxOKZone;

    void setupUi(QDialog *EditAxisIDFormClass)
    {
        if (EditAxisIDFormClass->objectName().isEmpty())
            EditAxisIDFormClass->setObjectName(QString::fromUtf8("EditAxisIDFormClass"));
        EditAxisIDFormClass->resize(242, 156);
        spinBoxAxisID = new QSpinBox(EditAxisIDFormClass);
        spinBoxAxisID->setObjectName(QString::fromUtf8("spinBoxAxisID"));
        spinBoxAxisID->setGeometry(QRect(130, 10, 71, 22));
        spinBoxAxisID->setMaximum(999999);
        pushButtonOK = new QPushButton(EditAxisIDFormClass);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(30, 110, 75, 31));
        pushButtonCancel = new QPushButton(EditAxisIDFormClass);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(140, 110, 75, 31));
        label = new QLabel(EditAxisIDFormClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 10, 61, 21));
        label_2 = new QLabel(EditAxisIDFormClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 40, 101, 21));
        spinBoxCenterInMaster = new QSpinBox(EditAxisIDFormClass);
        spinBoxCenterInMaster->setObjectName(QString::fromUtf8("spinBoxCenterInMaster"));
        spinBoxCenterInMaster->setGeometry(QRect(130, 40, 71, 22));
        spinBoxCenterInMaster->setMaximum(999999);
        label_3 = new QLabel(EditAxisIDFormClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 70, 101, 21));
        spinBoxOKZone = new QSpinBox(EditAxisIDFormClass);
        spinBoxOKZone->setObjectName(QString::fromUtf8("spinBoxOKZone"));
        spinBoxOKZone->setGeometry(QRect(130, 70, 71, 22));
        spinBoxOKZone->setMaximum(999999);

        retranslateUi(EditAxisIDFormClass);

        QMetaObject::connectSlotsByName(EditAxisIDFormClass);
    } // setupUi

    void retranslateUi(QDialog *EditAxisIDFormClass)
    {
        EditAxisIDFormClass->setWindowTitle(QCoreApplication::translate("EditAxisIDFormClass", "Input ID and Threshold", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditAxisIDFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditAxisIDFormClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("EditAxisIDFormClass", "Area ID", nullptr));
        label_2->setText(QCoreApplication::translate("EditAxisIDFormClass", "OK center Position", nullptr));
        label_3->setText(QCoreApplication::translate("EditAxisIDFormClass", "OK position zone", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditAxisIDFormClass: public Ui_EditAxisIDFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITAXISIDFORM_H
