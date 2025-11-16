/********************************************************************************
** Form generated from reading UI file 'ListMasterDataAndLoadPropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTMASTERDATAANDLOADPROPERTYFORM_H
#define UI_LISTMASTERDATAANDLOADPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ListMasterDataAndLoadPropertyClass
{
public:
    QGridLayout *gridLayout;
    QPushButton *pbCancel;
    QPushButton *pbOK;
    QPushButton *pbMachineIDFilter;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *ListMasterDataAndLoadPropertyClass)
    {
        if (ListMasterDataAndLoadPropertyClass->objectName().isEmpty())
            ListMasterDataAndLoadPropertyClass->setObjectName(QString::fromUtf8("ListMasterDataAndLoadPropertyClass"));
        ListMasterDataAndLoadPropertyClass->resize(302, 154);
        gridLayout = new QGridLayout(ListMasterDataAndLoadPropertyClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbCancel = new QPushButton(ListMasterDataAndLoadPropertyClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));

        gridLayout->addWidget(pbCancel, 1, 3, 1, 1);

        pbOK = new QPushButton(ListMasterDataAndLoadPropertyClass);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));

        gridLayout->addWidget(pbOK, 1, 2, 1, 1);

        pbMachineIDFilter = new QPushButton(ListMasterDataAndLoadPropertyClass);
        pbMachineIDFilter->setObjectName(QString::fromUtf8("pbMachineIDFilter"));

        gridLayout->addWidget(pbMachineIDFilter, 0, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(73, 27, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 2);


        retranslateUi(ListMasterDataAndLoadPropertyClass);
        QObject::connect(pbOK, SIGNAL(clicked()), ListMasterDataAndLoadPropertyClass, SLOT(accept()));
        QObject::connect(pbCancel, SIGNAL(clicked()), ListMasterDataAndLoadPropertyClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(ListMasterDataAndLoadPropertyClass);
    } // setupUi

    void retranslateUi(QDialog *ListMasterDataAndLoadPropertyClass)
    {
        ListMasterDataAndLoadPropertyClass->setWindowTitle(QCoreApplication::translate("ListMasterDataAndLoadPropertyClass", "ListMasterDataAndLoadForm", nullptr));
        pbCancel->setText(QCoreApplication::translate("ListMasterDataAndLoadPropertyClass", "Cancel", nullptr));
        pbOK->setText(QCoreApplication::translate("ListMasterDataAndLoadPropertyClass", "OK", nullptr));
        pbMachineIDFilter->setText(QCoreApplication::translate("ListMasterDataAndLoadPropertyClass", "Set MachineID filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListMasterDataAndLoadPropertyClass: public Ui_ListMasterDataAndLoadPropertyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTMASTERDATAANDLOADPROPERTYFORM_H
