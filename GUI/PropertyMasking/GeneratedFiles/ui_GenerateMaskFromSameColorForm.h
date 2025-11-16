/********************************************************************************
** Form generated from reading UI file 'GenerateMaskFromSameColorForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEMASKFROMSAMECOLORFORM_H
#define UI_GENERATEMASKFROMSAMECOLORFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateMaskFromSameColorFormClass
{
public:
    QListWidget *listWidgetEliminatedColor;
    QLabel *label_26;
    QLabel *label_23;
    QSpinBox *EditMaxPickupSize;
    QLabel *label_7;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QWidget *tab_2;
    QFrame *framePicked;
    QLabel *label_36;
    QPushButton *pushButtonSubPickupColor;
    QPushButton *pushButtonAddPickupColor;
    QSpinBox *spinBoxMerginAddPickupColor;
    QSpinBox *spinBoxMerginSubPickupColor;
    QLabel *label_37;
    QFrame *framePickupColor;
    QWidget *tab_3;
    QFrame *frameShowColorSmples;
    QPushButton *pushButtonAddColorArea;
    QPushButton *pushButtonEliminateColorArea;
    QFrame *frameThreshold;
    QListWidget *listWidgetBaseColor;
    QLabel *label_8;
    QSpinBox *EditMinPickupSize;
    QLabel *label_25;
    QSpinBox *EditMaxPickupDots;
    QLabel *label_27;
    QSpinBox *EditMinPickupDots;
    QLabel *label_24;
    QPushButton *pushButton;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonEffective;
    QPushButton *pushButtonNonEffective;
    QLabel *label_28;
    QSpinBox *EditErosion;
    QPushButton *pushButtonLimited;

    void setupUi(QDialog *GenerateMaskFromSameColorFormClass)
    {
        if (GenerateMaskFromSameColorFormClass->objectName().isEmpty())
            GenerateMaskFromSameColorFormClass->setObjectName("GenerateMaskFromSameColorFormClass");
        GenerateMaskFromSameColorFormClass->resize(818, 569);
        listWidgetEliminatedColor = new QListWidget(GenerateMaskFromSameColorFormClass);
        listWidgetEliminatedColor->setObjectName("listWidgetEliminatedColor");
        listWidgetEliminatedColor->setGeometry(QRect(290, 210, 61, 61));
        label_26 = new QLabel(GenerateMaskFromSameColorFormClass);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 10, 271, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(GenerateMaskFromSameColorFormClass);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 300, 161, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxPickupSize = new QSpinBox(GenerateMaskFromSameColorFormClass);
        EditMaxPickupSize->setObjectName("EditMaxPickupSize");
        EditMaxPickupSize->setGeometry(QRect(180, 320, 81, 22));
        EditMaxPickupSize->setMaximum(2000000000);
        label_7 = new QLabel(GenerateMaskFromSameColorFormClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(290, 30, 61, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget = new QTabWidget(GenerateMaskFromSameColorFormClass);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(370, 10, 441, 551));
        tab = new QWidget();
        tab->setObjectName("tab");
        frameColorSample = new QFrame(tab);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(10, 10, 205, 511));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 480, 161, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 450, 161, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon1);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        framePicked = new QFrame(tab_2);
        framePicked->setObjectName("framePicked");
        framePicked->setGeometry(QRect(10, 10, 191, 111));
        framePicked->setFrameShape(QFrame::StyledPanel);
        framePicked->setFrameShadow(QFrame::Sunken);
        label_36 = new QLabel(framePicked);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(0, 0, 191, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSubPickupColor = new QPushButton(framePicked);
        pushButtonSubPickupColor->setObjectName("pushButtonSubPickupColor");
        pushButtonSubPickupColor->setGeometry(QRect(40, 80, 75, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSubPickupColor->setIcon(icon2);
        pushButtonAddPickupColor = new QPushButton(framePicked);
        pushButtonAddPickupColor->setObjectName("pushButtonAddPickupColor");
        pushButtonAddPickupColor->setGeometry(QRect(40, 50, 75, 23));
        pushButtonAddPickupColor->setIcon(icon1);
        spinBoxMerginAddPickupColor = new QSpinBox(framePicked);
        spinBoxMerginAddPickupColor->setObjectName("spinBoxMerginAddPickupColor");
        spinBoxMerginAddPickupColor->setGeometry(QRect(120, 50, 61, 22));
        spinBoxMerginAddPickupColor->setValue(10);
        spinBoxMerginSubPickupColor = new QSpinBox(framePicked);
        spinBoxMerginSubPickupColor->setObjectName("spinBoxMerginSubPickupColor");
        spinBoxMerginSubPickupColor->setGeometry(QRect(120, 80, 61, 22));
        spinBoxMerginSubPickupColor->setValue(10);
        label_37 = new QLabel(framePicked);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(120, 30, 64, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        framePickupColor = new QFrame(framePicked);
        framePickupColor->setObjectName("framePickupColor");
        framePickupColor->setGeometry(QRect(10, 30, 21, 71));
        framePickupColor->setFrameShape(QFrame::NoFrame);
        framePickupColor->setFrameShadow(QFrame::Plain);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        frameShowColorSmples = new QFrame(tab_3);
        frameShowColorSmples->setObjectName("frameShowColorSmples");
        frameShowColorSmples->setGeometry(QRect(10, 10, 415, 355));
        frameShowColorSmples->setFrameShape(QFrame::NoFrame);
        frameShowColorSmples->setFrameShadow(QFrame::Plain);
        pushButtonAddColorArea = new QPushButton(tab_3);
        pushButtonAddColorArea->setObjectName("pushButtonAddColorArea");
        pushButtonAddColorArea->setGeometry(QRect(60, 370, 161, 25));
        pushButtonAddColorArea->setIcon(icon1);
        pushButtonEliminateColorArea = new QPushButton(tab_3);
        pushButtonEliminateColorArea->setObjectName("pushButtonEliminateColorArea");
        pushButtonEliminateColorArea->setGeometry(QRect(60, 400, 161, 25));
        pushButtonEliminateColorArea->setIcon(icon);
        tabWidget->addTab(tab_3, QString());
        frameThreshold = new QFrame(GenerateMaskFromSameColorFormClass);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(10, 30, 271, 251));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Raised);
        listWidgetBaseColor = new QListWidget(GenerateMaskFromSameColorFormClass);
        listWidgetBaseColor->setObjectName("listWidgetBaseColor");
        listWidgetBaseColor->setGeometry(QRect(290, 50, 61, 61));
        label_8 = new QLabel(GenerateMaskFromSameColorFormClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(290, 190, 61, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinPickupSize = new QSpinBox(GenerateMaskFromSameColorFormClass);
        EditMinPickupSize->setObjectName("EditMinPickupSize");
        EditMinPickupSize->setGeometry(QRect(180, 300, 81, 22));
        EditMinPickupSize->setMaximum(2000000000);
        label_25 = new QLabel(GenerateMaskFromSameColorFormClass);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 320, 161, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxPickupDots = new QSpinBox(GenerateMaskFromSameColorFormClass);
        EditMaxPickupDots->setObjectName("EditMaxPickupDots");
        EditMaxPickupDots->setGeometry(QRect(180, 370, 81, 22));
        EditMaxPickupDots->setMaximum(2000000000);
        label_27 = new QLabel(GenerateMaskFromSameColorFormClass);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 370, 161, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinPickupDots = new QSpinBox(GenerateMaskFromSameColorFormClass);
        EditMinPickupDots->setObjectName("EditMinPickupDots");
        EditMinPickupDots->setGeometry(QRect(180, 350, 81, 22));
        EditMinPickupDots->setMaximum(2000000000);
        label_24 = new QLabel(GenerateMaskFromSameColorFormClass);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 350, 161, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton = new QPushButton(GenerateMaskFromSameColorFormClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 430, 101, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon3);
        pushButtonCancel = new QPushButton(GenerateMaskFromSameColorFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(260, 500, 91, 41));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon4);
        pushButtonEffective = new QPushButton(GenerateMaskFromSameColorFormClass);
        pushButtonEffective->setObjectName("pushButtonEffective");
        pushButtonEffective->setGeometry(QRect(30, 480, 101, 41));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Mask.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEffective->setIcon(icon5);
        pushButtonNonEffective = new QPushButton(GenerateMaskFromSameColorFormClass);
        pushButtonNonEffective->setObjectName("pushButtonNonEffective");
        pushButtonNonEffective->setGeometry(QRect(140, 480, 101, 41));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/MaskNG.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonNonEffective->setIcon(icon6);
        label_28 = new QLabel(GenerateMaskFromSameColorFormClass);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 400, 161, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditErosion = new QSpinBox(GenerateMaskFromSameColorFormClass);
        EditErosion->setObjectName("EditErosion");
        EditErosion->setGeometry(QRect(180, 400, 81, 22));
        EditErosion->setMinimum(-255);
        EditErosion->setMaximum(255);
        pushButtonLimited = new QPushButton(GenerateMaskFromSameColorFormClass);
        pushButtonLimited->setObjectName("pushButtonLimited");
        pushButtonLimited->setGeometry(QRect(30, 520, 211, 41));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Qtres/MaskLimit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLimited->setIcon(icon7);

        retranslateUi(GenerateMaskFromSameColorFormClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GenerateMaskFromSameColorFormClass);
    } // setupUi

    void retranslateUi(QDialog *GenerateMaskFromSameColorFormClass)
    {
        GenerateMaskFromSameColorFormClass->setWindowTitle(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "GenerateMaskFromSameColorForm", nullptr));
        label_26->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\347\251\264\343\201\256\350\211\262\346\214\207\345\256\232", nullptr));
        label_23->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\346\234\200\345\260\217\347\270\246\343\203\273\346\250\252\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_7->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\350\277\275\345\212\240\350\211\262", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "Add Color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\350\211\262\347\231\273\351\214\262\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        label_36->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\343\203\224\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        pushButtonSubPickupColor->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "Sub =>", nullptr));
        pushButtonAddPickupColor->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "Add =>", nullptr));
        label_37->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\343\203\224\343\202\257\343\202\273\343\203\253\346\212\275\345\207\272\350\211\262", nullptr));
        pushButtonAddColorArea->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "Add Color", nullptr));
        pushButtonEliminateColorArea->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "Eliminate color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\351\240\230\345\237\237\346\212\275\345\207\272\350\211\262", nullptr));
        label_8->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\351\231\244\345\244\226\350\211\262", nullptr));
        label_25->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\346\234\200\345\244\247\347\270\246\343\203\273\346\250\252\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_27->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\346\234\200\345\244\247\351\235\242\347\251\215\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_24->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\346\234\200\345\260\217\351\235\242\347\251\215\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\344\273\256\346\212\275\345\207\272", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        pushButtonEffective->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\346\234\211\345\212\271\343\203\236\343\202\271\343\202\257", nullptr));
        pushButtonNonEffective->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\347\204\241\345\212\271\343\203\236\343\202\271\343\202\257", nullptr));
        label_28->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260\357\274\210\343\203\236\343\202\244\343\203\212\343\202\271\343\201\247\345\217\216\347\270\256\357\274\211", nullptr));
        pushButtonLimited->setText(QCoreApplication::translate("GenerateMaskFromSameColorFormClass", "\351\231\220\345\256\232\343\203\236\343\202\271\343\202\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerateMaskFromSameColorFormClass: public Ui_GenerateMaskFromSameColorFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEMASKFROMSAMECOLORFORM_H
