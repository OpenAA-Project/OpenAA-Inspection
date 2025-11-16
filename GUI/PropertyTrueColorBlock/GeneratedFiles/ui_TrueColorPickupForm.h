/********************************************************************************
** Form generated from reading UI file 'TrueColorPickupForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRUECOLORPICKUPFORM_H
#define UI_TRUECOLORPICKUPFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TrueColorPickupFormClass
{
public:
    QFrame *frameColorCube;
    QPushButton *pushButtonClose;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QPushButton *pushButtonSetToColor;
    QPushButton *pushButtonClearColor;
    QPushButton *pushButtonClearBaseColor;
    QPushButton *pushButtonClearEliminateColor;

    void setupUi(QDialog *TrueColorPickupFormClass)
    {
        if (TrueColorPickupFormClass->objectName().isEmpty())
            TrueColorPickupFormClass->setObjectName("TrueColorPickupFormClass");
        TrueColorPickupFormClass->resize(620, 506);
        frameColorCube = new QFrame(TrueColorPickupFormClass);
        frameColorCube->setObjectName("frameColorCube");
        frameColorCube->setGeometry(QRect(0, 0, 401, 411));
        frameColorCube->setFrameShape(QFrame::NoFrame);
        frameColorCube->setFrameShadow(QFrame::Sunken);
        pushButtonClose = new QPushButton(TrueColorPickupFormClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(330, 440, 71, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon);
        frameColorSample = new QFrame(TrueColorPickupFormClass);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(410, 0, 205, 501));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 470, 161, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon1);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 440, 161, 25));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon2);
        pushButtonSetToColor = new QPushButton(TrueColorPickupFormClass);
        pushButtonSetToColor->setObjectName("pushButtonSetToColor");
        pushButtonSetToColor->setGeometry(QRect(10, 440, 91, 51));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetToColor->setIcon(icon3);
        pushButtonClearColor = new QPushButton(TrueColorPickupFormClass);
        pushButtonClearColor->setObjectName("pushButtonClearColor");
        pushButtonClearColor->setGeometry(QRect(110, 440, 211, 25));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearColor->setIcon(icon4);
        pushButtonClearBaseColor = new QPushButton(TrueColorPickupFormClass);
        pushButtonClearBaseColor->setObjectName("pushButtonClearBaseColor");
        pushButtonClearBaseColor->setGeometry(QRect(110, 470, 91, 25));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/ClearBase.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearBaseColor->setIcon(icon5);
        pushButtonClearEliminateColor = new QPushButton(TrueColorPickupFormClass);
        pushButtonClearEliminateColor->setObjectName("pushButtonClearEliminateColor");
        pushButtonClearEliminateColor->setGeometry(QRect(210, 470, 111, 25));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/ClearCancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearEliminateColor->setIcon(icon6);

        retranslateUi(TrueColorPickupFormClass);

        QMetaObject::connectSlotsByName(TrueColorPickupFormClass);
    } // setupUi

    void retranslateUi(QDialog *TrueColorPickupFormClass)
    {
        TrueColorPickupFormClass->setWindowTitle(QCoreApplication::translate("TrueColorPickupFormClass", "TrueColorPickupForm", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("TrueColorPickupFormClass", "Close", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("TrueColorPickupFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("TrueColorPickupFormClass", "Add Color", nullptr));
        pushButtonSetToColor->setText(QCoreApplication::translate("TrueColorPickupFormClass", "Set to Color", nullptr));
        pushButtonClearColor->setText(QCoreApplication::translate("TrueColorPickupFormClass", "Clear", nullptr));
        pushButtonClearBaseColor->setText(QCoreApplication::translate("TrueColorPickupFormClass", "Clear base", nullptr));
        pushButtonClearEliminateColor->setText(QCoreApplication::translate("TrueColorPickupFormClass", "Clear Eliminate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrueColorPickupFormClass: public Ui_TrueColorPickupFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRUECOLORPICKUPFORM_H
