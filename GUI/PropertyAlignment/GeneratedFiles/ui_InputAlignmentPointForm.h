/********************************************************************************
** Form generated from reading UI file 'InputAlignmentPointForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTALIGNMENTPOINTFORM_H
#define UI_INPUTALIGNMENTPOINTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_InputAlignmentPointFormClass
{
public:
    QLabel *label_2;
    QLabel *label;
    QSpinBox *EditMoveDot;
    QSpinBox *EditThreshold;
    QCheckBox *CheckBAlignmentOnOutline;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
    QPushButton *ButtonDefault;

    void setupUi(QDialog *InputAlignmentPointFormClass)
    {
        if (InputAlignmentPointFormClass->objectName().isEmpty())
            InputAlignmentPointFormClass->setObjectName("InputAlignmentPointFormClass");
        InputAlignmentPointFormClass->resize(333, 110);
        label_2 = new QLabel(InputAlignmentPointFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 10, 91, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(InputAlignmentPointFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMoveDot = new QSpinBox(InputAlignmentPointFormClass);
        EditMoveDot->setObjectName("EditMoveDot");
        EditMoveDot->setGeometry(QRect(10, 30, 91, 22));
        EditMoveDot->setMaximum(999);
        EditThreshold = new QSpinBox(InputAlignmentPointFormClass);
        EditThreshold->setObjectName("EditThreshold");
        EditThreshold->setGeometry(QRect(110, 30, 91, 21));
        EditThreshold->setMaximum(256);
        CheckBAlignmentOnOutline = new QCheckBox(InputAlignmentPointFormClass);
        CheckBAlignmentOnOutline->setObjectName("CheckBAlignmentOnOutline");
        CheckBAlignmentOnOutline->setGeometry(QRect(210, 20, 141, 18));
        ButtonOK = new QPushButton(InputAlignmentPointFormClass);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(20, 70, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(InputAlignmentPointFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(220, 70, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        ButtonDefault = new QPushButton(InputAlignmentPointFormClass);
        ButtonDefault->setObjectName("ButtonDefault");
        ButtonDefault->setGeometry(QRect(120, 70, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Default.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonDefault->setIcon(icon2);

        retranslateUi(InputAlignmentPointFormClass);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputAlignmentPointFormClass);
    } // setupUi

    void retranslateUi(QDialog *InputAlignmentPointFormClass)
    {
        InputAlignmentPointFormClass->setWindowTitle(QCoreApplication::translate("InputAlignmentPointFormClass", "InputAlignmentPointForm", nullptr));
        label_2->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\343\201\227\343\201\215\343\201\204\350\274\235\345\272\246", nullptr));
        label->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\346\216\242\347\264\242\350\267\235\351\233\242", nullptr));
        CheckBAlignmentOnOutline->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "\350\274\252\351\203\255\345\220\210\343\202\217\343\201\233", nullptr));
        ButtonOK->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "Cancel", nullptr));
        ButtonDefault->setText(QCoreApplication::translate("InputAlignmentPointFormClass", "Default", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputAlignmentPointFormClass: public Ui_InputAlignmentPointFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTALIGNMENTPOINTFORM_H
