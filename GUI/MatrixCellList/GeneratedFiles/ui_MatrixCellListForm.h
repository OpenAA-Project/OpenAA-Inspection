/********************************************************************************
** Form generated from reading UI file 'MatrixCellListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXCELLLISTFORM_H
#define UI_MATRIXCELLLISTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_MatrixCellListFormClass
{
public:
    QTableWidget *tableWidget;
    QFrame *frameETC;
    QLabel *label;
    QLineEdit *lineEditTotalCount;
    QPushButton *pushButtonSet;
    QFrame *frameColor;
    QToolButton *toolButtonPiece;

    void setupUi(GUIFormBase *MatrixCellListFormClass)
    {
        if (MatrixCellListFormClass->objectName().isEmpty())
            MatrixCellListFormClass->setObjectName("MatrixCellListFormClass");
        MatrixCellListFormClass->resize(263, 546);
        tableWidget = new QTableWidget(MatrixCellListFormClass);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 261, 471));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameETC = new QFrame(MatrixCellListFormClass);
        frameETC->setObjectName("frameETC");
        frameETC->setGeometry(QRect(0, 470, 271, 71));
        frameETC->setFrameShape(QFrame::StyledPanel);
        frameETC->setFrameShadow(QFrame::Raised);
        label = new QLabel(frameETC);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 10, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditTotalCount = new QLineEdit(frameETC);
        lineEditTotalCount->setObjectName("lineEditTotalCount");
        lineEditTotalCount->setGeometry(QRect(140, 10, 71, 20));
        lineEditTotalCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditTotalCount->setReadOnly(true);
        pushButtonSet = new QPushButton(frameETC);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(0, 40, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Frame.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);
        frameColor = new QFrame(frameETC);
        frameColor->setObjectName("frameColor");
        frameColor->setGeometry(QRect(100, 40, 61, 31));
        frameColor->setFrameShape(QFrame::StyledPanel);
        frameColor->setFrameShadow(QFrame::Raised);
        toolButtonPiece = new QToolButton(frameETC);
        toolButtonPiece->setObjectName("toolButtonPiece");
        toolButtonPiece->setGeometry(QRect(170, 40, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Display.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonPiece->setIcon(icon1);
        toolButtonPiece->setCheckable(true);
        toolButtonPiece->setChecked(true);
        toolButtonPiece->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        retranslateUi(MatrixCellListFormClass);

        QMetaObject::connectSlotsByName(MatrixCellListFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *MatrixCellListFormClass)
    {
        MatrixCellListFormClass->setWindowTitle(QCoreApplication::translate("MatrixCellListFormClass", "MatrixCellListForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MatrixCellListFormClass", "\345\267\246\343\201\213\343\202\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MatrixCellListFormClass", "\344\270\212\343\201\213\343\202\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MatrixCellListFormClass", "\350\246\226\351\207\216\347\225\252\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MatrixCellListFormClass", "\345\200\213\347\211\207\345\220\215", nullptr));
        label->setText(QCoreApplication::translate("MatrixCellListFormClass", "\345\200\213\346\225\260", nullptr));
        lineEditTotalCount->setText(QCoreApplication::translate("MatrixCellListFormClass", "100", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("MatrixCellListFormClass", "\350\246\226\351\207\216\346\236\240\344\275\234\346\210\220", nullptr));
        toolButtonPiece->setText(QCoreApplication::translate("MatrixCellListFormClass", "\345\200\213\347\211\207\346\236\240\350\241\250\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixCellListFormClass: public Ui_MatrixCellListFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXCELLLISTFORM_H
