/********************************************************************************
** Form generated from reading UI file 'InputNamingNameForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTNAMINGNAMEFORM_H
#define UI_INPUTNAMINGNAMEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputNamingNameFormClass
{
public:
    QLineEdit *lineEditName;
    QLabel *label;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label_2;
    QSpinBox *spinBoxX;
    QSpinBox *spinBoxY;
    QLabel *label_3;

    void setupUi(QWidget *InputNamingNameFormClass)
    {
        if (InputNamingNameFormClass->objectName().isEmpty())
            InputNamingNameFormClass->setObjectName("InputNamingNameFormClass");
        InputNamingNameFormClass->resize(226, 134);
        lineEditName = new QLineEdit(InputNamingNameFormClass);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(30, 30, 181, 20));
        label = new QLabel(InputNamingNameFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 50, 14));
        pushButtonOK = new QPushButton(InputNamingNameFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 90, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonOK->setAutoDefault(false);
        pushButtonCancel = new QPushButton(InputNamingNameFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 90, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label_2 = new QLabel(InputNamingNameFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(115, 60, 41, 21));
        spinBoxX = new QSpinBox(InputNamingNameFormClass);
        spinBoxX->setObjectName("spinBoxX");
        spinBoxX->setGeometry(QRect(160, 60, 51, 22));
        spinBoxX->setMaximum(9999);
        spinBoxY = new QSpinBox(InputNamingNameFormClass);
        spinBoxY->setObjectName("spinBoxY");
        spinBoxY->setGeometry(QRect(40, 60, 51, 22));
        spinBoxY->setMinimum(-1);
        spinBoxY->setMaximum(9999);
        label_3 = new QLabel(InputNamingNameFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(15, 60, 21, 21));

        retranslateUi(InputNamingNameFormClass);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputNamingNameFormClass);
    } // setupUi

    void retranslateUi(QWidget *InputNamingNameFormClass)
    {
        InputNamingNameFormClass->setWindowTitle(QCoreApplication::translate("InputNamingNameFormClass", "InputNamingNameForm", nullptr));
        label->setText(QCoreApplication::translate("InputNamingNameFormClass", "Name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputNamingNameFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputNamingNameFormClass", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("InputNamingNameFormClass", "Column", nullptr));
        label_3->setText(QCoreApplication::translate("InputNamingNameFormClass", "Row", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputNamingNameFormClass: public Ui_InputNamingNameFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTNAMINGNAMEFORM_H
