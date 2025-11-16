/********************************************************************************
** Form generated from reading UI file 'EditSourceDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSOURCEDIALOG_H
#define UI_EDITSOURCEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditSourceDialog
{
public:
    QTableWidget *tableWidgetAlgorithm;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelPage;
    QLabel *labelLayer;
    QLabel *label_5;
    QTableWidget *tableWidgetItems;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButtonDeleteLines;
    QPushButton *pushButtonAddItem;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditSourceDialog)
    {
        if (EditSourceDialog->objectName().isEmpty())
            EditSourceDialog->setObjectName("EditSourceDialog");
        EditSourceDialog->resize(644, 506);
        tableWidgetAlgorithm = new QTableWidget(EditSourceDialog);
        if (tableWidgetAlgorithm->columnCount() < 2)
            tableWidgetAlgorithm->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetAlgorithm->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetAlgorithm->setObjectName("tableWidgetAlgorithm");
        tableWidgetAlgorithm->setGeometry(QRect(10, 110, 241, 281));
        tableWidgetAlgorithm->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAlgorithm->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(EditSourceDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 62, 15));
        label_2 = new QLabel(EditSourceDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 62, 15));
        labelPage = new QLabel(EditSourceDialog);
        labelPage->setObjectName("labelPage");
        labelPage->setGeometry(QRect(80, 40, 62, 15));
        labelPage->setFrameShape(QFrame::Panel);
        labelPage->setFrameShadow(QFrame::Sunken);
        labelPage->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelLayer = new QLabel(EditSourceDialog);
        labelLayer->setObjectName("labelLayer");
        labelLayer->setGeometry(QRect(80, 60, 62, 15));
        labelLayer->setFrameShape(QFrame::Panel);
        labelLayer->setFrameShadow(QFrame::Sunken);
        labelLayer->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(EditSourceDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 90, 241, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        tableWidgetItems = new QTableWidget(EditSourceDialog);
        if (tableWidgetItems->columnCount() < 3)
            tableWidgetItems->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        tableWidgetItems->setObjectName("tableWidgetItems");
        tableWidgetItems->setGeometry(QRect(260, 110, 371, 281));
        tableWidgetItems->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetItems->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_6 = new QLabel(EditSourceDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(260, 90, 371, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(EditSourceDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 0, 621, 20));
        pushButtonDeleteLines = new QPushButton(EditSourceDialog);
        pushButtonDeleteLines->setObjectName("pushButtonDeleteLines");
        pushButtonDeleteLines->setGeometry(QRect(290, 400, 93, 28));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDeleteLines->setIcon(icon);
        pushButtonAddItem = new QPushButton(EditSourceDialog);
        pushButtonAddItem->setObjectName("pushButtonAddItem");
        pushButtonAddItem->setGeometry(QRect(520, 400, 93, 28));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddItem->setIcon(icon1);
        pushButtonOK = new QPushButton(EditSourceDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(120, 450, 93, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon2);
        pushButtonCancel = new QPushButton(EditSourceDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(400, 450, 93, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon3);

        retranslateUi(EditSourceDialog);

        pushButtonOK->setDefault(true);
        pushButtonCancel->setDefault(false);


        QMetaObject::connectSlotsByName(EditSourceDialog);
    } // setupUi

    void retranslateUi(QDialog *EditSourceDialog)
    {
        EditSourceDialog->setWindowTitle(QCoreApplication::translate("EditSourceDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetAlgorithm->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditSourceDialog", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetAlgorithm->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditSourceDialog", "Name", nullptr));
        label->setText(QCoreApplication::translate("EditSourceDialog", "Page", nullptr));
        label_2->setText(QCoreApplication::translate("EditSourceDialog", "Layer", nullptr));
        labelPage->setText(QCoreApplication::translate("EditSourceDialog", "0", nullptr));
        labelLayer->setText(QCoreApplication::translate("EditSourceDialog", "0", nullptr));
        label_5->setText(QCoreApplication::translate("EditSourceDialog", "Algorithm", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItems->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditSourceDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetItems->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EditSourceDialog", "ItemName", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetItems->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("EditSourceDialog", "Area", nullptr));
        label_6->setText(QCoreApplication::translate("EditSourceDialog", "Source items", nullptr));
        label_7->setText(QCoreApplication::translate("EditSourceDialog", "When one or more of these items makes NG, all results of Naming area are changed to OK", nullptr));
        pushButtonDeleteLines->setText(QCoreApplication::translate("EditSourceDialog", "Delete lines", nullptr));
        pushButtonAddItem->setText(QCoreApplication::translate("EditSourceDialog", "Add item", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditSourceDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditSourceDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditSourceDialog: public Ui_EditSourceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSOURCEDIALOG_H
