/********************************************************************************
** Form generated from reading UI file 'SelectMaskingLibraryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMASKINGLIBRARYFORM_H
#define UI_SELECTMASKINGLIBRARYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectMaskingLibraryFormClass
{
public:
    QFrame *frameLibFolder;
    QPushButton *ButtonSelect;
    QPushButton *ButtonCancel;
    QTableWidget *tableWidgetLibList;

    void setupUi(QDialog *SelectMaskingLibraryFormClass)
    {
        if (SelectMaskingLibraryFormClass->objectName().isEmpty())
            SelectMaskingLibraryFormClass->setObjectName("SelectMaskingLibraryFormClass");
        SelectMaskingLibraryFormClass->resize(483, 385);
        frameLibFolder = new QFrame(SelectMaskingLibraryFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 321));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonSelect = new QPushButton(SelectMaskingLibraryFormClass);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(210, 340, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelect->setIcon(icon);
        ButtonCancel = new QPushButton(SelectMaskingLibraryFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(320, 340, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        tableWidgetLibList = new QTableWidget(SelectMaskingLibraryFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 261, 321));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(SelectMaskingLibraryFormClass);

        QMetaObject::connectSlotsByName(SelectMaskingLibraryFormClass);
    } // setupUi

    void retranslateUi(QDialog *SelectMaskingLibraryFormClass)
    {
        SelectMaskingLibraryFormClass->setWindowTitle(QCoreApplication::translate("SelectMaskingLibraryFormClass", "SelectMaskingLibraryForm", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectMaskingLibraryFormClass", "Select", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectMaskingLibraryFormClass", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectMaskingLibraryFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectMaskingLibraryFormClass", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMaskingLibraryFormClass: public Ui_SelectMaskingLibraryFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMASKINGLIBRARYFORM_H
