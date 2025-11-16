/********************************************************************************
** Form generated from reading UI file 'ShowSettingVCutForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSETTINGVCUTFORM_H
#define UI_SHOWSETTINGVCUTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowSettingVCutForm
{
public:
    QLabel *label_11;
    QSpinBox *EditThresholdShift;
    QLabel *label_10;
    QLabel *label_12;
    QCheckBox *checkBoxGenDynamicMask;
    QLabel *label_13;
    QSpinBox *EditThresholdLength;
    QSpinBox *EditExpandGenMask;
    QPushButton *pushButtonSetOne;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSetAll;
    QPushButton *pushButtonSimShowCenterPos;
    QLineEdit *EditShowShiftXY;
    QFrame *frame_SimImage;
    QToolButton *toolButtonSimShowNGMark;
    QLabel *label_6;
    QToolButton *toolButtonSimShowItem;
    QLabel *label_14;
    QLineEdit *EditResultMinDifference;
    QDoubleSpinBox *EditThresholdLevel;

    void setupUi(QWidget *ShowSettingVCutForm)
    {
        if (ShowSettingVCutForm->objectName().isEmpty())
            ShowSettingVCutForm->setObjectName("ShowSettingVCutForm");
        ShowSettingVCutForm->resize(504, 663);
        label_11 = new QLabel(ShowSettingVCutForm);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 500, 251, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditThresholdShift = new QSpinBox(ShowSettingVCutForm);
        EditThresholdShift->setObjectName("EditThresholdShift");
        EditThresholdShift->setGeometry(QRect(270, 500, 81, 22));
        EditThresholdShift->setMaximum(1000000);
        label_10 = new QLabel(ShowSettingVCutForm);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 480, 251, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_12 = new QLabel(ShowSettingVCutForm);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 520, 251, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxGenDynamicMask = new QCheckBox(ShowSettingVCutForm);
        checkBoxGenDynamicMask->setObjectName("checkBoxGenDynamicMask");
        checkBoxGenDynamicMask->setGeometry(QRect(20, 550, 241, 22));
        label_13 = new QLabel(ShowSettingVCutForm);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 580, 251, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditThresholdLength = new QSpinBox(ShowSettingVCutForm);
        EditThresholdLength->setObjectName("EditThresholdLength");
        EditThresholdLength->setGeometry(QRect(270, 520, 81, 22));
        EditThresholdLength->setMaximum(1000000);
        EditExpandGenMask = new QSpinBox(ShowSettingVCutForm);
        EditExpandGenMask->setObjectName("EditExpandGenMask");
        EditExpandGenMask->setGeometry(QRect(270, 580, 81, 22));
        EditExpandGenMask->setMinimum(-100);
        EditExpandGenMask->setMaximum(100);
        pushButtonSetOne = new QPushButton(ShowSettingVCutForm);
        pushButtonSetOne->setObjectName("pushButtonSetOne");
        pushButtonSetOne->setGeometry(QRect(10, 620, 151, 31));
        pushButtonClose = new QPushButton(ShowSettingVCutForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(380, 620, 101, 31));
        pushButtonSetAll = new QPushButton(ShowSettingVCutForm);
        pushButtonSetAll->setObjectName("pushButtonSetAll");
        pushButtonSetAll->setGeometry(QRect(180, 620, 171, 31));
        pushButtonSimShowCenterPos = new QPushButton(ShowSettingVCutForm);
        pushButtonSimShowCenterPos->setObjectName("pushButtonSimShowCenterPos");
        pushButtonSimShowCenterPos->setGeometry(QRect(370, 10, 111, 31));
        EditShowShiftXY = new QLineEdit(ShowSettingVCutForm);
        EditShowShiftXY->setObjectName("EditShowShiftXY");
        EditShowShiftXY->setGeometry(QRect(220, 450, 151, 21));
        EditShowShiftXY->setReadOnly(true);
        frame_SimImage = new QFrame(ShowSettingVCutForm);
        frame_SimImage->setObjectName("frame_SimImage");
        frame_SimImage->setGeometry(QRect(10, 50, 481, 391));
        frame_SimImage->setFrameShape(QFrame::StyledPanel);
        frame_SimImage->setFrameShadow(QFrame::Sunken);
        toolButtonSimShowNGMark = new QToolButton(ShowSettingVCutForm);
        toolButtonSimShowNGMark->setObjectName("toolButtonSimShowNGMark");
        toolButtonSimShowNGMark->setGeometry(QRect(180, 10, 141, 31));
        toolButtonSimShowNGMark->setCheckable(true);
        toolButtonSimShowNGMark->setChecked(true);
        label_6 = new QLabel(ShowSettingVCutForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(61, 450, 151, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        toolButtonSimShowItem = new QToolButton(ShowSettingVCutForm);
        toolButtonSimShowItem->setObjectName("toolButtonSimShowItem");
        toolButtonSimShowItem->setGeometry(QRect(10, 10, 141, 31));
        toolButtonSimShowItem->setCheckable(true);
        toolButtonSimShowItem->setChecked(true);
        label_14 = new QLabel(ShowSettingVCutForm);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(380, 460, 111, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditResultMinDifference = new QLineEdit(ShowSettingVCutForm);
        EditResultMinDifference->setObjectName("EditResultMinDifference");
        EditResultMinDifference->setGeometry(QRect(380, 480, 111, 21));
        EditResultMinDifference->setReadOnly(true);
        EditThresholdLevel = new QDoubleSpinBox(ShowSettingVCutForm);
        EditThresholdLevel->setObjectName("EditThresholdLevel");
        EditThresholdLevel->setGeometry(QRect(270, 480, 101, 22));
        EditThresholdLevel->setDecimals(3);
        EditThresholdLevel->setMaximum(99999999.000000000000000);

        retranslateUi(ShowSettingVCutForm);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(ShowSettingVCutForm);
    } // setupUi

    void retranslateUi(QWidget *ShowSettingVCutForm)
    {
        ShowSettingVCutForm->setWindowTitle(QCoreApplication::translate("ShowSettingVCutForm", "Form", nullptr));
        label_11->setText(QCoreApplication::translate("ShowSettingVCutForm", "\344\275\215\347\275\256\343\201\232\343\202\214\350\250\261\345\256\271\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        label_10->setText(QCoreApplication::translate("ShowSettingVCutForm", "\346\212\275\345\207\272\343\203\254\343\203\231\343\203\253", nullptr));
        label_12->setText(QCoreApplication::translate("ShowSettingVCutForm", "V\343\202\253\343\203\203\343\203\210\347\204\241\343\201\227\343\201\256\350\250\261\345\256\271\351\225\267\343\201\225", nullptr));
        checkBoxGenDynamicMask->setText(QCoreApplication::translate("ShowSettingVCutForm", "DynamicMask\347\224\237\346\210\220", nullptr));
        label_13->setText(QCoreApplication::translate("ShowSettingVCutForm", "\347\224\237\346\210\220\343\203\236\343\202\271\343\202\257\343\201\256\350\206\250\345\274\265", nullptr));
        pushButtonSetOne->setText(QCoreApplication::translate("ShowSettingVCutForm", "Set in this point", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowSettingVCutForm", "Close", nullptr));
        pushButtonSetAll->setText(QCoreApplication::translate("ShowSettingVCutForm", "Set to all points", nullptr));
        pushButtonSimShowCenterPos->setText(QCoreApplication::translate("ShowSettingVCutForm", "\345\276\251\345\270\260", nullptr));
        EditShowShiftXY->setText(QCoreApplication::translate("ShowSettingVCutForm", "12345", nullptr));
        toolButtonSimShowNGMark->setText(QCoreApplication::translate("ShowSettingVCutForm", "NG\351\240\230\345\237\237", nullptr));
        label_6->setText(QCoreApplication::translate("ShowSettingVCutForm", "\344\275\215\347\275\256\343\202\272\343\203\254\350\243\234\346\255\243", nullptr));
        toolButtonSimShowItem->setText(QCoreApplication::translate("ShowSettingVCutForm", "\346\244\234\346\237\273\351\240\230\345\237\237", nullptr));
        label_14->setText(QCoreApplication::translate("ShowSettingVCutForm", "\347\217\276\345\234\250\343\201\256\347\265\220\346\236\234", nullptr));
        EditResultMinDifference->setText(QCoreApplication::translate("ShowSettingVCutForm", "12345", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowSettingVCutForm: public Ui_ShowSettingVCutForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSETTINGVCUTFORM_H
