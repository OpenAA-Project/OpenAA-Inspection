/********************************************************************************
** Form generated from reading UI file 'PropertyAlignmentProjectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYALIGNMENTPROJECTIONFORM_H
#define UI_PROPERTYALIGNMENTPROJECTIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyAlignmentProjectionForm
{
public:
    QFrame *frame;
    QFrame *framePoint;
    QTableWidget *tableWidgetPoint;
    QLabel *label_3;

    void setupUi(GUIFormBase *PropertyAlignmentProjectionForm)
    {
        if (PropertyAlignmentProjectionForm->objectName().isEmpty())
            PropertyAlignmentProjectionForm->setObjectName("PropertyAlignmentProjectionForm");
        PropertyAlignmentProjectionForm->resize(400, 700);
        frame = new QFrame(PropertyAlignmentProjectionForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 311));
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
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetPoint->setObjectName("tableWidgetPoint");
        tableWidgetPoint->setGeometry(QRect(0, 0, 361, 271));
        tableWidgetPoint->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPoint->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 20));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignJustify|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(PropertyAlignmentProjectionForm);

        QMetaObject::connectSlotsByName(PropertyAlignmentProjectionForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyAlignmentProjectionForm)
    {
        PropertyAlignmentProjectionForm->setWindowTitle(QCoreApplication::translate("PropertyAlignmentProjectionForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPoint->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyAlignmentProjectionForm", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPoint->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyAlignmentProjectionForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPoint->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyAlignmentProjectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetPoint->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyAlignmentProjectionForm", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetPoint->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyAlignmentProjectionForm", "Peak", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyAlignmentProjectionForm", "\343\203\235\343\202\244\343\203\263\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAlignmentProjectionForm: public Ui_PropertyAlignmentProjectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYALIGNMENTPROJECTIONFORM_H
