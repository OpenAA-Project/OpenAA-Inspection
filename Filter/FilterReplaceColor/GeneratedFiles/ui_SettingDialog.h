/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBoxSourceLayer;
    QComboBox *comboBoxAdaptedLayer;
    QFrame *frame;
    QToolButton *toolButtonReplaceBrightness;
    QToolButton *toolButtonShiftBrightness;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_7;
    QLabel *label_4;
    QSpinBox *spinBoxAdaptedBrightnessToReplace;
    QLabel *label_6;
    QSpinBox *spinBoxPickupBrightnessLToReplace;
    QSpinBox *spinBoxPickupBrightnessHToReplace;
    QWidget *page_2;
    QLabel *label_5;
    QSpinBox *spinBoxAddedBrightnessToShift;
    QSpinBox *spinBoxPickupBrightnessHToShift;
    QLabel *label_3;
    QLabel *label_8;
    QSpinBox *spinBoxPickupBrightnessLToShift;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(533, 230);
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 101, 16));
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 101, 16));
        comboBoxSourceLayer = new QComboBox(SettingDialog);
        comboBoxSourceLayer->setObjectName("comboBoxSourceLayer");
        comboBoxSourceLayer->setGeometry(QRect(30, 30, 80, 22));
        comboBoxAdaptedLayer = new QComboBox(SettingDialog);
        comboBoxAdaptedLayer->setObjectName("comboBoxAdaptedLayer");
        comboBoxAdaptedLayer->setGeometry(QRect(30, 110, 80, 22));
        frame = new QFrame(SettingDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(130, 10, 161, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonReplaceBrightness = new QToolButton(frame);
        toolButtonReplaceBrightness->setObjectName("toolButtonReplaceBrightness");
        toolButtonReplaceBrightness->setGeometry(QRect(10, 10, 141, 31));
        toolButtonReplaceBrightness->setCheckable(true);
        toolButtonReplaceBrightness->setChecked(true);
        toolButtonReplaceBrightness->setAutoExclusive(true);
        toolButtonShiftBrightness = new QToolButton(frame);
        toolButtonShiftBrightness->setObjectName("toolButtonShiftBrightness");
        toolButtonShiftBrightness->setGeometry(QRect(10, 40, 141, 31));
        toolButtonShiftBrightness->setCheckable(true);
        toolButtonShiftBrightness->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(SettingDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(300, 20, 221, 121));
        stackedWidget->setFrameShape(QFrame::Panel);
        stackedWidget->setFrameShadow(QFrame::Sunken);
        page = new QWidget();
        page->setObjectName("page");
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 10, 201, 16));
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 70, 201, 16));
        spinBoxAdaptedBrightnessToReplace = new QSpinBox(page);
        spinBoxAdaptedBrightnessToReplace->setObjectName("spinBoxAdaptedBrightnessToReplace");
        spinBoxAdaptedBrightnessToReplace->setGeometry(QRect(10, 90, 71, 22));
        spinBoxAdaptedBrightnessToReplace->setMaximum(255);
        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(100, 30, 16, 20));
        spinBoxPickupBrightnessLToReplace = new QSpinBox(page);
        spinBoxPickupBrightnessLToReplace->setObjectName("spinBoxPickupBrightnessLToReplace");
        spinBoxPickupBrightnessLToReplace->setGeometry(QRect(10, 30, 71, 22));
        spinBoxPickupBrightnessLToReplace->setMaximum(255);
        spinBoxPickupBrightnessHToReplace = new QSpinBox(page);
        spinBoxPickupBrightnessHToReplace->setObjectName("spinBoxPickupBrightnessHToReplace");
        spinBoxPickupBrightnessHToReplace->setGeometry(QRect(130, 30, 71, 22));
        spinBoxPickupBrightnessHToReplace->setMaximum(255);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_5 = new QLabel(page_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 30, 16, 20));
        spinBoxAddedBrightnessToShift = new QSpinBox(page_2);
        spinBoxAddedBrightnessToShift->setObjectName("spinBoxAddedBrightnessToShift");
        spinBoxAddedBrightnessToShift->setGeometry(QRect(10, 90, 71, 22));
        spinBoxAddedBrightnessToShift->setMinimum(-255);
        spinBoxAddedBrightnessToShift->setMaximum(255);
        spinBoxPickupBrightnessHToShift = new QSpinBox(page_2);
        spinBoxPickupBrightnessHToShift->setObjectName("spinBoxPickupBrightnessHToShift");
        spinBoxPickupBrightnessHToShift->setGeometry(QRect(130, 30, 71, 22));
        spinBoxPickupBrightnessHToShift->setMaximum(255);
        label_3 = new QLabel(page_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 201, 16));
        label_8 = new QLabel(page_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 70, 201, 16));
        spinBoxPickupBrightnessLToShift = new QSpinBox(page_2);
        spinBoxPickupBrightnessLToShift->setObjectName("spinBoxPickupBrightnessLToShift");
        spinBoxPickupBrightnessLToShift->setGeometry(QRect(10, 30, 71, 22));
        spinBoxPickupBrightnessLToShift->setMaximum(255);
        stackedWidget->addWidget(page_2);
        pushButtonOK = new QPushButton(SettingDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(110, 170, 111, 41));
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(300, 170, 111, 41));

        retranslateUi(SettingDialog);

        stackedWidget->setCurrentIndex(1);
        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Setting replace-color", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "Source layer", nullptr));
        label_2->setText(QCoreApplication::translate("SettingDialog", "Adapted layer", nullptr));
        toolButtonReplaceBrightness->setText(QCoreApplication::translate("SettingDialog", "Replace brightness", nullptr));
        toolButtonShiftBrightness->setText(QCoreApplication::translate("SettingDialog", "Shift brightness", nullptr));
        label_7->setText(QCoreApplication::translate("SettingDialog", "Brightness range to pick up", nullptr));
        label_4->setText(QCoreApplication::translate("SettingDialog", "Brightness to replace", nullptr));
        label_6->setText(QCoreApplication::translate("SettingDialog", "-", nullptr));
        label_5->setText(QCoreApplication::translate("SettingDialog", "-", nullptr));
        label_3->setText(QCoreApplication::translate("SettingDialog", "Brightness range to pick up", nullptr));
        label_8->setText(QCoreApplication::translate("SettingDialog", "Added brightness", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
