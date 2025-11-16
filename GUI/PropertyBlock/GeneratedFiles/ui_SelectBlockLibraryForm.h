/********************************************************************************
** Form generated from reading UI file 'SelectBlockLibraryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTBLOCKLIBRARYFORM_H
#define UI_SELECTBLOCKLIBRARYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectBlockLibraryFormClass
{
public:
    QFrame *frameLibFolder;
    QPushButton *ButtonSelect;
    QPushButton *ButtonCancel;
    QTableWidget *tableWidgetLibList;

    void setupUi(QDialog *SelectBlockLibraryFormClass)
    {
        if (SelectBlockLibraryFormClass->objectName().isEmpty())
            SelectBlockLibraryFormClass->setObjectName("SelectBlockLibraryFormClass");
        SelectBlockLibraryFormClass->resize(493, 385);
        frameLibFolder = new QFrame(SelectBlockLibraryFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 321));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonSelect = new QPushButton(SelectBlockLibraryFormClass);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(210, 340, 121, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelect->setIcon(icon);
        ButtonCancel = new QPushButton(SelectBlockLibraryFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(380, 340, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        tableWidgetLibList = new QTableWidget(SelectBlockLibraryFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 271, 321));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(SelectBlockLibraryFormClass);

        QMetaObject::connectSlotsByName(SelectBlockLibraryFormClass);
    } // setupUi

    void retranslateUi(QDialog *SelectBlockLibraryFormClass)
    {
        SelectBlockLibraryFormClass->setWindowTitle(QCoreApplication::translate("SelectBlockLibraryFormClass", "Select Block Library", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectBlockLibraryFormClass", "Select", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectBlockLibraryFormClass", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectBlockLibraryFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectBlockLibraryFormClass", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectBlockLibraryFormClass: public Ui_SelectBlockLibraryFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTBLOCKLIBRARYFORM_H
