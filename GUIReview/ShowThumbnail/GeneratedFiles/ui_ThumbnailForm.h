/********************************************************************************
** Form generated from reading UI file 'ThumbnailForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THUMBNAILFORM_H
#define UI_THUMBNAILFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include "ImageWidgetInThumbnail.h"

QT_BEGIN_NAMESPACE

class Ui_ThumbnailClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    ImageWidgetInThumbnail *lbMasterImage;
    ImageWidgetInThumbnail *lbNGImage;

    void setupUi(QWidget *ThumbnailClass)
    {
        if (ThumbnailClass->objectName().isEmpty())
            ThumbnailClass->setObjectName(QString::fromUtf8("ThumbnailClass"));
        ThumbnailClass->resize(441, 463);
        gridLayout = new QGridLayout(ThumbnailClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        lbMasterImage = new ImageWidgetInThumbnail(ThumbnailClass);
        lbMasterImage->setObjectName(QString::fromUtf8("lbMasterImage"));

        horizontalLayout->addWidget(lbMasterImage);

        lbNGImage = new ImageWidgetInThumbnail(ThumbnailClass);
        lbNGImage->setObjectName(QString::fromUtf8("lbNGImage"));

        horizontalLayout->addWidget(lbNGImage);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(ThumbnailClass);

        QMetaObject::connectSlotsByName(ThumbnailClass);
    } // setupUi

    void retranslateUi(QWidget *ThumbnailClass)
    {
        ThumbnailClass->setWindowTitle(QCoreApplication::translate("ThumbnailClass", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThumbnailClass: public Ui_ThumbnailClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THUMBNAILFORM_H
