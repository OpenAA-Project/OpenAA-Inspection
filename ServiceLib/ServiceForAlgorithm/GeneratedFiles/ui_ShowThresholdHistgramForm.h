/********************************************************************************
** Form generated from reading UI file 'ShowThresholdHistgramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWTHRESHOLDHISTGRAMFORM_H
#define UI_SHOWTHRESHOLDHISTGRAMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowThresholdHistgramForm
{
public:
    QLineEdit *lineEditThresh1;
    QPushButton *pushButtonCalcD;
    QPushButton *pushButtonCalc2;
    QPushButton *pushButtonCalcU;
    QPushButton *pushButtonSave;
    QFrame *frame;
    QPushButton *pushButtonCalc;
    QLabel *label_5;
    QLineEdit *lineEditNumDev;
    QLabel *label_8;
    QLineEdit *lineEditNumCenter;
    QLineEdit *lineEditLibName;
    QPushButton *pushButtonSetThreshold;
    QLineEdit *lineEditThresh2;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEditLibID;
    QLabel *label_7;
    QLineEdit *lineEditHistName;
    QLabel *label;
    QFrame *frame_2;
    QToolButton *toolButtonThreshold1;
    QToolButton *toolButtonThreshold2;
    QLineEdit *lineEditNumPercent;
    QPushButton *pushButtonClose;
    QLabel *label_4;

    void setupUi(QWidget *ShowThresholdHistgramForm)
    {
        if (ShowThresholdHistgramForm->objectName().isEmpty())
            ShowThresholdHistgramForm->setObjectName("ShowThresholdHistgramForm");
        ShowThresholdHistgramForm->resize(755, 513);
        lineEditThresh1 = new QLineEdit(ShowThresholdHistgramForm);
        lineEditThresh1->setObjectName("lineEditThresh1");
        lineEditThresh1->setGeometry(QRect(430, 400, 81, 20));
        pushButtonCalcD = new QPushButton(ShowThresholdHistgramForm);
        pushButtonCalcD->setObjectName("pushButtonCalcD");
        pushButtonCalcD->setGeometry(QRect(430, 450, 81, 21));
        pushButtonCalc2 = new QPushButton(ShowThresholdHistgramForm);
        pushButtonCalc2->setObjectName("pushButtonCalc2");
        pushButtonCalc2->setGeometry(QRect(520, 430, 81, 21));
        pushButtonCalcU = new QPushButton(ShowThresholdHistgramForm);
        pushButtonCalcU->setObjectName("pushButtonCalcU");
        pushButtonCalcU->setGeometry(QRect(520, 450, 81, 21));
        pushButtonSave = new QPushButton(ShowThresholdHistgramForm);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(620, 380, 121, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSave->setIcon(icon);
        frame = new QFrame(ShowThresholdHistgramForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 731, 351));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        pushButtonCalc = new QPushButton(ShowThresholdHistgramForm);
        pushButtonCalc->setObjectName("pushButtonCalc");
        pushButtonCalc->setGeometry(QRect(430, 430, 81, 21));
        label_5 = new QLabel(ShowThresholdHistgramForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 380, 51, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditNumDev = new QLineEdit(ShowThresholdHistgramForm);
        lineEditNumDev->setObjectName("lineEditNumDev");
        lineEditNumDev->setGeometry(QRect(260, 450, 81, 20));
        lineEditNumDev->setReadOnly(true);
        label_8 = new QLabel(ShowThresholdHistgramForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(350, 450, 81, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditNumCenter = new QLineEdit(ShowThresholdHistgramForm);
        lineEditNumCenter->setObjectName("lineEditNumCenter");
        lineEditNumCenter->setGeometry(QRect(260, 400, 81, 20));
        lineEditNumCenter->setReadOnly(true);
        lineEditLibName = new QLineEdit(ShowThresholdHistgramForm);
        lineEditLibName->setObjectName("lineEditLibName");
        lineEditLibName->setGeometry(QRect(60, 400, 191, 20));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(192, 192, 192, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditLibName->setPalette(palette);
        lineEditLibName->setReadOnly(true);
        pushButtonSetThreshold = new QPushButton(ShowThresholdHistgramForm);
        pushButtonSetThreshold->setObjectName("pushButtonSetThreshold");
        pushButtonSetThreshold->setGeometry(QRect(620, 410, 121, 34));
        lineEditThresh2 = new QLineEdit(ShowThresholdHistgramForm);
        lineEditThresh2->setObjectName("lineEditThresh2");
        lineEditThresh2->setGeometry(QRect(520, 400, 81, 20));
        label_6 = new QLabel(ShowThresholdHistgramForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 430, 241, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(ShowThresholdHistgramForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(290, 480, 231, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(ShowThresholdHistgramForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 430, 81, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLibID = new QLineEdit(ShowThresholdHistgramForm);
        lineEditLibID->setObjectName("lineEditLibID");
        lineEditLibID->setGeometry(QRect(10, 400, 51, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditLibID->setPalette(palette1);
        lineEditLibID->setReadOnly(true);
        label_7 = new QLabel(ShowThresholdHistgramForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(350, 430, 81, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditHistName = new QLineEdit(ShowThresholdHistgramForm);
        lineEditHistName->setObjectName("lineEditHistName");
        lineEditHistName->setGeometry(QRect(10, 450, 241, 20));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditHistName->setPalette(palette2);
        lineEditHistName->setReadOnly(true);
        label = new QLabel(ShowThresholdHistgramForm);
        label->setObjectName("label");
        label->setGeometry(QRect(260, 380, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(ShowThresholdHistgramForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(420, 370, 191, 31));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        toolButtonThreshold1 = new QToolButton(frame_2);
        toolButtonThreshold1->setObjectName("toolButtonThreshold1");
        toolButtonThreshold1->setGeometry(QRect(10, 10, 81, 21));
        toolButtonThreshold1->setCheckable(true);
        toolButtonThreshold1->setChecked(false);
        toolButtonThreshold1->setAutoExclusive(true);
        toolButtonThreshold2 = new QToolButton(frame_2);
        toolButtonThreshold2->setObjectName("toolButtonThreshold2");
        toolButtonThreshold2->setGeometry(QRect(100, 10, 81, 21));
        toolButtonThreshold2->setCheckable(true);
        toolButtonThreshold2->setChecked(true);
        toolButtonThreshold2->setAutoExclusive(true);
        lineEditNumPercent = new QLineEdit(ShowThresholdHistgramForm);
        lineEditNumPercent->setObjectName("lineEditNumPercent");
        lineEditNumPercent->setGeometry(QRect(520, 480, 81, 20));
        pushButtonClose = new QPushButton(ShowThresholdHistgramForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(620, 460, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/NG.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        label_4 = new QLabel(ShowThresholdHistgramForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(60, 380, 191, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(ShowThresholdHistgramForm);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(ShowThresholdHistgramForm);
    } // setupUi

    void retranslateUi(QWidget *ShowThresholdHistgramForm)
    {
        ShowThresholdHistgramForm->setWindowTitle(QCoreApplication::translate("ShowThresholdHistgramForm", "Form", nullptr));
        pushButtonCalcD->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\350\250\210\347\256\227\343\200\200\342\206\223", nullptr));
        pushButtonCalc2->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\350\250\210\347\256\227\343\200\200\342\206\221", nullptr));
        pushButtonCalcU->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\350\250\210\347\256\227\343\200\200\342\206\221", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "Save", nullptr));
        pushButtonCalc->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\350\250\210\347\256\227\343\200\200\342\206\223", nullptr));
        label_5->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\357\274\254\357\275\211\357\275\202\357\274\251\357\274\244", nullptr));
        label_8->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\346\255\243\350\246\217\345\210\206\345\270\203", nullptr));
        pushButtonSetThreshold->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "Set threshold", nullptr));
        label_6->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\343\203\222\343\202\271\343\203\210\343\202\260\343\203\251\343\203\240\345\220\215\347\247\260", nullptr));
        label_3->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\343\201\227\343\201\215\343\201\204\345\200\244\357\274\221\343\201\213\343\202\211\357\274\222\343\201\276\343\201\247\343\201\256\346\244\234\345\256\232\345\200\244\357\274\210\357\274\205\357\274\211", nullptr));
        label_2->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\346\250\231\346\272\226\345\201\217\345\267\256", nullptr));
        label_7->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\345\256\237\347\270\276", nullptr));
        label->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\344\270\255\345\277\203\345\200\244", nullptr));
        toolButtonThreshold1->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\343\201\227\343\201\215\343\201\204\345\200\244\357\274\221", nullptr));
        toolButtonThreshold2->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\343\201\227\343\201\215\343\201\204\345\200\244\357\274\222", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_4->setText(QCoreApplication::translate("ShowThresholdHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowThresholdHistgramForm: public Ui_ShowThresholdHistgramForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWTHRESHOLDHISTGRAMFORM_H
