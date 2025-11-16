/********************************************************************************
** Form generated from reading UI file 'ShowIODialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWIODIALOG_H
#define UI_SHOWIODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ShowIODialog
{
public:
    QFrame *frame;
    QLabel *label_3;
    QComboBox *comboBoxSelectBoard;
    QLabel *label;
    QToolButton *toolButtonAutoUpdate;
    QCheckBox *checkBoxInput0;
    QCheckBox *checkBoxInput1;
    QFrame *frame_2;
    QLabel *label_11;
    QLabel *label_10;
    QLineEdit *lineEditAD0;
    QLineEdit *lineEditAD3;
    QLabel *label_4;
    QLineEdit *lineEditAD7;
    QLabel *label_8;
    QLabel *label_7;
    QLineEdit *lineEditAD4;
    QLabel *label_5;
    QLineEdit *lineEditAD6;
    QLabel *label_9;
    QLabel *label_6;
    QLineEdit *lineEditAD5;
    QLineEdit *lineEditAD1;
    QLineEdit *lineEditAD2;
    QFrame *frame_3;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *lineEditAD8;
    QLineEdit *lineEditAD11;
    QLabel *label_14;
    QLineEdit *lineEditAD15;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *lineEditAD12;
    QLabel *label_17;
    QLineEdit *lineEditAD14;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *lineEditAD13;
    QLineEdit *lineEditAD9;
    QLineEdit *lineEditAD10;
    QFrame *frame_4;
    QComboBox *comboBoxLineNumber;
    QLabel *label_20;
    QLineEdit *lineEditCurrentValue;
    QLabel *label_21;
    QPushButton *pushButtonReadAD;
    QPushButton *pushButtonReadInput;
    QToolButton *toolButtonTestLED;

    void setupUi(QDialog *ShowIODialog)
    {
        if (ShowIODialog->objectName().isEmpty())
            ShowIODialog->setObjectName("ShowIODialog");
        ShowIODialog->resize(432, 469);
        frame = new QFrame(ShowIODialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 411, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 411, 16));
        label_3->setAlignment(Qt::AlignCenter);
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
        toolButtonAutoUpdate = new QToolButton(frame);
        toolButtonAutoUpdate->setObjectName("toolButtonAutoUpdate");
        toolButtonAutoUpdate->setGeometry(QRect(290, 20, 111, 41));
        toolButtonAutoUpdate->setCheckable(true);
        checkBoxInput0 = new QCheckBox(ShowIODialog);
        checkBoxInput0->setObjectName("checkBoxInput0");
        checkBoxInput0->setGeometry(QRect(60, 110, 93, 19));
        checkBoxInput1 = new QCheckBox(ShowIODialog);
        checkBoxInput1->setObjectName("checkBoxInput1");
        checkBoxInput1->setGeometry(QRect(60, 140, 93, 19));
        frame_2 = new QFrame(ShowIODialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(20, 170, 191, 181));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 150, 91, 21));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 130, 91, 21));
        lineEditAD0 = new QLineEdit(frame_2);
        lineEditAD0->setObjectName("lineEditAD0");
        lineEditAD0->setGeometry(QRect(110, 10, 71, 21));
        lineEditAD3 = new QLineEdit(frame_2);
        lineEditAD3->setObjectName("lineEditAD3");
        lineEditAD3->setGeometry(QRect(110, 70, 71, 21));
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 91, 21));
        lineEditAD7 = new QLineEdit(frame_2);
        lineEditAD7->setObjectName("lineEditAD7");
        lineEditAD7->setGeometry(QRect(110, 150, 71, 21));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 90, 91, 21));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 70, 91, 21));
        lineEditAD4 = new QLineEdit(frame_2);
        lineEditAD4->setObjectName("lineEditAD4");
        lineEditAD4->setGeometry(QRect(110, 90, 71, 21));
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 30, 91, 21));
        lineEditAD6 = new QLineEdit(frame_2);
        lineEditAD6->setObjectName("lineEditAD6");
        lineEditAD6->setGeometry(QRect(110, 130, 71, 21));
        label_9 = new QLabel(frame_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 110, 91, 21));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 50, 91, 21));
        lineEditAD5 = new QLineEdit(frame_2);
        lineEditAD5->setObjectName("lineEditAD5");
        lineEditAD5->setGeometry(QRect(110, 110, 71, 21));
        lineEditAD1 = new QLineEdit(frame_2);
        lineEditAD1->setObjectName("lineEditAD1");
        lineEditAD1->setGeometry(QRect(110, 30, 71, 21));
        lineEditAD2 = new QLineEdit(frame_2);
        lineEditAD2->setObjectName("lineEditAD2");
        lineEditAD2->setGeometry(QRect(110, 50, 71, 21));
        frame_3 = new QFrame(ShowIODialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(230, 170, 191, 181));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(frame_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 150, 91, 21));
        label_13 = new QLabel(frame_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 130, 91, 21));
        lineEditAD8 = new QLineEdit(frame_3);
        lineEditAD8->setObjectName("lineEditAD8");
        lineEditAD8->setGeometry(QRect(110, 10, 71, 21));
        lineEditAD11 = new QLineEdit(frame_3);
        lineEditAD11->setObjectName("lineEditAD11");
        lineEditAD11->setGeometry(QRect(110, 70, 71, 21));
        label_14 = new QLabel(frame_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 10, 91, 21));
        lineEditAD15 = new QLineEdit(frame_3);
        lineEditAD15->setObjectName("lineEditAD15");
        lineEditAD15->setGeometry(QRect(110, 150, 71, 21));
        label_15 = new QLabel(frame_3);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 90, 91, 21));
        label_16 = new QLabel(frame_3);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 70, 91, 21));
        lineEditAD12 = new QLineEdit(frame_3);
        lineEditAD12->setObjectName("lineEditAD12");
        lineEditAD12->setGeometry(QRect(110, 90, 71, 21));
        label_17 = new QLabel(frame_3);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 30, 91, 21));
        lineEditAD14 = new QLineEdit(frame_3);
        lineEditAD14->setObjectName("lineEditAD14");
        lineEditAD14->setGeometry(QRect(110, 130, 71, 21));
        label_18 = new QLabel(frame_3);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 110, 91, 21));
        label_19 = new QLabel(frame_3);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(10, 50, 91, 21));
        lineEditAD13 = new QLineEdit(frame_3);
        lineEditAD13->setObjectName("lineEditAD13");
        lineEditAD13->setGeometry(QRect(110, 110, 71, 21));
        lineEditAD9 = new QLineEdit(frame_3);
        lineEditAD9->setObjectName("lineEditAD9");
        lineEditAD9->setGeometry(QRect(110, 30, 71, 21));
        lineEditAD10 = new QLineEdit(frame_3);
        lineEditAD10->setObjectName("lineEditAD10");
        lineEditAD10->setGeometry(QRect(110, 50, 71, 21));
        frame_4 = new QFrame(ShowIODialog);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(20, 360, 401, 91));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        comboBoxLineNumber = new QComboBox(frame_4);
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->addItem(QString());
        comboBoxLineNumber->setObjectName("comboBoxLineNumber");
        comboBoxLineNumber->setGeometry(QRect(160, 10, 61, 22));
        label_20 = new QLabel(frame_4);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(51, 10, 91, 21));
        lineEditCurrentValue = new QLineEdit(frame_4);
        lineEditCurrentValue->setObjectName("lineEditCurrentValue");
        lineEditCurrentValue->setGeometry(QRect(180, 50, 71, 21));
        label_21 = new QLabel(frame_4);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(50, 50, 121, 21));
        label_21->setAlignment(Qt::AlignCenter);
        pushButtonReadAD = new QPushButton(frame_4);
        pushButtonReadAD->setObjectName("pushButtonReadAD");
        pushButtonReadAD->setGeometry(QRect(290, 10, 93, 28));
        pushButtonReadInput = new QPushButton(ShowIODialog);
        pushButtonReadInput->setObjectName("pushButtonReadInput");
        pushButtonReadInput->setGeometry(QRect(150, 110, 93, 28));
        toolButtonTestLED = new QToolButton(ShowIODialog);
        toolButtonTestLED->setObjectName("toolButtonTestLED");
        toolButtonTestLED->setGeometry(QRect(320, 130, 91, 31));
        toolButtonTestLED->setCheckable(true);

        retranslateUi(ShowIODialog);

        QMetaObject::connectSlotsByName(ShowIODialog);
    } // setupUi

    void retranslateUi(QDialog *ShowIODialog)
    {
        ShowIODialog->setWindowTitle(QCoreApplication::translate("ShowIODialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("ShowIODialog", "Select", nullptr));
        comboBoxSelectBoard->setItemText(0, QCoreApplication::translate("ShowIODialog", "0", nullptr));
        comboBoxSelectBoard->setItemText(1, QCoreApplication::translate("ShowIODialog", "1", nullptr));
        comboBoxSelectBoard->setItemText(2, QCoreApplication::translate("ShowIODialog", "2", nullptr));

        label->setText(QCoreApplication::translate("ShowIODialog", "Board", nullptr));
        toolButtonAutoUpdate->setText(QCoreApplication::translate("ShowIODialog", "Auto update", nullptr));
        checkBoxInput0->setText(QCoreApplication::translate("ShowIODialog", "Input 0", nullptr));
        checkBoxInput1->setText(QCoreApplication::translate("ShowIODialog", "Input 1", nullptr));
        label_11->setText(QCoreApplication::translate("ShowIODialog", "A/D value 7", nullptr));
        label_10->setText(QCoreApplication::translate("ShowIODialog", "A/D value 6", nullptr));
        label_4->setText(QCoreApplication::translate("ShowIODialog", "A/D value 0", nullptr));
        label_8->setText(QCoreApplication::translate("ShowIODialog", "A/D value 4", nullptr));
        label_7->setText(QCoreApplication::translate("ShowIODialog", "A/D value 3", nullptr));
        label_5->setText(QCoreApplication::translate("ShowIODialog", "A/D value 1", nullptr));
        label_9->setText(QCoreApplication::translate("ShowIODialog", "A/D value 5", nullptr));
        label_6->setText(QCoreApplication::translate("ShowIODialog", "A/D value 2", nullptr));
        label_12->setText(QCoreApplication::translate("ShowIODialog", "A/D value 15", nullptr));
        label_13->setText(QCoreApplication::translate("ShowIODialog", "A/D value 14", nullptr));
        label_14->setText(QCoreApplication::translate("ShowIODialog", "A/D value 8", nullptr));
        label_15->setText(QCoreApplication::translate("ShowIODialog", "A/D value 12", nullptr));
        label_16->setText(QCoreApplication::translate("ShowIODialog", "A/D value 11", nullptr));
        label_17->setText(QCoreApplication::translate("ShowIODialog", "A/D value 9", nullptr));
        label_18->setText(QCoreApplication::translate("ShowIODialog", "A/D value 13", nullptr));
        label_19->setText(QCoreApplication::translate("ShowIODialog", "A/D value 10", nullptr));
        comboBoxLineNumber->setItemText(0, QCoreApplication::translate("ShowIODialog", "0", nullptr));
        comboBoxLineNumber->setItemText(1, QCoreApplication::translate("ShowIODialog", "1", nullptr));
        comboBoxLineNumber->setItemText(2, QCoreApplication::translate("ShowIODialog", "2", nullptr));
        comboBoxLineNumber->setItemText(3, QCoreApplication::translate("ShowIODialog", "3", nullptr));
        comboBoxLineNumber->setItemText(4, QCoreApplication::translate("ShowIODialog", "4", nullptr));
        comboBoxLineNumber->setItemText(5, QCoreApplication::translate("ShowIODialog", "5", nullptr));
        comboBoxLineNumber->setItemText(6, QCoreApplication::translate("ShowIODialog", "6", nullptr));
        comboBoxLineNumber->setItemText(7, QCoreApplication::translate("ShowIODialog", "7", nullptr));
        comboBoxLineNumber->setItemText(8, QCoreApplication::translate("ShowIODialog", "8", nullptr));
        comboBoxLineNumber->setItemText(9, QCoreApplication::translate("ShowIODialog", "9", nullptr));
        comboBoxLineNumber->setItemText(10, QCoreApplication::translate("ShowIODialog", "10", nullptr));
        comboBoxLineNumber->setItemText(11, QCoreApplication::translate("ShowIODialog", "11", nullptr));
        comboBoxLineNumber->setItemText(12, QCoreApplication::translate("ShowIODialog", "12", nullptr));
        comboBoxLineNumber->setItemText(13, QCoreApplication::translate("ShowIODialog", "13", nullptr));
        comboBoxLineNumber->setItemText(14, QCoreApplication::translate("ShowIODialog", "14", nullptr));
        comboBoxLineNumber->setItemText(15, QCoreApplication::translate("ShowIODialog", "15", nullptr));

        label_20->setText(QCoreApplication::translate("ShowIODialog", "Line number", nullptr));
        label_21->setText(QCoreApplication::translate("ShowIODialog", "Current value", nullptr));
        pushButtonReadAD->setText(QCoreApplication::translate("ShowIODialog", "Read A/D", nullptr));
        pushButtonReadInput->setText(QCoreApplication::translate("ShowIODialog", "Read Input", nullptr));
        toolButtonTestLED->setText(QCoreApplication::translate("ShowIODialog", "Test LED", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowIODialog: public Ui_ShowIODialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWIODIALOG_H
