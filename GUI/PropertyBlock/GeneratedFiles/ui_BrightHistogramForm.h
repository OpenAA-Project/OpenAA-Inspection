/********************************************************************************
** Form generated from reading UI file 'BrightHistogramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRIGHTHISTOGRAMFORM_H
#define UI_BRIGHTHISTOGRAMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BrightHistogramFormClass
{
public:
    QFrame *frameLineGraph;
    QLabel *label_7;
    QSpinBox *EditPickupH;
    QSpinBox *EditPickupL;
    QLabel *label_8;
    QPushButton *ButtonClose;
    QPushButton *ButtonReflect;

    void setupUi(QDialog *BrightHistogramFormClass)
    {
        if (BrightHistogramFormClass->objectName().isEmpty())
            BrightHistogramFormClass->setObjectName("BrightHistogramFormClass");
        BrightHistogramFormClass->resize(752, 532);
        frameLineGraph = new QFrame(BrightHistogramFormClass);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(20, 20, 711, 381));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        label_7 = new QLabel(BrightHistogramFormClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(30, 470, 161, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(BrightHistogramFormClass);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(200, 500, 61, 22));
        EditPickupH->setMaximum(255);
        EditPickupL = new QSpinBox(BrightHistogramFormClass);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(200, 470, 61, 22));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(192, 192, 192, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditPickupL->setPalette(palette);
        EditPickupL->setMaximum(255);
        label_8 = new QLabel(BrightHistogramFormClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 500, 161, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonClose = new QPushButton(BrightHistogramFormClass);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(540, 490, 171, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonClose->setIcon(icon);
        ButtonReflect = new QPushButton(BrightHistogramFormClass);
        ButtonReflect->setObjectName("ButtonReflect");
        ButtonReflect->setGeometry(QRect(540, 440, 171, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Reflection.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonReflect->setIcon(icon1);

        retranslateUi(BrightHistogramFormClass);

        QMetaObject::connectSlotsByName(BrightHistogramFormClass);
    } // setupUi

    void retranslateUi(QDialog *BrightHistogramFormClass)
    {
        BrightHistogramFormClass->setWindowTitle(QCoreApplication::translate("BrightHistogramFormClass", "BrightHistogramForm", nullptr));
        label_7->setText(QCoreApplication::translate("BrightHistogramFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        label_8->setText(QCoreApplication::translate("BrightHistogramFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        ButtonClose->setText(QCoreApplication::translate("BrightHistogramFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonReflect->setText(QCoreApplication::translate("BrightHistogramFormClass", "\345\217\215\346\230\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BrightHistogramFormClass: public Ui_BrightHistogramFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRIGHTHISTOGRAMFORM_H
