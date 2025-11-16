/********************************************************************************
** Form generated from reading UI file 'InputFloatDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTFLOATDIALOG_H
#define UI_INPUTFLOATDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputFloatDialog
{
public:
    QPushButton *pushButtonOK;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputFloatDialog)
    {
        if (InputFloatDialog->objectName().isEmpty())
            InputFloatDialog->setObjectName("InputFloatDialog");
        InputFloatDialog->resize(217, 81);
        pushButtonOK = new QPushButton(InputFloatDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 40, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        doubleSpinBox = new QDoubleSpinBox(InputFloatDialog);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(21, 10, 151, 22));
        doubleSpinBox->setDecimals(4);
        doubleSpinBox->setMinimum(-99999999.999899998307228);
        doubleSpinBox->setMaximum(99999999.999899998307228);
        pushButtonCancel = new QPushButton(InputFloatDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 40, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(InputFloatDialog);

        QMetaObject::connectSlotsByName(InputFloatDialog);
    } // setupUi

    void retranslateUi(QDialog *InputFloatDialog)
    {
        InputFloatDialog->setWindowTitle(QCoreApplication::translate("InputFloatDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputFloatDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputFloatDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputFloatDialog: public Ui_InputFloatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTFLOATDIALOG_H
