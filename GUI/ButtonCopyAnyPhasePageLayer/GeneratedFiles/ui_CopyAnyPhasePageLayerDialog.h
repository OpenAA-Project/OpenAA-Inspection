/********************************************************************************
** Form generated from reading UI file 'CopyAnyPhasePageLayerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYANYPHASEPAGELAYERDIALOG_H
#define UI_COPYANYPHASEPAGELAYERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CopyAnyPhasePageLayerDialog
{
public:
    QFrame *frame;
    QListWidget *listWidgetSrcPhase;
    QListWidget *listWidgetSrcPage;
    QListWidget *listWidgetSrcLayer;
    QLabel *label;
    QCheckBox *checkBoxMasterImage;
    QCheckBox *checkBoxAlgorithm;
    QCheckBox *checkBoxTargetImage;
    QFrame *frame_2;
    QListWidget *listWidgetDstPhase;
    QListWidget *listWidgetDstPage;
    QListWidget *listWidgetDstLayer;
    QLabel *label_2;
    QCheckBox *checkBoxDestTargetImage;
    QCheckBox *checkBoxDestMasterImage;
    QPushButton *pushButtonExecuteCopy;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonTest;

    void setupUi(QDialog *CopyAnyPhasePageLayerDialog)
    {
        if (CopyAnyPhasePageLayerDialog->objectName().isEmpty())
            CopyAnyPhasePageLayerDialog->setObjectName("CopyAnyPhasePageLayerDialog");
        CopyAnyPhasePageLayerDialog->resize(650, 317);
        frame = new QFrame(CopyAnyPhasePageLayerDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 281, 281));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        listWidgetSrcPhase = new QListWidget(frame);
        listWidgetSrcPhase->setObjectName("listWidgetSrcPhase");
        listWidgetSrcPhase->setGeometry(QRect(10, 30, 71, 141));
        listWidgetSrcPhase->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetSrcPage = new QListWidget(frame);
        listWidgetSrcPage->setObjectName("listWidgetSrcPage");
        listWidgetSrcPage->setGeometry(QRect(90, 30, 71, 141));
        listWidgetSrcPage->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetSrcLayer = new QListWidget(frame);
        listWidgetSrcLayer->setObjectName("listWidgetSrcLayer");
        listWidgetSrcLayer->setGeometry(QRect(170, 30, 101, 141));
        listWidgetSrcLayer->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 281, 20));
        checkBoxMasterImage = new QCheckBox(frame);
        checkBoxMasterImage->setObjectName("checkBoxMasterImage");
        checkBoxMasterImage->setGeometry(QRect(20, 190, 211, 22));
        checkBoxMasterImage->setChecked(true);
        checkBoxAlgorithm = new QCheckBox(frame);
        checkBoxAlgorithm->setObjectName("checkBoxAlgorithm");
        checkBoxAlgorithm->setGeometry(QRect(20, 250, 211, 22));
        checkBoxAlgorithm->setChecked(true);
        checkBoxTargetImage = new QCheckBox(frame);
        checkBoxTargetImage->setObjectName("checkBoxTargetImage");
        checkBoxTargetImage->setGeometry(QRect(20, 220, 221, 22));
        checkBoxTargetImage->setChecked(true);
        frame_2 = new QFrame(CopyAnyPhasePageLayerDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(360, 10, 281, 251));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        listWidgetDstPhase = new QListWidget(frame_2);
        listWidgetDstPhase->setObjectName("listWidgetDstPhase");
        listWidgetDstPhase->setGeometry(QRect(10, 30, 71, 141));
        listWidgetDstPhase->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetDstPage = new QListWidget(frame_2);
        listWidgetDstPage->setObjectName("listWidgetDstPage");
        listWidgetDstPage->setGeometry(QRect(90, 30, 71, 141));
        listWidgetDstPage->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetDstLayer = new QListWidget(frame_2);
        listWidgetDstLayer->setObjectName("listWidgetDstLayer");
        listWidgetDstLayer->setGeometry(QRect(170, 30, 101, 141));
        listWidgetDstLayer->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 281, 20));
        checkBoxDestTargetImage = new QCheckBox(frame_2);
        checkBoxDestTargetImage->setObjectName("checkBoxDestTargetImage");
        checkBoxDestTargetImage->setGeometry(QRect(20, 220, 221, 22));
        checkBoxDestTargetImage->setChecked(true);
        checkBoxDestMasterImage = new QCheckBox(frame_2);
        checkBoxDestMasterImage->setObjectName("checkBoxDestMasterImage");
        checkBoxDestMasterImage->setGeometry(QRect(20, 190, 211, 22));
        checkBoxDestMasterImage->setChecked(true);
        pushButtonExecuteCopy = new QPushButton(CopyAnyPhasePageLayerDialog);
        pushButtonExecuteCopy->setObjectName("pushButtonExecuteCopy");
        pushButtonExecuteCopy->setGeometry(QRect(300, 100, 51, 51));
        pushButtonClose = new QPushButton(CopyAnyPhasePageLayerDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(470, 270, 112, 34));
        pushButtonTest = new QPushButton(CopyAnyPhasePageLayerDialog);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(770, 400, 21, 20));

        retranslateUi(CopyAnyPhasePageLayerDialog);

        QMetaObject::connectSlotsByName(CopyAnyPhasePageLayerDialog);
    } // setupUi

    void retranslateUi(QDialog *CopyAnyPhasePageLayerDialog)
    {
        CopyAnyPhasePageLayerDialog->setWindowTitle(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "Copy image", nullptr));
        label->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "Source", nullptr));
        checkBoxMasterImage->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "Master Image", nullptr));
        checkBoxAlgorithm->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "Algorithm data", nullptr));
        checkBoxTargetImage->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "Target Image", nullptr));
        label_2->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "Destination", nullptr));
        checkBoxDestTargetImage->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "Target Image", nullptr));
        checkBoxDestMasterImage->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "Master Image", nullptr));
        pushButtonExecuteCopy->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", ">>", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "Close", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("CopyAnyPhasePageLayerDialog", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CopyAnyPhasePageLayerDialog: public Ui_CopyAnyPhasePageLayerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYANYPHASEPAGELAYERDIALOG_H
