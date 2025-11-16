/********************************************************************************
** Form generated from reading UI file 'AutoGenerateSettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOGENERATESETTINGDIALOG_H
#define UI_AUTOGENERATESETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoGenerateSettingDialog
{
public:
    QTableWidget *tableWidgetBladePos;
    QPushButton *PushButtonSaveBladePos;
    QPushButton *PushButtonLoadBladePos;
    QPushButton *PushButtonClose;

    void setupUi(QDialog *AutoGenerateSettingDialog)
    {
        if (AutoGenerateSettingDialog->objectName().isEmpty())
            AutoGenerateSettingDialog->setObjectName("AutoGenerateSettingDialog");
        AutoGenerateSettingDialog->resize(621, 504);
        tableWidgetBladePos = new QTableWidget(AutoGenerateSettingDialog);
        if (tableWidgetBladePos->columnCount() < 7)
            tableWidgetBladePos->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetBladePos->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidgetBladePos->setObjectName("tableWidgetBladePos");
        tableWidgetBladePos->setGeometry(QRect(10, 10, 601, 361));
        PushButtonSaveBladePos = new QPushButton(AutoGenerateSettingDialog);
        PushButtonSaveBladePos->setObjectName("PushButtonSaveBladePos");
        PushButtonSaveBladePos->setGeometry(QRect(20, 380, 191, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(16);
        font.setBold(true);
        PushButtonSaveBladePos->setFont(font);
        PushButtonSaveBladePos->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonSaveBladePos->setCheckable(true);
        PushButtonSaveBladePos->setAutoDefault(false);
        PushButtonSaveBladePos->setFlat(false);
        PushButtonLoadBladePos = new QPushButton(AutoGenerateSettingDialog);
        PushButtonLoadBladePos->setObjectName("PushButtonLoadBladePos");
        PushButtonLoadBladePos->setGeometry(QRect(400, 380, 191, 51));
        PushButtonLoadBladePos->setFont(font);
        PushButtonLoadBladePos->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonLoadBladePos->setCheckable(true);
        PushButtonLoadBladePos->setAutoDefault(false);
        PushButtonLoadBladePos->setFlat(false);
        PushButtonClose = new QPushButton(AutoGenerateSettingDialog);
        PushButtonClose->setObjectName("PushButtonClose");
        PushButtonClose->setGeometry(QRect(400, 440, 191, 51));
        PushButtonClose->setFont(font);
        PushButtonClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonClose->setCheckable(true);
        PushButtonClose->setAutoDefault(false);
        PushButtonClose->setFlat(false);

        retranslateUi(AutoGenerateSettingDialog);

        PushButtonSaveBladePos->setDefault(false);
        PushButtonLoadBladePos->setDefault(false);
        PushButtonClose->setDefault(false);


        QMetaObject::connectSlotsByName(AutoGenerateSettingDialog);
    } // setupUi

    void retranslateUi(QDialog *AutoGenerateSettingDialog)
    {
        AutoGenerateSettingDialog->setWindowTitle(QCoreApplication::translate("AutoGenerateSettingDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetBladePos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "\345\240\264\346\211\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBladePos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "\345\267\246\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetBladePos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "\344\270\212\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetBladePos->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "\345\217\263\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetBladePos->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "\344\270\213\343\201\213\343\202\211\343\201\256\350\267\235\351\233\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetBladePos->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "OK\347\257\204\345\233\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetBladePos->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "\350\250\210\346\270\254\347\267\232\343\201\256\351\225\267\343\201\225", nullptr));
        PushButtonSaveBladePos->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "\350\250\210\346\270\254\344\275\215\347\275\256\343\201\256\344\277\235\345\255\230", nullptr));
        PushButtonLoadBladePos->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "\350\250\210\346\270\254\344\275\215\347\275\256\343\201\256\350\252\255\350\276\274", nullptr));
        PushButtonClose->setText(QCoreApplication::translate("AutoGenerateSettingDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoGenerateSettingDialog: public Ui_AutoGenerateSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOGENERATESETTINGDIALOG_H
