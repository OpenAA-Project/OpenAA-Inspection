/********************************************************************************
** Form generated from reading UI file 'SelectEulerRingL1LibraryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTEULERRINGL1LIBRARYFORM_H
#define UI_SELECTEULERRINGL1LIBRARYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectEulerRingL1LibraryFormClass
{
public:
    QFrame *frameLibFolder;
    QPushButton *ButtonSelect;
    QPushButton *ButtonCancel;
    QTableWidget *tableWidgetLibList;

    void setupUi(QDialog *SelectEulerRingL1LibraryFormClass)
    {
        if (SelectEulerRingL1LibraryFormClass->objectName().isEmpty())
            SelectEulerRingL1LibraryFormClass->setObjectName("SelectEulerRingL1LibraryFormClass");
        SelectEulerRingL1LibraryFormClass->resize(413, 385);
        frameLibFolder = new QFrame(SelectEulerRingL1LibraryFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 321));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonSelect = new QPushButton(SelectEulerRingL1LibraryFormClass);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(210, 340, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelect->setIcon(icon);
        ButtonCancel = new QPushButton(SelectEulerRingL1LibraryFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(320, 340, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        tableWidgetLibList = new QTableWidget(SelectEulerRingL1LibraryFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 321));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(SelectEulerRingL1LibraryFormClass);

        QMetaObject::connectSlotsByName(SelectEulerRingL1LibraryFormClass);
    } // setupUi

    void retranslateUi(QDialog *SelectEulerRingL1LibraryFormClass)
    {
        SelectEulerRingL1LibraryFormClass->setWindowTitle(QCoreApplication::translate("SelectEulerRingL1LibraryFormClass", "SelectEulerRingL1LibraryForm", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectEulerRingL1LibraryFormClass", "Select", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectEulerRingL1LibraryFormClass", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectEulerRingL1LibraryFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectEulerRingL1LibraryFormClass", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectEulerRingL1LibraryFormClass: public Ui_SelectEulerRingL1LibraryFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTEULERRINGL1LIBRARYFORM_H
