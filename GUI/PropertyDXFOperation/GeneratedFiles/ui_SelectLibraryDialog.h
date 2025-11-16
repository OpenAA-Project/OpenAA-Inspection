/********************************************************************************
** Form generated from reading UI file 'SelectLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYDIALOG_H
#define UI_SELECTLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibraryDialog
{
public:
    QTableWidget *tableWidgetAlgorithm;
    QLabel *label;
    QFrame *frameLibFolderSelect;
    QTableWidget *tableWidgetLibListSelect;
    QLabel *label_2;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SelectLibraryDialog)
    {
        if (SelectLibraryDialog->objectName().isEmpty())
            SelectLibraryDialog->setObjectName("SelectLibraryDialog");
        SelectLibraryDialog->resize(534, 498);
        tableWidgetAlgorithm = new QTableWidget(SelectLibraryDialog);
        if (tableWidgetAlgorithm->columnCount() < 3)
            tableWidgetAlgorithm->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetAlgorithm->setObjectName("tableWidgetAlgorithm");
        tableWidgetAlgorithm->setGeometry(QRect(10, 30, 511, 141));
        tableWidgetAlgorithm->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAlgorithm->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(SelectLibraryDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 511, 18));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        frameLibFolderSelect = new QFrame(SelectLibraryDialog);
        frameLibFolderSelect->setObjectName("frameLibFolderSelect");
        frameLibFolderSelect->setGeometry(QRect(10, 210, 241, 231));
        frameLibFolderSelect->setFrameShape(QFrame::StyledPanel);
        frameLibFolderSelect->setFrameShadow(QFrame::Sunken);
        tableWidgetLibListSelect = new QTableWidget(SelectLibraryDialog);
        if (tableWidgetLibListSelect->columnCount() < 2)
            tableWidgetLibListSelect->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLibListSelect->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetLibListSelect->setObjectName("tableWidgetLibListSelect");
        tableWidgetLibListSelect->setGeometry(QRect(260, 210, 261, 231));
        tableWidgetLibListSelect->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetLibListSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(SelectLibraryDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 190, 511, 18));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonSelect = new QPushButton(SelectLibraryDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(260, 450, 112, 34));
        pushButtonClose = new QPushButton(SelectLibraryDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(410, 450, 112, 34));

        retranslateUi(SelectLibraryDialog);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(SelectLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryDialog)
    {
        SelectLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAlgorithm->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryDialog", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAlgorithm->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetAlgorithm->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectLibraryDialog", "Explain", nullptr));
        label->setText(QCoreApplication::translate("SelectLibraryDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\256\347\250\256\351\241\236", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibListSelect->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLibListSelect->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectLibraryDialog", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("SelectLibraryDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\351\201\270\346\212\236", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryDialog", "\351\201\270\346\212\236", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SelectLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryDialog: public Ui_SelectLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYDIALOG_H
