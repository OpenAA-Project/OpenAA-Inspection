/********************************************************************************
** Form generated from reading UI file 'PIOBitSettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIOBITSETTINGDIALOG_H
#define UI_PIOBITSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_PIOBitSettingDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxBoardNumber;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QSpinBox *spinBoxPortNumber;
    QLabel *label_3;
    QComboBox *comboBoxBitNumber;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *PIOBitSettingDialog)
    {
        if (PIOBitSettingDialog->objectName().isEmpty())
            PIOBitSettingDialog->setObjectName(QString::fromUtf8("PIOBitSettingDialog"));
        PIOBitSettingDialog->resize(251, 181);
        label = new QLabel(PIOBitSettingDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 231, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxBoardNumber = new QSpinBox(PIOBitSettingDialog);
        spinBoxBoardNumber->setObjectName(QString::fromUtf8("spinBoxBoardNumber"));
        spinBoxBoardNumber->setGeometry(QRect(10, 30, 46, 22));
        lineEdit = new QLineEdit(PIOBitSettingDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(60, 30, 181, 20));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lineEdit->setPalette(palette);
        lineEdit->setReadOnly(true);
        label_2 = new QLabel(PIOBitSettingDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 111, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxPortNumber = new QSpinBox(PIOBitSettingDialog);
        spinBoxPortNumber->setObjectName(QString::fromUtf8("spinBoxPortNumber"));
        spinBoxPortNumber->setGeometry(QRect(10, 90, 46, 22));
        label_3 = new QLabel(PIOBitSettingDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 70, 111, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        comboBoxBitNumber = new QComboBox(PIOBitSettingDialog);
        comboBoxBitNumber->addItem(QString());
        comboBoxBitNumber->addItem(QString());
        comboBoxBitNumber->addItem(QString());
        comboBoxBitNumber->addItem(QString());
        comboBoxBitNumber->addItem(QString());
        comboBoxBitNumber->addItem(QString());
        comboBoxBitNumber->addItem(QString());
        comboBoxBitNumber->addItem(QString());
        comboBoxBitNumber->setObjectName(QString::fromUtf8("comboBoxBitNumber"));
        comboBoxBitNumber->setGeometry(QRect(130, 90, 74, 22));
        pushButtonOK = new QPushButton(PIOBitSettingDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(10, 130, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(PIOBitSettingDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(130, 130, 111, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(PIOBitSettingDialog);

        QMetaObject::connectSlotsByName(PIOBitSettingDialog);
    } // setupUi

    void retranslateUi(QDialog *PIOBitSettingDialog)
    {
        PIOBitSettingDialog->setWindowTitle(QCoreApplication::translate("PIOBitSettingDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("PIOBitSettingDialog", "Board Number", nullptr));
        label_2->setText(QCoreApplication::translate("PIOBitSettingDialog", "Port Number", nullptr));
        label_3->setText(QCoreApplication::translate("PIOBitSettingDialog", "Bit Number", nullptr));
        comboBoxBitNumber->setItemText(0, QCoreApplication::translate("PIOBitSettingDialog", "Bit 0", nullptr));
        comboBoxBitNumber->setItemText(1, QCoreApplication::translate("PIOBitSettingDialog", "Bit 1", nullptr));
        comboBoxBitNumber->setItemText(2, QCoreApplication::translate("PIOBitSettingDialog", "Bit 2", nullptr));
        comboBoxBitNumber->setItemText(3, QCoreApplication::translate("PIOBitSettingDialog", "Bit 3", nullptr));
        comboBoxBitNumber->setItemText(4, QCoreApplication::translate("PIOBitSettingDialog", "Bit 4", nullptr));
        comboBoxBitNumber->setItemText(5, QCoreApplication::translate("PIOBitSettingDialog", "Bit 5", nullptr));
        comboBoxBitNumber->setItemText(6, QCoreApplication::translate("PIOBitSettingDialog", "Bit 6", nullptr));
        comboBoxBitNumber->setItemText(7, QCoreApplication::translate("PIOBitSettingDialog", "Bit 7", nullptr));

        pushButtonOK->setText(QCoreApplication::translate("PIOBitSettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("PIOBitSettingDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PIOBitSettingDialog: public Ui_PIOBitSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIOBITSETTINGDIALOG_H
