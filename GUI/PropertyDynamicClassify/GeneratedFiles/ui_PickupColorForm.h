/********************************************************************************
** Form generated from reading UI file 'PickupColorForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICKUPCOLORFORM_H
#define UI_PICKUPCOLORFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PickupColorFormClass
{
public:
    QFrame *frameColorCube;
    QPushButton *pushButtonClearColor;
    QPushButton *pushButtonClearBaseColor;
    QPushButton *pushButtonClearEliminateColor;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSetToColor;

    void setupUi(QDialog *PickupColorFormClass)
    {
        if (PickupColorFormClass->objectName().isEmpty())
            PickupColorFormClass->setObjectName("PickupColorFormClass");
        PickupColorFormClass->resize(637, 522);
        frameColorCube = new QFrame(PickupColorFormClass);
        frameColorCube->setObjectName("frameColorCube");
        frameColorCube->setGeometry(QRect(10, 10, 401, 411));
        frameColorCube->setFrameShape(QFrame::NoFrame);
        frameColorCube->setFrameShadow(QFrame::Sunken);
        pushButtonClearColor = new QPushButton(PickupColorFormClass);
        pushButtonClearColor->setObjectName("pushButtonClearColor");
        pushButtonClearColor->setGeometry(QRect(120, 450, 201, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearColor->setIcon(icon);
        pushButtonClearBaseColor = new QPushButton(PickupColorFormClass);
        pushButtonClearBaseColor->setObjectName("pushButtonClearBaseColor");
        pushButtonClearBaseColor->setGeometry(QRect(120, 480, 81, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ClearBase.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearBaseColor->setIcon(icon1);
        pushButtonClearEliminateColor = new QPushButton(PickupColorFormClass);
        pushButtonClearEliminateColor->setObjectName("pushButtonClearEliminateColor");
        pushButtonClearEliminateColor->setGeometry(QRect(210, 480, 111, 25));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ClearCancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearEliminateColor->setIcon(icon2);
        frameColorSample = new QFrame(PickupColorFormClass);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(420, 10, 205, 501));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 470, 161, 25));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon3);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 440, 161, 25));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon4);
        pushButtonClose = new QPushButton(PickupColorFormClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(330, 450, 81, 51));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon5);
        pushButtonSetToColor = new QPushButton(PickupColorFormClass);
        pushButtonSetToColor->setObjectName("pushButtonSetToColor");
        pushButtonSetToColor->setGeometry(QRect(20, 450, 91, 51));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetToColor->setIcon(icon6);

        retranslateUi(PickupColorFormClass);

        QMetaObject::connectSlotsByName(PickupColorFormClass);
    } // setupUi

    void retranslateUi(QDialog *PickupColorFormClass)
    {
        PickupColorFormClass->setWindowTitle(QCoreApplication::translate("PickupColorFormClass", "PickupColorForm", nullptr));
        pushButtonClearColor->setText(QCoreApplication::translate("PickupColorFormClass", "Clear", nullptr));
        pushButtonClearBaseColor->setText(QCoreApplication::translate("PickupColorFormClass", "Clear base", nullptr));
        pushButtonClearEliminateColor->setText(QCoreApplication::translate("PickupColorFormClass", "Clear Eliminate", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("PickupColorFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("PickupColorFormClass", "Add Color", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("PickupColorFormClass", "Close", nullptr));
        pushButtonSetToColor->setText(QCoreApplication::translate("PickupColorFormClass", "Set to Color", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PickupColorFormClass: public Ui_PickupColorFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICKUPCOLORFORM_H
