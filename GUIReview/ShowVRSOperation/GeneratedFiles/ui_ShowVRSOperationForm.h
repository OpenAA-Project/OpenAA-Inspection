/********************************************************************************
** Form generated from reading UI file 'ShowVRSOperationForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWVRSOPERATIONFORM_H
#define UI_SHOWVRSOPERATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
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

class Ui_ShowVRSOperationClass
{
public:
    QGridLayout *gridLayout_3;
    QFrame *line;
    QGridLayout *gridLayout;
    QPushButton *pbMoveUp;
    QPushButton *pbMoveLeft;
    QPushButton *pbMoveRight;
    QPushButton *pbMoveDown;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QSpinBox *sbMoveLength;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QSpinBox *sbZDiatance;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *sbZDistanceStep;
    QPushButton *pbSetZDiastance;
    QCheckBox *cbYReverse;
    QCheckBox *cbXReverse;
    QSpacerItem *verticalSpacer;
    QGroupBox *gbPosition;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLabel *lbZPos;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLabel *lbXPos;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLabel *lbYPos;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pbAlignmentManager;
    QPushButton *pbOrigin;
    QPushButton *pbVRSSetting;
    QPushButton *pbEscape;

    void setupUi(QWidget *ShowVRSOperationClass)
    {
        if (ShowVRSOperationClass->objectName().isEmpty())
            ShowVRSOperationClass->setObjectName(QString::fromUtf8("ShowVRSOperationClass"));
        ShowVRSOperationClass->resize(667, 310);
        gridLayout_3 = new QGridLayout(ShowVRSOperationClass);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        line = new QFrame(ShowVRSOperationClass);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 4, 0, 1, 8);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbMoveUp = new QPushButton(ShowVRSOperationClass);
        pbMoveUp->setObjectName(QString::fromUtf8("pbMoveUp"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbMoveUp->sizePolicy().hasHeightForWidth());
        pbMoveUp->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pbMoveUp, 0, 1, 1, 1);

        pbMoveLeft = new QPushButton(ShowVRSOperationClass);
        pbMoveLeft->setObjectName(QString::fromUtf8("pbMoveLeft"));
        sizePolicy.setHeightForWidth(pbMoveLeft->sizePolicy().hasHeightForWidth());
        pbMoveLeft->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pbMoveLeft, 1, 0, 1, 1);

        pbMoveRight = new QPushButton(ShowVRSOperationClass);
        pbMoveRight->setObjectName(QString::fromUtf8("pbMoveRight"));
        sizePolicy.setHeightForWidth(pbMoveRight->sizePolicy().hasHeightForWidth());
        pbMoveRight->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pbMoveRight, 1, 2, 1, 1);

        pbMoveDown = new QPushButton(ShowVRSOperationClass);
        pbMoveDown->setObjectName(QString::fromUtf8("pbMoveDown"));
        sizePolicy.setHeightForWidth(pbMoveDown->sizePolicy().hasHeightForWidth());
        pbMoveDown->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pbMoveDown, 2, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 4, 2);

        line_2 = new QFrame(ShowVRSOperationClass);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_2, 6, 0, 1, 8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_9 = new QLabel(ShowVRSOperationClass);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_9);

        sbMoveLength = new QSpinBox(ShowVRSOperationClass);
        sbMoveLength->setObjectName(QString::fromUtf8("sbMoveLength"));
        sbMoveLength->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sbMoveLength->setMaximum(2147483646);

        horizontalLayout_2->addWidget(sbMoveLength);


        gridLayout_3->addLayout(horizontalLayout_2, 3, 2, 1, 6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(ShowVRSOperationClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        sbZDiatance = new QSpinBox(ShowVRSOperationClass);
        sbZDiatance->setObjectName(QString::fromUtf8("sbZDiatance"));
        sbZDiatance->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sbZDiatance->setMinimum(-99999999);
        sbZDiatance->setMaximum(99999999);
        sbZDiatance->setSingleStep(100);

        horizontalLayout->addWidget(sbZDiatance);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(ShowVRSOperationClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(ShowVRSOperationClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);


        horizontalLayout->addLayout(verticalLayout_2);

        sbZDistanceStep = new QSpinBox(ShowVRSOperationClass);
        sbZDistanceStep->setObjectName(QString::fromUtf8("sbZDistanceStep"));
        sbZDistanceStep->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sbZDistanceStep->setMinimum(0);
        sbZDistanceStep->setMaximum(99999);
        sbZDistanceStep->setSingleStep(100);
        sbZDistanceStep->setValue(100);

        horizontalLayout->addWidget(sbZDistanceStep);

        pbSetZDiastance = new QPushButton(ShowVRSOperationClass);
        pbSetZDiastance->setObjectName(QString::fromUtf8("pbSetZDiastance"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pbSetZDiastance->sizePolicy().hasHeightForWidth());
        pbSetZDiastance->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(pbSetZDiastance);


        gridLayout_3->addLayout(horizontalLayout, 5, 0, 1, 8);

        cbYReverse = new QCheckBox(ShowVRSOperationClass);
        cbYReverse->setObjectName(QString::fromUtf8("cbYReverse"));

        gridLayout_3->addWidget(cbYReverse, 0, 7, 1, 1);

        cbXReverse = new QCheckBox(ShowVRSOperationClass);
        cbXReverse->setObjectName(QString::fromUtf8("cbXReverse"));

        gridLayout_3->addWidget(cbXReverse, 1, 7, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 7, 1, 1);

        gbPosition = new QGroupBox(ShowVRSOperationClass);
        gbPosition->setObjectName(QString::fromUtf8("gbPosition"));
        gbPosition->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(gbPosition);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_8 = new QLabel(gbPosition);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(label_8);

        lbZPos = new QLabel(gbPosition);
        lbZPos->setObjectName(QString::fromUtf8("lbZPos"));
        sizePolicy3.setHeightForWidth(lbZPos->sizePolicy().hasHeightForWidth());
        lbZPos->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(lbZPos);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(gbPosition);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(label_6);

        lbXPos = new QLabel(gbPosition);
        lbXPos->setObjectName(QString::fromUtf8("lbXPos"));
        sizePolicy3.setHeightForWidth(lbXPos->sizePolicy().hasHeightForWidth());
        lbXPos->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(lbXPos);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_7 = new QLabel(gbPosition);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(label_7);

        lbYPos = new QLabel(gbPosition);
        lbYPos->setObjectName(QString::fromUtf8("lbYPos"));
        sizePolicy3.setHeightForWidth(lbYPos->sizePolicy().hasHeightForWidth());
        lbYPos->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(lbYPos);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout_3->addWidget(gbPosition, 0, 2, 3, 5);

        pbAlignmentManager = new QPushButton(ShowVRSOperationClass);
        pbAlignmentManager->setObjectName(QString::fromUtf8("pbAlignmentManager"));

        gridLayout_3->addWidget(pbAlignmentManager, 8, 7, 1, 1);

        pbOrigin = new QPushButton(ShowVRSOperationClass);
        pbOrigin->setObjectName(QString::fromUtf8("pbOrigin"));

        gridLayout_3->addWidget(pbOrigin, 8, 0, 1, 1);

        pbVRSSetting = new QPushButton(ShowVRSOperationClass);
        pbVRSSetting->setObjectName(QString::fromUtf8("pbVRSSetting"));

        gridLayout_3->addWidget(pbVRSSetting, 8, 2, 1, 5);

        pbEscape = new QPushButton(ShowVRSOperationClass);
        pbEscape->setObjectName(QString::fromUtf8("pbEscape"));

        gridLayout_3->addWidget(pbEscape, 8, 1, 1, 1);

        QWidget::setTabOrder(sbMoveLength, sbZDiatance);
        QWidget::setTabOrder(sbZDiatance, sbZDistanceStep);
        QWidget::setTabOrder(sbZDistanceStep, pbSetZDiastance);
        QWidget::setTabOrder(pbSetZDiastance, cbYReverse);
        QWidget::setTabOrder(cbYReverse, cbXReverse);
        QWidget::setTabOrder(cbXReverse, pbMoveUp);
        QWidget::setTabOrder(pbMoveUp, pbMoveDown);
        QWidget::setTabOrder(pbMoveDown, pbMoveLeft);
        QWidget::setTabOrder(pbMoveLeft, pbMoveRight);

        retranslateUi(ShowVRSOperationClass);

        QMetaObject::connectSlotsByName(ShowVRSOperationClass);
    } // setupUi

    void retranslateUi(QWidget *ShowVRSOperationClass)
    {
        ShowVRSOperationClass->setWindowTitle(QCoreApplication::translate("ShowVRSOperationClass", "ShowVRSOperation", nullptr));
        pbMoveUp->setText(QCoreApplication::translate("ShowVRSOperationClass", "Up", nullptr));
        pbMoveLeft->setText(QCoreApplication::translate("ShowVRSOperationClass", "Left", nullptr));
        pbMoveRight->setText(QCoreApplication::translate("ShowVRSOperationClass", "Right", nullptr));
        pbMoveDown->setText(QCoreApplication::translate("ShowVRSOperationClass", "Down", nullptr));
        label_9->setText(QCoreApplication::translate("ShowVRSOperationClass", "Move Length", nullptr));
        label->setText(QCoreApplication::translate("ShowVRSOperationClass", "Z Distance", nullptr));
        label_4->setText(QCoreApplication::translate("ShowVRSOperationClass", "+", nullptr));
        label_5->setText(QCoreApplication::translate("ShowVRSOperationClass", "-", nullptr));
        sbZDistanceStep->setSuffix(QCoreApplication::translate("ShowVRSOperationClass", "step", nullptr));
        sbZDistanceStep->setPrefix(QString());
        pbSetZDiastance->setText(QCoreApplication::translate("ShowVRSOperationClass", "set", nullptr));
        cbYReverse->setText(QCoreApplication::translate("ShowVRSOperationClass", "Reverse Y", nullptr));
        cbXReverse->setText(QCoreApplication::translate("ShowVRSOperationClass", "Reverse X", nullptr));
        gbPosition->setTitle(QCoreApplication::translate("ShowVRSOperationClass", "Posision", nullptr));
        label_8->setText(QCoreApplication::translate("ShowVRSOperationClass", "Z:", nullptr));
        lbZPos->setText(QCoreApplication::translate("ShowVRSOperationClass", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("ShowVRSOperationClass", "X:", nullptr));
        lbXPos->setText(QCoreApplication::translate("ShowVRSOperationClass", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("ShowVRSOperationClass", "Y:", nullptr));
        lbYPos->setText(QCoreApplication::translate("ShowVRSOperationClass", "TextLabel", nullptr));
        pbAlignmentManager->setText(QCoreApplication::translate("ShowVRSOperationClass", "Alingment Manager", nullptr));
        pbOrigin->setText(QCoreApplication::translate("ShowVRSOperationClass", "Go to origin", nullptr));
        pbVRSSetting->setText(QCoreApplication::translate("ShowVRSOperationClass", "VRS Setting", nullptr));
        pbEscape->setText(QCoreApplication::translate("ShowVRSOperationClass", "Go to escape", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowVRSOperationClass: public Ui_ShowVRSOperationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWVRSOPERATIONFORM_H
