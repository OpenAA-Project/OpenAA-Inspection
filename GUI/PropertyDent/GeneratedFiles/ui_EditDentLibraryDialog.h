/********************************************************************************
** Form generated from reading UI file 'EditDentLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDENTLIBRARYDIALOG_H
#define UI_EDITDENTLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditDentLibraryDialog
{
public:
    QPushButton *ButtonLibUpdate;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibDelete;
    QPushButton *pushButtonClose;
    QPushButton *ButtonLibSaveNew;
    QPushButton *ButtonLibNew;
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QLabel *label_4;
    QFrame *frame_2;
    QLabel *label_7;
    QLabel *label_30;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBoxMinNGSize;
    QLabel *label_19;
    QDoubleSpinBox *doubleSpinBoxMaxNGSize;
    QDoubleSpinBox *doubleSpinBoxMaxDiffCoef;
    QLabel *label_24;
    QSpinBox *EditBaseWaveLength;
    QLabel *label_25;
    QSpinBox *EditLinesForAverage;
    QLineEdit *EditLibName;
    QFrame *frame_3;
    QSpinBox *EditMinDentSize;
    QLabel *label_9;
    QSpinBox *EditMaxDentSize;
    QLabel *label_10;
    QSpinBox *EditMinDentDots;
    QLabel *label_12;
    QSpinBox *EditMaxDentDots;
    QLabel *label_11;
    QLabel *label_13;
    QSpinBox *EditLimitDentSize;
    QLabel *label_32;
    QLabel *label_20;
    QSpinBox *EditIgnoreAroundHole;
    QFrame *frame_4;
    QLabel *label_14;
    QSpinBox *EditPickupRL;
    QLabel *label_15;
    QSpinBox *EditPickupRH;
    QLabel *label_31;
    QLabel *label_16;
    QLabel *label_21;
    QSpinBox *EditPickupGL;
    QSpinBox *EditPickupGH;
    QLabel *label_22;
    QLabel *label_23;
    QSpinBox *EditPickupBL;
    QSpinBox *EditPickupBH;
    QFrame *frame_5;
    QLabel *label_17;
    QSpinBox *EditSpaceToOutline;
    QSpinBox *EditNoiseSize;
    QLabel *label_33;
    QLabel *label_48;
    QLabel *label_49;
    QSpinBox *EditNoiseSizePinHole;
    QDoubleSpinBox *doubleSpinBoxBandWidth;
    QLabel *label_8;
    QLabel *label_2;
    QFrame *frameGenLayer;

    void setupUi(QDialog *EditDentLibraryDialog)
    {
        if (EditDentLibraryDialog->objectName().isEmpty())
            EditDentLibraryDialog->setObjectName("EditDentLibraryDialog");
        EditDentLibraryDialog->resize(642, 802);
        ButtonLibUpdate = new QPushButton(EditDentLibraryDialog);
        ButtonLibUpdate->setObjectName("ButtonLibUpdate");
        ButtonLibUpdate->setGeometry(QRect(530, 720, 81, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibUpdate->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibUpdate->setIcon(icon);
        EditLibID = new QLineEdit(EditDentLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(270, 10, 81, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        ButtonLibDelete = new QPushButton(EditDentLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(340, 720, 81, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon1);
        pushButtonClose = new QPushButton(EditDentLibraryDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(530, 760, 81, 31));
        pushButtonClose->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon2);
        ButtonLibSaveNew = new QPushButton(EditDentLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(430, 720, 91, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon3);
        ButtonLibNew = new QPushButton(EditDentLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(240, 720, 91, 31));
        ButtonLibNew->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon4);
        tableWidgetLibList = new QTableWidget(EditDentLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 240, 191, 231));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(EditDentLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 20, 191, 211));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(EditDentLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(220, 10, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(EditDentLibraryDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(220, 570, 411, 141));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(60, 10, 221, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(0, 0, 31, 141));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Raised);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30->setIndent(1);
        label_18 = new QLabel(frame_2);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(60, 30, 221, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxMinNGSize = new QDoubleSpinBox(frame_2);
        doubleSpinBoxMinNGSize->setObjectName("doubleSpinBoxMinNGSize");
        doubleSpinBoxMinNGSize->setGeometry(QRect(290, 30, 111, 24));
        doubleSpinBoxMinNGSize->setDecimals(3);
        doubleSpinBoxMinNGSize->setMaximum(99999999.000000000000000);
        label_19 = new QLabel(frame_2);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(60, 50, 221, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxMaxNGSize = new QDoubleSpinBox(frame_2);
        doubleSpinBoxMaxNGSize->setObjectName("doubleSpinBoxMaxNGSize");
        doubleSpinBoxMaxNGSize->setGeometry(QRect(290, 50, 111, 24));
        doubleSpinBoxMaxNGSize->setDecimals(3);
        doubleSpinBoxMaxNGSize->setMaximum(99999999.000000000000000);
        doubleSpinBoxMaxDiffCoef = new QDoubleSpinBox(frame_2);
        doubleSpinBoxMaxDiffCoef->setObjectName("doubleSpinBoxMaxDiffCoef");
        doubleSpinBoxMaxDiffCoef->setGeometry(QRect(290, 80, 111, 24));
        doubleSpinBoxMaxDiffCoef->setDecimals(3);
        doubleSpinBoxMaxDiffCoef->setMaximum(99999999.000000000000000);
        label_24 = new QLabel(frame_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(60, 80, 221, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBaseWaveLength = new QSpinBox(frame_2);
        EditBaseWaveLength->setObjectName("EditBaseWaveLength");
        EditBaseWaveLength->setGeometry(QRect(290, 10, 111, 20));
        QFont font2;
        font2.setPointSize(9);
        EditBaseWaveLength->setFont(font2);
        label_25 = new QLabel(frame_2);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(60, 110, 221, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLinesForAverage = new QSpinBox(frame_2);
        EditLinesForAverage->setObjectName("EditLinesForAverage");
        EditLinesForAverage->setGeometry(QRect(290, 110, 111, 20));
        EditLinesForAverage->setFont(font2);
        EditLibName = new QLineEdit(EditDentLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(350, 10, 281, 31));
        EditLibName->setFont(font1);
        frame_3 = new QFrame(EditDentLibraryDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(220, 280, 411, 171));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        EditMinDentSize = new QSpinBox(frame_3);
        EditMinDentSize->setObjectName("EditMinDentSize");
        EditMinDentSize->setGeometry(QRect(290, 10, 81, 22));
        EditMinDentSize->setMaximum(1000000);
        label_9 = new QLabel(frame_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(60, 30, 221, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxDentSize = new QSpinBox(frame_3);
        EditMaxDentSize->setObjectName("EditMaxDentSize");
        EditMaxDentSize->setGeometry(QRect(290, 30, 81, 22));
        EditMaxDentSize->setMaximum(1000000);
        label_10 = new QLabel(frame_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(60, 10, 221, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinDentDots = new QSpinBox(frame_3);
        EditMinDentDots->setObjectName("EditMinDentDots");
        EditMinDentDots->setGeometry(QRect(290, 60, 101, 22));
        EditMinDentDots->setMaximum(2000000000);
        label_12 = new QLabel(frame_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(60, 60, 221, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxDentDots = new QSpinBox(frame_3);
        EditMaxDentDots->setObjectName("EditMaxDentDots");
        EditMaxDentDots->setGeometry(QRect(290, 80, 101, 22));
        EditMaxDentDots->setMaximum(2000000000);
        EditMaxDentDots->setValue(2000000000);
        label_11 = new QLabel(frame_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(60, 80, 221, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(60, 110, 221, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitDentSize = new QSpinBox(frame_3);
        EditLimitDentSize->setObjectName("EditLimitDentSize");
        EditLimitDentSize->setGeometry(QRect(290, 110, 61, 22));
        EditLimitDentSize->setMaximum(99999);
        label_32 = new QLabel(frame_3);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(0, 0, 31, 171));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Raised);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32->setIndent(1);
        label_20 = new QLabel(frame_3);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(60, 140, 221, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditIgnoreAroundHole = new QSpinBox(frame_3);
        EditIgnoreAroundHole->setObjectName("EditIgnoreAroundHole");
        EditIgnoreAroundHole->setGeometry(QRect(290, 140, 61, 22));
        EditIgnoreAroundHole->setMaximum(99999);
        frame_4 = new QFrame(EditDentLibraryDialog);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(220, 110, 411, 161));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(60, 10, 261, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupRL = new QSpinBox(frame_4);
        EditPickupRL->setObjectName("EditPickupRL");
        EditPickupRL->setGeometry(QRect(330, 10, 61, 22));
        EditPickupRL->setMaximum(255);
        label_15 = new QLabel(frame_4);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(60, 30, 261, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupRH = new QSpinBox(frame_4);
        EditPickupRH->setObjectName("EditPickupRH");
        EditPickupRH->setGeometry(QRect(330, 30, 61, 22));
        EditPickupRH->setMaximum(255);
        label_31 = new QLabel(frame_4);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(0, 0, 31, 161));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Raised);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31->setIndent(1);
        label_16 = new QLabel(frame_4);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(60, 60, 261, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_21 = new QLabel(frame_4);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(60, 80, 261, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupGL = new QSpinBox(frame_4);
        EditPickupGL->setObjectName("EditPickupGL");
        EditPickupGL->setGeometry(QRect(330, 60, 61, 22));
        EditPickupGL->setMaximum(255);
        EditPickupGH = new QSpinBox(frame_4);
        EditPickupGH->setObjectName("EditPickupGH");
        EditPickupGH->setGeometry(QRect(330, 80, 61, 22));
        EditPickupGH->setMaximum(255);
        label_22 = new QLabel(frame_4);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(60, 110, 261, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(frame_4);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(60, 130, 261, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupBL = new QSpinBox(frame_4);
        EditPickupBL->setObjectName("EditPickupBL");
        EditPickupBL->setGeometry(QRect(330, 110, 61, 22));
        EditPickupBL->setMaximum(255);
        EditPickupBH = new QSpinBox(frame_4);
        EditPickupBH->setObjectName("EditPickupBH");
        EditPickupBH->setGeometry(QRect(330, 130, 61, 22));
        EditPickupBH->setMaximum(255);
        frame_5 = new QFrame(EditDentLibraryDialog);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(220, 460, 411, 101));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_17 = new QLabel(frame_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(60, 10, 261, 20));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSpaceToOutline = new QSpinBox(frame_5);
        EditSpaceToOutline->setObjectName("EditSpaceToOutline");
        EditSpaceToOutline->setGeometry(QRect(330, 10, 61, 20));
        EditNoiseSize = new QSpinBox(frame_5);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(330, 30, 61, 20));
        EditNoiseSize->setFont(font2);
        label_33 = new QLabel(frame_5);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(0, 0, 31, 101));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Raised);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_33->setIndent(1);
        label_48 = new QLabel(frame_5);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(60, 50, 261, 20));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Sunken);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_49 = new QLabel(frame_5);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(60, 30, 261, 20));
        label_49->setFrameShape(QFrame::Panel);
        label_49->setFrameShadow(QFrame::Sunken);
        label_49->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSizePinHole = new QSpinBox(frame_5);
        EditNoiseSizePinHole->setObjectName("EditNoiseSizePinHole");
        EditNoiseSizePinHole->setGeometry(QRect(330, 50, 61, 20));
        EditNoiseSizePinHole->setFont(font2);
        doubleSpinBoxBandWidth = new QDoubleSpinBox(frame_5);
        doubleSpinBoxBandWidth->setObjectName("doubleSpinBoxBandWidth");
        doubleSpinBoxBandWidth->setGeometry(QRect(290, 70, 101, 20));
        doubleSpinBoxBandWidth->setDecimals(3);
        doubleSpinBoxBandWidth->setMaximum(99999999.000000000000000);
        label_8 = new QLabel(frame_5);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(60, 70, 221, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(EditDentLibraryDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(220, 50, 393, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(EditDentLibraryDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(220, 70, 393, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);

        retranslateUi(EditDentLibraryDialog);

        QMetaObject::connectSlotsByName(EditDentLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditDentLibraryDialog)
    {
        EditDentLibraryDialog->setWindowTitle(QCoreApplication::translate("EditDentLibraryDialog", "Dialog", nullptr));
        ButtonLibUpdate->setText(QCoreApplication::translate("EditDentLibraryDialog", "Update", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditDentLibraryDialog", "12345", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditDentLibraryDialog", "Delete", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditDentLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditDentLibraryDialog", "Save New", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditDentLibraryDialog", "Clear new", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditDentLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditDentLibraryDialog", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("EditDentLibraryDialog", "\345\220\215\347\247\260", nullptr));
        label_7->setText(QCoreApplication::translate("EditDentLibraryDialog", "\346\250\252\346\226\271\345\220\221\343\201\256\345\237\272\346\234\254\346\263\242\351\225\267", nullptr));
        label_30->setText(QCoreApplication::translate("EditDentLibraryDialog", "<html><head/><body><p>\346\244\234</p><p>\346\237\273</p><p>\350\250\255</p><p>\345\256\232</p></body></html>", nullptr));
        label_18->setText(QCoreApplication::translate("EditDentLibraryDialog", "Minimum NG size", nullptr));
        label_19->setText(QCoreApplication::translate("EditDentLibraryDialog", "Maximum NG size", nullptr));
        label_24->setText(QCoreApplication::translate("EditDentLibraryDialog", "\346\244\234\345\207\272\343\201\256\346\263\242\351\225\267\345\267\256\347\225\260", nullptr));
        label_25->setText(QCoreApplication::translate("EditDentLibraryDialog", "\347\270\246\346\226\271\345\220\221\343\201\256\345\271\263\345\235\207\345\214\226\343\203\251\343\202\244\343\203\263\346\225\260", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditDentLibraryDialog", "Library Name", nullptr));
        label_9->setText(QCoreApplication::translate("EditDentLibraryDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_10->setText(QCoreApplication::translate("EditDentLibraryDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("EditDentLibraryDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_11->setText(QCoreApplication::translate("EditDentLibraryDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_13->setText(QCoreApplication::translate("EditDentLibraryDialog", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        label_32->setText(QCoreApplication::translate("EditDentLibraryDialog", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        label_20->setText(QCoreApplication::translate("EditDentLibraryDialog", "\347\251\264\345\221\250\350\276\272\343\201\256\351\231\244\345\216\273\343\202\265\343\202\244\343\202\272", nullptr));
        label_14->setText(QCoreApplication::translate("EditDentLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246 R\343\200\200\346\232\227\345\201\264", nullptr));
        label_15->setText(QCoreApplication::translate("EditDentLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246 R\343\200\200\346\230\216\345\201\264", nullptr));
        label_31->setText(QCoreApplication::translate("EditDentLibraryDialog", "\350\274\235\n"
"\345\272\246", nullptr));
        label_16->setText(QCoreApplication::translate("EditDentLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246 G\343\200\200\346\232\227\345\201\264", nullptr));
        label_21->setText(QCoreApplication::translate("EditDentLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246 G\343\200\200\346\230\216\345\201\264", nullptr));
        label_22->setText(QCoreApplication::translate("EditDentLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246 B\343\200\200\346\232\227\345\201\264", nullptr));
        label_23->setText(QCoreApplication::translate("EditDentLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246 B\343\200\200\346\230\216\345\201\264", nullptr));
        label_17->setText(QCoreApplication::translate("EditDentLibraryDialog", "\350\274\252\351\203\255\343\201\213\343\202\211\343\201\256\351\226\223\351\232\224", nullptr));
        label_33->setText(QCoreApplication::translate("EditDentLibraryDialog", "\347\224\237\n"
"\346\210\220", nullptr));
        label_48->setText(QCoreApplication::translate("EditDentLibraryDialog", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272\343\200\200\343\203\224\343\203\263\343\203\233\343\203\274\343\203\253\345\211\212\351\231\244", nullptr));
        label_49->setText(QCoreApplication::translate("EditDentLibraryDialog", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272 \345\255\244\347\253\213\347\202\271\345\211\212\351\231\244", nullptr));
        label_8->setText(QCoreApplication::translate("EditDentLibraryDialog", "Band width", nullptr));
        label_2->setText(QCoreApplication::translate("EditDentLibraryDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditDentLibraryDialog: public Ui_EditDentLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDENTLIBRARYDIALOG_H
