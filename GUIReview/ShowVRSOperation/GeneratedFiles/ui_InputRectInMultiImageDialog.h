/********************************************************************************
** Form generated from reading UI file 'InputRectInMultiImageDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTRECTINMULTIIMAGEDIALOG_H
#define UI_INPUTRECTINMULTIIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "InputRectInMultiImageWidget.h"

QT_BEGIN_NAMESPACE

class Ui_InputRectInMultiImageDialogClass
{
public:
    QGridLayout *gridLayout;
    QGroupBox *gbOperation;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbCreateRect;
    QRadioButton *rbShiftImage;
    InputRectInMultiImageWidget *wCanvas;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *label;

    void setupUi(QDialog *InputRectInMultiImageDialogClass)
    {
        if (InputRectInMultiImageDialogClass->objectName().isEmpty())
            InputRectInMultiImageDialogClass->setObjectName(QString::fromUtf8("InputRectInMultiImageDialogClass"));
        InputRectInMultiImageDialogClass->resize(997, 727);
        gridLayout = new QGridLayout(InputRectInMultiImageDialogClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gbOperation = new QGroupBox(InputRectInMultiImageDialogClass);
        gbOperation->setObjectName(QString::fromUtf8("gbOperation"));
        verticalLayout = new QVBoxLayout(gbOperation);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rbCreateRect = new QRadioButton(gbOperation);
        rbCreateRect->setObjectName(QString::fromUtf8("rbCreateRect"));
        rbCreateRect->setChecked(true);

        verticalLayout->addWidget(rbCreateRect);

        rbShiftImage = new QRadioButton(gbOperation);
        rbShiftImage->setObjectName(QString::fromUtf8("rbShiftImage"));

        verticalLayout->addWidget(rbShiftImage);


        gridLayout->addWidget(gbOperation, 0, 1, 1, 1);

        wCanvas = new InputRectInMultiImageWidget(InputRectInMultiImageDialogClass);
        wCanvas->setObjectName(QString::fromUtf8("wCanvas"));

        gridLayout->addWidget(wCanvas, 0, 0, 3, 1);

        verticalSpacer = new QSpacerItem(20, 540, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(InputRectInMultiImageDialogClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(InputRectInMultiImageDialogClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 3, 0, 1, 2);

        label = new QLabel(InputRectInMultiImageDialogClass);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);

        retranslateUi(InputRectInMultiImageDialogClass);
        QObject::connect(okButton, SIGNAL(clicked()), InputRectInMultiImageDialogClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), InputRectInMultiImageDialogClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(InputRectInMultiImageDialogClass);
    } // setupUi

    void retranslateUi(QDialog *InputRectInMultiImageDialogClass)
    {
        InputRectInMultiImageDialogClass->setWindowTitle(QCoreApplication::translate("InputRectInMultiImageDialogClass", "InputRectInMultiImageForm", nullptr));
        gbOperation->setTitle(QCoreApplication::translate("InputRectInMultiImageDialogClass", "Operations", nullptr));
        rbCreateRect->setText(QCoreApplication::translate("InputRectInMultiImageDialogClass", "CreateRect", nullptr));
        rbShiftImage->setText(QCoreApplication::translate("InputRectInMultiImageDialogClass", "ShiftImage", nullptr));
        okButton->setText(QCoreApplication::translate("InputRectInMultiImageDialogClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("InputRectInMultiImageDialogClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("InputRectInMultiImageDialogClass", "[Ctrl] key is switch", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputRectInMultiImageDialogClass: public Ui_InputRectInMultiImageDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTRECTINMULTIIMAGEDIALOG_H
