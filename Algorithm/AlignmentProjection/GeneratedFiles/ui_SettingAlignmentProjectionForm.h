/********************************************************************************
** Form generated from reading UI file 'SettingAlignmentProjectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGALIGNMENTPROJECTIONFORM_H
#define UI_SETTINGALIGNMENTPROJECTIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingAlignmentProjectionForm
{
public:
    QLineEdit *lineEditItemName;
    QDoubleSpinBox *doubleSpinBoxAngle;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;
    QSpinBox *spinBoxUsageLayer;
    QSpinBox *spinBoxPeakCount;
    QPushButton *pushButtonSetAll;
    QPushButton *pushButtonSetOne;
    QPushButton *pushButtonClose;
    QFrame *frameLineGraph;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxAbandonRateL;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBoxAbandonRateH;
    QDoubleSpinBox *doubleSpinBoxPeakIsolation;
    QLabel *label_7;

    void setupUi(QWidget *SettingAlignmentProjectionForm)
    {
        if (SettingAlignmentProjectionForm->objectName().isEmpty())
            SettingAlignmentProjectionForm->setObjectName("SettingAlignmentProjectionForm");
        SettingAlignmentProjectionForm->resize(1039, 577);
        lineEditItemName = new QLineEdit(SettingAlignmentProjectionForm);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(120, 370, 151, 24));
        doubleSpinBoxAngle = new QDoubleSpinBox(SettingAlignmentProjectionForm);
        doubleSpinBoxAngle->setObjectName("doubleSpinBoxAngle");
        doubleSpinBoxAngle->setGeometry(QRect(160, 440, 111, 24));
        doubleSpinBoxAngle->setMaximum(360.000000000000000);
        label_2 = new QLabel(SettingAlignmentProjectionForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 440, 101, 18));
        label_3 = new QLabel(SettingAlignmentProjectionForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 500, 111, 18));
        label_4 = new QLabel(SettingAlignmentProjectionForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 370, 101, 21));
        label = new QLabel(SettingAlignmentProjectionForm);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 410, 101, 18));
        spinBoxUsageLayer = new QSpinBox(SettingAlignmentProjectionForm);
        spinBoxUsageLayer->setObjectName("spinBoxUsageLayer");
        spinBoxUsageLayer->setGeometry(QRect(160, 500, 111, 24));
        spinBoxPeakCount = new QSpinBox(SettingAlignmentProjectionForm);
        spinBoxPeakCount->setObjectName("spinBoxPeakCount");
        spinBoxPeakCount->setGeometry(QRect(160, 410, 111, 24));
        pushButtonSetAll = new QPushButton(SettingAlignmentProjectionForm);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(160, 540, 161, 31));
        pushButtonSetOne = new QPushButton(SettingAlignmentProjectionForm);
        pushButtonSetOne->setObjectName("pushButtonSetOne");
        pushButtonSetOne->setGeometry(QRect(10, 540, 141, 31));
        pushButtonClose = new QPushButton(SettingAlignmentProjectionForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(900, 540, 111, 31));
        frameLineGraph = new QFrame(SettingAlignmentProjectionForm);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(0, 10, 1031, 351));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        label_5 = new QLabel(SettingAlignmentProjectionForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(380, 420, 181, 18));
        doubleSpinBoxAbandonRateL = new QDoubleSpinBox(SettingAlignmentProjectionForm);
        doubleSpinBoxAbandonRateL->setObjectName("doubleSpinBoxAbandonRateL");
        doubleSpinBoxAbandonRateL->setGeometry(QRect(570, 420, 111, 24));
        doubleSpinBoxAbandonRateL->setDecimals(3);
        doubleSpinBoxAbandonRateL->setMaximum(1.000000000000000);
        label_6 = new QLabel(SettingAlignmentProjectionForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(380, 450, 181, 18));
        doubleSpinBoxAbandonRateH = new QDoubleSpinBox(SettingAlignmentProjectionForm);
        doubleSpinBoxAbandonRateH->setObjectName("doubleSpinBoxAbandonRateH");
        doubleSpinBoxAbandonRateH->setGeometry(QRect(570, 450, 111, 24));
        doubleSpinBoxAbandonRateH->setDecimals(3);
        doubleSpinBoxAbandonRateH->setMaximum(1.000000000000000);
        doubleSpinBoxPeakIsolation = new QDoubleSpinBox(SettingAlignmentProjectionForm);
        doubleSpinBoxPeakIsolation->setObjectName("doubleSpinBoxPeakIsolation");
        doubleSpinBoxPeakIsolation->setGeometry(QRect(160, 470, 111, 24));
        doubleSpinBoxPeakIsolation->setMaximum(360.000000000000000);
        label_7 = new QLabel(SettingAlignmentProjectionForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 470, 101, 18));

        retranslateUi(SettingAlignmentProjectionForm);

        QMetaObject::connectSlotsByName(SettingAlignmentProjectionForm);
    } // setupUi

    void retranslateUi(QWidget *SettingAlignmentProjectionForm)
    {
        SettingAlignmentProjectionForm->setWindowTitle(QCoreApplication::translate("SettingAlignmentProjectionForm", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "Angle", nullptr));
        label_3->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "Usage layer", nullptr));
        label_4->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "ItemName", nullptr));
        label->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "Peak count", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "Set to all points", nullptr));
        pushButtonSetOne->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "Set in this point", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "Close", nullptr));
        label_5->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "Abandon rate Low", nullptr));
        label_6->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "Abandon rate High", nullptr));
        label_7->setText(QCoreApplication::translate("SettingAlignmentProjectionForm", "Peak Isolation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingAlignmentProjectionForm: public Ui_SettingAlignmentProjectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGALIGNMENTPROJECTIONFORM_H
