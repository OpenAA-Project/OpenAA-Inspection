/********************************************************************************
** Form generated from reading UI file 'NGImageListForReviewPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NGIMAGELISTFORREVIEWPROPERTYFORM_H
#define UI_NGIMAGELISTFORREVIEWPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_NGImageListForReviewPropertyClass
{
public:
    QGridLayout *gridLayout;
    QGroupBox *gbMoveHistoryOnLeftRightKey;
    QGridLayout *gridLayout_2;
    QCheckBox *cbAllCheckOnMoveHistoryByLeftRightKey;
    QGroupBox *gbMoveHistoryOnEnterKey;
    QGridLayout *gridLayout_3;
    QCheckBox *cbAllCheckOnMoveHistoryByEnterKey;
    QCheckBox *cbAlwaysOperationPreviousEnable;
    QCheckBox *cbIgnoreResultError;
    QPushButton *pbOK;
    QPushButton *pbCancel;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *NGImageListForReviewPropertyClass)
    {
        if (NGImageListForReviewPropertyClass->objectName().isEmpty())
            NGImageListForReviewPropertyClass->setObjectName(QString::fromUtf8("NGImageListForReviewPropertyClass"));
        NGImageListForReviewPropertyClass->resize(384, 251);
        gridLayout = new QGridLayout(NGImageListForReviewPropertyClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gbMoveHistoryOnLeftRightKey = new QGroupBox(NGImageListForReviewPropertyClass);
        gbMoveHistoryOnLeftRightKey->setObjectName(QString::fromUtf8("gbMoveHistoryOnLeftRightKey"));
        gbMoveHistoryOnLeftRightKey->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gbMoveHistoryOnLeftRightKey->setCheckable(true);
        gridLayout_2 = new QGridLayout(gbMoveHistoryOnLeftRightKey);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        cbAllCheckOnMoveHistoryByLeftRightKey = new QCheckBox(gbMoveHistoryOnLeftRightKey);
        cbAllCheckOnMoveHistoryByLeftRightKey->setObjectName(QString::fromUtf8("cbAllCheckOnMoveHistoryByLeftRightKey"));
        cbAllCheckOnMoveHistoryByLeftRightKey->setChecked(true);

        gridLayout_2->addWidget(cbAllCheckOnMoveHistoryByLeftRightKey, 0, 0, 1, 1);


        gridLayout->addWidget(gbMoveHistoryOnLeftRightKey, 0, 0, 1, 3);

        gbMoveHistoryOnEnterKey = new QGroupBox(NGImageListForReviewPropertyClass);
        gbMoveHistoryOnEnterKey->setObjectName(QString::fromUtf8("gbMoveHistoryOnEnterKey"));
        gbMoveHistoryOnEnterKey->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gbMoveHistoryOnEnterKey->setCheckable(true);
        gridLayout_3 = new QGridLayout(gbMoveHistoryOnEnterKey);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        cbAllCheckOnMoveHistoryByEnterKey = new QCheckBox(gbMoveHistoryOnEnterKey);
        cbAllCheckOnMoveHistoryByEnterKey->setObjectName(QString::fromUtf8("cbAllCheckOnMoveHistoryByEnterKey"));
        cbAllCheckOnMoveHistoryByEnterKey->setChecked(true);

        gridLayout_3->addWidget(cbAllCheckOnMoveHistoryByEnterKey, 0, 0, 1, 1);


        gridLayout->addWidget(gbMoveHistoryOnEnterKey, 1, 0, 1, 3);

        cbAlwaysOperationPreviousEnable = new QCheckBox(NGImageListForReviewPropertyClass);
        cbAlwaysOperationPreviousEnable->setObjectName(QString::fromUtf8("cbAlwaysOperationPreviousEnable"));
        cbAlwaysOperationPreviousEnable->setChecked(true);

        gridLayout->addWidget(cbAlwaysOperationPreviousEnable, 3, 0, 1, 3);

        cbIgnoreResultError = new QCheckBox(NGImageListForReviewPropertyClass);
        cbIgnoreResultError->setObjectName(QString::fromUtf8("cbIgnoreResultError"));
        cbIgnoreResultError->setChecked(true);

        gridLayout->addWidget(cbIgnoreResultError, 2, 0, 1, 3);

        pbOK = new QPushButton(NGImageListForReviewPropertyClass);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));

        gridLayout->addWidget(pbOK, 5, 1, 1, 1);

        pbCancel = new QPushButton(NGImageListForReviewPropertyClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));

        gridLayout->addWidget(pbCancel, 5, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 0, 1, 1);


        retranslateUi(NGImageListForReviewPropertyClass);
        QObject::connect(pbOK, SIGNAL(clicked()), NGImageListForReviewPropertyClass, SLOT(accept()));
        QObject::connect(pbCancel, SIGNAL(clicked()), NGImageListForReviewPropertyClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(NGImageListForReviewPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *NGImageListForReviewPropertyClass)
    {
        NGImageListForReviewPropertyClass->setWindowTitle(QCoreApplication::translate("NGImageListForReviewPropertyClass", "NGImageListForReviewForm", nullptr));
        gbMoveHistoryOnLeftRightKey->setTitle(QCoreApplication::translate("NGImageListForReviewPropertyClass", "Enable Left and Right key to move History", nullptr));
        cbAllCheckOnMoveHistoryByLeftRightKey->setText(QCoreApplication::translate("NGImageListForReviewPropertyClass", "must all NG was checked", nullptr));
        gbMoveHistoryOnEnterKey->setTitle(QCoreApplication::translate("NGImageListForReviewPropertyClass", "Enable Enter key to move History", nullptr));
        cbAllCheckOnMoveHistoryByEnterKey->setText(QCoreApplication::translate("NGImageListForReviewPropertyClass", "must all NG was checked", nullptr));
        cbAlwaysOperationPreviousEnable->setText(QCoreApplication::translate("NGImageListForReviewPropertyClass", "Previous operation is always enable.", nullptr));
        cbIgnoreResultError->setText(QCoreApplication::translate("NGImageListForReviewPropertyClass", "Ignore then result is error. ex)MaxOver, TimeOut", nullptr));
        pbOK->setText(QCoreApplication::translate("NGImageListForReviewPropertyClass", "OK", nullptr));
        pbCancel->setText(QCoreApplication::translate("NGImageListForReviewPropertyClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NGImageListForReviewPropertyClass: public Ui_NGImageListForReviewPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NGIMAGELISTFORREVIEWPROPERTYFORM_H
