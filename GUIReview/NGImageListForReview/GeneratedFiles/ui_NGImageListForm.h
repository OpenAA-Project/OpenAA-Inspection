/********************************************************************************
** Form generated from reading UI file 'NGImageListForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NGIMAGELISTFORM_H
#define UI_NGIMAGELISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NGImageListClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *tblMain;
    QProgressBar *progKeyWait;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *leNGCount;

    void setupUi(QWidget *NGImageListClass)
    {
        if (NGImageListClass->objectName().isEmpty())
            NGImageListClass->setObjectName(QString::fromUtf8("NGImageListClass"));
        NGImageListClass->resize(342, 392);
        gridLayout = new QGridLayout(NGImageListClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tblMain = new QTableWidget(NGImageListClass);
        if (tblMain->columnCount() < 3)
            tblMain->setColumnCount(3);
        if (tblMain->rowCount() < 100)
            tblMain->setRowCount(100);
        tblMain->setObjectName(QString::fromUtf8("tblMain"));
        tblMain->setFocusPolicy(Qt::StrongFocus);
        tblMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblMain->setProperty("showDropIndicator", QVariant(false));
        tblMain->setDragDropOverwriteMode(false);
        tblMain->setAlternatingRowColors(false);
        tblMain->setSelectionMode(QAbstractItemView::SingleSelection);
        tblMain->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblMain->setTextElideMode(Qt::ElideNone);
        tblMain->setRowCount(100);
        tblMain->setColumnCount(3);

        verticalLayout->addWidget(tblMain);

        progKeyWait = new QProgressBar(NGImageListClass);
        progKeyWait->setObjectName(QString::fromUtf8("progKeyWait"));
        progKeyWait->setValue(100);
        progKeyWait->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        progKeyWait->setTextVisible(true);
        progKeyWait->setOrientation(Qt::Horizontal);
        progKeyWait->setInvertedAppearance(false);
        progKeyWait->setTextDirection(QProgressBar::TopToBottom);

        verticalLayout->addWidget(progKeyWait);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(NGImageListClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        leNGCount = new QLineEdit(NGImageListClass);
        leNGCount->setObjectName(QString::fromUtf8("leNGCount"));
        leNGCount->setFocusPolicy(Qt::NoFocus);
        leNGCount->setFrame(false);
        leNGCount->setCursorPosition(1);
        leNGCount->setAlignment(Qt::AlignCenter);
        leNGCount->setReadOnly(true);

        horizontalLayout->addWidget(leNGCount);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(NGImageListClass);

        QMetaObject::connectSlotsByName(NGImageListClass);
    } // setupUi

    void retranslateUi(QWidget *NGImageListClass)
    {
        NGImageListClass->setWindowTitle(QCoreApplication::translate("NGImageListClass", "Form", nullptr));
        progKeyWait->setFormat(QCoreApplication::translate("NGImageListClass", "WaitTime", nullptr));
        label->setText(QCoreApplication::translate("NGImageListClass", "NG Count", nullptr));
        leNGCount->setText(QCoreApplication::translate("NGImageListClass", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NGImageListClass: public Ui_NGImageListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NGIMAGELISTFORM_H
