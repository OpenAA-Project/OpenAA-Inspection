/********************************************************************************
** Form generated from reading UI file 'VRSSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VRSSETTINGFORM_H
#define UI_VRSSETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VRSSettingClass
{
public:
    QGridLayout *gridLayout_11;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QGroupBox *gbVRSSide;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QComboBox *cbRotation;
    QLabel *label_8;
    QGroupBox *gbCameraState;
    QGridLayout *gridLayout_10;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbVRSResolution;
    QSpinBox *sbVRSResolution;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbVRSViewSise;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbVRSViewSizeW;
    QSpinBox *sbCameraWidth;
    QLabel *label_12;
    QVBoxLayout *verticalLayout;
    QLabel *lbVRSViewSizeH;
    QSpinBox *sbCameraHeight;
    QGroupBox *gbMotorState;
    QGridLayout *gridLayout_8;
    QGroupBox *gbMotorMovableAreaSize;
    QGridLayout *gridLayout_4;
    QLabel *lbMotorMovableAreaSizeW;
    QLabel *lbMotorMovableAreaSizeH;
    QSpinBox *sbMotorMovableAreaSizeW;
    QSpinBox *sbMotorMovableAreaSizeH;
    QLabel *label_22;
    QLabel *label_23;
    QGroupBox *gbZMotor;
    QGridLayout *gridLayout_6;
    QSpinBox *sbMotorZInitDistance;
    QLabel *label_19;
    QLabel *label_30;
    QGroupBox *gbMotorOriginPosition;
    QGridLayout *gridLayout_3;
    QLabel *label_13;
    QLabel *label_14;
    QSpinBox *sbMotorOriginY;
    QSpinBox *sbMotorOriginX;
    QLabel *label_26;
    QLabel *label_27;
    QGroupBox *gbMotorEscapePosition;
    QGridLayout *gridLayout_5;
    QLabel *label_17;
    QLabel *label_18;
    QSpinBox *sbMotorEscapeX;
    QSpinBox *sbMotorEscapeY;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label;
    QSpinBox *sbMotorEscapeZ;
    QLabel *label_5;
    QGroupBox *gbMotorOffset;
    QGridLayout *gridLayout_7;
    QSpinBox *sbMotorOffsetX;
    QLabel *label_20;
    QLabel *label_21;
    QSpinBox *sbMotorOffsetY;
    QLabel *label_28;
    QLabel *label_29;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *gbInspectionSide;
    QGridLayout *gridLayout_2;
    QGroupBox *gbInspectOffset;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QSpinBox *sbInspectOffsetX;
    QLabel *label_4;
    QSpinBox *sbInspectOffsetY;
    QHBoxLayout *horizontalLayout;
    QLabel *lbInsResolution;
    QSpinBox *sbInspectResolution;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *VRSSettingClass)
    {
        if (VRSSettingClass->objectName().isEmpty())
            VRSSettingClass->setObjectName(QString::fromUtf8("VRSSettingClass"));
        VRSSettingClass->resize(562, 756);
        gridLayout_11 = new QGridLayout(VRSSettingClass);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(VRSSettingClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(VRSSettingClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout_11->addLayout(hboxLayout, 2, 1, 1, 3);

        gbVRSSide = new QGroupBox(VRSSettingClass);
        gbVRSSide->setObjectName(QString::fromUtf8("gbVRSSide"));
        gridLayout_9 = new QGridLayout(gbVRSSide);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_7 = new QLabel(gbVRSSide);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        cbRotation = new QComboBox(gbVRSSide);
        cbRotation->addItem(QString());
        cbRotation->addItem(QString());
        cbRotation->addItem(QString());
        cbRotation->addItem(QString());
        cbRotation->setObjectName(QString::fromUtf8("cbRotation"));
        cbRotation->setInsertPolicy(QComboBox::NoInsert);
        cbRotation->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(cbRotation);

        label_8 = new QLabel(gbVRSSide);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_3->addWidget(label_8);


        gridLayout_9->addLayout(horizontalLayout_3, 0, 1, 1, 2);

        gbCameraState = new QGroupBox(gbVRSSide);
        gbCameraState->setObjectName(QString::fromUtf8("gbCameraState"));
        gridLayout_10 = new QGridLayout(gbCameraState);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lbVRSResolution = new QLabel(gbCameraState);
        lbVRSResolution->setObjectName(QString::fromUtf8("lbVRSResolution"));

        horizontalLayout_2->addWidget(lbVRSResolution);

        sbVRSResolution = new QSpinBox(gbCameraState);
        sbVRSResolution->setObjectName(QString::fromUtf8("sbVRSResolution"));
        sbVRSResolution->setMaximum(99999999);
        sbVRSResolution->setValue(20);

        horizontalLayout_2->addWidget(sbVRSResolution);

        label_6 = new QLabel(gbCameraState);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout_10->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lbVRSViewSise = new QLabel(gbCameraState);
        lbVRSViewSise->setObjectName(QString::fromUtf8("lbVRSViewSise"));

        horizontalLayout_4->addWidget(lbVRSViewSise);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lbVRSViewSizeW = new QLabel(gbCameraState);
        lbVRSViewSizeW->setObjectName(QString::fromUtf8("lbVRSViewSizeW"));
        lbVRSViewSizeW->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lbVRSViewSizeW);

        sbCameraWidth = new QSpinBox(gbCameraState);
        sbCameraWidth->setObjectName(QString::fromUtf8("sbCameraWidth"));
        sbCameraWidth->setMaximum(99999999);
        sbCameraWidth->setValue(4700);

        verticalLayout_2->addWidget(sbCameraWidth);


        horizontalLayout_4->addLayout(verticalLayout_2);

        label_12 = new QLabel(gbCameraState);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_4->addWidget(label_12);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbVRSViewSizeH = new QLabel(gbCameraState);
        lbVRSViewSizeH->setObjectName(QString::fromUtf8("lbVRSViewSizeH"));
        lbVRSViewSizeH->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lbVRSViewSizeH);

        sbCameraHeight = new QSpinBox(gbCameraState);
        sbCameraHeight->setObjectName(QString::fromUtf8("sbCameraHeight"));
        sbCameraHeight->setMaximum(99999999);
        sbCameraHeight->setValue(4000);

        verticalLayout->addWidget(sbCameraHeight);


        horizontalLayout_4->addLayout(verticalLayout);


        gridLayout_10->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout_9->addWidget(gbCameraState, 1, 1, 1, 2);

        gbMotorState = new QGroupBox(gbVRSSide);
        gbMotorState->setObjectName(QString::fromUtf8("gbMotorState"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gbMotorState->sizePolicy().hasHeightForWidth());
        gbMotorState->setSizePolicy(sizePolicy);
        gridLayout_8 = new QGridLayout(gbMotorState);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gbMotorMovableAreaSize = new QGroupBox(gbMotorState);
        gbMotorMovableAreaSize->setObjectName(QString::fromUtf8("gbMotorMovableAreaSize"));
        gridLayout_4 = new QGridLayout(gbMotorMovableAreaSize);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lbMotorMovableAreaSizeW = new QLabel(gbMotorMovableAreaSize);
        lbMotorMovableAreaSizeW->setObjectName(QString::fromUtf8("lbMotorMovableAreaSizeW"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbMotorMovableAreaSizeW->sizePolicy().hasHeightForWidth());
        lbMotorMovableAreaSizeW->setSizePolicy(sizePolicy1);
        lbMotorMovableAreaSizeW->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lbMotorMovableAreaSizeW, 0, 0, 1, 1);

        lbMotorMovableAreaSizeH = new QLabel(gbMotorMovableAreaSize);
        lbMotorMovableAreaSizeH->setObjectName(QString::fromUtf8("lbMotorMovableAreaSizeH"));
        sizePolicy1.setHeightForWidth(lbMotorMovableAreaSizeH->sizePolicy().hasHeightForWidth());
        lbMotorMovableAreaSizeH->setSizePolicy(sizePolicy1);
        lbMotorMovableAreaSizeH->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lbMotorMovableAreaSizeH, 1, 0, 1, 1);

        sbMotorMovableAreaSizeW = new QSpinBox(gbMotorMovableAreaSize);
        sbMotorMovableAreaSizeW->setObjectName(QString::fromUtf8("sbMotorMovableAreaSizeW"));
        sbMotorMovableAreaSizeW->setMaximum(99999999);
        sbMotorMovableAreaSizeW->setValue(350);

        gridLayout_4->addWidget(sbMotorMovableAreaSizeW, 0, 1, 1, 1);

        sbMotorMovableAreaSizeH = new QSpinBox(gbMotorMovableAreaSize);
        sbMotorMovableAreaSizeH->setObjectName(QString::fromUtf8("sbMotorMovableAreaSizeH"));
        sbMotorMovableAreaSizeH->setMaximum(99999999);
        sbMotorMovableAreaSizeH->setValue(350);

        gridLayout_4->addWidget(sbMotorMovableAreaSizeH, 1, 1, 1, 1);

        label_22 = new QLabel(gbMotorMovableAreaSize);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(label_22, 0, 2, 1, 1);

        label_23 = new QLabel(gbMotorMovableAreaSize);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy2.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(label_23, 1, 2, 1, 1);


        gridLayout_8->addWidget(gbMotorMovableAreaSize, 2, 1, 1, 1);

        gbZMotor = new QGroupBox(gbMotorState);
        gbZMotor->setObjectName(QString::fromUtf8("gbZMotor"));
        gridLayout_6 = new QGridLayout(gbZMotor);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        sbMotorZInitDistance = new QSpinBox(gbZMotor);
        sbMotorZInitDistance->setObjectName(QString::fromUtf8("sbMotorZInitDistance"));
        sbMotorZInitDistance->setMaximum(99999999);

        gridLayout_6->addWidget(sbMotorZInitDistance, 0, 1, 1, 1);

        label_19 = new QLabel(gbZMotor);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy1);
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_19, 0, 0, 1, 1);

        label_30 = new QLabel(gbZMotor);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        sizePolicy2.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy2);

        gridLayout_6->addWidget(label_30, 0, 2, 1, 1);


        gridLayout_8->addWidget(gbZMotor, 4, 1, 1, 1);

        gbMotorOriginPosition = new QGroupBox(gbMotorState);
        gbMotorOriginPosition->setObjectName(QString::fromUtf8("gbMotorOriginPosition"));
        gridLayout_3 = new QGridLayout(gbMotorOriginPosition);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_13 = new QLabel(gbMotorOriginPosition);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_13, 1, 1, 1, 1);

        label_14 = new QLabel(gbMotorOriginPosition);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy1.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy1);
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_14, 0, 1, 1, 1);

        sbMotorOriginY = new QSpinBox(gbMotorOriginPosition);
        sbMotorOriginY->setObjectName(QString::fromUtf8("sbMotorOriginY"));
        sbMotorOriginY->setMaximum(99999999);

        gridLayout_3->addWidget(sbMotorOriginY, 1, 2, 1, 1);

        sbMotorOriginX = new QSpinBox(gbMotorOriginPosition);
        sbMotorOriginX->setObjectName(QString::fromUtf8("sbMotorOriginX"));
        sbMotorOriginX->setMaximum(99999999);

        gridLayout_3->addWidget(sbMotorOriginX, 0, 2, 1, 1);

        label_26 = new QLabel(gbMotorOriginPosition);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy2.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label_26, 0, 3, 1, 1);

        label_27 = new QLabel(gbMotorOriginPosition);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        sizePolicy2.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label_27, 1, 3, 1, 1);


        gridLayout_8->addWidget(gbMotorOriginPosition, 0, 1, 1, 1);

        gbMotorEscapePosition = new QGroupBox(gbMotorState);
        gbMotorEscapePosition->setObjectName(QString::fromUtf8("gbMotorEscapePosition"));
        gridLayout_5 = new QGridLayout(gbMotorEscapePosition);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_17 = new QLabel(gbMotorEscapePosition);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy1);
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_17, 0, 0, 1, 1);

        label_18 = new QLabel(gbMotorEscapePosition);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy1);
        label_18->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_18, 1, 0, 1, 1);

        sbMotorEscapeX = new QSpinBox(gbMotorEscapePosition);
        sbMotorEscapeX->setObjectName(QString::fromUtf8("sbMotorEscapeX"));
        sbMotorEscapeX->setMaximum(99999999);

        gridLayout_5->addWidget(sbMotorEscapeX, 0, 1, 1, 1);

        sbMotorEscapeY = new QSpinBox(gbMotorEscapePosition);
        sbMotorEscapeY->setObjectName(QString::fromUtf8("sbMotorEscapeY"));
        sbMotorEscapeY->setMaximum(99999999);

        gridLayout_5->addWidget(sbMotorEscapeY, 1, 1, 1, 1);

        label_24 = new QLabel(gbMotorEscapePosition);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        sizePolicy2.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(label_24, 0, 2, 1, 1);

        label_25 = new QLabel(gbMotorEscapePosition);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy2.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(label_25, 1, 2, 1, 1);

        label = new QLabel(gbMotorEscapePosition);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label, 2, 0, 1, 1);

        sbMotorEscapeZ = new QSpinBox(gbMotorEscapePosition);
        sbMotorEscapeZ->setObjectName(QString::fromUtf8("sbMotorEscapeZ"));

        gridLayout_5->addWidget(sbMotorEscapeZ, 2, 1, 1, 1);

        label_5 = new QLabel(gbMotorEscapePosition);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_5->addWidget(label_5, 2, 2, 1, 1);


        gridLayout_8->addWidget(gbMotorEscapePosition, 3, 1, 1, 1);

        gbMotorOffset = new QGroupBox(gbMotorState);
        gbMotorOffset->setObjectName(QString::fromUtf8("gbMotorOffset"));
        gridLayout_7 = new QGridLayout(gbMotorOffset);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        sbMotorOffsetX = new QSpinBox(gbMotorOffset);
        sbMotorOffsetX->setObjectName(QString::fromUtf8("sbMotorOffsetX"));
        sbMotorOffsetX->setMinimum(-99999999);
        sbMotorOffsetX->setMaximum(99999999);

        gridLayout_7->addWidget(sbMotorOffsetX, 0, 1, 1, 1);

        label_20 = new QLabel(gbMotorOffset);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy1);
        label_20->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_20, 0, 0, 1, 1);

        label_21 = new QLabel(gbMotorOffset);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy1.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy1);
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_21, 1, 0, 1, 1);

        sbMotorOffsetY = new QSpinBox(gbMotorOffset);
        sbMotorOffsetY->setObjectName(QString::fromUtf8("sbMotorOffsetY"));
        sbMotorOffsetY->setMinimum(-99999999);
        sbMotorOffsetY->setMaximum(99999999);

        gridLayout_7->addWidget(sbMotorOffsetY, 1, 1, 1, 1);

        label_28 = new QLabel(gbMotorOffset);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        sizePolicy2.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(label_28, 0, 2, 1, 1);

        label_29 = new QLabel(gbMotorOffset);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        sizePolicy2.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(label_29, 1, 2, 1, 1);


        gridLayout_8->addWidget(gbMotorOffset, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_3, 0, 2, 5, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_4, 0, 0, 5, 1);


        gridLayout_9->addWidget(gbMotorState, 2, 1, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_9->addItem(verticalSpacer_2, 3, 0, 1, 4);

        gridLayout_9->setColumnStretch(0, 1);

        gridLayout_11->addWidget(gbVRSSide, 1, 3, 1, 1);

        gbInspectionSide = new QGroupBox(VRSSettingClass);
        gbInspectionSide->setObjectName(QString::fromUtf8("gbInspectionSide"));
        gridLayout_2 = new QGridLayout(gbInspectionSide);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gbInspectOffset = new QGroupBox(gbInspectionSide);
        gbInspectOffset->setObjectName(QString::fromUtf8("gbInspectOffset"));
        gridLayout = new QGridLayout(gbInspectOffset);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(gbInspectOffset);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        sbInspectOffsetX = new QSpinBox(gbInspectOffset);
        sbInspectOffsetX->setObjectName(QString::fromUtf8("sbInspectOffsetX"));
        sbInspectOffsetX->setMaximum(99999999);

        gridLayout->addWidget(sbInspectOffsetX, 0, 1, 1, 1);

        label_4 = new QLabel(gbInspectOffset);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        sbInspectOffsetY = new QSpinBox(gbInspectOffset);
        sbInspectOffsetY->setObjectName(QString::fromUtf8("sbInspectOffsetY"));
        sbInspectOffsetY->setMaximum(99999999);

        gridLayout->addWidget(sbInspectOffsetY, 1, 1, 1, 1);


        gridLayout_2->addWidget(gbInspectOffset, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lbInsResolution = new QLabel(gbInspectionSide);
        lbInsResolution->setObjectName(QString::fromUtf8("lbInsResolution"));

        horizontalLayout->addWidget(lbInsResolution);

        sbInspectResolution = new QSpinBox(gbInspectionSide);
        sbInspectResolution->setObjectName(QString::fromUtf8("sbInspectResolution"));
        sbInspectResolution->setValue(20);

        horizontalLayout->addWidget(sbInspectResolution);

        label_2 = new QLabel(gbInspectionSide);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);


        gridLayout_11->addWidget(gbInspectionSide, 1, 0, 1, 3);

        QWidget::setTabOrder(sbInspectResolution, sbInspectOffsetX);
        QWidget::setTabOrder(sbInspectOffsetX, sbInspectOffsetY);
        QWidget::setTabOrder(sbInspectOffsetY, cbRotation);
        QWidget::setTabOrder(cbRotation, sbVRSResolution);
        QWidget::setTabOrder(sbVRSResolution, sbCameraWidth);
        QWidget::setTabOrder(sbCameraWidth, sbCameraHeight);
        QWidget::setTabOrder(sbCameraHeight, sbMotorOriginX);
        QWidget::setTabOrder(sbMotorOriginX, sbMotorOriginY);
        QWidget::setTabOrder(sbMotorOriginY, sbMotorOffsetX);
        QWidget::setTabOrder(sbMotorOffsetX, sbMotorOffsetY);
        QWidget::setTabOrder(sbMotorOffsetY, sbMotorMovableAreaSizeW);
        QWidget::setTabOrder(sbMotorMovableAreaSizeW, sbMotorMovableAreaSizeH);
        QWidget::setTabOrder(sbMotorMovableAreaSizeH, sbMotorEscapeX);
        QWidget::setTabOrder(sbMotorEscapeX, sbMotorEscapeY);
        QWidget::setTabOrder(sbMotorEscapeY, sbMotorZInitDistance);
        QWidget::setTabOrder(sbMotorZInitDistance, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(VRSSettingClass);
        QObject::connect(okButton, SIGNAL(clicked()), VRSSettingClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), VRSSettingClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(VRSSettingClass);
    } // setupUi

    void retranslateUi(QDialog *VRSSettingClass)
    {
        VRSSettingClass->setWindowTitle(QCoreApplication::translate("VRSSettingClass", "VRSSettingForm", nullptr));
        okButton->setText(QCoreApplication::translate("VRSSettingClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("VRSSettingClass", "Cancel", nullptr));
        gbVRSSide->setTitle(QCoreApplication::translate("VRSSettingClass", "VRS Side", nullptr));
        label_7->setText(QCoreApplication::translate("VRSSettingClass", "Board Rotation", nullptr));
        cbRotation->setItemText(0, QCoreApplication::translate("VRSSettingClass", "0", nullptr));
        cbRotation->setItemText(1, QCoreApplication::translate("VRSSettingClass", "90", nullptr));
        cbRotation->setItemText(2, QCoreApplication::translate("VRSSettingClass", "180", nullptr));
        cbRotation->setItemText(3, QCoreApplication::translate("VRSSettingClass", "270", nullptr));

        label_8->setText(QCoreApplication::translate("VRSSettingClass", "deg", nullptr));
        gbCameraState->setTitle(QCoreApplication::translate("VRSSettingClass", "Camera State", nullptr));
        lbVRSResolution->setText(QCoreApplication::translate("VRSSettingClass", "Resolution", nullptr));
        label_6->setText(QCoreApplication::translate("VRSSettingClass", "um", nullptr));
        lbVRSViewSise->setText(QCoreApplication::translate("VRSSettingClass", "View Size", nullptr));
        lbVRSViewSizeW->setText(QCoreApplication::translate("VRSSettingClass", "Width(um)", nullptr));
        label_12->setText(QCoreApplication::translate("VRSSettingClass", "x", nullptr));
        lbVRSViewSizeH->setText(QCoreApplication::translate("VRSSettingClass", "Height(um)", nullptr));
        gbMotorState->setTitle(QCoreApplication::translate("VRSSettingClass", "Motor State", nullptr));
        gbMotorMovableAreaSize->setTitle(QCoreApplication::translate("VRSSettingClass", "Movable Area Size", nullptr));
        lbMotorMovableAreaSizeW->setText(QCoreApplication::translate("VRSSettingClass", "Width", nullptr));
        lbMotorMovableAreaSizeH->setText(QCoreApplication::translate("VRSSettingClass", "Height", nullptr));
        label_22->setText(QCoreApplication::translate("VRSSettingClass", "Pls", nullptr));
        label_23->setText(QCoreApplication::translate("VRSSettingClass", "Pls", nullptr));
        gbZMotor->setTitle(QCoreApplication::translate("VRSSettingClass", "Z Motor", nullptr));
        label_19->setText(QCoreApplication::translate("VRSSettingClass", "Initial distance", nullptr));
        label_30->setText(QCoreApplication::translate("VRSSettingClass", "mm", nullptr));
        gbMotorOriginPosition->setTitle(QCoreApplication::translate("VRSSettingClass", "Origin Position", nullptr));
        label_13->setText(QCoreApplication::translate("VRSSettingClass", "Y", nullptr));
        label_14->setText(QCoreApplication::translate("VRSSettingClass", "X", nullptr));
        label_26->setText(QCoreApplication::translate("VRSSettingClass", "mm", nullptr));
        label_27->setText(QCoreApplication::translate("VRSSettingClass", "mm", nullptr));
        gbMotorEscapePosition->setTitle(QCoreApplication::translate("VRSSettingClass", "Escape Position", nullptr));
        label_17->setText(QCoreApplication::translate("VRSSettingClass", "X", nullptr));
        label_18->setText(QCoreApplication::translate("VRSSettingClass", "Y", nullptr));
        label_24->setText(QCoreApplication::translate("VRSSettingClass", "mm", nullptr));
        label_25->setText(QCoreApplication::translate("VRSSettingClass", "mm", nullptr));
        label->setText(QCoreApplication::translate("VRSSettingClass", "Z", nullptr));
        label_5->setText(QCoreApplication::translate("VRSSettingClass", "mm", nullptr));
        gbMotorOffset->setTitle(QCoreApplication::translate("VRSSettingClass", "Offset", nullptr));
        label_20->setText(QCoreApplication::translate("VRSSettingClass", "X", nullptr));
        label_21->setText(QCoreApplication::translate("VRSSettingClass", "Y", nullptr));
        label_28->setText(QCoreApplication::translate("VRSSettingClass", "um", nullptr));
        label_29->setText(QCoreApplication::translate("VRSSettingClass", "um", nullptr));
        gbInspectionSide->setTitle(QCoreApplication::translate("VRSSettingClass", "Inspection Side", nullptr));
        gbInspectOffset->setTitle(QCoreApplication::translate("VRSSettingClass", "Offset", nullptr));
        label_3->setText(QCoreApplication::translate("VRSSettingClass", "X", nullptr));
        label_4->setText(QCoreApplication::translate("VRSSettingClass", "Y", nullptr));
        lbInsResolution->setText(QCoreApplication::translate("VRSSettingClass", "Resolution", nullptr));
        label_2->setText(QCoreApplication::translate("VRSSettingClass", "um", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VRSSettingClass: public Ui_VRSSettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VRSSETTINGFORM_H
