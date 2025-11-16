/********************************************************************************
** Form generated from reading UI file 'paramset.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMSET_H
#define UI_PARAMSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamSetClass
{
public:
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QLabel *label_13;
    QLineEdit *txtOutDir;
    QPushButton *btnSelect;
    QWidget *layoutWidget1;
    QHBoxLayout *hboxLayout1;
    QLabel *label_8;
    QLineEdit *txtPadValue_1;
    QLabel *label_9;
    QLineEdit *txtPadValue_2;
    QWidget *layoutWidget2;
    QHBoxLayout *hboxLayout2;
    QLabel *label_14;
    QLineEdit *txtThreshVal_1;
    QLabel *label_15;
    QLineEdit *txtThreshVal_2;
    QCheckBox *chkEffect;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget3;
    QHBoxLayout *hboxLayout3;
    QLabel *label_7;
    QLineEdit *txtScaleZ_2;
    QCheckBox *chkBar_2;
    QCheckBox *chkMode;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget4;
    QHBoxLayout *hboxLayout4;
    QLabel *label_4;
    QLineEdit *txtRotation_x;
    QWidget *layoutWidget_2;
    QHBoxLayout *hboxLayout5;
    QLabel *label_5;
    QLineEdit *txtRotation_y;
    QWidget *layoutWidget_3;
    QHBoxLayout *hboxLayout6;
    QLabel *label_6;
    QLineEdit *txtRotation_z;
    QWidget *layoutWidget_8;
    QHBoxLayout *hboxLayout7;
    QLabel *label_16;
    QSpinBox *avgy;
    QWidget *layoutWidget5;
    QHBoxLayout *hboxLayout8;
    QLabel *label;
    QSpinBox *avgx;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget_4;
    QHBoxLayout *hboxLayout9;
    QLabel *label_10;
    QLineEdit *txtScaleZ_3;
    QRadioButton *rbAxis_1;
    QLabel *label_3;
    QRadioButton *rbAxis_2;
    QLineEdit *txtPadVal_2;
    QLineEdit *txtPadVal_1;
    QLabel *label_2;
    QCheckBox *chkBar_3;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget_5;
    QHBoxLayout *hboxLayout10;
    QLabel *label_11;
    QLineEdit *txtScaleZ_4;
    QCheckBox *chkBar_4;
    QGroupBox *groupBox_6;
    QWidget *layoutWidget_6;
    QHBoxLayout *hboxLayout11;
    QLabel *label_12;
    QLineEdit *txtScaleZ_1;
    QCheckBox *chkBar_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *ParamSetClass)
    {
        if (ParamSetClass->objectName().isEmpty())
            ParamSetClass->setObjectName("ParamSetClass");
        ParamSetClass->resize(652, 446);
        pushButton = new QPushButton(ParamSetClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(570, 400, 75, 23));
        groupBox = new QGroupBox(ParamSetClass);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 311, 121));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 80, 291, 25));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName("label_13");

        hboxLayout->addWidget(label_13);

        txtOutDir = new QLineEdit(layoutWidget);
        txtOutDir->setObjectName("txtOutDir");

        hboxLayout->addWidget(txtOutDir);

        btnSelect = new QPushButton(layoutWidget);
        btnSelect->setObjectName("btnSelect");

        hboxLayout->addWidget(btnSelect);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(10, 50, 291, 22));
        hboxLayout1 = new QHBoxLayout(layoutWidget1);
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(11, 11, 11, 11);
        hboxLayout1->setObjectName("hboxLayout1");
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName("label_8");

        hboxLayout1->addWidget(label_8);

        txtPadValue_1 = new QLineEdit(layoutWidget1);
        txtPadValue_1->setObjectName("txtPadValue_1");

        hboxLayout1->addWidget(txtPadValue_1);

        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName("label_9");

        hboxLayout1->addWidget(label_9);

        txtPadValue_2 = new QLineEdit(layoutWidget1);
        txtPadValue_2->setObjectName("txtPadValue_2");

        hboxLayout1->addWidget(txtPadValue_2);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(10, 20, 291, 22));
        hboxLayout2 = new QHBoxLayout(layoutWidget2);
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(11, 11, 11, 11);
        hboxLayout2->setObjectName("hboxLayout2");
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget2);
        label_14->setObjectName("label_14");

        hboxLayout2->addWidget(label_14);

        txtThreshVal_1 = new QLineEdit(layoutWidget2);
        txtThreshVal_1->setObjectName("txtThreshVal_1");

        hboxLayout2->addWidget(txtThreshVal_1);

        label_15 = new QLabel(layoutWidget2);
        label_15->setObjectName("label_15");

        hboxLayout2->addWidget(label_15);

        txtThreshVal_2 = new QLineEdit(layoutWidget2);
        txtThreshVal_2->setObjectName("txtThreshVal_2");

        hboxLayout2->addWidget(txtThreshVal_2);

        chkEffect = new QCheckBox(layoutWidget2);
        chkEffect->setObjectName("chkEffect");

        hboxLayout2->addWidget(chkEffect);

        groupBox_2 = new QGroupBox(ParamSetClass);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 270, 311, 121));
        layoutWidget3 = new QWidget(groupBox_2);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(10, 20, 159, 22));
        hboxLayout3 = new QHBoxLayout(layoutWidget3);
        hboxLayout3->setSpacing(6);
        hboxLayout3->setContentsMargins(11, 11, 11, 11);
        hboxLayout3->setObjectName("hboxLayout3");
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget3);
        label_7->setObjectName("label_7");

        hboxLayout3->addWidget(label_7);

        txtScaleZ_2 = new QLineEdit(layoutWidget3);
        txtScaleZ_2->setObjectName("txtScaleZ_2");

        hboxLayout3->addWidget(txtScaleZ_2);

        chkBar_2 = new QCheckBox(groupBox_2);
        chkBar_2->setObjectName("chkBar_2");
        chkBar_2->setGeometry(QRect(180, 20, 111, 18));
        chkMode = new QCheckBox(groupBox_2);
        chkMode->setObjectName("chkMode");
        chkMode->setGeometry(QRect(11, 52, 173, 18));
        groupBox_3 = new QGroupBox(ParamSetClass);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(330, 10, 311, 121));
        layoutWidget4 = new QWidget(groupBox_3);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(10, 20, 131, 22));
        hboxLayout4 = new QHBoxLayout(layoutWidget4);
        hboxLayout4->setSpacing(6);
        hboxLayout4->setContentsMargins(11, 11, 11, 11);
        hboxLayout4->setObjectName("hboxLayout4");
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget4);
        label_4->setObjectName("label_4");

        hboxLayout4->addWidget(label_4);

        txtRotation_x = new QLineEdit(layoutWidget4);
        txtRotation_x->setObjectName("txtRotation_x");

        hboxLayout4->addWidget(txtRotation_x);

        layoutWidget_2 = new QWidget(groupBox_3);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(10, 50, 131, 22));
        hboxLayout5 = new QHBoxLayout(layoutWidget_2);
        hboxLayout5->setSpacing(6);
        hboxLayout5->setContentsMargins(11, 11, 11, 11);
        hboxLayout5->setObjectName("hboxLayout5");
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName("label_5");

        hboxLayout5->addWidget(label_5);

        txtRotation_y = new QLineEdit(layoutWidget_2);
        txtRotation_y->setObjectName("txtRotation_y");

        hboxLayout5->addWidget(txtRotation_y);

        layoutWidget_3 = new QWidget(groupBox_3);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(10, 80, 131, 22));
        hboxLayout6 = new QHBoxLayout(layoutWidget_3);
        hboxLayout6->setSpacing(6);
        hboxLayout6->setContentsMargins(11, 11, 11, 11);
        hboxLayout6->setObjectName("hboxLayout6");
        hboxLayout6->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget_3);
        label_6->setObjectName("label_6");

        hboxLayout6->addWidget(label_6);

        txtRotation_z = new QLineEdit(layoutWidget_3);
        txtRotation_z->setObjectName("txtRotation_z");

        hboxLayout6->addWidget(txtRotation_z);

        layoutWidget_8 = new QWidget(groupBox_3);
        layoutWidget_8->setObjectName("layoutWidget_8");
        layoutWidget_8->setGeometry(QRect(160, 50, 121, 22));
        hboxLayout7 = new QHBoxLayout(layoutWidget_8);
        hboxLayout7->setSpacing(6);
        hboxLayout7->setContentsMargins(11, 11, 11, 11);
        hboxLayout7->setObjectName("hboxLayout7");
        hboxLayout7->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(layoutWidget_8);
        label_16->setObjectName("label_16");

        hboxLayout7->addWidget(label_16);

        avgy = new QSpinBox(layoutWidget_8);
        avgy->setObjectName("avgy");
        avgy->setValue(2);

        hboxLayout7->addWidget(avgy);

        layoutWidget5 = new QWidget(groupBox_3);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(160, 20, 121, 22));
        hboxLayout8 = new QHBoxLayout(layoutWidget5);
        hboxLayout8->setSpacing(6);
        hboxLayout8->setContentsMargins(11, 11, 11, 11);
        hboxLayout8->setObjectName("hboxLayout8");
        hboxLayout8->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget5);
        label->setObjectName("label");

        hboxLayout8->addWidget(label);

        avgx = new QSpinBox(layoutWidget5);
        avgx->setObjectName("avgx");
        avgx->setValue(3);

        hboxLayout8->addWidget(avgx);

        groupBox_4 = new QGroupBox(ParamSetClass);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(330, 140, 311, 121));
        layoutWidget_4 = new QWidget(groupBox_4);
        layoutWidget_4->setObjectName("layoutWidget_4");
        layoutWidget_4->setGeometry(QRect(10, 20, 159, 22));
        hboxLayout9 = new QHBoxLayout(layoutWidget_4);
        hboxLayout9->setSpacing(6);
        hboxLayout9->setContentsMargins(11, 11, 11, 11);
        hboxLayout9->setObjectName("hboxLayout9");
        hboxLayout9->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget_4);
        label_10->setObjectName("label_10");

        hboxLayout9->addWidget(label_10);

        txtScaleZ_3 = new QLineEdit(layoutWidget_4);
        txtScaleZ_3->setObjectName("txtScaleZ_3");

        hboxLayout9->addWidget(txtScaleZ_3);

        rbAxis_1 = new QRadioButton(groupBox_4);
        rbAxis_1->setObjectName("rbAxis_1");
        rbAxis_1->setGeometry(QRect(10, 60, 111, 18));
        rbAxis_1->setChecked(true);
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(190, 90, 50, 14));
        rbAxis_2 = new QRadioButton(groupBox_4);
        rbAxis_2->setObjectName("rbAxis_2");
        rbAxis_2->setGeometry(QRect(10, 90, 111, 18));
        txtPadVal_2 = new QLineEdit(groupBox_4);
        txtPadVal_2->setObjectName("txtPadVal_2");
        txtPadVal_2->setGeometry(QRect(122, 90, 61, 20));
        txtPadVal_1 = new QLineEdit(groupBox_4);
        txtPadVal_1->setObjectName("txtPadVal_1");
        txtPadVal_1->setGeometry(QRect(122, 60, 61, 20));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(190, 60, 50, 14));
        chkBar_3 = new QCheckBox(groupBox_4);
        chkBar_3->setObjectName("chkBar_3");
        chkBar_3->setGeometry(QRect(180, 20, 101, 18));
        groupBox_5 = new QGroupBox(ParamSetClass);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(330, 270, 311, 121));
        layoutWidget_5 = new QWidget(groupBox_5);
        layoutWidget_5->setObjectName("layoutWidget_5");
        layoutWidget_5->setGeometry(QRect(10, 20, 159, 22));
        hboxLayout10 = new QHBoxLayout(layoutWidget_5);
        hboxLayout10->setSpacing(6);
        hboxLayout10->setContentsMargins(11, 11, 11, 11);
        hboxLayout10->setObjectName("hboxLayout10");
        hboxLayout10->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget_5);
        label_11->setObjectName("label_11");

        hboxLayout10->addWidget(label_11);

        txtScaleZ_4 = new QLineEdit(layoutWidget_5);
        txtScaleZ_4->setObjectName("txtScaleZ_4");

        hboxLayout10->addWidget(txtScaleZ_4);

        chkBar_4 = new QCheckBox(groupBox_5);
        chkBar_4->setObjectName("chkBar_4");
        chkBar_4->setGeometry(QRect(180, 20, 101, 18));
        groupBox_6 = new QGroupBox(ParamSetClass);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(10, 140, 311, 121));
        layoutWidget_6 = new QWidget(groupBox_6);
        layoutWidget_6->setObjectName("layoutWidget_6");
        layoutWidget_6->setGeometry(QRect(10, 20, 281, 22));
        hboxLayout11 = new QHBoxLayout(layoutWidget_6);
        hboxLayout11->setSpacing(6);
        hboxLayout11->setContentsMargins(11, 11, 11, 11);
        hboxLayout11->setObjectName("hboxLayout11");
        hboxLayout11->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget_6);
        label_12->setObjectName("label_12");

        hboxLayout11->addWidget(label_12);

        txtScaleZ_1 = new QLineEdit(layoutWidget_6);
        txtScaleZ_1->setObjectName("txtScaleZ_1");

        hboxLayout11->addWidget(txtScaleZ_1);

        chkBar_1 = new QCheckBox(layoutWidget_6);
        chkBar_1->setObjectName("chkBar_1");

        hboxLayout11->addWidget(chkBar_1);

        pushButton_2 = new QPushButton(ParamSetClass);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 400, 75, 23));
        pushButton_3 = new QPushButton(ParamSetClass);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(100, 400, 75, 23));

        retranslateUi(ParamSetClass);

        QMetaObject::connectSlotsByName(ParamSetClass);
    } // setupUi

    void retranslateUi(QWidget *ParamSetClass)
    {
        ParamSetClass->setWindowTitle(QCoreApplication::translate("ParamSetClass", "ParamSet", nullptr));
        pushButton->setText(QCoreApplication::translate("ParamSetClass", "Close(&C)", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ParamSetClass", "Common Parameter", nullptr));
        label_13->setText(QCoreApplication::translate("ParamSetClass", "OutPutDir", nullptr));
        txtOutDir->setText(QCoreApplication::translate("ParamSetClass", "C:/Tmp", nullptr));
        btnSelect->setText(QCoreApplication::translate("ParamSetClass", "Select", nullptr));
        label_8->setText(QCoreApplication::translate("ParamSetClass", "Pad Value Range", nullptr));
        txtPadValue_1->setText(QCoreApplication::translate("ParamSetClass", "350", nullptr));
        label_9->setText(QCoreApplication::translate("ParamSetClass", "-", nullptr));
        txtPadValue_2->setText(QCoreApplication::translate("ParamSetClass", "2000", nullptr));
        label_14->setText(QCoreApplication::translate("ParamSetClass", "threshold Range Value", nullptr));
        txtThreshVal_1->setText(QCoreApplication::translate("ParamSetClass", "80", nullptr));
        label_15->setText(QCoreApplication::translate("ParamSetClass", "-", nullptr));
        txtThreshVal_2->setText(QCoreApplication::translate("ParamSetClass", "255", nullptr));
        chkEffect->setText(QCoreApplication::translate("ParamSetClass", "Effect", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ParamSetClass", "Brightness Parameter", nullptr));
        label_7->setText(QCoreApplication::translate("ParamSetClass", "Scale-Z", nullptr));
        txtScaleZ_2->setText(QCoreApplication::translate("ParamSetClass", "30", nullptr));
        chkBar_2->setText(QCoreApplication::translate("ParamSetClass", "BarChar", nullptr));
        chkMode->setText(QCoreApplication::translate("ParamSetClass", "OffSetMode", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ParamSetClass", "3D Graph Common Parameter", nullptr));
        label_4->setText(QCoreApplication::translate("ParamSetClass", "Rotation-X", nullptr));
        txtRotation_x->setText(QCoreApplication::translate("ParamSetClass", "30", nullptr));
        label_5->setText(QCoreApplication::translate("ParamSetClass", "Rotation-Y", nullptr));
        txtRotation_y->setText(QCoreApplication::translate("ParamSetClass", "0", nullptr));
        label_6->setText(QCoreApplication::translate("ParamSetClass", "Rotation-Z", nullptr));
        txtRotation_z->setText(QCoreApplication::translate("ParamSetClass", "15", nullptr));
        label_16->setText(QCoreApplication::translate("ParamSetClass", "AvgY", nullptr));
        label->setText(QCoreApplication::translate("ParamSetClass", "AvgX", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ParamSetClass", "Resolution Parameter", nullptr));
        label_10->setText(QCoreApplication::translate("ParamSetClass", "Scale-Z", nullptr));
        txtScaleZ_3->setText(QCoreApplication::translate("ParamSetClass", "50", nullptr));
        rbAxis_1->setText(QCoreApplication::translate("ParamSetClass", "X Axis", nullptr));
        label_3->setText(QCoreApplication::translate("ParamSetClass", "um", nullptr));
        rbAxis_2->setText(QCoreApplication::translate("ParamSetClass", "Y Axis", nullptr));
        txtPadVal_2->setText(QCoreApplication::translate("ParamSetClass", "5000", nullptr));
        txtPadVal_1->setText(QCoreApplication::translate("ParamSetClass", "5000", nullptr));
        label_2->setText(QCoreApplication::translate("ParamSetClass", "um", nullptr));
        chkBar_3->setText(QCoreApplication::translate("ParamSetClass", "BarChar", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("ParamSetClass", "Angle Parameter", nullptr));
        label_11->setText(QCoreApplication::translate("ParamSetClass", "Scale-Z", nullptr));
        txtScaleZ_4->setText(QCoreApplication::translate("ParamSetClass", "30", nullptr));
        chkBar_4->setText(QCoreApplication::translate("ParamSetClass", "BarChar", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("ParamSetClass", "Focus Parameter", nullptr));
        label_12->setText(QCoreApplication::translate("ParamSetClass", "Scale-Z", nullptr));
        txtScaleZ_1->setText(QCoreApplication::translate("ParamSetClass", "800", nullptr));
        chkBar_1->setText(QCoreApplication::translate("ParamSetClass", "BarChar", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ParamSetClass", "Load(&L)", nullptr));
        pushButton_3->setText(QCoreApplication::translate("ParamSetClass", "Save(&S)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParamSetClass: public Ui_ParamSetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMSET_H
