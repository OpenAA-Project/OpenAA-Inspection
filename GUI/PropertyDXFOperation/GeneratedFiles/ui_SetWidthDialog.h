/********************************************************************************
** Form generated from reading UI file 'SetWidthDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETWIDTHDIALOG_H
#define UI_SETWIDTHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SetWidthDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxLineWidth;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SetWidthDialog)
    {
        if (SetWidthDialog->objectName().isEmpty())
            SetWidthDialog->setObjectName("SetWidthDialog");
        SetWidthDialog->resize(232, 116);
        label = new QLabel(SetWidthDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 75, 21));
        spinBoxLineWidth = new QSpinBox(SetWidthDialog);
        spinBoxLineWidth->setObjectName("spinBoxLineWidth");
        spinBoxLineWidth->setGeometry(QRect(110, 20, 81, 24));
        spinBoxLineWidth->setMaximum(99999999);
        pushButtonCancel = new QPushButton(SetWidthDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 60, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonOK = new QPushButton(SetWidthDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 60, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(SetWidthDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SetWidthDialog);
    } // setupUi

    void retranslateUi(QDialog *SetWidthDialog)
    {
        SetWidthDialog->setWindowTitle(QCoreApplication::translate("SetWidthDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SetWidthDialog", "\347\267\232\345\271\205", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetWidthDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetWidthDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetWidthDialog: public Ui_SetWidthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETWIDTHDIALOG_H
