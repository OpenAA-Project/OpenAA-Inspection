/********************************************************************************
** Form generated from reading UI file 'MultiSelectButtonForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTISELECTBUTTONFORM_H
#define UI_MULTISELECTBUTTONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MultiSelectButtonClass
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *vlMachineButtonList;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *MultiSelectButtonClass)
    {
        if (MultiSelectButtonClass->objectName().isEmpty())
            MultiSelectButtonClass->setObjectName(QString::fromUtf8("MultiSelectButtonClass"));
        MultiSelectButtonClass->resize(400, 300);
        gridLayout = new QGridLayout(MultiSelectButtonClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vlMachineButtonList = new QVBoxLayout();
        vlMachineButtonList->setObjectName(QString::fromUtf8("vlMachineButtonList"));

        gridLayout->addLayout(vlMachineButtonList, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(MultiSelectButtonClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(MultiSelectButtonClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);

        retranslateUi(MultiSelectButtonClass);
        QObject::connect(okButton, SIGNAL(clicked()), MultiSelectButtonClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), MultiSelectButtonClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(MultiSelectButtonClass);
    } // setupUi

    void retranslateUi(QDialog *MultiSelectButtonClass)
    {
        MultiSelectButtonClass->setWindowTitle(QCoreApplication::translate("MultiSelectButtonClass", "Dialog", nullptr));
        okButton->setText(QCoreApplication::translate("MultiSelectButtonClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("MultiSelectButtonClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MultiSelectButtonClass: public Ui_MultiSelectButtonClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTISELECTBUTTONFORM_H
