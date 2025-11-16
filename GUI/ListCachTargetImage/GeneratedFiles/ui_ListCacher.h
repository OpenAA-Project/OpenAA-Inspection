/********************************************************************************
** Form generated from reading UI file 'ListCacher.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTCACHER_H
#define UI_LISTCACHER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListCacherClass
{
public:
    QPushButton *pushButtonSavePix;
    QPushButton *pushButtonSetToTarget;
    QListWidget *listWidget;

    void setupUi(GUIFormBase *ListCacherClass)
    {
        if (ListCacherClass->objectName().isEmpty())
            ListCacherClass->setObjectName("ListCacherClass");
        ListCacherClass->resize(201, 212);
        pushButtonSavePix = new QPushButton(ListCacherClass);
        pushButtonSavePix->setObjectName("pushButtonSavePix");
        pushButtonSavePix->setGeometry(QRect(90, 90, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSavePix->setIcon(icon);
        pushButtonSetToTarget = new QPushButton(ListCacherClass);
        pushButtonSetToTarget->setObjectName("pushButtonSetToTarget");
        pushButtonSetToTarget->setGeometry(QRect(90, 20, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetToTarget->setIcon(icon1);
        listWidget = new QListWidget(ListCacherClass);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 10, 71, 192));

        retranslateUi(ListCacherClass);

        QMetaObject::connectSlotsByName(ListCacherClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ListCacherClass)
    {
        ListCacherClass->setWindowTitle(QCoreApplication::translate("ListCacherClass", "ListCacher", nullptr));
        pushButtonSavePix->setText(QCoreApplication::translate("ListCacherClass", "Save Pix", nullptr));
        pushButtonSetToTarget->setText(QCoreApplication::translate("ListCacherClass", "Set to Target", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListCacherClass: public Ui_ListCacherClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTCACHER_H
