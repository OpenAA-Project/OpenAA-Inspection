/********************************************************************************
** Form generated from reading UI file 'EditStatusComment.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSTATUSCOMMENT_H
#define UI_EDITSTATUSCOMMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditStatusCommentClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QLabel *label;
    QListWidget *listWidgetModeAll;
    QTableWidget *tableWidgetGUIAll;
    QLabel *label_2;
    QLabel *label_7;
    QListWidget *listWidgetCommentOpinionList;
    QFrame *frameComment;
    QLabel *label_5;
    QTextEdit *textEditCommentNow;
    QFrame *frameCommentText;
    QPushButton *pushButtonLoadHTML;
    QPushButton *pushButtonRegist;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonFont;
    QFrame *frameBottom;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonSave;
    QFrame *frame_2;
    QLabel *label_6;
    QPushButton *pushButtonFontToolTip;
    QPushButton *pushButtonClearToolTip;
    QPushButton *pushButtonLoadHTMLToolTip;
    QTextEdit *textEditToolTip;
    QCheckBox *checkBoxEnableToolTip;

    void setupUi(QMainWindow *EditStatusCommentClass)
    {
        if (EditStatusCommentClass->objectName().isEmpty())
            EditStatusCommentClass->setObjectName("EditStatusCommentClass");
        EditStatusCommentClass->resize(824, 661);
        centralWidget = new QWidget(EditStatusCommentClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 801, 261));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(9, 30, 481, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetModeAll = new QListWidget(frame);
        listWidgetModeAll->setObjectName("listWidgetModeAll");
        listWidgetModeAll->setGeometry(QRect(550, 50, 241, 192));
        tableWidgetGUIAll = new QTableWidget(frame);
        if (tableWidgetGUIAll->columnCount() < 3)
            tableWidgetGUIAll->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGUIAll->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGUIAll->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGUIAll->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetGUIAll->setObjectName("tableWidgetGUIAll");
        tableWidgetGUIAll->setGeometry(QRect(10, 50, 481, 192));
        tableWidgetGUIAll->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetGUIAll->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(500, 30, 291, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 831, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetCommentOpinionList = new QListWidget(frame);
        listWidgetCommentOpinionList->setObjectName("listWidgetCommentOpinionList");
        listWidgetCommentOpinionList->setGeometry(QRect(500, 50, 51, 192));
        frameComment = new QFrame(centralWidget);
        frameComment->setObjectName("frameComment");
        frameComment->setGeometry(QRect(10, 440, 801, 161));
        frameComment->setFrameShape(QFrame::Panel);
        frameComment->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frameComment);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 781, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        textEditCommentNow = new QTextEdit(frameComment);
        textEditCommentNow->setObjectName("textEditCommentNow");
        textEditCommentNow->setGeometry(QRect(10, 30, 781, 81));
        frameCommentText = new QFrame(frameComment);
        frameCommentText->setObjectName("frameCommentText");
        frameCommentText->setGeometry(QRect(0, 120, 801, 40));
        frameCommentText->setFrameShape(QFrame::StyledPanel);
        frameCommentText->setFrameShadow(QFrame::Raised);
        pushButtonLoadHTML = new QPushButton(frameCommentText);
        pushButtonLoadHTML->setObjectName("pushButtonLoadHTML");
        pushButtonLoadHTML->setGeometry(QRect(10, 0, 112, 34));
        pushButtonRegist = new QPushButton(frameCommentText);
        pushButtonRegist->setObjectName("pushButtonRegist");
        pushButtonRegist->setGeometry(QRect(670, 0, 121, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        pushButtonRegist->setFont(font);
        pushButtonClear = new QPushButton(frameCommentText);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(320, 0, 112, 34));
        pushButtonFont = new QPushButton(frameCommentText);
        pushButtonFont->setObjectName("pushButtonFont");
        pushButtonFont->setGeometry(QRect(130, 0, 112, 34));
        frameBottom = new QFrame(centralWidget);
        frameBottom->setObjectName("frameBottom");
        frameBottom->setGeometry(QRect(0, 610, 811, 41));
        frameBottom->setFrameShape(QFrame::StyledPanel);
        frameBottom->setFrameShadow(QFrame::Raised);
        pushButtonClose = new QPushButton(frameBottom);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(700, 10, 101, 23));
        pushButtonLoad = new QPushButton(frameBottom);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(10, 10, 75, 23));
        pushButtonSave = new QPushButton(frameBottom);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(100, 10, 75, 23));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 279, 801, 151));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(120, 8, 671, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonFontToolTip = new QPushButton(frame_2);
        pushButtonFontToolTip->setObjectName("pushButtonFontToolTip");
        pushButtonFontToolTip->setGeometry(QRect(130, 110, 112, 34));
        pushButtonClearToolTip = new QPushButton(frame_2);
        pushButtonClearToolTip->setObjectName("pushButtonClearToolTip");
        pushButtonClearToolTip->setGeometry(QRect(320, 110, 112, 34));
        pushButtonLoadHTMLToolTip = new QPushButton(frame_2);
        pushButtonLoadHTMLToolTip->setObjectName("pushButtonLoadHTMLToolTip");
        pushButtonLoadHTMLToolTip->setGeometry(QRect(10, 110, 112, 34));
        textEditToolTip = new QTextEdit(frame_2);
        textEditToolTip->setObjectName("textEditToolTip");
        textEditToolTip->setGeometry(QRect(10, 30, 781, 71));
        checkBoxEnableToolTip = new QCheckBox(frame_2);
        checkBoxEnableToolTip->setObjectName("checkBoxEnableToolTip");
        checkBoxEnableToolTip->setGeometry(QRect(20, 6, 108, 22));
        EditStatusCommentClass->setCentralWidget(centralWidget);

        retranslateUi(EditStatusCommentClass);

        QMetaObject::connectSlotsByName(EditStatusCommentClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditStatusCommentClass)
    {
        EditStatusCommentClass->setWindowTitle(QCoreApplication::translate("EditStatusCommentClass", "EditStatusComment", nullptr));
        label->setText(QCoreApplication::translate("EditStatusCommentClass", "Where", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGUIAll->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditStatusCommentClass", "DLLRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGUIAll->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditStatusCommentClass", "DLLName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGUIAll->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditStatusCommentClass", "InstName", nullptr));
        label_2->setText(QCoreApplication::translate("EditStatusCommentClass", "Object Path", nullptr));
        label_7->setText(QCoreApplication::translate("EditStatusCommentClass", "All opinions", nullptr));
        label_5->setText(QCoreApplication::translate("EditStatusCommentClass", "\343\202\263\343\203\241\343\203\263\343\203\210\343\203\273\343\203\241\343\203\203\343\202\273\343\203\274\343\202\270", nullptr));
        pushButtonLoadHTML->setText(QCoreApplication::translate("EditStatusCommentClass", "Load HTML", nullptr));
        pushButtonRegist->setText(QCoreApplication::translate("EditStatusCommentClass", "\347\231\273\351\214\262", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("EditStatusCommentClass", "Clear", nullptr));
        pushButtonFont->setText(QCoreApplication::translate("EditStatusCommentClass", "Font", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditStatusCommentClass", "Close", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("EditStatusCommentClass", "Load", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("EditStatusCommentClass", "Save", nullptr));
        label_6->setText(QCoreApplication::translate("EditStatusCommentClass", "ToolTip", nullptr));
        pushButtonFontToolTip->setText(QCoreApplication::translate("EditStatusCommentClass", "Font", nullptr));
        pushButtonClearToolTip->setText(QCoreApplication::translate("EditStatusCommentClass", "Clear", nullptr));
        pushButtonLoadHTMLToolTip->setText(QCoreApplication::translate("EditStatusCommentClass", "Load HTML", nullptr));
        checkBoxEnableToolTip->setText(QCoreApplication::translate("EditStatusCommentClass", "Show", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditStatusCommentClass: public Ui_EditStatusCommentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSTATUSCOMMENT_H
