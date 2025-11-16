/********************************************************************************
** Form generated from reading UI file 'CreateManualFocusDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMANUALFOCUSDIALOG_H
#define UI_CREATEMANUALFOCUSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateManualFocusDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QLineEdit *lineEditItemName;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxFocusLow;

    void setupUi(QDialog *CreateManualFocusDialog)
    {
        if (CreateManualFocusDialog->objectName().isEmpty())
            CreateManualFocusDialog->setObjectName("CreateManualFocusDialog");
        CreateManualFocusDialog->resize(247, 164);
        pushButtonOK = new QPushButton(CreateManualFocusDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 120, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(CreateManualFocusDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 120, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(CreateManualFocusDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 101, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditItemName = new QLineEdit(CreateManualFocusDialog);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(10, 30, 231, 21));
        label_3 = new QLabel(CreateManualFocusDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 231, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxFocusLow = new QDoubleSpinBox(CreateManualFocusDialog);
        doubleSpinBoxFocusLow->setObjectName("doubleSpinBoxFocusLow");
        doubleSpinBoxFocusLow->setGeometry(QRect(10, 80, 101, 22));
        doubleSpinBoxFocusLow->setDecimals(3);

        retranslateUi(CreateManualFocusDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(CreateManualFocusDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateManualFocusDialog)
    {
        CreateManualFocusDialog->setWindowTitle(QCoreApplication::translate("CreateManualFocusDialog", "Create Manual Focus", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CreateManualFocusDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateManualFocusDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("CreateManualFocusDialog", "Focus Low", nullptr));
        label_3->setText(QCoreApplication::translate("CreateManualFocusDialog", "Item name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateManualFocusDialog: public Ui_CreateManualFocusDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMANUALFOCUSDIALOG_H
