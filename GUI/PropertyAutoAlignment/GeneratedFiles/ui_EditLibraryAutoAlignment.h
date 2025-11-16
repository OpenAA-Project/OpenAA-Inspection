/********************************************************************************
** Form generated from reading UI file 'EditLibraryAutoAlignment.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYAUTOALIGNMENT_H
#define UI_EDITLIBRARYAUTOALIGNMENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditLibraryAutoAlignmentClass
{
public:
    QFrame *frameThreshold;
    QFrame *frameLibFolder;
    QLineEdit *EditLibName;
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonLibSave;
    QLineEdit *EditLibID;
    QPushButton *pushButton;
    QPushButton *ButtonLibNew;
    QLabel *label_4;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibSaveNew;
    QSpinBox *EditPicoShift;
    QLabel *label_22;
    QListWidget *listWidgetEliminatedColor;
    QLabel *label_8;
    QLabel *label_7;
    QListWidget *listWidgetBaseColor;
    QPushButton *pushButtonAddAllColor;
    QCheckBox *checkBoxStartupExecute;
    QLabel *label_23;
    QSpinBox *EditPriority;
    QLabel *label_24;
    QSpinBox *EditPickupExpansion;
    QSpinBox *EditNoiseShrink;
    QLabel *label_25;
    QSpinBox *EditExpandForPickup;
    QLabel *label_26;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QWidget *tab_2;
    QFrame *framePicked;
    QLabel *label_36;
    QPushButton *pushButtonSubPickupColor;
    QPushButton *pushButtonAddPickupColor;
    QSpinBox *spinBoxMerginAddPickupColor;
    QSpinBox *spinBoxMerginSubPickupColor;
    QLabel *label_37;
    QFrame *framePickupColor;
    QWidget *tab_3;
    QFrame *frameShowColorSmples;
    QPushButton *pushButtonAddColorArea;
    QPushButton *pushButtonEliminateColorArea;
    QLabel *label_27;
    QSpinBox *EditMinDot;
    QSpinBox *EditFringeWidth;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBoxAdptedMatchingRate;
    QDoubleSpinBox *doubleSpinBoxCompletelyMatchingRate;

    void setupUi(QDialog *EditLibraryAutoAlignmentClass)
    {
        if (EditLibraryAutoAlignmentClass->objectName().isEmpty())
            EditLibraryAutoAlignmentClass->setObjectName("EditLibraryAutoAlignmentClass");
        EditLibraryAutoAlignmentClass->resize(820, 847);
        frameThreshold = new QFrame(EditLibraryAutoAlignmentClass);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(10, 270, 271, 251));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Raised);
        frameLibFolder = new QFrame(EditLibraryAutoAlignmentClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibName = new QLineEdit(EditLibraryAutoAlignmentClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 230, 211, 31));
        QFont font;
        font.setPointSize(12);
        EditLibName->setFont(font);
        tableWidgetLibList = new QTableWidget(EditLibraryAutoAlignmentClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(240, 10, 221, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonLibSave = new QPushButton(EditLibraryAutoAlignmentClass);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(290, 770, 71, 31));
        QFont font1;
        font1.setPointSize(11);
        ButtonLibSave->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon);
        EditLibID = new QLineEdit(EditLibraryAutoAlignmentClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        pushButton = new QPushButton(EditLibraryAutoAlignmentClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(290, 800, 71, 31));
        pushButton->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon1);
        ButtonLibNew = new QPushButton(EditLibraryAutoAlignmentClass);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 770, 91, 31));
        ButtonLibNew->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon2);
        label_4 = new QLabel(EditLibraryAutoAlignmentClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibDelete = new QPushButton(EditLibraryAutoAlignmentClass);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(110, 770, 71, 31));
        ButtonLibDelete->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon3);
        ButtonLibSaveNew = new QPushButton(EditLibraryAutoAlignmentClass);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(190, 770, 91, 31));
        ButtonLibSaveNew->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon4);
        EditPicoShift = new QSpinBox(EditLibraryAutoAlignmentClass);
        EditPicoShift->setObjectName("EditPicoShift");
        EditPicoShift->setGeometry(QRect(130, 530, 61, 22));
        EditPicoShift->setMaximum(255);
        label_22 = new QLabel(EditLibraryAutoAlignmentClass);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 530, 121, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetEliminatedColor = new QListWidget(EditLibraryAutoAlignmentClass);
        listWidgetEliminatedColor->setObjectName("listWidgetEliminatedColor");
        listWidgetEliminatedColor->setGeometry(QRect(290, 450, 61, 61));
        label_8 = new QLabel(EditLibraryAutoAlignmentClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(290, 430, 61, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(EditLibraryAutoAlignmentClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(290, 270, 61, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetBaseColor = new QListWidget(EditLibraryAutoAlignmentClass);
        listWidgetBaseColor->setObjectName("listWidgetBaseColor");
        listWidgetBaseColor->setGeometry(QRect(290, 290, 61, 61));
        pushButtonAddAllColor = new QPushButton(EditLibraryAutoAlignmentClass);
        pushButtonAddAllColor->setObjectName("pushButtonAddAllColor");
        pushButtonAddAllColor->setGeometry(QRect(290, 360, 71, 41));
        checkBoxStartupExecute = new QCheckBox(EditLibraryAutoAlignmentClass);
        checkBoxStartupExecute->setObjectName("checkBoxStartupExecute");
        checkBoxStartupExecute->setGeometry(QRect(30, 560, 131, 18));
        label_23 = new QLabel(EditLibraryAutoAlignmentClass);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 590, 121, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(EditLibraryAutoAlignmentClass);
        EditPriority->setObjectName("EditPriority");
        EditPriority->setGeometry(QRect(130, 590, 61, 22));
        EditPriority->setMaximum(255);
        label_24 = new QLabel(EditLibraryAutoAlignmentClass);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 620, 121, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupExpansion = new QSpinBox(EditLibraryAutoAlignmentClass);
        EditPickupExpansion->setObjectName("EditPickupExpansion");
        EditPickupExpansion->setGeometry(QRect(130, 620, 61, 22));
        EditPickupExpansion->setMaximum(255);
        EditNoiseShrink = new QSpinBox(EditLibraryAutoAlignmentClass);
        EditNoiseShrink->setObjectName("EditNoiseShrink");
        EditNoiseShrink->setGeometry(QRect(130, 650, 61, 22));
        EditNoiseShrink->setMaximum(255);
        label_25 = new QLabel(EditLibraryAutoAlignmentClass);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 650, 121, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditExpandForPickup = new QSpinBox(EditLibraryAutoAlignmentClass);
        EditExpandForPickup->setObjectName("EditExpandForPickup");
        EditExpandForPickup->setGeometry(QRect(130, 680, 61, 22));
        EditExpandForPickup->setMaximum(255);
        label_26 = new QLabel(EditLibraryAutoAlignmentClass);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 680, 121, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget = new QTabWidget(EditLibraryAutoAlignmentClass);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(370, 220, 441, 551));
        tab = new QWidget();
        tab->setObjectName("tab");
        frameColorSample = new QFrame(tab);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(10, 10, 205, 511));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 480, 161, 25));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon5);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 450, 161, 25));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon6);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        framePicked = new QFrame(tab_2);
        framePicked->setObjectName("framePicked");
        framePicked->setGeometry(QRect(10, 10, 191, 111));
        framePicked->setFrameShape(QFrame::StyledPanel);
        framePicked->setFrameShadow(QFrame::Sunken);
        label_36 = new QLabel(framePicked);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(0, 0, 191, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSubPickupColor = new QPushButton(framePicked);
        pushButtonSubPickupColor->setObjectName("pushButtonSubPickupColor");
        pushButtonSubPickupColor->setGeometry(QRect(40, 80, 75, 23));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSubPickupColor->setIcon(icon7);
        pushButtonAddPickupColor = new QPushButton(framePicked);
        pushButtonAddPickupColor->setObjectName("pushButtonAddPickupColor");
        pushButtonAddPickupColor->setGeometry(QRect(40, 50, 75, 23));
        pushButtonAddPickupColor->setIcon(icon6);
        spinBoxMerginAddPickupColor = new QSpinBox(framePicked);
        spinBoxMerginAddPickupColor->setObjectName("spinBoxMerginAddPickupColor");
        spinBoxMerginAddPickupColor->setGeometry(QRect(120, 50, 61, 22));
        spinBoxMerginAddPickupColor->setValue(10);
        spinBoxMerginSubPickupColor = new QSpinBox(framePicked);
        spinBoxMerginSubPickupColor->setObjectName("spinBoxMerginSubPickupColor");
        spinBoxMerginSubPickupColor->setGeometry(QRect(120, 80, 61, 22));
        spinBoxMerginSubPickupColor->setValue(10);
        label_37 = new QLabel(framePicked);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(120, 30, 64, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        framePickupColor = new QFrame(framePicked);
        framePickupColor->setObjectName("framePickupColor");
        framePickupColor->setGeometry(QRect(10, 30, 21, 71));
        framePickupColor->setFrameShape(QFrame::NoFrame);
        framePickupColor->setFrameShadow(QFrame::Plain);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        frameShowColorSmples = new QFrame(tab_3);
        frameShowColorSmples->setObjectName("frameShowColorSmples");
        frameShowColorSmples->setGeometry(QRect(10, 10, 415, 355));
        frameShowColorSmples->setFrameShape(QFrame::NoFrame);
        frameShowColorSmples->setFrameShadow(QFrame::Plain);
        pushButtonAddColorArea = new QPushButton(tab_3);
        pushButtonAddColorArea->setObjectName("pushButtonAddColorArea");
        pushButtonAddColorArea->setGeometry(QRect(60, 370, 161, 25));
        pushButtonAddColorArea->setIcon(icon6);
        pushButtonEliminateColorArea = new QPushButton(tab_3);
        pushButtonEliminateColorArea->setObjectName("pushButtonEliminateColorArea");
        pushButtonEliminateColorArea->setGeometry(QRect(60, 400, 161, 25));
        pushButtonEliminateColorArea->setIcon(icon5);
        tabWidget->addTab(tab_3, QString());
        label_27 = new QLabel(EditLibraryAutoAlignmentClass);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(210, 530, 81, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinDot = new QSpinBox(EditLibraryAutoAlignmentClass);
        EditMinDot->setObjectName("EditMinDot");
        EditMinDot->setGeometry(QRect(290, 530, 71, 22));
        EditMinDot->setMaximum(99999);
        EditFringeWidth = new QSpinBox(EditLibraryAutoAlignmentClass);
        EditFringeWidth->setObjectName("EditFringeWidth");
        EditFringeWidth->setGeometry(QRect(300, 570, 61, 22));
        EditFringeWidth->setMaximum(255);
        label_28 = new QLabel(EditLibraryAutoAlignmentClass);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(210, 570, 91, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_29 = new QLabel(EditLibraryAutoAlignmentClass);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 710, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(EditLibraryAutoAlignmentClass);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 740, 121, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxAdptedMatchingRate = new QDoubleSpinBox(EditLibraryAutoAlignmentClass);
        doubleSpinBoxAdptedMatchingRate->setObjectName("doubleSpinBoxAdptedMatchingRate");
        doubleSpinBoxAdptedMatchingRate->setGeometry(QRect(130, 710, 62, 22));
        doubleSpinBoxAdptedMatchingRate->setDecimals(4);
        doubleSpinBoxCompletelyMatchingRate = new QDoubleSpinBox(EditLibraryAutoAlignmentClass);
        doubleSpinBoxCompletelyMatchingRate->setObjectName("doubleSpinBoxCompletelyMatchingRate");
        doubleSpinBoxCompletelyMatchingRate->setGeometry(QRect(130, 740, 62, 22));
        doubleSpinBoxCompletelyMatchingRate->setDecimals(4);

        retranslateUi(EditLibraryAutoAlignmentClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditLibraryAutoAlignmentClass);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryAutoAlignmentClass)
    {
        EditLibraryAutoAlignmentClass->setWindowTitle(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "EditLibraryAutoAlignment", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Library Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Name", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Update", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "12345", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Clear new", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\345\220\215\347\247\260", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Delete", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Save New", nullptr));
        label_22->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\350\251\263\347\264\260\351\240\230\345\237\237\343\202\267\343\203\225\343\203\210\351\207\217", nullptr));
        label_8->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\351\231\244\345\244\226\350\211\262", nullptr));
        label_7->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\350\277\275\345\212\240\350\211\262", nullptr));
        pushButtonAddAllColor->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "<<\345\205\250\350\211\262\350\277\275\345\212\240", nullptr));
        checkBoxStartupExecute->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\343\203\207\343\203\225\343\202\251\343\203\253\343\203\210\343\201\247\345\256\237\350\241\214", nullptr));
        label_23->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\345\204\252\345\205\210\345\272\246\347\225\252\345\217\267", nullptr));
        label_24->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\351\201\267\347\247\273\345\271\205", nullptr));
        label_25->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\347\224\237\346\210\220\346\231\202\343\203\216\343\202\244\343\202\272\351\231\244\345\216\273\343\203\211\343\203\203\343\203\210", nullptr));
        label_26->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\346\212\275\345\207\272\351\240\230\345\237\237\343\201\256\350\206\250\345\274\265\351\207\217", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Add Color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\350\211\262\347\231\273\351\214\262\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        label_36->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\343\203\224\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        pushButtonSubPickupColor->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Sub =>", nullptr));
        pushButtonAddPickupColor->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Add =>", nullptr));
        label_37->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\343\203\224\343\202\257\343\202\273\343\203\253\346\212\275\345\207\272\350\211\262", nullptr));
        pushButtonAddColorArea->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Add Color", nullptr));
        pushButtonEliminateColorArea->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "Eliminate color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\351\240\230\345\237\237\346\212\275\345\207\272\350\211\262", nullptr));
        label_27->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\346\234\200\345\260\217\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_28->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\345\221\250\347\270\201\343\203\211\343\203\203\343\203\210\345\271\205", nullptr));
        label_29->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\346\216\241\347\224\250\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_30->setText(QCoreApplication::translate("EditLibraryAutoAlignmentClass", "\346\234\200\347\265\202\346\261\272\345\256\232\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryAutoAlignmentClass: public Ui_EditLibraryAutoAlignmentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYAUTOALIGNMENT_H
