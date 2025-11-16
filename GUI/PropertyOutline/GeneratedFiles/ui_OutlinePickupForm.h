/********************************************************************************
** Form generated from reading UI file 'OutlinePickupForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTLINEPICKUPFORM_H
#define UI_OUTLINEPICKUPFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_OutlinePickupForm
{
public:
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QPushButton *pushButtonClearBaseColor;
    QPushButton *pushButtonClearEliminateColor;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSetToColor;
    QPushButton *pushButtonClearColor;
    QFrame *frameColorCube;

    void setupUi(QDialog *OutlinePickupForm)
    {
        if (OutlinePickupForm->objectName().isEmpty())
            OutlinePickupForm->setObjectName("OutlinePickupForm");
        OutlinePickupForm->resize(659, 519);
        frameColorSample = new QFrame(OutlinePickupForm);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(450, 10, 205, 501));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 470, 161, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 440, 161, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon1);
        pushButtonClearBaseColor = new QPushButton(OutlinePickupForm);
        pushButtonClearBaseColor->setObjectName("pushButtonClearBaseColor");
        pushButtonClearBaseColor->setGeometry(QRect(130, 480, 91, 25));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ClearBase.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearBaseColor->setIcon(icon2);
        pushButtonClearEliminateColor = new QPushButton(OutlinePickupForm);
        pushButtonClearEliminateColor->setObjectName("pushButtonClearEliminateColor");
        pushButtonClearEliminateColor->setGeometry(QRect(230, 480, 121, 25));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/ClearCancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearEliminateColor->setIcon(icon3);
        pushButtonClose = new QPushButton(OutlinePickupForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(360, 450, 81, 51));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon4);
        pushButtonSetToColor = new QPushButton(OutlinePickupForm);
        pushButtonSetToColor->setObjectName("pushButtonSetToColor");
        pushButtonSetToColor->setGeometry(QRect(10, 450, 111, 51));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetToColor->setIcon(icon5);
        pushButtonClearColor = new QPushButton(OutlinePickupForm);
        pushButtonClearColor->setObjectName("pushButtonClearColor");
        pushButtonClearColor->setGeometry(QRect(130, 450, 221, 25));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearColor->setIcon(icon6);
        frameColorCube = new QFrame(OutlinePickupForm);
        frameColorCube->setObjectName("frameColorCube");
        frameColorCube->setGeometry(QRect(10, 10, 431, 411));
        frameColorCube->setFrameShape(QFrame::NoFrame);
        frameColorCube->setFrameShadow(QFrame::Sunken);

        retranslateUi(OutlinePickupForm);

        QMetaObject::connectSlotsByName(OutlinePickupForm);
    } // setupUi

    void retranslateUi(QDialog *OutlinePickupForm)
    {
        OutlinePickupForm->setWindowTitle(QCoreApplication::translate("OutlinePickupForm", "Dialog", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("OutlinePickupForm", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("OutlinePickupForm", "Add Color", nullptr));
        pushButtonClearBaseColor->setText(QCoreApplication::translate("OutlinePickupForm", "Clear base", nullptr));
        pushButtonClearEliminateColor->setText(QCoreApplication::translate("OutlinePickupForm", "Clear Eliminate", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("OutlinePickupForm", "Close", nullptr));
        pushButtonSetToColor->setText(QCoreApplication::translate("OutlinePickupForm", "Set to Color", nullptr));
        pushButtonClearColor->setText(QCoreApplication::translate("OutlinePickupForm", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutlinePickupForm: public Ui_OutlinePickupForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTLINEPICKUPFORM_H
