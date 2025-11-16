/********************************************************************************
** Form generated from reading UI file 'SetLanguageDetailForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETLANGUAGEDETAILFORM_H
#define UI_SETLANGUAGEDETAILFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SetLanguageDetailForm
{
public:
    QSpinBox *spinBoxColumnNo;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBoxLanguage;
    QLabel *label_3;
    QComboBox *comboBoxExcelFont;
    QLabel *label_4;
    QComboBox *comboBoxQtCodec;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SetLanguageDetailForm)
    {
        if (SetLanguageDetailForm->objectName().isEmpty())
            SetLanguageDetailForm->setObjectName("SetLanguageDetailForm");
        SetLanguageDetailForm->resize(275, 300);
        spinBoxColumnNo = new QSpinBox(SetLanguageDetailForm);
        spinBoxColumnNo->setObjectName("spinBoxColumnNo");
        spinBoxColumnNo->setGeometry(QRect(30, 30, 61, 22));
        spinBoxColumnNo->setMaximum(9999);
        label = new QLabel(SetLanguageDetailForm);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 61, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(SetLanguageDetailForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 70, 211, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        comboBoxLanguage = new QComboBox(SetLanguageDetailForm);
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->setObjectName("comboBoxLanguage");
        comboBoxLanguage->setGeometry(QRect(30, 90, 211, 22));
        comboBoxLanguage->setEditable(true);
        label_3 = new QLabel(SetLanguageDetailForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 130, 211, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        comboBoxExcelFont = new QComboBox(SetLanguageDetailForm);
        comboBoxExcelFont->addItem(QString());
        comboBoxExcelFont->addItem(QString());
        comboBoxExcelFont->addItem(QString());
        comboBoxExcelFont->addItem(QString());
        comboBoxExcelFont->addItem(QString());
        comboBoxExcelFont->setObjectName("comboBoxExcelFont");
        comboBoxExcelFont->setGeometry(QRect(30, 150, 211, 22));
        comboBoxExcelFont->setEditable(true);
        label_4 = new QLabel(SetLanguageDetailForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 190, 211, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        comboBoxQtCodec = new QComboBox(SetLanguageDetailForm);
        comboBoxQtCodec->setObjectName("comboBoxQtCodec");
        comboBoxQtCodec->setGeometry(QRect(30, 210, 211, 22));
        comboBoxQtCodec->setEditable(true);
        pushButtonOK = new QPushButton(SetLanguageDetailForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 250, 91, 31));
        pushButtonCancel = new QPushButton(SetLanguageDetailForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(150, 250, 91, 31));

        retranslateUi(SetLanguageDetailForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SetLanguageDetailForm);
    } // setupUi

    void retranslateUi(QDialog *SetLanguageDetailForm)
    {
        SetLanguageDetailForm->setWindowTitle(QCoreApplication::translate("SetLanguageDetailForm", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SetLanguageDetailForm", "Column No", nullptr));
        label_2->setText(QCoreApplication::translate("SetLanguageDetailForm", "Language", nullptr));
        comboBoxLanguage->setItemText(0, QCoreApplication::translate("SetLanguageDetailForm", "Japanese", nullptr));
        comboBoxLanguage->setItemText(1, QCoreApplication::translate("SetLanguageDetailForm", "English", nullptr));
        comboBoxLanguage->setItemText(2, QCoreApplication::translate("SetLanguageDetailForm", "Chinese(Taiwan)", nullptr));
        comboBoxLanguage->setItemText(3, QCoreApplication::translate("SetLanguageDetailForm", "Chinese(China)", nullptr));
        comboBoxLanguage->setItemText(4, QCoreApplication::translate("SetLanguageDetailForm", "Korean", nullptr));

        label_3->setText(QCoreApplication::translate("SetLanguageDetailForm", "EXCEL Font", nullptr));
        comboBoxExcelFont->setItemText(0, QCoreApplication::translate("SetLanguageDetailForm", "\357\274\255\357\274\263 \357\274\260\343\202\264\343\202\267\343\203\203\343\202\257", nullptr));
        comboBoxExcelFont->setItemText(1, QCoreApplication::translate("SetLanguageDetailForm", "Arial", nullptr));
        comboBoxExcelFont->setItemText(2, QCoreApplication::translate("SetLanguageDetailForm", "SimSun", nullptr));
        comboBoxExcelFont->setItemText(3, QCoreApplication::translate("SetLanguageDetailForm", "MingLiU", nullptr));
        comboBoxExcelFont->setItemText(4, QCoreApplication::translate("SetLanguageDetailForm", "Gulim", nullptr));

        label_4->setText(QCoreApplication::translate("SetLanguageDetailForm", "Qt Codec", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetLanguageDetailForm", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetLanguageDetailForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetLanguageDetailForm: public Ui_SetLanguageDetailForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETLANGUAGEDETAILFORM_H
