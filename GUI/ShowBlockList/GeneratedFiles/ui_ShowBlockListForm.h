/********************************************************************************
** Form generated from reading UI file 'ShowBlockListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWBLOCKLISTFORM_H
#define UI_SHOWBLOCKLISTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowBlockListForm
{
public:
    QTableWidget *tableWidgetLib;
    QStackedWidget *stackedWidgetMode;
    QWidget *DetailOperation;
    QListWidget *listWidgetValueType;
    QStackedWidget *stackedWidget;
    QWidget *BroadDark;
    QListWidget *listWidgetBroadDark;
    QWidget *BroadLight;
    QListWidget *listWidgetBroadLight;
    QWidget *NarrowDark;
    QListWidget *listWidgetNarrowDark;
    QWidget *NarrowLight;
    QListWidget *listWidgetNarrowLight;
    QWidget *BrightAdjustment;
    QListWidget *listWidgetBrightAdjustment;
    QWidget *Attribute;
    QListWidget *listWidgetAttribute;
    QWidget *Search;
    QListWidget *listWidgetSearch;
    QTableWidget *tableWidgetValue;
    QPushButton *pushButtonSaveCSV;
    QWidget *EasyOperation;
    QLabel *label;
    QSlider *horizontalSliderBrightnessN;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelBrightnessN;
    QLabel *labelSIzeN;
    QSlider *horizontalSizeN;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *labelBrightnessB;
    QLabel *label_8;
    QLabel *label_4;
    QLabel *label_5;
    QSlider *horizontalSizeB;
    QLabel *labelSIzeB;
    QLabel *label_9;
    QLabel *label_10;
    QSlider *horizontalSliderBrightnessB;
    QLabel *label_11;
    QLabel *label_12;
    QSlider *horizontalSliderSearch;
    QLabel *labelSearch;
    QPushButton *pushButtonSetEasyOperation;

    void setupUi(GUIFormBase *ShowBlockListForm)
    {
        if (ShowBlockListForm->objectName().isEmpty())
            ShowBlockListForm->setObjectName("ShowBlockListForm");
        ShowBlockListForm->resize(542, 185);
        tableWidgetLib = new QTableWidget(ShowBlockListForm);
        if (tableWidgetLib->columnCount() < 3)
            tableWidgetLib->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLib->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLib->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLib->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetLib->setObjectName("tableWidgetLib");
        tableWidgetLib->setGeometry(QRect(1, 0, 221, 186));
        tableWidgetLib->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLib->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidgetMode = new QStackedWidget(ShowBlockListForm);
        stackedWidgetMode->setObjectName("stackedWidgetMode");
        stackedWidgetMode->setGeometry(QRect(220, 0, 321, 186));
        DetailOperation = new QWidget();
        DetailOperation->setObjectName("DetailOperation");
        listWidgetValueType = new QListWidget(DetailOperation);
        new QListWidgetItem(listWidgetValueType);
        new QListWidgetItem(listWidgetValueType);
        new QListWidgetItem(listWidgetValueType);
        new QListWidgetItem(listWidgetValueType);
        new QListWidgetItem(listWidgetValueType);
        new QListWidgetItem(listWidgetValueType);
        new QListWidgetItem(listWidgetValueType);
        listWidgetValueType->setObjectName("listWidgetValueType");
        listWidgetValueType->setGeometry(QRect(0, 0, 141, 261));
        stackedWidget = new QStackedWidget(DetailOperation);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(150, 0, 181, 271));
        stackedWidget->setFrameShape(QFrame::Panel);
        stackedWidget->setFrameShadow(QFrame::Sunken);
        BroadDark = new QWidget();
        BroadDark->setObjectName("BroadDark");
        listWidgetBroadDark = new QListWidget(BroadDark);
        new QListWidgetItem(listWidgetBroadDark);
        new QListWidgetItem(listWidgetBroadDark);
        new QListWidgetItem(listWidgetBroadDark);
        new QListWidgetItem(listWidgetBroadDark);
        new QListWidgetItem(listWidgetBroadDark);
        new QListWidgetItem(listWidgetBroadDark);
        listWidgetBroadDark->setObjectName("listWidgetBroadDark");
        listWidgetBroadDark->setGeometry(QRect(0, 0, 171, 321));
        stackedWidget->addWidget(BroadDark);
        BroadLight = new QWidget();
        BroadLight->setObjectName("BroadLight");
        listWidgetBroadLight = new QListWidget(BroadLight);
        new QListWidgetItem(listWidgetBroadLight);
        new QListWidgetItem(listWidgetBroadLight);
        new QListWidgetItem(listWidgetBroadLight);
        new QListWidgetItem(listWidgetBroadLight);
        new QListWidgetItem(listWidgetBroadLight);
        new QListWidgetItem(listWidgetBroadLight);
        listWidgetBroadLight->setObjectName("listWidgetBroadLight");
        listWidgetBroadLight->setGeometry(QRect(0, 0, 171, 261));
        stackedWidget->addWidget(BroadLight);
        NarrowDark = new QWidget();
        NarrowDark->setObjectName("NarrowDark");
        listWidgetNarrowDark = new QListWidget(NarrowDark);
        new QListWidgetItem(listWidgetNarrowDark);
        new QListWidgetItem(listWidgetNarrowDark);
        new QListWidgetItem(listWidgetNarrowDark);
        new QListWidgetItem(listWidgetNarrowDark);
        new QListWidgetItem(listWidgetNarrowDark);
        new QListWidgetItem(listWidgetNarrowDark);
        listWidgetNarrowDark->setObjectName("listWidgetNarrowDark");
        listWidgetNarrowDark->setGeometry(QRect(0, 0, 171, 321));
        stackedWidget->addWidget(NarrowDark);
        NarrowLight = new QWidget();
        NarrowLight->setObjectName("NarrowLight");
        listWidgetNarrowLight = new QListWidget(NarrowLight);
        new QListWidgetItem(listWidgetNarrowLight);
        new QListWidgetItem(listWidgetNarrowLight);
        new QListWidgetItem(listWidgetNarrowLight);
        new QListWidgetItem(listWidgetNarrowLight);
        new QListWidgetItem(listWidgetNarrowLight);
        new QListWidgetItem(listWidgetNarrowLight);
        listWidgetNarrowLight->setObjectName("listWidgetNarrowLight");
        listWidgetNarrowLight->setGeometry(QRect(0, 0, 171, 321));
        stackedWidget->addWidget(NarrowLight);
        BrightAdjustment = new QWidget();
        BrightAdjustment->setObjectName("BrightAdjustment");
        listWidgetBrightAdjustment = new QListWidget(BrightAdjustment);
        new QListWidgetItem(listWidgetBrightAdjustment);
        new QListWidgetItem(listWidgetBrightAdjustment);
        new QListWidgetItem(listWidgetBrightAdjustment);
        listWidgetBrightAdjustment->setObjectName("listWidgetBrightAdjustment");
        listWidgetBrightAdjustment->setGeometry(QRect(0, 0, 171, 321));
        stackedWidget->addWidget(BrightAdjustment);
        Attribute = new QWidget();
        Attribute->setObjectName("Attribute");
        listWidgetAttribute = new QListWidget(Attribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        new QListWidgetItem(listWidgetAttribute);
        listWidgetAttribute->setObjectName("listWidgetAttribute");
        listWidgetAttribute->setGeometry(QRect(0, 0, 171, 321));
        stackedWidget->addWidget(Attribute);
        Search = new QWidget();
        Search->setObjectName("Search");
        listWidgetSearch = new QListWidget(Search);
        new QListWidgetItem(listWidgetSearch);
        new QListWidgetItem(listWidgetSearch);
        new QListWidgetItem(listWidgetSearch);
        listWidgetSearch->setObjectName("listWidgetSearch");
        listWidgetSearch->setGeometry(QRect(0, 0, 171, 321));
        stackedWidget->addWidget(Search);
        tableWidgetValue = new QTableWidget(DetailOperation);
        if (tableWidgetValue->columnCount() < 4)
            tableWidgetValue->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetValue->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetValue->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetValue->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetValue->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        tableWidgetValue->setObjectName("tableWidgetValue");
        tableWidgetValue->setGeometry(QRect(330, 0, 241, 231));
        pushButtonSaveCSV = new QPushButton(DetailOperation);
        pushButtonSaveCSV->setObjectName("pushButtonSaveCSV");
        pushButtonSaveCSV->setGeometry(QRect(420, 240, 111, 28));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSaveCSV->setIcon(icon);
        stackedWidgetMode->addWidget(DetailOperation);
        EasyOperation = new QWidget();
        EasyOperation->setObjectName("EasyOperation");
        label = new QLabel(EasyOperation);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 321, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        horizontalSliderBrightnessN = new QSlider(EasyOperation);
        horizontalSliderBrightnessN->setObjectName("horizontalSliderBrightnessN");
        horizontalSliderBrightnessN->setGeometry(QRect(70, 20, 148, 22));
        horizontalSliderBrightnessN->setMaximum(100);
        horizontalSliderBrightnessN->setValue(50);
        horizontalSliderBrightnessN->setOrientation(Qt::Horizontal);
        horizontalSliderBrightnessN->setTickPosition(QSlider::TicksBelow);
        label_2 = new QLabel(EasyOperation);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 61, 20));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(EasyOperation);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 44, 61, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelBrightnessN = new QLabel(EasyOperation);
        labelBrightnessN->setObjectName("labelBrightnessN");
        labelBrightnessN->setGeometry(QRect(220, 20, 31, 21));
        labelSIzeN = new QLabel(EasyOperation);
        labelSIzeN->setObjectName("labelSIzeN");
        labelSIzeN->setGeometry(QRect(220, 44, 31, 21));
        horizontalSizeN = new QSlider(EasyOperation);
        horizontalSizeN->setObjectName("horizontalSizeN");
        horizontalSizeN->setGeometry(QRect(70, 44, 148, 22));
        horizontalSizeN->setMaximum(100);
        horizontalSizeN->setValue(50);
        horizontalSizeN->setOrientation(Qt::Horizontal);
        horizontalSizeN->setTickPosition(QSlider::TicksBelow);
        label_6 = new QLabel(EasyOperation);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(250, 20, 71, 20));
        label_7 = new QLabel(EasyOperation);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(250, 44, 71, 20));
        labelBrightnessB = new QLabel(EasyOperation);
        labelBrightnessB->setObjectName("labelBrightnessB");
        labelBrightnessB->setGeometry(QRect(220, 88, 31, 21));
        label_8 = new QLabel(EasyOperation);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(250, 88, 71, 20));
        label_4 = new QLabel(EasyOperation);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 88, 61, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(EasyOperation);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 112, 61, 20));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        horizontalSizeB = new QSlider(EasyOperation);
        horizontalSizeB->setObjectName("horizontalSizeB");
        horizontalSizeB->setGeometry(QRect(70, 112, 148, 22));
        horizontalSizeB->setMaximum(100);
        horizontalSizeB->setValue(50);
        horizontalSizeB->setOrientation(Qt::Horizontal);
        horizontalSizeB->setTickPosition(QSlider::TicksBelow);
        labelSIzeB = new QLabel(EasyOperation);
        labelSIzeB->setObjectName("labelSIzeB");
        labelSIzeB->setGeometry(QRect(220, 112, 31, 21));
        label_9 = new QLabel(EasyOperation);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(250, 112, 71, 20));
        label_10 = new QLabel(EasyOperation);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(0, 68, 321, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        horizontalSliderBrightnessB = new QSlider(EasyOperation);
        horizontalSliderBrightnessB->setObjectName("horizontalSliderBrightnessB");
        horizontalSliderBrightnessB->setGeometry(QRect(70, 88, 148, 22));
        horizontalSliderBrightnessB->setMaximum(100);
        horizontalSliderBrightnessB->setValue(50);
        horizontalSliderBrightnessB->setOrientation(Qt::Horizontal);
        horizontalSliderBrightnessB->setTickPosition(QSlider::TicksBelow);
        label_11 = new QLabel(EasyOperation);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(0, 136, 321, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(EasyOperation);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(0, 156, 61, 20));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        horizontalSliderSearch = new QSlider(EasyOperation);
        horizontalSliderSearch->setObjectName("horizontalSliderSearch");
        horizontalSliderSearch->setGeometry(QRect(70, 156, 148, 22));
        horizontalSliderSearch->setMaximum(100);
        horizontalSliderSearch->setValue(50);
        horizontalSliderSearch->setOrientation(Qt::Horizontal);
        horizontalSliderSearch->setTickPosition(QSlider::TicksBelow);
        labelSearch = new QLabel(EasyOperation);
        labelSearch->setObjectName("labelSearch");
        labelSearch->setGeometry(QRect(220, 156, 31, 21));
        pushButtonSetEasyOperation = new QPushButton(EasyOperation);
        pushButtonSetEasyOperation->setObjectName("pushButtonSetEasyOperation");
        pushButtonSetEasyOperation->setGeometry(QRect(254, 158, 61, 26));
        stackedWidgetMode->addWidget(EasyOperation);

        retranslateUi(ShowBlockListForm);

        stackedWidgetMode->setCurrentIndex(1);
        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ShowBlockListForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowBlockListForm)
    {
        ShowBlockListForm->setWindowTitle(QCoreApplication::translate("ShowBlockListForm", "Show Block List", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLib->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowBlockListForm", "TYpe", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLib->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowBlockListForm", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLib->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowBlockListForm", "Lib Name", nullptr));

        const bool __sortingEnabled = listWidgetValueType->isSortingEnabled();
        listWidgetValueType->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetValueType->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("ShowBlockListForm", "Broad dark", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidgetValueType->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("ShowBlockListForm", "Broad light", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidgetValueType->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("ShowBlockListForm", "Narrow dark", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidgetValueType->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("ShowBlockListForm", "Narrow light", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidgetValueType->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("ShowBlockListForm", "Bright adjustment", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidgetValueType->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("ShowBlockListForm", "Attribute", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidgetValueType->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("ShowBlockListForm", "Search", nullptr));
        listWidgetValueType->setSortingEnabled(__sortingEnabled);


        const bool __sortingEnabled1 = listWidgetBroadDark->isSortingEnabled();
        listWidgetBroadDark->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem7 = listWidgetBroadDark->item(0);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("ShowBlockListForm", "Brightness width", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidgetBroadDark->item(1);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("ShowBlockListForm", "NG size", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidgetBroadDark->item(2);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("ShowBlockListForm", "NG length", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidgetBroadDark->item(3);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("ShowBlockListForm", "Max size", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidgetBroadDark->item(4);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("ShowBlockListForm", "Cluster count", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidgetBroadDark->item(5);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("ShowBlockListForm", "Connection", nullptr));
        listWidgetBroadDark->setSortingEnabled(__sortingEnabled1);


        const bool __sortingEnabled2 = listWidgetBroadLight->isSortingEnabled();
        listWidgetBroadLight->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem13 = listWidgetBroadLight->item(0);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("ShowBlockListForm", "Brightness width", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidgetBroadLight->item(1);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("ShowBlockListForm", "NG size", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidgetBroadLight->item(2);
        ___qlistwidgetitem15->setText(QCoreApplication::translate("ShowBlockListForm", "NG length", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = listWidgetBroadLight->item(3);
        ___qlistwidgetitem16->setText(QCoreApplication::translate("ShowBlockListForm", "Max size", nullptr));
        QListWidgetItem *___qlistwidgetitem17 = listWidgetBroadLight->item(4);
        ___qlistwidgetitem17->setText(QCoreApplication::translate("ShowBlockListForm", "Cluster count", nullptr));
        QListWidgetItem *___qlistwidgetitem18 = listWidgetBroadLight->item(5);
        ___qlistwidgetitem18->setText(QCoreApplication::translate("ShowBlockListForm", "Connection", nullptr));
        listWidgetBroadLight->setSortingEnabled(__sortingEnabled2);


        const bool __sortingEnabled3 = listWidgetNarrowDark->isSortingEnabled();
        listWidgetNarrowDark->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem19 = listWidgetNarrowDark->item(0);
        ___qlistwidgetitem19->setText(QCoreApplication::translate("ShowBlockListForm", "Brightness width", nullptr));
        QListWidgetItem *___qlistwidgetitem20 = listWidgetNarrowDark->item(1);
        ___qlistwidgetitem20->setText(QCoreApplication::translate("ShowBlockListForm", "NG size", nullptr));
        QListWidgetItem *___qlistwidgetitem21 = listWidgetNarrowDark->item(2);
        ___qlistwidgetitem21->setText(QCoreApplication::translate("ShowBlockListForm", "NG length", nullptr));
        QListWidgetItem *___qlistwidgetitem22 = listWidgetNarrowDark->item(3);
        ___qlistwidgetitem22->setText(QCoreApplication::translate("ShowBlockListForm", "Max size", nullptr));
        QListWidgetItem *___qlistwidgetitem23 = listWidgetNarrowDark->item(4);
        ___qlistwidgetitem23->setText(QCoreApplication::translate("ShowBlockListForm", "Cluster count", nullptr));
        QListWidgetItem *___qlistwidgetitem24 = listWidgetNarrowDark->item(5);
        ___qlistwidgetitem24->setText(QCoreApplication::translate("ShowBlockListForm", "Connection", nullptr));
        listWidgetNarrowDark->setSortingEnabled(__sortingEnabled3);


        const bool __sortingEnabled4 = listWidgetNarrowLight->isSortingEnabled();
        listWidgetNarrowLight->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem25 = listWidgetNarrowLight->item(0);
        ___qlistwidgetitem25->setText(QCoreApplication::translate("ShowBlockListForm", "Brightness width", nullptr));
        QListWidgetItem *___qlistwidgetitem26 = listWidgetNarrowLight->item(1);
        ___qlistwidgetitem26->setText(QCoreApplication::translate("ShowBlockListForm", "NG size", nullptr));
        QListWidgetItem *___qlistwidgetitem27 = listWidgetNarrowLight->item(2);
        ___qlistwidgetitem27->setText(QCoreApplication::translate("ShowBlockListForm", "NG length", nullptr));
        QListWidgetItem *___qlistwidgetitem28 = listWidgetNarrowLight->item(3);
        ___qlistwidgetitem28->setText(QCoreApplication::translate("ShowBlockListForm", "Max size", nullptr));
        QListWidgetItem *___qlistwidgetitem29 = listWidgetNarrowLight->item(4);
        ___qlistwidgetitem29->setText(QCoreApplication::translate("ShowBlockListForm", "Cluster count", nullptr));
        QListWidgetItem *___qlistwidgetitem30 = listWidgetNarrowLight->item(5);
        ___qlistwidgetitem30->setText(QCoreApplication::translate("ShowBlockListForm", "Connection", nullptr));
        listWidgetNarrowLight->setSortingEnabled(__sortingEnabled4);


        const bool __sortingEnabled5 = listWidgetBrightAdjustment->isSortingEnabled();
        listWidgetBrightAdjustment->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem31 = listWidgetBrightAdjustment->item(0);
        ___qlistwidgetitem31->setText(QCoreApplication::translate("ShowBlockListForm", "Enable", nullptr));
        QListWidgetItem *___qlistwidgetitem32 = listWidgetBrightAdjustment->item(1);
        ___qlistwidgetitem32->setText(QCoreApplication::translate("ShowBlockListForm", "Dark side", nullptr));
        QListWidgetItem *___qlistwidgetitem33 = listWidgetBrightAdjustment->item(2);
        ___qlistwidgetitem33->setText(QCoreApplication::translate("ShowBlockListForm", "Light side", nullptr));
        listWidgetBrightAdjustment->setSortingEnabled(__sortingEnabled5);


        const bool __sortingEnabled6 = listWidgetAttribute->isSortingEnabled();
        listWidgetAttribute->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem34 = listWidgetAttribute->item(0);
        ___qlistwidgetitem34->setText(QCoreApplication::translate("ShowBlockListForm", "Inspection effective", nullptr));
        QListWidgetItem *___qlistwidgetitem35 = listWidgetAttribute->item(1);
        ___qlistwidgetitem35->setText(QCoreApplication::translate("ShowBlockListForm", "Absolute brightness", nullptr));
        QListWidgetItem *___qlistwidgetitem36 = listWidgetAttribute->item(2);
        ___qlistwidgetitem36->setText(QCoreApplication::translate("ShowBlockListForm", "Clusterize", nullptr));
        QListWidgetItem *___qlistwidgetitem37 = listWidgetAttribute->item(3);
        ___qlistwidgetitem37->setText(QCoreApplication::translate("ShowBlockListForm", "DIfferential", nullptr));
        QListWidgetItem *___qlistwidgetitem38 = listWidgetAttribute->item(4);
        ___qlistwidgetitem38->setText(QCoreApplication::translate("ShowBlockListForm", "Follow outline", nullptr));
        QListWidgetItem *___qlistwidgetitem39 = listWidgetAttribute->item(5);
        ___qlistwidgetitem39->setText(QCoreApplication::translate("ShowBlockListForm", "Only Max NG size", nullptr));
        QListWidgetItem *___qlistwidgetitem40 = listWidgetAttribute->item(6);
        ___qlistwidgetitem40->setText(QCoreApplication::translate("ShowBlockListForm", "No output", nullptr));
        QListWidgetItem *___qlistwidgetitem41 = listWidgetAttribute->item(7);
        ___qlistwidgetitem41->setText(QCoreApplication::translate("ShowBlockListForm", "White mask", nullptr));
        QListWidgetItem *___qlistwidgetitem42 = listWidgetAttribute->item(8);
        ___qlistwidgetitem42->setText(QCoreApplication::translate("ShowBlockListForm", "Black mask", nullptr));
        QListWidgetItem *___qlistwidgetitem43 = listWidgetAttribute->item(9);
        ___qlistwidgetitem43->setText(QCoreApplication::translate("ShowBlockListForm", "Pickup from parts", nullptr));
        QListWidgetItem *___qlistwidgetitem44 = listWidgetAttribute->item(10);
        ___qlistwidgetitem44->setText(QCoreApplication::translate("ShowBlockListForm", "Reverse logic", nullptr));
        QListWidgetItem *___qlistwidgetitem45 = listWidgetAttribute->item(11);
        ___qlistwidgetitem45->setText(QCoreApplication::translate("ShowBlockListForm", "Detail search", nullptr));
        QListWidgetItem *___qlistwidgetitem46 = listWidgetAttribute->item(12);
        ___qlistwidgetitem46->setText(QCoreApplication::translate("ShowBlockListForm", "Dynamic mask", nullptr));
        QListWidgetItem *___qlistwidgetitem47 = listWidgetAttribute->item(13);
        ___qlistwidgetitem47->setText(QCoreApplication::translate("ShowBlockListForm", "Use master image", nullptr));
        listWidgetAttribute->setSortingEnabled(__sortingEnabled6);


        const bool __sortingEnabled7 = listWidgetSearch->isSortingEnabled();
        listWidgetSearch->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem48 = listWidgetSearch->item(0);
        ___qlistwidgetitem48->setText(QCoreApplication::translate("ShowBlockListForm", "Enabled whole search", nullptr));
        QListWidgetItem *___qlistwidgetitem49 = listWidgetSearch->item(1);
        ___qlistwidgetitem49->setText(QCoreApplication::translate("ShowBlockListForm", "Self search dot", nullptr));
        QListWidgetItem *___qlistwidgetitem50 = listWidgetSearch->item(2);
        ___qlistwidgetitem50->setText(QCoreApplication::translate("ShowBlockListForm", "Whole search dot", nullptr));
        listWidgetSearch->setSortingEnabled(__sortingEnabled7);

        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetValue->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowBlockListForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetValue->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowBlockListForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetValue->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowBlockListForm", "Value", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetValue->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ShowBlockListForm", "Count", nullptr));
        pushButtonSaveCSV->setText(QCoreApplication::translate("ShowBlockListForm", "Save CSV", nullptr));
        label->setText(QCoreApplication::translate("ShowBlockListForm", "\345\260\217\343\201\225\343\201\217\343\201\246\346\230\216\347\236\255\343\201\252\344\270\215\350\211\257", nullptr));
        label_2->setText(QCoreApplication::translate("ShowBlockListForm", "\346\230\216\347\236\255\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("ShowBlockListForm", "\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272", nullptr));
        labelBrightnessN->setText(QCoreApplication::translate("ShowBlockListForm", "5.0", nullptr));
        labelSIzeN->setText(QCoreApplication::translate("ShowBlockListForm", "10", nullptr));
        label_6->setText(QCoreApplication::translate("ShowBlockListForm", "\303\227\317\203", nullptr));
        label_7->setText(QCoreApplication::translate("ShowBlockListForm", "\351\235\242\347\251\215\343\201\256\345\257\276\346\225\260", nullptr));
        labelBrightnessB->setText(QCoreApplication::translate("ShowBlockListForm", "5.0", nullptr));
        label_8->setText(QCoreApplication::translate("ShowBlockListForm", "\303\227\317\203", nullptr));
        label_4->setText(QCoreApplication::translate("ShowBlockListForm", "\346\230\216\347\236\255\345\272\246", nullptr));
        label_5->setText(QCoreApplication::translate("ShowBlockListForm", "\346\244\234\345\207\272\343\202\265\343\202\244\343\202\272", nullptr));
        labelSIzeB->setText(QCoreApplication::translate("ShowBlockListForm", "10", nullptr));
        label_9->setText(QCoreApplication::translate("ShowBlockListForm", "\351\235\242\347\251\215\343\201\256\345\257\276\346\225\260", nullptr));
        label_10->setText(QCoreApplication::translate("ShowBlockListForm", "\345\244\247\343\201\215\343\201\217\343\201\246\344\270\215\346\230\216\347\236\255\343\201\252\344\270\215\350\211\257", nullptr));
        label_11->setText(QCoreApplication::translate("ShowBlockListForm", "\343\202\272\343\203\254\346\216\242\347\264\242\351\207\217", nullptr));
        label_12->setText(QCoreApplication::translate("ShowBlockListForm", "\346\216\242\347\264\242\351\207\217", nullptr));
        labelSearch->setText(QCoreApplication::translate("ShowBlockListForm", "10", nullptr));
        pushButtonSetEasyOperation->setText(QCoreApplication::translate("ShowBlockListForm", "\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowBlockListForm: public Ui_ShowBlockListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWBLOCKLISTFORM_H
