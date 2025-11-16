/********************************************************************************
** Form generated from reading UI file 'SearchItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHITEMDIALOG_H
#define UI_SEARCHITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchItemDialog
{
public:
    QTableWidget *tableWidgetItems;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QFrame *frame;
    QLineEdit *lineEditTopName;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxTopID;
    QPushButton *pushButtonSortByID;
    QPushButton *pushButtonSortByName;
    QPushButton *pushButtonSortByLibID;

    void setupUi(QDialog *SearchItemDialog)
    {
        if (SearchItemDialog->objectName().isEmpty())
            SearchItemDialog->setObjectName("SearchItemDialog");
        SearchItemDialog->resize(794, 591);
        tableWidgetItems = new QTableWidget(SearchItemDialog);
        if (tableWidgetItems->columnCount() < 5)
            tableWidgetItems->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetItems->setObjectName("tableWidgetItems");
        tableWidgetItems->setGeometry(QRect(10, 120, 771, 421));
        tableWidgetItems->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetItems->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(SearchItemDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(80, 550, 93, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(SearchItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(640, 550, 93, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        frame = new QFrame(SearchItemDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 771, 101));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        lineEditTopName = new QLineEdit(frame);
        lineEditTopName->setObjectName("lineEditTopName");
        lineEditTopName->setGeometry(QRect(130, 30, 121, 21));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 10, 121, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 10, 91, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxTopID = new QSpinBox(frame);
        spinBoxTopID->setObjectName("spinBoxTopID");
        spinBoxTopID->setGeometry(QRect(20, 30, 91, 22));
        spinBoxTopID->setMaximum(999999999);
        pushButtonSortByID = new QPushButton(frame);
        pushButtonSortByID->setObjectName("pushButtonSortByID");
        pushButtonSortByID->setGeometry(QRect(20, 60, 93, 28));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/SortNumber.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSortByID->setIcon(icon2);
        pushButtonSortByName = new QPushButton(frame);
        pushButtonSortByName->setObjectName("pushButtonSortByName");
        pushButtonSortByName->setGeometry(QRect(140, 60, 101, 28));
        pushButtonSortByName->setIcon(icon2);
        pushButtonSortByLibID = new QPushButton(frame);
        pushButtonSortByLibID->setObjectName("pushButtonSortByLibID");
        pushButtonSortByLibID->setGeometry(QRect(430, 60, 111, 28));
        pushButtonSortByLibID->setIcon(icon2);

        retranslateUi(SearchItemDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SearchItemDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchItemDialog)
    {
        SearchItemDialog->setWindowTitle(QCoreApplication::translate("SearchItemDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItems->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SearchItemDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItems->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SearchItemDialog", "Item name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItems->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SearchItemDialog", "Area", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetItems->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SearchItemDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItems->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SearchItemDialog", "Lib name", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SearchItemDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SearchItemDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SearchItemDialog", "By name", nullptr));
        label_2->setText(QCoreApplication::translate("SearchItemDialog", "By ID", nullptr));
        pushButtonSortByID->setText(QCoreApplication::translate("SearchItemDialog", "Sort and top", nullptr));
        pushButtonSortByName->setText(QCoreApplication::translate("SearchItemDialog", "Sort and top", nullptr));
        pushButtonSortByLibID->setText(QCoreApplication::translate("SearchItemDialog", "Sort by LibID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchItemDialog: public Ui_SearchItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHITEMDIALOG_H
