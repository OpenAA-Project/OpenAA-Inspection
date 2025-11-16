/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SettingDialogClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cbSortOrder;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;

    void setupUi(QDialog *SettingDialogClass)
    {
        if (SettingDialogClass->objectName().isEmpty())
            SettingDialogClass->setObjectName(QString::fromUtf8("SettingDialogClass"));
        SettingDialogClass->resize(295, 82);
        SettingDialogClass->setMinimumSize(QSize(295, 82));
        SettingDialogClass->setMaximumSize(QSize(295, 82));
        gridLayout = new QGridLayout(SettingDialogClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SettingDialogClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        cbSortOrder = new QComboBox(SettingDialogClass);
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->setObjectName(QString::fromUtf8("cbSortOrder"));
        cbSortOrder->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout->addWidget(cbSortOrder);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(168, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        okButton = new QPushButton(SettingDialogClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon);

        gridLayout->addWidget(okButton, 1, 1, 1, 1);

        QWidget::setTabOrder(cbSortOrder, okButton);

        retranslateUi(SettingDialogClass);
        QObject::connect(okButton, SIGNAL(clicked()), SettingDialogClass, SLOT(accept()));

        QMetaObject::connectSlotsByName(SettingDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SettingDialogClass)
    {
        SettingDialogClass->setWindowTitle(QCoreApplication::translate("SettingDialogClass", "Setting Form", nullptr));
        label->setText(QCoreApplication::translate("SettingDialogClass", "Sort Order", nullptr));
        cbSortOrder->setItemText(0, QCoreApplication::translate("SettingDialogClass", "InspectID(Greater)", nullptr));
        cbSortOrder->setItemText(1, QCoreApplication::translate("SettingDialogClass", "InspectID(Lesser)", nullptr));
        cbSortOrder->setItemText(2, QCoreApplication::translate("SettingDialogClass", "InspectTime(Greater)", nullptr));
        cbSortOrder->setItemText(3, QCoreApplication::translate("SettingDialogClass", "InspectTime(Lesser)", nullptr));
        cbSortOrder->setItemText(4, QCoreApplication::translate("SettingDialogClass", "NCCount(Greater)", nullptr));
        cbSortOrder->setItemText(5, QCoreApplication::translate("SettingDialogClass", "NCCount(Lesser)", nullptr));
        cbSortOrder->setItemText(6, QCoreApplication::translate("SettingDialogClass", "NCCountOnlyFront(Greater)", nullptr));
        cbSortOrder->setItemText(7, QCoreApplication::translate("SettingDialogClass", "NCCountOnlyFront(Lesser)", nullptr));
        cbSortOrder->setItemText(8, QCoreApplication::translate("SettingDialogClass", "NCCountOnlyBack(Greater)", nullptr));
        cbSortOrder->setItemText(9, QCoreApplication::translate("SettingDialogClass", "NCCountOnlyBack(Lesser)", nullptr));

        okButton->setText(QCoreApplication::translate("SettingDialogClass", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialogClass: public Ui_SettingDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
