/********************************************************************************
** Form generated from reading UI file 'Setting.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_FilterImageShadingClass
{
public:
    QGridLayout *gridLayout_7;
    QGroupBox *gbLayer0;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QDoubleSpinBox *dsbTargetValueLayer0;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *dsbPreOffsetLayer0;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_7;
    QDoubleSpinBox *dsbAftOffsetLayer0;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_13;
    QLineEdit *leImageFilePathLayer0;
    QPushButton *pbLoadImageLayer0;
    QPushButton *pbClearLayer0;
    QGroupBox *gbInfoLayer0;
    QGridLayout *gridLayout_4;
    QLabel *label_3;
    QDoubleSpinBox *dsbMaxLayer0;
    QLabel *label_4;
    QDoubleSpinBox *dsbMinLayer0;
    QGroupBox *gbLayer1;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *dsbTargetValueLayer1;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_4;
    QDoubleSpinBox *dsbPreOffsetLayer1;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_8;
    QDoubleSpinBox *dsbAftOffsetLayer1;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_14;
    QLineEdit *leImageFilePathLayer1;
    QPushButton *pbLoadImageLayer1;
    QPushButton *pbClearLayer1;
    QGroupBox *gbInfoLayer0_2;
    QGridLayout *gridLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *dsbMaxLayer1;
    QLabel *label_6;
    QDoubleSpinBox *dsbMinLayer1;
    QGroupBox *gbLayer2;
    QGridLayout *gridLayout_10;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_15;
    QLineEdit *leImageFilePathLayer2;
    QPushButton *pbLoadImageLayer2;
    QPushButton *pbClearLayer2;
    QGroupBox *gbInfoLayer0_3;
    QGridLayout *gridLayout_6;
    QLabel *label_7;
    QDoubleSpinBox *dsbMaxLayer2;
    QLabel *label_8;
    QDoubleSpinBox *dsbMinLayer2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_5;
    QDoubleSpinBox *dsbTargetValueLayer2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_6;
    QDoubleSpinBox *dsbPreOffsetLayer2;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_9;
    QDoubleSpinBox *dsbAftOffsetLayer2;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *FilterImageShadingClass)
    {
        if (FilterImageShadingClass->objectName().isEmpty())
            FilterImageShadingClass->setObjectName("FilterImageShadingClass");
        FilterImageShadingClass->resize(549, 586);
        gridLayout_7 = new QGridLayout(FilterImageShadingClass);
        gridLayout_7->setObjectName("gridLayout_7");
        gbLayer0 = new QGroupBox(FilterImageShadingClass);
        gbLayer0->setObjectName("gbLayer0");
        gridLayout = new QGridLayout(gbLayer0);
        gridLayout->setObjectName("gridLayout");
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName("gridLayout_8");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(gbLayer0);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        dsbTargetValueLayer0 = new QDoubleSpinBox(gbLayer0);
        dsbTargetValueLayer0->setObjectName("dsbTargetValueLayer0");
        dsbTargetValueLayer0->setMinimum(1.000000000000000);
        dsbTargetValueLayer0->setMaximum(255.990000000000009);
        dsbTargetValueLayer0->setValue(1.000000000000000);

        horizontalLayout->addWidget(dsbTargetValueLayer0);


        gridLayout_8->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(gbLayer0);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        dsbPreOffsetLayer0 = new QDoubleSpinBox(gbLayer0);
        dsbPreOffsetLayer0->setObjectName("dsbPreOffsetLayer0");
        dsbPreOffsetLayer0->setMinimum(-254.990000000000009);
        dsbPreOffsetLayer0->setMaximum(254.990000000000009);
        dsbPreOffsetLayer0->setValue(0.000000000000000);

        horizontalLayout_2->addWidget(dsbPreOffsetLayer0);


        gridLayout_8->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_16 = new QLabel(gbLayer0);
        label_16->setObjectName("label_16");

        horizontalLayout_4->addWidget(label_16);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        dsbAftOffsetLayer0 = new QDoubleSpinBox(gbLayer0);
        dsbAftOffsetLayer0->setObjectName("dsbAftOffsetLayer0");
        dsbAftOffsetLayer0->setMinimum(-254.990000000000009);
        dsbAftOffsetLayer0->setMaximum(254.990000000000009);
        dsbAftOffsetLayer0->setValue(0.000000000000000);

        horizontalLayout_4->addWidget(dsbAftOffsetLayer0);


        gridLayout_8->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_8, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_13 = new QLabel(gbLayer0);
        label_13->setObjectName("label_13");

        horizontalLayout_3->addWidget(label_13);

        leImageFilePathLayer0 = new QLineEdit(gbLayer0);
        leImageFilePathLayer0->setObjectName("leImageFilePathLayer0");
        leImageFilePathLayer0->setReadOnly(true);

        horizontalLayout_3->addWidget(leImageFilePathLayer0);

        pbLoadImageLayer0 = new QPushButton(gbLayer0);
        pbLoadImageLayer0->setObjectName("pbLoadImageLayer0");
        pbLoadImageLayer0->setEnabled(true);

        horizontalLayout_3->addWidget(pbLoadImageLayer0);

        pbClearLayer0 = new QPushButton(gbLayer0);
        pbClearLayer0->setObjectName("pbClearLayer0");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbClearLayer0->sizePolicy().hasHeightForWidth());
        pbClearLayer0->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pbClearLayer0);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 2);

        gbInfoLayer0 = new QGroupBox(gbLayer0);
        gbInfoLayer0->setObjectName("gbInfoLayer0");
        gridLayout_4 = new QGridLayout(gbInfoLayer0);
        gridLayout_4->setObjectName("gridLayout_4");
        label_3 = new QLabel(gbInfoLayer0);
        label_3->setObjectName("label_3");

        gridLayout_4->addWidget(label_3, 0, 0, 1, 1);

        dsbMaxLayer0 = new QDoubleSpinBox(gbInfoLayer0);
        dsbMaxLayer0->setObjectName("dsbMaxLayer0");
        dsbMaxLayer0->setAlignment(Qt::AlignCenter);
        dsbMaxLayer0->setReadOnly(true);
        dsbMaxLayer0->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMaxLayer0->setMinimum(0.000000000000000);
        dsbMaxLayer0->setMaximum(255.000000000000000);
        dsbMaxLayer0->setValue(0.000000000000000);

        gridLayout_4->addWidget(dsbMaxLayer0, 0, 1, 1, 1);

        label_4 = new QLabel(gbInfoLayer0);
        label_4->setObjectName("label_4");

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        dsbMinLayer0 = new QDoubleSpinBox(gbInfoLayer0);
        dsbMinLayer0->setObjectName("dsbMinLayer0");
        dsbMinLayer0->setAlignment(Qt::AlignCenter);
        dsbMinLayer0->setReadOnly(true);
        dsbMinLayer0->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMinLayer0->setAccelerated(false);
        dsbMinLayer0->setMinimum(0.000000000000000);
        dsbMinLayer0->setMaximum(255.000000000000000);

        gridLayout_4->addWidget(dsbMinLayer0, 1, 1, 1, 1);


        gridLayout->addWidget(gbInfoLayer0, 1, 0, 1, 1);


        gridLayout_7->addWidget(gbLayer0, 0, 0, 1, 1);

        gbLayer1 = new QGroupBox(FilterImageShadingClass);
        gbLayer1->setObjectName("gbLayer1");
        gridLayout_9 = new QGridLayout(gbLayer1);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_9 = new QLabel(gbLayer1);
        label_9->setObjectName("label_9");

        horizontalLayout_5->addWidget(label_9);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        dsbTargetValueLayer1 = new QDoubleSpinBox(gbLayer1);
        dsbTargetValueLayer1->setObjectName("dsbTargetValueLayer1");
        dsbTargetValueLayer1->setMinimum(1.000000000000000);
        dsbTargetValueLayer1->setMaximum(255.990000000000009);

        horizontalLayout_5->addWidget(dsbTargetValueLayer1);


        gridLayout_2->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_10 = new QLabel(gbLayer1);
        label_10->setObjectName("label_10");

        horizontalLayout_6->addWidget(label_10);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        dsbPreOffsetLayer1 = new QDoubleSpinBox(gbLayer1);
        dsbPreOffsetLayer1->setObjectName("dsbPreOffsetLayer1");
        dsbPreOffsetLayer1->setMinimum(-254.990000000000009);
        dsbPreOffsetLayer1->setMaximum(254.990000000000009);
        dsbPreOffsetLayer1->setValue(0.000000000000000);

        horizontalLayout_6->addWidget(dsbPreOffsetLayer1);


        gridLayout_2->addLayout(horizontalLayout_6, 2, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_17 = new QLabel(gbLayer1);
        label_17->setObjectName("label_17");

        horizontalLayout_10->addWidget(label_17);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_8);

        dsbAftOffsetLayer1 = new QDoubleSpinBox(gbLayer1);
        dsbAftOffsetLayer1->setObjectName("dsbAftOffsetLayer1");
        dsbAftOffsetLayer1->setMinimum(-254.990000000000009);
        dsbAftOffsetLayer1->setMaximum(254.990000000000009);
        dsbAftOffsetLayer1->setValue(0.000000000000000);

        horizontalLayout_10->addWidget(dsbAftOffsetLayer1);


        gridLayout_2->addLayout(horizontalLayout_10, 1, 0, 1, 1);


        gridLayout_9->addLayout(gridLayout_2, 1, 1, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_14 = new QLabel(gbLayer1);
        label_14->setObjectName("label_14");

        horizontalLayout_7->addWidget(label_14);

        leImageFilePathLayer1 = new QLineEdit(gbLayer1);
        leImageFilePathLayer1->setObjectName("leImageFilePathLayer1");
        leImageFilePathLayer1->setReadOnly(true);

        horizontalLayout_7->addWidget(leImageFilePathLayer1);

        pbLoadImageLayer1 = new QPushButton(gbLayer1);
        pbLoadImageLayer1->setObjectName("pbLoadImageLayer1");
        pbLoadImageLayer1->setEnabled(true);

        horizontalLayout_7->addWidget(pbLoadImageLayer1);

        pbClearLayer1 = new QPushButton(gbLayer1);
        pbClearLayer1->setObjectName("pbClearLayer1");

        horizontalLayout_7->addWidget(pbClearLayer1);


        gridLayout_9->addLayout(horizontalLayout_7, 0, 0, 1, 2);

        gbInfoLayer0_2 = new QGroupBox(gbLayer1);
        gbInfoLayer0_2->setObjectName("gbInfoLayer0_2");
        gridLayout_5 = new QGridLayout(gbInfoLayer0_2);
        gridLayout_5->setObjectName("gridLayout_5");
        label_5 = new QLabel(gbInfoLayer0_2);
        label_5->setObjectName("label_5");

        gridLayout_5->addWidget(label_5, 0, 0, 1, 1);

        dsbMaxLayer1 = new QDoubleSpinBox(gbInfoLayer0_2);
        dsbMaxLayer1->setObjectName("dsbMaxLayer1");
        dsbMaxLayer1->setAlignment(Qt::AlignCenter);
        dsbMaxLayer1->setReadOnly(true);
        dsbMaxLayer1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMaxLayer1->setMinimum(0.000000000000000);
        dsbMaxLayer1->setMaximum(255.000000000000000);

        gridLayout_5->addWidget(dsbMaxLayer1, 0, 1, 1, 1);

        label_6 = new QLabel(gbInfoLayer0_2);
        label_6->setObjectName("label_6");

        gridLayout_5->addWidget(label_6, 1, 0, 1, 1);

        dsbMinLayer1 = new QDoubleSpinBox(gbInfoLayer0_2);
        dsbMinLayer1->setObjectName("dsbMinLayer1");
        dsbMinLayer1->setAlignment(Qt::AlignCenter);
        dsbMinLayer1->setReadOnly(true);
        dsbMinLayer1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMinLayer1->setMinimum(0.000000000000000);
        dsbMinLayer1->setMaximum(255.000000000000000);

        gridLayout_5->addWidget(dsbMinLayer1, 1, 1, 1, 1);


        gridLayout_9->addWidget(gbInfoLayer0_2, 1, 0, 1, 1);


        gridLayout_7->addWidget(gbLayer1, 1, 0, 1, 1);

        gbLayer2 = new QGroupBox(FilterImageShadingClass);
        gbLayer2->setObjectName("gbLayer2");
        gridLayout_10 = new QGridLayout(gbLayer2);
        gridLayout_10->setObjectName("gridLayout_10");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_15 = new QLabel(gbLayer2);
        label_15->setObjectName("label_15");

        horizontalLayout_11->addWidget(label_15);

        leImageFilePathLayer2 = new QLineEdit(gbLayer2);
        leImageFilePathLayer2->setObjectName("leImageFilePathLayer2");
        leImageFilePathLayer2->setReadOnly(true);

        horizontalLayout_11->addWidget(leImageFilePathLayer2);

        pbLoadImageLayer2 = new QPushButton(gbLayer2);
        pbLoadImageLayer2->setObjectName("pbLoadImageLayer2");
        pbLoadImageLayer2->setEnabled(true);

        horizontalLayout_11->addWidget(pbLoadImageLayer2);

        pbClearLayer2 = new QPushButton(gbLayer2);
        pbClearLayer2->setObjectName("pbClearLayer2");

        horizontalLayout_11->addWidget(pbClearLayer2);


        gridLayout_10->addLayout(horizontalLayout_11, 0, 0, 1, 2);

        gbInfoLayer0_3 = new QGroupBox(gbLayer2);
        gbInfoLayer0_3->setObjectName("gbInfoLayer0_3");
        gridLayout_6 = new QGridLayout(gbInfoLayer0_3);
        gridLayout_6->setObjectName("gridLayout_6");
        label_7 = new QLabel(gbInfoLayer0_3);
        label_7->setObjectName("label_7");

        gridLayout_6->addWidget(label_7, 0, 0, 1, 1);

        dsbMaxLayer2 = new QDoubleSpinBox(gbInfoLayer0_3);
        dsbMaxLayer2->setObjectName("dsbMaxLayer2");
        dsbMaxLayer2->setAlignment(Qt::AlignCenter);
        dsbMaxLayer2->setReadOnly(true);
        dsbMaxLayer2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMaxLayer2->setMinimum(0.000000000000000);
        dsbMaxLayer2->setMaximum(255.000000000000000);

        gridLayout_6->addWidget(dsbMaxLayer2, 0, 1, 1, 1);

        label_8 = new QLabel(gbInfoLayer0_3);
        label_8->setObjectName("label_8");

        gridLayout_6->addWidget(label_8, 1, 0, 1, 1);

        dsbMinLayer2 = new QDoubleSpinBox(gbInfoLayer0_3);
        dsbMinLayer2->setObjectName("dsbMinLayer2");
        dsbMinLayer2->setAlignment(Qt::AlignCenter);
        dsbMinLayer2->setReadOnly(true);
        dsbMinLayer2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMinLayer2->setMinimum(0.000000000000000);
        dsbMinLayer2->setMaximum(255.000000000000000);

        gridLayout_6->addWidget(dsbMinLayer2, 1, 1, 1, 1);


        gridLayout_10->addWidget(gbInfoLayer0_3, 1, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_11 = new QLabel(gbLayer2);
        label_11->setObjectName("label_11");

        horizontalLayout_8->addWidget(label_11);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        dsbTargetValueLayer2 = new QDoubleSpinBox(gbLayer2);
        dsbTargetValueLayer2->setObjectName("dsbTargetValueLayer2");
        dsbTargetValueLayer2->setMinimum(1.000000000000000);
        dsbTargetValueLayer2->setMaximum(255.990000000000009);

        horizontalLayout_8->addWidget(dsbTargetValueLayer2);


        gridLayout_3->addLayout(horizontalLayout_8, 0, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_12 = new QLabel(gbLayer2);
        label_12->setObjectName("label_12");

        horizontalLayout_9->addWidget(label_12);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        dsbPreOffsetLayer2 = new QDoubleSpinBox(gbLayer2);
        dsbPreOffsetLayer2->setObjectName("dsbPreOffsetLayer2");
        dsbPreOffsetLayer2->setMinimum(-254.990000000000009);
        dsbPreOffsetLayer2->setMaximum(254.990000000000009);
        dsbPreOffsetLayer2->setValue(0.000000000000000);

        horizontalLayout_9->addWidget(dsbPreOffsetLayer2);


        gridLayout_3->addLayout(horizontalLayout_9, 2, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_18 = new QLabel(gbLayer2);
        label_18->setObjectName("label_18");

        horizontalLayout_12->addWidget(label_18);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_9);

        dsbAftOffsetLayer2 = new QDoubleSpinBox(gbLayer2);
        dsbAftOffsetLayer2->setObjectName("dsbAftOffsetLayer2");
        dsbAftOffsetLayer2->setMinimum(-254.990000000000009);
        dsbAftOffsetLayer2->setMaximum(254.990000000000009);
        dsbAftOffsetLayer2->setValue(0.000000000000000);

        horizontalLayout_12->addWidget(dsbAftOffsetLayer2);


        gridLayout_3->addLayout(horizontalLayout_12, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_3, 1, 1, 1, 1);


        gridLayout_7->addWidget(gbLayer2, 2, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName("hboxLayout");
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(FilterImageShadingClass);
        okButton->setObjectName("okButton");

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(FilterImageShadingClass);
        cancelButton->setObjectName("cancelButton");

        hboxLayout->addWidget(cancelButton);


        gridLayout_7->addLayout(hboxLayout, 3, 0, 1, 1);


        retranslateUi(FilterImageShadingClass);
        QObject::connect(okButton, &QPushButton::clicked, FilterImageShadingClass, qOverload<>(&QDialog::accept));
        QObject::connect(cancelButton, &QPushButton::clicked, FilterImageShadingClass, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(FilterImageShadingClass);
    } // setupUi

    void retranslateUi(QDialog *FilterImageShadingClass)
    {
        FilterImageShadingClass->setWindowTitle(QCoreApplication::translate("FilterImageShadingClass", "FilterImageShading", nullptr));
        gbLayer0->setTitle(QCoreApplication::translate("FilterImageShadingClass", "Layer 0", nullptr));
        label_2->setText(QCoreApplication::translate("FilterImageShadingClass", "Target Value", nullptr));
        label->setText(QCoreApplication::translate("FilterImageShadingClass", "Aft offset", nullptr));
        label_16->setText(QCoreApplication::translate("FilterImageShadingClass", "Pre offset", nullptr));
        label_13->setText(QCoreApplication::translate("FilterImageShadingClass", "ImageFilePath", nullptr));
#if QT_CONFIG(tooltip)
        leImageFilePathLayer0->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        leImageFilePathLayer0->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbLoadImageLayer0->setText(QCoreApplication::translate("FilterImageShadingClass", "Load Image", nullptr));
        pbClearLayer0->setText(QCoreApplication::translate("FilterImageShadingClass", "Clear", nullptr));
        gbInfoLayer0->setTitle(QCoreApplication::translate("FilterImageShadingClass", "Infomation", nullptr));
        label_3->setText(QCoreApplication::translate("FilterImageShadingClass", "Max", nullptr));
        label_4->setText(QCoreApplication::translate("FilterImageShadingClass", "Min", nullptr));
        gbLayer1->setTitle(QCoreApplication::translate("FilterImageShadingClass", "Layer 1", nullptr));
        label_9->setText(QCoreApplication::translate("FilterImageShadingClass", "Target Value", nullptr));
        label_10->setText(QCoreApplication::translate("FilterImageShadingClass", "Aft offset", nullptr));
        label_17->setText(QCoreApplication::translate("FilterImageShadingClass", "Pre offset", nullptr));
        label_14->setText(QCoreApplication::translate("FilterImageShadingClass", "ImageFilePath", nullptr));
        pbLoadImageLayer1->setText(QCoreApplication::translate("FilterImageShadingClass", "Load Image", nullptr));
        pbClearLayer1->setText(QCoreApplication::translate("FilterImageShadingClass", "Clear", nullptr));
        gbInfoLayer0_2->setTitle(QCoreApplication::translate("FilterImageShadingClass", "Infomation", nullptr));
        label_5->setText(QCoreApplication::translate("FilterImageShadingClass", "Max", nullptr));
        label_6->setText(QCoreApplication::translate("FilterImageShadingClass", "Min", nullptr));
        gbLayer2->setTitle(QCoreApplication::translate("FilterImageShadingClass", "Layer 2", nullptr));
        label_15->setText(QCoreApplication::translate("FilterImageShadingClass", "ImageFilePath", nullptr));
        pbLoadImageLayer2->setText(QCoreApplication::translate("FilterImageShadingClass", "Load Image", nullptr));
        pbClearLayer2->setText(QCoreApplication::translate("FilterImageShadingClass", "Clear", nullptr));
        gbInfoLayer0_3->setTitle(QCoreApplication::translate("FilterImageShadingClass", "Infomation", nullptr));
        label_7->setText(QCoreApplication::translate("FilterImageShadingClass", "Max", nullptr));
        label_8->setText(QCoreApplication::translate("FilterImageShadingClass", "Min", nullptr));
        label_11->setText(QCoreApplication::translate("FilterImageShadingClass", "Target Value", nullptr));
        label_12->setText(QCoreApplication::translate("FilterImageShadingClass", "Aft offset", nullptr));
        label_18->setText(QCoreApplication::translate("FilterImageShadingClass", "Pre offset", nullptr));
        okButton->setText(QCoreApplication::translate("FilterImageShadingClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("FilterImageShadingClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterImageShadingClass: public Ui_FilterImageShadingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
