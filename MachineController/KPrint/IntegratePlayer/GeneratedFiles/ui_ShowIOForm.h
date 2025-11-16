/********************************************************************************
** Form generated from reading UI file 'ShowIOForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWIOFORM_H
#define UI_SHOWIOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowIOForm
{
public:
    QTableWidget *twOUT;
    QTableWidget *twIN;
    QComboBox *comboBoxBoardNumber;
    QLabel *label_3;
    QCheckBox *chkEchoBack;

    void setupUi(QWidget *ShowIOForm)
    {
        if (ShowIOForm->objectName().isEmpty())
            ShowIOForm->setObjectName(QString::fromUtf8("ShowIOForm"));
        ShowIOForm->resize(519, 706);
        twOUT = new QTableWidget(ShowIOForm);
        twOUT->setObjectName(QString::fromUtf8("twOUT"));
        twOUT->setGeometry(QRect(260, 40, 251, 612));
        twOUT->setSelectionMode(QAbstractItemView::SingleSelection);
        twOUT->setSelectionBehavior(QAbstractItemView::SelectRows);
        twOUT->setShowGrid(true);
        twOUT->setColumnCount(0);
        twIN = new QTableWidget(ShowIOForm);
        if (twIN->columnCount() < 1)
            twIN->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twIN->setHorizontalHeaderItem(0, __qtablewidgetitem);
        twIN->setObjectName(QString::fromUtf8("twIN"));
        twIN->setGeometry(QRect(10, 40, 251, 612));
        twIN->setSelectionMode(QAbstractItemView::SingleSelection);
        twIN->setSelectionBehavior(QAbstractItemView::SelectRows);
        twIN->setShowGrid(true);
        twIN->setColumnCount(1);
        twIN->verticalHeader()->setVisible(false);
        comboBoxBoardNumber = new QComboBox(ShowIOForm);
        comboBoxBoardNumber->setObjectName(QString::fromUtf8("comboBoxBoardNumber"));
        comboBoxBoardNumber->setGeometry(QRect(140, 10, 74, 22));
        label_3 = new QLabel(ShowIOForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 121, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        chkEchoBack = new QCheckBox(ShowIOForm);
        chkEchoBack->setObjectName(QString::fromUtf8("chkEchoBack"));
        chkEchoBack->setGeometry(QRect(20, 670, 81, 17));
        chkEchoBack->setChecked(true);

        retranslateUi(ShowIOForm);

        QMetaObject::connectSlotsByName(ShowIOForm);
    } // setupUi

    void retranslateUi(QWidget *ShowIOForm)
    {
        ShowIOForm->setWindowTitle(QCoreApplication::translate("ShowIOForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twIN->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowIOForm", "Input bit", nullptr));
        label_3->setText(QCoreApplication::translate("ShowIOForm", "PIO Number", nullptr));
        chkEchoBack->setText(QCoreApplication::translate("ShowIOForm", "Echo Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowIOForm: public Ui_ShowIOForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWIOFORM_H
