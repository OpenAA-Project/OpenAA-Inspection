/********************************************************************************
** Form generated from reading UI file 'PasswordForm.ui'
**
** Created: Fri Mar 7 22:34:33 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDFORM_H
#define UI_PASSWORDFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_InputPasswordClass
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lePassword;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *InputPasswordClass)
    {
        if (InputPasswordClass->objectName().isEmpty())
            InputPasswordClass->setObjectName(QString::fromUtf8("InputPasswordClass"));
        InputPasswordClass->resize(271, 77);
        gridLayout = new QGridLayout(InputPasswordClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lePassword = new QLineEdit(InputPasswordClass);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));

        gridLayout->addWidget(lePassword, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(InputPasswordClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(InputPasswordClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);


        retranslateUi(InputPasswordClass);
        QObject::connect(okButton, SIGNAL(clicked()), InputPasswordClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), InputPasswordClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(InputPasswordClass);
    } // setupUi

    void retranslateUi(QDialog *InputPasswordClass)
    {
        InputPasswordClass->setWindowTitle(QApplication::translate("InputPasswordClass", "InputPassword", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("InputPasswordClass", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("InputPasswordClass", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InputPasswordClass: public Ui_InputPasswordClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDFORM_H
