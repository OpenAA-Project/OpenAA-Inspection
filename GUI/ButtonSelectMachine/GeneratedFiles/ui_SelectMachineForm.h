/********************************************************************************
** Form generated from reading UI file 'SelectMachineForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMACHINEFORM_H
#define UI_SELECTMACHINEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectMachineFormClass
{
public:
    QTableWidget *twMachineList;
    QPushButton *pbOK;
    QLineEdit *lineEdit;
    QPushButton *pbCancel;

    void setupUi(QDialog *SelectMachineFormClass)
    {
        if (SelectMachineFormClass->objectName().isEmpty())
            SelectMachineFormClass->setObjectName("SelectMachineFormClass");
        SelectMachineFormClass->resize(520, 289);
        twMachineList = new QTableWidget(SelectMachineFormClass);
        twMachineList->setObjectName("twMachineList");
        twMachineList->setGeometry(QRect(20, 40, 481, 192));
        twMachineList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twMachineList->setSelectionMode(QAbstractItemView::SingleSelection);
        twMachineList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pbOK = new QPushButton(SelectMachineFormClass);
        pbOK->setObjectName("pbOK");
        pbOK->setGeometry(QRect(120, 240, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbOK->setIcon(icon);
        lineEdit = new QLineEdit(SelectMachineFormClass);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(20, 20, 481, 20));
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setReadOnly(true);
        pbCancel = new QPushButton(SelectMachineFormClass);
        pbCancel->setObjectName("pbCancel");
        pbCancel->setGeometry(QRect(280, 240, 111, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbCancel->setIcon(icon1);

        retranslateUi(SelectMachineFormClass);

        QMetaObject::connectSlotsByName(SelectMachineFormClass);
    } // setupUi

    void retranslateUi(QDialog *SelectMachineFormClass)
    {
        SelectMachineFormClass->setWindowTitle(QCoreApplication::translate("SelectMachineFormClass", "SelectMachineForm", nullptr));
        pbOK->setText(QCoreApplication::translate("SelectMachineFormClass", "OK", nullptr));
        lineEdit->setText(QCoreApplication::translate("SelectMachineFormClass", "Select Machine", nullptr));
        pbCancel->setText(QCoreApplication::translate("SelectMachineFormClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMachineFormClass: public Ui_SelectMachineFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMACHINEFORM_H
