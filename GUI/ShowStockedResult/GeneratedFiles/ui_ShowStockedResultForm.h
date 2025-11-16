/********************************************************************************
** Form generated from reading UI file 'ShowStockedResultForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSTOCKEDRESULTFORM_H
#define UI_SHOWSTOCKEDRESULTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowStockedResultFormClass
{
public:
    QLabel *label;
    QLineEdit *lineEditStockedNumb;
    QPushButton *pushButtonForceWrite;
    QPushButton *pushButtonCast;

    void setupUi(GUIFormBase *ShowStockedResultFormClass)
    {
        if (ShowStockedResultFormClass->objectName().isEmpty())
            ShowStockedResultFormClass->setObjectName("ShowStockedResultFormClass");
        ShowStockedResultFormClass->resize(294, 22);
        label = new QLabel(ShowStockedResultFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditStockedNumb = new QLineEdit(ShowStockedResultFormClass);
        lineEditStockedNumb->setObjectName("lineEditStockedNumb");
        lineEditStockedNumb->setGeometry(QRect(70, 0, 51, 20));
        lineEditStockedNumb->setMaxLength(10);
        lineEditStockedNumb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditStockedNumb->setReadOnly(true);
        pushButtonForceWrite = new QPushButton(ShowStockedResultFormClass);
        pushButtonForceWrite->setObjectName("pushButtonForceWrite");
        pushButtonForceWrite->setGeometry(QRect(130, 0, 91, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonForceWrite->setIcon(icon);
        pushButtonCast = new QPushButton(ShowStockedResultFormClass);
        pushButtonCast->setObjectName("pushButtonCast");
        pushButtonCast->setGeometry(QRect(220, 0, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Trash.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCast->setIcon(icon1);

        retranslateUi(ShowStockedResultFormClass);

        QMetaObject::connectSlotsByName(ShowStockedResultFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowStockedResultFormClass)
    {
        ShowStockedResultFormClass->setWindowTitle(QCoreApplication::translate("ShowStockedResultFormClass", "ShowStockedResultForm", nullptr));
        label->setText(QCoreApplication::translate("ShowStockedResultFormClass", "\350\223\204\347\251\215\346\225\260", nullptr));
        pushButtonForceWrite->setText(QCoreApplication::translate("ShowStockedResultFormClass", "\345\274\267\345\210\266\346\233\270\350\276\274", nullptr));
        pushButtonCast->setText(QCoreApplication::translate("ShowStockedResultFormClass", "\347\240\264\346\243\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowStockedResultFormClass: public Ui_ShowStockedResultFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSTOCKEDRESULTFORM_H
