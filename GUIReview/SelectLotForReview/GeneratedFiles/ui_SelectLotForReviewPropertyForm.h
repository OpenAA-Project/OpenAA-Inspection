/********************************************************************************
** Form generated from reading UI file 'SelectLotForReviewPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLOTFORREVIEWPROPERTYFORM_H
#define UI_SELECTLOTFORREVIEWPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SelectLotForReviewPropertyClass
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *gbAutoShowResultLotLoadForm;
    QGridLayout *gridLayout;
    QCheckBox *cbShowOnlyError;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbOK;
    QPushButton *pbCancel;

    void setupUi(QDialog *SelectLotForReviewPropertyClass)
    {
        if (SelectLotForReviewPropertyClass->objectName().isEmpty())
            SelectLotForReviewPropertyClass->setObjectName(QString::fromUtf8("SelectLotForReviewPropertyClass"));
        SelectLotForReviewPropertyClass->resize(278, 122);
        gridLayout_2 = new QGridLayout(SelectLotForReviewPropertyClass);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gbAutoShowResultLotLoadForm = new QGroupBox(SelectLotForReviewPropertyClass);
        gbAutoShowResultLotLoadForm->setObjectName(QString::fromUtf8("gbAutoShowResultLotLoadForm"));
        gbAutoShowResultLotLoadForm->setCheckable(true);
        gridLayout = new QGridLayout(gbAutoShowResultLotLoadForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cbShowOnlyError = new QCheckBox(gbAutoShowResultLotLoadForm);
        cbShowOnlyError->setObjectName(QString::fromUtf8("cbShowOnlyError"));

        gridLayout->addWidget(cbShowOnlyError, 0, 0, 1, 1);


        gridLayout_2->addWidget(gbAutoShowResultLotLoadForm, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbOK = new QPushButton(SelectLotForReviewPropertyClass);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));

        horizontalLayout->addWidget(pbOK);

        pbCancel = new QPushButton(SelectLotForReviewPropertyClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));

        horizontalLayout->addWidget(pbCancel);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 1);

        retranslateUi(SelectLotForReviewPropertyClass);
        QObject::connect(pbOK, SIGNAL(clicked()), SelectLotForReviewPropertyClass, SLOT(accept()));
        QObject::connect(pbCancel, SIGNAL(clicked()), SelectLotForReviewPropertyClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(SelectLotForReviewPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *SelectLotForReviewPropertyClass)
    {
        SelectLotForReviewPropertyClass->setWindowTitle(QCoreApplication::translate("SelectLotForReviewPropertyClass", "SelectLotForReviewForm", nullptr));
        gbAutoShowResultLotLoadForm->setTitle(QCoreApplication::translate("SelectLotForReviewPropertyClass", "Show result of lot loaded", nullptr));
        cbShowOnlyError->setText(QCoreApplication::translate("SelectLotForReviewPropertyClass", "show then result has error", nullptr));
        pbOK->setText(QCoreApplication::translate("SelectLotForReviewPropertyClass", "OK", nullptr));
        pbCancel->setText(QCoreApplication::translate("SelectLotForReviewPropertyClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLotForReviewPropertyClass: public Ui_SelectLotForReviewPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLOTFORREVIEWPROPERTYFORM_H
