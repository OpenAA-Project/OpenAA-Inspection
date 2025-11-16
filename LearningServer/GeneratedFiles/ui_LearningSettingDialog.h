/********************************************************************************
** Form generated from reading UI file 'LearningSettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEARNINGSETTINGDIALOG_H
#define UI_LEARNINGSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LearningSettingDialogClass
{
public:
    QPushButton *ButtonCancel;
    QPushButton *ButtonOK;
    QFrame *frame;

    void setupUi(QDialog *LearningSettingDialogClass)
    {
        if (LearningSettingDialogClass->objectName().isEmpty())
            LearningSettingDialogClass->setObjectName("LearningSettingDialogClass");
        LearningSettingDialogClass->resize(697, 483);
        ButtonCancel = new QPushButton(LearningSettingDialogClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(490, 420, 131, 41));
        ButtonOK = new QPushButton(LearningSettingDialogClass);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(80, 420, 131, 41));
        frame = new QFrame(LearningSettingDialogClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 20, 661, 371));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(LearningSettingDialogClass);

        QMetaObject::connectSlotsByName(LearningSettingDialogClass);
    } // setupUi

    void retranslateUi(QDialog *LearningSettingDialogClass)
    {
        LearningSettingDialogClass->setWindowTitle(QCoreApplication::translate("LearningSettingDialogClass", "LearningSettingDialog", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("LearningSettingDialogClass", "Cancel", nullptr));
        ButtonOK->setText(QCoreApplication::translate("LearningSettingDialogClass", "OK  Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearningSettingDialogClass: public Ui_LearningSettingDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNINGSETTINGDIALOG_H
