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

class Ui_SetBaseForm
{
public:
    QSpinBox *spinBoxPort0;
    QPushButton *pushButtonOK;
    QLabel *label;
    QSpinBox *spinBoxPort1;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxPort3;
    QLabel *label_4;
    QSpinBox *spinBoxPort2;

    void setupUi(QDialog *SetBaseForm)
    {
        if (SetBaseForm->objectName().isEmpty())
            SetBaseForm->setObjectName("SetBaseForm");
        SetBaseForm->resize(161, 188);
        spinBoxPort0 = new QSpinBox(SetBaseForm);
        spinBoxPort0->setObjectName("spinBoxPort0");
        spinBoxPort0->setGeometry(QRect(80, 10, 61, 22));
        pushButtonOK = new QPushButton(SetBaseForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 140, 81, 31));
        label = new QLabel(SetBaseForm);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 50, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPort1 = new QSpinBox(SetBaseForm);
        spinBoxPort1->setObjectName("spinBoxPort1");
        spinBoxPort1->setGeometry(QRect(80, 40, 61, 22));
        label_2 = new QLabel(SetBaseForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 50, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(SetBaseForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 70, 50, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPort3 = new QSpinBox(SetBaseForm);
        spinBoxPort3->setObjectName("spinBoxPort3");
        spinBoxPort3->setGeometry(QRect(80, 100, 61, 22));
        label_4 = new QLabel(SetBaseForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 100, 50, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPort2 = new QSpinBox(SetBaseForm);
        spinBoxPort2->setObjectName("spinBoxPort2");
        spinBoxPort2->setGeometry(QRect(80, 70, 61, 22));

        retranslateUi(SetBaseForm);

        QMetaObject::connectSlotsByName(SetBaseForm);
    } // setupUi

    void retranslateUi(QDialog *SetBaseForm)
    {
        SetBaseForm->setWindowTitle(QCoreApplication::translate("SetBaseForm", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetBaseForm", "OK", nullptr));
        label->setText(QCoreApplication::translate("SetBaseForm", "Port 0", nullptr));
        label_2->setText(QCoreApplication::translate("SetBaseForm", "Port 0", nullptr));
        label_3->setText(QCoreApplication::translate("SetBaseForm", "Port 0", nullptr));
        label_4->setText(QCoreApplication::translate("SetBaseForm", "Port 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetBaseForm: public Ui_SetBaseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETBASEFORM_H
