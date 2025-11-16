/********************************************************************************
** Form generated from reading UI file 'ShowTotalHistgramGraphForm.ui'
**
** Created: Sun May 26 19:16:59 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWTOTALHISTGRAMGRAPHFORM_H
#define UI_SHOWTOTALHISTGRAMGRAPHFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QToolButton>

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
            ShowTotalHistgramGraphForm->setObjectName(QString::fromUtf8("ShowTotalHistgramGraphForm"));
        ShowTotalHistgramGraphForm->resize(731, 523);
        lineEditNumCenter = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditNumCenter->setObjectName(QString::fromUtf8("lineEditNumCenter"));
        lineEditNumCenter->setGeometry(QRect(260, 400, 81, 20));
        lineEditNumCenter->setReadOnly(true);
        lineEditNumDev = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditNumDev->setObjectName(QString::fromUtf8("lineEditNumDev"));
        lineEditNumDev->setGeometry(QRect(260, 450, 81, 20));
        lineEditNumDev->setReadOnly(true);
        label = new QLabel(ShowTotalHistgramGraphForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 380, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditAlgoRoot = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditAlgoRoot->setObjectName(QString::fromUtf8("lineEditAlgoRoot"));
        lineEditAlgoRoot->setGeometry(QRect(10, 390, 121, 20));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(192, 192, 192, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lineEditAlgoRoot->setPalette(palette);
        lineEditAlgoRoot->setReadOnly(true);
        frame = new QFrame(ShowTotalHistgramGraphForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 711, 351));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        label_6 = new QLabel(ShowTotalHistgramGraphForm);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 370, 121, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(ShowTotalHistgramGraphForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 430, 81, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonClose = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(620, 470, 101, 41));
        pushButtonClose->setDefault(true);
        lineEditAlgoName = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditAlgoName->setObjectName(QString::fromUtf8("lineEditAlgoName"));
        lineEditAlgoName->setGeometry(QRect(130, 390, 121, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lineEditAlgoName->setPalette(palette1);
        lineEditAlgoName->setReadOnly(true);
        label_7 = new QLabel(ShowTotalHistgramGraphForm);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(130, 370, 121, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditHistName = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditHistName->setObjectName(QString::fromUtf8("lineEditHistName"));
        lineEditHistName->setGeometry(QRect(10, 490, 241, 20));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lineEditHistName->setPalette(palette2);
        lineEditHistName->setReadOnly(true);
        label_8 = new QLabel(ShowTotalHistgramGraphForm);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 470, 241, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLibID = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditLibID->setObjectName(QString::fromUtf8("lineEditLibID"));
        lineEditLibID->setGeometry(QRect(10, 440, 51, 20));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lineEditLibID->setPalette(palette3);
        lineEditLibID->setReadOnly(true);
        label_5 = new QLabel(ShowTotalHistgramGraphForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 420, 51, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditLibName = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditLibName->setObjectName(QString::fromUtf8("lineEditLibName"));
        lineEditLibName->setGeometry(QRect(60, 440, 191, 20));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        lineEditLibName->setPalette(palette4);
        lineEditLibName->setReadOnly(true);
        label_4 = new QLabel(ShowTotalHistgramGraphForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 420, 191, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCalc = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonCalc->setObjectName(QString::fromUtf8("pushButtonCalc"));
        pushButtonCalc->setGeometry(QRect(440, 430, 81, 21));
        label_9 = new QLabel(ShowTotalHistgramGraphForm);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(360, 450, 81, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(ShowTotalHistgramGraphForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(360, 480, 171, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(ShowTotalHistgramGraphForm);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(430, 370, 191, 31));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        toolButtonThreshold1 = new QToolButton(frame_2);
        toolButtonThreshold1->setObjectName(QString::fromUtf8("toolButtonThreshold1"));
        toolButtonThreshold1->setGeometry(QRect(10, 10, 81, 21));
        toolButtonThreshold1->setCheckable(true);
        toolButtonThreshold1->setChecked(true);
        toolButtonThreshold1->setAutoExclusive(true);
        toolButtonThreshold2 = new QToolButton(frame_2);
        toolButtonThreshold2->setObjectName(QString::fromUtf8("toolButtonThreshold2"));
        toolButtonThreshold2->setGeometry(QRect(100, 10, 81, 21));
        toolButtonThreshold2->setCheckable(true);
        toolButtonThreshold2->setAutoExclusive(true);
        pushButtonCalc2 = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonCalc2->setObjectName(QString::fromUtf8("pushButtonCalc2"));
        pushButtonCalc2->setGeometry(QRect(530, 430, 81, 21));
        pushButtonCalcU = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonCalcU->setObjectName(QString::fromUtf8("pushButtonCalcU"));
        pushButtonCalcU->setGeometry(QRect(530, 450, 81, 21));
        lineEditThresh1 = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditThresh1->setObjectName(QString::fromUtf8("lineEditThresh1"));
        lineEditThresh1->setGeometry(QRect(440, 400, 81, 20));
        lineEditThresh2 = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditThresh2->setObjectName(QString::fromUtf8("lineEditThresh2"));
        lineEditThresh2->setGeometry(QRect(530, 400, 81, 20));
        label_10 = new QLabel(ShowTotalHistgramGraphForm);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(360, 430, 81, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditNumPercent = new QLineEdit(ShowTotalHistgramGraphForm);
        lineEditNumPercent->setObjectName(QString::fromUtf8("lineEditNumPercent"));
        lineEditNumPercent->setGeometry(QRect(530, 480, 81, 20));
        pushButtonCalcD = new QPushButton(ShowTotalHistgramGraphForm);
        pushButtonCalcD->setObjectName(QString::fromUtf8("pushButtonCalcD"));
        pushButtonCalcD->setGeometry(QRect(440, 450, 81, 21));

        retranslateUi(ShowTotalHistgramGraphForm);

        QMetaObject::connectSlotsByName(ShowTotalHistgramGraphForm);
    } // setupUi

    void retranslateUi(QDialog *ShowTotalHistgramGraphForm)
    {
        ShowTotalHistgramGraphForm->setWindowTitle(QApplication::translate("ShowTotalHistgramGraphForm", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\344\270\255\345\277\203\345\200\244", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ShowTotalHistgramGraphForm", "AlgorithmRoot", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\346\250\231\346\272\226\345\201\217\345\267\256", 0, QApplication::UnicodeUTF8));
        pushButtonClose->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\351\226\211\343\201\230\343\202\213", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ShowTotalHistgramGraphForm", "AlgorithmName", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\343\203\222\343\202\271\343\203\210\343\202\260\343\203\251\343\203\240\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\357\274\254\357\275\211\357\275\202\357\274\251\357\274\244", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", 0, QApplication::UnicodeUTF8));
        pushButtonCalc->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\350\250\210\347\256\227\343\200\200\342\206\223", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\346\255\243\350\246\217\345\210\206\345\270\203", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\343\201\227\343\201\215\343\201\204\345\200\244\357\274\221\343\201\213\343\202\211\357\274\222\343\201\276\343\201\247\343\201\256\346\244\234\345\256\232\345\200\244\357\274\210\357\274\205\357\274\211", 0, QApplication::UnicodeUTF8));
        toolButtonThreshold1->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\343\201\227\343\201\215\343\201\204\345\200\244\357\274\221", 0, QApplication::UnicodeUTF8));
        toolButtonThreshold2->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\343\201\227\343\201\215\343\201\204\345\200\244\357\274\222", 0, QApplication::UnicodeUTF8));
        pushButtonCalc2->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\350\250\210\347\256\227\343\200\200\342\206\221", 0, QApplication::UnicodeUTF8));
        pushButtonCalcU->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\350\250\210\347\256\227\343\200\200\342\206\221", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\345\256\237\347\270\276", 0, QApplication::UnicodeUTF8));
        pushButtonCalcD->setText(QApplication::translate("ShowTotalHistgramGraphForm", "\350\250\210\347\256\227\343\200\200\342\206\223", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ShowTotalHistgramGraphForm: public Ui_ShowTotalHistgramGraphForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWTOTALHISTGRAMGRAPHFORM_H
