/********************************************************************************
** Form generated from reading UI file 'InputNameForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTNAMEFORM_H
#define UI_INPUTNAMEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputNameFormClass
{
public:
    QLineEdit *lineEditLibName;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputNameFormClass)
    {
        if (InputNameFormClass->objectName().isEmpty())
            InputNameFormClass->setObjectName("InputNameFormClass");
        InputNameFormClass->resize(347, 81);
        lineEditLibName = new QLineEdit(InputNameFormClass);
        lineEditLibName->setObjectName("lineEditLibName");
        lineEditLibName->setGeometry(QRect(10, 10, 331, 20));
        pushButtonOK = new QPushButton(InputNameFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 40, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(InputNameFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(240, 40, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(InputNameFormClass);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputNameFormClass);
    } // setupUi

    void retranslateUi(QDialog *InputNameFormClass)
    {
        InputNameFormClass->setWindowTitle(QCoreApplication::translate("InputNameFormClass", "Input Library Name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputNameFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputNameFormClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputNameFormClass: public Ui_InputNameFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTNAMEFORM_H
