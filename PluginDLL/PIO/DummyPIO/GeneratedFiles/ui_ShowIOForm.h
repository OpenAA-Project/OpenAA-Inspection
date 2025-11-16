/********************************************************************************
** Form generated from reading UI file 'ShowIOForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWIOFORM_H
#define UI_SHOWIOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowIOForm
{
public:
    QTableWidget *twOUT;
    QTableWidget *twIN;

    void setupUi(QDialog *ShowIOForm)
    {
        if (ShowIOForm->objectName().isEmpty())
            ShowIOForm->setObjectName("ShowIOForm");
        ShowIOForm->resize(502, 612);
        twOUT = new QTableWidget(ShowIOForm);
        twOUT->setObjectName("twOUT");
        twOUT->setGeometry(QRect(250, 0, 251, 612));
        twOUT->setSelectionMode(QAbstractItemView::SingleSelection);
        twOUT->setSelectionBehavior(QAbstractItemView::SelectRows);
        twOUT->setShowGrid(true);
        twOUT->setColumnCount(0);
        twIN = new QTableWidget(ShowIOForm);
        twIN->setObjectName("twIN");
        twIN->setGeometry(QRect(0, 0, 251, 612));
        twIN->setSelectionMode(QAbstractItemView::SingleSelection);
        twIN->setSelectionBehavior(QAbstractItemView::SelectRows);
        twIN->setShowGrid(true);
        twIN->setColumnCount(0);

        retranslateUi(ShowIOForm);

        QMetaObject::connectSlotsByName(ShowIOForm);
    } // setupUi

    void retranslateUi(QDialog *ShowIOForm)
    {
        ShowIOForm->setWindowTitle(QCoreApplication::translate("ShowIOForm", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowIOForm: public Ui_ShowIOForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWIOFORM_H
