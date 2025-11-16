/********************************************************************************
** Form generated from reading UI file 'SelectHoleWallLibraryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTHOLEWALLLIBRARYFORM_H
#define UI_SELECTHOLEWALLLIBRARYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectHoleWallLibraryForm
{
public:
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonCancel;
    QFrame *frameLibFolder;
    QPushButton *ButtonSelect;

    void setupUi(QDialog *SelectHoleWallLibraryForm)
    {
        if (SelectHoleWallLibraryForm->objectName().isEmpty())
            SelectHoleWallLibraryForm->setObjectName("SelectHoleWallLibraryForm");
        SelectHoleWallLibraryForm->resize(421, 382);
        tableWidgetLibList = new QTableWidget(SelectHoleWallLibraryForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 321));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonCancel = new QPushButton(SelectHoleWallLibraryForm);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(320, 340, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        frameLibFolder = new QFrame(SelectHoleWallLibraryForm);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 321));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonSelect = new QPushButton(SelectHoleWallLibraryForm);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(210, 340, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelect->setIcon(icon1);

        retranslateUi(SelectHoleWallLibraryForm);

        QMetaObject::connectSlotsByName(SelectHoleWallLibraryForm);
    } // setupUi

    void retranslateUi(QDialog *SelectHoleWallLibraryForm)
    {
        SelectHoleWallLibraryForm->setWindowTitle(QCoreApplication::translate("SelectHoleWallLibraryForm", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectHoleWallLibraryForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectHoleWallLibraryForm", "Name", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectHoleWallLibraryForm", "Cancel", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectHoleWallLibraryForm", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectHoleWallLibraryForm: public Ui_SelectHoleWallLibraryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTHOLEWALLLIBRARYFORM_H
