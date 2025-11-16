/********************************************************************************
** Form generated from reading UI file 'InputFrameDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTFRAMEDIALOG_H
#define UI_INPUTFRAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_InputFrameDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxGroupNumber;
    QSpinBox *spinBoxFrameNumber;
    QCheckBox *checkBoxOrigin;

    void setupUi(QDialog *InputFrameDialog)
    {
        if (InputFrameDialog->objectName().isEmpty())
            InputFrameDialog->setObjectName("InputFrameDialog");
        InputFrameDialog->resize(251, 163);
        label = new QLabel(InputFrameDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(InputFrameDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 10, 91, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(InputFrameDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 110, 112, 34));
        pushButtonCancel = new QPushButton(InputFrameDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 110, 112, 34));
        spinBoxGroupNumber = new QSpinBox(InputFrameDialog);
        spinBoxGroupNumber->setObjectName("spinBoxGroupNumber");
        spinBoxGroupNumber->setGeometry(QRect(20, 30, 91, 24));
        spinBoxFrameNumber = new QSpinBox(InputFrameDialog);
        spinBoxFrameNumber->setObjectName("spinBoxFrameNumber");
        spinBoxFrameNumber->setGeometry(QRect(130, 30, 91, 24));
        checkBoxOrigin = new QCheckBox(InputFrameDialog);
        checkBoxOrigin->setObjectName("checkBoxOrigin");
        checkBoxOrigin->setGeometry(QRect(130, 70, 111, 22));

        retranslateUi(InputFrameDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputFrameDialog);
    } // setupUi

    void retranslateUi(QDialog *InputFrameDialog)
    {
        InputFrameDialog->setWindowTitle(QCoreApplication::translate("InputFrameDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("InputFrameDialog", "Group No", nullptr));
        label_2->setText(QCoreApplication::translate("InputFrameDialog", "Frame No", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputFrameDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputFrameDialog", "Cancel", nullptr));
        checkBoxOrigin->setText(QCoreApplication::translate("InputFrameDialog", "Origin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputFrameDialog: public Ui_InputFrameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTFRAMEDIALOG_H
