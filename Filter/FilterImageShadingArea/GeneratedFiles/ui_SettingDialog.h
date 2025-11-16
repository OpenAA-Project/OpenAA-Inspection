/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QListWidget *listWidgetFileList;
    QLabel *label;
    QPushButton *pushButtonAddFiles;
    QPushButton *pushButtonDelFiles;
    QPushButton *pushButtonCalculate;
    QPushButton *pushButtonClose;
    QLabel *labelMagR;
    QDoubleSpinBox *doubleSpinBoxMagR;
    QLabel *labelMagG;
    QDoubleSpinBox *doubleSpinBoxMagG;
    QLabel *labelMagB;
    QDoubleSpinBox *doubleSpinBoxMagB;
    QLabel *labelMagR_2;
    QSpinBox *spinBoxUsePhaseNumber;
    QLabel *labelMagR_3;
    QSpinBox *spinBoxUsePageNumber;
    QLabel *labelMagR_4;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName("SettingDialog");
        SettingDialog->resize(400, 496);
        listWidgetFileList = new QListWidget(SettingDialog);
        listWidgetFileList->setObjectName("listWidgetFileList");
        listWidgetFileList->setGeometry(QRect(10, 30, 256, 192));
        listWidgetFileList->setSelectionMode(QAbstractItemView::MultiSelection);
        listWidgetFileList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(SettingDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 251, 21));
        pushButtonAddFiles = new QPushButton(SettingDialog);
        pushButtonAddFiles->setObjectName("pushButtonAddFiles");
        pushButtonAddFiles->setGeometry(QRect(280, 70, 112, 34));
        pushButtonDelFiles = new QPushButton(SettingDialog);
        pushButtonDelFiles->setObjectName("pushButtonDelFiles");
        pushButtonDelFiles->setGeometry(QRect(280, 120, 112, 34));
        pushButtonCalculate = new QPushButton(SettingDialog);
        pushButtonCalculate->setObjectName("pushButtonCalculate");
        pushButtonCalculate->setGeometry(QRect(20, 380, 201, 34));
        pushButtonClose = new QPushButton(SettingDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(60, 440, 112, 34));
        labelMagR = new QLabel(SettingDialog);
        labelMagR->setObjectName("labelMagR");
        labelMagR->setGeometry(QRect(20, 247, 101, 21));
        doubleSpinBoxMagR = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxMagR->setObjectName("doubleSpinBoxMagR");
        doubleSpinBoxMagR->setGeometry(QRect(20, 270, 111, 24));
        doubleSpinBoxMagR->setDecimals(3);
        doubleSpinBoxMagR->setValue(1.000000000000000);
        labelMagG = new QLabel(SettingDialog);
        labelMagG->setObjectName("labelMagG");
        labelMagG->setGeometry(QRect(140, 247, 101, 21));
        doubleSpinBoxMagG = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxMagG->setObjectName("doubleSpinBoxMagG");
        doubleSpinBoxMagG->setGeometry(QRect(140, 270, 111, 24));
        doubleSpinBoxMagG->setDecimals(3);
        doubleSpinBoxMagG->setValue(1.000000000000000);
        labelMagB = new QLabel(SettingDialog);
        labelMagB->setObjectName("labelMagB");
        labelMagB->setGeometry(QRect(260, 247, 101, 21));
        doubleSpinBoxMagB = new QDoubleSpinBox(SettingDialog);
        doubleSpinBoxMagB->setObjectName("doubleSpinBoxMagB");
        doubleSpinBoxMagB->setGeometry(QRect(260, 270, 111, 24));
        doubleSpinBoxMagB->setDecimals(3);
        doubleSpinBoxMagB->setValue(1.000000000000000);
        labelMagR_2 = new QLabel(SettingDialog);
        labelMagR_2->setObjectName("labelMagR_2");
        labelMagR_2->setGeometry(QRect(30, 310, 341, 21));
        labelMagR_2->setFrameShape(QFrame::Panel);
        labelMagR_2->setFrameShadow(QFrame::Sunken);
        spinBoxUsePhaseNumber = new QSpinBox(SettingDialog);
        spinBoxUsePhaseNumber->setObjectName("spinBoxUsePhaseNumber");
        spinBoxUsePhaseNumber->setGeometry(QRect(110, 330, 71, 24));
        labelMagR_3 = new QLabel(SettingDialog);
        labelMagR_3->setObjectName("labelMagR_3");
        labelMagR_3->setGeometry(QRect(40, 330, 61, 21));
        labelMagR_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxUsePageNumber = new QSpinBox(SettingDialog);
        spinBoxUsePageNumber->setObjectName("spinBoxUsePageNumber");
        spinBoxUsePageNumber->setGeometry(QRect(270, 330, 71, 24));
        labelMagR_4 = new QLabel(SettingDialog);
        labelMagR_4->setObjectName("labelMagR_4");
        labelMagR_4->setGeometry(QRect(200, 330, 61, 21));
        labelMagR_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(SettingDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(230, 440, 112, 34));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QCoreApplication::translate("SettingDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingDialog", "File list", nullptr));
        pushButtonAddFiles->setText(QCoreApplication::translate("SettingDialog", "Add files", nullptr));
        pushButtonDelFiles->setText(QCoreApplication::translate("SettingDialog", "Delete files", nullptr));
        pushButtonCalculate->setText(QCoreApplication::translate("SettingDialog", "Calculate", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SettingDialog", "OK", nullptr));
        labelMagR->setText(QCoreApplication::translate("SettingDialog", "Magnificant R", nullptr));
        labelMagG->setText(QCoreApplication::translate("SettingDialog", "Magnificant G", nullptr));
        labelMagB->setText(QCoreApplication::translate("SettingDialog", "Magnificant B", nullptr));
        labelMagR_2->setText(QCoreApplication::translate("SettingDialog", "Usage  data in Pix file", nullptr));
        labelMagR_3->setText(QCoreApplication::translate("SettingDialog", "Phase", nullptr));
        labelMagR_4->setText(QCoreApplication::translate("SettingDialog", "Page", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
