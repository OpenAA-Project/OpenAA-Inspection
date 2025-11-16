/********************************************************************************
** Form generated from reading UI file 'BrightHistgramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRIGHTHISTGRAMFORM_H
#define UI_BRIGHTHISTGRAMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BrightHistgramForm
{
public:
    QSpinBox *EditPickupL;
    QPushButton *ButtonClose;
    QLabel *label_8;
    QPushButton *ButtonReflect;
    QLabel *label_7;
    QSpinBox *EditPickupH;
    QFrame *frameLineGraph;

    void setupUi(QDialog *BrightHistgramForm)
    {
        if (BrightHistgramForm->objectName().isEmpty())
            BrightHistgramForm->setObjectName("BrightHistgramForm");
        BrightHistgramForm->resize(730, 509);
        EditPickupL = new QSpinBox(BrightHistgramForm);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(180, 440, 61, 22));
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
        ButtonClose = new QPushButton(BrightHistgramForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(520, 460, 171, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonClose->setIcon(icon);
        label_8 = new QLabel(BrightHistgramForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(60, 470, 111, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonReflect = new QPushButton(BrightHistgramForm);
        ButtonReflect->setObjectName("ButtonReflect");
        ButtonReflect->setGeometry(QRect(520, 410, 171, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Reflection.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonReflect->setIcon(icon1);
        label_7 = new QLabel(BrightHistgramForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(60, 440, 111, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(BrightHistgramForm);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(180, 470, 61, 22));
        EditPickupH->setMaximum(255);
        frameLineGraph = new QFrame(BrightHistgramForm);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(10, 10, 711, 381));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);

        retranslateUi(BrightHistgramForm);

        QMetaObject::connectSlotsByName(BrightHistgramForm);
    } // setupUi

    void retranslateUi(QDialog *BrightHistgramForm)
    {
        BrightHistgramForm->setWindowTitle(QCoreApplication::translate("BrightHistgramForm", "Bright Histgram", nullptr));
        ButtonClose->setText(QCoreApplication::translate("BrightHistgramForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_8->setText(QCoreApplication::translate("BrightHistgramForm", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        ButtonReflect->setText(QCoreApplication::translate("BrightHistgramForm", "\345\217\215\346\230\240", nullptr));
        label_7->setText(QCoreApplication::translate("BrightHistgramForm", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BrightHistgramForm: public Ui_BrightHistgramForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRIGHTHISTGRAMFORM_H
