/********************************************************************************
** Form generated from reading UI file 'ShowRGBSamples.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRGBSAMPLES_H
#define UI_SHOWRGBSAMPLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowRGBSamples
{
public:
    QFrame *frameZone;
    QLabel *label;
    QSpinBox *spinBoxExtend;
    QSlider *VSliderBrightness;
    QListWidget *listWidgetColor;

    void setupUi(QWidget *ShowRGBSamples)
    {
        if (ShowRGBSamples->objectName().isEmpty())
            ShowRGBSamples->setObjectName("ShowRGBSamples");
        ShowRGBSamples->resize(427, 369);
        frameZone = new QFrame(ShowRGBSamples);
        frameZone->setObjectName("frameZone");
        frameZone->setGeometry(QRect(10, 10, 350, 350));
        frameZone->setFrameShape(QFrame::StyledPanel);
        frameZone->setFrameShadow(QFrame::Sunken);
        label = new QLabel(ShowRGBSamples);
        label->setObjectName("label");
        label->setGeometry(QRect(370, 220, 51, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxExtend = new QSpinBox(ShowRGBSamples);
        spinBoxExtend->setObjectName("spinBoxExtend");
        spinBoxExtend->setGeometry(QRect(370, 240, 46, 22));
        spinBoxExtend->setMaximum(255);
        spinBoxExtend->setValue(10);
        VSliderBrightness = new QSlider(ShowRGBSamples);
        VSliderBrightness->setObjectName("VSliderBrightness");
        VSliderBrightness->setGeometry(QRect(380, 20, 21, 191));
        VSliderBrightness->setMaximum(255);
        VSliderBrightness->setPageStep(25);
        VSliderBrightness->setValue(100);
        VSliderBrightness->setOrientation(Qt::Vertical);
        VSliderBrightness->setTickPosition(QSlider::TicksBelow);
        listWidgetColor = new QListWidget(ShowRGBSamples);
        new QListWidgetItem(listWidgetColor);
        new QListWidgetItem(listWidgetColor);
        new QListWidgetItem(listWidgetColor);
        listWidgetColor->setObjectName("listWidgetColor");
        listWidgetColor->setGeometry(QRect(360, 270, 61, 91));
        listWidgetColor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        retranslateUi(ShowRGBSamples);

        QMetaObject::connectSlotsByName(ShowRGBSamples);
    } // setupUi

    void retranslateUi(QWidget *ShowRGBSamples)
    {
        ShowRGBSamples->setWindowTitle(QCoreApplication::translate("ShowRGBSamples", "Form", nullptr));
        label->setText(QCoreApplication::translate("ShowRGBSamples", "\350\206\250\345\274\265", nullptr));

        const bool __sortingEnabled = listWidgetColor->isSortingEnabled();
        listWidgetColor->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetColor->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("ShowRGBSamples", "R:128", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidgetColor->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("ShowRGBSamples", "G:128", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidgetColor->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("ShowRGBSamples", "B:128", nullptr));
        listWidgetColor->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class ShowRGBSamples: public Ui_ShowRGBSamples {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRGBSAMPLES_H
