/********************************************************************************
** Form generated from reading UI file 'ShowVRSOperationPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWVRSOPERATIONPROPERTYFORM_H
#define UI_SHOWVRSOPERATIONPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ShowVRSOperationPropertyClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *sbInitialMoveLength;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *sbZDistanceStep;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *cbWholeImageRotate;

    void setupUi(QDialog *ShowVRSOperationPropertyClass)
    {
        if (ShowVRSOperationPropertyClass->objectName().isEmpty())
            ShowVRSOperationPropertyClass->setObjectName(QString::fromUtf8("ShowVRSOperationPropertyClass"));
        ShowVRSOperationPropertyClass->resize(185, 96);
        gridLayout = new QGridLayout(ShowVRSOperationPropertyClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ShowVRSOperationPropertyClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        sbInitialMoveLength = new QSpinBox(ShowVRSOperationPropertyClass);
        sbInitialMoveLength->setObjectName(QString::fromUtf8("sbInitialMoveLength"));
        sbInitialMoveLength->setMaximum(999999);
        sbInitialMoveLength->setSingleStep(1);

        horizontalLayout->addWidget(sbInitialMoveLength);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(ShowVRSOperationPropertyClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        sbZDistanceStep = new QSpinBox(ShowVRSOperationPropertyClass);
        sbZDistanceStep->setObjectName(QString::fromUtf8("sbZDistanceStep"));
        sbZDistanceStep->setMaximum(999999);
        sbZDistanceStep->setSingleStep(1);

        horizontalLayout_2->addWidget(sbZDistanceStep);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(ShowVRSOperationPropertyClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        cbWholeImageRotate = new QComboBox(ShowVRSOperationPropertyClass);
        cbWholeImageRotate->addItem(QString());
        cbWholeImageRotate->addItem(QString());
        cbWholeImageRotate->addItem(QString());
        cbWholeImageRotate->addItem(QString());
        cbWholeImageRotate->setObjectName(QString::fromUtf8("cbWholeImageRotate"));
        cbWholeImageRotate->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(cbWholeImageRotate);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        retranslateUi(ShowVRSOperationPropertyClass);

        QMetaObject::connectSlotsByName(ShowVRSOperationPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *ShowVRSOperationPropertyClass)
    {
        ShowVRSOperationPropertyClass->setWindowTitle(QCoreApplication::translate("ShowVRSOperationPropertyClass", "ShowVRSOperationForm", nullptr));
        label->setText(QCoreApplication::translate("ShowVRSOperationPropertyClass", "Initial Move Length", nullptr));
        label_2->setText(QCoreApplication::translate("ShowVRSOperationPropertyClass", "Z Distance Step", nullptr));
        label_3->setText(QCoreApplication::translate("ShowVRSOperationPropertyClass", "Whole Image Rotate", nullptr));
        cbWholeImageRotate->setItemText(0, QCoreApplication::translate("ShowVRSOperationPropertyClass", "0", nullptr));
        cbWholeImageRotate->setItemText(1, QCoreApplication::translate("ShowVRSOperationPropertyClass", "90", nullptr));
        cbWholeImageRotate->setItemText(2, QCoreApplication::translate("ShowVRSOperationPropertyClass", "180", nullptr));
        cbWholeImageRotate->setItemText(3, QCoreApplication::translate("ShowVRSOperationPropertyClass", "270", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ShowVRSOperationPropertyClass: public Ui_ShowVRSOperationPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWVRSOPERATIONPROPERTYFORM_H
