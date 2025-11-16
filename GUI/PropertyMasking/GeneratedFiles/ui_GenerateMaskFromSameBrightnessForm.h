/********************************************************************************
** Form generated from reading UI file 'GenerateMaskFromSameBrightnessForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEMASKFROMSAMEBRIGHTNESSFORM_H
#define UI_GENERATEMASKFROMSAMEBRIGHTNESSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_GenerateMaskFromSameBrightnessFormClass
{
public:
    QPushButton *ButtonCancel;
    QSpinBox *spinBoxH;
    QSpinBox *spinBoxL;
    QPushButton *ButtonNotEffective;
    QLabel *label_2;
    QPushButton *ButtonEffective;
    QLabel *label;
    QLabel *label_25;
    QLabel *label_24;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_23;
    QSpinBox *EditMaxPickupDots;
    QSpinBox *EditMaxPickupSize;
    QSpinBox *EditMinPickupSize;
    QSpinBox *EditErosion;
    QSpinBox *EditMinPickupDots;
    QPushButton *pushButton;
    QPushButton *pushButtonLimited;

    void setupUi(QDialog *GenerateMaskFromSameBrightnessFormClass)
    {
        if (GenerateMaskFromSameBrightnessFormClass->objectName().isEmpty())
            GenerateMaskFromSameBrightnessFormClass->setObjectName("GenerateMaskFromSameBrightnessFormClass");
        GenerateMaskFromSameBrightnessFormClass->resize(262, 323);
        ButtonCancel = new QPushButton(GenerateMaskFromSameBrightnessFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(150, 280, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        spinBoxH = new QSpinBox(GenerateMaskFromSameBrightnessFormClass);
        spinBoxH->setObjectName("spinBoxH");
        spinBoxH->setGeometry(QRect(100, 30, 81, 22));
        spinBoxH->setMaximum(256);
        spinBoxL = new QSpinBox(GenerateMaskFromSameBrightnessFormClass);
        spinBoxL->setObjectName("spinBoxL");
        spinBoxL->setGeometry(QRect(10, 30, 81, 22));
        spinBoxL->setMaximum(256);
        ButtonNotEffective = new QPushButton(GenerateMaskFromSameBrightnessFormClass);
        ButtonNotEffective->setObjectName("ButtonNotEffective");
        ButtonNotEffective->setGeometry(QRect(150, 240, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/EffectNG.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonNotEffective->setIcon(icon1);
        label_2 = new QLabel(GenerateMaskFromSameBrightnessFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 10, 81, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonEffective = new QPushButton(GenerateMaskFromSameBrightnessFormClass);
        ButtonEffective->setObjectName("ButtonEffective");
        ButtonEffective->setGeometry(QRect(30, 240, 111, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Effect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonEffective->setIcon(icon2);
        label = new QLabel(GenerateMaskFromSameBrightnessFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 81, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(GenerateMaskFromSameBrightnessFormClass);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 90, 161, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_24 = new QLabel(GenerateMaskFromSameBrightnessFormClass);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 120, 161, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_27 = new QLabel(GenerateMaskFromSameBrightnessFormClass);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 140, 161, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(GenerateMaskFromSameBrightnessFormClass);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 170, 161, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(GenerateMaskFromSameBrightnessFormClass);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 70, 161, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxPickupDots = new QSpinBox(GenerateMaskFromSameBrightnessFormClass);
        EditMaxPickupDots->setObjectName("EditMaxPickupDots");
        EditMaxPickupDots->setGeometry(QRect(170, 140, 81, 22));
        EditMaxPickupDots->setMaximum(2000000000);
        EditMaxPickupSize = new QSpinBox(GenerateMaskFromSameBrightnessFormClass);
        EditMaxPickupSize->setObjectName("EditMaxPickupSize");
        EditMaxPickupSize->setGeometry(QRect(170, 90, 81, 22));
        EditMaxPickupSize->setMaximum(2000000000);
        EditMinPickupSize = new QSpinBox(GenerateMaskFromSameBrightnessFormClass);
        EditMinPickupSize->setObjectName("EditMinPickupSize");
        EditMinPickupSize->setGeometry(QRect(170, 70, 81, 22));
        EditMinPickupSize->setMaximum(2000000000);
        EditErosion = new QSpinBox(GenerateMaskFromSameBrightnessFormClass);
        EditErosion->setObjectName("EditErosion");
        EditErosion->setGeometry(QRect(170, 170, 81, 22));
        EditErosion->setMinimum(-255);
        EditErosion->setMaximum(255);
        EditMinPickupDots = new QSpinBox(GenerateMaskFromSameBrightnessFormClass);
        EditMinPickupDots->setObjectName("EditMinPickupDots");
        EditMinPickupDots->setGeometry(QRect(170, 120, 81, 22));
        EditMinPickupDots->setMaximum(2000000000);
        pushButton = new QPushButton(GenerateMaskFromSameBrightnessFormClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 200, 111, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon3);
        pushButtonLimited = new QPushButton(GenerateMaskFromSameBrightnessFormClass);
        pushButtonLimited->setObjectName("pushButtonLimited");
        pushButtonLimited->setGeometry(QRect(30, 280, 111, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Mask.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLimited->setIcon(icon4);

        retranslateUi(GenerateMaskFromSameBrightnessFormClass);

        QMetaObject::connectSlotsByName(GenerateMaskFromSameBrightnessFormClass);
    } // setupUi

    void retranslateUi(QDialog *GenerateMaskFromSameBrightnessFormClass)
    {
        GenerateMaskFromSameBrightnessFormClass->setWindowTitle(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "GenerateMaskFromSameBrightnessForm", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "Cancel", nullptr));
        ButtonNotEffective->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "Not effective", nullptr));
        label_2->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "\346\230\216\345\201\264", nullptr));
        ButtonEffective->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "Effective", nullptr));
        label->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "\346\232\227\345\201\264", nullptr));
        label_25->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "\346\234\200\345\244\247\347\270\246\343\203\273\346\250\252\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_24->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "\346\234\200\345\260\217\351\235\242\347\251\215\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_27->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "\346\234\200\345\244\247\351\235\242\347\251\215\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_28->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260\357\274\210\343\203\236\343\202\244\343\203\212\343\202\271\343\201\247\345\217\216\347\270\256\357\274\211", nullptr));
        label_23->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "\346\234\200\345\260\217\347\270\246\343\203\273\346\250\252\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "\344\273\256\346\212\275\345\207\272", nullptr));
        pushButtonLimited->setText(QCoreApplication::translate("GenerateMaskFromSameBrightnessFormClass", "\351\231\220\345\256\232\343\203\236\343\202\271\343\202\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerateMaskFromSameBrightnessFormClass: public Ui_GenerateMaskFromSameBrightnessFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEMASKFROMSAMEBRIGHTNESSFORM_H
