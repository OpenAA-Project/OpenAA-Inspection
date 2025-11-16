/********************************************************************************
** Form generated from reading UI file 'ManualInputLineEnhancerL1Dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALINPUTLINEENHANCERL1DIALOG_H
#define UI_MANUALINPUTLINEENHANCERL1DIALOG_H

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

class Ui_ManualInputLineEnhancerL1Dialog
{
public:
    QTableWidget *tableWidgetLibList;
    QLineEdit *EditLibName;
    QPushButton *ButtonCancel;
    QLineEdit *EditLibID;
    QPushButton *ButtonOK;
    QFrame *frameLibFolder;

    void setupUi(QDialog *ManualInputLineEnhancerL1Dialog)
    {
        if (ManualInputLineEnhancerL1Dialog->objectName().isEmpty())
            ManualInputLineEnhancerL1Dialog->setObjectName("ManualInputLineEnhancerL1Dialog");
        ManualInputLineEnhancerL1Dialog->resize(423, 248);
        tableWidgetLibList = new QTableWidget(ManualInputLineEnhancerL1Dialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        EditLibName = new QLineEdit(ManualInputLineEnhancerL1Dialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(80, 160, 251, 21));
        EditLibName->setReadOnly(true);
        ButtonCancel = new QPushButton(ManualInputLineEnhancerL1Dialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(270, 200, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        EditLibID = new QLineEdit(ManualInputLineEnhancerL1Dialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(40, 160, 41, 21));
        EditLibID->setReadOnly(true);
        ButtonOK = new QPushButton(ManualInputLineEnhancerL1Dialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(30, 200, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon1);
        frameLibFolder = new QFrame(ManualInputLineEnhancerL1Dialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);

        retranslateUi(ManualInputLineEnhancerL1Dialog);

        QMetaObject::connectSlotsByName(ManualInputLineEnhancerL1Dialog);
    } // setupUi

    void retranslateUi(QDialog *ManualInputLineEnhancerL1Dialog)
    {
        ManualInputLineEnhancerL1Dialog->setWindowTitle(QCoreApplication::translate("ManualInputLineEnhancerL1Dialog", "Manual Input LineEnhancerL1", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ManualInputLineEnhancerL1Dialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ManualInputLineEnhancerL1Dialog", "Name", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ManualInputLineEnhancerL1Dialog", "Cancel", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ManualInputLineEnhancerL1Dialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManualInputLineEnhancerL1Dialog: public Ui_ManualInputLineEnhancerL1Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALINPUTLINEENHANCERL1DIALOG_H
