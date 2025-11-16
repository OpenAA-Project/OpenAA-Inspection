/********************************************************************************
** Form generated from reading UI file 'ManualInputProjectedInspectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALINPUTPROJECTEDINSPECTIONDIALOG_H
#define UI_MANUALINPUTPROJECTEDINSPECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ManualInputProjectedInspectionDialog
{
public:
    QTableWidget *tableWidgetLibList;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;
    QFrame *frameLibFolder;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;

    void setupUi(QDialog *ManualInputProjectedInspectionDialog)
    {
        if (ManualInputProjectedInspectionDialog->objectName().isEmpty())
            ManualInputProjectedInspectionDialog->setObjectName("ManualInputProjectedInspectionDialog");
        ManualInputProjectedInspectionDialog->resize(422, 244);
        tableWidgetLibList = new QTableWidget(ManualInputProjectedInspectionDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        EditLibName = new QLineEdit(ManualInputProjectedInspectionDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(80, 160, 251, 21));
        EditLibName->setReadOnly(true);
        EditLibID = new QLineEdit(ManualInputProjectedInspectionDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(40, 160, 41, 21));
        EditLibID->setReadOnly(true);
        frameLibFolder = new QFrame(ManualInputProjectedInspectionDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonOK = new QPushButton(ManualInputProjectedInspectionDialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(30, 200, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(ManualInputProjectedInspectionDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(270, 200, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);

        retranslateUi(ManualInputProjectedInspectionDialog);

        QMetaObject::connectSlotsByName(ManualInputProjectedInspectionDialog);
    } // setupUi

    void retranslateUi(QDialog *ManualInputProjectedInspectionDialog)
    {
        ManualInputProjectedInspectionDialog->setWindowTitle(QCoreApplication::translate("ManualInputProjectedInspectionDialog", "Manual Input ProjectedInspection", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ManualInputProjectedInspectionDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ManualInputProjectedInspectionDialog", "Name", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ManualInputProjectedInspectionDialog", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ManualInputProjectedInspectionDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManualInputProjectedInspectionDialog: public Ui_ManualInputProjectedInspectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALINPUTPROJECTEDINSPECTIONDIALOG_H
