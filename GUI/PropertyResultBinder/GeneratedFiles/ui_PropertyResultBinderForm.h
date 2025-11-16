/********************************************************************************
** Form generated from reading UI file 'PropertyResultBinderForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYRESULTBINDERFORM_H
#define UI_PROPERTYRESULTBINDERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyResultBinderForm
{
public:
    QFrame *frame;
    QToolButton *toolButtonAlignmentItem;
    QToolButton *toolButtonAllItemsInLayer;
    QToolButton *toolButtonAllItemsInPage;
    QToolButton *toolButtonOperationOR;
    QToolButton *toolButtonOperationAND;
    QToolButton *toolButtonOperationXOR;
    QToolButton *toolButtonOperationNEG;
    QToolButton *toolButtonOperationConditional;
    QToolButton *toolButtonNothing;
    QToolButton *toolButtonLinkArrow;
    QTableWidget *tableWidgetItemList;
    QPushButton *pushButtonAddItem;
    QPushButton *pushButtonDeleteItem;
    QPushButton *pushButtonModifyItem;

    void setupUi(GUIFormBase *PropertyResultBinderForm)
    {
        if (PropertyResultBinderForm->objectName().isEmpty())
            PropertyResultBinderForm->setObjectName("PropertyResultBinderForm");
        PropertyResultBinderForm->resize(400, 700);
        frame = new QFrame(PropertyResultBinderForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 261));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonAlignmentItem = new QToolButton(frame);
        toolButtonAlignmentItem->setObjectName("toolButtonAlignmentItem");
        toolButtonAlignmentItem->setGeometry(QRect(10, 60, 161, 41));
        toolButtonAlignmentItem->setCheckable(true);
        toolButtonAlignmentItem->setChecked(false);
        toolButtonAlignmentItem->setAutoExclusive(true);
        toolButtonAllItemsInLayer = new QToolButton(frame);
        toolButtonAllItemsInLayer->setObjectName("toolButtonAllItemsInLayer");
        toolButtonAllItemsInLayer->setGeometry(QRect(10, 110, 161, 41));
        toolButtonAllItemsInLayer->setCheckable(true);
        toolButtonAllItemsInLayer->setAutoExclusive(true);
        toolButtonAllItemsInPage = new QToolButton(frame);
        toolButtonAllItemsInPage->setObjectName("toolButtonAllItemsInPage");
        toolButtonAllItemsInPage->setGeometry(QRect(10, 160, 161, 41));
        toolButtonAllItemsInPage->setCheckable(true);
        toolButtonAllItemsInPage->setAutoExclusive(true);
        toolButtonOperationOR = new QToolButton(frame);
        toolButtonOperationOR->setObjectName("toolButtonOperationOR");
        toolButtonOperationOR->setGeometry(QRect(190, 10, 161, 41));
        toolButtonOperationOR->setCheckable(true);
        toolButtonOperationOR->setAutoExclusive(true);
        toolButtonOperationAND = new QToolButton(frame);
        toolButtonOperationAND->setObjectName("toolButtonOperationAND");
        toolButtonOperationAND->setGeometry(QRect(190, 60, 161, 41));
        toolButtonOperationAND->setCheckable(true);
        toolButtonOperationAND->setAutoExclusive(true);
        toolButtonOperationXOR = new QToolButton(frame);
        toolButtonOperationXOR->setObjectName("toolButtonOperationXOR");
        toolButtonOperationXOR->setGeometry(QRect(190, 110, 161, 41));
        toolButtonOperationXOR->setCheckable(true);
        toolButtonOperationXOR->setAutoExclusive(true);
        toolButtonOperationNEG = new QToolButton(frame);
        toolButtonOperationNEG->setObjectName("toolButtonOperationNEG");
        toolButtonOperationNEG->setGeometry(QRect(190, 160, 161, 41));
        toolButtonOperationNEG->setCheckable(true);
        toolButtonOperationNEG->setAutoExclusive(true);
        toolButtonOperationConditional = new QToolButton(frame);
        toolButtonOperationConditional->setObjectName("toolButtonOperationConditional");
        toolButtonOperationConditional->setGeometry(QRect(190, 210, 161, 41));
        toolButtonOperationConditional->setCheckable(true);
        toolButtonOperationConditional->setAutoExclusive(true);
        toolButtonNothing = new QToolButton(frame);
        toolButtonNothing->setObjectName("toolButtonNothing");
        toolButtonNothing->setGeometry(QRect(10, 10, 161, 41));
        toolButtonNothing->setCheckable(true);
        toolButtonNothing->setChecked(true);
        toolButtonNothing->setAutoExclusive(true);
        toolButtonLinkArrow = new QToolButton(frame);
        toolButtonLinkArrow->setObjectName("toolButtonLinkArrow");
        toolButtonLinkArrow->setGeometry(QRect(10, 210, 161, 41));
        toolButtonLinkArrow->setCheckable(true);
        toolButtonLinkArrow->setAutoExclusive(true);
        tableWidgetItemList = new QTableWidget(PropertyResultBinderForm);
        if (tableWidgetItemList->columnCount() < 3)
            tableWidgetItemList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetItemList->setObjectName("tableWidgetItemList");
        tableWidgetItemList->setGeometry(QRect(10, 310, 381, 321));
        tableWidgetItemList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItemList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAddItem = new QPushButton(PropertyResultBinderForm);
        pushButtonAddItem->setObjectName("pushButtonAddItem");
        pushButtonAddItem->setGeometry(QRect(10, 640, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddItem->setIcon(icon);
        pushButtonDeleteItem = new QPushButton(PropertyResultBinderForm);
        pushButtonDeleteItem->setObjectName("pushButtonDeleteItem");
        pushButtonDeleteItem->setGeometry(QRect(290, 640, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDeleteItem->setIcon(icon1);
        pushButtonModifyItem = new QPushButton(PropertyResultBinderForm);
        pushButtonModifyItem->setObjectName("pushButtonModifyItem");
        pushButtonModifyItem->setGeometry(QRect(150, 640, 101, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonModifyItem->setIcon(icon2);

        retranslateUi(PropertyResultBinderForm);

        QMetaObject::connectSlotsByName(PropertyResultBinderForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyResultBinderForm)
    {
        PropertyResultBinderForm->setWindowTitle(QCoreApplication::translate("PropertyResultBinderForm", "Property ResultBinder", nullptr));
        toolButtonAlignmentItem->setText(QCoreApplication::translate("PropertyResultBinderForm", "Algorithm Item", nullptr));
        toolButtonAllItemsInLayer->setText(QCoreApplication::translate("PropertyResultBinderForm", "All items in Layer", nullptr));
        toolButtonAllItemsInPage->setText(QCoreApplication::translate("PropertyResultBinderForm", "All items in Page", nullptr));
        toolButtonOperationOR->setText(QCoreApplication::translate("PropertyResultBinderForm", "Operation OR", nullptr));
        toolButtonOperationAND->setText(QCoreApplication::translate("PropertyResultBinderForm", "Operation AND", nullptr));
        toolButtonOperationXOR->setText(QCoreApplication::translate("PropertyResultBinderForm", "Operation XOR", nullptr));
        toolButtonOperationNEG->setText(QCoreApplication::translate("PropertyResultBinderForm", "Operation NEG", nullptr));
        toolButtonOperationConditional->setText(QCoreApplication::translate("PropertyResultBinderForm", "Operation Conditional", nullptr));
        toolButtonNothing->setText(QCoreApplication::translate("PropertyResultBinderForm", "Nothing", nullptr));
        toolButtonLinkArrow->setText(QCoreApplication::translate("PropertyResultBinderForm", "Link-Arrow", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItemList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyResultBinderForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItemList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyResultBinderForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItemList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyResultBinderForm", "ItemID", nullptr));
        pushButtonAddItem->setText(QCoreApplication::translate("PropertyResultBinderForm", "Add new", nullptr));
        pushButtonDeleteItem->setText(QCoreApplication::translate("PropertyResultBinderForm", "Delete", nullptr));
        pushButtonModifyItem->setText(QCoreApplication::translate("PropertyResultBinderForm", "Modify", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyResultBinderForm: public Ui_PropertyResultBinderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYRESULTBINDERFORM_H
