/********************************************************************************
** Form generated from reading UI file 'ShowTotalNGNamingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWTOTALNGNAMINGFORM_H
#define UI_SHOWTOTALNGNAMINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowTotalNGNamingForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditTotalNG;
    QLineEdit *lineEditTotalOK;
    QTableWidget *tableWidgetList;
    QPushButton *pushButtonReset;

    void setupUi(GUIFormBase *ShowTotalNGNamingForm)
    {
        if (ShowTotalNGNamingForm->objectName().isEmpty())
            ShowTotalNGNamingForm->setObjectName("ShowTotalNGNamingForm");
        ShowTotalNGNamingForm->resize(268, 331);
        label = new QLabel(ShowTotalNGNamingForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 121, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(ShowTotalNGNamingForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 30, 121, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditTotalNG = new QLineEdit(ShowTotalNGNamingForm);
        lineEditTotalNG->setObjectName("lineEditTotalNG");
        lineEditTotalNG->setGeometry(QRect(140, 10, 81, 20));
        lineEditTotalOK = new QLineEdit(ShowTotalNGNamingForm);
        lineEditTotalOK->setObjectName("lineEditTotalOK");
        lineEditTotalOK->setGeometry(QRect(140, 30, 81, 20));
        tableWidgetList = new QTableWidget(ShowTotalNGNamingForm);
        if (tableWidgetList->columnCount() < 3)
            tableWidgetList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetList->setObjectName("tableWidgetList");
        tableWidgetList->setGeometry(QRect(10, 60, 251, 231));
        pushButtonReset = new QPushButton(ShowTotalNGNamingForm);
        pushButtonReset->setObjectName("pushButtonReset");
        pushButtonReset->setGeometry(QRect(80, 300, 111, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Refresh.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonReset->setIcon(icon);

        retranslateUi(ShowTotalNGNamingForm);

        QMetaObject::connectSlotsByName(ShowTotalNGNamingForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowTotalNGNamingForm)
    {
        ShowTotalNGNamingForm->setWindowTitle(QCoreApplication::translate("ShowTotalNGNamingForm", "Show total NG Naming", nullptr));
        label->setText(QCoreApplication::translate("ShowTotalNGNamingForm", "Total NG piece", nullptr));
        label_2->setText(QCoreApplication::translate("ShowTotalNGNamingForm", "Total OK piece", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowTotalNGNamingForm", "Piece", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowTotalNGNamingForm", "OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowTotalNGNamingForm", "NG", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("ShowTotalNGNamingForm", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowTotalNGNamingForm: public Ui_ShowTotalNGNamingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWTOTALNGNAMINGFORM_H
