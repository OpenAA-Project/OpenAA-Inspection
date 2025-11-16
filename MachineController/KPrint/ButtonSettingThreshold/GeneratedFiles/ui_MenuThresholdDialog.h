/********************************************************************************
** Form generated from reading UI file 'MenuThresholdDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUTHRESHOLDDIALOG_H
#define UI_MENUTHRESHOLDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuThresholdDialog
{
public:
    QPushButton *PushButtonClosed;
    QTableWidget *tableWidget;
    QFrame *frameThresholdLevel;
    QSlider *horizontalSlider;
    QPushButton *PushButtonSettingEasy;
    QLabel *label;
    QLabel *labelLevelNumber;
    QLabel *labelLevelName;
    QPushButton *PushButtonBlade;
    QPushButton *PushButtonCADLine;
    QPushButton *PushButtonWhole;

    void setupUi(QDialog *MenuThresholdDialog)
    {
        if (MenuThresholdDialog->objectName().isEmpty())
            MenuThresholdDialog->setObjectName("MenuThresholdDialog");
        MenuThresholdDialog->resize(712, 766);
        PushButtonClosed = new QPushButton(MenuThresholdDialog);
        PushButtonClosed->setObjectName("PushButtonClosed");
        PushButtonClosed->setGeometry(QRect(270, 690, 191, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font.setPointSize(24);
        PushButtonClosed->setFont(font);
        PushButtonClosed->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonClosed->setCheckable(false);
        PushButtonClosed->setChecked(false);
        PushButtonClosed->setAutoDefault(false);
        PushButtonClosed->setFlat(false);
        tableWidget = new QTableWidget(MenuThresholdDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 4)
            tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem6);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 210, 671, 391));
        QFont font1;
        font1.setPointSize(16);
        tableWidget->setFont(font1);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setAutoScroll(false);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->horizontalHeader()->setMinimumSectionSize(80);
        tableWidget->verticalHeader()->setMinimumSectionSize(80);
        tableWidget->verticalHeader()->setDefaultSectionSize(80);
        frameThresholdLevel = new QFrame(MenuThresholdDialog);
        frameThresholdLevel->setObjectName("frameThresholdLevel");
        frameThresholdLevel->setGeometry(QRect(10, 10, 631, 181));
        frameThresholdLevel->setFrameShape(QFrame::Panel);
        frameThresholdLevel->setFrameShadow(QFrame::Sunken);
        horizontalSlider = new QSlider(frameThresholdLevel);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(50, 50, 371, 61));
        horizontalSlider->setMaximum(4);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setValue(2);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        PushButtonSettingEasy = new QPushButton(frameThresholdLevel);
        PushButtonSettingEasy->setObjectName("PushButtonSettingEasy");
        PushButtonSettingEasy->setGeometry(QRect(440, 30, 171, 101));
        PushButtonSettingEasy->setFont(font);
        PushButtonSettingEasy->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonSettingEasy->setCheckable(false);
        PushButtonSettingEasy->setChecked(false);
        PushButtonSettingEasy->setAutoDefault(false);
        PushButtonSettingEasy->setFlat(false);
        label = new QLabel(frameThresholdLevel);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 591, 31));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);
        labelLevelNumber = new QLabel(frameThresholdLevel);
        labelLevelNumber->setObjectName("labelLevelNumber");
        labelLevelNumber->setGeometry(QRect(0, 60, 41, 31));
        labelLevelNumber->setFont(font2);
        labelLevelNumber->setAlignment(Qt::AlignCenter);
        labelLevelName = new QLabel(frameThresholdLevel);
        labelLevelName->setObjectName("labelLevelName");
        labelLevelName->setGeometry(QRect(50, 140, 371, 31));
        QFont font3;
        font3.setPointSize(12);
        labelLevelName->setFont(font3);
        labelLevelName->setFrameShape(QFrame::Panel);
        labelLevelName->setFrameShadow(QFrame::Sunken);
        labelLevelName->setAlignment(Qt::AlignCenter);
        PushButtonBlade = new QPushButton(MenuThresholdDialog);
        PushButtonBlade->setObjectName("PushButtonBlade");
        PushButtonBlade->setGeometry(QRect(500, 610, 181, 61));
        PushButtonBlade->setFont(font);
        PushButtonBlade->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonBlade->setCheckable(false);
        PushButtonBlade->setChecked(false);
        PushButtonBlade->setAutoDefault(false);
        PushButtonBlade->setFlat(false);
        PushButtonCADLine = new QPushButton(MenuThresholdDialog);
        PushButtonCADLine->setObjectName("PushButtonCADLine");
        PushButtonCADLine->setGeometry(QRect(240, 610, 251, 61));
        PushButtonCADLine->setFont(font);
        PushButtonCADLine->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonCADLine->setCheckable(false);
        PushButtonCADLine->setChecked(false);
        PushButtonCADLine->setAutoDefault(false);
        PushButtonCADLine->setFlat(false);
        PushButtonWhole = new QPushButton(MenuThresholdDialog);
        PushButtonWhole->setObjectName("PushButtonWhole");
        PushButtonWhole->setGeometry(QRect(10, 610, 221, 61));
        PushButtonWhole->setFont(font);
        PushButtonWhole->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonWhole->setCheckable(false);
        PushButtonWhole->setChecked(false);
        PushButtonWhole->setAutoDefault(false);
        PushButtonWhole->setFlat(false);

        retranslateUi(MenuThresholdDialog);

        PushButtonClosed->setDefault(false);
        PushButtonSettingEasy->setDefault(false);
        PushButtonBlade->setDefault(false);
        PushButtonCADLine->setDefault(false);
        PushButtonWhole->setDefault(false);


        QMetaObject::connectSlotsByName(MenuThresholdDialog);
    } // setupUi

    void retranslateUi(QDialog *MenuThresholdDialog)
    {
        MenuThresholdDialog->setWindowTitle(QCoreApplication::translate("MenuThresholdDialog", "Setting", nullptr));
        PushButtonClosed->setText(QCoreApplication::translate("MenuThresholdDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MenuThresholdDialog", "\345\215\230\350\211\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MenuThresholdDialog", "\343\202\260\343\203\251\343\203\207\343\203\274\343\202\267\343\203\247\343\203\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MenuThresholdDialog", "\346\226\207\345\255\227\351\203\250\345\210\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MenuThresholdDialog", "\346\277\203\346\267\241\346\244\234\346\237\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MenuThresholdDialog", "\350\265\244\350\211\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MenuThresholdDialog", "\343\201\253\343\201\230\343\201\277", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MenuThresholdDialog", "\345\244\232\347\202\271", nullptr));
        PushButtonSettingEasy->setText(QCoreApplication::translate("MenuThresholdDialog", "\350\250\255\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("MenuThresholdDialog", "\345\205\250\344\275\223\343\201\270\343\201\256\347\260\241\346\230\223\350\250\255\345\256\232", nullptr));
        labelLevelNumber->setText(QCoreApplication::translate("MenuThresholdDialog", "3", nullptr));
        labelLevelName->setText(QCoreApplication::translate("MenuThresholdDialog", "Lavel name", nullptr));
        PushButtonBlade->setText(QCoreApplication::translate("MenuThresholdDialog", "\350\250\210\346\270\254", nullptr));
        PushButtonCADLine->setText(QCoreApplication::translate("MenuThresholdDialog", "CAD\347\267\232\344\270\212", nullptr));
        PushButtonWhole->setText(QCoreApplication::translate("MenuThresholdDialog", "\345\205\250\344\275\223\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuThresholdDialog: public Ui_MenuThresholdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUTHRESHOLDDIALOG_H
