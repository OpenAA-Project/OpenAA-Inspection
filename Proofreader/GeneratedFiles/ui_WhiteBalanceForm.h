/********************************************************************************
** Form generated from reading UI file 'WhiteBalanceForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHITEBALANCEFORM_H
#define UI_WHITEBALANCEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WhiteBalanceFormClass
{
public:
    QGridLayout *gridLayout;
    QDockWidget *dwRGBGraph;
    QWidget *dockWidgetContents;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QSpinBox *sbRedAdjustNumb;
    QLabel *lbRedRange;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout1;
    QLabel *label_2;
    QSpinBox *sbGreenAdjustNumb;
    QLabel *lbGreenRange;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout2;
    QLabel *label_3;
    QSpinBox *sbBlueAdjustNumb;
    QLabel *lbBlueRange;
    QSpacerItem *spacerItem3;
    QSpinBox *sbShading;
    QSpacerItem *spacerItem4;
    QPushButton *pbSave;
    QSpacerItem *spacerItem5;
    QPushButton *pbClose;
    QPushButton *pbShading;

    void setupUi(QDialog *WhiteBalanceFormClass)
    {
        if (WhiteBalanceFormClass->objectName().isEmpty())
            WhiteBalanceFormClass->setObjectName("WhiteBalanceFormClass");
        WhiteBalanceFormClass->resize(978, 556);
        gridLayout = new QGridLayout(WhiteBalanceFormClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        dwRGBGraph = new QDockWidget(WhiteBalanceFormClass);
        dwRGBGraph->setObjectName("dwRGBGraph");
        dwRGBGraph->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        dwRGBGraph->setWidget(dockWidgetContents);

        gridLayout->addWidget(dwRGBGraph, 0, 0, 1, 12);

        spacerItem = new QSpacerItem(21, 51, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(spacerItem, 1, 0, 2, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName("hboxLayout");
        label = new QLabel(WhiteBalanceFormClass);
        label->setObjectName("label");

        hboxLayout->addWidget(label);

        sbRedAdjustNumb = new QSpinBox(WhiteBalanceFormClass);
        sbRedAdjustNumb->setObjectName("sbRedAdjustNumb");

        hboxLayout->addWidget(sbRedAdjustNumb);

        lbRedRange = new QLabel(WhiteBalanceFormClass);
        lbRedRange->setObjectName("lbRedRange");

        hboxLayout->addWidget(lbRedRange);


        gridLayout->addLayout(hboxLayout, 1, 1, 2, 1);

        spacerItem1 = new QSpacerItem(21, 51, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(spacerItem1, 1, 2, 2, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName("hboxLayout1");
        label_2 = new QLabel(WhiteBalanceFormClass);
        label_2->setObjectName("label_2");

        hboxLayout1->addWidget(label_2);

        sbGreenAdjustNumb = new QSpinBox(WhiteBalanceFormClass);
        sbGreenAdjustNumb->setObjectName("sbGreenAdjustNumb");

        hboxLayout1->addWidget(sbGreenAdjustNumb);

        lbGreenRange = new QLabel(WhiteBalanceFormClass);
        lbGreenRange->setObjectName("lbGreenRange");

        hboxLayout1->addWidget(lbGreenRange);


        gridLayout->addLayout(hboxLayout1, 1, 3, 2, 1);

        spacerItem2 = new QSpacerItem(21, 51, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(spacerItem2, 1, 4, 2, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName("hboxLayout2");
        label_3 = new QLabel(WhiteBalanceFormClass);
        label_3->setObjectName("label_3");

        hboxLayout2->addWidget(label_3);

        sbBlueAdjustNumb = new QSpinBox(WhiteBalanceFormClass);
        sbBlueAdjustNumb->setObjectName("sbBlueAdjustNumb");

        hboxLayout2->addWidget(sbBlueAdjustNumb);

        lbBlueRange = new QLabel(WhiteBalanceFormClass);
        lbBlueRange->setObjectName("lbBlueRange");

        hboxLayout2->addWidget(lbBlueRange);


        gridLayout->addLayout(hboxLayout2, 1, 5, 2, 1);

        spacerItem3 = new QSpacerItem(21, 51, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(spacerItem3, 1, 6, 2, 1);

        sbShading = new QSpinBox(WhiteBalanceFormClass);
        sbShading->setObjectName("sbShading");
        sbShading->setMaximum(255);

        gridLayout->addWidget(sbShading, 1, 7, 1, 1);

        spacerItem4 = new QSpacerItem(81, 51, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(spacerItem4, 1, 8, 2, 1);

        pbSave = new QPushButton(WhiteBalanceFormClass);
        pbSave->setObjectName("pbSave");
        pbSave->setMinimumSize(QSize(101, 51));

        gridLayout->addWidget(pbSave, 1, 9, 2, 1);

        spacerItem5 = new QSpacerItem(21, 51, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(spacerItem5, 1, 10, 2, 1);

        pbClose = new QPushButton(WhiteBalanceFormClass);
        pbClose->setObjectName("pbClose");
        pbClose->setMinimumSize(QSize(101, 51));

        gridLayout->addWidget(pbClose, 1, 11, 2, 1);

        pbShading = new QPushButton(WhiteBalanceFormClass);
        pbShading->setObjectName("pbShading");
        pbShading->setMinimumSize(QSize(50, 29));
        pbShading->setCheckable(true);

        gridLayout->addWidget(pbShading, 2, 7, 1, 1);


        retranslateUi(WhiteBalanceFormClass);

        QMetaObject::connectSlotsByName(WhiteBalanceFormClass);
    } // setupUi

    void retranslateUi(QDialog *WhiteBalanceFormClass)
    {
        WhiteBalanceFormClass->setWindowTitle(QCoreApplication::translate("WhiteBalanceFormClass", "WhiteBalanceForm", nullptr));
        label->setText(QCoreApplication::translate("WhiteBalanceFormClass", "Red", nullptr));
        label_2->setText(QCoreApplication::translate("WhiteBalanceFormClass", "Green", nullptr));
        label_3->setText(QCoreApplication::translate("WhiteBalanceFormClass", "Blue", nullptr));
        pbSave->setText(QCoreApplication::translate("WhiteBalanceFormClass", "Save", nullptr));
        pbClose->setText(QCoreApplication::translate("WhiteBalanceFormClass", "Close", nullptr));
        pbShading->setText(QCoreApplication::translate("WhiteBalanceFormClass", "Shading", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WhiteBalanceFormClass: public Ui_WhiteBalanceFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHITEBALANCEFORM_H
