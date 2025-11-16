/********************************************************************************
** Form generated from reading UI file 'EditHoleWallInspectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITHOLEWALLINSPECTIONDIALOG_H
#define UI_EDITHOLEWALLINSPECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditHoleWallInspectionDialog
{
public:
    QFrame *frameLibFolder;
    QPushButton *ButtonLibDelete;
    QToolButton *toolButtonInspect;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QPushButton *ButtonLibSave;
    QLabel *label_10;
    QTableWidget *tableWidgetLibList;
    QFrame *frameGenLayer;
    QPushButton *pushButtonClose;
    QPushButton *ButtonLibNew;
    QToolButton *toolButtonPickup;
    QPushButton *ButtonLibSaveNew;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QFrame *frame_15;
    QSpinBox *EditMinBlockSize;
    QLabel *label_58;
    QSpinBox *EditMaxBlockSize;
    QLabel *label_59;
    QSpinBox *EditMinBlockDots;
    QLabel *label_60;
    QSpinBox *EditMaxBlockDots;
    QLabel *label_61;
    QLabel *label_63;
    QFrame *frame_5;
    QLabel *label_15;
    QSpinBox *EditNoiseSize;
    QLabel *label_53;
    QLabel *label_17;
    QSpinBox *EditNoiseSizePinHole;
    QSpinBox *EditSpaceToOutline;
    QLabel *label_18;
    QFrame *frame_2;
    QLabel *label_7;
    QSpinBox *EditPickupL;
    QLabel *label_8;
    QSpinBox *EditPickupH;
    QLabel *label_30;
    QWidget *page_2;
    QFrame *frame_29;
    QLabel *label_92;
    QFrame *frame_30;
    QLabel *label_93;
    QSpinBox *EditSearchDot;
    QLabel *label_32;
    QLabel *label_24;
    QSpinBox *EditNGSize;
    QFrame *framePickLayer;
    QLineEdit *EditLibName;
    QLabel *label_9;

    void setupUi(QDialog *EditHoleWallInspectionDialog)
    {
        if (EditHoleWallInspectionDialog->objectName().isEmpty())
            EditHoleWallInspectionDialog->setObjectName("EditHoleWallInspectionDialog");
        EditHoleWallInspectionDialog->resize(648, 617);
        frameLibFolder = new QFrame(EditHoleWallInspectionDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 30, 191, 211));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonLibDelete = new QPushButton(EditHoleWallInspectionDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(310, 530, 101, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibDelete->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon);
        toolButtonInspect = new QToolButton(EditHoleWallInspectionDialog);
        toolButtonInspect->setObjectName("toolButtonInspect");
        toolButtonInspect->setGeometry(QRect(450, 10, 141, 31));
        toolButtonInspect->setCheckable(true);
        toolButtonInspect->setAutoExclusive(true);
        EditLibID = new QLineEdit(EditHoleWallInspectionDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(300, 50, 81, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(EditHoleWallInspectionDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(250, 50, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLibSave = new QPushButton(EditHoleWallInspectionDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(540, 530, 101, 31));
        ButtonLibSave->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon1);
        label_10 = new QLabel(EditHoleWallInspectionDialog);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(210, 90, 381, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setTextFormat(Qt::AutoText);
        label_10->setAlignment(Qt::AlignCenter);
        tableWidgetLibList = new QTableWidget(EditHoleWallInspectionDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 250, 191, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameGenLayer = new QFrame(EditHoleWallInspectionDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(210, 160, 381, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        pushButtonClose = new QPushButton(EditHoleWallInspectionDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(540, 570, 101, 31));
        pushButtonClose->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon2);
        ButtonLibNew = new QPushButton(EditHoleWallInspectionDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(190, 530, 111, 31));
        ButtonLibNew->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon3);
        toolButtonPickup = new QToolButton(EditHoleWallInspectionDialog);
        toolButtonPickup->setObjectName("toolButtonPickup");
        toolButtonPickup->setGeometry(QRect(250, 10, 141, 31));
        toolButtonPickup->setCheckable(true);
        toolButtonPickup->setChecked(true);
        toolButtonPickup->setAutoExclusive(true);
        ButtonLibSaveNew = new QPushButton(EditHoleWallInspectionDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(420, 530, 111, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon4);
        stackedWidget = new QStackedWidget(EditHoleWallInspectionDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(210, 190, 431, 321));
        page = new QWidget();
        page->setObjectName("page");
        frame_15 = new QFrame(page);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(10, 80, 421, 111));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        EditMinBlockSize = new QSpinBox(frame_15);
        EditMinBlockSize->setObjectName("EditMinBlockSize");
        EditMinBlockSize->setGeometry(QRect(300, 10, 81, 22));
        EditMinBlockSize->setMaximum(1000000);
        label_58 = new QLabel(frame_15);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(40, 30, 251, 21));
        label_58->setFrameShape(QFrame::Panel);
        label_58->setFrameShadow(QFrame::Sunken);
        label_58->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockSize = new QSpinBox(frame_15);
        EditMaxBlockSize->setObjectName("EditMaxBlockSize");
        EditMaxBlockSize->setGeometry(QRect(300, 30, 81, 22));
        EditMaxBlockSize->setMaximum(1000000);
        label_59 = new QLabel(frame_15);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(40, 10, 251, 21));
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinBlockDots = new QSpinBox(frame_15);
        EditMinBlockDots->setObjectName("EditMinBlockDots");
        EditMinBlockDots->setGeometry(QRect(300, 60, 101, 22));
        EditMinBlockDots->setMaximum(2000000000);
        label_60 = new QLabel(frame_15);
        label_60->setObjectName("label_60");
        label_60->setGeometry(QRect(40, 60, 251, 21));
        label_60->setFrameShape(QFrame::Panel);
        label_60->setFrameShadow(QFrame::Sunken);
        label_60->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockDots = new QSpinBox(frame_15);
        EditMaxBlockDots->setObjectName("EditMaxBlockDots");
        EditMaxBlockDots->setGeometry(QRect(300, 80, 101, 22));
        EditMaxBlockDots->setMaximum(2000000000);
        EditMaxBlockDots->setValue(2000000000);
        label_61 = new QLabel(frame_15);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(40, 80, 251, 21));
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63 = new QLabel(frame_15);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(0, 0, 31, 111));
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Raised);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63->setIndent(1);
        frame_5 = new QFrame(page);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 200, 421, 91));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Sunken);
        label_15 = new QLabel(frame_5);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(40, 10, 301, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSize = new QSpinBox(frame_5);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(350, 10, 61, 23));
        QFont font2;
        font2.setPointSize(9);
        EditNoiseSize->setFont(font2);
        label_53 = new QLabel(frame_5);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(0, 0, 31, 91));
        label_53->setFrameShape(QFrame::Panel);
        label_53->setFrameShadow(QFrame::Raised);
        label_53->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_53->setIndent(1);
        label_17 = new QLabel(frame_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(40, 30, 301, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSizePinHole = new QSpinBox(frame_5);
        EditNoiseSizePinHole->setObjectName("EditNoiseSizePinHole");
        EditNoiseSizePinHole->setGeometry(QRect(350, 30, 61, 23));
        EditNoiseSizePinHole->setFont(font2);
        EditSpaceToOutline = new QSpinBox(frame_5);
        EditSpaceToOutline->setObjectName("EditSpaceToOutline");
        EditSpaceToOutline->setGeometry(QRect(350, 60, 61, 23));
        EditSpaceToOutline->setFont(font2);
        label_18 = new QLabel(frame_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(40, 60, 301, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(page);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 421, 61));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(40, 10, 251, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(frame_2);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(300, 10, 61, 22));
        EditPickupL->setMaximum(255);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(40, 30, 241, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(frame_2);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(300, 30, 61, 22));
        EditPickupH->setMaximum(255);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(0, 0, 31, 61));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Raised);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30->setIndent(1);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        frame_29 = new QFrame(page_2);
        frame_29->setObjectName("frame_29");
        frame_29->setGeometry(QRect(0, 0, 421, 71));
        frame_29->setFrameShape(QFrame::StyledPanel);
        frame_29->setFrameShadow(QFrame::Sunken);
        label_92 = new QLabel(frame_29);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(0, 0, 20, 71));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Raised);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_92->setIndent(1);
        frame_30 = new QFrame(frame_29);
        frame_30->setObjectName("frame_30");
        frame_30->setGeometry(QRect(10, 120, 371, 101));
        frame_30->setFrameShape(QFrame::StyledPanel);
        frame_30->setFrameShadow(QFrame::Sunken);
        label_93 = new QLabel(frame_30);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(0, 0, 20, 61));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Raised);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_93->setIndent(1);
        EditSearchDot = new QSpinBox(frame_29);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(300, 40, 71, 20));
        EditSearchDot->setMaximum(99999999);
        label_32 = new QLabel(frame_29);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(40, 40, 251, 20));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_24 = new QLabel(frame_29);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(40, 10, 251, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNGSize = new QSpinBox(frame_29);
        EditNGSize->setObjectName("EditNGSize");
        EditNGSize->setGeometry(QRect(300, 10, 71, 20));
        EditNGSize->setMinimum(-255);
        EditNGSize->setMaximum(255);
        stackedWidget->addWidget(page_2);
        framePickLayer = new QFrame(EditHoleWallInspectionDialog);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(210, 110, 381, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        EditLibName = new QLineEdit(EditHoleWallInspectionDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(380, 50, 211, 31));
        EditLibName->setFont(font1);
        label_9 = new QLabel(EditHoleWallInspectionDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(210, 140, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);

        retranslateUi(EditHoleWallInspectionDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditHoleWallInspectionDialog);
    } // setupUi

    void retranslateUi(QDialog *EditHoleWallInspectionDialog)
    {
        EditHoleWallInspectionDialog->setWindowTitle(QCoreApplication::translate("EditHoleWallInspectionDialog", "Dialog", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "Delete", nullptr));
        toolButtonInspect->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\346\244\234\346\237\273", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\345\220\215\347\247\260", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "Update", nullptr));
        label_10->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "Name", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "Clear new", nullptr));
        toolButtonPickup->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\347\224\237\346\210\220", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "Save New", nullptr));
        label_58->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_59->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_60->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_61->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_63->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        label_15->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272 \345\255\244\347\253\213\347\202\271\345\211\212\351\231\244", nullptr));
        label_53->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\347\224\237\n"
"\346\210\220", nullptr));
        label_17->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272\343\200\200\343\203\224\343\203\263\343\203\233\343\203\274\343\203\253\345\211\212\351\231\244", nullptr));
        label_18->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\350\274\252\351\203\255\343\201\213\343\202\211\343\201\256\351\226\223\351\232\224", nullptr));
        label_7->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        label_8->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        label_30->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\350\274\235\n"
"\345\272\246", nullptr));
        label_92->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\347\251\264", nullptr));
        label_93->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\350\274\235\n"
"\345\272\246", nullptr));
        label_32->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_24->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "NG\343\202\265\343\202\244\343\202\272", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "Library Name", nullptr));
        label_9->setText(QCoreApplication::translate("EditHoleWallInspectionDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditHoleWallInspectionDialog: public Ui_EditHoleWallInspectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITHOLEWALLINSPECTIONDIALOG_H
