/********************************************************************************
** Form generated from reading UI file 'SetSkipMarkForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSKIPMARKFORM_H
#define UI_SETSKIPMARKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetSkipMarkForm
{
public:
    QLineEdit *lineEditItemName;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QPushButton *pushButtonModify;
    QSpinBox *spinBox;
    QLineEdit *lineEditItemName_2;
    QLabel *label_2;
    QPushButton *pushButtonSelectArea;

    void setupUi(QWidget *SetSkipMarkForm)
    {
        if (SetSkipMarkForm->objectName().isEmpty())
            SetSkipMarkForm->setObjectName("SetSkipMarkForm");
        SetSkipMarkForm->resize(472, 121);
        lineEditItemName = new QLineEdit(SetSkipMarkForm);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(100, 10, 361, 21));
        pushButtonCancel = new QPushButton(SetSkipMarkForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(360, 80, 101, 31));
        label = new QLabel(SetSkipMarkForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonModify = new QPushButton(SetSkipMarkForm);
        pushButtonModify->setObjectName("pushButtonModify");
        pushButtonModify->setGeometry(QRect(240, 80, 101, 31));
        spinBox = new QSpinBox(SetSkipMarkForm);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(110, 40, 81, 22));
        spinBox->setMaximum(9999999);
        lineEditItemName_2 = new QLineEdit(SetSkipMarkForm);
        lineEditItemName_2->setObjectName("lineEditItemName_2");
        lineEditItemName_2->setGeometry(QRect(190, 40, 271, 21));
        label_2 = new QLabel(SetSkipMarkForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 91, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonSelectArea = new QPushButton(SetSkipMarkForm);
        pushButtonSelectArea->setObjectName("pushButtonSelectArea");
        pushButtonSelectArea->setGeometry(QRect(92, 70, 101, 28));

        retranslateUi(SetSkipMarkForm);

        pushButtonModify->setDefault(true);


        QMetaObject::connectSlotsByName(SetSkipMarkForm);
    } // setupUi

    void retranslateUi(QWidget *SetSkipMarkForm)
    {
        SetSkipMarkForm->setWindowTitle(QCoreApplication::translate("SetSkipMarkForm", "Form", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetSkipMarkForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SetSkipMarkForm", "Item Name", nullptr));
        pushButtonModify->setText(QCoreApplication::translate("SetSkipMarkForm", "Modify", nullptr));
        label_2->setText(QCoreApplication::translate("SetSkipMarkForm", "Area to skip", nullptr));
        pushButtonSelectArea->setText(QCoreApplication::translate("SetSkipMarkForm", "Select area", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetSkipMarkForm: public Ui_SetSkipMarkForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSKIPMARKFORM_H
