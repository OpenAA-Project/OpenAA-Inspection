/********************************************************************************
** Form generated from reading UI file 'SettingParameterDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGPARAMETERDIALOG_H
#define UI_SETTINGPARAMETERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingParameterDialog
{
public:
    QFrame *frame;
    QPushButton *pushButtonOk;

    void setupUi(QDialog *SettingParameterDialog)
    {
        if (SettingParameterDialog->objectName().isEmpty())
            SettingParameterDialog->setObjectName("SettingParameterDialog");
        SettingParameterDialog->resize(673, 535);
        frame = new QFrame(SettingParameterDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 671, 491));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonOk = new QPushButton(SettingParameterDialog);
        pushButtonOk->setObjectName("pushButtonOk");
        pushButtonOk->setGeometry(QRect(240, 500, 191, 23));

        retranslateUi(SettingParameterDialog);

        QMetaObject::connectSlotsByName(SettingParameterDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingParameterDialog)
    {
        SettingParameterDialog->setWindowTitle(QCoreApplication::translate("SettingParameterDialog", "Setting Parameter", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("SettingParameterDialog", "OK & Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingParameterDialog: public Ui_SettingParameterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGPARAMETERDIALOG_H
