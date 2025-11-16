/********************************************************************************
** Form generated from reading UI file 'SelectAreaFilterLibrary.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTAREAFILTERLIBRARY_H
#define UI_SELECTAREAFILTERLIBRARY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectAreaFilterLibraryClass
{
public:
    QPushButton *ButtonSelect;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonCancel;

    void setupUi(QDialog *SelectAreaFilterLibraryClass)
    {
        if (SelectAreaFilterLibraryClass->objectName().isEmpty())
            SelectAreaFilterLibraryClass->setObjectName("SelectAreaFilterLibraryClass");
        SelectAreaFilterLibraryClass->resize(422, 201);
        ButtonSelect = new QPushButton(SelectAreaFilterLibraryClass);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(210, 160, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelect->setIcon(icon);
        frameLibFolder = new QFrame(SelectAreaFilterLibraryClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(SelectAreaFilterLibraryClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonCancel = new QPushButton(SelectAreaFilterLibraryClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(320, 160, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);

        retranslateUi(SelectAreaFilterLibraryClass);

        QMetaObject::connectSlotsByName(SelectAreaFilterLibraryClass);
    } // setupUi

    void retranslateUi(QDialog *SelectAreaFilterLibraryClass)
    {
        SelectAreaFilterLibraryClass->setWindowTitle(QCoreApplication::translate("SelectAreaFilterLibraryClass", "SelectAreaFilterLibrary", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectAreaFilterLibraryClass", "Select", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectAreaFilterLibraryClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectAreaFilterLibraryClass", "Name", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectAreaFilterLibraryClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectAreaFilterLibraryClass: public Ui_SelectAreaFilterLibraryClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTAREAFILTERLIBRARY_H
