/********************************************************************************
** Form generated from reading UI file 'LoadMasterDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADMASTERDIALOG_H
#define UI_LOADMASTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_LoadMasterDialog
{
public:
    QTableView *tableView;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonCancel;
    QFrame *frameView;
    QLabel *labelTitleMasterNumber;
    QLineEdit *lineEditSearchByNumber;
    QPushButton *pushButtonInputMasterNumber;
    QLabel *labelTitleMasterName;
    QPushButton *pushButtonInputMasterName;
    QLineEdit *lineEditSearchByName;
    QLineEdit *lineEditSearchByRemark;
    QLabel *labelTitleRemark;
    QPushButton *pushButtonInputRemark;
    QDoubleSpinBox *doubleSpinBoxSizeX;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxSizeY;

    void setupUi(QDialog *LoadMasterDialog)
    {
        if (LoadMasterDialog->objectName().isEmpty())
            LoadMasterDialog->setObjectName("LoadMasterDialog");
        LoadMasterDialog->resize(1138, 781);
        tableView = new QTableView(LoadMasterDialog);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(10, 270, 1081, 361));
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonLoad = new QPushButton(LoadMasterDialog);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(170, 40, 161, 61));
        QFont font;
        font.setPointSize(12);
        pushButtonLoad->setFont(font);
        pushButtonLoad->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonCancel = new QPushButton(LoadMasterDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(340, 40, 141, 61));
        pushButtonCancel->setFont(font);
        pushButtonCancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        frameView = new QFrame(LoadMasterDialog);
        frameView->setObjectName("frameView");
        frameView->setGeometry(QRect(570, 10, 512, 256));
        frameView->setFrameShape(QFrame::StyledPanel);
        frameView->setFrameShadow(QFrame::Raised);
        labelTitleMasterNumber = new QLabel(LoadMasterDialog);
        labelTitleMasterNumber->setObjectName("labelTitleMasterNumber");
        labelTitleMasterNumber->setGeometry(QRect(20, 110, 151, 41));
        labelTitleMasterNumber->setFrameShape(QFrame::Panel);
        labelTitleMasterNumber->setFrameShadow(QFrame::Sunken);
        labelTitleMasterNumber->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditSearchByNumber = new QLineEdit(LoadMasterDialog);
        lineEditSearchByNumber->setObjectName("lineEditSearchByNumber");
        lineEditSearchByNumber->setGeometry(QRect(180, 110, 301, 41));
        pushButtonInputMasterNumber = new QPushButton(LoadMasterDialog);
        pushButtonInputMasterNumber->setObjectName("pushButtonInputMasterNumber");
        pushButtonInputMasterNumber->setGeometry(QRect(490, 110, 61, 41));
        labelTitleMasterName = new QLabel(LoadMasterDialog);
        labelTitleMasterName->setObjectName("labelTitleMasterName");
        labelTitleMasterName->setGeometry(QRect(20, 160, 151, 41));
        labelTitleMasterName->setFrameShape(QFrame::Panel);
        labelTitleMasterName->setFrameShadow(QFrame::Sunken);
        labelTitleMasterName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonInputMasterName = new QPushButton(LoadMasterDialog);
        pushButtonInputMasterName->setObjectName("pushButtonInputMasterName");
        pushButtonInputMasterName->setGeometry(QRect(490, 160, 61, 41));
        lineEditSearchByName = new QLineEdit(LoadMasterDialog);
        lineEditSearchByName->setObjectName("lineEditSearchByName");
        lineEditSearchByName->setGeometry(QRect(180, 160, 301, 41));
        lineEditSearchByRemark = new QLineEdit(LoadMasterDialog);
        lineEditSearchByRemark->setObjectName("lineEditSearchByRemark");
        lineEditSearchByRemark->setGeometry(QRect(180, 210, 301, 41));
        labelTitleRemark = new QLabel(LoadMasterDialog);
        labelTitleRemark->setObjectName("labelTitleRemark");
        labelTitleRemark->setGeometry(QRect(20, 210, 151, 41));
        labelTitleRemark->setFrameShape(QFrame::Panel);
        labelTitleRemark->setFrameShadow(QFrame::Sunken);
        labelTitleRemark->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonInputRemark = new QPushButton(LoadMasterDialog);
        pushButtonInputRemark->setObjectName("pushButtonInputRemark");
        pushButtonInputRemark->setGeometry(QRect(490, 210, 61, 41));
        doubleSpinBoxSizeX = new QDoubleSpinBox(LoadMasterDialog);
        doubleSpinBoxSizeX->setObjectName("doubleSpinBoxSizeX");
        doubleSpinBoxSizeX->setGeometry(QRect(900, 680, 121, 41));
        QPalette palette;
        QBrush brush(QColor(85, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxSizeX->setPalette(palette);
        QFont font1;
        font1.setPointSize(16);
        doubleSpinBoxSizeX->setFont(font1);
        doubleSpinBoxSizeX->setReadOnly(true);
        doubleSpinBoxSizeX->setDecimals(1);
        doubleSpinBoxSizeX->setMaximum(50000.000000000000000);
        doubleSpinBoxSizeX->setValue(100.000000000000000);
        label_6 = new QLabel(LoadMasterDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(570, 640, 521, 31));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        label_6->setFont(font2);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(LoadMasterDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(570, 730, 311, 41));
        label_5->setFont(font2);
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(LoadMasterDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(570, 680, 321, 41));
        label_4->setFont(font2);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        doubleSpinBoxSizeY = new QDoubleSpinBox(LoadMasterDialog);
        doubleSpinBoxSizeY->setObjectName("doubleSpinBoxSizeY");
        doubleSpinBoxSizeY->setGeometry(QRect(900, 730, 121, 41));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxSizeY->setPalette(palette1);
        doubleSpinBoxSizeY->setFont(font1);
        doubleSpinBoxSizeY->setReadOnly(true);
        doubleSpinBoxSizeY->setDecimals(1);
        doubleSpinBoxSizeY->setMaximum(200000.000000000000000);
        doubleSpinBoxSizeY->setValue(100.000000000000000);

        retranslateUi(LoadMasterDialog);

        QMetaObject::connectSlotsByName(LoadMasterDialog);
    } // setupUi

    void retranslateUi(QDialog *LoadMasterDialog)
    {
        LoadMasterDialog->setWindowTitle(QCoreApplication::translate("LoadMasterDialog", "\343\203\236\343\202\271\343\202\277\343\203\274\350\252\255\350\276\274", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("LoadMasterDialog", "\350\252\255\343\201\277\350\276\274\343\201\277", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("LoadMasterDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        labelTitleMasterNumber->setText(QCoreApplication::translate("LoadMasterDialog", "Number\346\244\234\347\264\242", nullptr));
        pushButtonInputMasterNumber->setText(QCoreApplication::translate("LoadMasterDialog", "...", nullptr));
        labelTitleMasterName->setText(QCoreApplication::translate("LoadMasterDialog", "Name\346\244\234\347\264\242", nullptr));
        pushButtonInputMasterName->setText(QCoreApplication::translate("LoadMasterDialog", "...", nullptr));
        labelTitleRemark->setText(QCoreApplication::translate("LoadMasterDialog", "Remark\346\244\234\347\264\242", nullptr));
        pushButtonInputRemark->setText(QCoreApplication::translate("LoadMasterDialog", "...", nullptr));
        label_6->setText(QCoreApplication::translate("LoadMasterDialog", "\343\203\257\343\203\274\343\202\257\343\202\265\343\202\244\343\202\272", nullptr));
        label_5->setText(QCoreApplication::translate("LoadMasterDialog", "\347\270\246\357\274\210\346\265\201\343\202\214\346\226\271\345\220\221\357\274\211mm", nullptr));
        label_4->setText(QCoreApplication::translate("LoadMasterDialog", "\346\250\252\345\271\205(\345\271\205\346\226\271\345\220\221\357\274\211 mm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadMasterDialog: public Ui_LoadMasterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADMASTERDIALOG_H
