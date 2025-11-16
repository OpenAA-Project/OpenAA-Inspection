/********************************************************************************
** Form generated from reading UI file 'ShowHistoryListForReviewPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWHISTORYLISTFORREVIEWPROPERTYFORM_H
#define UI_SHOWHISTORYLISTFORREVIEWPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ShowHistoryListForReviewPropertyClass
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label;

    void setupUi(QDialog *ShowHistoryListForReviewPropertyClass)
    {
        if (ShowHistoryListForReviewPropertyClass->objectName().isEmpty())
            ShowHistoryListForReviewPropertyClass->setObjectName(QString::fromUtf8("ShowHistoryListForReviewPropertyClass"));
        ShowHistoryListForReviewPropertyClass->resize(624, 188);
        gridLayout_2 = new QGridLayout(ShowHistoryListForReviewPropertyClass);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(ShowHistoryListForReviewPropertyClass);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        retranslateUi(ShowHistoryListForReviewPropertyClass);

        QMetaObject::connectSlotsByName(ShowHistoryListForReviewPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *ShowHistoryListForReviewPropertyClass)
    {
        ShowHistoryListForReviewPropertyClass->setWindowTitle(QCoreApplication::translate("ShowHistoryListForReviewPropertyClass", "ShowHistoryListForReviewForm", nullptr));
        label->setText(QCoreApplication::translate("ShowHistoryListForReviewPropertyClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowHistoryListForReviewPropertyClass: public Ui_ShowHistoryListForReviewPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWHISTORYLISTFORREVIEWPROPERTYFORM_H
