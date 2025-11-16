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
    QSpinBox *spinBoxAreaNumber;
    QLabel *label_2;
    QLineEdit *lineEditAreaName;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxSysRegNumber;
    QLabel *label_3;
    QLabel *labelSeqStatus;

    void setupUi(QDialog *AddItemDialog)
    {
        if (AddItemDialog->objectName().isEmpty())
            AddItemDialog->setObjectName("AddItemDialog");
        AddItemDialog->resize(312, 187);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddItemDialog->sizePolicy().hasHeightForWidth());
        AddItemDialog->setSizePolicy(sizePolicy);
        label = new QLabel(AddItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxAreaNumber = new QSpinBox(AddItemDialog);
        spinBoxAreaNumber->setObjectName("spinBoxAreaNumber");
        spinBoxAreaNumber->setGeometry(QRect(110, 10, 81, 22));
        spinBoxAreaNumber->setMaximum(999999);
        label_2 = new QLabel(AddItemDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 91, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        lineEditAreaName = new QLineEdit(AddItemDialog);
        lineEditAreaName->setObjectName("lineEditAreaName");
        lineEditAreaName->setGeometry(QRect(110, 40, 191, 20));
        lineEditAreaName->setFrame(true);
        pushButtonOK = new QPushButton(AddItemDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(60, 130, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(AddItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(180, 130, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        spinBoxSysRegNumber = new QSpinBox(AddItemDialog);
        spinBoxSysRegNumber->setObjectName("spinBoxSysRegNumber");
        spinBoxSysRegNumber->setGeometry(QRect(230, 70, 61, 22));
        spinBoxSysRegNumber->setMaximum(1000);
        label_3 = new QLabel(AddItemDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 70, 221, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        labelSeqStatus = new QLabel(AddItemDialog);
        labelSeqStatus->setObjectName("labelSeqStatus");
        labelSeqStatus->setGeometry(QRect(230, 90, 61, 21));
        labelSeqStatus->setFrameShape(QFrame::Panel);
        labelSeqStatus->setFrameShadow(QFrame::Sunken);
        labelSeqStatus->setAlignment(Qt::AlignCenter);

        retranslateUi(AddItemDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(AddItemDialog);
    } // setupUi

    void retranslateUi(QDialog *AddItemDialog)
    {
        AddItemDialog->setWindowTitle(QCoreApplication::translate("AddItemDialog", "Add Item", nullptr));
        label->setText(QCoreApplication::translate("AddItemDialog", "\347\225\252\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("AddItemDialog", "\345\220\215\347\247\260", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddItemDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddItemDialog", "Cancel", nullptr));
        label_3->setText(QCoreApplication::translate("AddItemDialog", "\343\202\267\343\203\274\343\202\261\343\203\263\343\202\271\343\200\200\343\202\267\343\202\271\343\203\206\343\203\240\343\203\254\343\202\270\343\202\271\343\202\277\347\225\252\345\217\267", nullptr));
        labelSeqStatus->setText(QCoreApplication::translate("AddItemDialog", "\346\234\252\344\275\277\347\224\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddItemDialog: public Ui_AddItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEMDIALOG_H
