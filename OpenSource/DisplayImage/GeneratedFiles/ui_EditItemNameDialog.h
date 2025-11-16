/********************************************************************************
** Form generated from reading UI file 'EditItemNameDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITITEMNAMEDIALOG_H
#define UI_EDITITEMNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditItemNameDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditItemName;
    QPushButton *pushButtonChange;
    QPushButton *pushButtonClose;
    QLabel *label_2;

    void setupUi(QDialog *EditItemNameDialog)
    {
        if (EditItemNameDialog->objectName().isEmpty())
            EditItemNameDialog->setObjectName("EditItemNameDialog");
        EditItemNameDialog->resize(400, 145);
        label = new QLabel(EditItemNameDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 40, 351, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditItemName = new QLineEdit(EditItemNameDialog);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(20, 60, 351, 21));
        pushButtonChange = new QPushButton(EditItemNameDialog);
        pushButtonChange->setObjectName("pushButtonChange");
        pushButtonChange->setGeometry(QRect(20, 100, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Change.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonChange->setIcon(icon);
        pushButtonClose = new QPushButton(EditItemNameDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(262, 100, 111, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        label_2 = new QLabel(EditItemNameDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 10, 351, 16));

        retranslateUi(EditItemNameDialog);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(EditItemNameDialog);
    } // setupUi

    void retranslateUi(QDialog *EditItemNameDialog)
    {
        EditItemNameDialog->setWindowTitle(QCoreApplication::translate("EditItemNameDialog", "Edit item name", nullptr));
        label->setText(QCoreApplication::translate("EditItemNameDialog", "Item name", nullptr));
        pushButtonChange->setText(QCoreApplication::translate("EditItemNameDialog", "Change", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditItemNameDialog", "Close", nullptr));
        label_2->setText(QCoreApplication::translate("EditItemNameDialog", "Set item name in all selected items", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditItemNameDialog: public Ui_EditItemNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITITEMNAMEDIALOG_H
