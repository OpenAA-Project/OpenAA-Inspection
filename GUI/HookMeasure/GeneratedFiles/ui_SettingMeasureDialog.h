/********************************************************************************
** Form generated from reading UI file 'SettingMeasureDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGMEASUREDIALOG_H
#define UI_SETTINGMEASUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingMeasureDialog
{
public:
    QToolButton *toolButtonLineColor;
    QToolButton *toolButtonCircleColor;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBoxLineWidth;
    QSpinBox *spinBoxTextSize;
    QSpinBox *spinBoxArrowSize;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxCircleSize;
    QLabel *label_6;

    void setupUi(QDialog *SettingMeasureDialog)
    {
        if (SettingMeasureDialog->objectName().isEmpty())
            SettingMeasureDialog->setObjectName("SettingMeasureDialog");
        SettingMeasureDialog->resize(230, 319);
        toolButtonLineColor = new QToolButton(SettingMeasureDialog);
        toolButtonLineColor->setObjectName("toolButtonLineColor");
        toolButtonLineColor->setGeometry(QRect(130, 10, 41, 41));
        toolButtonCircleColor = new QToolButton(SettingMeasureDialog);
        toolButtonCircleColor->setObjectName("toolButtonCircleColor");
        toolButtonCircleColor->setGeometry(QRect(130, 50, 41, 41));
        label = new QLabel(SettingMeasureDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 10, 81, 41));
        label_2 = new QLabel(SettingMeasureDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 50, 91, 41));
        label_3 = new QLabel(SettingMeasureDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 90, 91, 41));
        label_4 = new QLabel(SettingMeasureDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 170, 101, 41));
        label_5 = new QLabel(SettingMeasureDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 210, 101, 41));
        spinBoxLineWidth = new QSpinBox(SettingMeasureDialog);
        spinBoxLineWidth->setObjectName("spinBoxLineWidth");
        spinBoxLineWidth->setGeometry(QRect(130, 100, 81, 24));
        spinBoxTextSize = new QSpinBox(SettingMeasureDialog);
        spinBoxTextSize->setObjectName("spinBoxTextSize");
        spinBoxTextSize->setGeometry(QRect(130, 180, 81, 24));
        spinBoxArrowSize = new QSpinBox(SettingMeasureDialog);
        spinBoxArrowSize->setObjectName("spinBoxArrowSize");
        spinBoxArrowSize->setGeometry(QRect(130, 220, 81, 24));
        spinBoxArrowSize->setMaximum(200);
        pushButtonOK = new QPushButton(SettingMeasureDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 270, 81, 34));
        pushButtonCancel = new QPushButton(SettingMeasureDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 270, 81, 34));
        spinBoxCircleSize = new QSpinBox(SettingMeasureDialog);
        spinBoxCircleSize->setObjectName("spinBoxCircleSize");
        spinBoxCircleSize->setGeometry(QRect(130, 140, 81, 24));
        label_6 = new QLabel(SettingMeasureDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 130, 121, 41));

        retranslateUi(SettingMeasureDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingMeasureDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingMeasureDialog)
    {
        SettingMeasureDialog->setWindowTitle(QCoreApplication::translate("SettingMeasureDialog", "Dialog", nullptr));
        toolButtonLineColor->setText(QString());
        toolButtonCircleColor->setText(QString());
        label->setText(QCoreApplication::translate("SettingMeasureDialog", "\347\267\232\343\201\256\350\211\262", nullptr));
        label_2->setText(QCoreApplication::translate("SettingMeasureDialog", "\345\210\266\345\276\241\347\202\271\343\201\256\350\211\262", nullptr));
        label_3->setText(QCoreApplication::translate("SettingMeasureDialog", "\347\267\232\345\271\205", nullptr));
        label_4->setText(QCoreApplication::translate("SettingMeasureDialog", "\346\226\207\345\255\227\343\201\256\345\244\247\343\201\215\343\201\225", nullptr));
        label_5->setText(QCoreApplication::translate("SettingMeasureDialog", "\347\237\242\345\215\260\343\201\256\345\244\247\343\201\215\343\201\225", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingMeasureDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingMeasureDialog", "Cancel", nullptr));
        label_6->setText(QCoreApplication::translate("SettingMeasureDialog", "\345\210\266\345\276\241\347\202\271\343\201\256\345\244\247\343\201\215\343\201\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingMeasureDialog: public Ui_SettingMeasureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGMEASUREDIALOG_H
