/********************************************************************************
** Form generated from reading UI file 'ShowHistgramSelectForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWHISTGRAMSELECTFORM_H
#define UI_SHOWHISTGRAMSELECTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowHistgramSelectForm
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonReDraw;
    QTableWidget *tableWidget_2;
    QLabel *label;
    QLabel *label_2;

    void setupUi(GUIFormBase *ShowHistgramSelectForm)
    {
        if (ShowHistgramSelectForm->objectName().isEmpty())
            ShowHistgramSelectForm->setObjectName("ShowHistgramSelectForm");
        ShowHistgramSelectForm->resize(590, 399);
        tableWidget = new QTableWidget(ShowHistgramSelectForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 321, 351));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(ShowHistgramSelectForm);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(410, 360, 131, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        pushButtonReDraw = new QPushButton(ShowHistgramSelectForm);
        pushButtonReDraw->setObjectName("pushButtonReDraw");
        pushButtonReDraw->setGeometry(QRect(20, 360, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/draw_pen_64.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonReDraw->setIcon(icon1);
        tableWidget_2 = new QTableWidget(ShowHistgramSelectForm);
        if (tableWidget_2->columnCount() < 3)
            tableWidget_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(360, 40, 221, 311));
        tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(ShowHistgramSelectForm);
        label->setObjectName("label");
        label->setGeometry(QRect(360, 20, 221, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowHistgramSelectForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(320, 150, 41, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setFrameShape(QFrame::NoFrame);
        label_2->setFrameShadow(QFrame::Plain);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(ShowHistgramSelectForm);

        QMetaObject::connectSlotsByName(ShowHistgramSelectForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowHistgramSelectForm)
    {
        ShowHistgramSelectForm->setWindowTitle(QCoreApplication::translate("ShowHistgramSelectForm", "Show Histgram", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowHistgramSelectForm", "AlgorithmRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowHistgramSelectForm", "AlgorithmName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowHistgramSelectForm", "HistgramName", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("ShowHistgramSelectForm", "Select", nullptr));
        pushButtonReDraw->setText(QCoreApplication::translate("ShowHistgramSelectForm", "ReDraw", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowHistgramSelectForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowHistgramSelectForm", "Librarty name", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowHistgramSelectForm", "Items", nullptr));
        label->setText(QCoreApplication::translate("ShowHistgramSelectForm", "Library", nullptr));
        label_2->setText(QCoreApplication::translate("ShowHistgramSelectForm", "=>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowHistgramSelectForm: public Ui_ShowHistgramSelectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWHISTGRAMSELECTFORM_H
