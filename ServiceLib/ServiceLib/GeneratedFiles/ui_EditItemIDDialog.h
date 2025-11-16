/********************************************************************************
** Form generated from reading UI file 'EditItemIDDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITITEMIDDIALOG_H
#define UI_EDITITEMIDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditItemIDDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxOldItemID;
    QSpinBox *spinBoxNewItemID;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonCancel;
    QLabel *label_3;

    void setupUi(QDialog *EditItemIDDialog)
    {
        if (EditItemIDDialog->objectName().isEmpty())
            EditItemIDDialog->setObjectName("EditItemIDDialog");
        EditItemIDDialog->resize(222, 135);
        label = new QLabel(EditItemIDDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 61, 21));
        label_2 = new QLabel(EditItemIDDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 10, 61, 21));
        spinBoxOldItemID = new QSpinBox(EditItemIDDialog);
        spinBoxOldItemID->setObjectName("spinBoxOldItemID");
        spinBoxOldItemID->setGeometry(QRect(10, 30, 81, 31));
        spinBoxOldItemID->setReadOnly(true);
        spinBoxOldItemID->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxOldItemID->setMaximum(99999999);
        spinBoxNewItemID = new QSpinBox(EditItemIDDialog);
        spinBoxNewItemID->setObjectName("spinBoxNewItemID");
        spinBoxNewItemID->setGeometry(QRect(130, 30, 81, 31));
        spinBoxNewItemID->setMaximum(99999999);
        pushButtonUpdate = new QPushButton(EditItemIDDialog);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(10, 80, 91, 41));
        pushButtonCancel = new QPushButton(EditItemIDDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(119, 80, 91, 41));
        label_3 = new QLabel(EditItemIDDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(100, 30, 16, 31));

        retranslateUi(EditItemIDDialog);

        pushButtonUpdate->setDefault(true);


        QMetaObject::connectSlotsByName(EditItemIDDialog);
    } // setupUi

    void retranslateUi(QDialog *EditItemIDDialog)
    {
        EditItemIDDialog->setWindowTitle(QCoreApplication::translate("EditItemIDDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("EditItemIDDialog", "\347\217\276\345\234\250\343\201\256ID", nullptr));
        label_2->setText(QCoreApplication::translate("EditItemIDDialog", "\345\244\211\346\233\264\345\276\214\343\201\256ID", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("EditItemIDDialog", "\345\244\211\346\233\264", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditItemIDDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label_3->setText(QCoreApplication::translate("EditItemIDDialog", "=>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditItemIDDialog: public Ui_EditItemIDDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITITEMIDDIALOG_H
