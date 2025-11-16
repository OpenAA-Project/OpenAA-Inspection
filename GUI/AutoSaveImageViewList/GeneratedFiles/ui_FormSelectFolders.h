/********************************************************************************
** Form generated from reading UI file 'FormSelectFolders.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSELECTFOLDERS_H
#define UI_FORMSELECTFOLDERS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_FormSelectFoldersClass
{
public:
    QTreeView *treeViewFolders;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *FormSelectFoldersClass)
    {
        if (FormSelectFoldersClass->objectName().isEmpty())
            FormSelectFoldersClass->setObjectName("FormSelectFoldersClass");
        FormSelectFoldersClass->resize(564, 399);
        treeViewFolders = new QTreeView(FormSelectFoldersClass);
        treeViewFolders->setObjectName("treeViewFolders");
        treeViewFolders->setGeometry(QRect(10, 10, 541, 331));
        treeViewFolders->setSelectionMode(QAbstractItemView::MultiSelection);
        pushButtonOK = new QPushButton(FormSelectFoldersClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(180, 350, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(FormSelectFoldersClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(290, 350, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(FormSelectFoldersClass);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(FormSelectFoldersClass);
    } // setupUi

    void retranslateUi(QDialog *FormSelectFoldersClass)
    {
        FormSelectFoldersClass->setWindowTitle(QCoreApplication::translate("FormSelectFoldersClass", "FormSelectFolders", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("FormSelectFoldersClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("FormSelectFoldersClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormSelectFoldersClass: public Ui_FormSelectFoldersClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSELECTFOLDERS_H
