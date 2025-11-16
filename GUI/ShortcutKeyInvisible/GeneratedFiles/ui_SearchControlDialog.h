/********************************************************************************
** Form generated from reading UI file 'SearchControlDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHCONTROLDIALOG_H
#define UI_SEARCHCONTROLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchControlDialog
{
public:
    QTableWidget *tableWidgetComponent;
    QTableWidget *tableWidgetControl;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *SearchControlDialog)
    {
        if (SearchControlDialog->objectName().isEmpty())
            SearchControlDialog->setObjectName("SearchControlDialog");
        SearchControlDialog->resize(968, 680);
        tableWidgetComponent = new QTableWidget(SearchControlDialog);
        if (tableWidgetComponent->columnCount() < 3)
            tableWidgetComponent->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetComponent->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetComponent->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetComponent->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetComponent->setObjectName("tableWidgetComponent");
        tableWidgetComponent->setGeometry(QRect(0, 20, 961, 271));
        tableWidgetComponent->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetComponent->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetControl = new QTableWidget(SearchControlDialog);
        if (tableWidgetControl->columnCount() < 3)
            tableWidgetControl->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetControl->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetControl->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetControl->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidgetControl->setObjectName("tableWidgetControl");
        tableWidgetControl->setGeometry(QRect(0, 320, 961, 301));
        tableWidgetControl->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetControl->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButton = new QPushButton(SearchControlDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(320, 630, 121, 41));
        pushButton_2 = new QPushButton(SearchControlDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(490, 630, 101, 41));
        label = new QLabel(SearchControlDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 961, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(SearchControlDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 300, 961, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(SearchControlDialog);

        QMetaObject::connectSlotsByName(SearchControlDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchControlDialog)
    {
        SearchControlDialog->setWindowTitle(QCoreApplication::translate("SearchControlDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetComponent->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SearchControlDialog", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetComponent->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SearchControlDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetComponent->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SearchControlDialog", "Inst", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetControl->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SearchControlDialog", "Class", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetControl->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SearchControlDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetControl->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("SearchControlDialog", "Path", nullptr));
        pushButton->setText(QCoreApplication::translate("SearchControlDialog", "OK (Select)", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SearchControlDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SearchControlDialog", "Component", nullptr));
        label_2->setText(QCoreApplication::translate("SearchControlDialog", "Control", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchControlDialog: public Ui_SearchControlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHCONTROLDIALOG_H
