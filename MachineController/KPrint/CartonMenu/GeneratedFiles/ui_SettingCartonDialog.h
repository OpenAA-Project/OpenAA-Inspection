/********************************************************************************
** Form generated from reading UI file 'SettingCartonDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGCARTONDIALOG_H
#define UI_SETTINGCARTONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingCartonDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *Mask;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonTrigger;
    QPushButton *pushButtonUsageLibrary;

    void setupUi(QDialog *SettingCartonDialog)
    {
        if (SettingCartonDialog->objectName().isEmpty())
            SettingCartonDialog->setObjectName("SettingCartonDialog");
        SettingCartonDialog->resize(738, 562);
        tabWidget = new QTabWidget(SettingCartonDialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 731, 511));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        tabWidget->setFont(font);
        Mask = new QWidget();
        Mask->setObjectName("Mask");
        tabWidget->addTab(Mask, QString());
        pushButtonOK = new QPushButton(SettingCartonDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(390, 520, 112, 34));
        pushButtonCancel = new QPushButton(SettingCartonDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(600, 520, 112, 34));
        pushButtonTrigger = new QPushButton(SettingCartonDialog);
        pushButtonTrigger->setObjectName("pushButtonTrigger");
        pushButtonTrigger->setGeometry(QRect(10, 520, 171, 34));
        pushButtonUsageLibrary = new QPushButton(SettingCartonDialog);
        pushButtonUsageLibrary->setObjectName("pushButtonUsageLibrary");
        pushButtonUsageLibrary->setGeometry(QRect(200, 520, 141, 34));

        retranslateUi(SettingCartonDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingCartonDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingCartonDialog)
    {
        SettingCartonDialog->setWindowTitle(QCoreApplication::translate("SettingCartonDialog", "\343\203\221\343\203\251\343\203\241\343\203\274\343\202\277\350\250\255\345\256\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Mask), QCoreApplication::translate("SettingCartonDialog", "\343\203\236\343\202\271\343\202\257", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingCartonDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingCartonDialog", "Cancel", nullptr));
        pushButtonTrigger->setText(QCoreApplication::translate("SettingCartonDialog", "\343\203\210\343\203\252\343\202\254\343\203\274\344\275\215\347\275\256\350\252\277\346\225\264", nullptr));
        pushButtonUsageLibrary->setText(QCoreApplication::translate("SettingCartonDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\211\262\343\202\212\345\275\223\343\201\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingCartonDialog: public Ui_SettingCartonDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGCARTONDIALOG_H
