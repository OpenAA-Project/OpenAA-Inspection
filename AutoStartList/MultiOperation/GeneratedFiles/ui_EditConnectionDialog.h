/********************************************************************************
** Form generated from reading UI file 'EditConnectionDialog.ui'
**
** Created: Sat Jan 14 22:29:44 2017
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCONNECTIONDIALOG_H
#define UI_EDITCONNECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditConnectionDialog
{
public:
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButtonSet;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *EditConnectionDialog)
    {
        if (EditConnectionDialog->objectName().isEmpty())
            EditConnectionDialog->setObjectName(QString::fromUtf8("EditConnectionDialog"));
        EditConnectionDialog->resize(354, 216);
        label_3 = new QLabel(EditConnectionDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 331, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(EditConnectionDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 60, 331, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(EditConnectionDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 110, 331, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(EditConnectionDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 30, 331, 21));
        lineEdit_2 = new QLineEdit(EditConnectionDialog);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 80, 331, 21));
        lineEdit_3 = new QLineEdit(EditConnectionDialog);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(10, 130, 331, 21));
        pushButtonSet = new QPushButton(EditConnectionDialog);
        pushButtonSet->setObjectName(QString::fromUtf8("pushButtonSet"));
        pushButtonSet->setGeometry(QRect(20, 170, 101, 31));
        pushButtonClose = new QPushButton(EditConnectionDialog);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(250, 170, 93, 31));

        retranslateUi(EditConnectionDialog);

        QMetaObject::connectSlotsByName(EditConnectionDialog);
    } // setupUi

    void retranslateUi(QDialog *EditConnectionDialog)
    {
        EditConnectionDialog->setWindowTitle(QApplication::translate("EditConnectionDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("EditConnectionDialog", "Name", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("EditConnectionDialog", "IP address ( network host name )", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("EditConnectionDialog", "Local path", 0, QApplication::UnicodeUTF8));
        pushButtonSet->setText(QApplication::translate("EditConnectionDialog", "New / Update", 0, QApplication::UnicodeUTF8));
        pushButtonClose->setText(QApplication::translate("EditConnectionDialog", "Clode", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditConnectionDialog: public Ui_EditConnectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCONNECTIONDIALOG_H
