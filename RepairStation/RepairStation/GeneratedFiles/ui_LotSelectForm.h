/********************************************************************************
** Form generated from reading UI file 'LotSelectForm.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOTSELECTFORM_H
#define UI_LOTSELECTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include "passwordpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_LotSelectClass
{
public:
    QTableWidget *twLotList;
    QLineEdit *lineEdit;
    PasswordPushButton *pbSelect;
    QFrame *line;
    PasswordPushButton *pbCancel;
    PasswordPushButton *pbAllSelect;
    QLineEdit *leSearchLotName;
    QLabel *label;
    PasswordPushButton *pbSearch;

    void setupUi(QDialog *LotSelectClass)
    {
        if (LotSelectClass->objectName().isEmpty())
            LotSelectClass->setObjectName(QString::fromUtf8("LotSelectClass"));
        LotSelectClass->resize(582, 459);
        twLotList = new QTableWidget(LotSelectClass);
        twLotList->setObjectName(QString::fromUtf8("twLotList"));
        twLotList->setGeometry(QRect(10, 80, 561, 271));
        lineEdit = new QLineEdit(LotSelectClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 20, 561, 21));
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setReadOnly(true);
        pbSelect = new PasswordPushButton(LotSelectClass);
        pbSelect->setObjectName(QString::fromUtf8("pbSelect"));
        pbSelect->setGeometry(QRect(200, 360, 181, 41));
        line = new QFrame(LotSelectClass);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 403, 561, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pbCancel = new PasswordPushButton(LotSelectClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        pbCancel->setGeometry(QRect(480, 420, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbCancel->setIcon(icon);
        pbAllSelect = new PasswordPushButton(LotSelectClass);
        pbAllSelect->setObjectName(QString::fromUtf8("pbAllSelect"));
        pbAllSelect->setEnabled(false);
        pbAllSelect->setGeometry(QRect(10, 420, 91, 31));
        leSearchLotName = new QLineEdit(LotSelectClass);
        leSearchLotName->setObjectName(QString::fromUtf8("leSearchLotName"));
        leSearchLotName->setGeometry(QRect(160, 50, 261, 20));
        label = new QLabel(LotSelectClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 52, 91, 16));
        pbSearch = new PasswordPushButton(LotSelectClass);
        pbSearch->setObjectName(QString::fromUtf8("pbSearch"));
        pbSearch->setGeometry(QRect(430, 45, 91, 31));

        retranslateUi(LotSelectClass);

        QMetaObject::connectSlotsByName(LotSelectClass);
    } // setupUi

    void retranslateUi(QDialog *LotSelectClass)
    {
        LotSelectClass->setWindowTitle(QApplication::translate("LotSelectClass", "LotSelect", 0, QApplication::UnicodeUTF8));
        pbSelect->setText(QApplication::translate("LotSelectClass", "Select", 0, QApplication::UnicodeUTF8));
        pbCancel->setText(QApplication::translate("LotSelectClass", "Cancel", 0, QApplication::UnicodeUTF8));
        pbAllSelect->setText(QApplication::translate("LotSelectClass", "All Select", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LotSelectClass", "Search Lot Name", 0, QApplication::UnicodeUTF8));
        pbSearch->setText(QApplication::translate("LotSelectClass", "Search", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LotSelectClass: public Ui_LotSelectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOTSELECTFORM_H
