/********************************************************************************
** Form generated from reading UI file 'GeneralGroupSelfPasswordForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERALGROUPSELFPASSWORDFORM_H
#define UI_GENERALGROUPSELFPASSWORDFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_GeneralGroupSelfPasswordClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lePassword;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *GeneralGroupSelfPasswordClass)
    {
        if (GeneralGroupSelfPasswordClass->objectName().isEmpty())
            GeneralGroupSelfPasswordClass->setObjectName("GeneralGroupSelfPasswordClass");
        GeneralGroupSelfPasswordClass->resize(413, 82);
        gridLayout = new QGridLayout(GeneralGroupSelfPasswordClass);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(GeneralGroupSelfPasswordClass);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lePassword = new QLineEdit(GeneralGroupSelfPasswordClass);
        lePassword->setObjectName("lePassword");

        horizontalLayout->addWidget(lePassword);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(188, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        okButton = new QPushButton(GeneralGroupSelfPasswordClass);
        okButton->setObjectName("okButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        okButton->setIcon(icon);

        gridLayout->addWidget(okButton, 1, 1, 1, 1);

        cancelButton = new QPushButton(GeneralGroupSelfPasswordClass);
        cancelButton->setObjectName("cancelButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        cancelButton->setIcon(icon1);

        gridLayout->addWidget(cancelButton, 1, 2, 1, 1);


        retranslateUi(GeneralGroupSelfPasswordClass);
        QObject::connect(okButton, &QPushButton::clicked, GeneralGroupSelfPasswordClass, qOverload<>(&QDialog::accept));
        QObject::connect(cancelButton, &QPushButton::clicked, GeneralGroupSelfPasswordClass, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(GeneralGroupSelfPasswordClass);
    } // setupUi

    void retranslateUi(QDialog *GeneralGroupSelfPasswordClass)
    {
        GeneralGroupSelfPasswordClass->setWindowTitle(QCoreApplication::translate("GeneralGroupSelfPasswordClass", "Input Password", nullptr));
        label->setText(QCoreApplication::translate("GeneralGroupSelfPasswordClass", "Password", nullptr));
        okButton->setText(QCoreApplication::translate("GeneralGroupSelfPasswordClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("GeneralGroupSelfPasswordClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeneralGroupSelfPasswordClass: public Ui_GeneralGroupSelfPasswordClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERALGROUPSELFPASSWORDFORM_H
