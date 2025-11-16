/********************************************************************************
** Form generated from reading UI file 'SettingFilmPositionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFILMPOSITIONDIALOG_H
#define UI_SETTINGFILMPOSITIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingFilmPositionDialog
{
public:
    QTableWidget *tableWidget;
    QPushButton *PushButtonOK;
    QPushButton *PushButtonCancel;

    void setupUi(QDialog *SettingFilmPositionDialog)
    {
        if (SettingFilmPositionDialog->objectName().isEmpty())
            SettingFilmPositionDialog->setObjectName("SettingFilmPositionDialog");
        SettingFilmPositionDialog->resize(443, 348);
        tableWidget = new QTableWidget(SettingFilmPositionDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 421, 271));
        PushButtonOK = new QPushButton(SettingFilmPositionDialog);
        PushButtonOK->setObjectName("PushButtonOK");
        PushButtonOK->setGeometry(QRect(60, 290, 141, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(16);
        font.setBold(true);
        PushButtonOK->setFont(font);
        PushButtonOK->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOK->setCheckable(false);
        PushButtonOK->setAutoDefault(false);
        PushButtonOK->setFlat(false);
        PushButtonCancel = new QPushButton(SettingFilmPositionDialog);
        PushButtonCancel->setObjectName("PushButtonCancel");
        PushButtonCancel->setGeometry(QRect(240, 290, 141, 51));
        PushButtonCancel->setFont(font);
        PushButtonCancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonCancel->setCheckable(false);
        PushButtonCancel->setAutoDefault(false);
        PushButtonCancel->setFlat(false);

        retranslateUi(SettingFilmPositionDialog);

        PushButtonOK->setDefault(true);
        PushButtonCancel->setDefault(false);


        QMetaObject::connectSlotsByName(SettingFilmPositionDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingFilmPositionDialog)
    {
        SettingFilmPositionDialog->setWindowTitle(QCoreApplication::translate("SettingFilmPositionDialog", "\343\203\225\343\202\243\343\203\253\343\203\240\344\275\215\347\275\256\350\250\255\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SettingFilmPositionDialog", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SettingFilmPositionDialog", "\343\203\235\343\202\244\343\203\263\343\203\210\357\274\221", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SettingFilmPositionDialog", "\343\203\235\343\202\244\343\203\263\343\203\210\357\274\222", nullptr));
        PushButtonOK->setText(QCoreApplication::translate("SettingFilmPositionDialog", "OK", nullptr));
        PushButtonCancel->setText(QCoreApplication::translate("SettingFilmPositionDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingFilmPositionDialog: public Ui_SettingFilmPositionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFILMPOSITIONDIALOG_H
