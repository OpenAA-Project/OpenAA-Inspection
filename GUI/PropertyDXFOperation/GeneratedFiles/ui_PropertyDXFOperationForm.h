/********************************************************************************
** Form generated from reading UI file 'PropertyDXFOperationForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYDXFOPERATIONFORM_H
#define UI_PROPERTYDXFOPERATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyDXFOperationForm
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame;
    QLabel *label;
    QListWidget *listWidgetDXFFileName;
    QPushButton *pushButtonRegisterFileName;
    QPushButton *pushButtonRemoveFileName;
    QPushButton *pushButtonLoadDXF;
    QFrame *frame_2;
    QLabel *label_2;
    QFrame *frame_3;
    QLabel *label_3;
    QToolButton *toolButtonMirrorX;
    QToolButton *toolButtonMoveDialog;
    QToolButton *toolButtonShearDialog;
    QToolButton *toolButtonExpandDialog;
    QToolButton *toolButtonRotationDialog;
    QToolButton *toolButtonMirrorY;
    QToolButton *toolButtonCenterize;
    QFrame *frame_4;
    QLabel *label_4;
    QToolButton *toolButtonMove;
    QToolButton *toolButtonXShear;
    QToolButton *toolButtonYShear;
    QToolButton *toolButtonExpand;
    QToolButton *toolButtonRotate;
    QToolButton *toolButtonDrawInside;
    QPushButton *pushButtonSaveTransform;
    QPushButton *pushButtonLoadTransform;
    QFrame *frame_8;
    QTableWidget *tableWidgetLayerInfo;
    QPushButton *pushButtonAllocateColor;
    QFrame *frame_5;
    QLabel *label_5;
    QToolButton *toolButtonAutoMatching;
    QToolButton *toolButtonFatLine;
    QDoubleSpinBox *doubleSpinBoxLineWidth;
    QToolButton *toolButtonShowFilledArea;
    QToolButton *toolButtonMakeEffectiveMask;
    QToolButton *toolButtonSendEffectiveMask;
    QSpinBox *spinBoxShrinkDotForMask;
    QWidget *tab_2;
    QFrame *frame_7;
    QLabel *label_7;
    QFrame *frame_6;
    QLabel *label_6;
    QToolButton *toolButtonGenerateMask;
    QToolButton *toolButtonLibraryMask;
    QTableWidget *tableWidgetMaskList;
    QToolButton *toolButtonLibraryInspection;
    QToolButton *toolButtonGenerateInspection;
    QTableWidget *tableWidgetInspectionList;
    QToolButton *toolButtonGenerateMaskFillArea;

    void setupUi(GUIFormBase *PropertyDXFOperationForm)
    {
        if (PropertyDXFOperationForm->objectName().isEmpty())
            PropertyDXFOperationForm->setObjectName("PropertyDXFOperationForm");
        PropertyDXFOperationForm->resize(400, 900);
        tabWidget = new QTabWidget(PropertyDXFOperationForm);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 401, 891));
        tab = new QWidget();
        tab->setObjectName("tab");
        frame = new QFrame(tab);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 181));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 381, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        listWidgetDXFFileName = new QListWidget(frame);
        listWidgetDXFFileName->setObjectName("listWidgetDXFFileName");
        listWidgetDXFFileName->setGeometry(QRect(10, 26, 361, 111));
        listWidgetDXFFileName->setSelectionMode(QAbstractItemView::SingleSelection);
        listWidgetDXFFileName->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonRegisterFileName = new QPushButton(frame);
        pushButtonRegisterFileName->setObjectName("pushButtonRegisterFileName");
        pushButtonRegisterFileName->setGeometry(QRect(10, 140, 91, 34));
        pushButtonRemoveFileName = new QPushButton(frame);
        pushButtonRemoveFileName->setObjectName("pushButtonRemoveFileName");
        pushButtonRemoveFileName->setGeometry(QRect(110, 140, 91, 34));
        pushButtonLoadDXF = new QPushButton(frame);
        pushButtonLoadDXF->setObjectName("pushButtonLoadDXF");
        pushButtonLoadDXF->setGeometry(QRect(240, 140, 131, 34));
        frame_2 = new QFrame(tab);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 410, 381, 251));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 381, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 30, 181, 161));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 181, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        toolButtonMirrorX = new QToolButton(frame_3);
        toolButtonMirrorX->setObjectName("toolButtonMirrorX");
        toolButtonMirrorX->setGeometry(QRect(92, 60, 80, 31));
        toolButtonMoveDialog = new QToolButton(frame_3);
        toolButtonMoveDialog->setObjectName("toolButtonMoveDialog");
        toolButtonMoveDialog->setGeometry(QRect(10, 30, 80, 31));
        toolButtonShearDialog = new QToolButton(frame_3);
        toolButtonShearDialog->setObjectName("toolButtonShearDialog");
        toolButtonShearDialog->setGeometry(QRect(92, 30, 80, 31));
        toolButtonExpandDialog = new QToolButton(frame_3);
        toolButtonExpandDialog->setObjectName("toolButtonExpandDialog");
        toolButtonExpandDialog->setGeometry(QRect(10, 60, 80, 31));
        toolButtonRotationDialog = new QToolButton(frame_3);
        toolButtonRotationDialog->setObjectName("toolButtonRotationDialog");
        toolButtonRotationDialog->setGeometry(QRect(10, 90, 80, 31));
        toolButtonMirrorY = new QToolButton(frame_3);
        toolButtonMirrorY->setObjectName("toolButtonMirrorY");
        toolButtonMirrorY->setGeometry(QRect(92, 90, 80, 31));
        toolButtonCenterize = new QToolButton(frame_3);
        toolButtonCenterize->setObjectName("toolButtonCenterize");
        toolButtonCenterize->setGeometry(QRect(92, 120, 80, 31));
        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(190, 30, 181, 161));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        toolButtonMove = new QToolButton(frame_4);
        toolButtonMove->setObjectName("toolButtonMove");
        toolButtonMove->setGeometry(QRect(10, 30, 80, 31));
        toolButtonMove->setCheckable(true);
        toolButtonMove->setAutoExclusive(true);
        toolButtonXShear = new QToolButton(frame_4);
        toolButtonXShear->setObjectName("toolButtonXShear");
        toolButtonXShear->setGeometry(QRect(92, 30, 80, 31));
        toolButtonXShear->setCheckable(true);
        toolButtonXShear->setAutoExclusive(true);
        toolButtonYShear = new QToolButton(frame_4);
        toolButtonYShear->setObjectName("toolButtonYShear");
        toolButtonYShear->setGeometry(QRect(92, 60, 80, 31));
        toolButtonYShear->setCheckable(true);
        toolButtonYShear->setAutoExclusive(true);
        toolButtonExpand = new QToolButton(frame_4);
        toolButtonExpand->setObjectName("toolButtonExpand");
        toolButtonExpand->setGeometry(QRect(10, 60, 80, 31));
        toolButtonExpand->setCheckable(true);
        toolButtonExpand->setAutoExclusive(true);
        toolButtonRotate = new QToolButton(frame_4);
        toolButtonRotate->setObjectName("toolButtonRotate");
        toolButtonRotate->setGeometry(QRect(10, 90, 80, 31));
        toolButtonRotate->setCheckable(true);
        toolButtonRotate->setAutoExclusive(true);
        toolButtonDrawInside = new QToolButton(frame_4);
        toolButtonDrawInside->setObjectName("toolButtonDrawInside");
        toolButtonDrawInside->setGeometry(QRect(92, 90, 80, 31));
        toolButtonDrawInside->setCheckable(true);
        toolButtonDrawInside->setAutoExclusive(true);
        pushButtonSaveTransform = new QPushButton(frame_2);
        pushButtonSaveTransform->setObjectName("pushButtonSaveTransform");
        pushButtonSaveTransform->setGeometry(QRect(70, 200, 111, 41));
        pushButtonSaveTransform->setCheckable(true);
        pushButtonLoadTransform = new QPushButton(frame_2);
        pushButtonLoadTransform->setObjectName("pushButtonLoadTransform");
        pushButtonLoadTransform->setGeometry(QRect(190, 200, 111, 41));
        pushButtonLoadTransform->setCheckable(true);
        frame_8 = new QFrame(tab);
        frame_8->setObjectName("frame_8");
        frame_8->setGeometry(QRect(10, 200, 381, 201));
        frame_8->setFrameShape(QFrame::Panel);
        frame_8->setFrameShadow(QFrame::Sunken);
        tableWidgetLayerInfo = new QTableWidget(frame_8);
        if (tableWidgetLayerInfo->columnCount() < 3)
            tableWidgetLayerInfo->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLayerInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLayerInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLayerInfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetLayerInfo->setObjectName("tableWidgetLayerInfo");
        tableWidgetLayerInfo->setGeometry(QRect(10, 10, 361, 141));
        tableWidgetLayerInfo->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetLayerInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAllocateColor = new QPushButton(frame_8);
        pushButtonAllocateColor->setObjectName("pushButtonAllocateColor");
        pushButtonAllocateColor->setGeometry(QRect(160, 160, 211, 34));
        frame_5 = new QFrame(tab);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 670, 381, 191));
        frame_5->setFrameShape(QFrame::Panel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_5);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 381, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        toolButtonAutoMatching = new QToolButton(frame_5);
        toolButtonAutoMatching->setObjectName("toolButtonAutoMatching");
        toolButtonAutoMatching->setGeometry(QRect(10, 24, 261, 31));
        toolButtonFatLine = new QToolButton(frame_5);
        toolButtonFatLine->setObjectName("toolButtonFatLine");
        toolButtonFatLine->setGeometry(QRect(10, 54, 261, 31));
        doubleSpinBoxLineWidth = new QDoubleSpinBox(frame_5);
        doubleSpinBoxLineWidth->setObjectName("doubleSpinBoxLineWidth");
        doubleSpinBoxLineWidth->setGeometry(QRect(280, 54, 91, 31));
        doubleSpinBoxLineWidth->setMaximum(99999999.000000000000000);
        toolButtonShowFilledArea = new QToolButton(frame_5);
        toolButtonShowFilledArea->setObjectName("toolButtonShowFilledArea");
        toolButtonShowFilledArea->setGeometry(QRect(10, 86, 261, 31));
        toolButtonShowFilledArea->setCheckable(true);
        toolButtonMakeEffectiveMask = new QToolButton(frame_5);
        toolButtonMakeEffectiveMask->setObjectName("toolButtonMakeEffectiveMask");
        toolButtonMakeEffectiveMask->setGeometry(QRect(10, 120, 261, 31));
        toolButtonMakeEffectiveMask->setCheckable(false);
        toolButtonSendEffectiveMask = new QToolButton(frame_5);
        toolButtonSendEffectiveMask->setObjectName("toolButtonSendEffectiveMask");
        toolButtonSendEffectiveMask->setGeometry(QRect(10, 150, 261, 31));
        toolButtonSendEffectiveMask->setCheckable(false);
        spinBoxShrinkDotForMask = new QSpinBox(frame_5);
        spinBoxShrinkDotForMask->setObjectName("spinBoxShrinkDotForMask");
        spinBoxShrinkDotForMask->setGeometry(QRect(280, 120, 91, 31));
        spinBoxShrinkDotForMask->setMaximum(100);
        spinBoxShrinkDotForMask->setValue(10);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        frame_7 = new QFrame(tab_2);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(10, 640, 381, 141));
        frame_7->setFrameShape(QFrame::Panel);
        frame_7->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_7);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 381, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        frame_6 = new QFrame(tab_2);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 10, 381, 611));
        frame_6->setFrameShape(QFrame::Panel);
        frame_6->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame_6);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 381, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        toolButtonGenerateMask = new QToolButton(frame_6);
        toolButtonGenerateMask->setObjectName("toolButtonGenerateMask");
        toolButtonGenerateMask->setGeometry(QRect(10, 30, 181, 31));
        toolButtonLibraryMask = new QToolButton(frame_6);
        toolButtonLibraryMask->setObjectName("toolButtonLibraryMask");
        toolButtonLibraryMask->setGeometry(QRect(200, 30, 161, 31));
        tableWidgetMaskList = new QTableWidget(frame_6);
        if (tableWidgetMaskList->columnCount() < 2)
            tableWidgetMaskList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMaskList->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetMaskList->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetMaskList->setObjectName("tableWidgetMaskList");
        tableWidgetMaskList->setGeometry(QRect(10, 110, 361, 111));
        toolButtonLibraryInspection = new QToolButton(frame_6);
        toolButtonLibraryInspection->setObjectName("toolButtonLibraryInspection");
        toolButtonLibraryInspection->setGeometry(QRect(200, 410, 171, 31));
        toolButtonGenerateInspection = new QToolButton(frame_6);
        toolButtonGenerateInspection->setObjectName("toolButtonGenerateInspection");
        toolButtonGenerateInspection->setGeometry(QRect(10, 410, 181, 31));
        tableWidgetInspectionList = new QTableWidget(frame_6);
        if (tableWidgetInspectionList->columnCount() < 3)
            tableWidgetInspectionList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetInspectionList->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetInspectionList->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetInspectionList->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        tableWidgetInspectionList->setObjectName("tableWidgetInspectionList");
        tableWidgetInspectionList->setGeometry(QRect(10, 450, 361, 151));
        toolButtonGenerateMaskFillArea = new QToolButton(frame_6);
        toolButtonGenerateMaskFillArea->setObjectName("toolButtonGenerateMaskFillArea");
        toolButtonGenerateMaskFillArea->setGeometry(QRect(10, 70, 211, 31));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(PropertyDXFOperationForm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PropertyDXFOperationForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyDXFOperationForm)
    {
        PropertyDXFOperationForm->setWindowTitle(QCoreApplication::translate("PropertyDXFOperationForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\343\203\225\343\202\241\343\202\244\343\203\253\350\252\255\343\201\277\350\276\274\343\201\277", nullptr));
        pushButtonRegisterFileName->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\347\231\273\351\214\262", nullptr));
        pushButtonRemoveFileName->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\211\212\351\231\244", nullptr));
        pushButtonLoadDXF->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\350\252\255\343\201\277\350\276\274\343\201\277", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\244\211\345\275\242", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\343\203\221\343\203\251\343\203\241\343\203\274\343\202\277\346\223\215\344\275\234", nullptr));
        toolButtonMirrorX->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\343\203\237\343\203\251\343\203\274X", nullptr));
        toolButtonMoveDialog->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\347\247\273\345\213\225", nullptr));
        toolButtonShearDialog->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\343\201\233\343\202\223\346\226\255", nullptr));
        toolButtonExpandDialog->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\346\213\241\345\244\247", nullptr));
        toolButtonRotationDialog->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\233\236\350\273\242", nullptr));
        toolButtonMirrorY->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\343\203\237\343\203\251\343\203\274Y", nullptr));
        toolButtonCenterize->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\344\270\255\345\244\256\350\241\250\347\244\272", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\343\203\236\343\202\246\343\202\271\346\223\215\344\275\234", nullptr));
        toolButtonMove->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\347\247\273\345\213\225", nullptr));
        toolButtonXShear->setText(QCoreApplication::translate("PropertyDXFOperationForm", "X\343\201\233\343\202\223\346\226\255", nullptr));
        toolButtonYShear->setText(QCoreApplication::translate("PropertyDXFOperationForm", "Y\343\201\233\343\202\223\346\226\255", nullptr));
        toolButtonExpand->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\346\213\241\345\244\247", nullptr));
        toolButtonRotate->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\233\236\350\273\242", nullptr));
        toolButtonDrawInside->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\206\205\351\203\250\345\241\227", nullptr));
        pushButtonSaveTransform->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\244\211\345\275\242\344\275\234\347\224\250\343\201\256\344\277\235\345\255\230", nullptr));
        pushButtonLoadTransform->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\244\211\345\275\242\344\275\234\347\224\250\343\201\256\350\252\255\350\276\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLayerInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyDXFOperationForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLayerInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\350\211\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLayerInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\347\267\232\347\250\256", nullptr));
        pushButtonAllocateColor->setText(QCoreApplication::translate("PropertyDXFOperationForm", "Allocate Libraty in color", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\346\223\215\344\275\234", nullptr));
        toolButtonAutoMatching->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\350\207\252\345\213\225\343\203\236\343\203\203\343\203\201\343\203\263\343\202\260", nullptr));
        toolButtonFatLine->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\351\201\270\346\212\236\343\201\227\343\201\237DXF\343\201\256\347\267\232\343\202\222\345\244\252\343\201\217\343\201\231\343\202\213", nullptr));
        toolButtonShowFilledArea->setText(QCoreApplication::translate("PropertyDXFOperationForm", "FillArea\343\201\256\350\241\250\347\244\272", nullptr));
        toolButtonMakeEffectiveMask->setText(QCoreApplication::translate("PropertyDXFOperationForm", "CAD\351\226\211\351\240\230\345\237\237", nullptr));
        toolButtonSendEffectiveMask->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\351\226\211\351\240\230\345\237\237\343\202\222\346\234\211\345\212\271\343\203\236\343\202\271\343\202\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PropertyDXFOperationForm", "\346\223\215\344\275\234", nullptr));
        label_7->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\346\203\205\345\240\261", nullptr));
        label_6->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\347\224\237\346\210\220", nullptr));
        toolButtonGenerateMask->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\256\237\350\241\214\357\274\232\345\206\205\351\203\250\343\201\256\343\203\236\343\202\271\343\202\257\345\214\226", nullptr));
        toolButtonLibraryMask->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\343\203\236\343\202\271\343\202\257\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMaskList->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyDXFOperationForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetMaskList->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        toolButtonLibraryInspection->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\346\244\234\346\237\273\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        toolButtonGenerateInspection->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\256\237\350\241\214\357\274\232\346\244\234\346\237\273\351\240\230\345\237\237\347\224\237\346\210\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetInspectionList->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyDXFOperationForm", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetInspectionList->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyDXFOperationForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetInspectionList->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        toolButtonGenerateMaskFillArea->setText(QCoreApplication::translate("PropertyDXFOperationForm", "\345\256\237\350\241\214\357\274\232\345\205\205\345\241\253\351\240\230\345\237\237\343\203\236\343\202\271\343\202\257\345\214\226", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PropertyDXFOperationForm", "\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyDXFOperationForm: public Ui_PropertyDXFOperationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYDXFOPERATIONFORM_H
