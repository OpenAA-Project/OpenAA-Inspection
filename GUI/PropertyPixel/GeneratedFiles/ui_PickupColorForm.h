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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PickupColorFormClass
{
public:
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QFrame *frameThreshold;
    QLabel *label_33;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonEliminate;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *PickupColorFormClass)
    {
        if (PickupColorFormClass->objectName().isEmpty())
            PickupColorFormClass->setObjectName("PickupColorFormClass");
        PickupColorFormClass->resize(604, 444);
        frameColorSample = new QFrame(PickupColorFormClass);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(390, 10, 205, 421));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 390, 161, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 360, 161, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon1);
        frameThreshold = new QFrame(PickupColorFormClass);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(10, 30, 371, 281));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Sunken);
        label_33 = new QLabel(PickupColorFormClass);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, 10, 371, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonAdd = new QPushButton(PickupColorFormClass);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(60, 360, 131, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAdd->setIcon(icon2);
        pushButtonEliminate = new QPushButton(PickupColorFormClass);
        pushButtonEliminate->setObjectName("pushButtonEliminate");
        pushButtonEliminate->setGeometry(QRect(60, 400, 131, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminate->setIcon(icon3);
        pushButtonCancel = new QPushButton(PickupColorFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(220, 400, 131, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon4);

        retranslateUi(PickupColorFormClass);

        QMetaObject::connectSlotsByName(PickupColorFormClass);
    } // setupUi

    void retranslateUi(QDialog *PickupColorFormClass)
    {
        PickupColorFormClass->setWindowTitle(QCoreApplication::translate("PickupColorFormClass", "PickupColorForm", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("PickupColorFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("PickupColorFormClass", "Add Color", nullptr));
        label_33->setText(QCoreApplication::translate("PickupColorFormClass", "\346\244\234\346\237\273\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("PickupColorFormClass", "Add", nullptr));
        pushButtonEliminate->setText(QCoreApplication::translate("PickupColorFormClass", "Eliminate", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("PickupColorFormClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PickupColorFormClass: public Ui_PickupColorFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICKUPCOLORFORM_H
