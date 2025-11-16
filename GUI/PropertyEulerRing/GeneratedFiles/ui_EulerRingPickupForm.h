/********************************************************************************
** Form generated from reading UI file 'EulerRingPickupForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EULERRINGPICKUPFORM_H
#define UI_EULERRINGPICKUPFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EulerRingPickupFormClass
{
public:
    QPushButton *pushButtonClearEliminateColor;
    QPushButton *pushButtonSetToColor;
    QPushButton *pushButtonClearBaseColor;
    QPushButton *pushButtonClearColor;
    QPushButton *pushButtonClose;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QFrame *frameColorCube;

    void setupUi(QDialog *EulerRingPickupFormClass)
    {
        if (EulerRingPickupFormClass->objectName().isEmpty())
            EulerRingPickupFormClass->setObjectName("EulerRingPickupFormClass");
        EulerRingPickupFormClass->resize(620, 506);
        pushButtonClearEliminateColor = new QPushButton(EulerRingPickupFormClass);
        pushButtonClearEliminateColor->setObjectName("pushButtonClearEliminateColor");
        pushButtonClearEliminateColor->setGeometry(QRect(200, 470, 111, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ClearCancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearEliminateColor->setIcon(icon);
        pushButtonSetToColor = new QPushButton(EulerRingPickupFormClass);
        pushButtonSetToColor->setObjectName("pushButtonSetToColor");
        pushButtonSetToColor->setGeometry(QRect(10, 440, 91, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetToColor->setIcon(icon1);
        pushButtonClearBaseColor = new QPushButton(EulerRingPickupFormClass);
        pushButtonClearBaseColor->setObjectName("pushButtonClearBaseColor");
        pushButtonClearBaseColor->setGeometry(QRect(110, 470, 81, 25));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ClearBase.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearBaseColor->setIcon(icon2);
        pushButtonClearColor = new QPushButton(EulerRingPickupFormClass);
        pushButtonClearColor->setObjectName("pushButtonClearColor");
        pushButtonClearColor->setGeometry(QRect(110, 440, 201, 25));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearColor->setIcon(icon3);
        pushButtonClose = new QPushButton(EulerRingPickupFormClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(320, 440, 81, 51));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon4);
        frameColorSample = new QFrame(EulerRingPickupFormClass);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(410, 0, 205, 501));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 470, 161, 25));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon5);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 440, 161, 25));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon6);
        frameColorCube = new QFrame(EulerRingPickupFormClass);
        frameColorCube->setObjectName("frameColorCube");
        frameColorCube->setGeometry(QRect(0, 0, 401, 411));
        frameColorCube->setFrameShape(QFrame::NoFrame);
        frameColorCube->setFrameShadow(QFrame::Sunken);

        retranslateUi(EulerRingPickupFormClass);

        QMetaObject::connectSlotsByName(EulerRingPickupFormClass);
    } // setupUi

    void retranslateUi(QDialog *EulerRingPickupFormClass)
    {
        EulerRingPickupFormClass->setWindowTitle(QCoreApplication::translate("EulerRingPickupFormClass", "EulerRingPickupForm", nullptr));
        pushButtonClearEliminateColor->setText(QCoreApplication::translate("EulerRingPickupFormClass", "Clear Eliminate", nullptr));
        pushButtonSetToColor->setText(QCoreApplication::translate("EulerRingPickupFormClass", "Set to Color", nullptr));
        pushButtonClearBaseColor->setText(QCoreApplication::translate("EulerRingPickupFormClass", "Clear base", nullptr));
        pushButtonClearColor->setText(QCoreApplication::translate("EulerRingPickupFormClass", "Clear", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EulerRingPickupFormClass", "Close", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("EulerRingPickupFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("EulerRingPickupFormClass", "Add Color", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EulerRingPickupFormClass: public Ui_EulerRingPickupFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EULERRINGPICKUPFORM_H
