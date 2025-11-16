/********************************************************************************
** Form generated from reading UI file 'LoadOutlineOffsetForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADOUTLINEOFFSETFORM_H
#define UI_LOADOUTLINEOFFSETFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadOutlineOffsetFormClass
{
public:
    QPushButton *pbCancel;
    QPushButton *pbOK;
    QLineEdit *lineEdit;
    QTableWidget *twMachineList;

    void setupUi(QDialog *LoadOutlineOffsetFormClass)
    {
        if (LoadOutlineOffsetFormClass->objectName().isEmpty())
            LoadOutlineOffsetFormClass->setObjectName("LoadOutlineOffsetFormClass");
        LoadOutlineOffsetFormClass->resize(502, 277);
        pbCancel = new QPushButton(LoadOutlineOffsetFormClass);
        pbCancel->setObjectName("pbCancel");
        pbCancel->setGeometry(QRect(270, 230, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbCancel->setIcon(icon);
        pbOK = new QPushButton(LoadOutlineOffsetFormClass);
        pbOK->setObjectName("pbOK");
        pbOK->setGeometry(QRect(110, 230, 111, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbOK->setIcon(icon1);
        lineEdit = new QLineEdit(LoadOutlineOffsetFormClass);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 10, 481, 20));
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setReadOnly(true);
        twMachineList = new QTableWidget(LoadOutlineOffsetFormClass);
        twMachineList->setObjectName("twMachineList");
        twMachineList->setGeometry(QRect(10, 30, 481, 192));
        twMachineList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twMachineList->setSelectionMode(QAbstractItemView::SingleSelection);
        twMachineList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(LoadOutlineOffsetFormClass);

        QMetaObject::connectSlotsByName(LoadOutlineOffsetFormClass);
    } // setupUi

    void retranslateUi(QDialog *LoadOutlineOffsetFormClass)
    {
        LoadOutlineOffsetFormClass->setWindowTitle(QCoreApplication::translate("LoadOutlineOffsetFormClass", "LoadOutlineOffsetForm", nullptr));
        pbCancel->setText(QCoreApplication::translate("LoadOutlineOffsetFormClass", "Cancel", nullptr));
        pbOK->setText(QCoreApplication::translate("LoadOutlineOffsetFormClass", "OK", nullptr));
        lineEdit->setText(QCoreApplication::translate("LoadOutlineOffsetFormClass", "Select Machine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadOutlineOffsetFormClass: public Ui_LoadOutlineOffsetFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADOUTLINEOFFSETFORM_H
