/********************************************************************************
** Form generated from reading UI file 'CreateManualDotColorMatchingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMANUALDOTCOLORMATCHINGDIALOG_H
#define UI_CREATEMANUALDOTCOLORMATCHINGDIALOG_H

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

class Ui_CreateManualDotColorMatchingDialog
{
public:
    QFrame *frame_13;
    QLabel *label_43;
    QFrame *frame_14;
    QLabel *label_44;
    QSpinBox *EditSelfSearch;
    QLabel *label_27;
    QPushButton *ButtonOK;
    QFrame *frame_6;
    QLabel *label_35;
    QLabel *label_20;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_21;
    QLabel *label_22;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QSpinBox *EditOKDotB;
    QSpinBox *EditBrightWidthBGL;
    QSpinBox *EditBrightWidthBBL;
    QSpinBox *EditBrightWidthBBH;
    QSpinBox *EditBrightWidthBRL;
    QSpinBox *EditBrightWidthBGH;
    QSpinBox *EditBrightWidthBRH;
    QWidget *page_2;
    QSpinBox *EditOKDotN;
    QSpinBox *EditBrightWidthNGL;
    QSpinBox *EditBrightWidthNBL;
    QSpinBox *EditBrightWidthNBH;
    QSpinBox *EditBrightWidthNRL;
    QSpinBox *EditBrightWidthNGH;
    QSpinBox *EditBrightWidthNRH;
    QToolButton *toolButtonBroad;
    QToolButton *toolButtonNarrow;
    QFrame *frameLibFolder;
    QPushButton *ButtonCancel;
    QFrame *frame_11;
    QLabel *label_41;
    QFrame *frame_12;
    QLabel *label_42;
    QSpinBox *EditAdjustBlack;
    QSpinBox *EditAdjustWhite;
    QLabel *label_26;
    QLabel *label_25;
    QLineEdit *EditLibID;
    QTableWidget *tableWidgetLibList;
    QLineEdit *EditLibName;

    void setupUi(QDialog *CreateManualDotColorMatchingDialog)
    {
        if (CreateManualDotColorMatchingDialog->objectName().isEmpty())
            CreateManualDotColorMatchingDialog->setObjectName("CreateManualDotColorMatchingDialog");
        CreateManualDotColorMatchingDialog->resize(420, 505);
        frame_13 = new QFrame(CreateManualDotColorMatchingDialog);
        frame_13->setObjectName("frame_13");
        frame_13->setGeometry(QRect(20, 400, 371, 41));
        frame_13->setFrameShape(QFrame::StyledPanel);
        frame_13->setFrameShadow(QFrame::Sunken);
        label_43 = new QLabel(frame_13);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(0, 0, 31, 41));
        label_43->setFrameShape(QFrame::Panel);
        label_43->setFrameShadow(QFrame::Raised);
        label_43->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_43->setIndent(1);
        frame_14 = new QFrame(frame_13);
        frame_14->setObjectName("frame_14");
        frame_14->setGeometry(QRect(10, 120, 371, 101));
        frame_14->setFrameShape(QFrame::StyledPanel);
        frame_14->setFrameShadow(QFrame::Sunken);
        label_44 = new QLabel(frame_14);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(0, 0, 20, 61));
        label_44->setFrameShape(QFrame::Panel);
        label_44->setFrameShadow(QFrame::Raised);
        label_44->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_44->setIndent(1);
        EditSelfSearch = new QSpinBox(frame_13);
        EditSelfSearch->setObjectName("EditSelfSearch");
        EditSelfSearch->setGeometry(QRect(270, 10, 81, 22));
        label_27 = new QLabel(frame_13);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(60, 10, 201, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonOK = new QPushButton(CreateManualDotColorMatchingDialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(40, 460, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        frame_6 = new QFrame(CreateManualDotColorMatchingDialog);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(20, 190, 371, 131));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        label_35 = new QLabel(frame_6);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 0, 31, 131));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Raised);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35->setIndent(1);
        label_20 = new QLabel(frame_6);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(280, 8, 81, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_17 = new QLabel(frame_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(30, 28, 151, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_18 = new QLabel(frame_6);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(60, 98, 121, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_19 = new QLabel(frame_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(190, 8, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_21 = new QLabel(frame_6);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(30, 50, 151, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_22 = new QLabel(frame_6);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(30, 70, 151, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget = new QStackedWidget(frame_6);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(190, 30, 171, 91));
        page = new QWidget();
        page->setObjectName("page");
        EditOKDotB = new QSpinBox(page);
        EditOKDotB->setObjectName("EditOKDotB");
        EditOKDotB->setGeometry(QRect(40, 70, 81, 22));
        EditOKDotB->setMaximum(99999999);
        EditBrightWidthBGL = new QSpinBox(page);
        EditBrightWidthBGL->setObjectName("EditBrightWidthBGL");
        EditBrightWidthBGL->setGeometry(QRect(0, 20, 81, 22));
        EditBrightWidthBGL->setMaximum(255);
        EditBrightWidthBBL = new QSpinBox(page);
        EditBrightWidthBBL->setObjectName("EditBrightWidthBBL");
        EditBrightWidthBBL->setGeometry(QRect(0, 40, 81, 22));
        EditBrightWidthBBL->setMaximum(255);
        EditBrightWidthBBH = new QSpinBox(page);
        EditBrightWidthBBH->setObjectName("EditBrightWidthBBH");
        EditBrightWidthBBH->setGeometry(QRect(90, 40, 81, 22));
        EditBrightWidthBBH->setMaximum(255);
        EditBrightWidthBRL = new QSpinBox(page);
        EditBrightWidthBRL->setObjectName("EditBrightWidthBRL");
        EditBrightWidthBRL->setGeometry(QRect(0, -2, 81, 22));
        EditBrightWidthBRL->setMaximum(255);
        EditBrightWidthBGH = new QSpinBox(page);
        EditBrightWidthBGH->setObjectName("EditBrightWidthBGH");
        EditBrightWidthBGH->setGeometry(QRect(90, 20, 81, 22));
        EditBrightWidthBGH->setMaximum(255);
        EditBrightWidthBRH = new QSpinBox(page);
        EditBrightWidthBRH->setObjectName("EditBrightWidthBRH");
        EditBrightWidthBRH->setGeometry(QRect(90, -2, 81, 22));
        EditBrightWidthBRH->setMaximum(255);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        EditOKDotN = new QSpinBox(page_2);
        EditOKDotN->setObjectName("EditOKDotN");
        EditOKDotN->setGeometry(QRect(40, 72, 81, 22));
        EditOKDotN->setMaximum(99999999);
        EditBrightWidthNGL = new QSpinBox(page_2);
        EditBrightWidthNGL->setObjectName("EditBrightWidthNGL");
        EditBrightWidthNGL->setGeometry(QRect(0, 22, 81, 22));
        EditBrightWidthNGL->setMaximum(255);
        EditBrightWidthNBL = new QSpinBox(page_2);
        EditBrightWidthNBL->setObjectName("EditBrightWidthNBL");
        EditBrightWidthNBL->setGeometry(QRect(0, 42, 81, 22));
        EditBrightWidthNBL->setMaximum(255);
        EditBrightWidthNBH = new QSpinBox(page_2);
        EditBrightWidthNBH->setObjectName("EditBrightWidthNBH");
        EditBrightWidthNBH->setGeometry(QRect(90, 42, 81, 22));
        EditBrightWidthNBH->setMaximum(255);
        EditBrightWidthNRL = new QSpinBox(page_2);
        EditBrightWidthNRL->setObjectName("EditBrightWidthNRL");
        EditBrightWidthNRL->setGeometry(QRect(0, 0, 81, 22));
        EditBrightWidthNRL->setMaximum(255);
        EditBrightWidthNGH = new QSpinBox(page_2);
        EditBrightWidthNGH->setObjectName("EditBrightWidthNGH");
        EditBrightWidthNGH->setGeometry(QRect(90, 22, 81, 22));
        EditBrightWidthNGH->setMaximum(255);
        EditBrightWidthNRH = new QSpinBox(page_2);
        EditBrightWidthNRH->setObjectName("EditBrightWidthNRH");
        EditBrightWidthNRH->setGeometry(QRect(90, 0, 81, 22));
        EditBrightWidthNRH->setMaximum(255);
        stackedWidget->addWidget(page_2);
        toolButtonBroad = new QToolButton(frame_6);
        toolButtonBroad->setObjectName("toolButtonBroad");
        toolButtonBroad->setGeometry(QRect(40, 0, 51, 22));
        toolButtonBroad->setCheckable(true);
        toolButtonBroad->setChecked(true);
        toolButtonBroad->setAutoExclusive(true);
        toolButtonNarrow = new QToolButton(frame_6);
        toolButtonNarrow->setObjectName("toolButtonNarrow");
        toolButtonNarrow->setGeometry(QRect(100, 0, 51, 22));
        toolButtonNarrow->setCheckable(true);
        toolButtonNarrow->setAutoExclusive(true);
        frameLibFolder = new QFrame(CreateManualDotColorMatchingDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonCancel = new QPushButton(CreateManualDotColorMatchingDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(280, 460, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        frame_11 = new QFrame(CreateManualDotColorMatchingDialog);
        frame_11->setObjectName("frame_11");
        frame_11->setGeometry(QRect(20, 330, 371, 61));
        frame_11->setFrameShape(QFrame::StyledPanel);
        frame_11->setFrameShadow(QFrame::Sunken);
        label_41 = new QLabel(frame_11);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(0, 0, 31, 61));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setFrameShadow(QFrame::Raised);
        label_41->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_41->setIndent(1);
        frame_12 = new QFrame(frame_11);
        frame_12->setObjectName("frame_12");
        frame_12->setGeometry(QRect(10, 120, 371, 101));
        frame_12->setFrameShape(QFrame::StyledPanel);
        frame_12->setFrameShadow(QFrame::Sunken);
        label_42 = new QLabel(frame_12);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(0, 0, 20, 61));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setFrameShadow(QFrame::Raised);
        label_42->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_42->setIndent(1);
        EditAdjustBlack = new QSpinBox(frame_11);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(270, 10, 81, 22));
        EditAdjustBlack->setMaximum(255);
        EditAdjustWhite = new QSpinBox(frame_11);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(270, 30, 81, 22));
        EditAdjustWhite->setMaximum(255);
        label_26 = new QLabel(frame_11);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(60, 30, 201, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(frame_11);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(60, 10, 201, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(CreateManualDotColorMatchingDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(40, 160, 41, 21));
        EditLibID->setReadOnly(true);
        tableWidgetLibList = new QTableWidget(CreateManualDotColorMatchingDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        EditLibName = new QLineEdit(CreateManualDotColorMatchingDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(80, 160, 251, 21));
        EditLibName->setReadOnly(true);

        retranslateUi(CreateManualDotColorMatchingDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CreateManualDotColorMatchingDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateManualDotColorMatchingDialog)
    {
        CreateManualDotColorMatchingDialog->setWindowTitle(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "Dialog", nullptr));
        label_43->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "\346\216\242\n"
"\347\264\242", nullptr));
        label_44->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "\350\274\235\n"
"\345\272\246", nullptr));
        label_27->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "\343\203\226\343\203\255\343\203\203\343\202\257\345\215\230\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        ButtonOK->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "OK", nullptr));
        label_35->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "<html><head/><body><p>\346\244\234</p><p>\345\207\272</p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "\346\230\216\345\201\264", nullptr));
        label_17->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "OK\350\274\235\345\272\246\347\257\204\345\233\262 R", nullptr));
        label_18->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "\346\232\227\345\201\264", nullptr));
        label_21->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "OK\350\274\235\345\272\246\347\257\204\345\233\262 G", nullptr));
        label_22->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "OK\350\274\235\345\272\246\347\257\204\345\233\262 B", nullptr));
        toolButtonBroad->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "B", nullptr));
        toolButtonNarrow->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "N", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "Cancel", nullptr));
        label_41->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "\350\243\234\n"
"\346\255\243", nullptr));
        label_42->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "\350\274\235\n"
"\345\272\246", nullptr));
        label_26->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CreateManualDotColorMatchingDialog", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateManualDotColorMatchingDialog: public Ui_CreateManualDotColorMatchingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMANUALDOTCOLORMATCHINGDIALOG_H
