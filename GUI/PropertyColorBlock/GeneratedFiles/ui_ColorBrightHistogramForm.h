/********************************************************************************
** Form generated from reading UI file 'ColorBrightHistogramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORBRIGHTHISTOGRAMFORM_H
#define UI_COLORBRIGHTHISTOGRAMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ColorBrightHistogramFormClass
{
public:
    QFrame *frameLineGraph;
    QPushButton *ButtonClose;
    QPushButton *ButtonReflect;
    QFrame *frame;
    QLabel *label_7;
    QSpinBox *EditPickupBL;
    QToolButton *toolButtonL2;
    QLabel *label_8;
    QToolButton *toolButtonL3;
    QSpinBox *EditPickupGH;
    QSpinBox *EditPickupRH;
    QSpinBox *EditPickupRL;
    QSpinBox *EditPickupBH;
    QToolButton *toolButtonL1;
    QSpinBox *EditPickupGL;

    void setupUi(QDialog *ColorBrightHistogramFormClass)
    {
        if (ColorBrightHistogramFormClass->objectName().isEmpty())
            ColorBrightHistogramFormClass->setObjectName("ColorBrightHistogramFormClass");
        ColorBrightHistogramFormClass->resize(752, 527);
        frameLineGraph = new QFrame(ColorBrightHistogramFormClass);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(20, 20, 711, 381));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        ButtonClose = new QPushButton(ColorBrightHistogramFormClass);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(540, 470, 171, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonClose->setIcon(icon);
        ButtonReflect = new QPushButton(ColorBrightHistogramFormClass);
        ButtonReflect->setObjectName("ButtonReflect");
        ButtonReflect->setGeometry(QRect(540, 420, 171, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Reflection.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonReflect->setIcon(icon1);
        frame = new QFrame(ColorBrightHistogramFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(170, 410, 361, 111));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 50, 111, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupBL = new QSpinBox(frame);
        EditPickupBL->setObjectName("EditPickupBL");
        EditPickupBL->setGeometry(QRect(280, 50, 61, 22));
        EditPickupBL->setMaximum(255);
        toolButtonL2 = new QToolButton(frame);
        toolButtonL2->setObjectName("toolButtonL2");
        toolButtonL2->setGeometry(QRect(210, 10, 61, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Green.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonL2->setIcon(icon2);
        toolButtonL2->setCheckable(true);
        toolButtonL2->setChecked(false);
        toolButtonL2->setAutoExclusive(true);
        toolButtonL2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 80, 111, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        toolButtonL3 = new QToolButton(frame);
        toolButtonL3->setObjectName("toolButtonL3");
        toolButtonL3->setGeometry(QRect(280, 10, 61, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Blue.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonL3->setIcon(icon3);
        toolButtonL3->setCheckable(true);
        toolButtonL3->setAutoExclusive(true);
        toolButtonL3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        EditPickupGH = new QSpinBox(frame);
        EditPickupGH->setObjectName("EditPickupGH");
        EditPickupGH->setGeometry(QRect(210, 80, 61, 22));
        EditPickupGH->setMaximum(255);
        EditPickupRH = new QSpinBox(frame);
        EditPickupRH->setObjectName("EditPickupRH");
        EditPickupRH->setGeometry(QRect(140, 80, 61, 22));
        EditPickupRH->setMaximum(255);
        EditPickupRL = new QSpinBox(frame);
        EditPickupRL->setObjectName("EditPickupRL");
        EditPickupRL->setGeometry(QRect(140, 50, 61, 22));
        EditPickupRL->setMaximum(255);
        EditPickupBH = new QSpinBox(frame);
        EditPickupBH->setObjectName("EditPickupBH");
        EditPickupBH->setGeometry(QRect(280, 80, 61, 22));
        EditPickupBH->setMaximum(255);
        toolButtonL1 = new QToolButton(frame);
        toolButtonL1->setObjectName("toolButtonL1");
        toolButtonL1->setGeometry(QRect(140, 10, 61, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Red.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonL1->setIcon(icon4);
        toolButtonL1->setCheckable(true);
        toolButtonL1->setChecked(true);
        toolButtonL1->setAutoExclusive(true);
        toolButtonL1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        EditPickupGL = new QSpinBox(frame);
        EditPickupGL->setObjectName("EditPickupGL");
        EditPickupGL->setGeometry(QRect(210, 50, 61, 22));
        EditPickupGL->setMaximum(255);

        retranslateUi(ColorBrightHistogramFormClass);

        QMetaObject::connectSlotsByName(ColorBrightHistogramFormClass);
    } // setupUi

    void retranslateUi(QDialog *ColorBrightHistogramFormClass)
    {
        ColorBrightHistogramFormClass->setWindowTitle(QCoreApplication::translate("ColorBrightHistogramFormClass", "ColorBrightHistogramForm", nullptr));
        ButtonClose->setText(QCoreApplication::translate("ColorBrightHistogramFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonReflect->setText(QCoreApplication::translate("ColorBrightHistogramFormClass", "\345\217\215\346\230\240", nullptr));
        label_7->setText(QCoreApplication::translate("ColorBrightHistogramFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        toolButtonL2->setText(QCoreApplication::translate("ColorBrightHistogramFormClass", "L2(G)", nullptr));
        label_8->setText(QCoreApplication::translate("ColorBrightHistogramFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        toolButtonL3->setText(QCoreApplication::translate("ColorBrightHistogramFormClass", "L3(B)", nullptr));
        toolButtonL1->setText(QCoreApplication::translate("ColorBrightHistogramFormClass", "L1(R)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ColorBrightHistogramFormClass: public Ui_ColorBrightHistogramFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORBRIGHTHISTOGRAMFORM_H
