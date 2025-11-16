/********************************************************************************
** Form generated from reading UI file 'OthersDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OTHERSDIALOG_H
#define UI_OTHERSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_OthersDialog
{
public:
    QPushButton *PushButtonCheck;
    QPushButton *PushButtonSetting;
    QPushButton *PushButtonLevel;
    QPushButton *PushButtonNew;
    QPushButton *PushButtonSwitchImage;
    QCheckBox *checkBoxStateTop;
    QCheckBox *checkBoxStateBottom;
    QTableWidget *tableWidgetMemory;
    QPushButton *PushButtonClose;
    QPushButton *PushButtonSetBeltVelocity;

    void setupUi(QDialog *OthersDialog)
    {
        if (OthersDialog->objectName().isEmpty())
            OthersDialog->setObjectName("OthersDialog");
        OthersDialog->resize(244, 730);
        PushButtonCheck = new QPushButton(OthersDialog);
        PushButtonCheck->setObjectName("PushButtonCheck");
        PushButtonCheck->setGeometry(QRect(10, 100, 221, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font.setPointSize(24);
        PushButtonCheck->setFont(font);
        PushButtonCheck->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonCheck->setCheckable(false);
        PushButtonCheck->setAutoDefault(false);
        PushButtonCheck->setFlat(false);
        PushButtonSetting = new QPushButton(OthersDialog);
        PushButtonSetting->setObjectName("PushButtonSetting");
        PushButtonSetting->setGeometry(QRect(10, 170, 221, 61));
        PushButtonSetting->setFont(font);
        PushButtonSetting->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonSetting->setCheckable(false);
        PushButtonSetting->setAutoDefault(false);
        PushButtonSetting->setFlat(false);
        PushButtonLevel = new QPushButton(OthersDialog);
        PushButtonLevel->setObjectName("PushButtonLevel");
        PushButtonLevel->setGeometry(QRect(10, 10, 221, 61));
        PushButtonLevel->setFont(font);
        PushButtonLevel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonLevel->setCheckable(false);
        PushButtonLevel->setAutoDefault(false);
        PushButtonLevel->setFlat(false);
        PushButtonNew = new QPushButton(OthersDialog);
        PushButtonNew->setObjectName("PushButtonNew");
        PushButtonNew->setGeometry(QRect(10, 250, 221, 61));
        PushButtonNew->setFont(font);
        PushButtonNew->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonNew->setCheckable(false);
        PushButtonNew->setAutoDefault(false);
        PushButtonNew->setFlat(false);
        PushButtonSwitchImage = new QPushButton(OthersDialog);
        PushButtonSwitchImage->setObjectName("PushButtonSwitchImage");
        PushButtonSwitchImage->setGeometry(QRect(10, 410, 221, 61));
        PushButtonSwitchImage->setFont(font);
        PushButtonSwitchImage->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonSwitchImage->setCheckable(false);
        PushButtonSwitchImage->setAutoDefault(false);
        PushButtonSwitchImage->setFlat(false);
        checkBoxStateTop = new QCheckBox(OthersDialog);
        checkBoxStateTop->setObjectName("checkBoxStateTop");
        checkBoxStateTop->setGeometry(QRect(30, 490, 108, 22));
        QFont font1;
        font1.setPointSize(12);
        checkBoxStateTop->setFont(font1);
        checkBoxStateBottom = new QCheckBox(OthersDialog);
        checkBoxStateBottom->setObjectName("checkBoxStateBottom");
        checkBoxStateBottom->setGeometry(QRect(30, 520, 108, 22));
        checkBoxStateBottom->setFont(font1);
        tableWidgetMemory = new QTableWidget(OthersDialog);
        if (tableWidgetMemory->columnCount() < 2)
            tableWidgetMemory->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetMemory->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetMemory->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidgetMemory->rowCount() < 1)
            tableWidgetMemory->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMemory->setVerticalHeaderItem(0, __qtablewidgetitem2);
        tableWidgetMemory->setObjectName("tableWidgetMemory");
        tableWidgetMemory->setGeometry(QRect(10, 560, 221, 71));
        tableWidgetMemory->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetMemory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        PushButtonClose = new QPushButton(OthersDialog);
        PushButtonClose->setObjectName("PushButtonClose");
        PushButtonClose->setGeometry(QRect(10, 650, 211, 61));
        PushButtonClose->setFont(font);
        PushButtonClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 10px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 220, 160, 255), stop:1 rgba(165, 140, 100, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 100, 100, 255), stop:1 rgba(141, 60, 60, 255));\n"
"}"));
        PushButtonClose->setCheckable(true);
        PushButtonClose->setAutoExclusive(true);
        PushButtonClose->setAutoDefault(false);
        PushButtonClose->setFlat(false);
        PushButtonSetBeltVelocity = new QPushButton(OthersDialog);
        PushButtonSetBeltVelocity->setObjectName("PushButtonSetBeltVelocity");
        PushButtonSetBeltVelocity->setGeometry(QRect(10, 320, 221, 61));
        PushButtonSetBeltVelocity->setFont(font);
        PushButtonSetBeltVelocity->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonSetBeltVelocity->setCheckable(false);
        PushButtonSetBeltVelocity->setAutoDefault(false);
        PushButtonSetBeltVelocity->setFlat(false);

        retranslateUi(OthersDialog);

        PushButtonCheck->setDefault(false);
        PushButtonSetting->setDefault(false);
        PushButtonLevel->setDefault(false);
        PushButtonNew->setDefault(false);
        PushButtonSwitchImage->setDefault(false);
        PushButtonClose->setDefault(false);
        PushButtonSetBeltVelocity->setDefault(false);


        QMetaObject::connectSlotsByName(OthersDialog);
    } // setupUi

    void retranslateUi(QDialog *OthersDialog)
    {
        OthersDialog->setWindowTitle(QCoreApplication::translate("OthersDialog", "\343\201\235\343\201\256\344\273\226\350\250\255\345\256\232", nullptr));
        PushButtonCheck->setText(QCoreApplication::translate("OthersDialog", "\343\203\201\343\202\247\343\203\203\343\202\257", nullptr));
        PushButtonSetting->setText(QCoreApplication::translate("OthersDialog", "\350\250\255\345\256\232", nullptr));
        PushButtonLevel->setText(QCoreApplication::translate("OthersDialog", "Level", nullptr));
        PushButtonNew->setText(QCoreApplication::translate("OthersDialog", "\346\226\260\350\246\217", nullptr));
        PushButtonSwitchImage->setText(QCoreApplication::translate("OthersDialog", "\347\224\273\345\203\217\345\205\245\346\233\277", nullptr));
        checkBoxStateTop->setText(QCoreApplication::translate("OthersDialog", "\345\211\215", nullptr));
        checkBoxStateBottom->setText(QCoreApplication::translate("OthersDialog", "\345\276\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetMemory->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("OthersDialog", "\345\211\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetMemory->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("OthersDialog", "\345\276\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMemory->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("OthersDialog", "\343\203\241\343\203\242\343\203\252\343\203\274\344\275\277\347\224\250", nullptr));
        PushButtonClose->setText(QCoreApplication::translate("OthersDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        PushButtonSetBeltVelocity->setText(QCoreApplication::translate("OthersDialog", "\343\203\231\343\203\253\343\203\210\351\200\237\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OthersDialog: public Ui_OthersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OTHERSDIALOG_H
