/********************************************************************************
** Form generated from reading UI file 'AdjustTriggerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADJUSTTRIGGERFORM_H
#define UI_ADJUSTTRIGGERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdjustTriggerForm
{
public:
    QLabel *label;
    QSlider *horizontalSlider1;
    QSpinBox *spinBox1;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxDrop;
    QLabel *label_3;
    QSlider *horizontalSliderDrop;
    QFrame *frameDownStream;
    QSpinBox *spinBox2;
    QLabel *label_2;
    QSlider *horizontalSlider2;
    QLabel *label_9;
    QLabel *label_TriggerPos2MM;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_TriggerPos1MM;
    QLabel *label_8;
    QFrame *frame;
    QFrame *frame3;
    QSpinBox *spinBox3;
    QLabel *label_6;
    QSlider *horizontalSlider3;
    QLabel *label_10;
    QLabel *label_TriggerPos3MM;
    QLabel *label_7;
    QFrame *frame4;
    QSpinBox *spinBox4;
    QLabel *label_11;
    QSlider *horizontalSlider4;
    QLabel *label_12;
    QLabel *label_TriggerPos4MM;
    QLabel *label_13;

    void setupUi(QWidget *AdjustTriggerForm)
    {
        if (AdjustTriggerForm->objectName().isEmpty())
            AdjustTriggerForm->setObjectName("AdjustTriggerForm");
        AdjustTriggerForm->resize(905, 685);
        label = new QLabel(AdjustTriggerForm);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 221, 31));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        horizontalSlider1 = new QSlider(AdjustTriggerForm);
        horizontalSlider1->setObjectName("horizontalSlider1");
        horizontalSlider1->setGeometry(QRect(20, 50, 751, 31));
        horizontalSlider1->setMaximum(60000);
        horizontalSlider1->setValue(22000);
        horizontalSlider1->setOrientation(Qt::Horizontal);
        spinBox1 = new QSpinBox(AdjustTriggerForm);
        spinBox1->setObjectName("spinBox1");
        spinBox1->setGeometry(QRect(790, 50, 91, 31));
        QFont font1;
        font1.setPointSize(12);
        spinBox1->setFont(font1);
        spinBox1->setMaximum(60000);
        spinBox1->setValue(22000);
        pushButtonOK = new QPushButton(AdjustTriggerForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 640, 131, 41));
        pushButtonOK->setFont(font1);
        pushButtonCancel = new QPushButton(AdjustTriggerForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(720, 640, 131, 41));
        pushButtonCancel->setFont(font1);
        spinBoxDrop = new QSpinBox(AdjustTriggerForm);
        spinBoxDrop->setObjectName("spinBoxDrop");
        spinBoxDrop->setGeometry(QRect(790, 580, 91, 31));
        spinBoxDrop->setFont(font1);
        spinBoxDrop->setMaximum(4000);
        spinBoxDrop->setValue(1750);
        label_3 = new QLabel(AdjustTriggerForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 540, 221, 31));
        label_3->setFont(font);
        horizontalSliderDrop = new QSlider(AdjustTriggerForm);
        horizontalSliderDrop->setObjectName("horizontalSliderDrop");
        horizontalSliderDrop->setGeometry(QRect(20, 580, 751, 31));
        horizontalSliderDrop->setMaximum(4000);
        horizontalSliderDrop->setValue(1750);
        horizontalSliderDrop->setOrientation(Qt::Horizontal);
        frameDownStream = new QFrame(AdjustTriggerForm);
        frameDownStream->setObjectName("frameDownStream");
        frameDownStream->setGeometry(QRect(20, 150, 871, 121));
        frameDownStream->setFrameShape(QFrame::StyledPanel);
        frameDownStream->setFrameShadow(QFrame::Raised);
        spinBox2 = new QSpinBox(frameDownStream);
        spinBox2->setObjectName("spinBox2");
        spinBox2->setGeometry(QRect(770, 40, 91, 31));
        spinBox2->setFont(font1);
        spinBox2->setMaximum(60000);
        spinBox2->setValue(53000);
        label_2 = new QLabel(frameDownStream);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 221, 31));
        label_2->setFont(font);
        horizontalSlider2 = new QSlider(frameDownStream);
        horizontalSlider2->setObjectName("horizontalSlider2");
        horizontalSlider2->setGeometry(QRect(0, 40, 751, 31));
        horizontalSlider2->setMaximum(60000);
        horizontalSlider2->setValue(53000);
        horizontalSlider2->setOrientation(Qt::Horizontal);
        label_9 = new QLabel(frameDownStream);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(760, 80, 61, 31));
        label_9->setFont(font);
        label_TriggerPos2MM = new QLabel(frameDownStream);
        label_TriggerPos2MM->setObjectName("label_TriggerPos2MM");
        label_TriggerPos2MM->setGeometry(QRect(660, 80, 101, 31));
        label_TriggerPos2MM->setFont(font);
        label_5 = new QLabel(frameDownStream);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(410, 80, 251, 31));
        label_5->setFont(font);
        label_4 = new QLabel(AdjustTriggerForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(430, 100, 251, 31));
        label_4->setFont(font);
        label_TriggerPos1MM = new QLabel(AdjustTriggerForm);
        label_TriggerPos1MM->setObjectName("label_TriggerPos1MM");
        label_TriggerPos1MM->setGeometry(QRect(680, 100, 101, 31));
        label_TriggerPos1MM->setFont(font);
        label_8 = new QLabel(AdjustTriggerForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(780, 100, 61, 31));
        label_8->setFont(font);
        frame = new QFrame(AdjustTriggerForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 540, 881, 101));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame3 = new QFrame(AdjustTriggerForm);
        frame3->setObjectName("frame3");
        frame3->setGeometry(QRect(20, 280, 871, 121));
        frame3->setFrameShape(QFrame::StyledPanel);
        frame3->setFrameShadow(QFrame::Raised);
        spinBox3 = new QSpinBox(frame3);
        spinBox3->setObjectName("spinBox3");
        spinBox3->setGeometry(QRect(770, 40, 91, 31));
        spinBox3->setFont(font1);
        spinBox3->setMaximum(60000);
        spinBox3->setValue(53000);
        label_6 = new QLabel(frame3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 221, 31));
        label_6->setFont(font);
        horizontalSlider3 = new QSlider(frame3);
        horizontalSlider3->setObjectName("horizontalSlider3");
        horizontalSlider3->setGeometry(QRect(0, 40, 751, 31));
        horizontalSlider3->setMaximum(60000);
        horizontalSlider3->setValue(53000);
        horizontalSlider3->setOrientation(Qt::Horizontal);
        label_10 = new QLabel(frame3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(760, 80, 61, 31));
        label_10->setFont(font);
        label_TriggerPos3MM = new QLabel(frame3);
        label_TriggerPos3MM->setObjectName("label_TriggerPos3MM");
        label_TriggerPos3MM->setGeometry(QRect(660, 80, 101, 31));
        label_TriggerPos3MM->setFont(font);
        label_7 = new QLabel(frame3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(410, 80, 251, 31));
        label_7->setFont(font);
        frame4 = new QFrame(AdjustTriggerForm);
        frame4->setObjectName("frame4");
        frame4->setGeometry(QRect(20, 410, 871, 121));
        frame4->setFrameShape(QFrame::StyledPanel);
        frame4->setFrameShadow(QFrame::Raised);
        spinBox4 = new QSpinBox(frame4);
        spinBox4->setObjectName("spinBox4");
        spinBox4->setGeometry(QRect(770, 40, 91, 31));
        spinBox4->setFont(font1);
        spinBox4->setMaximum(60000);
        spinBox4->setValue(53000);
        label_11 = new QLabel(frame4);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(0, 0, 221, 31));
        label_11->setFont(font);
        horizontalSlider4 = new QSlider(frame4);
        horizontalSlider4->setObjectName("horizontalSlider4");
        horizontalSlider4->setGeometry(QRect(0, 40, 751, 31));
        horizontalSlider4->setMaximum(60000);
        horizontalSlider4->setValue(53000);
        horizontalSlider4->setOrientation(Qt::Horizontal);
        label_12 = new QLabel(frame4);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(760, 80, 61, 31));
        label_12->setFont(font);
        label_TriggerPos4MM = new QLabel(frame4);
        label_TriggerPos4MM->setObjectName("label_TriggerPos4MM");
        label_TriggerPos4MM->setGeometry(QRect(660, 80, 101, 31));
        label_TriggerPos4MM->setFont(font);
        label_13 = new QLabel(frame4);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(410, 80, 251, 31));
        label_13->setFont(font);

        retranslateUi(AdjustTriggerForm);

        QMetaObject::connectSlotsByName(AdjustTriggerForm);
    } // setupUi

    void retranslateUi(QWidget *AdjustTriggerForm)
    {
        AdjustTriggerForm->setWindowTitle(QCoreApplication::translate("AdjustTriggerForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("AdjustTriggerForm", "\346\222\256\345\203\217\344\275\215\347\275\256\357\274\221", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AdjustTriggerForm", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AdjustTriggerForm", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label_3->setText(QCoreApplication::translate("AdjustTriggerForm", "\346\214\257\343\202\212\345\210\206\343\201\221\343\202\277\343\202\244\343\203\237\343\203\263\343\202\260", nullptr));
        label_2->setText(QCoreApplication::translate("AdjustTriggerForm", "\346\222\256\345\203\217\344\275\215\347\275\256\357\274\222", nullptr));
        label_9->setText(QCoreApplication::translate("AdjustTriggerForm", "mm", nullptr));
        label_TriggerPos2MM->setText(QCoreApplication::translate("AdjustTriggerForm", "XXX.X", nullptr));
        label_5->setText(QCoreApplication::translate("AdjustTriggerForm", "\344\273\245\345\211\215\343\202\210\343\202\212\347\224\273\345\203\217\343\201\214\344\270\212\343\201\253", nullptr));
        label_4->setText(QCoreApplication::translate("AdjustTriggerForm", "\344\273\245\345\211\215\343\202\210\343\202\212\347\224\273\345\203\217\343\201\214\344\270\212\343\201\253", nullptr));
        label_TriggerPos1MM->setText(QCoreApplication::translate("AdjustTriggerForm", "XXX.X", nullptr));
        label_8->setText(QCoreApplication::translate("AdjustTriggerForm", "mm", nullptr));
        label_6->setText(QCoreApplication::translate("AdjustTriggerForm", "\346\222\256\345\203\217\344\275\215\347\275\2563", nullptr));
        label_10->setText(QCoreApplication::translate("AdjustTriggerForm", "mm", nullptr));
        label_TriggerPos3MM->setText(QCoreApplication::translate("AdjustTriggerForm", "XXX.X", nullptr));
        label_7->setText(QCoreApplication::translate("AdjustTriggerForm", "\344\273\245\345\211\215\343\202\210\343\202\212\347\224\273\345\203\217\343\201\214\344\270\212\343\201\253", nullptr));
        label_11->setText(QCoreApplication::translate("AdjustTriggerForm", "\346\222\256\345\203\217\344\275\215\347\275\2564", nullptr));
        label_12->setText(QCoreApplication::translate("AdjustTriggerForm", "mm", nullptr));
        label_TriggerPos4MM->setText(QCoreApplication::translate("AdjustTriggerForm", "XXX.X", nullptr));
        label_13->setText(QCoreApplication::translate("AdjustTriggerForm", "\344\273\245\345\211\215\343\202\210\343\202\212\347\224\273\345\203\217\343\201\214\344\270\212\343\201\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdjustTriggerForm: public Ui_AdjustTriggerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADJUSTTRIGGERFORM_H
