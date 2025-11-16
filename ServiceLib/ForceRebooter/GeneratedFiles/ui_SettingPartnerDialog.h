/********************************************************************************
** Form generated from reading UI file 'SettingPartnerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGPARTNERDIALOG_H
#define UI_SETTINGPARTNERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingPartnerDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditHostIP;
    QLabel *label_2;
    QSpinBox *spinBoxPortNumber;
    QLabel *label_3;
    QLineEdit *lineEditRemark;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SettingPartnerDialog)
    {
        if (SettingPartnerDialog->objectName().isEmpty())
            SettingPartnerDialog->setObjectName("SettingPartnerDialog");
        SettingPartnerDialog->resize(269, 229);
        label = new QLabel(SettingPartnerDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 251, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditHostIP = new QLineEdit(SettingPartnerDialog);
        lineEditHostIP->setObjectName("lineEditHostIP");
        lineEditHostIP->setGeometry(QRect(10, 30, 251, 20));
        label_2 = new QLabel(SettingPartnerDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 251, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxPortNumber = new QSpinBox(SettingPartnerDialog);
        spinBoxPortNumber->setObjectName("spinBoxPortNumber");
        spinBoxPortNumber->setGeometry(QRect(10, 80, 101, 22));
        spinBoxPortNumber->setMaximum(65535);
        label_3 = new QLabel(SettingPartnerDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 251, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        lineEditRemark = new QLineEdit(SettingPartnerDialog);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(10, 130, 251, 20));
        pushButtonCancel = new QPushButton(SettingPartnerDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(150, 170, 111, 41));
        pushButtonOK = new QPushButton(SettingPartnerDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 170, 111, 41));

        retranslateUi(SettingPartnerDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingPartnerDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingPartnerDialog)
    {
        SettingPartnerDialog->setWindowTitle(QCoreApplication::translate("SettingPartnerDialog", "Setting Partner", nullptr));
        label->setText(QCoreApplication::translate("SettingPartnerDialog", "Host/IP", nullptr));
        label_2->setText(QCoreApplication::translate("SettingPartnerDialog", "Port number", nullptr));
        label_3->setText(QCoreApplication::translate("SettingPartnerDialog", "Remark", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingPartnerDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingPartnerDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingPartnerDialog: public Ui_SettingPartnerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGPARTNERDIALOG_H
