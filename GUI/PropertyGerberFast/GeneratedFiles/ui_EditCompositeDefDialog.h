/********************************************************************************
** Form generated from reading UI file 'EditCompositeDefDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCOMPOSITEDEFDIALOG_H
#define UI_EDITCOMPOSITEDEFDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_EditCompositeDefDialog
{
public:
    QFrame *frame_2;
    QPushButton *pushButtonSaveNew;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSaveFile;
    QPushButton *pushButtonLoadFile;
    QPushButton *pushButtonAppendFile;
    QLabel *label_4;
    QListWidget *listComposite;
    QPushButton *ButtonPlus;
    QLineEdit *lineEditName;
    QPushButton *ButtonMinus;
    QFrame *frameSampleBase;
    QGroupBox *groupBoxOperation1;
    QRadioButton *radioButtonOr;
    QRadioButton *radioButtonAnd;
    QRadioButton *radioButtonNotAnd;
    QRadioButton *radioButtonNotOr;
    QFrame *frameItem1;
    QSpinBox *SBoxDotSpr;
    QLabel *LabelLayerType;
    QLabel *LabelDot;
    QLabel *LabelNo;
    QPushButton *ButtonLayerType;
    QLineEdit *LayerTypeLibID;
    QLineEdit *LayerTypeLibName;
    QCheckBox *checkBoxNegMode;
    QPushButton *pushButtonRemoveLine;
    QToolButton *toolButtonUpper;
    QToolButton *toolButtonUpper_2;
    QFrame *frame;
    QLabel *label_6;
    QSpinBox *spinBoxMaxEnlargeDot;
    QSpinBox *spinBoxMaxShrinkageDot;
    QLabel *label_7;
    QSpinBox *spinBoxMaxShiftDot;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBoxMaxAngleRadius;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBoxMaxUnstableZone;
    QLineEdit *lineEditLibID;
    QLineEdit *lineEditLibName;
    QLabel *label_5;
    QPushButton *pushButtonSelectLib;
    QCheckBox *checkBoxNegModeInContainer;
    QFrame *frameLibFolder;

    void setupUi(QDialog *EditCompositeDefDialog)
    {
        if (EditCompositeDefDialog->objectName().isEmpty())
            EditCompositeDefDialog->setObjectName("EditCompositeDefDialog");
        EditCompositeDefDialog->resize(971, 631);
        frame_2 = new QFrame(EditCompositeDefDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 540, 971, 91));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButtonSaveNew = new QPushButton(frame_2);
        pushButtonSaveNew->setObjectName("pushButtonSaveNew");
        pushButtonSaveNew->setGeometry(QRect(220, 10, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSaveNew->setIcon(icon);
        pushButtonUpdate = new QPushButton(frame_2);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(340, 10, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon1);
        pushButtonDelete = new QPushButton(frame_2);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(450, 10, 111, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon2);
        pushButtonClose = new QPushButton(frame_2);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(450, 50, 111, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon3);
        pushButtonSaveFile = new QPushButton(frame_2);
        pushButtonSaveFile->setObjectName("pushButtonSaveFile");
        pushButtonSaveFile->setGeometry(QRect(720, 10, 112, 34));
        pushButtonLoadFile = new QPushButton(frame_2);
        pushButtonLoadFile->setObjectName("pushButtonLoadFile");
        pushButtonLoadFile->setGeometry(QRect(840, 10, 112, 34));
        pushButtonAppendFile = new QPushButton(frame_2);
        pushButtonAppendFile->setObjectName("pushButtonAppendFile");
        pushButtonAppendFile->setGeometry(QRect(840, 50, 112, 34));
        label_4 = new QLabel(EditCompositeDefDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(240, 0, 421, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listComposite = new QListWidget(EditCompositeDefDialog);
        listComposite->setObjectName("listComposite");
        listComposite->setGeometry(QRect(0, 210, 221, 321));
        ButtonPlus = new QPushButton(EditCompositeDefDialog);
        ButtonPlus->setObjectName("ButtonPlus");
        ButtonPlus->setGeometry(QRect(390, 500, 31, 31));
        lineEditName = new QLineEdit(EditCompositeDefDialog);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(240, 21, 421, 20));
        ButtonMinus = new QPushButton(EditCompositeDefDialog);
        ButtonMinus->setObjectName("ButtonMinus");
        ButtonMinus->setGeometry(QRect(430, 500, 31, 31));
        frameSampleBase = new QFrame(EditCompositeDefDialog);
        frameSampleBase->setObjectName("frameSampleBase");
        frameSampleBase->setGeometry(QRect(230, 50, 451, 441));
        frameSampleBase->setFrameShape(QFrame::StyledPanel);
        frameSampleBase->setFrameShadow(QFrame::Raised);
        groupBoxOperation1 = new QGroupBox(frameSampleBase);
        groupBoxOperation1->setObjectName("groupBoxOperation1");
        groupBoxOperation1->setGeometry(QRect(60, 80, 241, 21));
        radioButtonOr = new QRadioButton(groupBoxOperation1);
        radioButtonOr->setObjectName("radioButtonOr");
        radioButtonOr->setGeometry(QRect(10, 0, 61, 21));
        radioButtonOr->setChecked(true);
        radioButtonAnd = new QRadioButton(groupBoxOperation1);
        radioButtonAnd->setObjectName("radioButtonAnd");
        radioButtonAnd->setGeometry(QRect(60, 0, 61, 21));
        radioButtonAnd->setChecked(false);
        radioButtonNotAnd = new QRadioButton(groupBoxOperation1);
        radioButtonNotAnd->setObjectName("radioButtonNotAnd");
        radioButtonNotAnd->setGeometry(QRect(110, 0, 61, 21));
        radioButtonNotOr = new QRadioButton(groupBoxOperation1);
        radioButtonNotOr->setObjectName("radioButtonNotOr");
        radioButtonNotOr->setGeometry(QRect(180, 0, 81, 21));
        frameItem1 = new QFrame(frameSampleBase);
        frameItem1->setObjectName("frameItem1");
        frameItem1->setGeometry(QRect(10, 10, 421, 61));
        frameItem1->setFrameShape(QFrame::StyledPanel);
        frameItem1->setFrameShadow(QFrame::Sunken);
        SBoxDotSpr = new QSpinBox(frameItem1);
        SBoxDotSpr->setObjectName("SBoxDotSpr");
        SBoxDotSpr->setGeometry(QRect(340, 30, 51, 21));
        SBoxDotSpr->setMinimum(-99);
        LabelLayerType = new QLabel(frameItem1);
        LabelLayerType->setObjectName("LabelLayerType");
        LabelLayerType->setGeometry(QRect(30, 10, 231, 20));
        LabelLayerType->setFrameShape(QFrame::Panel);
        LabelLayerType->setFrameShadow(QFrame::Sunken);
        LabelLayerType->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LabelDot = new QLabel(frameItem1);
        LabelDot->setObjectName("LabelDot");
        LabelDot->setGeometry(QRect(340, 9, 50, 21));
        LabelDot->setFrameShape(QFrame::Panel);
        LabelDot->setFrameShadow(QFrame::Sunken);
        LabelDot->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LabelNo = new QLabel(frameItem1);
        LabelNo->setObjectName("LabelNo");
        LabelNo->setGeometry(QRect(0, 0, 16, 61));
        LabelNo->setFrameShape(QFrame::Panel);
        LabelNo->setFrameShadow(QFrame::Sunken);
        LabelNo->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLayerType = new QPushButton(frameItem1);
        ButtonLayerType->setObjectName("ButtonLayerType");
        ButtonLayerType->setGeometry(QRect(220, 30, 41, 23));
        LayerTypeLibID = new QLineEdit(frameItem1);
        LayerTypeLibID->setObjectName("LayerTypeLibID");
        LayerTypeLibID->setGeometry(QRect(30, 30, 51, 20));
        LayerTypeLibName = new QLineEdit(frameItem1);
        LayerTypeLibName->setObjectName("LayerTypeLibName");
        LayerTypeLibName->setGeometry(QRect(80, 30, 131, 20));
        checkBoxNegMode = new QCheckBox(frameItem1);
        checkBoxNegMode->setObjectName("checkBoxNegMode");
        checkBoxNegMode->setGeometry(QRect(274, 20, 61, 17));
        pushButtonRemoveLine = new QPushButton(frameItem1);
        pushButtonRemoveLine->setObjectName("pushButtonRemoveLine");
        pushButtonRemoveLine->setGeometry(QRect(390, 2, 20, 20));
        toolButtonUpper = new QToolButton(frameItem1);
        toolButtonUpper->setObjectName("toolButtonUpper");
        toolButtonUpper->setGeometry(QRect(390, 22, 20, 20));
        toolButtonUpper->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButtonUpper->setArrowType(Qt::UpArrow);
        toolButtonUpper_2 = new QToolButton(frameItem1);
        toolButtonUpper_2->setObjectName("toolButtonUpper_2");
        toolButtonUpper_2->setGeometry(QRect(390, 40, 20, 20));
        toolButtonUpper_2->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButtonUpper_2->setArrowType(Qt::DownArrow);
        frame = new QFrame(EditCompositeDefDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(690, 10, 271, 221));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 70, 101, 21));
        spinBoxMaxEnlargeDot = new QSpinBox(frame);
        spinBoxMaxEnlargeDot->setObjectName("spinBoxMaxEnlargeDot");
        spinBoxMaxEnlargeDot->setGeometry(QRect(160, 70, 101, 22));
        spinBoxMaxEnlargeDot->setMaximum(99999999);
        spinBoxMaxShrinkageDot = new QSpinBox(frame);
        spinBoxMaxShrinkageDot->setObjectName("spinBoxMaxShrinkageDot");
        spinBoxMaxShrinkageDot->setGeometry(QRect(160, 100, 101, 22));
        spinBoxMaxShrinkageDot->setMaximum(99999999);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 100, 101, 21));
        spinBoxMaxShiftDot = new QSpinBox(frame);
        spinBoxMaxShiftDot->setObjectName("spinBoxMaxShiftDot");
        spinBoxMaxShiftDot->setGeometry(QRect(160, 130, 101, 22));
        spinBoxMaxShiftDot->setMaximum(99999999);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 130, 101, 21));
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 160, 101, 21));
        doubleSpinBoxMaxAngleRadius = new QDoubleSpinBox(frame);
        doubleSpinBoxMaxAngleRadius->setObjectName("doubleSpinBoxMaxAngleRadius");
        doubleSpinBoxMaxAngleRadius->setGeometry(QRect(160, 160, 101, 22));
        doubleSpinBoxMaxAngleRadius->setMaximum(99999999.000000000000000);
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 190, 141, 21));
        doubleSpinBoxMaxUnstableZone = new QDoubleSpinBox(frame);
        doubleSpinBoxMaxUnstableZone->setObjectName("doubleSpinBoxMaxUnstableZone");
        doubleSpinBoxMaxUnstableZone->setGeometry(QRect(160, 190, 101, 22));
        doubleSpinBoxMaxUnstableZone->setMaximum(99999999.000000000000000);
        lineEditLibID = new QLineEdit(frame);
        lineEditLibID->setObjectName("lineEditLibID");
        lineEditLibID->setGeometry(QRect(50, 10, 61, 21));
        lineEditLibID->setReadOnly(true);
        lineEditLibName = new QLineEdit(frame);
        lineEditLibName->setObjectName("lineEditLibName");
        lineEditLibName->setGeometry(QRect(50, 30, 161, 21));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 41, 21));
        pushButtonSelectLib = new QPushButton(frame);
        pushButtonSelectLib->setObjectName("pushButtonSelectLib");
        pushButtonSelectLib->setGeometry(QRect(220, 30, 41, 23));
        checkBoxNegModeInContainer = new QCheckBox(EditCompositeDefDialog);
        checkBoxNegModeInContainer->setObjectName("checkBoxNegModeInContainer");
        checkBoxNegModeInContainer->setGeometry(QRect(480, 500, 481, 20));
        frameLibFolder = new QFrame(EditCompositeDefDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(0, 0, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);

        retranslateUi(EditCompositeDefDialog);

        QMetaObject::connectSlotsByName(EditCompositeDefDialog);
    } // setupUi

    void retranslateUi(QDialog *EditCompositeDefDialog)
    {
        EditCompositeDefDialog->setWindowTitle(QCoreApplication::translate("EditCompositeDefDialog", "Define composite", nullptr));
        pushButtonSaveNew->setText(QCoreApplication::translate("EditCompositeDefDialog", "Save new", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("EditCompositeDefDialog", "Update", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EditCompositeDefDialog", "Delete", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditCompositeDefDialog", "Close", nullptr));
        pushButtonSaveFile->setText(QCoreApplication::translate("EditCompositeDefDialog", "Save file", nullptr));
        pushButtonLoadFile->setText(QCoreApplication::translate("EditCompositeDefDialog", "Load file", nullptr));
        pushButtonAppendFile->setText(QCoreApplication::translate("EditCompositeDefDialog", "Append file", nullptr));
        label_4->setText(QCoreApplication::translate("EditCompositeDefDialog", "Composite Name", nullptr));
        ButtonPlus->setText(QCoreApplication::translate("EditCompositeDefDialog", "+", nullptr));
        ButtonMinus->setText(QCoreApplication::translate("EditCompositeDefDialog", "-", nullptr));
        radioButtonOr->setText(QCoreApplication::translate("EditCompositeDefDialog", "Or", nullptr));
        radioButtonAnd->setText(QCoreApplication::translate("EditCompositeDefDialog", "And", nullptr));
        radioButtonNotAnd->setText(QCoreApplication::translate("EditCompositeDefDialog", "NotAnd", nullptr));
        radioButtonNotOr->setText(QCoreApplication::translate("EditCompositeDefDialog", "NotOr", nullptr));
        LabelLayerType->setText(QCoreApplication::translate("EditCompositeDefDialog", "Layer Type Library", nullptr));
        LabelDot->setText(QCoreApplication::translate("EditCompositeDefDialog", "Bold Dot", nullptr));
        LabelNo->setText(QCoreApplication::translate("EditCompositeDefDialog", "1", nullptr));
        ButtonLayerType->setText(QCoreApplication::translate("EditCompositeDefDialog", "...", nullptr));
        checkBoxNegMode->setText(QCoreApplication::translate("EditCompositeDefDialog", "Neg", nullptr));
        pushButtonRemoveLine->setText(QCoreApplication::translate("EditCompositeDefDialog", "X", nullptr));
        toolButtonUpper->setText(QCoreApplication::translate("EditCompositeDefDialog", "...", nullptr));
        toolButtonUpper_2->setText(QCoreApplication::translate("EditCompositeDefDialog", "...", nullptr));
        label_6->setText(QCoreApplication::translate("EditCompositeDefDialog", "Max enlarge dot", nullptr));
        label_7->setText(QCoreApplication::translate("EditCompositeDefDialog", "Max shrinkage dot", nullptr));
        label_8->setText(QCoreApplication::translate("EditCompositeDefDialog", "Max shift dot", nullptr));
        label_9->setText(QCoreApplication::translate("EditCompositeDefDialog", "Max angle Radius", nullptr));
        label_10->setText(QCoreApplication::translate("EditCompositeDefDialog", "Max unstable outline area", nullptr));
        label_5->setText(QCoreApplication::translate("EditCompositeDefDialog", "Type", nullptr));
        pushButtonSelectLib->setText(QCoreApplication::translate("EditCompositeDefDialog", "...", nullptr));
        checkBoxNegModeInContainer->setText(QCoreApplication::translate("EditCompositeDefDialog", "Final output  : Negative reverse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditCompositeDefDialog: public Ui_EditCompositeDefDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCOMPOSITEDEFDIALOG_H
