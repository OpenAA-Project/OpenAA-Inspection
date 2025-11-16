/********************************************************************************
** Form generated from reading UI file 'NGImageForReviewPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NGIMAGEFORREVIEWPROPERTYFORM_H
#define UI_NGIMAGEFORREVIEWPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NGImageForReviewPropertyClass
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cbRotate;
    QPushButton *pbClose;
    QCheckBox *checkBoxBlankImageOnCopyMaster;

    void setupUi(QDialog *NGImageForReviewPropertyClass)
    {
        if (NGImageForReviewPropertyClass->objectName().isEmpty())
            NGImageForReviewPropertyClass->setObjectName(QString::fromUtf8("NGImageForReviewPropertyClass"));
        NGImageForReviewPropertyClass->resize(194, 113);
        gridLayout = new QGridLayout(NGImageForReviewPropertyClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(NGImageForReviewPropertyClass);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cbRotate = new QComboBox(NGImageForReviewPropertyClass);
        cbRotate->addItem(QString());
        cbRotate->addItem(QString());
        cbRotate->addItem(QString());
        cbRotate->addItem(QString());
        cbRotate->setObjectName(QString::fromUtf8("cbRotate"));

        gridLayout->addWidget(cbRotate, 0, 1, 1, 1);

        pbClose = new QPushButton(NGImageForReviewPropertyClass);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));

        gridLayout->addWidget(pbClose, 2, 1, 1, 1);

        checkBoxBlankImageOnCopyMaster = new QCheckBox(NGImageForReviewPropertyClass);
        checkBoxBlankImageOnCopyMaster->setObjectName(QString::fromUtf8("checkBoxBlankImageOnCopyMaster"));

        gridLayout->addWidget(checkBoxBlankImageOnCopyMaster, 1, 0, 1, 2);


        retranslateUi(NGImageForReviewPropertyClass);
        QObject::connect(pbClose, SIGNAL(clicked()), NGImageForReviewPropertyClass, SLOT(accept()));

        QMetaObject::connectSlotsByName(NGImageForReviewPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *NGImageForReviewPropertyClass)
    {
        NGImageForReviewPropertyClass->setWindowTitle(QCoreApplication::translate("NGImageForReviewPropertyClass", "NGImageForReviewForm", nullptr));
        label->setText(QCoreApplication::translate("NGImageForReviewPropertyClass", "Rotate", nullptr));
        cbRotate->setItemText(0, QCoreApplication::translate("NGImageForReviewPropertyClass", "0", nullptr));
        cbRotate->setItemText(1, QCoreApplication::translate("NGImageForReviewPropertyClass", "90", nullptr));
        cbRotate->setItemText(2, QCoreApplication::translate("NGImageForReviewPropertyClass", "180", nullptr));
        cbRotate->setItemText(3, QCoreApplication::translate("NGImageForReviewPropertyClass", "270", nullptr));

        pbClose->setText(QCoreApplication::translate("NGImageForReviewPropertyClass", "Close", nullptr));
        checkBoxBlankImageOnCopyMaster->setText(QCoreApplication::translate("NGImageForReviewPropertyClass", "Blank image on CopyMaster", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NGImageForReviewPropertyClass: public Ui_NGImageForReviewPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NGIMAGEFORREVIEWPROPERTYFORM_H
