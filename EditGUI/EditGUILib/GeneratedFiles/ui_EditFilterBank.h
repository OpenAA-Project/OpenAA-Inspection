/********************************************************************************
** Form generated from reading UI file 'EditFilterBank.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITFILTERBANK_H
#define UI_EDITFILTERBANK_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditFilterBank
{
public:
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonLoadFiles;
    QPushButton *pushButtonDown;
    QTableWidget *tableWidgetFilter;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonDelete;

    void setupUi(QWidget *EditFilterBank)
    {
        if (EditFilterBank->objectName().isEmpty())
            EditFilterBank->setObjectName("EditFilterBank");
        EditFilterBank->resize(460, 310);
        pushButtonCancel = new QPushButton(EditFilterBank);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(230, 260, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonLoadFiles = new QPushButton(EditFilterBank);
        pushButtonLoadFiles->setObjectName("pushButtonLoadFiles");
        pushButtonLoadFiles->setGeometry(QRect(50, 10, 101, 41));
        pushButtonDown = new QPushButton(EditFilterBank);
        pushButtonDown->setObjectName("pushButtonDown");
        pushButtonDown->setGeometry(QRect(370, 140, 75, 41));
        tableWidgetFilter = new QTableWidget(EditFilterBank);
        if (tableWidgetFilter->columnCount() < 2)
            tableWidgetFilter->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetFilter->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetFilter->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetFilter->setObjectName("tableWidgetFilter");
        tableWidgetFilter->setGeometry(QRect(10, 60, 351, 191));
        tableWidgetFilter->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetFilter->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(EditFilterBank);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(30, 260, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        pushButtonUp = new QPushButton(EditFilterBank);
        pushButtonUp->setObjectName("pushButtonUp");
        pushButtonUp->setGeometry(QRect(370, 90, 75, 41));
        pushButtonDelete = new QPushButton(EditFilterBank);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(370, 200, 75, 41));

        retranslateUi(EditFilterBank);

        QMetaObject::connectSlotsByName(EditFilterBank);
    } // setupUi

    void retranslateUi(QWidget *EditFilterBank)
    {
        EditFilterBank->setWindowTitle(QCoreApplication::translate("EditFilterBank", "Form", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditFilterBank", "Cancel", nullptr));
        pushButtonLoadFiles->setText(QCoreApplication::translate("EditFilterBank", "Load files", nullptr));
        pushButtonDown->setText(QCoreApplication::translate("EditFilterBank", "Down", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetFilter->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditFilterBank", "FileNo", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetFilter->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditFilterBank", "Path/File", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditFilterBank", "OK", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("EditFilterBank", "Up", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EditFilterBank", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditFilterBank: public Ui_EditFilterBank {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITFILTERBANK_H
