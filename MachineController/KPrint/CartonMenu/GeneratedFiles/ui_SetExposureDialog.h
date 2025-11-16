/********************************************************************************
** Form generated from reading UI file 'SetExposureDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETEXPOSUREDIALOG_H
#define UI_SETEXPOSUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetExposureDialog
{
public:
    QPushButton *PushButtonClose;
    QFrame *frameTop;
    QLabel *labelTop;
    QPushButton *PushButtonSettingTop1;
    QPushButton *PushButtonSettingTop2;
    QPushButton *PushButtonSettingTop3;
    QPushButton *PushButtonSettingTopHolo;
    QFrame *frameBottom;
    QLabel *labelBottom;
    QPushButton *PushButtonSettingBottom2;
    QPushButton *PushButtonSettingBottom3;
    QPushButton *PushButtonSettingBottom1;
    QPushButton *PushButtonSettingBottomHolo;
    QFrame *frameMono;
    QLabel *labelMono;
    QPushButton *PushButtonSettingMono2;
    QPushButton *PushButtonSettingMono3;
    QPushButton *PushButtonSettingMono1;
    QPushButton *PushButtonSettingMonoHolo;

    void setupUi(QDialog *SetExposureDialog)
    {
        if (SetExposureDialog->objectName().isEmpty())
            SetExposureDialog->setObjectName("SetExposureDialog");
        SetExposureDialog->resize(633, 452);
        PushButtonClose = new QPushButton(SetExposureDialog);
        PushButtonClose->setObjectName("PushButtonClose");
        PushButtonClose->setGeometry(QRect(210, 380, 211, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font.setPointSize(24);
        PushButtonClose->setFont(font);
        PushButtonClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 10px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 220, 160, 255), stop:1 rgba(165, 140, 100, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 100, 100, 255), stop:1 rgba(141, 60, 60, 255));\n"
"}"));
        PushButtonClose->setCheckable(true);
        PushButtonClose->setAutoExclusive(true);
        PushButtonClose->setAutoDefault(false);
        PushButtonClose->setFlat(false);
        frameTop = new QFrame(SetExposureDialog);
        frameTop->setObjectName("frameTop");
        frameTop->setGeometry(QRect(10, 10, 611, 121));
        frameTop->setFrameShape(QFrame::Panel);
        frameTop->setFrameShadow(QFrame::Sunken);
        labelTop = new QLabel(frameTop);
        labelTop->setObjectName("labelTop");
        labelTop->setGeometry(QRect(30, 10, 401, 31));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        labelTop->setFont(font1);
        PushButtonSettingTop1 = new QPushButton(frameTop);
        PushButtonSettingTop1->setObjectName("PushButtonSettingTop1");
        PushButtonSettingTop1->setGeometry(QRect(10, 50, 121, 61));
        PushButtonSettingTop1->setFont(font);
        PushButtonSettingTop1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingTop1->setCheckable(true);
        PushButtonSettingTop1->setAutoExclusive(true);
        PushButtonSettingTop1->setAutoDefault(false);
        PushButtonSettingTop1->setFlat(false);
        PushButtonSettingTop2 = new QPushButton(frameTop);
        PushButtonSettingTop2->setObjectName("PushButtonSettingTop2");
        PushButtonSettingTop2->setGeometry(QRect(150, 50, 141, 61));
        PushButtonSettingTop2->setFont(font);
        PushButtonSettingTop2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingTop2->setCheckable(true);
        PushButtonSettingTop2->setAutoExclusive(true);
        PushButtonSettingTop2->setAutoDefault(false);
        PushButtonSettingTop2->setFlat(false);
        PushButtonSettingTop3 = new QPushButton(frameTop);
        PushButtonSettingTop3->setObjectName("PushButtonSettingTop3");
        PushButtonSettingTop3->setGeometry(QRect(310, 50, 141, 61));
        PushButtonSettingTop3->setFont(font);
        PushButtonSettingTop3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingTop3->setCheckable(true);
        PushButtonSettingTop3->setAutoExclusive(true);
        PushButtonSettingTop3->setAutoDefault(false);
        PushButtonSettingTop3->setFlat(false);
        PushButtonSettingTopHolo = new QPushButton(frameTop);
        PushButtonSettingTopHolo->setObjectName("PushButtonSettingTopHolo");
        PushButtonSettingTopHolo->setGeometry(QRect(460, 50, 141, 61));
        PushButtonSettingTopHolo->setFont(font);
        PushButtonSettingTopHolo->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingTopHolo->setCheckable(true);
        PushButtonSettingTopHolo->setAutoExclusive(true);
        PushButtonSettingTopHolo->setAutoDefault(false);
        PushButtonSettingTopHolo->setFlat(false);
        frameBottom = new QFrame(SetExposureDialog);
        frameBottom->setObjectName("frameBottom");
        frameBottom->setGeometry(QRect(10, 140, 611, 111));
        frameBottom->setFrameShape(QFrame::Panel);
        frameBottom->setFrameShadow(QFrame::Sunken);
        labelBottom = new QLabel(frameBottom);
        labelBottom->setObjectName("labelBottom");
        labelBottom->setGeometry(QRect(30, 0, 391, 31));
        labelBottom->setFont(font1);
        PushButtonSettingBottom2 = new QPushButton(frameBottom);
        PushButtonSettingBottom2->setObjectName("PushButtonSettingBottom2");
        PushButtonSettingBottom2->setGeometry(QRect(150, 40, 141, 61));
        PushButtonSettingBottom2->setFont(font);
        PushButtonSettingBottom2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingBottom2->setCheckable(true);
        PushButtonSettingBottom2->setAutoExclusive(true);
        PushButtonSettingBottom2->setAutoDefault(false);
        PushButtonSettingBottom2->setFlat(false);
        PushButtonSettingBottom3 = new QPushButton(frameBottom);
        PushButtonSettingBottom3->setObjectName("PushButtonSettingBottom3");
        PushButtonSettingBottom3->setGeometry(QRect(310, 40, 141, 61));
        PushButtonSettingBottom3->setFont(font);
        PushButtonSettingBottom3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingBottom3->setCheckable(true);
        PushButtonSettingBottom3->setAutoExclusive(true);
        PushButtonSettingBottom3->setAutoDefault(false);
        PushButtonSettingBottom3->setFlat(false);
        PushButtonSettingBottom1 = new QPushButton(frameBottom);
        PushButtonSettingBottom1->setObjectName("PushButtonSettingBottom1");
        PushButtonSettingBottom1->setGeometry(QRect(10, 40, 121, 61));
        PushButtonSettingBottom1->setFont(font);
        PushButtonSettingBottom1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingBottom1->setCheckable(true);
        PushButtonSettingBottom1->setAutoExclusive(true);
        PushButtonSettingBottom1->setAutoDefault(false);
        PushButtonSettingBottom1->setFlat(false);
        PushButtonSettingBottomHolo = new QPushButton(frameBottom);
        PushButtonSettingBottomHolo->setObjectName("PushButtonSettingBottomHolo");
        PushButtonSettingBottomHolo->setGeometry(QRect(460, 40, 141, 61));
        PushButtonSettingBottomHolo->setFont(font);
        PushButtonSettingBottomHolo->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingBottomHolo->setCheckable(true);
        PushButtonSettingBottomHolo->setAutoExclusive(true);
        PushButtonSettingBottomHolo->setAutoDefault(false);
        PushButtonSettingBottomHolo->setFlat(false);
        frameMono = new QFrame(SetExposureDialog);
        frameMono->setObjectName("frameMono");
        frameMono->setGeometry(QRect(10, 260, 611, 111));
        frameMono->setFrameShape(QFrame::Panel);
        frameMono->setFrameShadow(QFrame::Sunken);
        labelMono = new QLabel(frameMono);
        labelMono->setObjectName("labelMono");
        labelMono->setGeometry(QRect(30, 0, 391, 31));
        labelMono->setFont(font1);
        PushButtonSettingMono2 = new QPushButton(frameMono);
        PushButtonSettingMono2->setObjectName("PushButtonSettingMono2");
        PushButtonSettingMono2->setGeometry(QRect(150, 40, 141, 61));
        PushButtonSettingMono2->setFont(font);
        PushButtonSettingMono2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingMono2->setCheckable(true);
        PushButtonSettingMono2->setAutoExclusive(true);
        PushButtonSettingMono2->setAutoDefault(false);
        PushButtonSettingMono2->setFlat(false);
        PushButtonSettingMono3 = new QPushButton(frameMono);
        PushButtonSettingMono3->setObjectName("PushButtonSettingMono3");
        PushButtonSettingMono3->setGeometry(QRect(310, 40, 141, 61));
        PushButtonSettingMono3->setFont(font);
        PushButtonSettingMono3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingMono3->setCheckable(true);
        PushButtonSettingMono3->setAutoExclusive(true);
        PushButtonSettingMono3->setAutoDefault(false);
        PushButtonSettingMono3->setFlat(false);
        PushButtonSettingMono1 = new QPushButton(frameMono);
        PushButtonSettingMono1->setObjectName("PushButtonSettingMono1");
        PushButtonSettingMono1->setGeometry(QRect(10, 40, 121, 61));
        PushButtonSettingMono1->setFont(font);
        PushButtonSettingMono1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingMono1->setCheckable(true);
        PushButtonSettingMono1->setAutoExclusive(true);
        PushButtonSettingMono1->setAutoDefault(false);
        PushButtonSettingMono1->setFlat(false);
        PushButtonSettingMonoHolo = new QPushButton(frameMono);
        PushButtonSettingMonoHolo->setObjectName("PushButtonSettingMonoHolo");
        PushButtonSettingMonoHolo->setGeometry(QRect(460, 40, 141, 61));
        PushButtonSettingMonoHolo->setFont(font);
        PushButtonSettingMonoHolo->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonSettingMonoHolo->setCheckable(true);
        PushButtonSettingMonoHolo->setAutoExclusive(true);
        PushButtonSettingMonoHolo->setAutoDefault(false);
        PushButtonSettingMonoHolo->setFlat(false);

        retranslateUi(SetExposureDialog);

        PushButtonClose->setDefault(false);
        PushButtonSettingTop1->setDefault(false);
        PushButtonSettingTop2->setDefault(false);
        PushButtonSettingTop3->setDefault(false);
        PushButtonSettingTopHolo->setDefault(false);
        PushButtonSettingBottom2->setDefault(false);
        PushButtonSettingBottom3->setDefault(false);
        PushButtonSettingBottom1->setDefault(false);
        PushButtonSettingBottomHolo->setDefault(false);
        PushButtonSettingMono2->setDefault(false);
        PushButtonSettingMono3->setDefault(false);
        PushButtonSettingMono1->setDefault(false);
        PushButtonSettingMonoHolo->setDefault(false);


        QMetaObject::connectSlotsByName(SetExposureDialog);
    } // setupUi

    void retranslateUi(QDialog *SetExposureDialog)
    {
        SetExposureDialog->setWindowTitle(QCoreApplication::translate("SetExposureDialog", "Exposure", nullptr));
        PushButtonClose->setText(QCoreApplication::translate("SetExposureDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        labelTop->setText(QCoreApplication::translate("SetExposureDialog", "\345\211\215\345\201\264\343\202\253\343\203\241\343\203\251", nullptr));
        PushButtonSettingTop1->setText(QCoreApplication::translate("SetExposureDialog", "\344\270\200\350\210\254", nullptr));
        PushButtonSettingTop2->setText(QCoreApplication::translate("SetExposureDialog", "\345\205\211\346\262\242", nullptr));
        PushButtonSettingTop3->setText(QCoreApplication::translate("SetExposureDialog", "\350\222\270\347\235\200", nullptr));
        PushButtonSettingTopHolo->setText(QCoreApplication::translate("SetExposureDialog", "\343\203\233\343\203\255\343\202\260\343\203\251\343\203\240", nullptr));
        labelBottom->setText(QCoreApplication::translate("SetExposureDialog", "\343\201\206\343\201\227\343\202\215\345\201\264\343\202\253\343\203\241\343\203\251", nullptr));
        PushButtonSettingBottom2->setText(QCoreApplication::translate("SetExposureDialog", "\345\205\211\346\262\242", nullptr));
        PushButtonSettingBottom3->setText(QCoreApplication::translate("SetExposureDialog", "\350\222\270\347\235\200", nullptr));
        PushButtonSettingBottom1->setText(QCoreApplication::translate("SetExposureDialog", "\344\270\200\350\210\254", nullptr));
        PushButtonSettingBottomHolo->setText(QCoreApplication::translate("SetExposureDialog", "\343\203\233\343\203\255\343\202\260\343\203\251\343\203\240", nullptr));
        labelMono->setText(QCoreApplication::translate("SetExposureDialog", "\343\203\242\343\203\216\343\202\257\343\203\255\345\201\264\343\202\253\343\203\241\343\203\251", nullptr));
        PushButtonSettingMono2->setText(QCoreApplication::translate("SetExposureDialog", "\345\205\211\346\262\242", nullptr));
        PushButtonSettingMono3->setText(QCoreApplication::translate("SetExposureDialog", "\350\222\270\347\235\200", nullptr));
        PushButtonSettingMono1->setText(QCoreApplication::translate("SetExposureDialog", "\344\270\200\350\210\254", nullptr));
        PushButtonSettingMonoHolo->setText(QCoreApplication::translate("SetExposureDialog", "\343\203\233\343\203\255\343\202\260\343\203\251\343\203\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetExposureDialog: public Ui_SetExposureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETEXPOSUREDIALOG_H
