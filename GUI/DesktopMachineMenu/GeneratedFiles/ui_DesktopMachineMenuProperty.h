/********************************************************************************
** Form generated from reading UI file 'DesktopMachineMenuProperty.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESKTOPMACHINEMENUPROPERTY_H
#define UI_DESKTOPMACHINEMENUPROPERTY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_DesktopMachineMenuPropertyClass
{
public:
    QToolButton *toolButtonScanMaster;
    QLabel *labelCurrentCount;
    QLabel *labelCounter1;
    QToolButton *toolButtonScanTarget;
    QPushButton *pushButtonDetail;
    QPushButton *pushButtonClose;
    QLabel *labelMessage;
    QSlider *horizontalSliderQuality;
    QSpinBox *spinBoxQuality;
    QLabel *labelQuality;

    void setupUi(GUIFormBase *DesktopMachineMenuPropertyClass)
    {
        if (DesktopMachineMenuPropertyClass->objectName().isEmpty())
            DesktopMachineMenuPropertyClass->setObjectName("DesktopMachineMenuPropertyClass");
        DesktopMachineMenuPropertyClass->resize(185, 632);
        toolButtonScanMaster = new QToolButton(DesktopMachineMenuPropertyClass);
        toolButtonScanMaster->setObjectName("toolButtonScanMaster");
        toolButtonScanMaster->setGeometry(QRect(10, 10, 161, 51));
        toolButtonScanMaster->setCheckable(true);
        toolButtonScanMaster->setAutoExclusive(true);
        labelCurrentCount = new QLabel(DesktopMachineMenuPropertyClass);
        labelCurrentCount->setObjectName("labelCurrentCount");
        labelCurrentCount->setGeometry(QRect(35, 80, 31, 20));
        QFont font;
        font.setPointSize(12);
        labelCurrentCount->setFont(font);
        labelCurrentCount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelCounter1 = new QLabel(DesktopMachineMenuPropertyClass);
        labelCounter1->setObjectName("labelCounter1");
        labelCounter1->setGeometry(QRect(100, 80, 61, 21));
        labelCounter1->setFont(font);
        toolButtonScanTarget = new QToolButton(DesktopMachineMenuPropertyClass);
        toolButtonScanTarget->setObjectName("toolButtonScanTarget");
        toolButtonScanTarget->setGeometry(QRect(10, 150, 161, 81));
        toolButtonScanTarget->setCheckable(true);
        pushButtonDetail = new QPushButton(DesktopMachineMenuPropertyClass);
        pushButtonDetail->setObjectName("pushButtonDetail");
        pushButtonDetail->setGeometry(QRect(40, 450, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Preview.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDetail->setIcon(icon);
        pushButtonClose = new QPushButton(DesktopMachineMenuPropertyClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(10, 520, 161, 71));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        labelMessage = new QLabel(DesktopMachineMenuPropertyClass);
        labelMessage->setObjectName("labelMessage");
        labelMessage->setGeometry(QRect(0, 599, 181, 31));
        labelMessage->setFont(font);
        labelMessage->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalSliderQuality = new QSlider(DesktopMachineMenuPropertyClass);
        horizontalSliderQuality->setObjectName("horizontalSliderQuality");
        horizontalSliderQuality->setGeometry(QRect(10, 240, 160, 16));
        horizontalSliderQuality->setMaximum(256);
        horizontalSliderQuality->setOrientation(Qt::Horizontal);
        spinBoxQuality = new QSpinBox(DesktopMachineMenuPropertyClass);
        spinBoxQuality->setObjectName("spinBoxQuality");
        spinBoxQuality->setGeometry(QRect(105, 270, 61, 31));
        spinBoxQuality->setMaximum(256);
        labelQuality = new QLabel(DesktopMachineMenuPropertyClass);
        labelQuality->setObjectName("labelQuality");
        labelQuality->setGeometry(QRect(40, 270, 50, 31));
        labelQuality->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(DesktopMachineMenuPropertyClass);

        QMetaObject::connectSlotsByName(DesktopMachineMenuPropertyClass);
    } // setupUi

    void retranslateUi(GUIFormBase *DesktopMachineMenuPropertyClass)
    {
        DesktopMachineMenuPropertyClass->setWindowTitle(QCoreApplication::translate("DesktopMachineMenuPropertyClass", "DesktopMachineMenuProperty", nullptr));
        toolButtonScanMaster->setText(QCoreApplication::translate("DesktopMachineMenuPropertyClass", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\350\252\255\350\276\274", nullptr));
        labelCurrentCount->setText(QCoreApplication::translate("DesktopMachineMenuPropertyClass", "1", nullptr));
        labelCounter1->setText(QCoreApplication::translate("DesktopMachineMenuPropertyClass", "\346\236\232\347\233\256", nullptr));
        toolButtonScanTarget->setText(QCoreApplication::translate("DesktopMachineMenuPropertyClass", "\346\244\234\346\237\273\345\256\237\350\241\214", nullptr));
        pushButtonDetail->setText(QCoreApplication::translate("DesktopMachineMenuPropertyClass", "\350\251\263\347\264\260", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("DesktopMachineMenuPropertyClass", "\347\265\202\344\272\206", nullptr));
        labelMessage->setText(QCoreApplication::translate("DesktopMachineMenuPropertyClass", "XXX", nullptr));
        labelQuality->setText(QCoreApplication::translate("DesktopMachineMenuPropertyClass", "\345\223\201\350\263\252", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DesktopMachineMenuPropertyClass: public Ui_DesktopMachineMenuPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESKTOPMACHINEMENUPROPERTY_H
