/********************************************************************************
** Form generated from reading UI file 'SelectDirectoryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDIRECTORYDIALOG_H
#define UI_SELECTDIRECTORYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_SelectDirectoryDialog
{
public:
    QTreeView *treeView;
    QLineEdit *lineEditDirectory;
    QFrame *frame;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectDirectoryDialog)
    {
        if (SelectDirectoryDialog->objectName().isEmpty())
            SelectDirectoryDialog->setObjectName("SelectDirectoryDialog");
        SelectDirectoryDialog->resize(732, 362);
        treeView = new QTreeView(SelectDirectoryDialog);
        treeView->setObjectName("treeView");
        treeView->setGeometry(QRect(10, 10, 711, 261));
        lineEditDirectory = new QLineEdit(SelectDirectoryDialog);
        lineEditDirectory->setObjectName("lineEditDirectory");
        lineEditDirectory->setGeometry(QRect(10, 280, 711, 24));
        frame = new QFrame(SelectDirectoryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 310, 731, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(frame);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(240, 10, 112, 34));
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(380, 10, 112, 34));

        retranslateUi(SelectDirectoryDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectDirectoryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDirectoryDialog)
    {
        SelectDirectoryDialog->setWindowTitle(QCoreApplication::translate("SelectDirectoryDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectDirectoryDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectDirectoryDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDirectoryDialog: public Ui_SelectDirectoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDIRECTORYDIALOG_H
