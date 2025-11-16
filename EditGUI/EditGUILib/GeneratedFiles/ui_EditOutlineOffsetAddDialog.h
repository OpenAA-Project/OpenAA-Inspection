/********************************************************************************
** Form generated from reading UI file 'EditOutlineOffsetAddDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOUTLINEOFFSETADDDIALOG_H
#define UI_EDITOUTLINEOFFSETADDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditOutlineOffsetAddDialog
{
public:
    QSpinBox *spinBox;
    QLabel *label;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditOutlineOffsetAddDialog)
    {
        if (EditOutlineOffsetAddDialog->objectName().isEmpty())
            EditOutlineOffsetAddDialog->setObjectName("EditOutlineOffsetAddDialog");
        EditOutlineOffsetAddDialog->resize(271, 152);
        spinBox = new QSpinBox(EditOutlineOffsetAddDialog);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(50, 40, 131, 24));
        spinBox->setMinimum(-99999999);
        spinBox->setMaximum(99999999);
        label = new QLabel(EditOutlineOffsetAddDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 251, 18));
        pushButtonOK = new QPushButton(EditOutlineOffsetAddDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 90, 111, 34));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(EditOutlineOffsetAddDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 90, 111, 34));

        retranslateUi(EditOutlineOffsetAddDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditOutlineOffsetAddDialog);
    } // setupUi

    void retranslateUi(QDialog *EditOutlineOffsetAddDialog)
    {
        EditOutlineOffsetAddDialog->setWindowTitle(QCoreApplication::translate("EditOutlineOffsetAddDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("EditOutlineOffsetAddDialog", "Add offset after current page", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditOutlineOffsetAddDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditOutlineOffsetAddDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditOutlineOffsetAddDialog: public Ui_EditOutlineOffsetAddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOUTLINEOFFSETADDDIALOG_H
