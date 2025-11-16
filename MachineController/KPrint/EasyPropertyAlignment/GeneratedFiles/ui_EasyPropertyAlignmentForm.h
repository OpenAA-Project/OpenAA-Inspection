/********************************************************************************
** Form generated from reading UI file 'EasyPropertyAlignmentForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYPROPERTYALIGNMENTFORM_H
#define UI_EASYPROPERTYALIGNMENTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_EasyPropertyAlignmentForm
{
public:
    QToolButton *toolButtonAutoGenerate;
    QWidget *widget;
    QToolButton *toolButtonAreaFromMask;
    QToolButton *toolButtonAreaFromCAD;
    QToolButton *toolButtonDeleteAll;
    QFrame *frame;
    QLabel *label;
    QTableWidget *tableWidgetLimitedLib;
    QLabel *labelAreaName;
    QToolButton *toolButtonAreaPriority;
    QToolButton *toolButtonPriority;
    QPushButton *pushButtonAddLimitedLib;
    QToolButton *toolButtonAreaMode;
    QTableWidget *tableWidgetMarkList;

    void setupUi(GUIFormBase *EasyPropertyAlignmentForm)
    {
        if (EasyPropertyAlignmentForm->objectName().isEmpty())
            EasyPropertyAlignmentForm->setObjectName("EasyPropertyAlignmentForm");
        EasyPropertyAlignmentForm->resize(300, 900);
        toolButtonAutoGenerate = new QToolButton(EasyPropertyAlignmentForm);
        toolButtonAutoGenerate->setObjectName("toolButtonAutoGenerate");
        toolButtonAutoGenerate->setGeometry(QRect(10, 10, 281, 91));
        QFont font;
        font.setPointSize(26);
        toolButtonAutoGenerate->setFont(font);
        toolButtonAutoGenerate->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonAutoGenerate->setCheckable(false);
        widget = new QWidget(EasyPropertyAlignmentForm);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 301, 101));
        widget->setAutoFillBackground(true);
        toolButtonAreaFromMask = new QToolButton(widget);
        toolButtonAreaFromMask->setObjectName("toolButtonAreaFromMask");
        toolButtonAreaFromMask->setGeometry(QRect(10, 10, 131, 71));
        QFont font1;
        font1.setPointSize(12);
        toolButtonAreaFromMask->setFont(font1);
        toolButtonAreaFromMask->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(180, 254, 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 100, 180, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonAreaFromCAD = new QToolButton(widget);
        toolButtonAreaFromCAD->setObjectName("toolButtonAreaFromCAD");
        toolButtonAreaFromCAD->setGeometry(QRect(160, 10, 131, 71));
        toolButtonAreaFromCAD->setFont(font1);
        toolButtonAreaFromCAD->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(180, 254, 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 100, 180, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonDeleteAll = new QToolButton(EasyPropertyAlignmentForm);
        toolButtonDeleteAll->setObjectName("toolButtonDeleteAll");
        toolButtonDeleteAll->setGeometry(QRect(10, 580, 281, 71));
        toolButtonDeleteAll->setFont(font);
        toolButtonDeleteAll->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonDeleteAll->setCheckable(false);
        frame = new QFrame(EasyPropertyAlignmentForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 100, 291, 381));
        QPalette palette;
        QBrush brush(QColor(85, 170, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        frame->setPalette(palette);
        frame->setAutoFillBackground(true);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 190, 191, 31));
        QPalette palette1;
        QBrush brush2(QColor(186, 186, 186, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        label->setPalette(palette1);
        label->setAutoFillBackground(true);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        tableWidgetLimitedLib = new QTableWidget(frame);
        if (tableWidgetLimitedLib->columnCount() < 2)
            tableWidgetLimitedLib->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLimitedLib->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLimitedLib->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLimitedLib->setObjectName("tableWidgetLimitedLib");
        tableWidgetLimitedLib->setGeometry(QRect(10, 220, 271, 151));
        tableWidgetLimitedLib->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLimitedLib->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetLimitedLib->setWordWrap(true);
        labelAreaName = new QLabel(frame);
        labelAreaName->setObjectName("labelAreaName");
        labelAreaName->setGeometry(QRect(10, 119, 271, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        labelAreaName->setPalette(palette2);
        labelAreaName->setAutoFillBackground(true);
        labelAreaName->setFrameShape(QFrame::Panel);
        labelAreaName->setFrameShadow(QFrame::Sunken);
        labelAreaName->setAlignment(Qt::AlignCenter);
        toolButtonAreaPriority = new QToolButton(frame);
        toolButtonAreaPriority->setObjectName("toolButtonAreaPriority");
        toolButtonAreaPriority->setGeometry(QRect(10, 10, 271, 101));
        toolButtonAreaPriority->setFont(font);
        toolButtonAreaPriority->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 180, 180, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonAreaPriority->setCheckable(true);
        toolButtonAreaPriority->setChecked(false);
        toolButtonPriority = new QToolButton(frame);
        toolButtonPriority->setObjectName("toolButtonPriority");
        toolButtonPriority->setGeometry(QRect(10, 150, 271, 31));
        QFont font2;
        font2.setPointSize(16);
        toolButtonPriority->setFont(font2);
        toolButtonPriority->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 120, 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 180, 180, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonPriority->setCheckable(false);
        toolButtonPriority->setChecked(false);
        pushButtonAddLimitedLib = new QPushButton(frame);
        pushButtonAddLimitedLib->setObjectName("pushButtonAddLimitedLib");
        pushButtonAddLimitedLib->setGeometry(QRect(200, 190, 80, 31));
        pushButtonAddLimitedLib->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 120, 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 180, 180, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonAreaMode = new QToolButton(EasyPropertyAlignmentForm);
        toolButtonAreaMode->setObjectName("toolButtonAreaMode");
        toolButtonAreaMode->setGeometry(QRect(10, 480, 281, 91));
        toolButtonAreaMode->setFont(font);
        toolButtonAreaMode->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(100, 254, 120, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 180, 0, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        toolButtonAreaMode->setCheckable(true);
        toolButtonAreaMode->setChecked(false);
        tableWidgetMarkList = new QTableWidget(EasyPropertyAlignmentForm);
        if (tableWidgetMarkList->columnCount() < 2)
            tableWidgetMarkList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetMarkList->setObjectName("tableWidgetMarkList");
        tableWidgetMarkList->setGeometry(QRect(10, 660, 281, 201));
        tableWidgetMarkList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetMarkList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetMarkList->setWordWrap(true);

        retranslateUi(EasyPropertyAlignmentForm);

        QMetaObject::connectSlotsByName(EasyPropertyAlignmentForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyPropertyAlignmentForm)
    {
        EasyPropertyAlignmentForm->setWindowTitle(QCoreApplication::translate("EasyPropertyAlignmentForm", "Form", nullptr));
        toolButtonAutoGenerate->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\350\207\252\345\213\225\347\224\237\346\210\220", nullptr));
        toolButtonAreaFromMask->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "Mask -> Area", nullptr));
        toolButtonAreaFromCAD->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "CAD -> Area", nullptr));
        toolButtonDeleteAll->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\345\205\250\345\211\212\351\231\244", nullptr));
        label->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\345\275\261\351\237\277\343\202\222\344\270\216\343\201\210\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLimitedLib->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLimitedLib->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        labelAreaName->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\345\204\252\345\205\210\345\272\246", nullptr));
        toolButtonAreaPriority->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\345\244\226\345\275\242", nullptr));
        toolButtonPriority->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\351\240\230\345\237\237\351\201\270\346\212\236", nullptr));
        pushButtonAddLimitedLib->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "...", nullptr));
        toolButtonAreaMode->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\343\203\236\343\203\274\343\202\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMarkList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\346\216\242\347\264\2421", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMarkList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EasyPropertyAlignmentForm", "\346\216\242\347\264\2422", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyPropertyAlignmentForm: public Ui_EasyPropertyAlignmentForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYPROPERTYALIGNMENTFORM_H
