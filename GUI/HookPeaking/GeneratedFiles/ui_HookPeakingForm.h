/********************************************************************************
** Form generated from reading UI file 'HookPeakingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOOKPEAKINGFORM_H
#define UI_HOOKPEAKINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_HookPeakingForm
{
public:
    QToolButton *toolButtonMode;
    QToolButton *toolButtonColor;
    QSlider *horizontalSliderTransparentRate;
    QLabel *labelTransparent;
    QLabel *label_2;

    void setupUi(GUIFormBase *HookPeakingForm)
    {
        if (HookPeakingForm->objectName().isEmpty())
            HookPeakingForm->setObjectName("HookPeakingForm");
        HookPeakingForm->resize(297, 42);
        toolButtonMode = new QToolButton(HookPeakingForm);
        toolButtonMode->setObjectName("toolButtonMode");
        toolButtonMode->setGeometry(QRect(0, 0, 42, 42));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Resources/PeakingN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon.addFile(QString::fromUtf8(":/Resources/Resources/PeakingS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonMode->setIcon(icon);
        toolButtonMode->setIconSize(QSize(42, 42));
        toolButtonMode->setCheckable(true);
        toolButtonColor = new QToolButton(HookPeakingForm);
        toolButtonColor->setObjectName("toolButtonColor");
        toolButtonColor->setGeometry(QRect(50, 0, 41, 41));
        horizontalSliderTransparentRate = new QSlider(HookPeakingForm);
        horizontalSliderTransparentRate->setObjectName("horizontalSliderTransparentRate");
        horizontalSliderTransparentRate->setGeometry(QRect(100, 10, 141, 22));
        horizontalSliderTransparentRate->setMaximum(100);
        horizontalSliderTransparentRate->setPageStep(8);
        horizontalSliderTransparentRate->setValue(80);
        horizontalSliderTransparentRate->setOrientation(Qt::Horizontal);
        labelTransparent = new QLabel(HookPeakingForm);
        labelTransparent->setObjectName("labelTransparent");
        labelTransparent->setGeometry(QRect(250, 0, 31, 41));
        label_2 = new QLabel(HookPeakingForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(280, 10, 21, 21));

        retranslateUi(HookPeakingForm);

        QMetaObject::connectSlotsByName(HookPeakingForm);
    } // setupUi

    void retranslateUi(GUIFormBase *HookPeakingForm)
    {
        HookPeakingForm->setWindowTitle(QCoreApplication::translate("HookPeakingForm", "Form", nullptr));
        toolButtonMode->setText(QString());
        toolButtonColor->setText(QString());
        labelTransparent->setText(QCoreApplication::translate("HookPeakingForm", "100", nullptr));
        label_2->setText(QCoreApplication::translate("HookPeakingForm", "%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HookPeakingForm: public Ui_HookPeakingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOOKPEAKINGFORM_H
