/********************************************************************************
** Form generated from reading UI file 'ListStatisticNGPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTSTATISTICNGPROPERTYFORM_H
#define UI_LISTSTATISTICNGPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ListStatisticNGPropertyClass
{
public:
    QGridLayout *gridLayout;
    QPushButton *pbClose;
    QPushButton *pbUp;
    QPushButton *pbDown;
    QListWidget *listFKeyPriority;
    QSpacerItem *verticalSpacer;
    QPushButton *pbOK;

    void setupUi(QDialog *ListStatisticNGPropertyClass)
    {
        if (ListStatisticNGPropertyClass->objectName().isEmpty())
            ListStatisticNGPropertyClass->setObjectName(QString::fromUtf8("ListStatisticNGPropertyClass"));
        ListStatisticNGPropertyClass->resize(633, 555);
        gridLayout = new QGridLayout(ListStatisticNGPropertyClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbClose = new QPushButton(ListStatisticNGPropertyClass);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));

        gridLayout->addWidget(pbClose, 4, 1, 1, 1);

        pbUp = new QPushButton(ListStatisticNGPropertyClass);
        pbUp->setObjectName(QString::fromUtf8("pbUp"));

        gridLayout->addWidget(pbUp, 0, 1, 1, 1);

        pbDown = new QPushButton(ListStatisticNGPropertyClass);
        pbDown->setObjectName(QString::fromUtf8("pbDown"));

        gridLayout->addWidget(pbDown, 1, 1, 1, 1);

        listFKeyPriority = new QListWidget(ListStatisticNGPropertyClass);
        listFKeyPriority->setObjectName(QString::fromUtf8("listFKeyPriority"));
        listFKeyPriority->setAutoScroll(false);
        listFKeyPriority->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listFKeyPriority->setDragEnabled(false);
        listFKeyPriority->setDragDropOverwriteMode(false);
        listFKeyPriority->setDragDropMode(QAbstractItemView::InternalMove);
        listFKeyPriority->setAlternatingRowColors(false);
        listFKeyPriority->setSelectionBehavior(QAbstractItemView::SelectRows);

        gridLayout->addWidget(listFKeyPriority, 0, 0, 5, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        pbOK = new QPushButton(ListStatisticNGPropertyClass);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));

        gridLayout->addWidget(pbOK, 3, 1, 1, 1);


        retranslateUi(ListStatisticNGPropertyClass);

        QMetaObject::connectSlotsByName(ListStatisticNGPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *ListStatisticNGPropertyClass)
    {
        ListStatisticNGPropertyClass->setWindowTitle(QCoreApplication::translate("ListStatisticNGPropertyClass", "ListStatisticNGForm", nullptr));
        pbClose->setText(QCoreApplication::translate("ListStatisticNGPropertyClass", "Close", nullptr));
        pbUp->setText(QCoreApplication::translate("ListStatisticNGPropertyClass", "Up", nullptr));
        pbDown->setText(QCoreApplication::translate("ListStatisticNGPropertyClass", "Down", nullptr));
        pbOK->setText(QCoreApplication::translate("ListStatisticNGPropertyClass", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListStatisticNGPropertyClass: public Ui_ListStatisticNGPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTSTATISTICNGPROPERTYFORM_H
