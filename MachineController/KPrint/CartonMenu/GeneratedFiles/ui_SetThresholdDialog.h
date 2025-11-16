/********************************************************************************
** Form generated from reading UI file 'SetThresholdDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTHRESHOLDDIALOG_H
#define UI_SETTHRESHOLDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_SetThresholdDialog
{
public:
    QFrame *frame_2;
    QLabel *label_Level_6;
    QLabel *label_LevelCharBright;
    QSlider *horizontalSliderLevelCharBright;
    QFrame *frame_3;
    QLabel *label_Level_9;
    QLabel *label_LevelCharSize;
    QSlider *horizontalSliderLevelCharSize;
    QFrame *frame_4;
    QLabel *label_Level_13;
    QLabel *label_LevelFlatSize;
    QSlider *horizontalSliderLevelFlatSize;
    QFrame *frame_5;
    QLabel *label_Level_17;
    QLabel *label_LevelFlatBright;
    QSlider *horizontalSliderLevelFlatBright;
    QPushButton *PushButtonClose;

    void setupUi(QDialog *SetThresholdDialog)
    {
        if (SetThresholdDialog->objectName().isEmpty())
            SetThresholdDialog->setObjectName("SetThresholdDialog");
        SetThresholdDialog->resize(592, 290);
        frame_2 = new QFrame(SetThresholdDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 281, 101));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_Level_6 = new QLabel(frame_2);
        label_Level_6->setObjectName("label_Level_6");
        label_Level_6->setGeometry(QRect(0, 0, 281, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252")});
        font.setPointSize(12);
        font.setBold(false);
        label_Level_6->setFont(font);
        label_Level_6->setFrameShape(QFrame::Panel);
        label_Level_6->setFrameShadow(QFrame::Sunken);
        label_Level_6->setAlignment(Qt::AlignCenter);
        label_LevelCharBright = new QLabel(frame_2);
        label_LevelCharBright->setObjectName("label_LevelCharBright");
        label_LevelCharBright->setGeometry(QRect(240, 40, 41, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252")});
        font1.setPointSize(18);
        font1.setBold(false);
        label_LevelCharBright->setFont(font1);
        horizontalSliderLevelCharBright = new QSlider(frame_2);
        horizontalSliderLevelCharBright->setObjectName("horizontalSliderLevelCharBright");
        horizontalSliderLevelCharBright->setGeometry(QRect(10, 40, 221, 41));
        horizontalSliderLevelCharBright->setMaximum(10);
        horizontalSliderLevelCharBright->setPageStep(2);
        horizontalSliderLevelCharBright->setSliderPosition(5);
        horizontalSliderLevelCharBright->setOrientation(Qt::Horizontal);
        horizontalSliderLevelCharBright->setTickPosition(QSlider::TicksBelow);
        frame_3 = new QFrame(SetThresholdDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(300, 10, 281, 101));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_Level_9 = new QLabel(frame_3);
        label_Level_9->setObjectName("label_Level_9");
        label_Level_9->setGeometry(QRect(0, 0, 281, 31));
        label_Level_9->setFont(font);
        label_Level_9->setFrameShape(QFrame::Panel);
        label_Level_9->setFrameShadow(QFrame::Sunken);
        label_Level_9->setAlignment(Qt::AlignCenter);
        label_LevelCharSize = new QLabel(frame_3);
        label_LevelCharSize->setObjectName("label_LevelCharSize");
        label_LevelCharSize->setGeometry(QRect(240, 40, 41, 41));
        label_LevelCharSize->setFont(font1);
        horizontalSliderLevelCharSize = new QSlider(frame_3);
        horizontalSliderLevelCharSize->setObjectName("horizontalSliderLevelCharSize");
        horizontalSliderLevelCharSize->setGeometry(QRect(10, 40, 221, 41));
        horizontalSliderLevelCharSize->setMaximum(10);
        horizontalSliderLevelCharSize->setPageStep(2);
        horizontalSliderLevelCharSize->setSliderPosition(5);
        horizontalSliderLevelCharSize->setOrientation(Qt::Horizontal);
        horizontalSliderLevelCharSize->setTickPosition(QSlider::TicksBelow);
        frame_4 = new QFrame(SetThresholdDialog);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(300, 120, 281, 101));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_Level_13 = new QLabel(frame_4);
        label_Level_13->setObjectName("label_Level_13");
        label_Level_13->setGeometry(QRect(0, 0, 281, 31));
        label_Level_13->setFont(font);
        label_Level_13->setFrameShape(QFrame::Panel);
        label_Level_13->setFrameShadow(QFrame::Sunken);
        label_Level_13->setAlignment(Qt::AlignCenter);
        label_LevelFlatSize = new QLabel(frame_4);
        label_LevelFlatSize->setObjectName("label_LevelFlatSize");
        label_LevelFlatSize->setGeometry(QRect(240, 40, 41, 41));
        label_LevelFlatSize->setFont(font1);
        horizontalSliderLevelFlatSize = new QSlider(frame_4);
        horizontalSliderLevelFlatSize->setObjectName("horizontalSliderLevelFlatSize");
        horizontalSliderLevelFlatSize->setGeometry(QRect(10, 40, 221, 41));
        horizontalSliderLevelFlatSize->setMaximum(10);
        horizontalSliderLevelFlatSize->setPageStep(2);
        horizontalSliderLevelFlatSize->setSliderPosition(5);
        horizontalSliderLevelFlatSize->setOrientation(Qt::Horizontal);
        horizontalSliderLevelFlatSize->setTickPosition(QSlider::TicksBelow);
        frame_5 = new QFrame(SetThresholdDialog);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 120, 281, 101));
        frame_5->setFrameShape(QFrame::Panel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_Level_17 = new QLabel(frame_5);
        label_Level_17->setObjectName("label_Level_17");
        label_Level_17->setGeometry(QRect(0, 0, 281, 31));
        label_Level_17->setFont(font);
        label_Level_17->setFrameShape(QFrame::Panel);
        label_Level_17->setFrameShadow(QFrame::Sunken);
        label_Level_17->setAlignment(Qt::AlignCenter);
        label_LevelFlatBright = new QLabel(frame_5);
        label_LevelFlatBright->setObjectName("label_LevelFlatBright");
        label_LevelFlatBright->setGeometry(QRect(240, 40, 41, 41));
        label_LevelFlatBright->setFont(font1);
        horizontalSliderLevelFlatBright = new QSlider(frame_5);
        horizontalSliderLevelFlatBright->setObjectName("horizontalSliderLevelFlatBright");
        horizontalSliderLevelFlatBright->setGeometry(QRect(10, 40, 221, 41));
        horizontalSliderLevelFlatBright->setMaximum(10);
        horizontalSliderLevelFlatBright->setPageStep(2);
        horizontalSliderLevelFlatBright->setSliderPosition(5);
        horizontalSliderLevelFlatBright->setOrientation(Qt::Horizontal);
        horizontalSliderLevelFlatBright->setTickPosition(QSlider::TicksBelow);
        PushButtonClose = new QPushButton(SetThresholdDialog);
        PushButtonClose->setObjectName("PushButtonClose");
        PushButtonClose->setGeometry(QRect(190, 230, 211, 50));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font2.setPointSize(24);
        PushButtonClose->setFont(font2);
        PushButtonClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonClose->setCheckable(false);
        PushButtonClose->setAutoDefault(false);
        PushButtonClose->setFlat(false);

        retranslateUi(SetThresholdDialog);

        PushButtonClose->setDefault(false);


        QMetaObject::connectSlotsByName(SetThresholdDialog);
    } // setupUi

    void retranslateUi(QDialog *SetThresholdDialog)
    {
        SetThresholdDialog->setWindowTitle(QCoreApplication::translate("SetThresholdDialog", "\347\260\241\346\230\223\343\201\227\343\201\215\343\201\204\345\200\244\350\250\255\345\256\232", nullptr));
        label_Level_6->setText(QCoreApplication::translate("SetThresholdDialog", "\346\226\207\345\255\227\343\201\252\343\201\251\343\202\253\343\202\271\343\203\254", nullptr));
        label_LevelCharBright->setText(QCoreApplication::translate("SetThresholdDialog", "5", nullptr));
        label_Level_9->setText(QCoreApplication::translate("SetThresholdDialog", "\346\226\207\345\255\227\343\201\252\343\201\251\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_LevelCharSize->setText(QCoreApplication::translate("SetThresholdDialog", "5", nullptr));
        label_Level_13->setText(QCoreApplication::translate("SetThresholdDialog", "\343\201\271\343\201\237\351\203\250\345\210\206\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_LevelFlatSize->setText(QCoreApplication::translate("SetThresholdDialog", "5", nullptr));
        label_Level_17->setText(QCoreApplication::translate("SetThresholdDialog", "\343\201\271\343\201\237\351\203\250\345\210\206\343\202\253\343\202\271\343\203\254", nullptr));
        label_LevelFlatBright->setText(QCoreApplication::translate("SetThresholdDialog", "5", nullptr));
        PushButtonClose->setText(QCoreApplication::translate("SetThresholdDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetThresholdDialog: public Ui_SetThresholdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTHRESHOLDDIALOG_H
