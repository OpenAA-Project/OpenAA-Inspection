/********************************************************************************
** Form generated from reading UI file 'LightingManager.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHTINGMANAGER_H
#define UI_LIGHTINGMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LightingManagerClass
{
public:
    QGroupBox *gbMainFrame;
    QPushButton *pbResetTotalSumHour;
    QLCDNumber *lcdTotalSumHour;
    QProgressBar *pgbElapsedTime;
    QLabel *label;
    QLabel *lbMainMessage;
    QLCDNumber *lcdElapsedTime;
    QPushButton *pbDetail;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_8;
    QFrame *frame;
    QPushButton *pbShowMessage;
    QCheckBox *chkIsShowWidget;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *sbWarmMinute;
    QSpinBox *sbChangeHour;
    QLabel *label_6;
    QLabel *label_7;
    QCheckBox *chkIsCloseWidget;
    QGroupBox *gbIsStartExe;
    QGridLayout *gridLayout;
    QLineEdit *leStartExe;
    QToolButton *tbStartExe;

    void setupUi(QWidget *LightingManagerClass)
    {
        if (LightingManagerClass->objectName().isEmpty())
            LightingManagerClass->setObjectName("LightingManagerClass");
        LightingManagerClass->resize(530, 480);
        gbMainFrame = new QGroupBox(LightingManagerClass);
        gbMainFrame->setObjectName("gbMainFrame");
        gbMainFrame->setGeometry(QRect(-8, 0, 541, 271));
        gbMainFrame->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	background-color: qlineargradient( x1: 0, y1: 0, x2:0.5, x2: 0.5, stop: 0 #FF92BB, stop: 1 white);\n"
"}\n"
""));
        pbResetTotalSumHour = new QPushButton(gbMainFrame);
        pbResetTotalSumHour->setObjectName("pbResetTotalSumHour");
        pbResetTotalSumHour->setGeometry(QRect(400, 150, 121, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(11);
        font.setBold(true);
        pbResetTotalSumHour->setFont(font);
        pbResetTotalSumHour->setStyleSheet(QString::fromUtf8("font-family: MS UI Gothic;font-size: 11pt;font-weight: bold;"));
        lcdTotalSumHour = new QLCDNumber(gbMainFrame);
        lcdTotalSumHour->setObjectName("lcdTotalSumHour");
        lcdTotalSumHour->setGeometry(QRect(188, 200, 131, 41));
        lcdTotalSumHour->setFrameShape(QFrame::Box);
        lcdTotalSumHour->setFrameShadow(QFrame::Sunken);
        lcdTotalSumHour->setDigitCount(6);
        lcdTotalSumHour->setSegmentStyle(QLCDNumber::Filled);
        pgbElapsedTime = new QProgressBar(gbMainFrame);
        pgbElapsedTime->setObjectName("pgbElapsedTime");
        pgbElapsedTime->setGeometry(QRect(18, 90, 511, 41));
        pgbElapsedTime->setValue(0);
        label = new QLabel(gbMainFrame);
        label->setObjectName("label");
        label->setGeometry(QRect(8, 200, 171, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font1.setPointSize(20);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("font-family: MS UI Gothic;font-size: 20pt;font-weight: bold;"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lbMainMessage = new QLabel(gbMainFrame);
        lbMainMessage->setObjectName("lbMainMessage");
        lbMainMessage->setGeometry(QRect(8, 20, 531, 41));
        lbMainMessage->setFont(font1);
        lbMainMessage->setStyleSheet(QString::fromUtf8("font-family: MS UI Gothic;font-size: 20pt;font-weight: bold;"));
        lbMainMessage->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lcdElapsedTime = new QLCDNumber(gbMainFrame);
        lcdElapsedTime->setObjectName("lcdElapsedTime");
        lcdElapsedTime->setGeometry(QRect(188, 140, 91, 41));
        lcdElapsedTime->setFrameShape(QFrame::Box);
        lcdElapsedTime->setFrameShadow(QFrame::Sunken);
        lcdElapsedTime->setDigitCount(4);
        lcdElapsedTime->setSegmentStyle(QLCDNumber::Filled);
        pbDetail = new QPushButton(gbMainFrame);
        pbDetail->setObjectName("pbDetail");
        pbDetail->setGeometry(QRect(448, 220, 75, 31));
        pbDetail->setCheckable(true);
        label_3 = new QLabel(gbMainFrame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(290, 140, 111, 41));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("font-family: MS UI Gothic;font-size: 20pt;font-weight: bold;"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(gbMainFrame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(328, 200, 71, 41));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("font-family: MS UI Gothic;font-size: 20pt;font-weight: bold;"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(gbMainFrame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(8, 140, 171, 41));
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("font-family: MS UI Gothic;font-size: 20pt;font-weight: bold;"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        frame = new QFrame(LightingManagerClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 280, 511, 191));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        pbShowMessage = new QPushButton(frame);
        pbShowMessage->setObjectName("pbShowMessage");
        pbShowMessage->setGeometry(QRect(190, 140, 131, 41));
        chkIsShowWidget = new QCheckBox(frame);
        chkIsShowWidget->setObjectName("chkIsShowWidget");
        chkIsShowWidget->setGeometry(QRect(270, 20, 231, 17));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 20, 131, 16));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 50, 131, 16));
        sbWarmMinute = new QSpinBox(frame);
        sbWarmMinute->setObjectName("sbWarmMinute");
        sbWarmMinute->setGeometry(QRect(150, 20, 61, 22));
        sbWarmMinute->setMaximum(999);
        sbChangeHour = new QSpinBox(frame);
        sbChangeHour->setObjectName("sbChangeHour");
        sbChangeHour->setGeometry(QRect(150, 50, 61, 22));
        sbChangeHour->setMaximum(999999);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(220, 20, 41, 16));
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(220, 50, 41, 16));
        chkIsCloseWidget = new QCheckBox(frame);
        chkIsCloseWidget->setObjectName("chkIsCloseWidget");
        chkIsCloseWidget->setGeometry(QRect(270, 50, 231, 17));
        gbIsStartExe = new QGroupBox(frame);
        gbIsStartExe->setObjectName("gbIsStartExe");
        gbIsStartExe->setGeometry(QRect(10, 80, 491, 54));
        gbIsStartExe->setCheckable(true);
        gridLayout = new QGridLayout(gbIsStartExe);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        leStartExe = new QLineEdit(gbIsStartExe);
        leStartExe->setObjectName("leStartExe");
        leStartExe->setReadOnly(true);

        gridLayout->addWidget(leStartExe, 0, 0, 1, 1);

        tbStartExe = new QToolButton(gbIsStartExe);
        tbStartExe->setObjectName("tbStartExe");

        gridLayout->addWidget(tbStartExe, 0, 1, 1, 1);


        retranslateUi(LightingManagerClass);

        QMetaObject::connectSlotsByName(LightingManagerClass);
    } // setupUi

    void retranslateUi(QWidget *LightingManagerClass)
    {
        LightingManagerClass->setWindowTitle(QCoreApplication::translate("LightingManagerClass", "LightingManager", nullptr));
        pbResetTotalSumHour->setText(QCoreApplication::translate("LightingManagerClass", "\347\264\257\350\250\210\346\231\202\351\226\223\343\203\252\343\202\273\343\203\203\343\203\210", nullptr));
        label->setText(QCoreApplication::translate("LightingManagerClass", "\347\264\257\350\250\210\346\231\202\351\226\223", nullptr));
        lbMainMessage->setText(QCoreApplication::translate("LightingManagerClass", "\347\205\247\346\230\216\343\201\214\345\256\211\345\256\232\343\201\231\343\202\213\343\201\276\343\201\247\343\201\227\343\201\260\343\202\211\343\201\217\343\201\212\345\276\205\343\201\241\344\270\213\343\201\225\343\201\204\357\274\216\357\274\216\357\274\216", nullptr));
        pbDetail->setText(QCoreApplication::translate("LightingManagerClass", "\350\251\263\347\264\260", nullptr));
        label_3->setText(QCoreApplication::translate("LightingManagerClass", "\345\210\206\343\201\247\345\256\214\344\272\206", nullptr));
        label_2->setText(QCoreApplication::translate("LightingManagerClass", "\346\231\202\351\226\223", nullptr));
        label_8->setText(QCoreApplication::translate("LightingManagerClass", "\343\201\202\343\201\250", nullptr));
        pbShowMessage->setText(QCoreApplication::translate("LightingManagerClass", "\343\203\241\343\203\203\343\202\273\343\203\274\343\202\270\350\241\250\347\244\272\343\203\206\343\202\271\343\203\210", nullptr));
        chkIsShowWidget->setText(QCoreApplication::translate("LightingManagerClass", "\350\265\267\345\213\225\346\231\202\343\201\253\347\224\273\351\235\242\343\202\222\350\241\250\347\244\272\343\201\231\343\202\213", nullptr));
        label_4->setText(QCoreApplication::translate("LightingManagerClass", "\346\232\226\346\251\237\346\231\202\351\226\223", nullptr));
        label_5->setText(QCoreApplication::translate("LightingManagerClass", "\347\205\247\346\230\216\344\272\244\346\217\233\347\233\256\345\256\211\346\231\202\351\226\223", nullptr));
        label_6->setText(QCoreApplication::translate("LightingManagerClass", "\345\210\206", nullptr));
        label_7->setText(QCoreApplication::translate("LightingManagerClass", "\346\231\202\351\226\223", nullptr));
        chkIsCloseWidget->setText(QCoreApplication::translate("LightingManagerClass", "\346\232\226\346\251\237\347\265\202\344\272\206\345\276\214\343\200\201\347\224\273\351\235\242\343\202\222\351\226\211\343\201\230\343\202\213", nullptr));
        gbIsStartExe->setTitle(QCoreApplication::translate("LightingManagerClass", "\346\232\226\346\260\227\347\265\202\344\272\206\345\276\214\343\200\201\350\265\267\345\213\225\343\201\231\343\202\213\343\202\275\343\203\225\343\203\210\343\202\222\346\214\207\345\256\232\343\201\231\343\202\213", nullptr));
        tbStartExe->setText(QCoreApplication::translate("LightingManagerClass", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LightingManagerClass: public Ui_LightingManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHTINGMANAGER_H
