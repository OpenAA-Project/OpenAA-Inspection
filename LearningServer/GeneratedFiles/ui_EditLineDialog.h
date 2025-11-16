/********************************************************************************
** Form generated from reading UI file 'EditLineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLINEDIALOG_H
#define UI_EDITLINEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditLineDialog
{
public:
    QLabel *label_2;
    QLabel *label_3;
    QSlider *horizontalSliderPriority;
    QLabel *label_4;
    QSpinBox *spinBoxPriority;
    QGroupBox *groupBox;
    QRadioButton *radioButtonOK;
    QRadioButton *radioButtonNG;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditLineDialog)
    {
        if (EditLineDialog->objectName().isEmpty())
            EditLineDialog->setObjectName("EditLineDialog");
        EditLineDialog->resize(415, 171);
        label_2 = new QLabel(EditLineDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 10, 61, 20));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(EditLineDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(300, 10, 41, 20));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalSliderPriority = new QSlider(EditLineDialog);
        horizontalSliderPriority->setObjectName("horizontalSliderPriority");
        horizontalSliderPriority->setGeometry(QRect(130, 10, 160, 16));
        horizontalSliderPriority->setMaximum(100);
        horizontalSliderPriority->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(EditLineDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(80, 10, 41, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxPriority = new QSpinBox(EditLineDialog);
        spinBoxPriority->setObjectName("spinBoxPriority");
        spinBoxPriority->setGeometry(QRect(340, 5, 61, 27));
        spinBoxPriority->setMaximum(100);
        groupBox = new QGroupBox(EditLineDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 40, 120, 101));
        radioButtonOK = new QRadioButton(groupBox);
        radioButtonOK->setObjectName("radioButtonOK");
        radioButtonOK->setGeometry(QRect(10, 27, 81, 31));
        radioButtonNG = new QRadioButton(groupBox);
        radioButtonNG->setObjectName("radioButtonNG");
        radioButtonNG->setGeometry(QRect(10, 57, 81, 31));
        pushButtonSave = new QPushButton(EditLineDialog);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(190, 110, 80, 31));
        pushButtonCancel = new QPushButton(EditLineDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(300, 110, 80, 31));

        retranslateUi(EditLineDialog);

        QMetaObject::connectSlotsByName(EditLineDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLineDialog)
    {
        EditLineDialog->setWindowTitle(QCoreApplication::translate("EditLineDialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("EditLineDialog", "\351\207\215\350\246\201\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("EditLineDialog", "\344\275\216\343\201\204", nullptr));
        label_4->setText(QCoreApplication::translate("EditLineDialog", "\351\253\230\343\201\204", nullptr));
        groupBox->setTitle(QCoreApplication::translate("EditLineDialog", "\345\210\244\345\256\232\346\214\257\343\202\212\345\210\206\343\201\221", nullptr));
        radioButtonOK->setText(QCoreApplication::translate("EditLineDialog", "OK", nullptr));
        radioButtonNG->setText(QCoreApplication::translate("EditLineDialog", "NG", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("EditLineDialog", "\344\277\235\345\255\230", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditLineDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLineDialog: public Ui_EditLineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLINEDIALOG_H
