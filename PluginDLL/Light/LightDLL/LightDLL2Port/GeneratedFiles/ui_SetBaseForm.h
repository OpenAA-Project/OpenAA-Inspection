/********************************************************************************
** Form generated from reading UI file 'SetBaseForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETBASEFORM_H
#define UI_SETBASEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SetBaseFormClass
{
public:
    QSpinBox *spinBoxPort0;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxPort1;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SetBaseFormClass)
    {
        if (SetBaseFormClass->objectName().isEmpty())
            SetBaseFormClass->setObjectName("SetBaseFormClass");
        SetBaseFormClass->resize(140, 131);
        spinBoxPort0 = new QSpinBox(SetBaseFormClass);
        spinBoxPort0->setObjectName("spinBoxPort0");
        spinBoxPort0->setGeometry(QRect(70, 10, 61, 22));
        label = new QLabel(SetBaseFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 50, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(SetBaseFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 50, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPort1 = new QSpinBox(SetBaseFormClass);
        spinBoxPort1->setObjectName("spinBoxPort1");
        spinBoxPort1->setGeometry(QRect(70, 40, 61, 22));
        pushButtonOK = new QPushButton(SetBaseFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 90, 81, 31));

        retranslateUi(SetBaseFormClass);

        QMetaObject::connectSlotsByName(SetBaseFormClass);
    } // setupUi

    void retranslateUi(QDialog *SetBaseFormClass)
    {
        SetBaseFormClass->setWindowTitle(QCoreApplication::translate("SetBaseFormClass", "SetBaseForm", nullptr));
        label->setText(QCoreApplication::translate("SetBaseFormClass", "Port 0", nullptr));
        label_2->setText(QCoreApplication::translate("SetBaseFormClass", "Port 0", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetBaseFormClass", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetBaseFormClass: public Ui_SetBaseFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETBASEFORM_H
