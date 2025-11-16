/********************************************************************************
** Form generated from reading UI file 'EditItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITITEMDIALOG_H
#define UI_EDITITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditItemDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditItemName;
    QLabel *label_2;
    QSpinBox *spinBoxPriority;
    QLabel *label_3;
    QCheckBox *checkBoxSaveTargetImage;
    QCheckBox *checkBoxSaveOnlyInNG;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonClose;
    QLabel *label_4;
    QComboBox *comboBoxBufferType;

    void setupUi(QDialog *EditItemDialog)
    {
        if (EditItemDialog->objectName().isEmpty())
            EditItemDialog->setObjectName("EditItemDialog");
        EditItemDialog->resize(400, 282);
        label = new QLabel(EditItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        lineEditItemName = new QLineEdit(EditItemDialog);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(90, 10, 291, 21));
        label_2 = new QLabel(EditItemDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxPriority = new QSpinBox(EditItemDialog);
        spinBoxPriority->setObjectName("spinBoxPriority");
        spinBoxPriority->setGeometry(QRect(90, 40, 101, 22));
        label_3 = new QLabel(EditItemDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 71, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        checkBoxSaveTargetImage = new QCheckBox(EditItemDialog);
        checkBoxSaveTargetImage->setObjectName("checkBoxSaveTargetImage");
        checkBoxSaveTargetImage->setGeometry(QRect(100, 70, 131, 19));
        checkBoxSaveOnlyInNG = new QCheckBox(EditItemDialog);
        checkBoxSaveOnlyInNG->setObjectName("checkBoxSaveOnlyInNG");
        checkBoxSaveOnlyInNG->setGeometry(QRect(100, 100, 131, 19));
        pushButtonAdd = new QPushButton(EditItemDialog);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(30, 190, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAdd->setIcon(icon);
        pushButtonEdit = new QPushButton(EditItemDialog);
        pushButtonEdit->setObjectName("pushButtonEdit");
        pushButtonEdit->setGeometry(QRect(150, 190, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEdit->setIcon(icon1);
        pushButtonDelete = new QPushButton(EditItemDialog);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(270, 190, 101, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon2);
        pushButtonClose = new QPushButton(EditItemDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(150, 230, 101, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon3);
        label_4 = new QLabel(EditItemDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 130, 81, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        comboBoxBufferType = new QComboBox(EditItemDialog);
        comboBoxBufferType->addItem(QString());
        comboBoxBufferType->addItem(QString());
        comboBoxBufferType->addItem(QString());
        comboBoxBufferType->addItem(QString());
        comboBoxBufferType->addItem(QString());
        comboBoxBufferType->setObjectName("comboBoxBufferType");
        comboBoxBufferType->setGeometry(QRect(100, 130, 171, 22));

        retranslateUi(EditItemDialog);

        pushButtonClose->setDefault(true);


        QMetaObject::connectSlotsByName(EditItemDialog);
    } // setupUi

    void retranslateUi(QDialog *EditItemDialog)
    {
        EditItemDialog->setWindowTitle(QCoreApplication::translate("EditItemDialog", "Edit Item", nullptr));
        label->setText(QCoreApplication::translate("EditItemDialog", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("EditItemDialog", "Priority", nullptr));
        label_3->setText(QCoreApplication::translate("EditItemDialog", "Save", nullptr));
        checkBoxSaveTargetImage->setText(QCoreApplication::translate("EditItemDialog", "Save image", nullptr));
        checkBoxSaveOnlyInNG->setText(QCoreApplication::translate("EditItemDialog", "Only NG", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("EditItemDialog", "Add", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("EditItemDialog", "Edit", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EditItemDialog", "Delete", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditItemDialog", "Close", nullptr));
        label_4->setText(QCoreApplication::translate("EditItemDialog", "Buffer type", nullptr));
        comboBoxBufferType->setItemText(0, QCoreApplication::translate("EditItemDialog", "Master buffer", nullptr));
        comboBoxBufferType->setItemText(1, QCoreApplication::translate("EditItemDialog", "Target buffer", nullptr));
        comboBoxBufferType->setItemText(2, QCoreApplication::translate("EditItemDialog", "Delayed buffer", nullptr));
        comboBoxBufferType->setItemText(3, QCoreApplication::translate("EditItemDialog", "RawTarget buffer", nullptr));
        comboBoxBufferType->setItemText(4, QCoreApplication::translate("EditItemDialog", "CamTarget buffer", nullptr));

    } // retranslateUi

};

namespace Ui {
    class EditItemDialog: public Ui_EditItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITITEMDIALOG_H
