/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QFrame *frame;
    QDoubleSpinBox *doubleSpinBoxInclineL;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxStrengthL;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxWidthL;
    QDoubleSpinBox *doubleSpinBoxAddVL;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBoxAddBL;
    QFrame *frame_2;
    QDoubleSpinBox *doubleSpinBoxInclineR;
    QDoubleSpinBox *doubleSpinBoxStrengthR;
    QDoubleSpinBox *doubleSpinBoxWidthR;
    QDoubleSpinBox *doubleSpinBoxAddVR;
    QDoubleSpinBox *doubleSpinBoxAddBR;
    QLabel *label_12;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(400, 409);
        frame = new QFrame(SettingDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 30, 181, 311));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        doubleSpinBoxInclineL = new QDoubleSpinBox(frame);
        doubleSpinBoxInclineL->setObjectName("doubleSpinBoxInclineL");
        doubleSpinBoxInclineL->setGeometry(QRect(10, 30, 141, 22));
        doubleSpinBoxInclineL->setDecimals(10);
        doubleSpinBoxInclineL->setMinimum(-1000.000000000000000);
        doubleSpinBoxInclineL->setMaximum(1000.000000000000000);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 161, 16));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 70, 161, 16));
        doubleSpinBoxStrengthL = new QDoubleSpinBox(frame);
        doubleSpinBoxStrengthL->setObjectName("doubleSpinBoxStrengthL");
        doubleSpinBoxStrengthL->setGeometry(QRect(10, 150, 141, 22));
        doubleSpinBoxStrengthL->setDecimals(4);
        doubleSpinBoxStrengthL->setMinimum(-1000.000000000000000);
        doubleSpinBoxStrengthL->setMaximum(1000.000000000000000);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 130, 161, 16));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 190, 161, 16));
        doubleSpinBoxWidthL = new QDoubleSpinBox(frame);
        doubleSpinBoxWidthL->setObjectName("doubleSpinBoxWidthL");
        doubleSpinBoxWidthL->setGeometry(QRect(10, 210, 141, 22));
        doubleSpinBoxWidthL->setDecimals(4);
        doubleSpinBoxAddVL = new QDoubleSpinBox(frame);
        doubleSpinBoxAddVL->setObjectName("doubleSpinBoxAddVL");
        doubleSpinBoxAddVL->setGeometry(QRect(10, 90, 141, 22));
        doubleSpinBoxAddVL->setDecimals(10);
        doubleSpinBoxAddVL->setMinimum(-1000.000000000000000);
        doubleSpinBoxAddVL->setMaximum(1000.000000000000000);
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 250, 161, 16));
        doubleSpinBoxAddBL = new QDoubleSpinBox(frame);
        doubleSpinBoxAddBL->setObjectName("doubleSpinBoxAddBL");
        doubleSpinBoxAddBL->setGeometry(QRect(10, 270, 141, 22));
        doubleSpinBoxAddBL->setDecimals(4);
        doubleSpinBoxAddBL->setMinimum(-1000.000000000000000);
        doubleSpinBoxAddBL->setMaximum(1000.000000000000000);
        frame_2 = new QFrame(SettingDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(200, 30, 181, 311));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        doubleSpinBoxInclineR = new QDoubleSpinBox(frame_2);
        doubleSpinBoxInclineR->setObjectName("doubleSpinBoxInclineR");
        doubleSpinBoxInclineR->setGeometry(QRect(10, 30, 141, 22));
        doubleSpinBoxInclineR->setDecimals(10);
        doubleSpinBoxInclineR->setMinimum(-1000.000000000000000);
        doubleSpinBoxInclineR->setMaximum(1000.000000000000000);
        doubleSpinBoxStrengthR = new QDoubleSpinBox(frame_2);
        doubleSpinBoxStrengthR->setObjectName("doubleSpinBoxStrengthR");
        doubleSpinBoxStrengthR->setGeometry(QRect(10, 150, 141, 22));
        doubleSpinBoxStrengthR->setDecimals(4);
        doubleSpinBoxStrengthR->setMinimum(-1000.000000000000000);
        doubleSpinBoxStrengthR->setMaximum(1000.000000000000000);
        doubleSpinBoxWidthR = new QDoubleSpinBox(frame_2);
        doubleSpinBoxWidthR->setObjectName("doubleSpinBoxWidthR");
        doubleSpinBoxWidthR->setGeometry(QRect(10, 210, 141, 22));
        doubleSpinBoxWidthR->setDecimals(4);
        doubleSpinBoxAddVR = new QDoubleSpinBox(frame_2);
        doubleSpinBoxAddVR->setObjectName("doubleSpinBoxAddVR");
        doubleSpinBoxAddVR->setGeometry(QRect(10, 90, 141, 22));
        doubleSpinBoxAddVR->setDecimals(10);
        doubleSpinBoxAddVR->setMinimum(-1000.000000000000000);
        doubleSpinBoxAddVR->setMaximum(1000.000000000000000);
        doubleSpinBoxAddBR = new QDoubleSpinBox(frame_2);
        doubleSpinBoxAddBR->setObjectName("doubleSpinBoxAddBR");
        doubleSpinBoxAddBR->setGeometry(QRect(10, 270, 141, 22));
        doubleSpinBoxAddBR->setDecimals(4);
        doubleSpinBoxAddBR->setMinimum(-1000.000000000000000);
        doubleSpinBoxAddBR->setMaximum(1000.000000000000000);
        label_12 = new QLabel(frame_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 250, 161, 16));
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 70, 161, 16));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 190, 161, 16));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 130, 161, 16));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 10, 161, 16));
        label_9 = new QLabel(SettingDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 10, 161, 16));
        label_10 = new QLabel(SettingDialog);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(200, 10, 161, 16));
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(60, 360, 101, 41));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(230, 360, 101, 41));

        retranslateUi(SettingDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "A \345\202\276\343\201\215\357\274\210\350\274\235\345\272\246\345\244\211\345\214\226\345\200\244\357\274\217\343\203\224\343\202\257\343\202\273\343\203\253\357\274\211", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "B \350\274\235\345\272\246\344\277\202\346\225\260\343\201\256\345\233\272\345\256\232\343\202\252\343\203\225\343\202\273\343\203\203\343\203\210", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "C \350\274\235\345\272\246\345\233\272\345\256\232\344\277\202\346\225\260", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "D \350\274\235\345\272\246\351\200\206Cosine\344\277\202\346\225\260", nullptr));
        label_11->setText(QCoreApplication::translate("SettingDialog", "E \350\274\235\345\272\246\345\212\240\347\256\227\345\200\244", nullptr));
        label_12->setText(QCoreApplication::translate("SettingDialog", "E \350\274\235\345\272\246\345\212\240\347\256\227\345\200\244", nullptr));
        label_5->setText(QCoreApplication::translate("SettingDialog", "B \350\274\235\345\272\246\344\277\202\346\225\260\343\201\256\345\233\272\345\256\232\343\202\252\343\203\225\343\202\273\343\203\203\343\203\210", nullptr));
        label_6->setText(QCoreApplication::translate("SettingDialog", "D \350\274\235\345\272\246\351\200\206Cosine\344\277\202\346\225\260", nullptr));
        label_7->setText(QCoreApplication::translate("SettingDialog", "C \350\274\235\345\272\246\345\233\272\345\256\232\344\277\202\346\225\260", nullptr));
        label_8->setText(QCoreApplication::translate("SettingDialog", "A \345\202\276\343\201\215\357\274\210\350\274\235\345\272\246\345\244\211\345\214\226\345\200\244\357\274\217\343\203\224\343\202\257\343\202\273\343\203\253\357\274\211", nullptr));
        label_9->setText(QCoreApplication::translate("SettingDialog", "\345\267\246\345\201\264", nullptr));
        label_10->setText(QCoreApplication::translate("SettingDialog", "\345\217\263\345\201\264", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
