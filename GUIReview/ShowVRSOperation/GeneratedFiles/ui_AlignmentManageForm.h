/********************************************************************************
** Form generated from reading UI file 'AlignmentManageForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALIGNMENTMANAGEFORM_H
#define UI_ALIGNMENTMANAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ImageWidget.h"

QT_BEGIN_NAMESPACE

class Ui_AlignmentManageClass
{
public:
    QGridLayout *gridLayout_14;
    QGridLayout *gridLayout_12;
    QLabel *lbSideType;
    QComboBox *cbSideType;
    QLabel *lbPhase;
    QComboBox *cbPhase;
    QGroupBox *gbAlignmentType;
    QGridLayout *gridLayout;
    QRadioButton *rbWholeAlignment;
    QRadioButton *rbEachPageAlignment;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cbImageRotation;
    QGroupBox *gbDebugGo;
    QGridLayout *gridLayout_13;
    QLabel *label_3;
    QLineEdit *leGoX;
    QPushButton *pbDebugGo;
    QLabel *label_4;
    QLineEdit *leGoY;
    ImageWidget *wWholeAlignmentImage;
    QVBoxLayout *verticalLayout;
    QStackedWidget *tabwSetAlignment;
    QWidget *tabwSetAlignmentPage1;
    QGridLayout *gridLayout_5;
    QGroupBox *gbWholeAlignment;
    QGridLayout *gridLayout_2;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pbClearWholeAlignment1;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pbClearWholeAlignment2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pbClearWholeAlignment3;
    QGridLayout *gridLayout_4;
    QPushButton *pbSetCameraWholeAlignment1;
    QPushButton *pbSetWholeAlignmentPoint1;
    QPushButton *pbClearWholeAlignmentOfImage1;
    QPushButton *pbClearWholeAlignmentOfCamera1;
    ImageWidget *wWholeAlignmentCameraEnable1;
    ImageWidget *wWholeAlignmentImageEnable1;
    QGridLayout *gridLayout_6;
    QPushButton *pbSetCameraWholeAlignment2;
    QPushButton *pbSetWholeAlignmentPoint2;
    QPushButton *pbClearWholeAlignmentOfImage2;
    QPushButton *pbClearWholeAlignmentOfCamera2;
    ImageWidget *wWholeAlignmentCameraEnable2;
    ImageWidget *wWholeAlignmentImageEnable2;
    QGridLayout *gridLayout_7;
    QPushButton *pbSetCameraWholeAlignment3;
    QPushButton *pbSetWholeAlignmentPoint3;
    QPushButton *pbClearWholeAlignmentOfImage3;
    QPushButton *pbClearWholeAlignmentOfCamera3;
    ImageWidget *wWholeAlignmentImageEnable3;
    ImageWidget *wWholeAlignmentCameraEnable3;
    QFrame *line_5;
    QPushButton *pbClearWholeAlignmentAll;
    QWidget *tabwSetAlignmentPage2;
    QGridLayout *gridLayout_3;
    QGroupBox *gbEachPageAlignment;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *pbClearEachPageAlignment1;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *pbClearEachPageAlignment2;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *pbClearEachPageAlignment3;
    QGridLayout *gridLayout_9;
    QPushButton *pbSetEachPageAlignmentPoint1;
    QPushButton *pbSetCameraEachPageAlignment1;
    QPushButton *pbClearEachPageAlignmentOfImage1;
    QPushButton *pbClearEachPageAlignmentOfCamera1;
    ImageWidget *wEachPageAlignmentCameraEnable1;
    ImageWidget *wEachPageAlignmentImageEnable1;
    QGridLayout *gridLayout_10;
    QPushButton *pbSetEachPageAlignmentPoint2;
    QPushButton *pbSetCameraEachPageAlignment2;
    QPushButton *pbClearEachPageAlignmentOfImage2;
    QPushButton *pbClearEachPageAlignmentOfCamera2;
    ImageWidget *wEachPageAlignmentImageEnable2;
    ImageWidget *wEachPageAlignmentCameraEnable2;
    QGridLayout *gridLayout_11;
    QPushButton *pbSetEachPageAlignmentPoint3;
    QPushButton *pbSetCameraEachPageAlignment3;
    QPushButton *pbClearEachPageAlignmentOfImage3;
    QPushButton *pbClearEachPageAlignmentOfCamera3;
    ImageWidget *wEachPageAlignmentImageEnable3;
    ImageWidget *wEachPageAlignmentCameraEnable3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *cbEachAlignmentSettingPage;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line;
    QPushButton *pbClearEachPageAlignmentAll;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLabel *laWholeAlignmentEnable;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *pbClose;

    void setupUi(QDialog *AlignmentManageClass)
    {
        if (AlignmentManageClass->objectName().isEmpty())
            AlignmentManageClass->setObjectName(QString::fromUtf8("AlignmentManageClass"));
        AlignmentManageClass->resize(1119, 846);
        gridLayout_14 = new QGridLayout(AlignmentManageClass);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        lbSideType = new QLabel(AlignmentManageClass);
        lbSideType->setObjectName(QString::fromUtf8("lbSideType"));

        gridLayout_12->addWidget(lbSideType, 0, 0, 1, 1);

        cbSideType = new QComboBox(AlignmentManageClass);
        cbSideType->addItem(QString());
        cbSideType->addItem(QString());
        cbSideType->setObjectName(QString::fromUtf8("cbSideType"));

        gridLayout_12->addWidget(cbSideType, 0, 1, 1, 1);

        lbPhase = new QLabel(AlignmentManageClass);
        lbPhase->setObjectName(QString::fromUtf8("lbPhase"));

        gridLayout_12->addWidget(lbPhase, 1, 0, 1, 1);

        cbPhase = new QComboBox(AlignmentManageClass);
        cbPhase->setObjectName(QString::fromUtf8("cbPhase"));

        gridLayout_12->addWidget(cbPhase, 1, 1, 1, 1);


        gridLayout_14->addLayout(gridLayout_12, 0, 0, 1, 1);

        gbAlignmentType = new QGroupBox(AlignmentManageClass);
        gbAlignmentType->setObjectName(QString::fromUtf8("gbAlignmentType"));
        gridLayout = new QGridLayout(gbAlignmentType);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        rbWholeAlignment = new QRadioButton(gbAlignmentType);
        rbWholeAlignment->setObjectName(QString::fromUtf8("rbWholeAlignment"));
        rbWholeAlignment->setChecked(true);

        gridLayout->addWidget(rbWholeAlignment, 0, 1, 1, 1);

        rbEachPageAlignment = new QRadioButton(gbAlignmentType);
        rbEachPageAlignment->setObjectName(QString::fromUtf8("rbEachPageAlignment"));
        rbEachPageAlignment->setEnabled(true);

        gridLayout->addWidget(rbEachPageAlignment, 1, 1, 1, 1);


        gridLayout_14->addWidget(gbAlignmentType, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(AlignmentManageClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        cbImageRotation = new QComboBox(AlignmentManageClass);
        cbImageRotation->addItem(QString());
        cbImageRotation->addItem(QString());
        cbImageRotation->addItem(QString());
        cbImageRotation->addItem(QString());
        cbImageRotation->setObjectName(QString::fromUtf8("cbImageRotation"));

        horizontalLayout_2->addWidget(cbImageRotation);


        gridLayout_14->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        gbDebugGo = new QGroupBox(AlignmentManageClass);
        gbDebugGo->setObjectName(QString::fromUtf8("gbDebugGo"));
        gridLayout_13 = new QGridLayout(gbDebugGo);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_3 = new QLabel(gbDebugGo);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_13->addWidget(label_3, 0, 0, 1, 1);

        leGoX = new QLineEdit(gbDebugGo);
        leGoX->setObjectName(QString::fromUtf8("leGoX"));

        gridLayout_13->addWidget(leGoX, 0, 1, 1, 1);

        pbDebugGo = new QPushButton(gbDebugGo);
        pbDebugGo->setObjectName(QString::fromUtf8("pbDebugGo"));

        gridLayout_13->addWidget(pbDebugGo, 0, 2, 2, 1);

        label_4 = new QLabel(gbDebugGo);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_13->addWidget(label_4, 1, 0, 1, 1);

        leGoY = new QLineEdit(gbDebugGo);
        leGoY->setObjectName(QString::fromUtf8("leGoY"));

        gridLayout_13->addWidget(leGoY, 1, 1, 1, 1);


        gridLayout_14->addWidget(gbDebugGo, 0, 3, 1, 1);

        wWholeAlignmentImage = new ImageWidget(AlignmentManageClass);
        wWholeAlignmentImage->setObjectName(QString::fromUtf8("wWholeAlignmentImage"));

        gridLayout_14->addWidget(wWholeAlignmentImage, 1, 0, 1, 3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabwSetAlignment = new QStackedWidget(AlignmentManageClass);
        tabwSetAlignment->setObjectName(QString::fromUtf8("tabwSetAlignment"));
        tabwSetAlignment->setEnabled(true);
        tabwSetAlignmentPage1 = new QWidget();
        tabwSetAlignmentPage1->setObjectName(QString::fromUtf8("tabwSetAlignmentPage1"));
        gridLayout_5 = new QGridLayout(tabwSetAlignmentPage1);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gbWholeAlignment = new QGroupBox(tabwSetAlignmentPage1);
        gbWholeAlignment->setObjectName(QString::fromUtf8("gbWholeAlignment"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gbWholeAlignment->sizePolicy().hasHeightForWidth());
        gbWholeAlignment->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(gbWholeAlignment);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(11, -1, -1, -1);
        line_4 = new QFrame(gbWholeAlignment);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_4, 2, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_7 = new QLabel(gbWholeAlignment);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_9->addWidget(label_7);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        pbClearWholeAlignment1 = new QPushButton(gbWholeAlignment);
        pbClearWholeAlignment1->setObjectName(QString::fromUtf8("pbClearWholeAlignment1"));

        horizontalLayout_9->addWidget(pbClearWholeAlignment1);


        gridLayout_2->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_8 = new QLabel(gbWholeAlignment);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_10->addWidget(label_8);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);

        pbClearWholeAlignment2 = new QPushButton(gbWholeAlignment);
        pbClearWholeAlignment2->setObjectName(QString::fromUtf8("pbClearWholeAlignment2"));

        horizontalLayout_10->addWidget(pbClearWholeAlignment2);


        gridLayout_2->addLayout(horizontalLayout_10, 3, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_9 = new QLabel(gbWholeAlignment);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_11->addWidget(label_9);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);

        pbClearWholeAlignment3 = new QPushButton(gbWholeAlignment);
        pbClearWholeAlignment3->setObjectName(QString::fromUtf8("pbClearWholeAlignment3"));

        horizontalLayout_11->addWidget(pbClearWholeAlignment3);


        gridLayout_2->addLayout(horizontalLayout_11, 6, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pbSetCameraWholeAlignment1 = new QPushButton(gbWholeAlignment);
        pbSetCameraWholeAlignment1->setObjectName(QString::fromUtf8("pbSetCameraWholeAlignment1"));

        gridLayout_4->addWidget(pbSetCameraWholeAlignment1, 1, 1, 1, 2);

        pbSetWholeAlignmentPoint1 = new QPushButton(gbWholeAlignment);
        pbSetWholeAlignmentPoint1->setObjectName(QString::fromUtf8("pbSetWholeAlignmentPoint1"));

        gridLayout_4->addWidget(pbSetWholeAlignmentPoint1, 0, 1, 1, 2);

        pbClearWholeAlignmentOfImage1 = new QPushButton(gbWholeAlignment);
        pbClearWholeAlignmentOfImage1->setObjectName(QString::fromUtf8("pbClearWholeAlignmentOfImage1"));

        gridLayout_4->addWidget(pbClearWholeAlignmentOfImage1, 0, 3, 1, 1);

        pbClearWholeAlignmentOfCamera1 = new QPushButton(gbWholeAlignment);
        pbClearWholeAlignmentOfCamera1->setObjectName(QString::fromUtf8("pbClearWholeAlignmentOfCamera1"));

        gridLayout_4->addWidget(pbClearWholeAlignmentOfCamera1, 1, 3, 1, 1);

        wWholeAlignmentCameraEnable1 = new ImageWidget(gbWholeAlignment);
        wWholeAlignmentCameraEnable1->setObjectName(QString::fromUtf8("wWholeAlignmentCameraEnable1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(wWholeAlignmentCameraEnable1->sizePolicy().hasHeightForWidth());
        wWholeAlignmentCameraEnable1->setSizePolicy(sizePolicy1);
        wWholeAlignmentCameraEnable1->setMinimumSize(QSize(30, 0));

        gridLayout_4->addWidget(wWholeAlignmentCameraEnable1, 1, 0, 1, 1);

        wWholeAlignmentImageEnable1 = new ImageWidget(gbWholeAlignment);
        wWholeAlignmentImageEnable1->setObjectName(QString::fromUtf8("wWholeAlignmentImageEnable1"));
        sizePolicy1.setHeightForWidth(wWholeAlignmentImageEnable1->sizePolicy().hasHeightForWidth());
        wWholeAlignmentImageEnable1->setSizePolicy(sizePolicy1);
        wWholeAlignmentImageEnable1->setMinimumSize(QSize(30, 0));

        gridLayout_4->addWidget(wWholeAlignmentImageEnable1, 0, 0, 1, 1);

        gridLayout_4->setColumnStretch(0, 1);

        gridLayout_2->addLayout(gridLayout_4, 1, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pbSetCameraWholeAlignment2 = new QPushButton(gbWholeAlignment);
        pbSetCameraWholeAlignment2->setObjectName(QString::fromUtf8("pbSetCameraWholeAlignment2"));

        gridLayout_6->addWidget(pbSetCameraWholeAlignment2, 1, 1, 1, 2);

        pbSetWholeAlignmentPoint2 = new QPushButton(gbWholeAlignment);
        pbSetWholeAlignmentPoint2->setObjectName(QString::fromUtf8("pbSetWholeAlignmentPoint2"));

        gridLayout_6->addWidget(pbSetWholeAlignmentPoint2, 0, 1, 1, 2);

        pbClearWholeAlignmentOfImage2 = new QPushButton(gbWholeAlignment);
        pbClearWholeAlignmentOfImage2->setObjectName(QString::fromUtf8("pbClearWholeAlignmentOfImage2"));

        gridLayout_6->addWidget(pbClearWholeAlignmentOfImage2, 0, 3, 1, 1);

        pbClearWholeAlignmentOfCamera2 = new QPushButton(gbWholeAlignment);
        pbClearWholeAlignmentOfCamera2->setObjectName(QString::fromUtf8("pbClearWholeAlignmentOfCamera2"));

        gridLayout_6->addWidget(pbClearWholeAlignmentOfCamera2, 1, 3, 1, 1);

        wWholeAlignmentCameraEnable2 = new ImageWidget(gbWholeAlignment);
        wWholeAlignmentCameraEnable2->setObjectName(QString::fromUtf8("wWholeAlignmentCameraEnable2"));
        sizePolicy1.setHeightForWidth(wWholeAlignmentCameraEnable2->sizePolicy().hasHeightForWidth());
        wWholeAlignmentCameraEnable2->setSizePolicy(sizePolicy1);
        wWholeAlignmentCameraEnable2->setMinimumSize(QSize(30, 0));

        gridLayout_6->addWidget(wWholeAlignmentCameraEnable2, 1, 0, 1, 1);

        wWholeAlignmentImageEnable2 = new ImageWidget(gbWholeAlignment);
        wWholeAlignmentImageEnable2->setObjectName(QString::fromUtf8("wWholeAlignmentImageEnable2"));
        sizePolicy1.setHeightForWidth(wWholeAlignmentImageEnable2->sizePolicy().hasHeightForWidth());
        wWholeAlignmentImageEnable2->setSizePolicy(sizePolicy1);
        wWholeAlignmentImageEnable2->setMinimumSize(QSize(30, 0));

        gridLayout_6->addWidget(wWholeAlignmentImageEnable2, 0, 0, 1, 1);

        gridLayout_6->setColumnStretch(0, 1);

        gridLayout_2->addLayout(gridLayout_6, 4, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        pbSetCameraWholeAlignment3 = new QPushButton(gbWholeAlignment);
        pbSetCameraWholeAlignment3->setObjectName(QString::fromUtf8("pbSetCameraWholeAlignment3"));

        gridLayout_7->addWidget(pbSetCameraWholeAlignment3, 1, 1, 1, 2);

        pbSetWholeAlignmentPoint3 = new QPushButton(gbWholeAlignment);
        pbSetWholeAlignmentPoint3->setObjectName(QString::fromUtf8("pbSetWholeAlignmentPoint3"));

        gridLayout_7->addWidget(pbSetWholeAlignmentPoint3, 0, 1, 1, 2);

        pbClearWholeAlignmentOfImage3 = new QPushButton(gbWholeAlignment);
        pbClearWholeAlignmentOfImage3->setObjectName(QString::fromUtf8("pbClearWholeAlignmentOfImage3"));

        gridLayout_7->addWidget(pbClearWholeAlignmentOfImage3, 0, 3, 1, 1);

        pbClearWholeAlignmentOfCamera3 = new QPushButton(gbWholeAlignment);
        pbClearWholeAlignmentOfCamera3->setObjectName(QString::fromUtf8("pbClearWholeAlignmentOfCamera3"));

        gridLayout_7->addWidget(pbClearWholeAlignmentOfCamera3, 1, 3, 1, 1);

        wWholeAlignmentImageEnable3 = new ImageWidget(gbWholeAlignment);
        wWholeAlignmentImageEnable3->setObjectName(QString::fromUtf8("wWholeAlignmentImageEnable3"));
        sizePolicy1.setHeightForWidth(wWholeAlignmentImageEnable3->sizePolicy().hasHeightForWidth());
        wWholeAlignmentImageEnable3->setSizePolicy(sizePolicy1);
        wWholeAlignmentImageEnable3->setMinimumSize(QSize(30, 0));

        gridLayout_7->addWidget(wWholeAlignmentImageEnable3, 0, 0, 1, 1);

        wWholeAlignmentCameraEnable3 = new ImageWidget(gbWholeAlignment);
        wWholeAlignmentCameraEnable3->setObjectName(QString::fromUtf8("wWholeAlignmentCameraEnable3"));
        sizePolicy1.setHeightForWidth(wWholeAlignmentCameraEnable3->sizePolicy().hasHeightForWidth());
        wWholeAlignmentCameraEnable3->setSizePolicy(sizePolicy1);
        wWholeAlignmentCameraEnable3->setMinimumSize(QSize(30, 0));

        gridLayout_7->addWidget(wWholeAlignmentCameraEnable3, 1, 0, 1, 1);

        gridLayout_7->setColumnStretch(0, 1);

        gridLayout_2->addLayout(gridLayout_7, 7, 0, 1, 1);

        line_5 = new QFrame(gbWholeAlignment);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_5, 5, 0, 1, 1);


        gridLayout_5->addWidget(gbWholeAlignment, 0, 0, 1, 2);

        pbClearWholeAlignmentAll = new QPushButton(tabwSetAlignmentPage1);
        pbClearWholeAlignmentAll->setObjectName(QString::fromUtf8("pbClearWholeAlignmentAll"));

        gridLayout_5->addWidget(pbClearWholeAlignmentAll, 1, 0, 1, 2);

        gridLayout_5->setColumnStretch(0, 1);
        tabwSetAlignment->addWidget(tabwSetAlignmentPage1);
        tabwSetAlignmentPage2 = new QWidget();
        tabwSetAlignmentPage2->setObjectName(QString::fromUtf8("tabwSetAlignmentPage2"));
        gridLayout_3 = new QGridLayout(tabwSetAlignmentPage2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gbEachPageAlignment = new QGroupBox(tabwSetAlignmentPage2);
        gbEachPageAlignment->setObjectName(QString::fromUtf8("gbEachPageAlignment"));
        gridLayout_8 = new QGridLayout(gbEachPageAlignment);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_11 = new QLabel(gbEachPageAlignment);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_12->addWidget(label_11);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_13);

        pbClearEachPageAlignment1 = new QPushButton(gbEachPageAlignment);
        pbClearEachPageAlignment1->setObjectName(QString::fromUtf8("pbClearEachPageAlignment1"));

        horizontalLayout_12->addWidget(pbClearEachPageAlignment1);


        gridLayout_8->addLayout(horizontalLayout_12, 2, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_12 = new QLabel(gbEachPageAlignment);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_13->addWidget(label_12);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_14);

        pbClearEachPageAlignment2 = new QPushButton(gbEachPageAlignment);
        pbClearEachPageAlignment2->setObjectName(QString::fromUtf8("pbClearEachPageAlignment2"));

        horizontalLayout_13->addWidget(pbClearEachPageAlignment2);


        gridLayout_8->addLayout(horizontalLayout_13, 6, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_13 = new QLabel(gbEachPageAlignment);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_14->addWidget(label_13);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_15);

        pbClearEachPageAlignment3 = new QPushButton(gbEachPageAlignment);
        pbClearEachPageAlignment3->setObjectName(QString::fromUtf8("pbClearEachPageAlignment3"));

        horizontalLayout_14->addWidget(pbClearEachPageAlignment3);


        gridLayout_8->addLayout(horizontalLayout_14, 9, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        pbSetEachPageAlignmentPoint1 = new QPushButton(gbEachPageAlignment);
        pbSetEachPageAlignmentPoint1->setObjectName(QString::fromUtf8("pbSetEachPageAlignmentPoint1"));

        gridLayout_9->addWidget(pbSetEachPageAlignmentPoint1, 0, 1, 1, 2);

        pbSetCameraEachPageAlignment1 = new QPushButton(gbEachPageAlignment);
        pbSetCameraEachPageAlignment1->setObjectName(QString::fromUtf8("pbSetCameraEachPageAlignment1"));

        gridLayout_9->addWidget(pbSetCameraEachPageAlignment1, 1, 1, 1, 2);

        pbClearEachPageAlignmentOfImage1 = new QPushButton(gbEachPageAlignment);
        pbClearEachPageAlignmentOfImage1->setObjectName(QString::fromUtf8("pbClearEachPageAlignmentOfImage1"));

        gridLayout_9->addWidget(pbClearEachPageAlignmentOfImage1, 0, 3, 1, 1);

        pbClearEachPageAlignmentOfCamera1 = new QPushButton(gbEachPageAlignment);
        pbClearEachPageAlignmentOfCamera1->setObjectName(QString::fromUtf8("pbClearEachPageAlignmentOfCamera1"));

        gridLayout_9->addWidget(pbClearEachPageAlignmentOfCamera1, 1, 3, 1, 1);

        wEachPageAlignmentCameraEnable1 = new ImageWidget(gbEachPageAlignment);
        wEachPageAlignmentCameraEnable1->setObjectName(QString::fromUtf8("wEachPageAlignmentCameraEnable1"));
        sizePolicy1.setHeightForWidth(wEachPageAlignmentCameraEnable1->sizePolicy().hasHeightForWidth());
        wEachPageAlignmentCameraEnable1->setSizePolicy(sizePolicy1);
        wEachPageAlignmentCameraEnable1->setMinimumSize(QSize(30, 0));

        gridLayout_9->addWidget(wEachPageAlignmentCameraEnable1, 1, 0, 1, 1);

        wEachPageAlignmentImageEnable1 = new ImageWidget(gbEachPageAlignment);
        wEachPageAlignmentImageEnable1->setObjectName(QString::fromUtf8("wEachPageAlignmentImageEnable1"));
        sizePolicy1.setHeightForWidth(wEachPageAlignmentImageEnable1->sizePolicy().hasHeightForWidth());
        wEachPageAlignmentImageEnable1->setSizePolicy(sizePolicy1);
        wEachPageAlignmentImageEnable1->setMinimumSize(QSize(30, 0));

        gridLayout_9->addWidget(wEachPageAlignmentImageEnable1, 0, 0, 1, 1);

        gridLayout_9->setColumnStretch(0, 1);

        gridLayout_8->addLayout(gridLayout_9, 4, 0, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        pbSetEachPageAlignmentPoint2 = new QPushButton(gbEachPageAlignment);
        pbSetEachPageAlignmentPoint2->setObjectName(QString::fromUtf8("pbSetEachPageAlignmentPoint2"));

        gridLayout_10->addWidget(pbSetEachPageAlignmentPoint2, 0, 1, 1, 2);

        pbSetCameraEachPageAlignment2 = new QPushButton(gbEachPageAlignment);
        pbSetCameraEachPageAlignment2->setObjectName(QString::fromUtf8("pbSetCameraEachPageAlignment2"));

        gridLayout_10->addWidget(pbSetCameraEachPageAlignment2, 1, 1, 1, 2);

        pbClearEachPageAlignmentOfImage2 = new QPushButton(gbEachPageAlignment);
        pbClearEachPageAlignmentOfImage2->setObjectName(QString::fromUtf8("pbClearEachPageAlignmentOfImage2"));

        gridLayout_10->addWidget(pbClearEachPageAlignmentOfImage2, 0, 3, 1, 1);

        pbClearEachPageAlignmentOfCamera2 = new QPushButton(gbEachPageAlignment);
        pbClearEachPageAlignmentOfCamera2->setObjectName(QString::fromUtf8("pbClearEachPageAlignmentOfCamera2"));

        gridLayout_10->addWidget(pbClearEachPageAlignmentOfCamera2, 1, 3, 1, 1);

        wEachPageAlignmentImageEnable2 = new ImageWidget(gbEachPageAlignment);
        wEachPageAlignmentImageEnable2->setObjectName(QString::fromUtf8("wEachPageAlignmentImageEnable2"));
        sizePolicy1.setHeightForWidth(wEachPageAlignmentImageEnable2->sizePolicy().hasHeightForWidth());
        wEachPageAlignmentImageEnable2->setSizePolicy(sizePolicy1);
        wEachPageAlignmentImageEnable2->setMinimumSize(QSize(30, 0));

        gridLayout_10->addWidget(wEachPageAlignmentImageEnable2, 0, 0, 1, 1);

        wEachPageAlignmentCameraEnable2 = new ImageWidget(gbEachPageAlignment);
        wEachPageAlignmentCameraEnable2->setObjectName(QString::fromUtf8("wEachPageAlignmentCameraEnable2"));
        sizePolicy1.setHeightForWidth(wEachPageAlignmentCameraEnable2->sizePolicy().hasHeightForWidth());
        wEachPageAlignmentCameraEnable2->setSizePolicy(sizePolicy1);
        wEachPageAlignmentCameraEnable2->setMinimumSize(QSize(30, 0));

        gridLayout_10->addWidget(wEachPageAlignmentCameraEnable2, 1, 0, 1, 1);

        gridLayout_10->setColumnStretch(0, 1);

        gridLayout_8->addLayout(gridLayout_10, 7, 0, 1, 1);

        gridLayout_11 = new QGridLayout();
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        pbSetEachPageAlignmentPoint3 = new QPushButton(gbEachPageAlignment);
        pbSetEachPageAlignmentPoint3->setObjectName(QString::fromUtf8("pbSetEachPageAlignmentPoint3"));

        gridLayout_11->addWidget(pbSetEachPageAlignmentPoint3, 0, 1, 1, 2);

        pbSetCameraEachPageAlignment3 = new QPushButton(gbEachPageAlignment);
        pbSetCameraEachPageAlignment3->setObjectName(QString::fromUtf8("pbSetCameraEachPageAlignment3"));

        gridLayout_11->addWidget(pbSetCameraEachPageAlignment3, 1, 1, 1, 2);

        pbClearEachPageAlignmentOfImage3 = new QPushButton(gbEachPageAlignment);
        pbClearEachPageAlignmentOfImage3->setObjectName(QString::fromUtf8("pbClearEachPageAlignmentOfImage3"));

        gridLayout_11->addWidget(pbClearEachPageAlignmentOfImage3, 0, 3, 1, 1);

        pbClearEachPageAlignmentOfCamera3 = new QPushButton(gbEachPageAlignment);
        pbClearEachPageAlignmentOfCamera3->setObjectName(QString::fromUtf8("pbClearEachPageAlignmentOfCamera3"));

        gridLayout_11->addWidget(pbClearEachPageAlignmentOfCamera3, 1, 3, 1, 1);

        wEachPageAlignmentImageEnable3 = new ImageWidget(gbEachPageAlignment);
        wEachPageAlignmentImageEnable3->setObjectName(QString::fromUtf8("wEachPageAlignmentImageEnable3"));
        sizePolicy1.setHeightForWidth(wEachPageAlignmentImageEnable3->sizePolicy().hasHeightForWidth());
        wEachPageAlignmentImageEnable3->setSizePolicy(sizePolicy1);
        wEachPageAlignmentImageEnable3->setMinimumSize(QSize(30, 0));

        gridLayout_11->addWidget(wEachPageAlignmentImageEnable3, 0, 0, 1, 1);

        wEachPageAlignmentCameraEnable3 = new ImageWidget(gbEachPageAlignment);
        wEachPageAlignmentCameraEnable3->setObjectName(QString::fromUtf8("wEachPageAlignmentCameraEnable3"));
        sizePolicy1.setHeightForWidth(wEachPageAlignmentCameraEnable3->sizePolicy().hasHeightForWidth());
        wEachPageAlignmentCameraEnable3->setSizePolicy(sizePolicy1);
        wEachPageAlignmentCameraEnable3->setMinimumSize(QSize(30, 0));

        gridLayout_11->addWidget(wEachPageAlignmentCameraEnable3, 1, 0, 1, 1);

        gridLayout_11->setColumnStretch(0, 1);

        gridLayout_8->addLayout(gridLayout_11, 10, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_10 = new QLabel(gbEachPageAlignment);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_3->addWidget(label_10);

        horizontalSpacer_3 = new QSpacerItem(68, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        cbEachAlignmentSettingPage = new QComboBox(gbEachPageAlignment);
        cbEachAlignmentSettingPage->setObjectName(QString::fromUtf8("cbEachAlignmentSettingPage"));

        horizontalLayout_3->addWidget(cbEachAlignmentSettingPage);


        gridLayout_8->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        line_2 = new QFrame(gbEachPageAlignment);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_2, 5, 0, 1, 1);

        line_3 = new QFrame(gbEachPageAlignment);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_3, 8, 0, 1, 1);

        line = new QFrame(gbEachPageAlignment);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line, 1, 0, 1, 1);


        gridLayout_3->addWidget(gbEachPageAlignment, 0, 0, 1, 1);

        pbClearEachPageAlignmentAll = new QPushButton(tabwSetAlignmentPage2);
        pbClearEachPageAlignmentAll->setObjectName(QString::fromUtf8("pbClearEachPageAlignmentAll"));

        gridLayout_3->addWidget(pbClearEachPageAlignmentAll, 1, 0, 1, 1);

        tabwSetAlignment->addWidget(tabwSetAlignmentPage2);

        verticalLayout->addWidget(tabwSetAlignment);

        verticalSpacer_2 = new QSpacerItem(249, 108, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(AlignmentManageClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        laWholeAlignmentEnable = new QLabel(AlignmentManageClass);
        laWholeAlignmentEnable->setObjectName(QString::fromUtf8("laWholeAlignmentEnable"));

        horizontalLayout->addWidget(laWholeAlignmentEnable);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_14->addLayout(verticalLayout, 1, 3, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        pbClose = new QPushButton(AlignmentManageClass);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));

        hboxLayout->addWidget(pbClose);


        gridLayout_14->addLayout(hboxLayout, 2, 0, 1, 4);

        gridLayout_14->setRowStretch(1, 1);
        gridLayout_14->setColumnStretch(0, 1);
        gridLayout_14->setColumnStretch(1, 1);
        gridLayout_14->setColumnStretch(2, 1);
        QWidget::setTabOrder(cbSideType, cbPhase);
        QWidget::setTabOrder(cbPhase, rbWholeAlignment);
        QWidget::setTabOrder(rbWholeAlignment, rbEachPageAlignment);
        QWidget::setTabOrder(rbEachPageAlignment, cbImageRotation);
        QWidget::setTabOrder(cbImageRotation, pbSetWholeAlignmentPoint1);
        QWidget::setTabOrder(pbSetWholeAlignmentPoint1, pbSetCameraWholeAlignment1);
        QWidget::setTabOrder(pbSetCameraWholeAlignment1, pbClearWholeAlignment1);
        QWidget::setTabOrder(pbClearWholeAlignment1, pbClearWholeAlignmentOfImage1);
        QWidget::setTabOrder(pbClearWholeAlignmentOfImage1, pbClearWholeAlignmentOfCamera1);
        QWidget::setTabOrder(pbClearWholeAlignmentOfCamera1, pbSetWholeAlignmentPoint2);
        QWidget::setTabOrder(pbSetWholeAlignmentPoint2, pbSetCameraWholeAlignment2);
        QWidget::setTabOrder(pbSetCameraWholeAlignment2, pbClearWholeAlignment2);
        QWidget::setTabOrder(pbClearWholeAlignment2, pbClearWholeAlignmentOfImage2);
        QWidget::setTabOrder(pbClearWholeAlignmentOfImage2, pbClearWholeAlignmentOfCamera2);
        QWidget::setTabOrder(pbClearWholeAlignmentOfCamera2, pbSetWholeAlignmentPoint3);
        QWidget::setTabOrder(pbSetWholeAlignmentPoint3, pbSetCameraWholeAlignment3);
        QWidget::setTabOrder(pbSetCameraWholeAlignment3, pbClearWholeAlignment3);
        QWidget::setTabOrder(pbClearWholeAlignment3, pbClearWholeAlignmentOfImage3);
        QWidget::setTabOrder(pbClearWholeAlignmentOfImage3, pbClearWholeAlignmentOfCamera3);
        QWidget::setTabOrder(pbClearWholeAlignmentOfCamera3, pbClearWholeAlignmentAll);
        QWidget::setTabOrder(pbClearWholeAlignmentAll, cbEachAlignmentSettingPage);
        QWidget::setTabOrder(cbEachAlignmentSettingPage, pbSetEachPageAlignmentPoint1);
        QWidget::setTabOrder(pbSetEachPageAlignmentPoint1, pbSetCameraEachPageAlignment1);
        QWidget::setTabOrder(pbSetCameraEachPageAlignment1, pbClearEachPageAlignment1);
        QWidget::setTabOrder(pbClearEachPageAlignment1, pbClearEachPageAlignmentOfImage1);
        QWidget::setTabOrder(pbClearEachPageAlignmentOfImage1, pbClearEachPageAlignmentOfCamera1);
        QWidget::setTabOrder(pbClearEachPageAlignmentOfCamera1, pbSetEachPageAlignmentPoint2);
        QWidget::setTabOrder(pbSetEachPageAlignmentPoint2, pbSetCameraEachPageAlignment2);
        QWidget::setTabOrder(pbSetCameraEachPageAlignment2, pbClearEachPageAlignment2);
        QWidget::setTabOrder(pbClearEachPageAlignment2, pbClearEachPageAlignmentOfImage2);
        QWidget::setTabOrder(pbClearEachPageAlignmentOfImage2, pbClearEachPageAlignmentOfCamera2);
        QWidget::setTabOrder(pbClearEachPageAlignmentOfCamera2, pbSetEachPageAlignmentPoint3);
        QWidget::setTabOrder(pbSetEachPageAlignmentPoint3, pbSetCameraEachPageAlignment3);
        QWidget::setTabOrder(pbSetCameraEachPageAlignment3, pbClearEachPageAlignment3);
        QWidget::setTabOrder(pbClearEachPageAlignment3, pbClearEachPageAlignmentOfImage3);
        QWidget::setTabOrder(pbClearEachPageAlignmentOfImage3, pbClearEachPageAlignmentOfCamera3);
        QWidget::setTabOrder(pbClearEachPageAlignmentOfCamera3, pbClearEachPageAlignmentAll);
        QWidget::setTabOrder(pbClearEachPageAlignmentAll, leGoX);
        QWidget::setTabOrder(leGoX, leGoY);
        QWidget::setTabOrder(leGoY, pbDebugGo);
        QWidget::setTabOrder(pbDebugGo, pbClose);

        retranslateUi(AlignmentManageClass);
        QObject::connect(pbClose, SIGNAL(clicked()), AlignmentManageClass, SLOT(accept()));

        tabwSetAlignment->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AlignmentManageClass);
    } // setupUi

    void retranslateUi(QDialog *AlignmentManageClass)
    {
        AlignmentManageClass->setWindowTitle(QCoreApplication::translate("AlignmentManageClass", "AlignmentManageForm", nullptr));
        lbSideType->setText(QCoreApplication::translate("AlignmentManageClass", "SideType", nullptr));
        cbSideType->setItemText(0, QCoreApplication::translate("AlignmentManageClass", "Front", nullptr));
        cbSideType->setItemText(1, QCoreApplication::translate("AlignmentManageClass", "Back", nullptr));

        lbPhase->setText(QCoreApplication::translate("AlignmentManageClass", "Phase", nullptr));
        gbAlignmentType->setTitle(QCoreApplication::translate("AlignmentManageClass", "Alignment Type", nullptr));
        rbWholeAlignment->setText(QCoreApplication::translate("AlignmentManageClass", "Whole Alignment", nullptr));
        rbEachPageAlignment->setText(QCoreApplication::translate("AlignmentManageClass", "Each Page Alignment", nullptr));
        label_2->setText(QCoreApplication::translate("AlignmentManageClass", "Image Rotation", nullptr));
        cbImageRotation->setItemText(0, QCoreApplication::translate("AlignmentManageClass", "0", nullptr));
        cbImageRotation->setItemText(1, QCoreApplication::translate("AlignmentManageClass", "90", nullptr));
        cbImageRotation->setItemText(2, QCoreApplication::translate("AlignmentManageClass", "180", nullptr));
        cbImageRotation->setItemText(3, QCoreApplication::translate("AlignmentManageClass", "270", nullptr));

        gbDebugGo->setTitle(QCoreApplication::translate("AlignmentManageClass", "DebugGo(WithAlignment)", nullptr));
        label_3->setText(QCoreApplication::translate("AlignmentManageClass", "X", nullptr));
        pbDebugGo->setText(QCoreApplication::translate("AlignmentManageClass", "Go", nullptr));
        label_4->setText(QCoreApplication::translate("AlignmentManageClass", "Y", nullptr));
        gbWholeAlignment->setTitle(QCoreApplication::translate("AlignmentManageClass", "WholeAlignment", nullptr));
        label_7->setText(QCoreApplication::translate("AlignmentManageClass", "Alignment 1", nullptr));
        pbClearWholeAlignment1->setText(QCoreApplication::translate("AlignmentManageClass", "Clear both", nullptr));
        label_8->setText(QCoreApplication::translate("AlignmentManageClass", "Alignment 2", nullptr));
        pbClearWholeAlignment2->setText(QCoreApplication::translate("AlignmentManageClass", "Clear both", nullptr));
        label_9->setText(QCoreApplication::translate("AlignmentManageClass", "Alignment 3", nullptr));
        pbClearWholeAlignment3->setText(QCoreApplication::translate("AlignmentManageClass", "Clear both", nullptr));
        pbSetCameraWholeAlignment1->setText(QCoreApplication::translate("AlignmentManageClass", "Set Camera Alignment", nullptr));
        pbSetWholeAlignmentPoint1->setText(QCoreApplication::translate("AlignmentManageClass", "Set Image Alignment", nullptr));
        pbClearWholeAlignmentOfImage1->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbClearWholeAlignmentOfCamera1->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbSetCameraWholeAlignment2->setText(QCoreApplication::translate("AlignmentManageClass", "Set Camera Alignment", nullptr));
        pbSetWholeAlignmentPoint2->setText(QCoreApplication::translate("AlignmentManageClass", "Set Image Alignment", nullptr));
        pbClearWholeAlignmentOfImage2->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbClearWholeAlignmentOfCamera2->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbSetCameraWholeAlignment3->setText(QCoreApplication::translate("AlignmentManageClass", "Set Camera Alignment", nullptr));
        pbSetWholeAlignmentPoint3->setText(QCoreApplication::translate("AlignmentManageClass", "Set Image Alignment", nullptr));
        pbClearWholeAlignmentOfImage3->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbClearWholeAlignmentOfCamera3->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbClearWholeAlignmentAll->setText(QCoreApplication::translate("AlignmentManageClass", "Clear All Whole Alignment", nullptr));
        gbEachPageAlignment->setTitle(QCoreApplication::translate("AlignmentManageClass", "EachPageAlignment", nullptr));
        label_11->setText(QCoreApplication::translate("AlignmentManageClass", "Alignment 1", nullptr));
        pbClearEachPageAlignment1->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        label_12->setText(QCoreApplication::translate("AlignmentManageClass", "Alignment 2", nullptr));
        pbClearEachPageAlignment2->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        label_13->setText(QCoreApplication::translate("AlignmentManageClass", "Alignment 3", nullptr));
        pbClearEachPageAlignment3->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbSetEachPageAlignmentPoint1->setText(QCoreApplication::translate("AlignmentManageClass", "Set Image Alignment", nullptr));
        pbSetCameraEachPageAlignment1->setText(QCoreApplication::translate("AlignmentManageClass", "Set Camera Alignment", nullptr));
        pbClearEachPageAlignmentOfImage1->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbClearEachPageAlignmentOfCamera1->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbSetEachPageAlignmentPoint2->setText(QCoreApplication::translate("AlignmentManageClass", "Set Image Alignment", nullptr));
        pbSetCameraEachPageAlignment2->setText(QCoreApplication::translate("AlignmentManageClass", "Set Camera Alignment", nullptr));
        pbClearEachPageAlignmentOfImage2->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbClearEachPageAlignmentOfCamera2->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbSetEachPageAlignmentPoint3->setText(QCoreApplication::translate("AlignmentManageClass", "Set Image Alignment", nullptr));
        pbSetCameraEachPageAlignment3->setText(QCoreApplication::translate("AlignmentManageClass", "Set Camera Alignment", nullptr));
        pbClearEachPageAlignmentOfImage3->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        pbClearEachPageAlignmentOfCamera3->setText(QCoreApplication::translate("AlignmentManageClass", "Clear", nullptr));
        label_10->setText(QCoreApplication::translate("AlignmentManageClass", "Setting Page No", nullptr));
        pbClearEachPageAlignmentAll->setText(QCoreApplication::translate("AlignmentManageClass", "Clear All Each Page Alignment", nullptr));
        label->setText(QCoreApplication::translate("AlignmentManageClass", "alignment operation:", nullptr));
        laWholeAlignmentEnable->setText(QCoreApplication::translate("AlignmentManageClass", "Not active", nullptr));
        pbClose->setText(QCoreApplication::translate("AlignmentManageClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlignmentManageClass: public Ui_AlignmentManageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALIGNMENTMANAGEFORM_H
