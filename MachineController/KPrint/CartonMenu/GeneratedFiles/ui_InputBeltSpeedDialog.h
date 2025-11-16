/********************************************************************************
** Form generated from reading UI file 'InputBeltSpeedDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTBELTSPEEDDIALOG_H
#define UI_INPUTBELTSPEEDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_InputBeltSpeedDialog
{
public:
    QFrame *frameTop;
    QLabel *labelTop;
    QSpinBox *spinBoxBeltVelocity;
    QPushButton *pushButtonInputPanelVelocity;
    QPushButton *PushButtonOK;
    QLabel *labelTimeout;
    QLabel *labelTop_2;

    void setupUi(QDialog *InputBeltSpeedDialog)
    {
        if (InputBeltSpeedDialog->objectName().isEmpty())
            InputBeltSpeedDialog->setObjectName("InputBeltSpeedDialog");
        InputBeltSpeedDialog->resize(347, 269);
        frameTop = new QFrame(InputBeltSpeedDialog);
        frameTop->setObjectName("frameTop");
        frameTop->setGeometry(QRect(10, 10, 321, 121));
        frameTop->setFrameShape(QFrame::Panel);
        frameTop->setFrameShadow(QFrame::Sunken);
        labelTop = new QLabel(frameTop);
        labelTop->setObjectName("labelTop");
        labelTop->setGeometry(QRect(30, 10, 261, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        labelTop->setFont(font);
        spinBoxBeltVelocity = new QSpinBox(frameTop);
        spinBoxBeltVelocity->setObjectName("spinBoxBeltVelocity");
        spinBoxBeltVelocity->setGeometry(QRect(20, 60, 151, 51));
        QFont font1;
        font1.setPointSize(16);
        spinBoxBeltVelocity->setFont(font1);
        spinBoxBeltVelocity->setMaximum(300);
        pushButtonInputPanelVelocity = new QPushButton(frameTop);
        pushButtonInputPanelVelocity->setObjectName("pushButtonInputPanelVelocity");
        pushButtonInputPanelVelocity->setGeometry(QRect(190, 60, 61, 51));
        PushButtonOK = new QPushButton(InputBeltSpeedDialog);
        PushButtonOK->setObjectName("PushButtonOK");
        PushButtonOK->setGeometry(QRect(70, 190, 201, 61));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font2.setPointSize(24);
        PushButtonOK->setFont(font2);
        PushButtonOK->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonOK->setCheckable(true);
        PushButtonOK->setAutoExclusive(true);
        PushButtonOK->setAutoDefault(false);
        PushButtonOK->setFlat(false);
        labelTimeout = new QLabel(InputBeltSpeedDialog);
        labelTimeout->setObjectName("labelTimeout");
        labelTimeout->setGeometry(QRect(200, 140, 111, 31));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        labelTimeout->setFont(font3);
        labelTop_2 = new QLabel(InputBeltSpeedDialog);
        labelTop_2->setObjectName("labelTop_2");
        labelTop_2->setGeometry(QRect(40, 140, 151, 31));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        labelTop_2->setFont(font4);

        retranslateUi(InputBeltSpeedDialog);

        PushButtonOK->setDefault(false);


        QMetaObject::connectSlotsByName(InputBeltSpeedDialog);
    } // setupUi

    void retranslateUi(QDialog *InputBeltSpeedDialog)
    {
        InputBeltSpeedDialog->setWindowTitle(QCoreApplication::translate("InputBeltSpeedDialog", "\343\203\231\343\203\253\343\203\210\351\200\237\345\272\246\345\205\245\345\212\233", nullptr));
        labelTop->setText(QCoreApplication::translate("InputBeltSpeedDialog", "\343\203\231\343\203\253\343\203\210\351\200\237\345\272\246\357\274\210m/\345\210\206)", nullptr));
        pushButtonInputPanelVelocity->setText(QCoreApplication::translate("InputBeltSpeedDialog", "...", nullptr));
        PushButtonOK->setText(QCoreApplication::translate("InputBeltSpeedDialog", "\350\250\255\345\256\232", nullptr));
        labelTimeout->setText(QCoreApplication::translate("InputBeltSpeedDialog", "xxx ms", nullptr));
        labelTop_2->setText(QCoreApplication::translate("InputBeltSpeedDialog", "\343\202\277\343\202\244\343\203\240\343\202\242\343\202\246\343\203\210\345\200\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputBeltSpeedDialog: public Ui_InputBeltSpeedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTBELTSPEEDDIALOG_H
