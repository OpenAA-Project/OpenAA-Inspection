/********************************************************************************
** Form generated from reading UI file 'PropertyImageProcessorForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYIMAGEPROCESSORFORM_H
#define UI_PROPERTYIMAGEPROCESSORFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyImageProcessorFormClass
{
public:
    QFrame *frame;
    QToolButton *FilterMonoButton;
    QToolButton *ButtonOpposite;
    QToolButton *FilterAddButton;
    QToolButton *FilterSubButton;
    QToolButton *FilterMulButton;
    QToolButton *FilterCoefButton;
    QToolButton *ButtonFilterLineEmphasis;
    QToolButton *ButtonLaplace;
    QToolButton *ButtonGradiant;
    QToolButton *ButtonTransLog;
    QToolButton *ButtonDiverse;
    QToolButton *FilterBinarizeButton;
    QToolButton *FilterEnfatButton;
    QToolButton *FilterShrinkButton;
    QToolButton *FilterRelativeBinarizeButton;
    QToolButton *FilterAndButton;
    QToolButton *FilterOrButton;
    QToolButton *FilterXorButton;
    QToolButton *FilterNotButton;
    QToolButton *FilterThresholdButton;
    QToolButton *FilterAllocButton;
    QToolButton *LoadImageButton;
    QToolButton *DigitalFilterLineNotchButton;
    QToolButton *StatisticButton;
    QToolButton *FractalDimButton;
    QToolButton *LinearizeButton;
    QToolButton *ButtonRemoveNoise;
    QToolButton *MatchLearnButton;
    QToolButton *ButtonRemoveStandalone;
    QToolButton *ButtonDisorderRegular;
    QToolButton *ButtonErgod;
    QToolButton *ButtonRemoveSpot;
    QToolButton *ButtonConnectNearBy;
    QToolButton *ButtonMakeMaxPath;
    QToolButton *AverageBinarizeButton;
    QToolButton *FilterMedianButton;
    QToolButton *FilterMosaicButton;
    QToolButton *FilterLineEmphasizerButton;
    QToolButton *ButtonPickupWeb;
    QToolButton *ButtonConnectPartial;
    QFrame *frameScrollPanel;
    QTableWidget *tableWidgetItem;
    QListWidget *listWidgetFileName;
    QLabel *label;
    QListWidget *listWidgetProgram;
    QLabel *label_2;
    QPushButton *ButtonAddProgram;
    QPushButton *ButtonDelProgram;
    QPushButton *ButtonAddFile;
    QPushButton *ButtonDelFile;
    QPushButton *ButtonStartOne;
    QPushButton *pushButtonUpArrowFile;
    QPushButton *pushButtonDownArrowFile;
    QPushButton *ButtonExecuteAll;
    QPushButton *ButtonLoadDef;
    QPushButton *ButtonDelAllProgram;

    void setupUi(GUIFormBase *PropertyImageProcessorFormClass)
    {
        if (PropertyImageProcessorFormClass->objectName().isEmpty())
            PropertyImageProcessorFormClass->setObjectName("PropertyImageProcessorFormClass");
        PropertyImageProcessorFormClass->resize(951, 745);
        frame = new QFrame(PropertyImageProcessorFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 180, 331, 441));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        FilterMonoButton = new QToolButton(frame);
        FilterMonoButton->setObjectName("FilterMonoButton");
        FilterMonoButton->setGeometry(QRect(10, 10, 71, 31));
        FilterMonoButton->setCheckable(true);
        FilterMonoButton->setChecked(false);
        FilterMonoButton->setAutoExclusive(true);
        ButtonOpposite = new QToolButton(frame);
        ButtonOpposite->setObjectName("ButtonOpposite");
        ButtonOpposite->setGeometry(QRect(10, 40, 71, 31));
        ButtonOpposite->setCheckable(true);
        ButtonOpposite->setChecked(true);
        ButtonOpposite->setAutoExclusive(true);
        FilterAddButton = new QToolButton(frame);
        FilterAddButton->setObjectName("FilterAddButton");
        FilterAddButton->setGeometry(QRect(10, 70, 71, 31));
        FilterAddButton->setCheckable(true);
        FilterAddButton->setAutoExclusive(true);
        FilterSubButton = new QToolButton(frame);
        FilterSubButton->setObjectName("FilterSubButton");
        FilterSubButton->setGeometry(QRect(10, 100, 71, 31));
        FilterSubButton->setCheckable(true);
        FilterSubButton->setAutoExclusive(true);
        FilterMulButton = new QToolButton(frame);
        FilterMulButton->setObjectName("FilterMulButton");
        FilterMulButton->setGeometry(QRect(10, 130, 71, 31));
        FilterMulButton->setCheckable(true);
        FilterMulButton->setAutoExclusive(true);
        FilterCoefButton = new QToolButton(frame);
        FilterCoefButton->setObjectName("FilterCoefButton");
        FilterCoefButton->setGeometry(QRect(10, 160, 71, 31));
        FilterCoefButton->setCheckable(true);
        FilterCoefButton->setAutoExclusive(true);
        ButtonFilterLineEmphasis = new QToolButton(frame);
        ButtonFilterLineEmphasis->setObjectName("ButtonFilterLineEmphasis");
        ButtonFilterLineEmphasis->setGeometry(QRect(10, 190, 71, 31));
        ButtonFilterLineEmphasis->setCheckable(true);
        ButtonFilterLineEmphasis->setAutoExclusive(true);
        ButtonLaplace = new QToolButton(frame);
        ButtonLaplace->setObjectName("ButtonLaplace");
        ButtonLaplace->setGeometry(QRect(10, 220, 71, 31));
        ButtonLaplace->setCheckable(true);
        ButtonLaplace->setAutoExclusive(true);
        ButtonGradiant = new QToolButton(frame);
        ButtonGradiant->setObjectName("ButtonGradiant");
        ButtonGradiant->setGeometry(QRect(10, 250, 71, 31));
        ButtonGradiant->setCheckable(true);
        ButtonGradiant->setAutoExclusive(true);
        ButtonTransLog = new QToolButton(frame);
        ButtonTransLog->setObjectName("ButtonTransLog");
        ButtonTransLog->setGeometry(QRect(10, 280, 71, 31));
        ButtonTransLog->setCheckable(true);
        ButtonTransLog->setAutoExclusive(true);
        ButtonDiverse = new QToolButton(frame);
        ButtonDiverse->setObjectName("ButtonDiverse");
        ButtonDiverse->setGeometry(QRect(10, 310, 71, 31));
        ButtonDiverse->setCheckable(true);
        ButtonDiverse->setAutoExclusive(true);
        FilterBinarizeButton = new QToolButton(frame);
        FilterBinarizeButton->setObjectName("FilterBinarizeButton");
        FilterBinarizeButton->setGeometry(QRect(90, 10, 71, 31));
        FilterBinarizeButton->setCheckable(true);
        FilterBinarizeButton->setAutoExclusive(true);
        FilterEnfatButton = new QToolButton(frame);
        FilterEnfatButton->setObjectName("FilterEnfatButton");
        FilterEnfatButton->setGeometry(QRect(90, 40, 71, 31));
        FilterEnfatButton->setCheckable(true);
        FilterEnfatButton->setAutoExclusive(true);
        FilterShrinkButton = new QToolButton(frame);
        FilterShrinkButton->setObjectName("FilterShrinkButton");
        FilterShrinkButton->setGeometry(QRect(90, 70, 71, 31));
        FilterShrinkButton->setCheckable(true);
        FilterShrinkButton->setAutoExclusive(true);
        FilterRelativeBinarizeButton = new QToolButton(frame);
        FilterRelativeBinarizeButton->setObjectName("FilterRelativeBinarizeButton");
        FilterRelativeBinarizeButton->setGeometry(QRect(90, 100, 71, 31));
        FilterRelativeBinarizeButton->setCheckable(true);
        FilterRelativeBinarizeButton->setAutoExclusive(true);
        FilterAndButton = new QToolButton(frame);
        FilterAndButton->setObjectName("FilterAndButton");
        FilterAndButton->setGeometry(QRect(90, 220, 71, 31));
        FilterAndButton->setCheckable(true);
        FilterAndButton->setAutoExclusive(true);
        FilterOrButton = new QToolButton(frame);
        FilterOrButton->setObjectName("FilterOrButton");
        FilterOrButton->setGeometry(QRect(90, 250, 71, 31));
        FilterOrButton->setCheckable(true);
        FilterOrButton->setAutoExclusive(true);
        FilterXorButton = new QToolButton(frame);
        FilterXorButton->setObjectName("FilterXorButton");
        FilterXorButton->setGeometry(QRect(90, 280, 71, 31));
        FilterXorButton->setCheckable(true);
        FilterXorButton->setAutoExclusive(true);
        FilterNotButton = new QToolButton(frame);
        FilterNotButton->setObjectName("FilterNotButton");
        FilterNotButton->setGeometry(QRect(90, 310, 71, 31));
        FilterNotButton->setCheckable(true);
        FilterNotButton->setAutoExclusive(true);
        FilterThresholdButton = new QToolButton(frame);
        FilterThresholdButton->setObjectName("FilterThresholdButton");
        FilterThresholdButton->setGeometry(QRect(250, 10, 71, 31));
        FilterThresholdButton->setCheckable(true);
        FilterThresholdButton->setAutoExclusive(true);
        FilterAllocButton = new QToolButton(frame);
        FilterAllocButton->setObjectName("FilterAllocButton");
        FilterAllocButton->setGeometry(QRect(250, 40, 71, 31));
        FilterAllocButton->setCheckable(true);
        FilterAllocButton->setAutoExclusive(true);
        LoadImageButton = new QToolButton(frame);
        LoadImageButton->setObjectName("LoadImageButton");
        LoadImageButton->setGeometry(QRect(250, 100, 71, 31));
        LoadImageButton->setCheckable(true);
        LoadImageButton->setAutoExclusive(true);
        DigitalFilterLineNotchButton = new QToolButton(frame);
        DigitalFilterLineNotchButton->setObjectName("DigitalFilterLineNotchButton");
        DigitalFilterLineNotchButton->setGeometry(QRect(250, 160, 71, 31));
        DigitalFilterLineNotchButton->setCheckable(true);
        DigitalFilterLineNotchButton->setAutoExclusive(true);
        StatisticButton = new QToolButton(frame);
        StatisticButton->setObjectName("StatisticButton");
        StatisticButton->setGeometry(QRect(250, 220, 71, 31));
        StatisticButton->setCheckable(true);
        StatisticButton->setAutoExclusive(true);
        FractalDimButton = new QToolButton(frame);
        FractalDimButton->setObjectName("FractalDimButton");
        FractalDimButton->setGeometry(QRect(250, 190, 71, 31));
        FractalDimButton->setCheckable(true);
        FractalDimButton->setAutoExclusive(true);
        LinearizeButton = new QToolButton(frame);
        LinearizeButton->setObjectName("LinearizeButton");
        LinearizeButton->setGeometry(QRect(90, 130, 71, 31));
        LinearizeButton->setCheckable(true);
        LinearizeButton->setAutoExclusive(true);
        ButtonRemoveNoise = new QToolButton(frame);
        ButtonRemoveNoise->setObjectName("ButtonRemoveNoise");
        ButtonRemoveNoise->setGeometry(QRect(170, 220, 71, 31));
        ButtonRemoveNoise->setCheckable(true);
        ButtonRemoveNoise->setAutoExclusive(true);
        MatchLearnButton = new QToolButton(frame);
        MatchLearnButton->setObjectName("MatchLearnButton");
        MatchLearnButton->setGeometry(QRect(250, 280, 71, 31));
        MatchLearnButton->setCheckable(true);
        MatchLearnButton->setAutoExclusive(true);
        ButtonRemoveStandalone = new QToolButton(frame);
        ButtonRemoveStandalone->setObjectName("ButtonRemoveStandalone");
        ButtonRemoveStandalone->setGeometry(QRect(170, 250, 71, 31));
        ButtonRemoveStandalone->setCheckable(true);
        ButtonRemoveStandalone->setAutoExclusive(true);
        ButtonDisorderRegular = new QToolButton(frame);
        ButtonDisorderRegular->setObjectName("ButtonDisorderRegular");
        ButtonDisorderRegular->setGeometry(QRect(170, 40, 71, 31));
        ButtonDisorderRegular->setCheckable(true);
        ButtonDisorderRegular->setAutoExclusive(true);
        ButtonErgod = new QToolButton(frame);
        ButtonErgod->setObjectName("ButtonErgod");
        ButtonErgod->setGeometry(QRect(170, 70, 71, 31));
        ButtonErgod->setCheckable(true);
        ButtonErgod->setAutoExclusive(true);
        ButtonRemoveSpot = new QToolButton(frame);
        ButtonRemoveSpot->setObjectName("ButtonRemoveSpot");
        ButtonRemoveSpot->setGeometry(QRect(170, 10, 71, 31));
        ButtonRemoveSpot->setCheckable(true);
        ButtonRemoveSpot->setAutoExclusive(true);
        ButtonConnectNearBy = new QToolButton(frame);
        ButtonConnectNearBy->setObjectName("ButtonConnectNearBy");
        ButtonConnectNearBy->setGeometry(QRect(170, 280, 71, 31));
        ButtonConnectNearBy->setCheckable(true);
        ButtonConnectNearBy->setAutoExclusive(true);
        ButtonMakeMaxPath = new QToolButton(frame);
        ButtonMakeMaxPath->setObjectName("ButtonMakeMaxPath");
        ButtonMakeMaxPath->setGeometry(QRect(170, 310, 71, 31));
        ButtonMakeMaxPath->setCheckable(true);
        ButtonMakeMaxPath->setAutoExclusive(true);
        AverageBinarizeButton = new QToolButton(frame);
        AverageBinarizeButton->setObjectName("AverageBinarizeButton");
        AverageBinarizeButton->setGeometry(QRect(90, 160, 71, 31));
        AverageBinarizeButton->setCheckable(true);
        AverageBinarizeButton->setAutoExclusive(true);
        FilterMedianButton = new QToolButton(frame);
        FilterMedianButton->setObjectName("FilterMedianButton");
        FilterMedianButton->setGeometry(QRect(10, 340, 71, 31));
        FilterMedianButton->setCheckable(true);
        FilterMedianButton->setAutoExclusive(true);
        FilterMosaicButton = new QToolButton(frame);
        FilterMosaicButton->setObjectName("FilterMosaicButton");
        FilterMosaicButton->setGeometry(QRect(10, 370, 71, 31));
        FilterMosaicButton->setCheckable(true);
        FilterMosaicButton->setAutoExclusive(true);
        FilterLineEmphasizerButton = new QToolButton(frame);
        FilterLineEmphasizerButton->setObjectName("FilterLineEmphasizerButton");
        FilterLineEmphasizerButton->setGeometry(QRect(10, 400, 71, 31));
        FilterLineEmphasizerButton->setCheckable(true);
        FilterLineEmphasizerButton->setAutoExclusive(true);
        ButtonPickupWeb = new QToolButton(frame);
        ButtonPickupWeb->setObjectName("ButtonPickupWeb");
        ButtonPickupWeb->setGeometry(QRect(170, 350, 71, 31));
        ButtonPickupWeb->setCheckable(true);
        ButtonPickupWeb->setAutoExclusive(true);
        ButtonConnectPartial = new QToolButton(frame);
        ButtonConnectPartial->setObjectName("ButtonConnectPartial");
        ButtonConnectPartial->setGeometry(QRect(170, 380, 71, 31));
        ButtonConnectPartial->setCheckable(true);
        ButtonConnectPartial->setAutoExclusive(true);
        frameScrollPanel = new QFrame(PropertyImageProcessorFormClass);
        frameScrollPanel->setObjectName("frameScrollPanel");
        frameScrollPanel->setGeometry(QRect(350, 170, 591, 531));
        frameScrollPanel->setFrameShape(QFrame::StyledPanel);
        frameScrollPanel->setFrameShadow(QFrame::Sunken);
        tableWidgetItem = new QTableWidget(PropertyImageProcessorFormClass);
        if (tableWidgetItem->columnCount() < 2)
            tableWidgetItem->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItem->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItem->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetItem->setObjectName("tableWidgetItem");
        tableWidgetItem->setGeometry(QRect(10, 630, 331, 111));
        listWidgetFileName = new QListWidget(PropertyImageProcessorFormClass);
        listWidgetFileName->setObjectName("listWidgetFileName");
        listWidgetFileName->setGeometry(QRect(350, 30, 591, 71));
        listWidgetFileName->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(PropertyImageProcessorFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(350, 10, 591, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetProgram = new QListWidget(PropertyImageProcessorFormClass);
        listWidgetProgram->setObjectName("listWidgetProgram");
        listWidgetProgram->setGeometry(QRect(90, 30, 241, 101));
        label_2 = new QLabel(PropertyImageProcessorFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 10, 221, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonAddProgram = new QPushButton(PropertyImageProcessorFormClass);
        ButtonAddProgram->setObjectName("ButtonAddProgram");
        ButtonAddProgram->setGeometry(QRect(90, 130, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonAddProgram->setIcon(icon);
        ButtonDelProgram = new QPushButton(PropertyImageProcessorFormClass);
        ButtonDelProgram->setObjectName("ButtonDelProgram");
        ButtonDelProgram->setGeometry(QRect(170, 130, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonDelProgram->setIcon(icon1);
        ButtonAddFile = new QPushButton(PropertyImageProcessorFormClass);
        ButtonAddFile->setObjectName("ButtonAddFile");
        ButtonAddFile->setGeometry(QRect(610, 110, 101, 23));
        ButtonAddFile->setIcon(icon);
        ButtonDelFile = new QPushButton(PropertyImageProcessorFormClass);
        ButtonDelFile->setObjectName("ButtonDelFile");
        ButtonDelFile->setGeometry(QRect(860, 110, 75, 23));
        ButtonDelFile->setIcon(icon1);
        ButtonStartOne = new QPushButton(PropertyImageProcessorFormClass);
        ButtonStartOne->setObjectName("ButtonStartOne");
        ButtonStartOne->setGeometry(QRect(350, 140, 121, 23));
        pushButtonUpArrowFile = new QPushButton(PropertyImageProcessorFormClass);
        pushButtonUpArrowFile->setObjectName("pushButtonUpArrowFile");
        pushButtonUpArrowFile->setGeometry(QRect(730, 110, 35, 23));
        pushButtonDownArrowFile = new QPushButton(PropertyImageProcessorFormClass);
        pushButtonDownArrowFile->setObjectName("pushButtonDownArrowFile");
        pushButtonDownArrowFile->setGeometry(QRect(780, 110, 35, 23));
        ButtonExecuteAll = new QPushButton(PropertyImageProcessorFormClass);
        ButtonExecuteAll->setObjectName("ButtonExecuteAll");
        ButtonExecuteAll->setGeometry(QRect(480, 140, 121, 23));
        ButtonLoadDef = new QPushButton(PropertyImageProcessorFormClass);
        ButtonLoadDef->setObjectName("ButtonLoadDef");
        ButtonLoadDef->setGeometry(QRect(10, 30, 75, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLoadDef->setIcon(icon2);
        ButtonDelAllProgram = new QPushButton(PropertyImageProcessorFormClass);
        ButtonDelAllProgram->setObjectName("ButtonDelAllProgram");
        ButtonDelAllProgram->setGeometry(QRect(260, 130, 75, 23));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Trash.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonDelAllProgram->setIcon(icon3);

        retranslateUi(PropertyImageProcessorFormClass);

        QMetaObject::connectSlotsByName(PropertyImageProcessorFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyImageProcessorFormClass)
    {
        PropertyImageProcessorFormClass->setWindowTitle(QCoreApplication::translate("PropertyImageProcessorFormClass", "PropertyImageProcessorForm", nullptr));
        FilterMonoButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\343\203\242\343\203\216\343\202\257\343\203\255\345\214\226", nullptr));
        ButtonOpposite->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\346\230\216\346\232\227\345\217\215\350\273\242", nullptr));
        FilterAddButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\345\212\240\347\256\227", nullptr));
        FilterSubButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\346\270\233\347\256\227", nullptr));
        FilterMulButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\344\271\227\347\256\227", nullptr));
        FilterCoefButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\347\233\270\351\226\242", nullptr));
        ButtonFilterLineEmphasis->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\351\273\222\347\267\232\345\215\224\350\252\277", nullptr));
        ButtonLaplace->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\343\203\251\343\203\227\343\203\251\343\202\267\343\202\242\343\203\263", nullptr));
        ButtonGradiant->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\345\213\276\351\205\215", nullptr));
        ButtonTransLog->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\350\274\235\345\272\246\345\257\276\346\225\260", nullptr));
        ButtonDiverse->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\345\267\256\345\210\206", nullptr));
        FilterBinarizeButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\357\274\222\345\200\244\345\214\226", nullptr));
        FilterEnfatButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\350\206\250\345\274\265", nullptr));
        FilterShrinkButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\345\217\216\347\270\256", nullptr));
        FilterRelativeBinarizeButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\347\233\270\345\257\276\357\274\222\345\200\244\345\214\226", nullptr));
        FilterAndButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\357\274\241\357\274\256\357\274\244", nullptr));
        FilterOrButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\357\274\257\357\274\262", nullptr));
        FilterXorButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\357\274\270\357\274\257\357\274\262", nullptr));
        FilterNotButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\357\274\256\357\274\257\357\274\264", nullptr));
        FilterThresholdButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        FilterAllocButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\347\265\220\346\236\234\345\211\262\345\275\223", nullptr));
        LoadImageButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\347\224\273\345\203\217\343\203\255\343\203\274\343\203\211", nullptr));
        DigitalFilterLineNotchButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\345\221\250\346\234\237\347\267\232\351\231\244\345\216\273", nullptr));
        StatisticButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\351\225\267\343\201\225\347\265\261\350\250\210", nullptr));
        FractalDimButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\343\203\225\343\203\251\343\202\257\343\202\277\343\203\253\346\254\241\345\205\203", nullptr));
        LinearizeButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\347\264\260\347\267\232\345\214\226", nullptr));
        ButtonRemoveNoise->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\343\203\216\343\202\244\343\202\272\351\231\244\345\216\273", nullptr));
        MatchLearnButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\345\255\246\347\277\222\343\203\236\343\203\203\343\203\201", nullptr));
        ButtonRemoveStandalone->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\345\255\244\347\253\213\347\202\271\351\231\244\345\216\273", nullptr));
        ButtonDisorderRegular->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\346\255\243\350\246\217\345\210\206\345\270\203\344\271\226\351\233\242", nullptr));
        ButtonErgod->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\343\202\250\343\203\253\343\202\264\343\203\274\343\203\211\346\200\247", nullptr));
        ButtonRemoveSpot->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\350\274\235\347\202\271\351\231\244\345\216\273", nullptr));
        ButtonConnectNearBy->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\350\277\221\345\202\215\346\216\245\347\266\232", nullptr));
        ButtonMakeMaxPath->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\346\234\200\351\225\267\343\203\221\343\202\271", nullptr));
        AverageBinarizeButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\345\271\263\345\235\207\357\274\222\345\200\244\345\214\226", nullptr));
        FilterMedianButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\344\270\255\345\244\256\345\271\263\345\235\207\345\214\226", nullptr));
        FilterMosaicButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\343\203\242\343\202\266\343\202\244\343\202\257\345\214\226", nullptr));
        FilterLineEmphasizerButton->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\347\267\232\345\274\267\350\252\277", nullptr));
        ButtonPickupWeb->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\347\266\262\347\233\256\346\244\234\345\207\272", nullptr));
        ButtonConnectPartial->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\351\200\224\345\210\207\346\216\245\347\266\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItem->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItem->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Value", nullptr));
        label->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\347\224\273\345\203\217\343\203\225\343\202\241\343\202\244\343\203\253", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\343\203\227\343\203\255\343\202\260\343\203\251\343\203\240\343\203\207\343\203\274\343\202\277", nullptr));
        ButtonAddProgram->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Add", nullptr));
        ButtonDelProgram->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Del", nullptr));
        ButtonAddFile->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Add file", nullptr));
        ButtonDelFile->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Del", nullptr));
        ButtonStartOne->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Execute one", nullptr));
        pushButtonUpArrowFile->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\342\206\221", nullptr));
        pushButtonDownArrowFile->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "\342\206\223", nullptr));
        ButtonExecuteAll->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Execute all", nullptr));
        ButtonLoadDef->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Load Def", nullptr));
        ButtonDelAllProgram->setText(QCoreApplication::translate("PropertyImageProcessorFormClass", "Delete all", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyImageProcessorFormClass: public Ui_PropertyImageProcessorFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYIMAGEPROCESSORFORM_H
