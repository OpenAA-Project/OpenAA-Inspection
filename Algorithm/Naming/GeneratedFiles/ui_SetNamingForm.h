/********************************************************************************
** Form generated from reading UI file 'SetNamingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETNAMINGFORM_H
#define UI_SETNAMINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetNamingFormClass
{
public:
    QLabel *label;
    QLineEdit *lineEditName;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxX;
    QLabel *label_2;
    QSpinBox *spinBoxY;
    QLabel *label_3;

    void setupUi(QWidget *SetNamingFormClass)
    {
        if (SetNamingFormClass->objectName().isEmpty())
            SetNamingFormClass->setObjectName("SetNamingFormClass");
        SetNamingFormClass->resize(214, 146);
        label = new QLabel(SetNamingFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 50, 14));
        lineEditName = new QLineEdit(SetNamingFormClass);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(10, 30, 191, 20));
        pushButtonOK = new QPushButton(SetNamingFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(70, 100, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        spinBoxX = new QSpinBox(SetNamingFormClass);
        spinBoxX->setObjectName("spinBoxX");
        spinBoxX->setGeometry(QRect(150, 60, 51, 22));
        spinBoxX->setMaximum(9999);
        label_2 = new QLabel(SetNamingFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 60, 41, 21));
        spinBoxY = new QSpinBox(SetNamingFormClass);
        spinBoxY->setObjectName("spinBoxY");
        spinBoxY->setGeometry(QRect(40, 60, 51, 22));
        spinBoxY->setMaximum(9999);
        label_3 = new QLabel(SetNamingFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(15, 60, 21, 21));

        retranslateUi(SetNamingFormClass);

        QMetaObject::connectSlotsByName(SetNamingFormClass);
    } // setupUi

    void retranslateUi(QWidget *SetNamingFormClass)
    {
        SetNamingFormClass->setWindowTitle(QCoreApplication::translate("SetNamingFormClass", "SetNamingForm", nullptr));
        label->setText(QCoreApplication::translate("SetNamingFormClass", "Name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetNamingFormClass", "OK", nullptr));
        label_2->setText(QCoreApplication::translate("SetNamingFormClass", "Column", nullptr));
        label_3->setText(QCoreApplication::translate("SetNamingFormClass", "Row", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetNamingFormClass: public Ui_SetNamingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETNAMINGFORM_H
