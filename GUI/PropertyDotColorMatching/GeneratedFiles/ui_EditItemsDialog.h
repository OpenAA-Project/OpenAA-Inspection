/********************************************************************************
** Form generated from reading UI file 'EditItemsDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITITEMSDIALOG_H
#define UI_EDITITEMSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditItemsDialog
{
public:
    QPushButton *pushButtonSubtractLibID;
    QPushButton *pushButtonMasterNo;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label_99;
    QSpinBox *EditExpandToSubBlock;

    void setupUi(QDialog *EditItemsDialog)
    {
        if (EditItemsDialog->objectName().isEmpty())
            EditItemsDialog->setObjectName("EditItemsDialog");
        EditItemsDialog->resize(310, 180);
        pushButtonSubtractLibID = new QPushButton(EditItemsDialog);
        pushButtonSubtractLibID->setObjectName("pushButtonSubtractLibID");
        pushButtonSubtractLibID->setGeometry(QRect(170, 10, 131, 31));
        pushButtonMasterNo = new QPushButton(EditItemsDialog);
        pushButtonMasterNo->setObjectName("pushButtonMasterNo");
        pushButtonMasterNo->setGeometry(QRect(10, 10, 131, 31));
        pushButtonOK = new QPushButton(EditItemsDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 120, 101, 41));
        pushButtonCancel = new QPushButton(EditItemsDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(170, 120, 101, 41));
        label_99 = new QLabel(EditItemsDialog);
        label_99->setObjectName("label_99");
        label_99->setGeometry(QRect(170, 50, 111, 31));
        label_99->setFrameShape(QFrame::Panel);
        label_99->setFrameShadow(QFrame::Sunken);
        label_99->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditExpandToSubBlock = new QSpinBox(EditItemsDialog);
        EditExpandToSubBlock->setObjectName("EditExpandToSubBlock");
        EditExpandToSubBlock->setGeometry(QRect(170, 80, 111, 31));
        EditExpandToSubBlock->setMaximum(99999999);

        retranslateUi(EditItemsDialog);

        QMetaObject::connectSlotsByName(EditItemsDialog);
    } // setupUi

    void retranslateUi(QDialog *EditItemsDialog)
    {
        EditItemsDialog->setWindowTitle(QCoreApplication::translate("EditItemsDialog", "Edit items", nullptr));
        pushButtonSubtractLibID->setText(QCoreApplication::translate("EditItemsDialog", "\351\231\244\345\216\273\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252", nullptr));
        pushButtonMasterNo->setText(QCoreApplication::translate("EditItemsDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\347\225\252\345\217\267", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditItemsDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditItemsDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label_99->setText(QCoreApplication::translate("EditItemsDialog", "\351\231\244\345\216\273\343\201\256\350\277\221\345\202\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditItemsDialog: public Ui_EditItemsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITITEMSDIALOG_H
