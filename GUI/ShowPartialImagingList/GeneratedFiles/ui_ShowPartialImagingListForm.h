/********************************************************************************
** Form generated from reading UI file 'ShowPartialImagingListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWPARTIALIMAGINGLISTFORM_H
#define UI_SHOWPARTIALIMAGINGLISTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowPartialImagingListForm
{
public:
    QTableWidget *tableWidgetList;
    QFrame *frame;
    QPushButton *pushButtonUpdate;

    void setupUi(GUIFormBase *ShowPartialImagingListForm)
    {
        if (ShowPartialImagingListForm->objectName().isEmpty())
            ShowPartialImagingListForm->setObjectName("ShowPartialImagingListForm");
        ShowPartialImagingListForm->resize(256, 624);
        tableWidgetList = new QTableWidget(ShowPartialImagingListForm);
        if (tableWidgetList->columnCount() < 4)
            tableWidgetList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetList->setObjectName("tableWidgetList");
        tableWidgetList->setGeometry(QRect(0, 0, 256, 561));
        tableWidgetList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(ShowPartialImagingListForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 559, 251, 61));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(70, 10, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);

        retranslateUi(ShowPartialImagingListForm);

        QMetaObject::connectSlotsByName(ShowPartialImagingListForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowPartialImagingListForm)
    {
        ShowPartialImagingListForm->setWindowTitle(QCoreApplication::translate("ShowPartialImagingListForm", "Show PartialImaging list", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowPartialImagingListForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowPartialImagingListForm", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowPartialImagingListForm", "ItemName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowPartialImagingListForm", "Priority", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("ShowPartialImagingListForm", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowPartialImagingListForm: public Ui_ShowPartialImagingListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWPARTIALIMAGINGLISTFORM_H
