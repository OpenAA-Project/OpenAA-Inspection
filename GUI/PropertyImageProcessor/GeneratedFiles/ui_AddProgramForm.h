/********************************************************************************
** Form generated from reading UI file 'AddProgramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPROGRAMFORM_H
#define UI_ADDPROGRAMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddProgramFormClass
{
public:
    QLineEdit *EditName;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;

    void setupUi(QDialog *AddProgramFormClass)
    {
        if (AddProgramFormClass->objectName().isEmpty())
            AddProgramFormClass->setObjectName("AddProgramFormClass");
        AddProgramFormClass->resize(315, 73);
        EditName = new QLineEdit(AddProgramFormClass);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(10, 30, 201, 20));
        pushButtonOK = new QPushButton(AddProgramFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(230, 10, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(AddProgramFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(230, 40, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(AddProgramFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 201, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(AddProgramFormClass);

        QMetaObject::connectSlotsByName(AddProgramFormClass);
    } // setupUi

    void retranslateUi(QDialog *AddProgramFormClass)
    {
        AddProgramFormClass->setWindowTitle(QCoreApplication::translate("AddProgramFormClass", "AddProgramForm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddProgramFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddProgramFormClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("AddProgramFormClass", "Program name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddProgramFormClass: public Ui_AddProgramFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPROGRAMFORM_H
