/********************************************************************************
** Form generated from reading UI file 'HookMeasureForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOOKMEASUREFORM_H
#define UI_HOOKMEASUREFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_HookMeasureForm
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QToolButton *toolButtonCircle3;
    QToolButton *toolButtonIsolation;
    QToolButton *toolButtonPolyLine;
    QToolButton *toolButtonPoint2Point;
    QToolButton *toolButtonArc;
    QToolButton *toolButtonAngle;
    QToolButton *toolButtonRectangle;
    QToolButton *toolButtonCircle;
    QToolButton *toolButtonFoldedLines;
    QToolButton *toolButtonCenterCircle;
    QWidget *page_2;

    void setupUi(GUIFormBase *HookMeasureForm)
    {
        if (HookMeasureForm->objectName().isEmpty())
            HookMeasureForm->setObjectName("HookMeasureForm");
        HookMeasureForm->resize(450, 43);
        stackedWidget = new QStackedWidget(HookMeasureForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 451, 41));
        page = new QWidget();
        page->setObjectName("page");
        toolButtonCircle3 = new QToolButton(page);
        toolButtonCircle3->setObjectName("toolButtonCircle3");
        toolButtonCircle3->setGeometry(QRect(360, 0, 42, 42));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/Circle2N.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/Circle2S.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonCircle3->setIcon(icon);
        toolButtonCircle3->setIconSize(QSize(42, 42));
        toolButtonCircle3->setCheckable(true);
        toolButtonCircle3->setAutoExclusive(true);
        toolButtonIsolation = new QToolButton(page);
        toolButtonIsolation->setObjectName("toolButtonIsolation");
        toolButtonIsolation->setGeometry(QRect(405, 0, 42, 42));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/ParallelLinesN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon1.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/ParallelLinesS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonIsolation->setIcon(icon1);
        toolButtonIsolation->setIconSize(QSize(42, 42));
        toolButtonIsolation->setCheckable(true);
        toolButtonIsolation->setAutoExclusive(true);
        toolButtonPolyLine = new QToolButton(page);
        toolButtonPolyLine->setObjectName("toolButtonPolyLine");
        toolButtonPolyLine->setGeometry(QRect(270, 0, 42, 42));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/MPolygonN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon2.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/MPolygonS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonPolyLine->setIcon(icon2);
        toolButtonPolyLine->setIconSize(QSize(42, 42));
        toolButtonPolyLine->setCheckable(true);
        toolButtonPolyLine->setAutoExclusive(true);
        toolButtonPoint2Point = new QToolButton(page);
        toolButtonPoint2Point->setObjectName("toolButtonPoint2Point");
        toolButtonPoint2Point->setGeometry(QRect(0, 0, 42, 42));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/StraightLineN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon3.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/StraightLineS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonPoint2Point->setIcon(icon3);
        toolButtonPoint2Point->setIconSize(QSize(42, 42));
        toolButtonPoint2Point->setCheckable(true);
        toolButtonPoint2Point->setChecked(true);
        toolButtonPoint2Point->setAutoExclusive(true);
        toolButtonArc = new QToolButton(page);
        toolButtonArc->setObjectName("toolButtonArc");
        toolButtonArc->setGeometry(QRect(135, 0, 42, 42));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/CrcularArcN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon4.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/CrcularArcS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonArc->setIcon(icon4);
        toolButtonArc->setIconSize(QSize(42, 42));
        toolButtonArc->setCheckable(true);
        toolButtonArc->setAutoExclusive(true);
        toolButtonAngle = new QToolButton(page);
        toolButtonAngle->setObjectName("toolButtonAngle");
        toolButtonAngle->setGeometry(QRect(180, 0, 42, 42));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/AngleN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon5.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/AngleS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonAngle->setIcon(icon5);
        toolButtonAngle->setIconSize(QSize(42, 42));
        toolButtonAngle->setCheckable(true);
        toolButtonAngle->setAutoExclusive(true);
        toolButtonRectangle = new QToolButton(page);
        toolButtonRectangle->setObjectName("toolButtonRectangle");
        toolButtonRectangle->setGeometry(QRect(225, 0, 42, 42));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/RectangleN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon6.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/RectangleS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonRectangle->setIcon(icon6);
        toolButtonRectangle->setIconSize(QSize(42, 42));
        toolButtonRectangle->setCheckable(true);
        toolButtonRectangle->setAutoExclusive(true);
        toolButtonCircle = new QToolButton(page);
        toolButtonCircle->setObjectName("toolButtonCircle");
        toolButtonCircle->setGeometry(QRect(315, 0, 42, 42));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/Circle1N.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon7.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/Circle1S.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonCircle->setIcon(icon7);
        toolButtonCircle->setIconSize(QSize(42, 42));
        toolButtonCircle->setCheckable(true);
        toolButtonCircle->setAutoExclusive(true);
        toolButtonFoldedLines = new QToolButton(page);
        toolButtonFoldedLines->setObjectName("toolButtonFoldedLines");
        toolButtonFoldedLines->setGeometry(QRect(45, 0, 42, 42));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/BrokenLineN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon8.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/BrokenLineS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonFoldedLines->setIcon(icon8);
        toolButtonFoldedLines->setIconSize(QSize(42, 42));
        toolButtonFoldedLines->setCheckable(true);
        toolButtonFoldedLines->setAutoExclusive(true);
        toolButtonCenterCircle = new QToolButton(page);
        toolButtonCenterCircle->setObjectName("toolButtonCenterCircle");
        toolButtonCenterCircle->setGeometry(QRect(90, 0, 42, 42));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/CircleTwoPointsN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon9.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/CircleTwoPointsS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonCenterCircle->setIcon(icon9);
        toolButtonCenterCircle->setIconSize(QSize(42, 42));
        toolButtonCenterCircle->setCheckable(true);
        toolButtonCenterCircle->setAutoExclusive(true);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        retranslateUi(HookMeasureForm);

        QMetaObject::connectSlotsByName(HookMeasureForm);
    } // setupUi

    void retranslateUi(GUIFormBase *HookMeasureForm)
    {
        HookMeasureForm->setWindowTitle(QCoreApplication::translate("HookMeasureForm", "\350\250\210\346\270\254\343\201\256\347\250\256\351\241\236", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonCircle3->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\345\206\206\342\221\241</p><p>\345\206\206\343\201\256\345\215\212\345\276\204\343\203\273\345\206\206\345\221\250\343\203\273\351\235\242\347\251\215\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231\357\274\210\345\206\206\345\221\250\357\274\223\347\202\271\357\274\211</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonCircle3->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonIsolation->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\345\271\263\350\241\214\347\267\232\350\267\235\351\233\242</p><p>\345\271\263\350\241\214\347\267\232\343\201\256\350\267\235\351\233\242\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonIsolation->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonPolyLine->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\345\244\232\350\247\222\345\275\242</p><p>\345\244\232\350\247\222\345\275\242\343\201\256\345\206\206\345\221\250\343\203\273\351\235\242\347\251\215\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonPolyLine->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonPoint2Point->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\347\233\264\347\267\232</p><p>2\347\202\271\351\226\223\343\201\256\350\267\235\351\233\242\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonPoint2Point->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonArc->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\345\206\206\345\274\247</p><p>\345\206\206\345\274\247\343\201\256\351\225\267\343\201\225\343\200\201\345\215\212\345\276\204\343\200\201\350\247\222\345\272\246\343\200\201\351\235\242\347\251\215\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonArc->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonAngle->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\350\247\222\345\272\246</p><p>\350\247\222\345\272\246\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonAngle->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonRectangle->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\351\225\267\346\226\271\345\275\242</p><p>\351\225\267\346\226\271\345\275\242\343\201\256\351\225\267\343\201\225\357\274\210\347\270\246\343\203\273\346\250\252\357\274\211\343\203\273\345\221\250\351\225\267\343\203\273\351\235\242\347\251\215\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonRectangle->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonCircle->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\345\206\206\342\221\240</p><p>\345\206\206\343\201\256\345\215\212\345\276\204\343\203\273\345\206\206\345\221\250\343\203\273\351\235\242\347\251\215\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231\357\274\210\347\233\264\345\276\204\357\274\222\347\202\271\357\274\211</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonCircle->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonFoldedLines->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\346\212\230\343\202\214\347\267\232</p><p>\350\244\207\346\225\260\347\202\271\343\201\256\350\267\235\351\233\242\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonFoldedLines->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonCenterCircle->setToolTip(QCoreApplication::translate("HookMeasureForm", "<html><head/><body><p>\345\206\206\345\277\2032\347\202\271\351\226\223\350\267\235\351\233\242</p><p>2\343\201\244\343\201\256\345\206\206\345\277\203\351\226\223\343\201\256\350\267\235\351\233\242\343\200\201\345\206\206\343\201\256\345\215\212\345\276\204\343\200\201\345\206\206\345\221\250\343\200\201\351\235\242\347\251\215\343\202\222\346\270\254\345\256\232\343\201\227\343\201\276\343\201\231</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonCenterCircle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HookMeasureForm: public Ui_HookMeasureForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOOKMEASUREFORM_H
