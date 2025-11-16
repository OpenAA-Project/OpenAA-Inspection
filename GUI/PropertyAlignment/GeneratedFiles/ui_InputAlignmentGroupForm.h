/********************************************************************************
** Form generated from reading UI file 'InputAlignmentGroupForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTALIGNMENTGROUPFORM_H
#define UI_INPUTALIGNMENTGROUPFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputAlignmentGroupFormClass
{
public:
    QLabel *label;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
    QComboBox *comboBGroup;

    void setupUi(QDialog *InputAlignmentGroupFormClass)
    {
        if (InputAlignmentGroupFormClass->objectName().isEmpty())
            InputAlignmentGroupFormClass->setObjectName("InputAlignmentGroupFormClass");
        InputAlignmentGroupFormClass->resize(209, 98);
        label = new QLabel(InputAlignmentGroupFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 10, 101, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonOK = new QPushButton(InputAlignmentGroupFormClass);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(10, 60, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(InputAlignmentGroupFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(110, 60, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        comboBGroup = new QComboBox(InputAlignmentGroupFormClass);
        comboBGroup->addItem(QString());
        comboBGroup->addItem(QString());
        comboBGroup->addItem(QString());
        comboBGroup->setObjectName("comboBGroup");
        comboBGroup->setGeometry(QRect(60, 30, 101, 22));

        retranslateUi(InputAlignmentGroupFormClass);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputAlignmentGroupFormClass);
    } // setupUi

    void retranslateUi(QDialog *InputAlignmentGroupFormClass)
    {
        InputAlignmentGroupFormClass->setWindowTitle(QCoreApplication::translate("InputAlignmentGroupFormClass", "InputAlignmentGroupForm", nullptr));
        label->setText(QCoreApplication::translate("InputAlignmentGroupFormClass", "\343\202\260\343\203\253\343\203\274\343\203\227\347\225\252\345\217\267\351\201\270\346\212\236", nullptr));
        ButtonOK->setText(QCoreApplication::translate("InputAlignmentGroupFormClass", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("InputAlignmentGroupFormClass", "Cancel", nullptr));
        comboBGroup->setItemText(0, QCoreApplication::translate("InputAlignmentGroupFormClass", "No 1", nullptr));
        comboBGroup->setItemText(1, QCoreApplication::translate("InputAlignmentGroupFormClass", "No 2", nullptr));
        comboBGroup->setItemText(2, QCoreApplication::translate("InputAlignmentGroupFormClass", "No 3", nullptr));

    } // retranslateUi

};

namespace Ui {
    class InputAlignmentGroupFormClass: public Ui_InputAlignmentGroupFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTALIGNMENTGROUPFORM_H
