/********************************************************************************
** Form generated from reading UI file 'BrightHistogramDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRIGHTHISTOGRAMDIALOG_H
#define UI_BRIGHTHISTOGRAMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BrightHistogramDialog
{
public:
    QPushButton *ButtonClose;
    QLabel *label_7;
    QSpinBox *EditPickupL;
    QFrame *frameLineGraph;
    QSpinBox *EditPickupH;
    QPushButton *ButtonReflect;
    QLabel *label_8;

    void setupUi(QDialog *BrightHistogramDialog)
    {
        if (BrightHistogramDialog->objectName().isEmpty())
            BrightHistogramDialog->setObjectName(QString::fromUtf8("BrightHistogramDialog"));
        BrightHistogramDialog->resize(738, 511);
        ButtonClose = new QPushButton(BrightHistogramDialog);
        ButtonClose->setObjectName(QString::fromUtf8("ButtonClose"));
        ButtonClose->setGeometry(QRect(520, 460, 171, 31));
        label_7 = new QLabel(BrightHistogramDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 440, 111, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(BrightHistogramDialog);
        EditPickupL->setObjectName(QString::fromUtf8("EditPickupL"));
        EditPickupL->setGeometry(QRect(180, 440, 61, 22));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(192, 192, 192, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        EditPickupL->setPalette(palette);
        EditPickupL->setMaximum(255);
        frameLineGraph = new QFrame(BrightHistogramDialog);
        frameLineGraph->setObjectName(QString::fromUtf8("frameLineGraph"));
        frameLineGraph->setGeometry(QRect(10, 10, 711, 381));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        EditPickupH = new QSpinBox(BrightHistogramDialog);
        EditPickupH->setObjectName(QString::fromUtf8("EditPickupH"));
        EditPickupH->setGeometry(QRect(180, 470, 61, 22));
        EditPickupH->setMaximum(255);
        ButtonReflect = new QPushButton(BrightHistogramDialog);
        ButtonReflect->setObjectName(QString::fromUtf8("ButtonReflect"));
        ButtonReflect->setGeometry(QRect(520, 410, 171, 31));
        label_8 = new QLabel(BrightHistogramDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(60, 470, 111, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(BrightHistogramDialog);

        QMetaObject::connectSlotsByName(BrightHistogramDialog);
    } // setupUi

    void retranslateUi(QDialog *BrightHistogramDialog)
    {
        BrightHistogramDialog->setWindowTitle(QCoreApplication::translate("BrightHistogramDialog", "Bright Histogram", nullptr));
        ButtonClose->setText(QCoreApplication::translate("BrightHistogramDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_7->setText(QCoreApplication::translate("BrightHistogramDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        ButtonReflect->setText(QCoreApplication::translate("BrightHistogramDialog", "\345\217\215\346\230\240", nullptr));
        label_8->setText(QCoreApplication::translate("BrightHistogramDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BrightHistogramDialog: public Ui_BrightHistogramDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRIGHTHISTOGRAMDIALOG_H
