/********************************************************************************
** Form generated from reading UI file 'CreateManualDotMatchingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMANUALDOTMATCHINGFORM_H
#define UI_CREATEMANUALDOTMATCHINGFORM_H

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
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateManualDotMatchingForm
{
public:
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QPushButton *ButtonCancel;
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonOK;
    QFrame *frameLibFolder;
    QFrame *frame_13;
    QLabel *label_43;
    QFrame *frame_14;
    QLabel *label_44;
    QSpinBox *EditSelfSearch;
    QLabel *label_27;
    QFrame *frame_6;
    QLabel *label_35;
    QLabel *label_20;
    QLabel *label_17;
    QSpinBox *EditOKDot;
    QLabel *label_18;
    QSpinBox *EditBrightWidthL;
    QSpinBox *EditBrightWidthH;
    QLabel *label_19;
    QFrame *frame_11;
    QLabel *label_41;
    QFrame *frame_12;
    QLabel *label_42;
    QSpinBox *EditAdjustBlack;
    QSpinBox *EditAdjustWhite;
    QLabel *label_26;
    QLabel *label_25;

    void setupUi(QDialog *CreateManualDotMatchingForm)
    {
        if (CreateManualDotMatchingForm->objectName().isEmpty())
            CreateManualDotMatchingForm->setObjectName("CreateManualDotMatchingForm");
        CreateManualDotMatchingForm->resize(422, 472);
        EditLibID = new QLineEdit(CreateManualDotMatchingForm);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(40, 160, 41, 21));
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(CreateManualDotMatchingForm);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(80, 160, 251, 21));
        EditLibName->setReadOnly(true);
        ButtonCancel = new QPushButton(CreateManualDotMatchingForm);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(280, 420, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        tableWidgetLibList = new QTableWidget(CreateManualDotMatchingForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonOK = new QPushButton(CreateManualDotMatchingForm);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(40, 420, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon1);
        frameLibFolder = new QFrame(CreateManualDotMatchingForm);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        frame_13 = new QFrame(CreateManualDotMatchingForm);
        frame_13->setObjectName("frame_13");
        frame_13->setGeometry(QRect(20, 360, 371, 41));
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
        frame_6 = new QFrame(CreateManualDotMatchingForm);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(20, 190, 371, 91));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Sunken);
        label_35 = new QLabel(frame_6);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 0, 31, 91));
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
        label_17->setGeometry(QRect(60, 28, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKDot = new QSpinBox(frame_6);
        EditOKDot->setObjectName("EditOKDot");
        EditOKDot->setGeometry(QRect(230, 50, 81, 22));
        EditOKDot->setMaximum(99999999);
        label_18 = new QLabel(frame_6);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(60, 48, 121, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditBrightWidthL = new QSpinBox(frame_6);
        EditBrightWidthL->setObjectName("EditBrightWidthL");
        EditBrightWidthL->setGeometry(QRect(190, 28, 81, 22));
        EditBrightWidthL->setMaximum(255);
        EditBrightWidthH = new QSpinBox(frame_6);
        EditBrightWidthH->setObjectName("EditBrightWidthH");
        EditBrightWidthH->setGeometry(QRect(280, 28, 81, 22));
        EditBrightWidthH->setMaximum(255);
        label_19 = new QLabel(frame_6);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(190, 8, 81, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_11 = new QFrame(CreateManualDotMatchingForm);
        frame_11->setObjectName("frame_11");
        frame_11->setGeometry(QRect(20, 290, 371, 61));
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

        retranslateUi(CreateManualDotMatchingForm);

        QMetaObject::connectSlotsByName(CreateManualDotMatchingForm);
    } // setupUi

    void retranslateUi(QDialog *CreateManualDotMatchingForm)
    {
        CreateManualDotMatchingForm->setWindowTitle(QCoreApplication::translate("CreateManualDotMatchingForm", "Create Manual DotMatching", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "Name", nullptr));
        ButtonOK->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "OK", nullptr));
        label_43->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "\346\216\242\n"
"\347\264\242", nullptr));
        label_44->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "\350\274\235\n"
"\345\272\246", nullptr));
        label_27->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "\343\203\226\343\203\255\343\203\203\343\202\257\345\215\230\344\275\223\343\201\247\343\201\256\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_35->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "<html><head/><body><p>\346\244\234</p><p>\345\207\272</p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "\346\230\216\345\201\264", nullptr));
        label_17->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "OK\350\274\235\345\272\246\347\257\204\345\233\262(%)", nullptr));
        label_18->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "OK\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_19->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "\346\232\227\345\201\264", nullptr));
        label_41->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "\350\243\234\n"
"\346\255\243", nullptr));
        label_42->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "\350\274\235\n"
"\345\272\246", nullptr));
        label_26->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("CreateManualDotMatchingForm", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateManualDotMatchingForm: public Ui_CreateManualDotMatchingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMANUALDOTMATCHINGFORM_H
