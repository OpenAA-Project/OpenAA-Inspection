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
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonLibNew;
    QPushButton *ButtonLibDelete;
    QPushButton *ButtonLibSaveNew;
    QPushButton *pushButtonClose;
    QPushButton *ButtonLibSave;
    QLineEdit *EditLibID;
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
    QWidget *tab_2;
    QFrame *frame_26;
    QLabel *label_87;
    QSpinBox *EditSearchAngle;
    QLabel *label_20;
    QLabel *label_3;
    QSpinBox *spinBoxSearchArea;
    QFrame *frame_27;
    QLabel *label_88;
    QLabel *label_5;
    QSpinBox *spinBoxSearchLittleInItem;
    QLabel *label_23;
    QDoubleSpinBox *doubleSpinBoxMatchingRate;
    QFrame *framePickLayer;
    QFrame *frameGenLayer;
    QLabel *label_9;
    QLineEdit *EditLibName;
    QLabel *label_4;
    QLabel *label_10;

    void setupUi(QDialog *EditLibraryDialog)
    {
        if (EditLibraryDialog->objectName().isEmpty())
            EditLibraryDialog->setObjectName("EditLibraryDialog");
        EditLibraryDialog->resize(620, 577);
        frameLibFolder = new QFrame(EditLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(EditLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 220, 191, 341));
        tableWidgetLibList->setDragEnabled(true);
        tableWidgetLibList->setDragDropOverwriteMode(true);
        tableWidgetLibList->setDragDropMode(QAbstractItemView::DragOnly);
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonLibNew = new QPushButton(EditLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(210, 450, 121, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibNew->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon);
        ButtonLibDelete = new QPushButton(EditLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(210, 490, 121, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon1);
        ButtonLibSaveNew = new QPushButton(EditLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(340, 490, 131, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon2);
        pushButtonClose = new QPushButton(EditLibraryDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(480, 530, 111, 31));
        pushButtonClose->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon3);
        ButtonLibSave = new QPushButton(EditLibraryDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(480, 490, 111, 31));
        ButtonLibSave->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon4);
        EditLibID = new QLineEdit(EditLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(260, 10, 81, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        tabWidget = new QTabWidget(EditLibraryDialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(210, 150, 401, 291));
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
        frame_15->setGeometry(QRect(10, 190, 381, 61));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Sunken);
        EditExpansionDot = new QSpinBox(frame_15);
        EditExpansionDot->setObjectName("EditExpansionDot");
        EditExpansionDot->setGeometry(QRect(290, 10, 81, 22));
        EditExpansionDot->setMaximum(1000000);
        label_58 = new QLabel(frame_15);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(40, 30, 241, 21));
        label_58->setFrameShape(QFrame::Panel);
        label_58->setFrameShadow(QFrame::Sunken);
        label_58->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitSize = new QSpinBox(frame_15);
        EditLimitSize->setObjectName("EditLimitSize");
        EditLimitSize->setGeometry(QRect(290, 30, 81, 22));
        EditLimitSize->setMaximum(1000000);
        label_59 = new QLabel(frame_15);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(40, 10, 241, 21));
        label_59->setFrameShape(QFrame::Panel);
        label_59->setFrameShadow(QFrame::Sunken);
        label_59->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63 = new QLabel(frame_15);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(0, 0, 31, 61));
        label_63->setFrameShape(QFrame::Panel);
        label_63->setFrameShadow(QFrame::Raised);
        label_63->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_63->setIndent(1);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        frame_26 = new QFrame(tab_2);
        frame_26->setObjectName("frame_26");
        frame_26->setGeometry(QRect(10, 10, 381, 71));
        frame_26->setFrameShape(QFrame::StyledPanel);
        frame_26->setFrameShadow(QFrame::Sunken);
        label_87 = new QLabel(frame_26);
        label_87->setObjectName("label_87");
        label_87->setGeometry(QRect(0, 0, 31, 71));
        label_87->setFrameShape(QFrame::Panel);
        label_87->setFrameShadow(QFrame::Raised);
        label_87->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_87->setIndent(1);
        EditSearchAngle = new QSpinBox(frame_26);
        EditSearchAngle->setObjectName("EditSearchAngle");
        EditSearchAngle->setGeometry(QRect(290, 40, 81, 20));
        EditSearchAngle->setMinimum(-255);
        EditSearchAngle->setMaximum(255);
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
        spinBoxSearchArea = new QSpinBox(frame_26);
        spinBoxSearchArea->setObjectName("spinBoxSearchArea");
        spinBoxSearchArea->setGeometry(QRect(290, 10, 81, 22));
        spinBoxSearchArea->setMaximum(999999);
        frame_27 = new QFrame(tab_2);
        frame_27->setObjectName("frame_27");
        frame_27->setGeometry(QRect(10, 90, 381, 81));
        frame_27->setFrameShape(QFrame::StyledPanel);
        frame_27->setFrameShadow(QFrame::Sunken);
        label_88 = new QLabel(frame_27);
        label_88->setObjectName("label_88");
        label_88->setGeometry(QRect(0, 0, 31, 81));
        label_88->setFrameShape(QFrame::Panel);
        label_88->setFrameShadow(QFrame::Raised);
        label_88->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_88->setIndent(1);
        label_5 = new QLabel(frame_27);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 10, 241, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxSearchLittleInItem = new QSpinBox(frame_27);
        spinBoxSearchLittleInItem->setObjectName("spinBoxSearchLittleInItem");
        spinBoxSearchLittleInItem->setGeometry(QRect(290, 10, 81, 22));
        spinBoxSearchLittleInItem->setMaximum(999999);
        label_23 = new QLabel(frame_27);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(40, 40, 241, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxMatchingRate = new QDoubleSpinBox(frame_27);
        doubleSpinBoxMatchingRate->setObjectName("doubleSpinBoxMatchingRate");
        doubleSpinBoxMatchingRate->setGeometry(QRect(290, 40, 81, 24));
        doubleSpinBoxMatchingRate->setMinimum(-1.000000000000000);
        doubleSpinBoxMatchingRate->setMaximum(1.000000000000000);
        tabWidget->addTab(tab_2, QString());
        framePickLayer = new QFrame(EditLibraryDialog);
        framePickLayer->setObjectName("framePickLayer");
        framePickLayer->setGeometry(QRect(210, 70, 381, 28));
        framePickLayer->setFrameShape(QFrame::NoFrame);
        framePickLayer->setFrameShadow(QFrame::Plain);
        frameGenLayer = new QFrame(EditLibraryDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(210, 120, 381, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        label_9 = new QLabel(EditLibraryDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(210, 100, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        EditLibName = new QLineEdit(EditLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(340, 10, 251, 31));
        EditLibName->setFont(font1);
        label_4 = new QLabel(EditLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(210, 10, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_10 = new QLabel(EditLibraryDialog);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(210, 50, 381, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setTextFormat(Qt::AutoText);
        label_10->setAlignment(Qt::AlignCenter);

        retranslateUi(EditLibraryDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EditLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryDialog)
    {
        EditLibraryDialog->setWindowTitle(QCoreApplication::translate("EditLibraryDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryDialog", "Name", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryDialog", "Clear new", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryDialog", "Delete", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryDialog", "Save New", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryDialog", "Update", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryDialog", "12345", nullptr));
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
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272", nullptr));
        label_87->setText(QCoreApplication::translate("EditLibraryDialog", "<html><head/><body><p>\351\240\230</p><p>\345\237\237</p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("EditLibraryDialog", "\346\216\242\347\264\242\350\247\222\345\272\246\343\200\200\302\261", nullptr));
        label_3->setText(QCoreApplication::translate("EditLibraryDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\343\200\200\302\261", nullptr));
        label_88->setText(QCoreApplication::translate("EditLibraryDialog", "<html><head/><body><p>\343\203\236</p><p>\343\203\274</p><p>\343\202\257</p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("EditLibraryDialog", "\345\276\256\345\260\217\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\343\200\200\302\261", nullptr));
        label_23->setText(QCoreApplication::translate("EditLibraryDialog", "\345\210\244\345\256\232\343\200\200\344\270\200\350\207\264\347\216\207", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("EditLibraryDialog", "\345\256\237\350\241\214", nullptr));
        label_9->setText(QCoreApplication::translate("EditLibraryDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryDialog", "Library Name", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryDialog", "\345\220\215\347\247\260", nullptr));
        label_10->setText(QCoreApplication::translate("EditLibraryDialog", "\346\212\275\345\207\272\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryDialog: public Ui_EditLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYDIALOG_H
