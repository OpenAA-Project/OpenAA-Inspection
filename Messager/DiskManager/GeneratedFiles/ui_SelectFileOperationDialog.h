/********************************************************************************
** Form generated from reading UI file 'SelectFileOperationDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTFILEOPERATIONDIALOG_H
#define UI_SELECTFILEOPERATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectFileOperationDialog
{
public:
    QPushButton *pushButtonDelete;
    QLineEdit *lineEditPath;
    QLineEdit *lineEditFileName;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditPCName;
    QLineEdit *lineEditDestination;
    QLabel *label_4;
    QPushButton *pushButtonSelectDestination;
    QPushButton *pushButtonMoveStart;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SelectFileOperationDialog)
    {
        if (SelectFileOperationDialog->objectName().isEmpty())
            SelectFileOperationDialog->setObjectName("SelectFileOperationDialog");
        SelectFileOperationDialog->resize(400, 291);
        pushButtonDelete = new QPushButton(SelectFileOperationDialog);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(10, 90, 161, 28));
        lineEditPath = new QLineEdit(SelectFileOperationDialog);
        lineEditPath->setObjectName("lineEditPath");
        lineEditPath->setGeometry(QRect(70, 30, 321, 21));
        lineEditFileName = new QLineEdit(SelectFileOperationDialog);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(70, 50, 321, 21));
        label = new QLabel(SelectFileOperationDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 31, 16));
        label_2 = new QLabel(SelectFileOperationDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 50, 31, 16));
        label_3 = new QLabel(SelectFileOperationDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 10, 31, 16));
        lineEditPCName = new QLineEdit(SelectFileOperationDialog);
        lineEditPCName->setObjectName("lineEditPCName");
        lineEditPCName->setGeometry(QRect(70, 10, 321, 21));
        lineEditDestination = new QLineEdit(SelectFileOperationDialog);
        lineEditDestination->setObjectName("lineEditDestination");
        lineEditDestination->setGeometry(QRect(10, 150, 331, 31));
        label_4 = new QLabel(SelectFileOperationDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 130, 121, 20));
        pushButtonSelectDestination = new QPushButton(SelectFileOperationDialog);
        pushButtonSelectDestination->setObjectName("pushButtonSelectDestination");
        pushButtonSelectDestination->setGeometry(QRect(340, 150, 31, 28));
        pushButtonMoveStart = new QPushButton(SelectFileOperationDialog);
        pushButtonMoveStart->setObjectName("pushButtonMoveStart");
        pushButtonMoveStart->setGeometry(QRect(10, 190, 161, 31));
        pushButtonClose = new QPushButton(SelectFileOperationDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(130, 237, 141, 41));

        retranslateUi(SelectFileOperationDialog);

        QMetaObject::connectSlotsByName(SelectFileOperationDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectFileOperationDialog)
    {
        SelectFileOperationDialog->setWindowTitle(QCoreApplication::translate("SelectFileOperationDialog", "Dialog", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("SelectFileOperationDialog", "Delete file", nullptr));
        label->setText(QCoreApplication::translate("SelectFileOperationDialog", "Path", nullptr));
        label_2->setText(QCoreApplication::translate("SelectFileOperationDialog", "File", nullptr));
        label_3->setText(QCoreApplication::translate("SelectFileOperationDialog", "PC", nullptr));
        label_4->setText(QCoreApplication::translate("SelectFileOperationDialog", "Move to folder", nullptr));
        pushButtonSelectDestination->setText(QCoreApplication::translate("SelectFileOperationDialog", "...", nullptr));
        pushButtonMoveStart->setText(QCoreApplication::translate("SelectFileOperationDialog", "Move start", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SelectFileOperationDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectFileOperationDialog: public Ui_SelectFileOperationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTFILEOPERATIONDIALOG_H
