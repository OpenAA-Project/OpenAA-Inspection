/********************************************************************************
** Form generated from reading UI file 'ShowMarkForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWMARKFORM_H
#define UI_SHOWMARKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowMarkForm
{
public:
    QTableWidget *tableWidgetPhaseList;
    QLabel *label_2;
    QSpinBox *spinBoxSearchDot;
    QPushButton *ButtonClose;
    QPushButton *ButtonReflectAllBlocks;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonReflectOnlyBlock;
    QWidget *page_3;
    QPushButton *ButtonReflectSaveParts;
    QWidget *page_2;

    void setupUi(QWidget *ShowMarkForm)
    {
        if (ShowMarkForm->objectName().isEmpty())
            ShowMarkForm->setObjectName("ShowMarkForm");
        ShowMarkForm->resize(842, 540);
        tableWidgetPhaseList = new QTableWidget(ShowMarkForm);
        if (tableWidgetPhaseList->columnCount() < 6)
            tableWidgetPhaseList->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPhaseList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPhaseList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPhaseList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetPhaseList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetPhaseList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetPhaseList->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidgetPhaseList->rowCount() < 1)
            tableWidgetPhaseList->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetPhaseList->setVerticalHeaderItem(0, __qtablewidgetitem6);
        tableWidgetPhaseList->setObjectName("tableWidgetPhaseList");
        tableWidgetPhaseList->setGeometry(QRect(10, 10, 821, 421));
        tableWidgetPhaseList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPhaseList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(ShowMarkForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(250, 440, 141, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxSearchDot = new QSpinBox(ShowMarkForm);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(250, 460, 141, 24));
        spinBoxSearchDot->setMaximum(99999);
        ButtonClose = new QPushButton(ShowMarkForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(670, 490, 161, 41));
        ButtonReflectAllBlocks = new QPushButton(ShowMarkForm);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(670, 440, 161, 41));
        stackedWidgetParts = new QStackedWidget(ShowMarkForm);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(500, 440, 161, 41));
        page = new QWidget();
        page->setObjectName("page");
        ButtonReflectOnlyBlock = new QPushButton(page);
        ButtonReflectOnlyBlock->setObjectName("ButtonReflectOnlyBlock");
        ButtonReflectOnlyBlock->setGeometry(QRect(0, 0, 161, 41));
        stackedWidgetParts->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        ButtonReflectSaveParts = new QPushButton(page_3);
        ButtonReflectSaveParts->setObjectName("ButtonReflectSaveParts");
        ButtonReflectSaveParts->setGeometry(QRect(0, 0, 221, 31));
        stackedWidgetParts->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetParts->addWidget(page_2);

        retranslateUi(ShowMarkForm);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ShowMarkForm);
    } // setupUi

    void retranslateUi(QWidget *ShowMarkForm)
    {
        ShowMarkForm->setWindowTitle(QCoreApplication::translate("ShowMarkForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPhaseList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowMarkForm", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPhaseList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowMarkForm", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPhaseList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowMarkForm", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetPhaseList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowMarkForm", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetPhaseList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowMarkForm", "TotalResult", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetPhaseList->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ShowMarkForm", "Shift", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetPhaseList->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ShowMarkForm", "Phase0", nullptr));
        label_2->setText(QCoreApplication::translate("ShowMarkForm", "SearchDot", nullptr));
        ButtonClose->setText(QCoreApplication::translate("ShowMarkForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("ShowMarkForm", "\345\205\250\343\201\246\343\201\256\343\203\236\343\203\274\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonReflectOnlyBlock->setText(QCoreApplication::translate("ShowMarkForm", "\343\201\223\343\201\256\343\203\236\343\203\274\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonReflectSaveParts->setText(QCoreApplication::translate("ShowMarkForm", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowMarkForm: public Ui_ShowMarkForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWMARKFORM_H
