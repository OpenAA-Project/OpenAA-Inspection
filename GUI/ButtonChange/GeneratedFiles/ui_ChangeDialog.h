/********************************************************************************
** Form generated from reading UI file 'ChangeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEDIALOG_H
#define UI_CHANGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ChangeDialog
{
public:
    QLabel *label;
    QSpinBox *spinBoxPhaseCount;
    QLabel *label_2;
    QSpinBox *spinBoxPageCount;
    QLabel *label_3;
    QSpinBox *spinBoxLayerCount;
    QLabel *label_4;
    QSpinBox *spinBoxLineCount;
    QLabel *label_5;
    QPushButton *pushButtonExecute;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *ChangeDialog)
    {
        if (ChangeDialog->objectName().isEmpty())
            ChangeDialog->setObjectName("ChangeDialog");
        ChangeDialog->resize(219, 202);
        label = new QLabel(ChangeDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 81, 21));
        spinBoxPhaseCount = new QSpinBox(ChangeDialog);
        spinBoxPhaseCount->setObjectName("spinBoxPhaseCount");
        spinBoxPhaseCount->setGeometry(QRect(120, 10, 71, 22));
        label_2 = new QLabel(ChangeDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 40, 81, 21));
        spinBoxPageCount = new QSpinBox(ChangeDialog);
        spinBoxPageCount->setObjectName("spinBoxPageCount");
        spinBoxPageCount->setGeometry(QRect(120, 40, 71, 22));
        spinBoxPageCount->setMaximum(99999999);
        label_3 = new QLabel(ChangeDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 70, 81, 21));
        spinBoxLayerCount = new QSpinBox(ChangeDialog);
        spinBoxLayerCount->setObjectName("spinBoxLayerCount");
        spinBoxLayerCount->setGeometry(QRect(120, 70, 71, 22));
        spinBoxLayerCount->setMaximum(99999999);
        label_4 = new QLabel(ChangeDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 100, 81, 21));
        spinBoxLineCount = new QSpinBox(ChangeDialog);
        spinBoxLineCount->setObjectName("spinBoxLineCount");
        spinBoxLineCount->setGeometry(QRect(120, 100, 71, 22));
        spinBoxLineCount->setMaximum(200000000);
        label_5 = new QLabel(ChangeDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 130, 201, 21));
        pushButtonExecute = new QPushButton(ChangeDialog);
        pushButtonExecute->setObjectName("pushButtonExecute");
        pushButtonExecute->setGeometry(QRect(20, 160, 75, 31));
        pushButtonCancel = new QPushButton(ChangeDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 160, 75, 31));

        retranslateUi(ChangeDialog);

        pushButtonExecute->setDefault(true);


        QMetaObject::connectSlotsByName(ChangeDialog);
    } // setupUi

    void retranslateUi(QDialog *ChangeDialog)
    {
        ChangeDialog->setWindowTitle(QCoreApplication::translate("ChangeDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ChangeDialog", "Phase count", nullptr));
        label_2->setText(QCoreApplication::translate("ChangeDialog", "Page count", nullptr));
        label_3->setText(QCoreApplication::translate("ChangeDialog", "Layer count", nullptr));
        label_4->setText(QCoreApplication::translate("ChangeDialog", "Line count", nullptr));
        label_5->setText(QCoreApplication::translate("ChangeDialog", "After execution, this can not roll back", nullptr));
        pushButtonExecute->setText(QCoreApplication::translate("ChangeDialog", "Execute", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ChangeDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeDialog: public Ui_ChangeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEDIALOG_H
