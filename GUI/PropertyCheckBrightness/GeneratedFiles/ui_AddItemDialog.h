/********************************************************************************
** Form generated from reading UI file 'AddItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITEMDIALOG_H
#define UI_ADDITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddItemDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxThreshL;
    QSpinBox *spinBoxThreshH;
    QComboBox *comboBoxCondition;
    QSpinBox *spinBoxRegNumber;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxRepeatableCount;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label_5;
    QLineEdit *lineEditItemName;

    void setupUi(QDialog *AddItemDialog)
    {
        if (AddItemDialog->objectName().isEmpty())
            AddItemDialog->setObjectName("AddItemDialog");
        AddItemDialog->resize(300, 228);
        label = new QLabel(AddItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 60, 46, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(AddItemDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 60, 46, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxThreshL = new QSpinBox(AddItemDialog);
        spinBoxThreshL->setObjectName("spinBoxThreshL");
        spinBoxThreshL->setGeometry(QRect(20, 80, 46, 22));
        spinBoxThreshL->setMaximum(255);
        spinBoxThreshL->setValue(255);
        spinBoxThreshH = new QSpinBox(AddItemDialog);
        spinBoxThreshH->setObjectName("spinBoxThreshH");
        spinBoxThreshH->setGeometry(QRect(70, 80, 46, 22));
        spinBoxThreshH->setMaximum(255);
        spinBoxThreshH->setValue(255);
        comboBoxCondition = new QComboBox(AddItemDialog);
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->setObjectName("comboBoxCondition");
        comboBoxCondition->setGeometry(QRect(130, 70, 161, 22));
        spinBoxRegNumber = new QSpinBox(AddItemDialog);
        spinBoxRegNumber->setObjectName("spinBoxRegNumber");
        spinBoxRegNumber->setGeometry(QRect(20, 130, 46, 22));
        spinBoxRegNumber->setMinimum(400);
        spinBoxRegNumber->setMaximum(499);
        spinBoxRegNumber->setValue(400);
        label_3 = new QLabel(AddItemDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 110, 46, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(AddItemDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 110, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        spinBoxRepeatableCount = new QSpinBox(AddItemDialog);
        spinBoxRepeatableCount->setObjectName("spinBoxRepeatableCount");
        spinBoxRepeatableCount->setGeometry(QRect(70, 130, 81, 22));
        spinBoxRepeatableCount->setMinimum(0);
        spinBoxRepeatableCount->setMaximum(1000000);
        spinBoxRepeatableCount->setValue(1);
        pushButtonOK = new QPushButton(AddItemDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 170, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(AddItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(180, 170, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label_5 = new QLabel(AddItemDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 10, 271, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        lineEditItemName = new QLineEdit(AddItemDialog);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(20, 30, 271, 20));

        retranslateUi(AddItemDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(AddItemDialog);
    } // setupUi

    void retranslateUi(QDialog *AddItemDialog)
    {
        AddItemDialog->setWindowTitle(QCoreApplication::translate("AddItemDialog", "Add Item", nullptr));
        label->setText(QCoreApplication::translate("AddItemDialog", "L", nullptr));
        label_2->setText(QCoreApplication::translate("AddItemDialog", "H", nullptr));
        comboBoxCondition->setItemText(0, QCoreApplication::translate("AddItemDialog", "Average must be inside", nullptr));
        comboBoxCondition->setItemText(1, QCoreApplication::translate("AddItemDialog", "All must be inside", nullptr));
        comboBoxCondition->setItemText(2, QCoreApplication::translate("AddItemDialog", "One must be inside at least", nullptr));
        comboBoxCondition->setItemText(3, QCoreApplication::translate("AddItemDialog", "Average must be outside", nullptr));
        comboBoxCondition->setItemText(4, QCoreApplication::translate("AddItemDialog", "All must be outside", nullptr));
        comboBoxCondition->setItemText(5, QCoreApplication::translate("AddItemDialog", "One must be outside at least", nullptr));

        label_3->setText(QCoreApplication::translate("AddItemDialog", "Reg No", nullptr));
        label_4->setText(QCoreApplication::translate("AddItemDialog", "Repeatable NG", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddItemDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddItemDialog", "Cancel", nullptr));
        label_5->setText(QCoreApplication::translate("AddItemDialog", "Item name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddItemDialog: public Ui_AddItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEMDIALOG_H
