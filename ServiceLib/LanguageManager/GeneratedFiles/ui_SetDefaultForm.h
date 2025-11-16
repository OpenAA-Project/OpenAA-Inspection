/********************************************************************************
** Form generated from reading UI file 'SetDefaultForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDEFAULTFORM_H
#define UI_SETDEFAULTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetDefaultForm
{
public:
    QLabel *label;
    QLineEdit *lineEditDefaultLNGPath;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SetDefaultForm)
    {
        if (SetDefaultForm->objectName().isEmpty())
            SetDefaultForm->setObjectName("SetDefaultForm");
        SetDefaultForm->resize(366, 164);
        label = new QLabel(SetDefaultForm);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 321, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditDefaultLNGPath = new QLineEdit(SetDefaultForm);
        lineEditDefaultLNGPath->setObjectName("lineEditDefaultLNGPath");
        lineEditDefaultLNGPath->setGeometry(QRect(20, 30, 321, 20));
        pushButtonOK = new QPushButton(SetDefaultForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 110, 81, 31));
        pushButtonCancel = new QPushButton(SetDefaultForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(260, 110, 81, 31));

        retranslateUi(SetDefaultForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SetDefaultForm);
    } // setupUi

    void retranslateUi(QDialog *SetDefaultForm)
    {
        SetDefaultForm->setWindowTitle(QCoreApplication::translate("SetDefaultForm", "Set default", nullptr));
        label->setText(QCoreApplication::translate("SetDefaultForm", "Default output LNG path", nullptr));
        lineEditDefaultLNGPath->setText(QCoreApplication::translate("SetDefaultForm", "Language", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetDefaultForm", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetDefaultForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetDefaultForm: public Ui_SetDefaultForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDEFAULTFORM_H
