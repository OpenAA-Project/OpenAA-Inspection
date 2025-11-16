/********************************************************************************
** Form generated from reading UI file 'PropertyAlignmentForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYALIGNMENTFORM_H
#define UI_PROPERTYALIGNMENTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyAlignmentFormClass
{
public:
    QFrame *frame_3;
    QToolButton *toolButtonGroup;
    QToolButton *toolButtonArea;
    QToolButton *toolButtonPoint;
    QFrame *frame_2;
    QLabel *label_4;
    QFrame *frameArea;
    QTableWidget *tableWidgetArea;
    QFrame *frame;
    QFrame *framePoint;
    QTableWidget *tableWidgetPoint;
    QLabel *label_3;

    void setupUi(GUIFormBase *PropertyAlignmentFormClass)
    {
        if (PropertyAlignmentFormClass->objectName().isEmpty())
            PropertyAlignmentFormClass->setObjectName("PropertyAlignmentFormClass");
        PropertyAlignmentFormClass->resize(400, 700);
        frame_3 = new QFrame(PropertyAlignmentFormClass);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 10, 381, 91));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        toolButtonGroup = new QToolButton(frame_3);
        toolButtonGroup->setObjectName("toolButtonGroup");
        toolButtonGroup->setGeometry(QRect(200, 10, 81, 61));
        toolButtonGroup->setCheckable(true);
        toolButtonGroup->setChecked(true);
        toolButtonGroup->setAutoExclusive(true);
        toolButtonArea = new QToolButton(frame_3);
        toolButtonArea->setObjectName("toolButtonArea");
        toolButtonArea->setGeometry(QRect(10, 10, 91, 61));
        toolButtonArea->setCheckable(true);
        toolButtonArea->setChecked(false);
        toolButtonArea->setAutoExclusive(true);
        toolButtonPoint = new QToolButton(frame_3);
        toolButtonPoint->setObjectName("toolButtonPoint");
        toolButtonPoint->setGeometry(QRect(110, 10, 81, 61));
        toolButtonPoint->setCheckable(true);
        toolButtonPoint->setChecked(false);
        toolButtonPoint->setAutoExclusive(true);
        frame_2 = new QFrame(PropertyAlignmentFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 120, 381, 241));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 381, 20));
        label_4->setFrameShape(QFrame::NoFrame);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignJustify|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameArea = new QFrame(frame_2);
        frameArea->setObjectName("frameArea");
        frameArea->setGeometry(QRect(10, 30, 361, 201));
        frameArea->setFrameShape(QFrame::StyledPanel);
        frameArea->setFrameShadow(QFrame::Sunken);
        tableWidgetArea = new QTableWidget(frameArea);
        if (tableWidgetArea->columnCount() < 5)
            tableWidgetArea->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetArea->setObjectName("tableWidgetArea");
        tableWidgetArea->setGeometry(QRect(0, 0, 361, 201));
        tableWidgetArea->setFocusPolicy(Qt::WheelFocus);
        tableWidgetArea->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetArea->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(PropertyAlignmentFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 370, 381, 311));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        framePoint = new QFrame(frame);
        framePoint->setObjectName("framePoint");
        framePoint->setGeometry(QRect(10, 30, 361, 271));
        framePoint->setFrameShape(QFrame::StyledPanel);
        framePoint->setFrameShadow(QFrame::Sunken);
        tableWidgetPoint = new QTableWidget(framePoint);
        if (tableWidgetPoint->columnCount() < 5)
            tableWidgetPoint->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tableWidgetPoint->setObjectName("tableWidgetPoint");
        tableWidgetPoint->setGeometry(QRect(0, 0, 361, 271));
        tableWidgetPoint->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPoint->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 20));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignJustify|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(PropertyAlignmentFormClass);

        QMetaObject::connectSlotsByName(PropertyAlignmentFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyAlignmentFormClass)
    {
        PropertyAlignmentFormClass->setWindowTitle(QCoreApplication::translate("PropertyAlignmentFormClass", "PropertyAlignmentForm", nullptr));
        toolButtonGroup->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "\343\202\260\343\203\253\343\203\274\343\203\227\345\214\226", nullptr));
        toolButtonArea->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "\351\240\230\345\237\237", nullptr));
        toolButtonPoint->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "\343\203\235\343\202\244\343\203\263\343\203\210", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "\343\202\242\343\203\251\343\202\244\343\203\263\343\203\241\343\203\263\343\203\210\351\240\230\345\237\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetArea->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetArea->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetArea->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetArea->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetArea->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "Size", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetPoint->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetPoint->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "Size", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetPoint->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "Group", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetPoint->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "Kind", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetPoint->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "Search", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyAlignmentFormClass", "\343\203\235\343\202\244\343\203\263\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAlignmentFormClass: public Ui_PropertyAlignmentFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYALIGNMENTFORM_H
