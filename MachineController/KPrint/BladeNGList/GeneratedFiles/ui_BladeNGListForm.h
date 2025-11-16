/********************************************************************************
** Form generated from reading UI file 'BladeNGListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLADENGLISTFORM_H
#define UI_BLADENGLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_BladeNGListForm
{
public:
    QTableWidget *tableWidgetNGList;
    QFrame *frame;
    QPushButton *pushButtonExcelOut;
    QPushButton *pushButtonReDraw;

    void setupUi(GUIFormBase *BladeNGListForm)
    {
        if (BladeNGListForm->objectName().isEmpty())
            BladeNGListForm->setObjectName("BladeNGListForm");
        BladeNGListForm->resize(400, 300);
        tableWidgetNGList = new QTableWidget(BladeNGListForm);
        if (tableWidgetNGList->columnCount() < 3)
            tableWidgetNGList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetNGList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetNGList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetNGList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetNGList->setObjectName("tableWidgetNGList");
        tableWidgetNGList->setGeometry(QRect(0, 40, 381, 271));
        QFont font;
        font.setPointSize(11);
        tableWidgetNGList->setFont(font);
        tableWidgetNGList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetNGList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(BladeNGListForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 391, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonExcelOut = new QPushButton(frame);
        pushButtonExcelOut->setObjectName("pushButtonExcelOut");
        pushButtonExcelOut->setGeometry(QRect(130, 0, 121, 34));
        pushButtonReDraw = new QPushButton(frame);
        pushButtonReDraw->setObjectName("pushButtonReDraw");
        pushButtonReDraw->setGeometry(QRect(0, 0, 81, 34));

        retranslateUi(BladeNGListForm);

        QMetaObject::connectSlotsByName(BladeNGListForm);
    } // setupUi

    void retranslateUi(GUIFormBase *BladeNGListForm)
    {
        BladeNGListForm->setWindowTitle(QCoreApplication::translate("BladeNGListForm", "\345\210\203\343\201\256NG\343\203\252\343\202\271\343\203\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetNGList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("BladeNGListForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetNGList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("BladeNGListForm", "\346\227\245\346\231\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetNGList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("BladeNGListForm", "\350\250\210\346\270\254\357\274\221", nullptr));
        pushButtonExcelOut->setText(QCoreApplication::translate("BladeNGListForm", "Excel\345\207\272\345\212\233", nullptr));
        pushButtonReDraw->setText(QCoreApplication::translate("BladeNGListForm", "\345\206\215\350\241\250\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BladeNGListForm: public Ui_BladeNGListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLADENGLISTFORM_H
