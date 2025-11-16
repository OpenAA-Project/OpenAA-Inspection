/********************************************************************************
** Form generated from reading UI file 'CreateManualLightDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMANUALLIGHTDIALOG_H
#define UI_CREATEMANUALLIGHTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CreateManualLightDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxBrightnessLow;
    QSpinBox *spinBoxBrightnessHigh;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label_3;
    QLineEdit *lineEditItemName;

    void setupUi(QDialog *CreateManualLightDialog)
    {
        if (CreateManualLightDialog->objectName().isEmpty())
            CreateManualLightDialog->setObjectName("CreateManualLightDialog");
        CreateManualLightDialog->resize(249, 173);
        label = new QLabel(CreateManualLightDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 111, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(CreateManualLightDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 60, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxBrightnessLow = new QSpinBox(CreateManualLightDialog);
        spinBoxBrightnessLow->setObjectName("spinBoxBrightnessLow");
        spinBoxBrightnessLow->setGeometry(QRect(10, 80, 81, 22));
        spinBoxBrightnessLow->setMaximum(255);
        spinBoxBrightnessHigh = new QSpinBox(CreateManualLightDialog);
        spinBoxBrightnessHigh->setObjectName("spinBoxBrightnessHigh");
        spinBoxBrightnessHigh->setGeometry(QRect(130, 80, 81, 22));
        spinBoxBrightnessHigh->setMaximum(255);
        pushButtonOK = new QPushButton(CreateManualLightDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 120, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(CreateManualLightDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 120, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label_3 = new QLabel(CreateManualLightDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 231, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        lineEditItemName = new QLineEdit(CreateManualLightDialog);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(10, 30, 231, 21));

        retranslateUi(CreateManualLightDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(CreateManualLightDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateManualLightDialog)
    {
        CreateManualLightDialog->setWindowTitle(QCoreApplication::translate("CreateManualLightDialog", "Create Manual Light", nullptr));
        label->setText(QCoreApplication::translate("CreateManualLightDialog", "Brightness Low", nullptr));
        label_2->setText(QCoreApplication::translate("CreateManualLightDialog", "Brightness High", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CreateManualLightDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateManualLightDialog", "Cancel", nullptr));
        label_3->setText(QCoreApplication::translate("CreateManualLightDialog", "Item name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateManualLightDialog: public Ui_CreateManualLightDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMANUALLIGHTDIALOG_H
