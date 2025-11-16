/********************************************************************************
** Form generated from reading UI file 'LearningPanelForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEARNINGPANELFORM_H
#define UI_LEARNINGPANELFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LearningPanelForm
{
public:
    QSpinBox *spinBoxPriority;
    QPushButton *pushButtonCancel;
    QLabel *labelMessage;
    QFrame *frame;
    QLabel *label_4;
    QSlider *horizontalSliderPriority;
    QPushButton *pushButtonOK;
    QFrame *frame_2;
    QToolButton *toolButtonPointDraw;
    QToolButton *toolButtonRectangleDraw;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *LearningPanelForm)
    {
        if (LearningPanelForm->objectName().isEmpty())
            LearningPanelForm->setObjectName("LearningPanelForm");
        LearningPanelForm->resize(489, 578);
        spinBoxPriority = new QSpinBox(LearningPanelForm);
        spinBoxPriority->setObjectName("spinBoxPriority");
        spinBoxPriority->setGeometry(QRect(360, 481, 61, 31));
        spinBoxPriority->setMaximum(100);
        pushButtonCancel = new QPushButton(LearningPanelForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 530, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        labelMessage = new QLabel(LearningPanelForm);
        labelMessage->setObjectName("labelMessage");
        labelMessage->setGeometry(QRect(60, 460, 351, 20));
        labelMessage->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(LearningPanelForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 50, 451, 411));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(LearningPanelForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(90, 490, 41, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        horizontalSliderPriority = new QSlider(LearningPanelForm);
        horizontalSliderPriority->setObjectName("horizontalSliderPriority");
        horizontalSliderPriority->setGeometry(QRect(140, 490, 160, 16));
        horizontalSliderPriority->setMaximum(100);
        horizontalSliderPriority->setOrientation(Qt::Horizontal);
        pushButtonOK = new QPushButton(LearningPanelForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(260, 530, 111, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        frame_2 = new QFrame(LearningPanelForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 451, 41));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        toolButtonPointDraw = new QToolButton(frame_2);
        toolButtonPointDraw->setObjectName("toolButtonPointDraw");
        toolButtonPointDraw->setGeometry(QRect(10, 0, 121, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Point.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonPointDraw->setIcon(icon2);
        toolButtonPointDraw->setCheckable(true);
        toolButtonPointDraw->setChecked(true);
        toolButtonPointDraw->setAutoExclusive(true);
        toolButtonPointDraw->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButtonRectangleDraw = new QToolButton(frame_2);
        toolButtonRectangleDraw->setObjectName("toolButtonRectangleDraw");
        toolButtonRectangleDraw->setGeometry(QRect(140, 0, 101, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/SelectAll.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonRectangleDraw->setIcon(icon3);
        toolButtonRectangleDraw->setCheckable(true);
        toolButtonRectangleDraw->setChecked(false);
        toolButtonRectangleDraw->setAutoExclusive(true);
        toolButtonRectangleDraw->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        label_2 = new QLabel(LearningPanelForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 490, 61, 20));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(LearningPanelForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(310, 490, 41, 20));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(LearningPanelForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(LearningPanelForm);
    } // setupUi

    void retranslateUi(QWidget *LearningPanelForm)
    {
        LearningPanelForm->setWindowTitle(QCoreApplication::translate("LearningPanelForm", "Learning registration", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("LearningPanelForm", "Cancel", nullptr));
        labelMessage->setText(QCoreApplication::translate("LearningPanelForm", "\357\274\256\357\274\247\347\256\207\346\211\200\343\202\222\343\203\236\343\202\246\343\202\271\343\201\247\343\202\257\343\203\252\343\203\203\343\202\257\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204", nullptr));
        label_4->setText(QCoreApplication::translate("LearningPanelForm", "\351\253\230\343\201\204", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("LearningPanelForm", "OK", nullptr));
        toolButtonPointDraw->setText(QCoreApplication::translate("LearningPanelForm", "\347\202\271\343\201\247\346\214\207\345\256\232", nullptr));
        toolButtonRectangleDraw->setText(QCoreApplication::translate("LearningPanelForm", "\347\237\251\345\275\242", nullptr));
        label_2->setText(QCoreApplication::translate("LearningPanelForm", "\351\207\215\350\246\201\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("LearningPanelForm", "\344\275\216\343\201\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearningPanelForm: public Ui_LearningPanelForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNINGPANELFORM_H
