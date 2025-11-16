/********************************************************************************
** Form generated from reading UI file 'AutoStartParamDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSTARTPARAMDIALOG_H
#define UI_AUTOSTARTPARAMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AutoStartParamDialogClass
{
public:
    QPushButton *CancelButton;
    QPushButton *OKButton;

    void setupUi(QDialog *AutoStartParamDialogClass)
    {
        if (AutoStartParamDialogClass->objectName().isEmpty())
            AutoStartParamDialogClass->setObjectName("AutoStartParamDialogClass");
        AutoStartParamDialogClass->resize(627, 489);
        CancelButton = new QPushButton(AutoStartParamDialogClass);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(450, 440, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        CancelButton->setIcon(icon);
        OKButton = new QPushButton(AutoStartParamDialogClass);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(100, 440, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        OKButton->setIcon(icon1);
        OKButton->setAutoDefault(true);

        retranslateUi(AutoStartParamDialogClass);

        QMetaObject::connectSlotsByName(AutoStartParamDialogClass);
    } // setupUi

    void retranslateUi(QDialog *AutoStartParamDialogClass)
    {
        AutoStartParamDialogClass->setWindowTitle(QCoreApplication::translate("AutoStartParamDialogClass", "AutoStartParamDialog", nullptr));
        CancelButton->setText(QCoreApplication::translate("AutoStartParamDialogClass", "Cancel", nullptr));
        OKButton->setText(QCoreApplication::translate("AutoStartParamDialogClass", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoStartParamDialogClass: public Ui_AutoStartParamDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSTARTPARAMDIALOG_H
