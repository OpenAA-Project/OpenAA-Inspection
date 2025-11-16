/********************************************************************************
** Form generated from reading UI file 'ChooseNextDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSENEXTDIALOG_H
#define UI_CHOOSENEXTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChooseNextDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;

    void setupUi(QDialog *ChooseNextDialog)
    {
        if (ChooseNextDialog->objectName().isEmpty())
            ChooseNextDialog->setObjectName(QString::fromUtf8("ChooseNextDialog"));
        ChooseNextDialog->resize(400, 183);
        pushButtonOK = new QPushButton(ChooseNextDialog);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(40, 100, 191, 61));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pushButtonOK->setFont(font);
        pushButtonCancel = new QPushButton(ChooseNextDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(260, 100, 101, 61));
        pushButtonCancel->setFont(font);
        label = new QLabel(ChooseNextDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 361, 31));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(ChooseNextDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ChooseNextDialog);
    } // setupUi

    void retranslateUi(QDialog *ChooseNextDialog)
    {
        ChooseNextDialog->setWindowTitle(QCoreApplication::translate("ChooseNextDialog", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ChooseNextDialog", "Next inspection", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ChooseNextDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("ChooseNextDialog", "End of NG list.  Go to next inspection?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseNextDialog: public Ui_ChooseNextDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSENEXTDIALOG_H
