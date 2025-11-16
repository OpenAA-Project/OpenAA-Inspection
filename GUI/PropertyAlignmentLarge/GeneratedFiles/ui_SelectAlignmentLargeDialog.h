/********************************************************************************
** Form generated from reading UI file 'SelectAlignmentLargeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTALIGNMENTLARGEDIALOG_H
#define UI_SELECTALIGNMENTLARGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectAlignmentLargeDialog
{
public:
    QLabel *label_9;
    QFrame *frameLibFolder;
    QPushButton *ButtonOK;
    QLineEdit *EditItemName;
    QPushButton *ButtonCancel;
    QLineEdit *EditLibID;
    QFrame *frameGenLayer;
    QLineEdit *EditLibName;
    QLabel *label;
    QTableWidget *tableWidgetLibList;
    QSpinBox *spinBoxMaxCountHLine;
    QSpinBox *spinBoxMaxCountVLine;
    QCheckBox *checkBoxJudgeWithBrDif;
    QLabel *label_12;
    QFrame *frame;
    QLabel *label_3;
    QSpinBox *EditMoveDotY;
    QSpinBox *EditMoveDot;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_11;
    QFrame *frame_2;
    QLabel *label_5;
    QLabel *label_7;
    QSpinBox *EditMoveDot2;
    QSpinBox *EditMoveDotY2;
    QLabel *label_8;
    QCheckBox *checkBoxUsageGlobal;
    QLabel *labelCautionForOrigin;

    void setupUi(QDialog *SelectAlignmentLargeDialog)
    {
        if (SelectAlignmentLargeDialog->objectName().isEmpty())
            SelectAlignmentLargeDialog->setObjectName("SelectAlignmentLargeDialog");
        SelectAlignmentLargeDialog->resize(457, 564);
        label_9 = new QLabel(SelectAlignmentLargeDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 230, 381, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setTextFormat(Qt::AutoText);
        label_9->setAlignment(Qt::AlignCenter);
        frameLibFolder = new QFrame(SelectAlignmentLargeDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonOK = new QPushButton(SelectAlignmentLargeDialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(90, 520, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        EditItemName = new QLineEdit(SelectAlignmentLargeDialog);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(90, 160, 321, 21));
        EditItemName->setReadOnly(false);
        ButtonCancel = new QPushButton(SelectAlignmentLargeDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(270, 520, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        EditLibID = new QLineEdit(SelectAlignmentLargeDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(40, 190, 51, 21));
        EditLibID->setReadOnly(true);
        frameGenLayer = new QFrame(SelectAlignmentLargeDialog);
        frameGenLayer->setObjectName("frameGenLayer");
        frameGenLayer->setGeometry(QRect(30, 250, 381, 28));
        frameGenLayer->setFrameShape(QFrame::NoFrame);
        frameGenLayer->setFrameShadow(QFrame::Plain);
        EditLibName = new QLineEdit(SelectAlignmentLargeDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(90, 190, 321, 21));
        EditLibName->setReadOnly(true);
        label = new QLabel(SelectAlignmentLargeDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 160, 81, 21));
        tableWidgetLibList = new QTableWidget(SelectAlignmentLargeDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 241, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        spinBoxMaxCountHLine = new QSpinBox(SelectAlignmentLargeDialog);
        spinBoxMaxCountHLine->setObjectName("spinBoxMaxCountHLine");
        spinBoxMaxCountHLine->setGeometry(QRect(80, 402, 91, 22));
        spinBoxMaxCountHLine->setMinimum(-1);
        spinBoxMaxCountHLine->setMaximum(3);
        spinBoxMaxCountHLine->setValue(-1);
        spinBoxMaxCountVLine = new QSpinBox(SelectAlignmentLargeDialog);
        spinBoxMaxCountVLine->setObjectName("spinBoxMaxCountVLine");
        spinBoxMaxCountVLine->setGeometry(QRect(310, 400, 91, 22));
        spinBoxMaxCountVLine->setMinimum(-1);
        spinBoxMaxCountVLine->setMaximum(3);
        spinBoxMaxCountVLine->setValue(-1);
        checkBoxJudgeWithBrDif = new QCheckBox(SelectAlignmentLargeDialog);
        checkBoxJudgeWithBrDif->setObjectName("checkBoxJudgeWithBrDif");
        checkBoxJudgeWithBrDif->setGeometry(QRect(30, 430, 291, 21));
        label_12 = new QLabel(SelectAlignmentLargeDialog);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(260, 378, 191, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(SelectAlignmentLargeDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 290, 211, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 20, 91, 16));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMoveDotY = new QSpinBox(frame);
        EditMoveDotY->setObjectName("EditMoveDotY");
        EditMoveDotY->setGeometry(QRect(110, 40, 91, 22));
        EditMoveDotY->setMaximum(99999);
        EditMoveDot = new QSpinBox(frame);
        EditMoveDot->setObjectName("EditMoveDot");
        EditMoveDot->setGeometry(QRect(10, 40, 91, 22));
        EditMoveDot->setMaximum(99999);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 91, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 211, 16));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(SelectAlignmentLargeDialog);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(40, 380, 191, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        frame_2 = new QFrame(SelectAlignmentLargeDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(240, 290, 211, 71));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 20, 91, 16));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(110, 20, 91, 16));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMoveDot2 = new QSpinBox(frame_2);
        EditMoveDot2->setObjectName("EditMoveDot2");
        EditMoveDot2->setGeometry(QRect(10, 40, 91, 22));
        EditMoveDot2->setMaximum(99999);
        EditMoveDotY2 = new QSpinBox(frame_2);
        EditMoveDotY2->setObjectName("EditMoveDotY2");
        EditMoveDotY2->setGeometry(QRect(110, 40, 91, 22));
        EditMoveDotY2->setMaximum(99999);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 211, 16));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxUsageGlobal = new QCheckBox(SelectAlignmentLargeDialog);
        checkBoxUsageGlobal->setObjectName("checkBoxUsageGlobal");
        checkBoxUsageGlobal->setGeometry(QRect(30, 460, 121, 21));
        labelCautionForOrigin = new QLabel(SelectAlignmentLargeDialog);
        labelCautionForOrigin->setObjectName("labelCautionForOrigin");
        labelCautionForOrigin->setGeometry(QRect(80, 490, 341, 20));

        retranslateUi(SelectAlignmentLargeDialog);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectAlignmentLargeDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectAlignmentLargeDialog)
    {
        SelectAlignmentLargeDialog->setWindowTitle(QCoreApplication::translate("SelectAlignmentLargeDialog", "Dialog", nullptr));
        label_9->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "\347\224\237\346\210\220\351\201\251\347\224\250\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
        ButtonOK->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "Item name", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "Name", nullptr));
        checkBoxJudgeWithBrDif->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "Judge with brightness difference", nullptr));
        label_12->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "Count of Horizontal line", nullptr));
        label_3->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "\346\216\242\347\264\242\350\267\235\351\233\242 Y", nullptr));
        label_2->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "\346\216\242\347\264\242\350\267\235\351\233\242 X", nullptr));
        label_6->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "\346\234\200\345\210\235\343\201\256\346\216\242\347\264\242", nullptr));
        label_11->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "Count of Horizontal line", nullptr));
        label_5->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "\346\216\242\347\264\242\350\267\235\351\233\242 X", nullptr));
        label_7->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "\346\216\242\347\264\242\350\267\235\351\233\242 Y", nullptr));
        label_8->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "\357\274\222\347\225\252\347\233\256\343\201\256\346\216\242\347\264\242", nullptr));
        checkBoxUsageGlobal->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "Global usage", nullptr));
        labelCautionForOrigin->setText(QCoreApplication::translate("SelectAlignmentLargeDialog", "Pickup/Generate from Master image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectAlignmentLargeDialog: public Ui_SelectAlignmentLargeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTALIGNMENTLARGEDIALOG_H
