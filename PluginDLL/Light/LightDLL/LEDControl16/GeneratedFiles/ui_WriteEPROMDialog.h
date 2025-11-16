/********************************************************************************
** Form generated from reading UI file 'WriteEPROMDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRITEEPROMDIALOG_H
#define UI_WRITEEPROMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_WriteEPROMDialog
{
public:
    QFrame *frame;
    QLabel *label_3;
    QComboBox *comboBoxSelectPort;
    QComboBox *comboBoxSelectBoard;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame_2;
    QLabel *label_4;
    QLabel *label_7;
    QSpinBox *spinBoxLineCount;
    QFrame *frame_3;
    QComboBox *comboBoxColorType;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *spinBoxMaxCurrent;
    QLabel *label_8;
    QComboBox *comboBoxLineNumber;
    QPushButton *pushButtonSetAll;
    QPushButton *pushButtonRead;
    QPushButton *pushButtonWrite;
    QPushButton *pushButtonReadStatus;
    QLineEdit *lineEditStatus;

    void setupUi(QDialog *WriteEPROMDialog)
    {
        if (WriteEPROMDialog->objectName().isEmpty())
            WriteEPROMDialog->setObjectName("WriteEPROMDialog");
        WriteEPROMDialog->resize(452, 425);
        frame = new QFrame(WriteEPROMDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 431, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 431, 16));
        label_3->setAlignment(Qt::AlignCenter);
        comboBoxSelectPort = new QComboBox(frame);
        comboBoxSelectPort->addItem(QString());
        comboBoxSelectPort->addItem(QString());
        comboBoxSelectPort->setObjectName("comboBoxSelectPort");
        comboBoxSelectPort->setGeometry(QRect(270, 30, 121, 22));
        comboBoxSelectBoard = new QComboBox(frame);
        comboBoxSelectBoard->addItem(QString());
        comboBoxSelectBoard->addItem(QString());
        comboBoxSelectBoard->addItem(QString());
        comboBoxSelectBoard->setObjectName("comboBoxSelectBoard");
        comboBoxSelectBoard->setGeometry(QRect(100, 30, 80, 22));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 62, 21));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(211, 30, 51, 21));
        label_2->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(WriteEPROMDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 90, 431, 211));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 431, 16));
        label_4->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 30, 171, 21));
        label_7->setAlignment(Qt::AlignCenter);
        spinBoxLineCount = new QSpinBox(frame_2);
        spinBoxLineCount->setObjectName("spinBoxLineCount");
        spinBoxLineCount->setGeometry(QRect(190, 30, 61, 22));
        spinBoxLineCount->setMaximum(64);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(20, 70, 391, 121));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        comboBoxColorType = new QComboBox(frame_3);
        comboBoxColorType->addItem(QString());
        comboBoxColorType->addItem(QString());
        comboBoxColorType->addItem(QString());
        comboBoxColorType->addItem(QString());
        comboBoxColorType->addItem(QString());
        comboBoxColorType->addItem(QString());
        comboBoxColorType->addItem(QString());
        comboBoxColorType->setObjectName("comboBoxColorType");
        comboBoxColorType->setGeometry(QRect(130, 50, 91, 22));
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 50, 111, 21));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(frame_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 80, 111, 21));
        label_6->setAlignment(Qt::AlignCenter);
        spinBoxMaxCurrent = new QSpinBox(frame_3);
        spinBoxMaxCurrent->setObjectName("spinBoxMaxCurrent");
        spinBoxMaxCurrent->setGeometry(QRect(130, 80, 101, 22));
        spinBoxMaxCurrent->setMaximum(9999);
        label_8 = new QLabel(frame_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 10, 121, 21));
        label_8->setAlignment(Qt::AlignCenter);
        comboBoxLineNumber = new QComboBox(frame_3);
        comboBoxLineNumber->setObjectName("comboBoxLineNumber");
        comboBoxLineNumber->setGeometry(QRect(160, 10, 80, 22));
        pushButtonSetAll = new QPushButton(frame_3);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(270, 60, 93, 41));
        pushButtonRead = new QPushButton(WriteEPROMDialog);
        pushButtonRead->setObjectName("pushButtonRead");
        pushButtonRead->setGeometry(QRect(60, 310, 151, 41));
        pushButtonWrite = new QPushButton(WriteEPROMDialog);
        pushButtonWrite->setObjectName("pushButtonWrite");
        pushButtonWrite->setGeometry(QRect(250, 310, 151, 41));
        pushButtonReadStatus = new QPushButton(WriteEPROMDialog);
        pushButtonReadStatus->setObjectName("pushButtonReadStatus");
        pushButtonReadStatus->setGeometry(QRect(60, 360, 151, 31));
        lineEditStatus = new QLineEdit(WriteEPROMDialog);
        lineEditStatus->setObjectName("lineEditStatus");
        lineEditStatus->setGeometry(QRect(60, 390, 151, 21));

        retranslateUi(WriteEPROMDialog);

        QMetaObject::connectSlotsByName(WriteEPROMDialog);
    } // setupUi

    void retranslateUi(QDialog *WriteEPROMDialog)
    {
        WriteEPROMDialog->setWindowTitle(QCoreApplication::translate("WriteEPROMDialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("WriteEPROMDialog", "Select", nullptr));
        comboBoxSelectPort->setItemText(0, QCoreApplication::translate("WriteEPROMDialog", "Port1 (8 Lines)", nullptr));
        comboBoxSelectPort->setItemText(1, QCoreApplication::translate("WriteEPROMDialog", "Port2 (8 Lines)", nullptr));

        comboBoxSelectBoard->setItemText(0, QCoreApplication::translate("WriteEPROMDialog", "0", nullptr));
        comboBoxSelectBoard->setItemText(1, QCoreApplication::translate("WriteEPROMDialog", "1", nullptr));
        comboBoxSelectBoard->setItemText(2, QCoreApplication::translate("WriteEPROMDialog", "2", nullptr));

        label->setText(QCoreApplication::translate("WriteEPROMDialog", "Board", nullptr));
        label_2->setText(QCoreApplication::translate("WriteEPROMDialog", "Port", nullptr));
        label_4->setText(QCoreApplication::translate("WriteEPROMDialog", "Setting", nullptr));
        label_7->setText(QCoreApplication::translate("WriteEPROMDialog", "Line count of usage", nullptr));
        comboBoxColorType->setItemText(0, QCoreApplication::translate("WriteEPROMDialog", "Red", nullptr));
        comboBoxColorType->setItemText(1, QCoreApplication::translate("WriteEPROMDialog", "Green", nullptr));
        comboBoxColorType->setItemText(2, QCoreApplication::translate("WriteEPROMDialog", "Blue", nullptr));
        comboBoxColorType->setItemText(3, QCoreApplication::translate("WriteEPROMDialog", "IR", nullptr));
        comboBoxColorType->setItemText(4, QCoreApplication::translate("WriteEPROMDialog", "UV", nullptr));
        comboBoxColorType->setItemText(5, QCoreApplication::translate("WriteEPROMDialog", "White", nullptr));
        comboBoxColorType->setItemText(6, QCoreApplication::translate("WriteEPROMDialog", "Other", nullptr));

        label_5->setText(QCoreApplication::translate("WriteEPROMDialog", "Color", nullptr));
        label_6->setText(QCoreApplication::translate("WriteEPROMDialog", "Max current", nullptr));
        label_8->setText(QCoreApplication::translate("WriteEPROMDialog", "Line number", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("WriteEPROMDialog", "Set all", nullptr));
        pushButtonRead->setText(QCoreApplication::translate("WriteEPROMDialog", "Read from device", nullptr));
        pushButtonWrite->setText(QCoreApplication::translate("WriteEPROMDialog", "Write to device", nullptr));
        pushButtonReadStatus->setText(QCoreApplication::translate("WriteEPROMDialog", "Read status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WriteEPROMDialog: public Ui_WriteEPROMDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRITEEPROMDIALOG_H
