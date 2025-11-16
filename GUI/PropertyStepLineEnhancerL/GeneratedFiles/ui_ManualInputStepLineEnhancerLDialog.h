/********************************************************************************
** Form generated from reading UI file 'ManualInputStepLineEnhancerLDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALINPUTSTEPLINEENHANCERLDIALOG_H
#define UI_MANUALINPUTSTEPLINEENHANCERLDIALOG_H

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

class Ui_ManualInputStepLineEnhancerLDialog
{
public:
    QPushButton *ButtonCancel;
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonOK;
    QLineEdit *EditLibName;
    QFrame *frameLibFolder;
    QLineEdit *EditLibID;

    void setupUi(QDialog *ManualInputStepLineEnhancerLDialog)
    {
        if (ManualInputStepLineEnhancerLDialog->objectName().isEmpty())
            ManualInputStepLineEnhancerLDialog->setObjectName(QString::fromUtf8("ManualInputStepLineEnhancerLDialog"));
        ManualInputStepLineEnhancerLDialog->resize(419, 244);
        ButtonCancel = new QPushButton(ManualInputStepLineEnhancerLDialog);
        ButtonCancel->setObjectName(QString::fromUtf8("ButtonCancel"));
        ButtonCancel->setGeometry(QRect(270, 200, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonCancel->setIcon(icon);
        tableWidgetLibList = new QTableWidget(ManualInputStepLineEnhancerLDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName(QString::fromUtf8("tableWidgetLibList"));
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonOK = new QPushButton(ManualInputStepLineEnhancerLDialog);
        ButtonOK->setObjectName(QString::fromUtf8("ButtonOK"));
        ButtonOK->setGeometry(QRect(30, 200, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonOK->setIcon(icon1);
        EditLibName = new QLineEdit(ManualInputStepLineEnhancerLDialog);
        EditLibName->setObjectName(QString::fromUtf8("EditLibName"));
        EditLibName->setGeometry(QRect(80, 160, 251, 21));
        EditLibName->setReadOnly(true);
        frameLibFolder = new QFrame(ManualInputStepLineEnhancerLDialog);
        frameLibFolder->setObjectName(QString::fromUtf8("frameLibFolder"));
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        EditLibID = new QLineEdit(ManualInputStepLineEnhancerLDialog);
        EditLibID->setObjectName(QString::fromUtf8("EditLibID"));
        EditLibID->setGeometry(QRect(40, 160, 41, 21));
        EditLibID->setReadOnly(true);

        retranslateUi(ManualInputStepLineEnhancerLDialog);

        QMetaObject::connectSlotsByName(ManualInputStepLineEnhancerLDialog);
    } // setupUi

    void retranslateUi(QDialog *ManualInputStepLineEnhancerLDialog)
    {
        ManualInputStepLineEnhancerLDialog->setWindowTitle(QCoreApplication::translate("ManualInputStepLineEnhancerLDialog", "Manual Input StepLineEnhancer", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ManualInputStepLineEnhancerLDialog", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ManualInputStepLineEnhancerLDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ManualInputStepLineEnhancerLDialog", "Name", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ManualInputStepLineEnhancerLDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManualInputStepLineEnhancerLDialog: public Ui_ManualInputStepLineEnhancerLDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALINPUTSTEPLINEENHANCERLDIALOG_H
