/********************************************************************************
** Form generated from reading UI file 'ControlPrecisionCheckerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLPRECISIONCHECKERFORM_H
#define UI_CONTROLPRECISIONCHECKERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ControlPrecisionCheckerFormClass
{
public:
    QPushButton *pushButtonResolution;
    QPushButton *pushButtonSetParam;
    QPushButton *pushButtonFocus;
    QPushButton *pushButtonAngle;
    QPushButton *pushButtonBrightness;
    QPushButton *pushButtonGrp;
    QComboBox *comboBoxPage;

    void setupUi(GUIFormBase *ControlPrecisionCheckerFormClass)
    {
        if (ControlPrecisionCheckerFormClass->objectName().isEmpty())
            ControlPrecisionCheckerFormClass->setObjectName("ControlPrecisionCheckerFormClass");
        ControlPrecisionCheckerFormClass->resize(94, 222);
        pushButtonResolution = new QPushButton(ControlPrecisionCheckerFormClass);
        pushButtonResolution->setObjectName("pushButtonResolution");
        pushButtonResolution->setGeometry(QRect(10, 160, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Resolution.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonResolution->setIcon(icon);
        pushButtonSetParam = new QPushButton(ControlPrecisionCheckerFormClass);
        pushButtonSetParam->setObjectName("pushButtonSetParam");
        pushButtonSetParam->setGeometry(QRect(10, 40, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Parameter.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetParam->setIcon(icon1);
        pushButtonFocus = new QPushButton(ControlPrecisionCheckerFormClass);
        pushButtonFocus->setObjectName("pushButtonFocus");
        pushButtonFocus->setGeometry(QRect(10, 100, 75, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Focus.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonFocus->setIcon(icon2);
        pushButtonAngle = new QPushButton(ControlPrecisionCheckerFormClass);
        pushButtonAngle->setObjectName("pushButtonAngle");
        pushButtonAngle->setGeometry(QRect(10, 190, 75, 23));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Angle.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAngle->setIcon(icon3);
        pushButtonBrightness = new QPushButton(ControlPrecisionCheckerFormClass);
        pushButtonBrightness->setObjectName("pushButtonBrightness");
        pushButtonBrightness->setGeometry(QRect(10, 130, 75, 23));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Bright.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonBrightness->setIcon(icon4);
        pushButtonGrp = new QPushButton(ControlPrecisionCheckerFormClass);
        pushButtonGrp->setObjectName("pushButtonGrp");
        pushButtonGrp->setGeometry(QRect(10, 70, 75, 23));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Group.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGrp->setIcon(icon5);
        comboBoxPage = new QComboBox(ControlPrecisionCheckerFormClass);
        comboBoxPage->addItem(QString());
        comboBoxPage->setObjectName("comboBoxPage");
        comboBoxPage->setGeometry(QRect(10, 10, 81, 22));

        retranslateUi(ControlPrecisionCheckerFormClass);

        comboBoxPage->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ControlPrecisionCheckerFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ControlPrecisionCheckerFormClass)
    {
        ControlPrecisionCheckerFormClass->setWindowTitle(QCoreApplication::translate("ControlPrecisionCheckerFormClass", "ControlPrecisionCheckerForm", nullptr));
        pushButtonResolution->setText(QCoreApplication::translate("ControlPrecisionCheckerFormClass", "Resolution", nullptr));
        pushButtonSetParam->setText(QCoreApplication::translate("ControlPrecisionCheckerFormClass", "Param", nullptr));
        pushButtonFocus->setText(QCoreApplication::translate("ControlPrecisionCheckerFormClass", "Focus", nullptr));
        pushButtonAngle->setText(QCoreApplication::translate("ControlPrecisionCheckerFormClass", "Angle", nullptr));
        pushButtonBrightness->setText(QCoreApplication::translate("ControlPrecisionCheckerFormClass", "Brightness", nullptr));
        pushButtonGrp->setText(QCoreApplication::translate("ControlPrecisionCheckerFormClass", "grp1", nullptr));
        comboBoxPage->setItemText(0, QCoreApplication::translate("ControlPrecisionCheckerFormClass", "Page 0", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ControlPrecisionCheckerFormClass: public Ui_ControlPrecisionCheckerFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLPRECISIONCHECKERFORM_H
