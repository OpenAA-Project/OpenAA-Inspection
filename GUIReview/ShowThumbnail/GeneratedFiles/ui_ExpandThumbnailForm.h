/********************************************************************************
** Form generated from reading UI file 'ExpandThumbnailForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPANDTHUMBNAILFORM_H
#define UI_EXPANDTHUMBNAILFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ImageWidgetInThumbnail.h"

QT_BEGIN_NAMESPACE

class Ui_ExpandThumbnailForm
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    ImageWidgetInThumbnail *lbMaster;
    ImageWidgetInThumbnail *lbNG;
    QVBoxLayout *verticalLayout;
    QGroupBox *gbIngomation;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *lbTargetPos;
    QLabel *label_3;
    QLabel *lbNGCount;
    QLabel *label_4;
    QLabel *lbMasterPos;
    QFrame *line_3;
    QFrame *line_2;
    QFrame *line;
    QLabel *lbFKeyType;
    QLabel *label_5;
    QComboBox *comboBoxKeyCode;
    QPushButton *pushButtonSetKey;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ExpandThumbnailForm)
    {
        if (ExpandThumbnailForm->objectName().isEmpty())
            ExpandThumbnailForm->setObjectName(QString::fromUtf8("ExpandThumbnailForm"));
        ExpandThumbnailForm->resize(877, 713);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ExpandThumbnailForm->sizePolicy().hasHeightForWidth());
        ExpandThumbnailForm->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(ExpandThumbnailForm);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lbMaster = new ImageWidgetInThumbnail(ExpandThumbnailForm);
        lbMaster->setObjectName(QString::fromUtf8("lbMaster"));

        horizontalLayout->addWidget(lbMaster);

        lbNG = new ImageWidgetInThumbnail(ExpandThumbnailForm);
        lbNG->setObjectName(QString::fromUtf8("lbNG"));

        horizontalLayout->addWidget(lbNG);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gbIngomation = new QGroupBox(ExpandThumbnailForm);
        gbIngomation->setObjectName(QString::fromUtf8("gbIngomation"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gbIngomation->sizePolicy().hasHeightForWidth());
        gbIngomation->setSizePolicy(sizePolicy1);
        gbIngomation->setLayoutDirection(Qt::LeftToRight);
        gbIngomation->setFlat(false);
        gbIngomation->setCheckable(false);
        gridLayout_2 = new QGridLayout(gbIngomation);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(gbIngomation);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gbIngomation);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        lbTargetPos = new QLabel(gbIngomation);
        lbTargetPos->setObjectName(QString::fromUtf8("lbTargetPos"));
        lbTargetPos->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbTargetPos, 0, 1, 1, 1);

        label_3 = new QLabel(gbIngomation);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 6, 0, 1, 1);

        lbNGCount = new QLabel(gbIngomation);
        lbNGCount->setObjectName(QString::fromUtf8("lbNGCount"));
        lbNGCount->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbNGCount, 6, 1, 1, 1);

        label_4 = new QLabel(gbIngomation);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 9, 0, 1, 1);

        lbMasterPos = new QLabel(gbIngomation);
        lbMasterPos->setObjectName(QString::fromUtf8("lbMasterPos"));
        lbMasterPos->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbMasterPos, 4, 1, 1, 1);

        line_3 = new QFrame(gbIngomation);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 7, 0, 1, 2);

        line_2 = new QFrame(gbIngomation);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 5, 0, 1, 2);

        line = new QFrame(gbIngomation);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 0, 1, 2);

        lbFKeyType = new QLabel(gbIngomation);
        lbFKeyType->setObjectName(QString::fromUtf8("lbFKeyType"));
        lbFKeyType->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbFKeyType, 9, 1, 1, 1);

        label_5 = new QLabel(gbIngomation);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 10, 0, 1, 1);

        comboBoxKeyCode = new QComboBox(gbIngomation);
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->addItem(QString());
        comboBoxKeyCode->setObjectName(QString::fromUtf8("comboBoxKeyCode"));
        comboBoxKeyCode->setEditable(true);

        gridLayout->addWidget(comboBoxKeyCode, 10, 1, 1, 1);

        pushButtonSetKey = new QPushButton(gbIngomation);
        pushButtonSetKey->setObjectName(QString::fromUtf8("pushButtonSetKey"));

        gridLayout->addWidget(pushButtonSetKey, 11, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 2, 1);


        verticalLayout->addWidget(gbIngomation);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_3->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(ExpandThumbnailForm);

        QMetaObject::connectSlotsByName(ExpandThumbnailForm);
    } // setupUi

    void retranslateUi(QWidget *ExpandThumbnailForm)
    {
        ExpandThumbnailForm->setWindowTitle(QCoreApplication::translate("ExpandThumbnailForm", "ExpandThumbnailForm", nullptr));
        gbIngomation->setTitle(QCoreApplication::translate("ExpandThumbnailForm", "Infomation", nullptr));
        label->setText(QCoreApplication::translate("ExpandThumbnailForm", "Target (X,Y)", nullptr));
        label_2->setText(QCoreApplication::translate("ExpandThumbnailForm", "Master (X,Y)", nullptr));
        lbTargetPos->setText(QCoreApplication::translate("ExpandThumbnailForm", "Target (X,Y)", nullptr));
        label_3->setText(QCoreApplication::translate("ExpandThumbnailForm", "NGCount", nullptr));
        lbNGCount->setText(QCoreApplication::translate("ExpandThumbnailForm", "NGCount", nullptr));
        label_4->setText(QCoreApplication::translate("ExpandThumbnailForm", "FKeyType", nullptr));
        lbMasterPos->setText(QCoreApplication::translate("ExpandThumbnailForm", "Master (X,Y)", nullptr));
        lbFKeyType->setText(QCoreApplication::translate("ExpandThumbnailForm", "FKeyType", nullptr));
        label_5->setText(QCoreApplication::translate("ExpandThumbnailForm", "Key code", nullptr));
        comboBoxKeyCode->setItemText(0, QCoreApplication::translate("ExpandThumbnailForm", "No key", nullptr));
        comboBoxKeyCode->setItemText(1, QCoreApplication::translate("ExpandThumbnailForm", "F1", nullptr));
        comboBoxKeyCode->setItemText(2, QCoreApplication::translate("ExpandThumbnailForm", "F2", nullptr));
        comboBoxKeyCode->setItemText(3, QCoreApplication::translate("ExpandThumbnailForm", "F3", nullptr));
        comboBoxKeyCode->setItemText(4, QCoreApplication::translate("ExpandThumbnailForm", "F4", nullptr));
        comboBoxKeyCode->setItemText(5, QCoreApplication::translate("ExpandThumbnailForm", "F5", nullptr));
        comboBoxKeyCode->setItemText(6, QCoreApplication::translate("ExpandThumbnailForm", "F6", nullptr));
        comboBoxKeyCode->setItemText(7, QCoreApplication::translate("ExpandThumbnailForm", "F7", nullptr));
        comboBoxKeyCode->setItemText(8, QCoreApplication::translate("ExpandThumbnailForm", "F8", nullptr));
        comboBoxKeyCode->setItemText(9, QCoreApplication::translate("ExpandThumbnailForm", "F9", nullptr));
        comboBoxKeyCode->setItemText(10, QCoreApplication::translate("ExpandThumbnailForm", "F10", nullptr));

        pushButtonSetKey->setText(QCoreApplication::translate("ExpandThumbnailForm", "SetKey/Code", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExpandThumbnailForm: public Ui_ExpandThumbnailForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPANDTHUMBNAILFORM_H
