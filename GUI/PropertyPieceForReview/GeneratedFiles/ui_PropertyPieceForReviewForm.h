/********************************************************************************
** Form generated from reading UI file 'PropertyPieceForReviewForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYPIECEFORREVIEWFORM_H
#define UI_PROPERTYPIECEFORREVIEWFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyPieceForReviewForm
{
public:
    QToolButton *toolButtonOverlap;
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *PropertyPieceForReviewForm)
    {
        if (PropertyPieceForReviewForm->objectName().isEmpty())
            PropertyPieceForReviewForm->setObjectName("PropertyPieceForReviewForm");
        PropertyPieceForReviewForm->resize(400, 700);
        toolButtonOverlap = new QToolButton(PropertyPieceForReviewForm);
        toolButtonOverlap->setObjectName("toolButtonOverlap");
        toolButtonOverlap->setGeometry(QRect(130, 10, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Composite.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonOverlap->setIcon(icon);
        toolButtonOverlap->setCheckable(true);
        toolButtonOverlap->setChecked(true);
        toolButtonOverlap->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        tableWidget = new QTableWidget(PropertyPieceForReviewForm);
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
        tableWidget->setGeometry(QRect(10, 70, 381, 621));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PropertyPieceForReviewForm);

        QMetaObject::connectSlotsByName(PropertyPieceForReviewForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyPieceForReviewForm)
    {
        PropertyPieceForReviewForm->setWindowTitle(QCoreApplication::translate("PropertyPieceForReviewForm", "Property PieceForReview", nullptr));
        toolButtonOverlap->setText(QCoreApplication::translate("PropertyPieceForReviewForm", "\347\224\273\345\203\217\351\207\215\343\201\255\345\220\210\343\202\217\343\201\233", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyPieceForReviewForm", "\347\225\252\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyPieceForReviewForm", "\343\203\232\343\203\274\343\202\270\347\225\252\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyPieceForReviewForm", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyPieceForReviewForm", "Seq", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyPieceForReviewForm: public Ui_PropertyPieceForReviewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYPIECEFORREVIEWFORM_H
