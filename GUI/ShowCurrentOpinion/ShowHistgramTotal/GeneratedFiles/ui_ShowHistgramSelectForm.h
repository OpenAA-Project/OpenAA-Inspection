/********************************************************************************
** Form generated from reading UI file 'ShowHistgramSelectForm.ui'
**
** Created: Sun May 26 19:16:58 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWHISTGRAMSELECTFORM_H
#define UI_SHOWHISTGRAMSELECTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
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
            ShowHistgramSelectForm->setObjectName(QString::fromUtf8("ShowHistgramSelectForm"));
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
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 321, 351));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelect = new QPushButton(ShowHistgramSelectForm);
        pushButtonSelect->setObjectName(QString::fromUtf8("pushButtonSelect"));
        pushButtonSelect->setGeometry(QRect(410, 360, 131, 31));
        pushButtonReDraw = new QPushButton(ShowHistgramSelectForm);
        pushButtonReDraw->setObjectName(QString::fromUtf8("pushButtonReDraw"));
        pushButtonReDraw->setGeometry(QRect(20, 360, 101, 31));
        tableWidget_2 = new QTableWidget(ShowHistgramSelectForm);
        if (tableWidget_2->columnCount() < 3)
            tableWidget_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(360, 40, 221, 311));
        tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(ShowHistgramSelectForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(360, 20, 221, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowHistgramSelectForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 150, 41, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setFrameShape(QFrame::NoFrame);
        label_2->setFrameShadow(QFrame::Plain);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(ShowHistgramSelectForm);

        QMetaObject::connectSlotsByName(ShowHistgramSelectForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowHistgramSelectForm)
    {
        ShowHistgramSelectForm->setWindowTitle(QApplication::translate("ShowHistgramSelectForm", "Show Histgram", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ShowHistgramSelectForm", "AlgorithmRoot", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ShowHistgramSelectForm", "AlgorithmName", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ShowHistgramSelectForm", "HistgramName", 0, QApplication::UnicodeUTF8));
        pushButtonSelect->setText(QApplication::translate("ShowHistgramSelectForm", "Select", 0, QApplication::UnicodeUTF8));
        pushButtonReDraw->setText(QApplication::translate("ShowHistgramSelectForm", "ReDraw", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("ShowHistgramSelectForm", "ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("ShowHistgramSelectForm", "Librarty name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("ShowHistgramSelectForm", "Items", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ShowHistgramSelectForm", "Library", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ShowHistgramSelectForm", "=>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ShowHistgramSelectForm: public Ui_ShowHistgramSelectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWHISTGRAMSELECTFORM_H
