/********************************************************************************
** Form generated from reading UI file 'ShowThumbnailPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWTHUMBNAILPROPERTYFORM_H
#define UI_SHOWTHUMBNAILPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ShowThumbnailPropertyClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButtonColorNoChecked;
    QPushButton *pushButtonColorChecked;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButtonColorF1;
    QPushButton *pushButtonColorF2;
    QPushButton *pushButtonColorF3;
    QPushButton *pushButtonColorF4;
    QPushButton *pushButtonColorF5;
    QPushButton *pushButtonColorF6;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButtonColorF7;
    QPushButton *pushButtonColorF8;
    QPushButton *pushButtonColorF9;
    QPushButton *pushButtonColorF10;
    QPushButton *pushButtonColorF11;
    QPushButton *pushButtonColorF12;
    QCheckBox *cbEnableExpandDialog;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *sbCheckMillSec;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *sbRowCount;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *cbInitialMoveMode;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *sbColumnCount;
    QCheckBox *cbViewMaster;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbOK;
    QPushButton *pbApply;
    QPushButton *pbCancel;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QSpinBox *sbNGSignSize;
    QLabel *label_7;
    QCheckBox *cbModeShowPageByPiece;

    void setupUi(QDialog *ShowThumbnailPropertyClass)
    {
        if (ShowThumbnailPropertyClass->objectName().isEmpty())
            ShowThumbnailPropertyClass->setObjectName(QString::fromUtf8("ShowThumbnailPropertyClass"));
        ShowThumbnailPropertyClass->resize(747, 585);
        gridLayout = new QGridLayout(ShowThumbnailPropertyClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButtonColorNoChecked = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorNoChecked->setObjectName(QString::fromUtf8("pushButtonColorNoChecked"));

        horizontalLayout_7->addWidget(pushButtonColorNoChecked);

        pushButtonColorChecked = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorChecked->setObjectName(QString::fromUtf8("pushButtonColorChecked"));

        horizontalLayout_7->addWidget(pushButtonColorChecked);


        gridLayout->addLayout(horizontalLayout_7, 8, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        pushButtonColorF1 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF1->setObjectName(QString::fromUtf8("pushButtonColorF1"));

        horizontalLayout_9->addWidget(pushButtonColorF1);

        pushButtonColorF2 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF2->setObjectName(QString::fromUtf8("pushButtonColorF2"));

        horizontalLayout_9->addWidget(pushButtonColorF2);

        pushButtonColorF3 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF3->setObjectName(QString::fromUtf8("pushButtonColorF3"));

        horizontalLayout_9->addWidget(pushButtonColorF3);

        pushButtonColorF4 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF4->setObjectName(QString::fromUtf8("pushButtonColorF4"));

        horizontalLayout_9->addWidget(pushButtonColorF4);

        pushButtonColorF5 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF5->setObjectName(QString::fromUtf8("pushButtonColorF5"));

        horizontalLayout_9->addWidget(pushButtonColorF5);

        pushButtonColorF6 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF6->setObjectName(QString::fromUtf8("pushButtonColorF6"));

        horizontalLayout_9->addWidget(pushButtonColorF6);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pushButtonColorF7 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF7->setObjectName(QString::fromUtf8("pushButtonColorF7"));

        horizontalLayout_8->addWidget(pushButtonColorF7);

        pushButtonColorF8 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF8->setObjectName(QString::fromUtf8("pushButtonColorF8"));

        horizontalLayout_8->addWidget(pushButtonColorF8);

        pushButtonColorF9 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF9->setObjectName(QString::fromUtf8("pushButtonColorF9"));

        horizontalLayout_8->addWidget(pushButtonColorF9);

        pushButtonColorF10 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF10->setObjectName(QString::fromUtf8("pushButtonColorF10"));

        horizontalLayout_8->addWidget(pushButtonColorF10);

        pushButtonColorF11 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF11->setObjectName(QString::fromUtf8("pushButtonColorF11"));

        horizontalLayout_8->addWidget(pushButtonColorF11);

        pushButtonColorF12 = new QPushButton(ShowThumbnailPropertyClass);
        pushButtonColorF12->setObjectName(QString::fromUtf8("pushButtonColorF12"));

        horizontalLayout_8->addWidget(pushButtonColorF12);


        verticalLayout->addLayout(horizontalLayout_8);


        gridLayout->addLayout(verticalLayout, 9, 0, 1, 1);

        cbEnableExpandDialog = new QCheckBox(ShowThumbnailPropertyClass);
        cbEnableExpandDialog->setObjectName(QString::fromUtf8("cbEnableExpandDialog"));

        gridLayout->addWidget(cbEnableExpandDialog, 5, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(ShowThumbnailPropertyClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        sbCheckMillSec = new QSpinBox(ShowThumbnailPropertyClass);
        sbCheckMillSec->setObjectName(QString::fromUtf8("sbCheckMillSec"));
        sbCheckMillSec->setMaximum(99999);

        horizontalLayout_3->addWidget(sbCheckMillSec);

        label_6 = new QLabel(ShowThumbnailPropertyClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(ShowThumbnailPropertyClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        sbRowCount = new QSpinBox(ShowThumbnailPropertyClass);
        sbRowCount->setObjectName(QString::fromUtf8("sbRowCount"));

        horizontalLayout_2->addWidget(sbRowCount);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(ShowThumbnailPropertyClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        cbInitialMoveMode = new QComboBox(ShowThumbnailPropertyClass);
        cbInitialMoveMode->addItem(QString());
        cbInitialMoveMode->addItem(QString());
        cbInitialMoveMode->setObjectName(QString::fromUtf8("cbInitialMoveMode"));
        cbInitialMoveMode->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_4->addWidget(cbInitialMoveMode);


        gridLayout->addLayout(horizontalLayout_4, 7, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(ShowThumbnailPropertyClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        sbColumnCount = new QSpinBox(ShowThumbnailPropertyClass);
        sbColumnCount->setObjectName(QString::fromUtf8("sbColumnCount"));

        horizontalLayout->addWidget(sbColumnCount);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        cbViewMaster = new QCheckBox(ShowThumbnailPropertyClass);
        cbViewMaster->setObjectName(QString::fromUtf8("cbViewMaster"));

        gridLayout->addWidget(cbViewMaster, 4, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        pbOK = new QPushButton(ShowThumbnailPropertyClass);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbOK->setIcon(icon);

        horizontalLayout_5->addWidget(pbOK);

        pbApply = new QPushButton(ShowThumbnailPropertyClass);
        pbApply->setObjectName(QString::fromUtf8("pbApply"));

        horizontalLayout_5->addWidget(pbApply);

        pbCancel = new QPushButton(ShowThumbnailPropertyClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbCancel->setIcon(icon1);

        horizontalLayout_5->addWidget(pbCancel);


        gridLayout->addLayout(horizontalLayout_5, 10, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(ShowThumbnailPropertyClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        sbNGSignSize = new QSpinBox(ShowThumbnailPropertyClass);
        sbNGSignSize->setObjectName(QString::fromUtf8("sbNGSignSize"));

        horizontalLayout_6->addWidget(sbNGSignSize);

        label_7 = new QLabel(ShowThumbnailPropertyClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_6->addWidget(label_7);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_6, 3, 0, 1, 1);

        cbModeShowPageByPiece = new QCheckBox(ShowThumbnailPropertyClass);
        cbModeShowPageByPiece->setObjectName(QString::fromUtf8("cbModeShowPageByPiece"));

        gridLayout->addWidget(cbModeShowPageByPiece, 6, 0, 1, 1);

        QWidget::setTabOrder(sbRowCount, sbColumnCount);
        QWidget::setTabOrder(sbColumnCount, sbCheckMillSec);
        QWidget::setTabOrder(sbCheckMillSec, sbNGSignSize);
        QWidget::setTabOrder(sbNGSignSize, cbViewMaster);
        QWidget::setTabOrder(cbViewMaster, cbEnableExpandDialog);
        QWidget::setTabOrder(cbEnableExpandDialog, cbInitialMoveMode);
        QWidget::setTabOrder(cbInitialMoveMode, pbOK);
        QWidget::setTabOrder(pbOK, pbApply);
        QWidget::setTabOrder(pbApply, pbCancel);

        retranslateUi(ShowThumbnailPropertyClass);

        QMetaObject::connectSlotsByName(ShowThumbnailPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *ShowThumbnailPropertyClass)
    {
        ShowThumbnailPropertyClass->setWindowTitle(QCoreApplication::translate("ShowThumbnailPropertyClass", "ShowThumbnailForm", nullptr));
        pushButtonColorNoChecked->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "No check color", nullptr));
        pushButtonColorChecked->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "Checked color", nullptr));
        pushButtonColorF1->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F1", nullptr));
        pushButtonColorF2->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F2", nullptr));
        pushButtonColorF3->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F3", nullptr));
        pushButtonColorF4->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F4", nullptr));
        pushButtonColorF5->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F5", nullptr));
        pushButtonColorF6->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F6", nullptr));
        pushButtonColorF7->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F7", nullptr));
        pushButtonColorF8->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F8", nullptr));
        pushButtonColorF9->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F9", nullptr));
        pushButtonColorF10->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F10", nullptr));
        pushButtonColorF11->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F11", nullptr));
        pushButtonColorF12->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "F12", nullptr));
        cbEnableExpandDialog->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "enable expand image dialog", nullptr));
        label_3->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "Interval to next NG", nullptr));
        label_6->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "milli sec", nullptr));
        label->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "Row Count", nullptr));
        label_4->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "Initial Move Mode", nullptr));
        cbInitialMoveMode->setItemText(0, QCoreApplication::translate("ShowThumbnailPropertyClass", "Thumbnail Mode", nullptr));
        cbInitialMoveMode->setItemText(1, QCoreApplication::translate("ShowThumbnailPropertyClass", "Page Mode", nullptr));

        label_2->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "Column Count", nullptr));
        cbViewMaster->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "view Master Image", nullptr));
        pbOK->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "OK", nullptr));
        pbApply->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "Apply", nullptr));
        pbCancel->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "Cancel", nullptr));
        label_5->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "NG Sign size", nullptr));
        label_7->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "dot", nullptr));
        cbModeShowPageByPiece->setText(QCoreApplication::translate("ShowThumbnailPropertyClass", "Mode to show page by piece", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowThumbnailPropertyClass: public Ui_ShowThumbnailPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWTHUMBNAILPROPERTYFORM_H
