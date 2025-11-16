/********************************************************************************
** Form generated from reading UI file 'VRSControlForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VRSCONTROLFORM_H
#define UI_VRSCONTROLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VRSControlClass
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *sbZDistanceValue;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *sbZDistanceValueStep;
    QPushButton *pbSetZDistance;
    QCheckBox *cbXReverse;
    QSpacerItem *verticalSpacer;
    QCheckBox *cbYReverse;
    QGroupBox *gbPosition;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLabel *lbZPos;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *lbXPos;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLabel *lbYPos;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pbClose;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *sbMoveLength;
    QGridLayout *gridLayout;
    QPushButton *pbDown;
    QPushButton *pbUp;
    QPushButton *pbRight;
    QPushButton *pbLeft;

    void setupUi(QWidget *VRSControlClass)
    {
        if (VRSControlClass->objectName().isEmpty())
            VRSControlClass->setObjectName(QString::fromUtf8("VRSControlClass"));
        VRSControlClass->resize(540, 251);
        VRSControlClass->setWindowOpacity(1.000000000000000);
        gridLayout_3 = new QGridLayout(VRSControlClass);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_2 = new QLabel(VRSControlClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        sbZDistanceValue = new QSpinBox(VRSControlClass);
        sbZDistanceValue->setObjectName(QString::fromUtf8("sbZDistanceValue"));
        sbZDistanceValue->setMaximum(9999999);
        sbZDistanceValue->setSingleStep(1000);

        horizontalLayout_2->addWidget(sbZDistanceValue);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(VRSControlClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(VRSControlClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label_4);


        horizontalLayout_2->addLayout(verticalLayout);

        sbZDistanceValueStep = new QSpinBox(VRSControlClass);
        sbZDistanceValueStep->setObjectName(QString::fromUtf8("sbZDistanceValueStep"));
        sbZDistanceValueStep->setMaximum(999999);
        sbZDistanceValueStep->setSingleStep(1000);

        horizontalLayout_2->addWidget(sbZDistanceValueStep);

        pbSetZDistance = new QPushButton(VRSControlClass);
        pbSetZDistance->setObjectName(QString::fromUtf8("pbSetZDistance"));

        horizontalLayout_2->addWidget(pbSetZDistance);

        horizontalLayout_2->setStretch(3, 1);

        gridLayout_3->addLayout(horizontalLayout_2, 5, 0, 1, 3);

        cbXReverse = new QCheckBox(VRSControlClass);
        cbXReverse->setObjectName(QString::fromUtf8("cbXReverse"));

        gridLayout_3->addWidget(cbXReverse, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(74, 63, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 2, 1, 1);

        cbYReverse = new QCheckBox(VRSControlClass);
        cbYReverse->setObjectName(QString::fromUtf8("cbYReverse"));

        gridLayout_3->addWidget(cbYReverse, 0, 2, 1, 1);

        gbPosition = new QGroupBox(VRSControlClass);
        gbPosition->setObjectName(QString::fromUtf8("gbPosition"));
        gbPosition->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(gbPosition);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_8 = new QLabel(gbPosition);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(label_8);

        lbZPos = new QLabel(gbPosition);
        lbZPos->setObjectName(QString::fromUtf8("lbZPos"));
        sizePolicy2.setHeightForWidth(lbZPos->sizePolicy().hasHeightForWidth());
        lbZPos->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(lbZPos);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        gridLayout_2->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(gbPosition);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_6);

        lbXPos = new QLabel(gbPosition);
        lbXPos->setObjectName(QString::fromUtf8("lbXPos"));
        sizePolicy2.setHeightForWidth(lbXPos->sizePolicy().hasHeightForWidth());
        lbXPos->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(lbXPos);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_7 = new QLabel(gbPosition);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);

        horizontalLayout_6->addWidget(label_7);

        lbYPos = new QLabel(gbPosition);
        lbYPos->setObjectName(QString::fromUtf8("lbYPos"));
        sizePolicy2.setHeightForWidth(lbYPos->sizePolicy().hasHeightForWidth());
        lbYPos->setSizePolicy(sizePolicy2);

        horizontalLayout_6->addWidget(lbYPos);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        gridLayout_2->addLayout(horizontalLayout_6, 1, 0, 1, 1);


        gridLayout_3->addWidget(gbPosition, 0, 1, 3, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pbClose = new QPushButton(VRSControlClass);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));

        horizontalLayout_3->addWidget(pbClose);


        gridLayout_3->addLayout(horizontalLayout_3, 6, 0, 1, 3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(VRSControlClass);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        sbMoveLength = new QSpinBox(VRSControlClass);
        sbMoveLength->setObjectName(QString::fromUtf8("sbMoveLength"));
        sbMoveLength->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sbMoveLength->setMaximum(9999999);
        sbMoveLength->setSingleStep(1000);

        horizontalLayout->addWidget(sbMoveLength);

        horizontalLayout->setStretch(1, 1);

        gridLayout_3->addLayout(horizontalLayout, 3, 1, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbDown = new QPushButton(VRSControlClass);
        pbDown->setObjectName(QString::fromUtf8("pbDown"));

        gridLayout->addWidget(pbDown, 2, 1, 1, 1);

        pbUp = new QPushButton(VRSControlClass);
        pbUp->setObjectName(QString::fromUtf8("pbUp"));

        gridLayout->addWidget(pbUp, 0, 1, 1, 1);

        pbRight = new QPushButton(VRSControlClass);
        pbRight->setObjectName(QString::fromUtf8("pbRight"));

        gridLayout->addWidget(pbRight, 1, 2, 1, 1);

        pbLeft = new QPushButton(VRSControlClass);
        pbLeft->setObjectName(QString::fromUtf8("pbLeft"));

        gridLayout->addWidget(pbLeft, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 4, 1);

        QWidget::setTabOrder(sbMoveLength, sbZDistanceValue);
        QWidget::setTabOrder(sbZDistanceValue, sbZDistanceValueStep);
        QWidget::setTabOrder(sbZDistanceValueStep, pbSetZDistance);
        QWidget::setTabOrder(pbSetZDistance, cbYReverse);
        QWidget::setTabOrder(cbYReverse, cbXReverse);
        QWidget::setTabOrder(cbXReverse, pbUp);
        QWidget::setTabOrder(pbUp, pbDown);
        QWidget::setTabOrder(pbDown, pbLeft);
        QWidget::setTabOrder(pbLeft, pbRight);
        QWidget::setTabOrder(pbRight, pbClose);

        retranslateUi(VRSControlClass);
        QObject::connect(pbClose, SIGNAL(clicked()), VRSControlClass, SLOT(close()));

        QMetaObject::connectSlotsByName(VRSControlClass);
    } // setupUi

    void retranslateUi(QWidget *VRSControlClass)
    {
        VRSControlClass->setWindowTitle(QCoreApplication::translate("VRSControlClass", "VRSControlForm", nullptr));
        label_2->setText(QCoreApplication::translate("VRSControlClass", "Z Distance", nullptr));
        label_3->setText(QCoreApplication::translate("VRSControlClass", "+", nullptr));
        label_4->setText(QCoreApplication::translate("VRSControlClass", "-", nullptr));
        pbSetZDistance->setText(QCoreApplication::translate("VRSControlClass", "Set", nullptr));
        cbXReverse->setText(QCoreApplication::translate("VRSControlClass", "Reverse X", nullptr));
        cbYReverse->setText(QCoreApplication::translate("VRSControlClass", "Reverce Y", nullptr));
        gbPosition->setTitle(QCoreApplication::translate("VRSControlClass", "Posision", nullptr));
        label_8->setText(QCoreApplication::translate("VRSControlClass", "Z:", nullptr));
        lbZPos->setText(QCoreApplication::translate("VRSControlClass", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("VRSControlClass", "X:", nullptr));
        lbXPos->setText(QCoreApplication::translate("VRSControlClass", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("VRSControlClass", "Y:", nullptr));
        lbYPos->setText(QCoreApplication::translate("VRSControlClass", "TextLabel", nullptr));
        pbClose->setText(QCoreApplication::translate("VRSControlClass", "Close", nullptr));
        label->setText(QCoreApplication::translate("VRSControlClass", "Move Length", nullptr));
        pbDown->setText(QCoreApplication::translate("VRSControlClass", "Down", nullptr));
        pbUp->setText(QCoreApplication::translate("VRSControlClass", "Up", nullptr));
        pbRight->setText(QCoreApplication::translate("VRSControlClass", "Right", nullptr));
        pbLeft->setText(QCoreApplication::translate("VRSControlClass", "Left", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VRSControlClass: public Ui_VRSControlClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VRSCONTROLFORM_H
