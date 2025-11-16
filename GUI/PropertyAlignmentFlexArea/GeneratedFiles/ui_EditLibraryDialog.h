/********************************************************************************
** Form generated from reading UI file 'EditLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYDIALOG_H
#define UI_EDITLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditLibraryDialog
{
public:
    QLabel *label_10;
    QLineEdit *EditLibName;
    QTableWidget *tableWidgetLibList;
    QFrame *framePickLayer;
    QPushButton *ButtonLibSaveNew;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibSave;
    QPushButton *ButtonLibNew;
    QPushButton *pushButtonClose;
    QFrame *frameLibFolder;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QLabel *label_9;
    QFrame *frameGenLayer;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame_2;
    QLabel *label_7;
    QSpinBox *EditPickupL;
    QLabel *label_8;
    QSpinBox *EditPickupH;
    QLabel *label_30;
    QFrame *frame_3;
    QSpinBox *EditMinAreaSize;
    QLabel *label_11;
    QSpinBox *EditMaxAreaSize;
    QLabel *label_12;
    QSpinBox *EditMinAreaDots;
    QLabel *label_13;
    QSpinBox *EditMaxAreaDots;
    QLabel *label_14;
    QLabel *label_32;
    QFrame *frame_15;
    QSpinBox *EditExpansionDot;
    QLabel *label_58;
    QSpinBox *EditLimitSize;
    QLabel *label_59;
    QLabel *label_63;
    QComboBox *comboBoxAdaptedPriority;
    QLabel *label_60;
    QCheckBox *checkBoxPickUpEdge;
    QLabel *label_61;
    QSpinBox *EditPickUpEdgeMinDiff;
    QLabel *label_62;
    QDoubleSpinBox *EditMaxCoeffInNeighbor;
    QWidget *tab_2;
    QFrame *frame_26;
    QLabel *label_87;
    QSpinBox *EditSearchDot;
    QLabel *label_20;
    QLabel *label_3;
    QSpinBox *spinBoxGlobalSearchDot;
    QSpinBox *EditGroupAreaSize;
    QLabel *label_21;
    QCheckBox *checkBoxKeepBW;
    QLabel *label_22;
    QLabel *label_23;
    QSpinBox *EditSmallSearch;
    QDoubleSpinBox *doubleSpinBoxCloserRate;

    void setupUi(QDialog *EditLibraryDialog)
    {
        if (EditLibraryDialog->objectName().isEmpty())
            EditLibraryDialog->setObjectName("EditLibraryDialog");
        EditLibraryDialog->resize(618, 692);
        label_10 = new QLabel(EditLibraryDialog);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(210, 60, 381, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setTextFormat(Qt::AutoText);
        label_10->setAlignment(Qt::AlignCenter);
        EditLibName = new QLineEdit(EditLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(340, 20, 251, 31));
        QFont font;
        font.setPointSize(12);
        EditLibName->setFont(font);
        tableWidgetLibList = new QTableWidget(EditLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 190, 191, 291));
        tableWidgetLibList->setDragEnabled(true);
        tableWidgetLibList->setDragDropOverwriteMode(true);
        tableWidgetLibList->setDragDropMode(QAbstractItemView::DragOnly);
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        framePickLayer = new QFrame(EditLibraryDialog);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(210, 80, 381, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        ButtonLibSaveNew = new QPushButton(EditLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(350, 610, 131, 31));
        QFont font1;
        font1.setPointSize(11);
        ButtonLibSaveNew->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon);
        ButtonLibDelete = new QPushButton(EditLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(220, 610, 121, 31));
        ButtonLibDelete->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon1);
        ButtonLibSave = new QPushButton(EditLibraryDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(490, 610, 111, 31));
        ButtonLibSave->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon2);
        ButtonLibNew = new QPushButton(EditLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(220, 570, 121, 31));
        ButtonLibNew->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon3);
        pushButtonClose = new QPushButton(EditLibraryDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(490, 650, 111, 31));
        pushButtonClose->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon4);
        frameLibFolder = new QFrame(EditLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 30, 191, 151));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibID = new QLineEdit(EditLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(260, 20, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(EditLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(210, 20, 51, 31));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_9 = new QLabel(EditLibraryDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(210, 110, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        frameGenLayer = new QFrame(EditLibraryDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(210, 130, 381, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        tabWidget = new QTabWidget(EditLibraryDialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(210, 160, 401, 401));
        tab = new QWidget();
        tab->setObjectName("tab");
        frame_2 = new QFrame(tab);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 381, 61));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(42, 10, 261, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame_2);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(310, 10, 61, 22));
        EditPickupL->setMaximum(255);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(42, 30, 261, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame_2);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(310, 30, 61, 22));
        EditPickupH->setMaximum(255);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(0, 0, 31, 61));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Raised);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30->setIndent(1);
        frame_3 = new QFrame(tab);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 80, 381, 101));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        EditMinAreaSize = new QSpinBox(frame_3);
        EditMinAreaSize->setObjectName("EditMinAreaSize");
        EditMinAreaSize->setGeometry(QRect(270, 10, 81, 22));
        EditMinAreaSize->setMaximum(1000000);
        label_11 = new QLabel(frame_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(40, 30, 221, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxAreaSize = new QSpinBox(frame_3);
        EditMaxAreaSize->setObjectName("EditMaxAreaSize");
        EditMaxAreaSize->setGeometry(QRect(270, 30, 81, 22));
        EditMaxAreaSize->setMaximum(1000000);
        label_12 = new QLabel(frame_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(40, 10, 221, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinAreaDots = new QSpinBox(frame_3);
        EditMinAreaDots->setObjectName("EditMinAreaDots");
        EditMinAreaDots->setGeometry(QRect(270, 50, 101, 22));
        EditMinAreaDots->setMaximum(2000000000);
        label_13 = new QLabel(frame_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(40, 50, 221, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxAreaDots = new QSpinBox(frame_3);
        EditMaxAreaDots->setObjectName("EditMaxAreaDots");
        EditMaxAreaDots->setGeometry(QRect(270, 70, 101, 22));
        EditMaxAreaDots->setMinimum(-1);
        EditMaxAreaDots->setMaximum(2000000000);
        EditMaxAreaDots->setValue(2000000000);
        label_14 = new QLabel(frame_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(40, 70, 221, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32 = new QLabel(frame_3);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(0, 0, 31, 101));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Raised);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_32->setIndent(1);
        frame_15 = new QFrame(tab);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(10, 190, 381, 171));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        EditExpansionDot = new QSpinBox(frame_15);
        EditExpansionDot->setObjectName("EditExpansionDot");
        EditExpansionDot->setGeometry(QRect(290, 90, 81, 22));
        EditExpansionDot->setMaximum(1000000);
        label_58 = new QLabel(frame_15);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(40, 110, 241, 21));
        label_58->setFrameShape(QFrame::Panel);
        label_58->setFrameShadow(QFrame::Sunken);
        label_58->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitSize = new QSpinBox(frame_15);
        EditLimitSize->setObjectName("EditLimitSize");
        EditLimitSize->setGeometry(QRect(290, 110, 81, 22));
        EditLimitSize->setMaximum(1000000);
        label_59 = new QLabel(frame_15);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(40, 90, 241, 21));
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63 = new QLabel(frame_15);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(0, 0, 31, 171));
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Raised);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63->setIndent(1);
        comboBoxAdaptedPriority = new QComboBox(frame_15);
        comboBoxAdaptedPriority->addItem(QString());
        comboBoxAdaptedPriority->addItem(QString());
        comboBoxAdaptedPriority->addItem(QString());
        comboBoxAdaptedPriority->addItem(QString());
        comboBoxAdaptedPriority->addItem(QString());
        comboBoxAdaptedPriority->setObjectName("comboBoxAdaptedPriority");
        comboBoxAdaptedPriority->setGeometry(QRect(201, 140, 171, 24));
        label_60 = new QLabel(frame_15);
        label_60->setObjectName("label_60");
        label_60->setGeometry(QRect(40, 140, 151, 21));
        label_60->setFrameShape(QFrame::Panel);
        label_60->setFrameShadow(QFrame::Sunken);
        label_60->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxPickUpEdge = new QCheckBox(frame_15);
        checkBoxPickUpEdge->setObjectName("checkBoxPickUpEdge");
        checkBoxPickUpEdge->setGeometry(QRect(40, 10, 331, 21));
        label_61 = new QLabel(frame_15);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(40, 40, 241, 21));
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickUpEdgeMinDiff = new QSpinBox(frame_15);
        EditPickUpEdgeMinDiff->setObjectName("EditPickUpEdgeMinDiff");
        EditPickUpEdgeMinDiff->setGeometry(QRect(290, 40, 81, 22));
        EditPickUpEdgeMinDiff->setMaximum(1000000);
        label_62 = new QLabel(frame_15);
        label_62->setObjectName("label_62");
        label_62->setGeometry(QRect(40, 60, 241, 21));
        label_62->setFrameShape(QFrame::Panel);
        label_62->setFrameShadow(QFrame::Sunken);
        label_62->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxCoeffInNeighbor = new QDoubleSpinBox(frame_15);
        EditMaxCoeffInNeighbor->setObjectName("EditMaxCoeffInNeighbor");
        EditMaxCoeffInNeighbor->setGeometry(QRect(290, 60, 81, 22));
        EditMaxCoeffInNeighbor->setDecimals(3);
        EditMaxCoeffInNeighbor->setMaximum(1.000000000000000);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        frame_26 = new QFrame(tab_2);
        frame_26->setObjectName("frame_26");
        frame_26->setGeometry(QRect(10, 10, 381, 211));
        frame_26->setFrameShape(QFrame::StyledPanel);
        frame_26->setFrameShadow(QFrame::Sunken);
        label_87 = new QLabel(frame_26);
        label_87->setObjectName("label_87");
        label_87->setGeometry(QRect(0, 0, 31, 211));
        label_87->setFrameShape(QFrame::Panel);
        label_87->setFrameShadow(QFrame::Raised);
        label_87->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_87->setIndent(1);
        EditSearchDot = new QSpinBox(frame_26);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(290, 40, 81, 20));
        EditSearchDot->setMinimum(-255);
        EditSearchDot->setMaximum(255);
        label_20 = new QLabel(frame_26);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(40, 40, 241, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(frame_26);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 10, 241, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        spinBoxGlobalSearchDot = new QSpinBox(frame_26);
        spinBoxGlobalSearchDot->setObjectName("spinBoxGlobalSearchDot");
        spinBoxGlobalSearchDot->setGeometry(QRect(290, 10, 81, 22));
        spinBoxGlobalSearchDot->setMaximum(999999);
        EditGroupAreaSize = new QSpinBox(frame_26);
        EditGroupAreaSize->setObjectName("EditGroupAreaSize");
        EditGroupAreaSize->setGeometry(QRect(290, 70, 81, 20));
        EditGroupAreaSize->setMinimum(0);
        EditGroupAreaSize->setMaximum(99999999);
        label_21 = new QLabel(frame_26);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(40, 70, 241, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxKeepBW = new QCheckBox(frame_26);
        checkBoxKeepBW->setObjectName("checkBoxKeepBW");
        checkBoxKeepBW->setGeometry(QRect(40, 180, 291, 22));
        label_22 = new QLabel(frame_26);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(40, 100, 241, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(frame_26);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(40, 130, 241, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSmallSearch = new QSpinBox(frame_26);
        EditSmallSearch->setObjectName("EditSmallSearch");
        EditSmallSearch->setGeometry(QRect(290, 130, 81, 20));
        EditSmallSearch->setMinimum(0);
        EditSmallSearch->setMaximum(99999999);
        doubleSpinBoxCloserRate = new QDoubleSpinBox(frame_26);
        doubleSpinBoxCloserRate->setObjectName("doubleSpinBoxCloserRate");
        doubleSpinBoxCloserRate->setGeometry(QRect(290, 100, 81, 24));
        doubleSpinBoxCloserRate->setDecimals(3);
        doubleSpinBoxCloserRate->setMaximum(1.000000000000000);
        tabWidget->addTab(tab_2, QString());

        retranslateUi(EditLibraryDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryDialog)
    {
        EditLibraryDialog->setWindowTitle(QCoreApplication::translate("EditLibraryDialog", "Edit library", nullptr));
        label_10->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryDialog", "Library Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryDialog", "Name", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryDialog", "Save New", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryDialog", "Delete", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryDialog", "Update", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryDialog", "Clear new", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryDialog", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryDialog", "\345\220\215\347\247\260", nullptr));
        label_9->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        label_7->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        label_8->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        label_30->setText(QCoreApplication::translate("EditLibraryDialog", "\350\274\235\n"
"\345\272\246", nullptr));
        label_11->setText(QCoreApplication::translate("EditLibraryDialog", "\351\240\230\345\237\237\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("EditLibraryDialog", "\351\240\230\345\237\237\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_13->setText(QCoreApplication::translate("EditLibraryDialog", "\351\240\230\345\237\237\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_14->setText(QCoreApplication::translate("EditLibraryDialog", "\351\240\230\345\237\237\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_32->setText(QCoreApplication::translate("EditLibraryDialog", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        label_58->setText(QCoreApplication::translate("EditLibraryDialog", "\351\231\220\347\225\214\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_59->setText(QCoreApplication::translate("EditLibraryDialog", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210", nullptr));
        label_63->setText(QCoreApplication::translate("EditLibraryDialog", "<html><head/><body><p>\347\224\237</p><p>\346\210\220</p></body></html>", nullptr));
        comboBoxAdaptedPriority->setItemText(0, QCoreApplication::translate("EditLibraryDialog", "\345\205\250\343\201\246\343\201\253\351\201\251\347\224\250", nullptr));
        comboBoxAdaptedPriority->setItemText(1, QCoreApplication::translate("EditLibraryDialog", "Global", nullptr));
        comboBoxAdaptedPriority->setItemText(2, QCoreApplication::translate("EditLibraryDialog", "High", nullptr));
        comboBoxAdaptedPriority->setItemText(3, QCoreApplication::translate("EditLibraryDialog", "Middle", nullptr));
        comboBoxAdaptedPriority->setItemText(4, QCoreApplication::translate("EditLibraryDialog", "Low", nullptr));

        label_60->setText(QCoreApplication::translate("EditLibraryDialog", "\343\202\250\343\203\252\343\202\242\343\201\256\347\250\256\351\241\236", nullptr));
        checkBoxPickUpEdge->setText(QCoreApplication::translate("EditLibraryDialog", "\343\202\250\343\203\203\343\202\270\343\202\222\346\212\275\345\207\272\343\201\231\343\202\213\343\203\242\343\203\274\343\203\211", nullptr));
        label_61->setText(QCoreApplication::translate("EditLibraryDialog", "\343\202\250\343\203\203\343\202\270\346\212\275\345\207\272\343\201\231\343\202\213\346\234\200\344\275\216\343\201\256\350\274\235\345\272\246\345\201\217\345\267\256", nullptr));
        label_62->setText(QCoreApplication::translate("EditLibraryDialog", "\347\233\270\344\272\222\347\233\270\351\226\242\345\200\244\343\201\214\343\201\223\343\202\214\344\273\245\344\270\212\343\201\256\346\231\202\343\200\201\347\224\237\346\210\220\343\201\227\343\201\252\343\201\204", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272", nullptr));
        label_87->setText(QCoreApplication::translate("EditLibraryDialog", "<html><head/><body><p>\345\256\237</p><p>\350\241\214</p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("EditLibraryDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_3->setText(QCoreApplication::translate("EditLibraryDialog", "\345\272\203\345\237\237\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_21->setText(QCoreApplication::translate("EditLibraryDialog", "\343\202\260\343\203\253\343\203\274\343\203\227\343\202\265\343\202\244\343\202\272", nullptr));
        checkBoxKeepBW->setText(QCoreApplication::translate("EditLibraryDialog", "Keep Block/White", nullptr));
        label_22->setText(QCoreApplication::translate("EditLibraryDialog", "Closer rate", nullptr));
        label_23->setText(QCoreApplication::translate("EditLibraryDialog", "Small search dot", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("EditLibraryDialog", "\345\256\237\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryDialog: public Ui_EditLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYDIALOG_H
