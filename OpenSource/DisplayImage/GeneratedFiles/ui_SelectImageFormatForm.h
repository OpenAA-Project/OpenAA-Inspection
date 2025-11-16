/********************************************************************************
** Form generated from reading UI file 'SelectImageFormatForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTIMAGEFORMATFORM_H
#define UI_SELECTIMAGEFORMATFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectImageFormatForm
{
public:
    QComboBox *comboBoxFormat;
    QLabel *label_6;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SelectImageFormatForm)
    {
        if (SelectImageFormatForm->objectName().isEmpty())
            SelectImageFormatForm->setObjectName("SelectImageFormatForm");
        SelectImageFormatForm->resize(299, 127);
        comboBoxFormat = new QComboBox(SelectImageFormatForm);
        comboBoxFormat->addItem(QString());
        comboBoxFormat->addItem(QString());
        comboBoxFormat->addItem(QString());
        comboBoxFormat->setObjectName("comboBoxFormat");
        comboBoxFormat->setGeometry(QRect(80, 30, 121, 22));
        label_6 = new QLabel(SelectImageFormatForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(70, 10, 121, 16));
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(SelectImageFormatForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(180, 70, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonOK = new QPushButton(SelectImageFormatForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 70, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(SelectImageFormatForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectImageFormatForm);
    } // setupUi

    void retranslateUi(QDialog *SelectImageFormatForm)
    {
        SelectImageFormatForm->setWindowTitle(QCoreApplication::translate("SelectImageFormatForm", "Dialog", nullptr));
        comboBoxFormat->setItemText(0, QCoreApplication::translate("SelectImageFormatForm", "Bitmap(Bmp)", nullptr));
        comboBoxFormat->setItemText(1, QCoreApplication::translate("SelectImageFormatForm", "JPEG(Jpg)", nullptr));
        comboBoxFormat->setItemText(2, QCoreApplication::translate("SelectImageFormatForm", "PNG(Png)", nullptr));

        label_6->setText(QCoreApplication::translate("SelectImageFormatForm", "\344\277\235\345\255\230\347\250\256\351\241\236", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectImageFormatForm", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectImageFormatForm", "\350\250\255\345\256\232\343\203\273\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectImageFormatForm: public Ui_SelectImageFormatForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTIMAGEFORMATFORM_H
