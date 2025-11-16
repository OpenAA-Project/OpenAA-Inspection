/********************************************************************************
** Form generated from reading UI file 'ShowTotalHistgramGraphForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWTOTALHISTGRAMGRAPHFORM_H
#define UI_SHOWTOTALHISTGRAMGRAPHFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ShowTotalHistgramGraphForm
{
public:
    QLineEdit *lineEditNumCenter;
    QLineEdit *lineEditNumDev;
    QLabel *label;
    QLineEdit *lineEditAlgoRoot;
    QFrame *frame;
    QLabel *label_6;
    QLabel *label_2;
    QPushButton *pushButtonClose;
    QLineEdit *lineEditAlgoName;
    QLabel *label_7;
    QLineEdit *lineEditHistName;
    QLabel *label_8;
    QLineEdit *lineEditLibID;
    QLabel *label_5;
    QLineEdit *lineEditLibName;
    QLabel *label_4;
    QPushButton *pushButtonCalc;
    QLabel *label_9;
    QLabel *label_3;
    QFrame *frame_2;
    QToolButton *toolButtonThreshold1;
    QToolButton *toolButtonThreshold2;
    QPushButton *pushButtonCalc2;
    QPushButton *pushButtonCalcU;
    QLineEdit *lineEditThresh1;
    QLineEdit *lineEditThresh2;
    QLabel *label_10;
    QLineEdit *lineEditNumPercent;
    QPushButton *pushButtonCalcD;

    void setupUi(QDialog *ShowTotalHistgramGraphForm)
    {
        if (ShowTotalHistgramGraphForm->objectName().isEmpty())
            ShowTotalHistgramGraphForm->setObjectName("ShowTotalHistgramGraphForm");
        ShowTotalHistgramGraphForm->resize(731, 523);
        lineEditNumCenter = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditNumCenter->setObjectName("lineEditNumCenter");
        lineEditNumCenter->setGeometry(QRect(260, 400, 81, 20));
        lineEditNumCenter->setReadOnly(true);
        lineEditNumDev = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditNumDev->setObjectName("lineEditNumDev");
        lineEditNumDev->setGeometry(QRect(260, 450, 81, 20));
        lineEditNumDev->setReadOnly(true);
        label = new QLabel(ShowTotalHistgramGraphForm);
        label->setObjectName("label");
        label->setGeometry(QRect(260, 380, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditAlgoRoot = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditAlgoRoot->setObjectName("lineEditAlgoRoot");
        lineEditAlgoRoot->setGeometry(QRect(10, 390, 121, 20));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(192, 192, 192, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditAlgoRoot->setPalette(palette);
        lineEditAlgoRoot->setReadOnly(true);
        frame = new QFrame(ShowTotalHistgramGraphForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 711, 351));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        label_6 = new QLabel(ShowTotalHistgramGraphForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 370, 121, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(ShowTotalHistgramGraphForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 430, 81, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonClose = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(620, 470, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon);
        lineEditAlgoName = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditAlgoName->setObjectName("lineEditAlgoName");
        lineEditAlgoName->setGeometry(QRect(130, 390, 121, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditAlgoName->setPalette(palette1);
        lineEditAlgoName->setReadOnly(true);
        label_7 = new QLabel(ShowTotalHistgramGraphForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(130, 370, 121, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditHistName = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditHistName->setObjectName("lineEditHistName");
        lineEditHistName->setGeometry(QRect(10, 490, 241, 20));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditHistName->setPalette(palette2);
        lineEditHistName->setReadOnly(true);
        label_8 = new QLabel(ShowTotalHistgramGraphForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 470, 241, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLibID = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditLibID->setObjectName("lineEditLibID");
        lineEditLibID->setGeometry(QRect(10, 440, 51, 20));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditLibID->setPalette(palette3);
        lineEditLibID->setReadOnly(true);
        label_5 = new QLabel(ShowTotalHistgramGraphForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 420, 51, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLibName = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditLibName->setObjectName("lineEditLibName");
        lineEditLibName->setGeometry(QRect(60, 440, 191, 20));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditLibName->setPalette(palette4);
        lineEditLibName->setReadOnly(true);
        label_4 = new QLabel(ShowTotalHistgramGraphForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(60, 420, 191, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCalc = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonCalc->setObjectName("pushButtonCalc");
        pushButtonCalc->setGeometry(QRect(440, 430, 81, 21));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Calculator.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCalc->setIcon(icon1);
        label_9 = new QLabel(ShowTotalHistgramGraphForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(360, 450, 81, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(ShowTotalHistgramGraphForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(360, 480, 171, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(ShowTotalHistgramGraphForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(430, 370, 191, 31));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        toolButtonThreshold1 = new QToolButton(frame_2);
        toolButtonThreshold1->setObjectName("toolButtonThreshold1");
        toolButtonThreshold1->setGeometry(QRect(10, 10, 81, 21));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Chart.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonThreshold1->setIcon(icon2);
        toolButtonThreshold1->setCheckable(true);
        toolButtonThreshold1->setChecked(true);
        toolButtonThreshold1->setAutoExclusive(true);
        toolButtonThreshold1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButtonThreshold2 = new QToolButton(frame_2);
        toolButtonThreshold2->setObjectName("toolButtonThreshold2");
        toolButtonThreshold2->setGeometry(QRect(100, 10, 81, 21));
        toolButtonThreshold2->setIcon(icon2);
        toolButtonThreshold2->setCheckable(true);
        toolButtonThreshold2->setAutoExclusive(true);
        toolButtonThreshold2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pushButtonCalc2 = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonCalc2->setObjectName("pushButtonCalc2");
        pushButtonCalc2->setGeometry(QRect(530, 430, 81, 21));
        pushButtonCalc2->setIcon(icon1);
        pushButtonCalcU = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonCalcU->setObjectName("pushButtonCalcU");
        pushButtonCalcU->setGeometry(QRect(530, 450, 81, 21));
        pushButtonCalcU->setIcon(icon1);
        lineEditThresh1 = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditThresh1->setObjectName("lineEditThresh1");
        lineEditThresh1->setGeometry(QRect(440, 400, 81, 20));
        lineEditThresh2 = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditThresh2->setObjectName("lineEditThresh2");
        lineEditThresh2->setGeometry(QRect(530, 400, 81, 20));
        label_10 = new QLabel(ShowTotalHistgramGraphForm);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(360, 430, 81, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditNumPercent = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditNumPercent->setObjectName("lineEditNumPercent");
        lineEditNumPercent->setGeometry(QRect(530, 480, 81, 20));
        pushButtonCalcD = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonCalcD->setObjectName("pushButtonCalcD");
        pushButtonCalcD->setGeometry(QRect(440, 450, 81, 21));
        pushButtonCalcD->setIcon(icon1);

        retranslateUi(ShowTotalHistgramGraphForm);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(ShowTotalHistgramGraphForm);
    } // setupUi

    void retranslateUi(QDialog *ShowTotalHistgramGraphForm)
    {
        ShowTotalHistgramGraphForm->setWindowTitle(QCoreApplication::translate("ShowTotalHistgramGraphForm", "Show total Histgram Graph", nullptr));
        label->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\344\270\255\345\277\203\345\200\244", nullptr));
        label_6->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "AlgorithmRoot", nullptr));
        label_2->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\346\250\231\346\272\226\345\201\217\345\267\256", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_7->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "AlgorithmName", nullptr));
        label_8->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\343\203\222\343\202\271\343\203\210\343\202\260\343\203\251\343\203\240\345\220\215\347\247\260", nullptr));
        label_5->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\357\274\254\357\275\211\357\275\202\357\274\251\357\274\244", nullptr));
        label_4->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        pushButtonCalc->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\350\250\210\347\256\227\343\200\200\342\206\223", nullptr));
        label_9->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\346\255\243\350\246\217\345\210\206\345\270\203", nullptr));
        label_3->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\343\201\227\343\201\215\343\201\204\345\200\244\357\274\221\343\201\213\343\202\211\357\274\222\343\201\276\343\201\247\343\201\256\346\244\234\345\256\232\345\200\244\357\274\210\357\274\205\357\274\211", nullptr));
        toolButtonThreshold1->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\343\201\227\343\201\215\343\201\204\345\200\244\357\274\221", nullptr));
        toolButtonThreshold2->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\343\201\227\343\201\215\343\201\204\345\200\244\357\274\222", nullptr));
        pushButtonCalc2->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\350\250\210\347\256\227\343\200\200\342\206\221", nullptr));
        pushButtonCalcU->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\350\250\210\347\256\227\343\200\200\342\206\221", nullptr));
        label_10->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\345\256\237\347\270\276", nullptr));
        pushButtonCalcD->setText(QCoreApplication::translate("ShowTotalHistgramGraphForm", "\350\250\210\347\256\227\343\200\200\342\206\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowTotalHistgramGraphForm: public Ui_ShowTotalHistgramGraphForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWTOTALHISTGRAMGRAPHFORM_H
