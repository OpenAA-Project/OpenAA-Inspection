/********************************************************************************
** Form generated from reading UI file 'SetStatisticThresholdDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSTATISTICTHRESHOLDDIALOG_H
#define UI_SETSTATISTICTHRESHOLDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetStatisticThresholdDialog
{
public:
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxSigmaH;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxSigmaS;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxSigmaV;
    QPushButton *pushButtonSet;
    QLabel *label_4;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonPanelH;
    QPushButton *pushButtonPanelS;
    QPushButton *pushButtonPanelV;

    void setupUi(QDialog *SetStatisticThresholdDialog)
    {
        if (SetStatisticThresholdDialog->objectName().isEmpty())
            SetStatisticThresholdDialog->setObjectName("SetStatisticThresholdDialog");
        SetStatisticThresholdDialog->resize(350, 326);
        label = new QLabel(SetStatisticThresholdDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 110, 36));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        doubleSpinBoxSigmaH = new QDoubleSpinBox(SetStatisticThresholdDialog);
        doubleSpinBoxSigmaH->setObjectName("doubleSpinBoxSigmaH");
        doubleSpinBoxSigmaH->setGeometry(QRect(150, 10, 120, 36));
        doubleSpinBoxSigmaH->setFont(font);
        doubleSpinBoxSigmaH->setDecimals(4);
        doubleSpinBoxSigmaH->setValue(3.000000000000000);
        label_2 = new QLabel(SetStatisticThresholdDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 110, 36));
        label_2->setFont(font);
        doubleSpinBoxSigmaS = new QDoubleSpinBox(SetStatisticThresholdDialog);
        doubleSpinBoxSigmaS->setObjectName("doubleSpinBoxSigmaS");
        doubleSpinBoxSigmaS->setGeometry(QRect(150, 50, 120, 36));
        doubleSpinBoxSigmaS->setFont(font);
        doubleSpinBoxSigmaS->setDecimals(4);
        doubleSpinBoxSigmaS->setValue(3.000000000000000);
        label_3 = new QLabel(SetStatisticThresholdDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 90, 110, 36));
        label_3->setFont(font);
        doubleSpinBoxSigmaV = new QDoubleSpinBox(SetStatisticThresholdDialog);
        doubleSpinBoxSigmaV->setObjectName("doubleSpinBoxSigmaV");
        doubleSpinBoxSigmaV->setGeometry(QRect(150, 90, 120, 36));
        doubleSpinBoxSigmaV->setFont(font);
        doubleSpinBoxSigmaV->setDecimals(4);
        doubleSpinBoxSigmaV->setValue(3.000000000000000);
        pushButtonSet = new QPushButton(SetStatisticThresholdDialog);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(20, 240, 141, 61));
        QFont font1;
        font1.setPointSize(16);
        pushButtonSet->setFont(font1);
        pushButtonSet->setAutoFillBackground(false);
        pushButtonSet->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(230, 254, 230, 255), stop:1 rgba(130, 165, 130, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 225, 0, 255), stop:1 rgba(0, 141, 0, 255));\n"
"}"));
        label_4 = new QLabel(SetStatisticThresholdDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 140, 321, 81));
        QFont font2;
        font2.setPointSize(12);
        label_4->setFont(font2);
        label_4->setWordWrap(true);
        pushButtonCancel = new QPushButton(SetStatisticThresholdDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(190, 240, 131, 61));
        pushButtonCancel->setFont(font1);
        pushButtonCancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 230, 230, 255), stop:1 rgba(165, 130, 130, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonPanelH = new QPushButton(SetStatisticThresholdDialog);
        pushButtonPanelH->setObjectName("pushButtonPanelH");
        pushButtonPanelH->setGeometry(QRect(280, 10, 51, 36));
        pushButtonPanelS = new QPushButton(SetStatisticThresholdDialog);
        pushButtonPanelS->setObjectName("pushButtonPanelS");
        pushButtonPanelS->setGeometry(QRect(280, 50, 51, 36));
        pushButtonPanelV = new QPushButton(SetStatisticThresholdDialog);
        pushButtonPanelV->setObjectName("pushButtonPanelV");
        pushButtonPanelV->setGeometry(QRect(280, 90, 51, 36));

        retranslateUi(SetStatisticThresholdDialog);

        pushButtonSet->setDefault(true);


        QMetaObject::connectSlotsByName(SetStatisticThresholdDialog);
    } // setupUi

    void retranslateUi(QDialog *SetStatisticThresholdDialog)
    {
        SetStatisticThresholdDialog->setWindowTitle(QCoreApplication::translate("SetStatisticThresholdDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "H-\343\202\267\343\202\260\343\203\236", nullptr));
        label_2->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "S-\343\202\267\343\202\260\343\203\236", nullptr));
        label_3->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "V-\343\202\267\343\202\260\343\203\236", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "\350\250\255\345\256\232", nullptr));
        label_4->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "Item\351\240\230\345\237\237\343\201\256\343\201\227\343\201\215\343\201\204\345\200\244\343\202\222\346\265\201\345\213\225\347\231\273\351\214\262\343\203\207\343\203\274\343\202\277\343\201\256\347\265\261\350\250\210\345\200\244\343\201\247\350\207\252\345\213\225\350\250\255\345\256\232\343\201\227\343\201\276\343\201\231", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "Cancel", nullptr));
        pushButtonPanelH->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "...", nullptr));
        pushButtonPanelS->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "...", nullptr));
        pushButtonPanelV->setText(QCoreApplication::translate("SetStatisticThresholdDialog", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetStatisticThresholdDialog: public Ui_SetStatisticThresholdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSTATISTICTHRESHOLDDIALOG_H
