/********************************************************************************
** Form generated from reading UI file 'CameraSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASETTINGFORM_H
#define UI_CAMERASETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CameraSettingClass
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *gbExposureTime;
    QGridLayout *gridLayout_4;
    QLabel *lbExposureTime;
    QSpinBox *sbExposureTime;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *pbShowFactoryControlPanelButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QGroupBox *gbCameraDeviceInfo;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *leModuleNo;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLineEdit *leSerialNo;
    QGroupBox *gbTriggerMode;
    QGridLayout *gridLayout_3;
    QRadioButton *rbTrigger;
    QRadioButton *rbFreeRun;
    QGroupBox *gbGain;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *sbGainR;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *sbGainG;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *sbGainB;
    QGroupBox *groupBox;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxGamma;
    QGroupBox *groupBox_2;
    QComboBox *comboBoxResolution;

    void setupUi(QDialog *CameraSettingClass)
    {
        if (CameraSettingClass->objectName().isEmpty())
            CameraSettingClass->setObjectName(QString::fromUtf8("CameraSettingClass"));
        CameraSettingClass->resize(414, 429);
        gridLayout_5 = new QGridLayout(CameraSettingClass);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gbExposureTime = new QGroupBox(CameraSettingClass);
        gbExposureTime->setObjectName(QString::fromUtf8("gbExposureTime"));
        gridLayout_4 = new QGridLayout(gbExposureTime);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lbExposureTime = new QLabel(gbExposureTime);
        lbExposureTime->setObjectName(QString::fromUtf8("lbExposureTime"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbExposureTime->sizePolicy().hasHeightForWidth());
        lbExposureTime->setSizePolicy(sizePolicy);
        lbExposureTime->setMinimumSize(QSize(80, 0));

        gridLayout_4->addWidget(lbExposureTime, 0, 3, 1, 1);

        sbExposureTime = new QSpinBox(gbExposureTime);
        sbExposureTime->setObjectName(QString::fromUtf8("sbExposureTime"));
        sbExposureTime->setMinimum(1);
        sbExposureTime->setMaximum(15000);

        gridLayout_4->addWidget(sbExposureTime, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        label_5 = new QLabel(gbExposureTime);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 2, 1, 1);


        gridLayout_5->addWidget(gbExposureTime, 1, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        pbShowFactoryControlPanelButton = new QPushButton(CameraSettingClass);
        pbShowFactoryControlPanelButton->setObjectName(QString::fromUtf8("pbShowFactoryControlPanelButton"));

        hboxLayout->addWidget(pbShowFactoryControlPanelButton);

        okButton = new QPushButton(CameraSettingClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(CameraSettingClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout_5->addLayout(hboxLayout, 3, 0, 1, 2);

        gbCameraDeviceInfo = new QGroupBox(CameraSettingClass);
        gbCameraDeviceInfo->setObjectName(QString::fromUtf8("gbCameraDeviceInfo"));
        gridLayout_2 = new QGridLayout(gbCameraDeviceInfo);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(gbCameraDeviceInfo);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_6);

        leModuleNo = new QLineEdit(gbCameraDeviceInfo);
        leModuleNo->setObjectName(QString::fromUtf8("leModuleNo"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leModuleNo->sizePolicy().hasHeightForWidth());
        leModuleNo->setSizePolicy(sizePolicy1);
        leModuleNo->setReadOnly(true);

        horizontalLayout_2->addWidget(leModuleNo);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_7 = new QLabel(gbCameraDeviceInfo);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_7);

        leSerialNo = new QLineEdit(gbCameraDeviceInfo);
        leSerialNo->setObjectName(QString::fromUtf8("leSerialNo"));
        sizePolicy1.setHeightForWidth(leSerialNo->sizePolicy().hasHeightForWidth());
        leSerialNo->setSizePolicy(sizePolicy1);
        leSerialNo->setReadOnly(true);

        horizontalLayout_3->addWidget(leSerialNo);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        gridLayout_5->addWidget(gbCameraDeviceInfo, 0, 0, 1, 1);

        gbTriggerMode = new QGroupBox(CameraSettingClass);
        gbTriggerMode->setObjectName(QString::fromUtf8("gbTriggerMode"));
        gridLayout_3 = new QGridLayout(gbTriggerMode);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        rbTrigger = new QRadioButton(gbTriggerMode);
        rbTrigger->setObjectName(QString::fromUtf8("rbTrigger"));
        rbTrigger->setChecked(true);

        gridLayout_3->addWidget(rbTrigger, 1, 0, 1, 1);

        rbFreeRun = new QRadioButton(gbTriggerMode);
        rbFreeRun->setObjectName(QString::fromUtf8("rbFreeRun"));

        gridLayout_3->addWidget(rbFreeRun, 2, 0, 1, 1);


        gridLayout_5->addWidget(gbTriggerMode, 0, 1, 1, 1);

        gbGain = new QGroupBox(CameraSettingClass);
        gbGain->setObjectName(QString::fromUtf8("gbGain"));
        gridLayout = new QGridLayout(gbGain);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(gbGain);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        sbGainR = new QSpinBox(gbGain);
        sbGainR->setObjectName(QString::fromUtf8("sbGainR"));
        sbGainR->setMinimum(1);
        sbGainR->setMaximum(64);
        sbGainR->setValue(1);

        horizontalLayout->addWidget(sbGainR);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(gbGain);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        sbGainG = new QSpinBox(gbGain);
        sbGainG->setObjectName(QString::fromUtf8("sbGainG"));
        sbGainG->setMinimum(1);
        sbGainG->setMaximum(64);
        sbGainG->setValue(1);

        horizontalLayout_4->addWidget(sbGainG);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(gbGain);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        sbGainB = new QSpinBox(gbGain);
        sbGainB->setObjectName(QString::fromUtf8("sbGainB"));
        sbGainB->setMinimum(1);
        sbGainB->setMaximum(64);
        sbGainB->setValue(1);

        horizontalLayout_5->addWidget(sbGainB);


        gridLayout->addLayout(horizontalLayout_5, 2, 0, 1, 1);


        gridLayout_5->addWidget(gbGain, 1, 1, 1, 1);

        groupBox = new QGroupBox(CameraSettingClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 20, 101, 21));
        doubleSpinBoxGamma = new QDoubleSpinBox(groupBox);
        doubleSpinBoxGamma->setObjectName(QString::fromUtf8("doubleSpinBoxGamma"));
        doubleSpinBoxGamma->setGeometry(QRect(130, 20, 81, 22));

        gridLayout_5->addWidget(groupBox, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(CameraSettingClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        comboBoxResolution = new QComboBox(groupBox_2);
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->addItem(QString());
        comboBoxResolution->setObjectName(QString::fromUtf8("comboBoxResolution"));
        comboBoxResolution->setGeometry(QRect(10, 30, 111, 22));

        gridLayout_5->addWidget(groupBox_2, 2, 1, 1, 1);

        QWidget::setTabOrder(sbGainR, rbTrigger);
        QWidget::setTabOrder(rbTrigger, rbFreeRun);
        QWidget::setTabOrder(rbFreeRun, pbShowFactoryControlPanelButton);
        QWidget::setTabOrder(pbShowFactoryControlPanelButton, okButton);
        QWidget::setTabOrder(okButton, cancelButton);
        QWidget::setTabOrder(cancelButton, leModuleNo);
        QWidget::setTabOrder(leModuleNo, leSerialNo);

        retranslateUi(CameraSettingClass);
        QObject::connect(okButton, SIGNAL(clicked()), CameraSettingClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), CameraSettingClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(CameraSettingClass);
    } // setupUi

    void retranslateUi(QDialog *CameraSettingClass)
    {
        CameraSettingClass->setWindowTitle(QCoreApplication::translate("CameraSettingClass", "CameraSettingForm", nullptr));
        gbExposureTime->setTitle(QCoreApplication::translate("CameraSettingClass", "ExposureTime", nullptr));
        lbExposureTime->setText(QCoreApplication::translate("CameraSettingClass", "TextLabel", nullptr));
#if QT_CONFIG(tooltip)
        sbExposureTime->setToolTip(QCoreApplication::translate("CameraSettingClass", "1 to 15000", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("CameraSettingClass", "* 50us = ", nullptr));
        pbShowFactoryControlPanelButton->setText(QCoreApplication::translate("CameraSettingClass", "Factory Control Panel", nullptr));
        okButton->setText(QCoreApplication::translate("CameraSettingClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("CameraSettingClass", "Cancel", nullptr));
        gbCameraDeviceInfo->setTitle(QCoreApplication::translate("CameraSettingClass", "Device Infomation", nullptr));
        label_6->setText(QCoreApplication::translate("CameraSettingClass", "Module No.", nullptr));
        label_7->setText(QCoreApplication::translate("CameraSettingClass", "Serial No", nullptr));
        gbTriggerMode->setTitle(QCoreApplication::translate("CameraSettingClass", "TriggerMode", nullptr));
        rbTrigger->setText(QCoreApplication::translate("CameraSettingClass", "TriggerInput", nullptr));
        rbFreeRun->setText(QCoreApplication::translate("CameraSettingClass", "FreeRun", nullptr));
        gbGain->setTitle(QCoreApplication::translate("CameraSettingClass", "Gain", nullptr));
        label->setText(QCoreApplication::translate("CameraSettingClass", "R", nullptr));
#if QT_CONFIG(tooltip)
        sbGainR->setToolTip(QCoreApplication::translate("CameraSettingClass", "1 to 64", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("CameraSettingClass", "G", nullptr));
#if QT_CONFIG(tooltip)
        sbGainG->setToolTip(QCoreApplication::translate("CameraSettingClass", "1 to 64", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("CameraSettingClass", "B", nullptr));
#if QT_CONFIG(tooltip)
        sbGainB->setToolTip(QCoreApplication::translate("CameraSettingClass", "1 to 64", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("CameraSettingClass", "Gamma", nullptr));
        label_4->setText(QCoreApplication::translate("CameraSettingClass", "Strength", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CameraSettingClass", "Resolution", nullptr));
        comboBoxResolution->setItemText(0, QCoreApplication::translate("CameraSettingClass", "0 : Undefined", nullptr));
        comboBoxResolution->setItemText(1, QCoreApplication::translate("CameraSettingClass", "1: 64 x 64", nullptr));
        comboBoxResolution->setItemText(2, QCoreApplication::translate("CameraSettingClass", "2: 160 x 120", nullptr));
        comboBoxResolution->setItemText(3, QCoreApplication::translate("CameraSettingClass", "3: 320 x 240", nullptr));
        comboBoxResolution->setItemText(4, QCoreApplication::translate("CameraSettingClass", "4: 640 x 480", nullptr));
        comboBoxResolution->setItemText(5, QCoreApplication::translate("CameraSettingClass", "5: 752 x 480", nullptr));
        comboBoxResolution->setItemText(6, QCoreApplication::translate("CameraSettingClass", "6: 800 x 600", nullptr));
        comboBoxResolution->setItemText(7, QCoreApplication::translate("CameraSettingClass", "7: 1024 x 768", nullptr));
        comboBoxResolution->setItemText(8, QCoreApplication::translate("CameraSettingClass", "8: 1280 x 1024", nullptr));
        comboBoxResolution->setItemText(9, QCoreApplication::translate("CameraSettingClass", "9: 1600 x 1200", nullptr));
        comboBoxResolution->setItemText(10, QCoreApplication::translate("CameraSettingClass", "10: 2048 x 1536", nullptr));
        comboBoxResolution->setItemText(11, QCoreApplication::translate("CameraSettingClass", "11: 2592 x 1944", nullptr));

    } // retranslateUi

};

namespace Ui {
    class CameraSettingClass: public Ui_CameraSettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASETTINGFORM_H
