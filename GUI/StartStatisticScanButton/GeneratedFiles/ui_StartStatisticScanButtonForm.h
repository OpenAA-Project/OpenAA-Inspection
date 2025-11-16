/********************************************************************************
** Form generated from reading UI file 'StartStatisticScanButtonForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTSTATISTICSCANBUTTONFORM_H
#define UI_STARTSTATISTICSCANBUTTONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_StartStatisticScanButtonFormClass
{
public:
    QLabel *label;
    QSpinBox *spinBoxMaxCount;
    QLabel *label_2;
    QLabel *labelNowCount;

    void setupUi(GUIFormBase *StartStatisticScanButtonFormClass)
    {
        if (StartStatisticScanButtonFormClass->objectName().isEmpty())
            StartStatisticScanButtonFormClass->setObjectName("StartStatisticScanButtonFormClass");
        StartStatisticScanButtonFormClass->resize(234, 40);
        label = new QLabel(StartStatisticScanButtonFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 0, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMaxCount = new QSpinBox(StartStatisticScanButtonFormClass);
        spinBoxMaxCount->setObjectName("spinBoxMaxCount");
        spinBoxMaxCount->setGeometry(QRect(170, 0, 61, 22));
        label_2 = new QLabel(StartStatisticScanButtonFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 20, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelNowCount = new QLabel(StartStatisticScanButtonFormClass);
        labelNowCount->setObjectName("labelNowCount");
        labelNowCount->setGeometry(QRect(170, 20, 61, 21));
        labelNowCount->setFrameShape(QFrame::Panel);
        labelNowCount->setFrameShadow(QFrame::Sunken);
        labelNowCount->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(StartStatisticScanButtonFormClass);

        QMetaObject::connectSlotsByName(StartStatisticScanButtonFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *StartStatisticScanButtonFormClass)
    {
        StartStatisticScanButtonFormClass->setWindowTitle(QCoreApplication::translate("StartStatisticScanButtonFormClass", "StartStatisticScanButtonForm", nullptr));
        label->setText(QCoreApplication::translate("StartStatisticScanButtonFormClass", "Max Count", nullptr));
        label_2->setText(QCoreApplication::translate("StartStatisticScanButtonFormClass", "Now", nullptr));
        labelNowCount->setText(QCoreApplication::translate("StartStatisticScanButtonFormClass", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartStatisticScanButtonFormClass: public Ui_StartStatisticScanButtonFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSTATISTICSCANBUTTONFORM_H
