/********************************************************************************
** Form generated from reading UI file 'ShowReqLotDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWREQLOTDIALOG_H
#define UI_SHOWREQLOTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShowReqLotDialog
{
public:
    QLabel *label;
    QPushButton *PushButtonOK;

    void setupUi(QDialog *ShowReqLotDialog)
    {
        if (ShowReqLotDialog->objectName().isEmpty())
            ShowReqLotDialog->setObjectName("ShowReqLotDialog");
        ShowReqLotDialog->resize(1017, 212);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(255, 0, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        ShowReqLotDialog->setPalette(palette);
        ShowReqLotDialog->setAutoFillBackground(true);
        label = new QLabel(ShowReqLotDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 50, 1001, 51));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        PushButtonOK = new QPushButton(ShowReqLotDialog);
        PushButtonOK->setObjectName("PushButtonOK");
        PushButtonOK->setGeometry(QRect(410, 130, 211, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font1.setPointSize(24);
        PushButtonOK->setFont(font1);
        PushButtonOK->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonOK->setCheckable(false);
        PushButtonOK->setAutoExclusive(false);
        PushButtonOK->setAutoDefault(false);
        PushButtonOK->setFlat(false);

        retranslateUi(ShowReqLotDialog);

        PushButtonOK->setDefault(false);


        QMetaObject::connectSlotsByName(ShowReqLotDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowReqLotDialog)
    {
        ShowReqLotDialog->setWindowTitle(QCoreApplication::translate("ShowReqLotDialog", "\346\263\250\346\204\217", nullptr));
        label->setText(QCoreApplication::translate("ShowReqLotDialog", "\343\203\255\343\203\203\343\203\210\343\201\256\343\202\263\343\203\274\343\203\211No\343\200\201\343\203\255\343\203\203\343\203\210No\343\200\201\345\211\257\347\225\252\343\202\222\345\205\245\345\212\233\343\201\227\343\201\246\347\231\273\351\214\262\343\203\234\343\202\277\343\203\263\343\202\222\346\212\274\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204", nullptr));
        PushButtonOK->setText(QCoreApplication::translate("ShowReqLotDialog", "\344\272\206\350\247\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowReqLotDialog: public Ui_ShowReqLotDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWREQLOTDIALOG_H
