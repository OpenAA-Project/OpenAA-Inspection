/********************************************************************************
** Form generated from reading UI file 'ShowRGBCube.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRGBCUBE_H
#define UI_SHOWRGBCUBE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowRGBCube
{
public:
    QSlider *VSliderBrightness;
    QFrame *frameZone;
    QListWidget *listWidgetColor;

    void setupUi(QWidget *ShowRGBCube)
    {
        if (ShowRGBCube->objectName().isEmpty())
            ShowRGBCube->setObjectName("ShowRGBCube");
        ShowRGBCube->resize(427, 366);
        VSliderBrightness = new QSlider(ShowRGBCube);
        VSliderBrightness->setObjectName("VSliderBrightness");
        VSliderBrightness->setGeometry(QRect(380, 20, 21, 241));
        VSliderBrightness->setMaximum(443);
        VSliderBrightness->setPageStep(25);
        VSliderBrightness->setValue(100);
        VSliderBrightness->setOrientation(Qt::Vertical);
        VSliderBrightness->setTickPosition(QSlider::TicksBelow);
        frameZone = new QFrame(ShowRGBCube);
        frameZone->setObjectName("frameZone");
        frameZone->setGeometry(QRect(10, 10, 350, 350));
        frameZone->setFrameShape(QFrame::StyledPanel);
        frameZone->setFrameShadow(QFrame::Sunken);
        listWidgetColor = new QListWidget(ShowRGBCube);
        new QListWidgetItem(listWidgetColor);
        new QListWidgetItem(listWidgetColor);
        new QListWidgetItem(listWidgetColor);
        listWidgetColor->setObjectName("listWidgetColor");
        listWidgetColor->setGeometry(QRect(360, 270, 61, 91));

        retranslateUi(ShowRGBCube);

        QMetaObject::connectSlotsByName(ShowRGBCube);
    } // setupUi

    void retranslateUi(QWidget *ShowRGBCube)
    {
        ShowRGBCube->setWindowTitle(QCoreApplication::translate("ShowRGBCube", "Form", nullptr));

        const bool __sortingEnabled = listWidgetColor->isSortingEnabled();
        listWidgetColor->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetColor->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("ShowRGBCube", "R:128", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidgetColor->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("ShowRGBCube", "G:128", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidgetColor->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("ShowRGBCube", "B:128", nullptr));
        listWidgetColor->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class ShowRGBCube: public Ui_ShowRGBCube {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRGBCUBE_H
