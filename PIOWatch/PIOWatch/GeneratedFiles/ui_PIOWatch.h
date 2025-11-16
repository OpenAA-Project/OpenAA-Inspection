/********************************************************************************
** Form generated from reading UI file 'PIOWatch.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIOWATCH_H
#define UI_PIOWATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PIOWatchClass
{
public:
    QTableWidget *twIN;
    QCheckBox *chkEchoBack;
    QPushButton *pbClose;
    QTableWidget *twOUT;
    QPushButton *pbRefer;
    QLineEdit *lePIODLL;
    QCheckBox *chkEchoBack_2;
    QTableWidget *twIN_2;
    QTableWidget *twOUT_2;

    void setupUi(QWidget *PIOWatchClass)
    {
        if (PIOWatchClass->objectName().isEmpty())
            PIOWatchClass->setObjectName("PIOWatchClass");
        PIOWatchClass->resize(1040, 709);
        twIN = new QTableWidget(PIOWatchClass);
        twIN->setObjectName("twIN");
        twIN->setGeometry(QRect(10, 40, 251, 612));
        twIN->setSelectionMode(QAbstractItemView::SingleSelection);
        twIN->setSelectionBehavior(QAbstractItemView::SelectRows);
        twIN->setShowGrid(false);
        twIN->setColumnCount(0);
        chkEchoBack = new QCheckBox(PIOWatchClass);
        chkEchoBack->setObjectName("chkEchoBack");
        chkEchoBack->setGeometry(QRect(20, 670, 81, 17));
        pbClose = new QPushButton(PIOWatchClass);
        pbClose->setObjectName("pbClose");
        pbClose->setGeometry(QRect(410, 660, 101, 41));
        twOUT = new QTableWidget(PIOWatchClass);
        twOUT->setObjectName("twOUT");
        twOUT->setGeometry(QRect(260, 40, 251, 612));
        twOUT->setSelectionMode(QAbstractItemView::SingleSelection);
        twOUT->setSelectionBehavior(QAbstractItemView::SelectRows);
        twOUT->setShowGrid(false);
        twOUT->setColumnCount(0);
        pbRefer = new QPushButton(PIOWatchClass);
        pbRefer->setObjectName("pbRefer");
        pbRefer->setGeometry(QRect(480, 5, 31, 31));
        lePIODLL = new QLineEdit(PIOWatchClass);
        lePIODLL->setObjectName("lePIODLL");
        lePIODLL->setGeometry(QRect(10, 10, 471, 20));
        lePIODLL->setReadOnly(true);
        chkEchoBack_2 = new QCheckBox(PIOWatchClass);
        chkEchoBack_2->setObjectName("chkEchoBack_2");
        chkEchoBack_2->setGeometry(QRect(540, 670, 81, 17));
        twIN_2 = new QTableWidget(PIOWatchClass);
        twIN_2->setObjectName("twIN_2");
        twIN_2->setGeometry(QRect(530, 40, 251, 612));
        twIN_2->setSelectionMode(QAbstractItemView::SingleSelection);
        twIN_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        twIN_2->setShowGrid(false);
        twIN_2->setColumnCount(0);
        twOUT_2 = new QTableWidget(PIOWatchClass);
        twOUT_2->setObjectName("twOUT_2");
        twOUT_2->setGeometry(QRect(780, 40, 251, 612));
        twOUT_2->setSelectionMode(QAbstractItemView::SingleSelection);
        twOUT_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        twOUT_2->setShowGrid(false);
        twOUT_2->setColumnCount(0);

        retranslateUi(PIOWatchClass);

        QMetaObject::connectSlotsByName(PIOWatchClass);
    } // setupUi

    void retranslateUi(QWidget *PIOWatchClass)
    {
        PIOWatchClass->setWindowTitle(QCoreApplication::translate("PIOWatchClass", "PIO Watch", nullptr));
        chkEchoBack->setText(QCoreApplication::translate("PIOWatchClass", "Echo Back", nullptr));
        pbClose->setText(QCoreApplication::translate("PIOWatchClass", "&Close", nullptr));
        pbRefer->setText(QCoreApplication::translate("PIOWatchClass", "\342\200\246", nullptr));
        chkEchoBack_2->setText(QCoreApplication::translate("PIOWatchClass", "Echo Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PIOWatchClass: public Ui_PIOWatchClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIOWATCH_H
