/********************************************************************************
** Form generated from reading UI file 'SelectLibraryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYFORM_H
#define UI_SELECTLIBRARYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibraryForm
{
public:
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;

    void setupUi(QWidget *SelectLibraryForm)
    {
        if (SelectLibraryForm->objectName().isEmpty())
            SelectLibraryForm->setObjectName("SelectLibraryForm");
        SelectLibraryForm->resize(221, 351);
        tableWidgetLibList = new QTableWidget(SelectLibraryForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 160, 201, 141));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(SelectLibraryForm);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        pushButtonSelect = new QPushButton(SelectLibraryForm);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(10, 310, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon);
        pushButtonCancel = new QPushButton(SelectLibraryForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(114, 310, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(SelectLibraryForm);

        QMetaObject::connectSlotsByName(SelectLibraryForm);
    } // setupUi

    void retranslateUi(QWidget *SelectLibraryForm)
    {
        SelectLibraryForm->setWindowTitle(QCoreApplication::translate("SelectLibraryForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryForm", "Name", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibraryForm", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibraryForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryForm: public Ui_SelectLibraryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYFORM_H
