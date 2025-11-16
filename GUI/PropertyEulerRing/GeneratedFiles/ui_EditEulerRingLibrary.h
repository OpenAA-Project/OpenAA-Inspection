/********************************************************************************
** Form generated from reading UI file 'EditEulerRingLibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITEULERRINGLIBRARY_H
#define UI_EDITEULERRINGLIBRARY_H

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

class Ui_EditEulerRingLibraryClass
{
public:
    QPushButton *ButtonLibSave;
    QPushButton *pushButtonClose;
    QTableWidget *tableWidgetLibList;
    QToolButton *toolButtonInspect;
    QLineEdit *EditLibName;
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
    QFrame *frame_18;
    QLabel *label_68;
    QFrame *frameGenerateH;
    QPushButton *pushButtonGColor;
    QFrame *frame_19;
    QLabel *label_70;
    QSpinBox *EditNoiseSize;
    QLabel *label_72;
    QSpinBox *EditExpandedDotToPad;
    QLabel *label_71;
    QFrame *frame_21;
    QLabel *label_69;
    QFrame *frameGenerateC;
    QPushButton *pushButtonCColor;
    QWidget *page_2;
    QFrame *frame_25;
    QLabel *label_86;
    QFrame *frame_26;
    QLabel *label_87;
    QSpinBox *EditAdjustBlack;
    QSpinBox *EditAdjustWhite;
    QLabel *label_88;
    QLabel *label_89;
    QFrame *frame_20;
    QLabel *label_73;
    QFrame *framePanel;
    QLabel *label_66;
    QSpinBox *EditMergin;
    QLabel *label_48;
    QSpinBox *EditExpandedDot;
    QPushButton *pushButtonNColor;
    QToolButton *toolButtonPickup;
    QPushButton *ButtonLibDelete;
    QFrame *frameLibFolder;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QPushButton *ButtonLibSaveNew;
    QPushButton *ButtonLibNew;

    void setupUi(QDialog *EditEulerRingLibraryClass)
    {
        if (EditEulerRingLibraryClass->objectName().isEmpty())
            EditEulerRingLibraryClass->setObjectName("EditEulerRingLibraryClass");
        EditEulerRingLibraryClass->resize(604, 573);
        ButtonLibSave = new QPushButton(EditEulerRingLibraryClass);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(510, 490, 81, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibSave->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon);
        pushButtonClose = new QPushButton(EditEulerRingLibraryClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(510, 530, 81, 31));
        pushButtonClose->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        tableWidgetLibList = new QTableWidget(EditEulerRingLibraryClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 190, 191, 181));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        toolButtonInspect = new QToolButton(EditEulerRingLibraryClass);
        toolButtonInspect->setObjectName("toolButtonInspect");
        toolButtonInspect->setGeometry(QRect(450, 10, 141, 31));
        toolButtonInspect->setCheckable(true);
        toolButtonInspect->setAutoExclusive(true);
        EditLibName = new QLineEdit(EditEulerRingLibraryClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(380, 50, 211, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibName->setFont(font1);
        stackedWidget = new QStackedWidget(EditEulerRingLibraryClass);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(210, 80, 381, 401));
        page = new QWidget();
        page->setObjectName("page");
        frame_15 = new QFrame(page);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(0, 210, 371, 111));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        EditMinBlockSize = new QSpinBox(frame_15);
        EditMinBlockSize->setObjectName("EditMinBlockSize");
        EditMinBlockSize->setGeometry(QRect(160, 10, 81, 22));
        EditMinBlockSize->setMaximum(1000000);
        label_58 = new QLabel(frame_15);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(30, 30, 111, 21));
        label_58->setFrameShape(QFrame::Panel);
        label_58->setFrameShadow(QFrame::Sunken);
        label_58->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockSize = new QSpinBox(frame_15);
        EditMaxBlockSize->setObjectName("EditMaxBlockSize");
        EditMaxBlockSize->setGeometry(QRect(160, 30, 81, 22));
        EditMaxBlockSize->setMaximum(1000000);
        label_59 = new QLabel(frame_15);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(30, 10, 111, 21));
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinBlockDots = new QSpinBox(frame_15);
        EditMinBlockDots->setObjectName("EditMinBlockDots");
        EditMinBlockDots->setGeometry(QRect(160, 60, 101, 22));
        EditMinBlockDots->setMaximum(2000000000);
        label_60 = new QLabel(frame_15);
        label_60->setObjectName("label_60");
        label_60->setGeometry(QRect(30, 60, 111, 21));
        label_60->setFrameShape(QFrame::Panel);
        label_60->setFrameShadow(QFrame::Sunken);
        label_60->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxBlockDots = new QSpinBox(frame_15);
        EditMaxBlockDots->setObjectName("EditMaxBlockDots");
        EditMaxBlockDots->setGeometry(QRect(160, 80, 101, 22));
        EditMaxBlockDots->setMaximum(2000000000);
        EditMaxBlockDots->setValue(2000000000);
        label_61 = new QLabel(frame_15);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(30, 80, 111, 21));
        label_61->setFrameShape(QFrame::Panel);
        label_61->setFrameShadow(QFrame::Sunken);
        label_61->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63 = new QLabel(frame_15);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(0, 0, 20, 111));
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Raised);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63->setIndent(1);
        frame_18 = new QFrame(page);
        frame_18->setObjectName("frame_18");
        frame_18->setGeometry(QRect(0, 0, 371, 101));
        frame_18->setFrameShape(QFrame::StyledPanel);
        frame_18->setFrameShadow(QFrame::Sunken);
        label_68 = new QLabel(frame_18);
        label_68->setObjectName("label_68");
        label_68->setGeometry(QRect(0, 0, 20, 101));
        label_68->setFrameShape(QFrame::Panel);
        label_68->setFrameShadow(QFrame::Raised);
        label_68->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_68->setIndent(1);
        frameGenerateH = new QFrame(frame_18);
        frameGenerateH->setObjectName("frameGenerateH");
        frameGenerateH->setGeometry(QRect(130, 0, 211, 101));
        frameGenerateH->setFrameShape(QFrame::NoFrame);
        frameGenerateH->setFrameShadow(QFrame::Raised);
        pushButtonGColor = new QPushButton(frame_18);
        pushButtonGColor->setObjectName("pushButtonGColor");
        pushButtonGColor->setGeometry(QRect(30, 50, 61, 40));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGColor->setIcon(icon2);
        frame_19 = new QFrame(page);
        frame_19->setObjectName("frame_19");
        frame_19->setGeometry(QRect(0, 330, 371, 71));
        frame_19->setFrameShape(QFrame::StyledPanel);
        frame_19->setFrameShadow(QFrame::Sunken);
        label_70 = new QLabel(frame_19);
        label_70->setObjectName("label_70");
        label_70->setGeometry(QRect(30, 10, 181, 21));
        label_70->setFrameShape(QFrame::Panel);
        label_70->setFrameShadow(QFrame::Sunken);
        label_70->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSize = new QSpinBox(frame_19);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(220, 10, 61, 23));
        QFont font2;
        font2.setPointSize(9);
        EditNoiseSize->setFont(font2);
        label_72 = new QLabel(frame_19);
        label_72->setObjectName("label_72");
        label_72->setGeometry(QRect(0, 0, 20, 61));
        label_72->setFrameShape(QFrame::Panel);
        label_72->setFrameShadow(QFrame::Raised);
        label_72->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_72->setIndent(1);
        EditExpandedDotToPad = new QSpinBox(frame_19);
        EditExpandedDotToPad->setObjectName("EditExpandedDotToPad");
        EditExpandedDotToPad->setGeometry(QRect(220, 40, 61, 23));
        EditExpandedDotToPad->setFont(font2);
        label_71 = new QLabel(frame_19);
        label_71->setObjectName("label_71");
        label_71->setGeometry(QRect(30, 40, 181, 21));
        label_71->setFrameShape(QFrame::Panel);
        label_71->setFrameShadow(QFrame::Sunken);
        label_71->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_21 = new QFrame(page);
        frame_21->setObjectName("frame_21");
        frame_21->setGeometry(QRect(0, 100, 371, 101));
        frame_21->setFrameShape(QFrame::StyledPanel);
        frame_21->setFrameShadow(QFrame::Sunken);
        label_69 = new QLabel(frame_21);
        label_69->setObjectName("label_69");
        label_69->setGeometry(QRect(0, 0, 20, 101));
        label_69->setFrameShape(QFrame::Panel);
        label_69->setFrameShadow(QFrame::Raised);
        label_69->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_69->setIndent(1);
        frameGenerateC = new QFrame(frame_21);
        frameGenerateC->setObjectName("frameGenerateC");
        frameGenerateC->setGeometry(QRect(130, 0, 211, 101));
        frameGenerateC->setFrameShape(QFrame::NoFrame);
        frameGenerateC->setFrameShadow(QFrame::Raised);
        pushButtonCColor = new QPushButton(frame_21);
        pushButtonCColor->setObjectName("pushButtonCColor");
        pushButtonCColor->setGeometry(QRect(30, 50, 61, 40));
        pushButtonCColor->setIcon(icon2);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        frame_25 = new QFrame(page_2);
        frame_25->setObjectName("frame_25");
        frame_25->setGeometry(QRect(0, 150, 371, 71));
        frame_25->setFrameShape(QFrame::StyledPanel);
        frame_25->setFrameShadow(QFrame::Sunken);
        label_86 = new QLabel(frame_25);
        label_86->setObjectName("label_86");
        label_86->setGeometry(QRect(0, 0, 20, 71));
        label_86->setFrameShape(QFrame::Panel);
        label_86->setFrameShadow(QFrame::Raised);
        label_86->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_86->setIndent(1);
        frame_26 = new QFrame(frame_25);
        frame_26->setObjectName("frame_26");
        frame_26->setGeometry(QRect(10, 120, 371, 101));
        frame_26->setFrameShape(QFrame::StyledPanel);
        frame_26->setFrameShadow(QFrame::Sunken);
        label_87 = new QLabel(frame_26);
        label_87->setObjectName("label_87");
        label_87->setGeometry(QRect(0, 0, 20, 61));
        label_87->setFrameShape(QFrame::Panel);
        label_87->setFrameShadow(QFrame::Raised);
        label_87->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_87->setIndent(1);
        EditAdjustBlack = new QSpinBox(frame_25);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(240, 10, 81, 22));
        EditAdjustBlack->setMaximum(255);
        EditAdjustWhite = new QSpinBox(frame_25);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(240, 40, 81, 22));
        EditAdjustWhite->setMaximum(255);
        label_88 = new QLabel(frame_25);
        label_88->setObjectName("label_88");
        label_88->setGeometry(QRect(30, 40, 201, 21));
        label_88->setFrameShape(QFrame::Panel);
        label_88->setFrameShadow(QFrame::Sunken);
        label_88->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_89 = new QLabel(frame_25);
        label_89->setObjectName("label_89");
        label_89->setGeometry(QRect(30, 10, 201, 21));
        label_89->setFrameShape(QFrame::Panel);
        label_89->setFrameShadow(QFrame::Sunken);
        label_89->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_20 = new QFrame(page_2);
        frame_20->setObjectName("frame_20");
        frame_20->setGeometry(QRect(0, 0, 371, 141));
        frame_20->setFrameShape(QFrame::StyledPanel);
        frame_20->setFrameShadow(QFrame::Sunken);
        label_73 = new QLabel(frame_20);
        label_73->setObjectName("label_73");
        label_73->setGeometry(QRect(0, 0, 20, 141));
        label_73->setFrameShape(QFrame::Panel);
        label_73->setFrameShadow(QFrame::Raised);
        label_73->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_73->setIndent(1);
        framePanel = new QFrame(frame_20);
        framePanel->setObjectName("framePanel");
        framePanel->setGeometry(QRect(150, 10, 211, 121));
        framePanel->setFrameShape(QFrame::NoFrame);
        framePanel->setFrameShadow(QFrame::Raised);
        label_66 = new QLabel(frame_20);
        label_66->setObjectName("label_66");
        label_66->setGeometry(QRect(40, 10, 70, 21));
        label_66->setFrameShape(QFrame::Panel);
        label_66->setFrameShadow(QFrame::Sunken);
        label_66->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMergin = new QSpinBox(frame_20);
        EditMergin->setObjectName("EditMergin");
        EditMergin->setGeometry(QRect(50, 30, 61, 22));
        EditMergin->setMaximum(99999999);
        label_48 = new QLabel(frame_20);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(40, 60, 71, 21));
        label_48->setFrameShape(QFrame::Panel);
        label_48->setFrameShadow(QFrame::Sunken);
        label_48->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditExpandedDot = new QSpinBox(frame_20);
        EditExpandedDot->setObjectName("EditExpandedDot");
        EditExpandedDot->setGeometry(QRect(50, 80, 61, 22));
        EditExpandedDot->setMaximum(99999999);
        pushButtonNColor = new QPushButton(frame_20);
        pushButtonNColor->setObjectName("pushButtonNColor");
        pushButtonNColor->setGeometry(QRect(40, 110, 77, 25));
        pushButtonNColor->setIcon(icon2);
        stackedWidget->addWidget(page_2);
        toolButtonPickup = new QToolButton(EditEulerRingLibraryClass);
        toolButtonPickup->setObjectName("toolButtonPickup");
        toolButtonPickup->setGeometry(QRect(250, 10, 141, 31));
        toolButtonPickup->setCheckable(true);
        toolButtonPickup->setChecked(true);
        toolButtonPickup->setAutoExclusive(true);
        ButtonLibDelete = new QPushButton(EditEulerRingLibraryClass);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(310, 490, 91, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon3);
        frameLibFolder = new QFrame(EditEulerRingLibraryClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 30, 191, 151));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(EditEulerRingLibraryClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(250, 50, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(EditEulerRingLibraryClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(300, 50, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        ButtonLibSaveNew = new QPushButton(EditEulerRingLibraryClass);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(410, 490, 91, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon4);
        ButtonLibNew = new QPushButton(EditEulerRingLibraryClass);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(210, 490, 91, 31));
        ButtonLibNew->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon5);

        retranslateUi(EditEulerRingLibraryClass);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EditEulerRingLibraryClass);
    } // setupUi

    void retranslateUi(QDialog *EditEulerRingLibraryClass)
    {
        EditEulerRingLibraryClass->setWindowTitle(QCoreApplication::translate("EditEulerRingLibraryClass", "EditEulerRingLibrary", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "Update", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "Name", nullptr));
        toolButtonInspect->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\346\244\234\346\237\273", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "Library Name", nullptr));
        label_58->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\343\202\265\343\202\244\343\202\272", nullptr));
        label_59->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_60->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\260\217\351\235\242\347\251\215", nullptr));
        label_61->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\343\203\226\343\203\255\343\203\203\343\202\257\346\234\200\345\244\247\351\235\242\347\251\215", nullptr));
        label_63->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\343\202\265\n"
"\343\202\244\n"
"\343\202\272", nullptr));
        label_68->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\347\251\264\n"
"\350\274\235\n"
"\345\272\246", nullptr));
        pushButtonGColor->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "Color", nullptr));
        label_70->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_72->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\347\224\237\n"
"\346\210\220", nullptr));
        label_71->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\347\251\264\343\201\213\343\202\211\343\203\221\343\203\203\343\203\211\350\274\252\351\203\255\343\201\276\343\201\247\343\201\256\343\203\211\343\203\203\343\203\210", nullptr));
        label_69->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\351\212\205\n"
"\350\274\235\n"
"\345\272\246", nullptr));
        pushButtonCColor->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "Color", nullptr));
        label_86->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\350\243\234\n"
"\346\255\243", nullptr));
        label_87->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\350\274\235\n"
"\345\272\246", nullptr));
        label_88->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_89->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_73->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\350\274\235\n"
"\345\272\246", nullptr));
        label_66->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\350\274\235\345\272\246\343\203\236\343\203\274\343\202\270\343\203\263", nullptr));
        label_48->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        pushButtonNColor->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "Color", nullptr));
        toolButtonPickup->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\347\224\237\346\210\220", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "Delete", nullptr));
        label_4->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "12345", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "Save New", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditEulerRingLibraryClass", "Clear new", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditEulerRingLibraryClass: public Ui_EditEulerRingLibraryClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITEULERRINGLIBRARY_H
