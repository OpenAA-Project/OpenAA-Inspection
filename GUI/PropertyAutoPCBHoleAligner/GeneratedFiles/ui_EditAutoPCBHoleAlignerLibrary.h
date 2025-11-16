/********************************************************************************
** Form generated from reading UI file 'EditAutoPCBHoleAlignerLibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITAUTOPCBHOLEALIGNERLIBRARY_H
#define UI_EDITAUTOPCBHOLEALIGNERLIBRARY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
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

class Ui_EditAutoPCBHoleAlignerLibrary
{
public:
    QFrame *frameThreshold;
    QLabel *label_8;
    QPushButton *pushButtonAddAllColor;
    QLabel *label_25;
    QLabel *label_26;
    QSpinBox *EditThresholdDiff;
    QPushButton *ButtonLibSaveNew;
    QTableWidget *tableWidgetLibList;
    QLabel *label_7;
    QCheckBox *checkBoxCheckOutside;
    QSpinBox *EditExpandForPickup;
    QListWidget *listWidgetBaseColor;
    QLabel *label_22;
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
    QPushButton *ButtonLibNew;
    QLabel *label_27;
    QLabel *label_23;
    QCheckBox *checkBoxStartupExecute;
    QPushButton *ButtonLibDelete;
    QFrame *frameLibFolder;
    QLabel *label_24;
    QSpinBox *EditMaxDiameter;
    QLabel *label_28;
    QLineEdit *EditLibName;
    QSpinBox *EditFringeDot;
    QSpinBox *EditMinDiameter;
    QPushButton *pushButton;
    QSpinBox *EditMaxSearch;
    QListWidget *listWidgetEliminatedColor;
    QLabel *label_4;
    QPushButton *ButtonLibSave;
    QLineEdit *EditLibID;

    void setupUi(QDialog *EditAutoPCBHoleAlignerLibrary)
    {
        if (EditAutoPCBHoleAlignerLibrary->objectName().isEmpty())
            EditAutoPCBHoleAlignerLibrary->setObjectName("EditAutoPCBHoleAlignerLibrary");
        EditAutoPCBHoleAlignerLibrary->resize(897, 785);
        frameThreshold = new QFrame(EditAutoPCBHoleAlignerLibrary);
        frameThreshold->setObjectName("frameThreshold");
        frameThreshold->setGeometry(QRect(10, 290, 271, 251));
        frameThreshold->setFrameShape(QFrame::StyledPanel);
        frameThreshold->setFrameShadow(QFrame::Raised);
        label_8 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(290, 450, 71, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonAddAllColor = new QPushButton(EditAutoPCBHoleAlignerLibrary);
        pushButtonAddAllColor->setObjectName("pushButtonAddAllColor");
        pushButtonAddAllColor->setGeometry(QRect(290, 380, 101, 41));
        label_25 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 670, 131, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_26 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 270, 271, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditThresholdDiff = new QSpinBox(EditAutoPCBHoleAlignerLibrary);
        EditThresholdDiff->setObjectName("EditThresholdDiff");
        EditThresholdDiff->setGeometry(QRect(370, 580, 61, 22));
        EditThresholdDiff->setMaximum(255);
        ButtonLibSaveNew = new QPushButton(EditAutoPCBHoleAlignerLibrary);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(230, 710, 111, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibSaveNew->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon);
        tableWidgetLibList = new QTableWidget(EditAutoPCBHoleAlignerLibrary);
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
        label_7 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(290, 290, 71, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxCheckOutside = new QCheckBox(EditAutoPCBHoleAlignerLibrary);
        checkBoxCheckOutside->setObjectName("checkBoxCheckOutside");
        checkBoxCheckOutside->setGeometry(QRect(210, 610, 231, 20));
        EditExpandForPickup = new QSpinBox(EditAutoPCBHoleAlignerLibrary);
        EditExpandForPickup->setObjectName("EditExpandForPickup");
        EditExpandForPickup->setGeometry(QRect(140, 550, 61, 22));
        EditExpandForPickup->setMaximum(255);
        listWidgetBaseColor = new QListWidget(EditAutoPCBHoleAlignerLibrary);
        listWidgetBaseColor->setObjectName("listWidgetBaseColor");
        listWidgetBaseColor->setGeometry(QRect(290, 310, 71, 61));
        label_22 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 550, 131, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget = new QTabWidget(EditAutoPCBHoleAlignerLibrary);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(440, 220, 441, 551));
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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon1);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 450, 161, 25));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon2);
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
        pushButtonSubPickupColor->setGeometry(QRect(24, 80, 91, 23));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSubPickupColor->setIcon(icon3);
        pushButtonAddPickupColor = new QPushButton(framePicked);
        pushButtonAddPickupColor->setObjectName("pushButtonAddPickupColor");
        pushButtonAddPickupColor->setGeometry(QRect(24, 50, 91, 23));
        pushButtonAddPickupColor->setIcon(icon2);
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
        pushButtonAddColorArea->setIcon(icon2);
        pushButtonEliminateColorArea = new QPushButton(tab_3);
        pushButtonEliminateColorArea->setObjectName("pushButtonEliminateColorArea");
        pushButtonEliminateColorArea->setGeometry(QRect(60, 400, 161, 25));
        pushButtonEliminateColorArea->setIcon(icon1);
        tabWidget->addTab(tab_3, QString());
        ButtonLibNew = new QPushButton(EditAutoPCBHoleAlignerLibrary);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 710, 111, 31));
        ButtonLibNew->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon4);
        label_27 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(240, 550, 131, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 610, 131, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxStartupExecute = new QCheckBox(EditAutoPCBHoleAlignerLibrary);
        checkBoxStartupExecute->setObjectName("checkBoxStartupExecute");
        checkBoxStartupExecute->setGeometry(QRect(30, 580, 181, 18));
        ButtonLibDelete = new QPushButton(EditAutoPCBHoleAlignerLibrary);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(130, 710, 91, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon5);
        frameLibFolder = new QFrame(EditAutoPCBHoleAlignerLibrary);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_24 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 640, 131, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxDiameter = new QSpinBox(EditAutoPCBHoleAlignerLibrary);
        EditMaxDiameter->setObjectName("EditMaxDiameter");
        EditMaxDiameter->setGeometry(QRect(140, 640, 61, 22));
        EditMaxDiameter->setMaximum(255);
        label_28 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(240, 580, 131, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(EditAutoPCBHoleAlignerLibrary);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 230, 211, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibName->setFont(font1);
        EditFringeDot = new QSpinBox(EditAutoPCBHoleAlignerLibrary);
        EditFringeDot->setObjectName("EditFringeDot");
        EditFringeDot->setGeometry(QRect(140, 670, 61, 22));
        EditFringeDot->setMaximum(255);
        EditMinDiameter = new QSpinBox(EditAutoPCBHoleAlignerLibrary);
        EditMinDiameter->setObjectName("EditMinDiameter");
        EditMinDiameter->setGeometry(QRect(140, 610, 61, 22));
        EditMinDiameter->setMaximum(255);
        pushButton = new QPushButton(EditAutoPCBHoleAlignerLibrary);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(350, 740, 91, 31));
        pushButton->setFont(font);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon6);
        EditMaxSearch = new QSpinBox(EditAutoPCBHoleAlignerLibrary);
        EditMaxSearch->setObjectName("EditMaxSearch");
        EditMaxSearch->setGeometry(QRect(370, 550, 61, 22));
        EditMaxSearch->setMaximum(255);
        listWidgetEliminatedColor = new QListWidget(EditAutoPCBHoleAlignerLibrary);
        listWidgetEliminatedColor->setObjectName("listWidgetEliminatedColor");
        listWidgetEliminatedColor->setGeometry(QRect(290, 470, 71, 61));
        label_4 = new QLabel(EditAutoPCBHoleAlignerLibrary);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(EditAutoPCBHoleAlignerLibrary);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(350, 710, 91, 31));
        ButtonLibSave->setFont(font);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon7);
        EditLibID = new QLineEdit(EditAutoPCBHoleAlignerLibrary);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 230, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);

        retranslateUi(EditAutoPCBHoleAlignerLibrary);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditAutoPCBHoleAlignerLibrary);
    } // setupUi

    void retranslateUi(QDialog *EditAutoPCBHoleAlignerLibrary)
    {
        EditAutoPCBHoleAlignerLibrary->setWindowTitle(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Dialog", nullptr));
        label_8->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\351\231\244\345\244\226\350\211\262", nullptr));
        pushButtonAddAllColor->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "<<\345\205\250\350\211\262\350\277\275\345\212\240", nullptr));
        label_25->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\345\221\250\347\270\201\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_26->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\347\251\264\343\201\256\350\211\262\346\214\207\345\256\232", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Save New", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Name", nullptr));
        label_7->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\350\277\275\345\212\240\350\211\262", nullptr));
        checkBoxCheckOutside->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\346\230\216\343\202\213\343\201\204\351\240\230\345\237\237\343\201\253\345\233\262\343\201\276\343\202\214\343\201\246\343\201\204\343\202\213\343\201\213\343\201\256\345\210\244\345\256\232", nullptr));
        label_22->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\347\251\264\351\240\230\345\237\237\350\206\250\345\274\265\351\207\217", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Add Color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\350\211\262\347\231\273\351\214\262\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        label_36->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\343\203\224\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        pushButtonSubPickupColor->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Sub =>", nullptr));
        pushButtonAddPickupColor->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Add =>", nullptr));
        label_37->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\343\203\224\343\202\257\343\202\273\343\203\253\346\212\275\345\207\272\350\211\262", nullptr));
        pushButtonAddColorArea->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Add Color", nullptr));
        pushButtonEliminateColorArea->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Eliminate color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\351\240\230\345\237\237\346\212\275\345\207\272\350\211\262", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Clear new", nullptr));
        label_27->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\345\221\250\345\233\262\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_23->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\346\234\200\345\260\217\347\233\264\345\276\204\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        checkBoxStartupExecute->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\343\203\207\343\203\225\343\202\251\343\203\253\343\203\210\343\201\247\345\256\237\350\241\214", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Delete", nullptr));
        label_24->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\346\234\200\345\244\247\347\233\264\345\276\204\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_28->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\350\274\235\345\272\246\345\244\211\345\214\226\351\226\276\345\200\244", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Library Name", nullptr));
        pushButton->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_4->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "\345\220\215\347\247\260", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "Update", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditAutoPCBHoleAlignerLibrary", "12345", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditAutoPCBHoleAlignerLibrary: public Ui_EditAutoPCBHoleAlignerLibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITAUTOPCBHOLEALIGNERLIBRARY_H
