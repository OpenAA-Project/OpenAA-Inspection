/********************************************************************************
** Form generated from reading UI file 'InputPasswordForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTPASSWORDFORM_H
#define UI_INPUTPASSWORDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputPasswordFormDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *liedPassword;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *InputPasswordFormDialog)
    {
        if (InputPasswordFormDialog->objectName().isEmpty())
            InputPasswordFormDialog->setObjectName("InputPasswordFormDialog");
        InputPasswordFormDialog->resize(362, 150);
        label = new QLabel(InputPasswordFormDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 16, 336, 18));
        label_2 = new QLabel(InputPasswordFormDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 43, 336, 18));
        liedPassword = new QLineEdit(InputPasswordFormDialog);
        liedPassword->setObjectName("liedPassword");
        liedPassword->setGeometry(QRect(10, 70, 336, 24));
        layoutWidget = new QWidget(InputPasswordFormDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 100, 341, 36));
        hboxLayout = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName("okButton");

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName("cancelButton");

        hboxLayout->addWidget(cancelButton);


        retranslateUi(InputPasswordFormDialog);
        QObject::connect(okButton, &QPushButton::clicked, InputPasswordFormDialog, qOverload<>(&QDialog::accept));
        QObject::connect(cancelButton, &QPushButton::clicked, InputPasswordFormDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(InputPasswordFormDialog);
    } // setupUi

    void retranslateUi(QDialog *InputPasswordFormDialog)
    {
        InputPasswordFormDialog->setWindowTitle(QCoreApplication::translate("InputPasswordFormDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("InputPasswordFormDialog", "\343\203\255\343\203\203\343\202\257\343\201\225\343\202\214\343\201\246\343\201\204\343\201\276\343\201\231", nullptr));
        label_2->setText(QCoreApplication::translate("InputPasswordFormDialog", "\343\203\221\343\202\271\343\203\257\343\203\274\343\203\211\343\202\222\345\205\245\345\212\233\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204", nullptr));
        okButton->setText(QCoreApplication::translate("InputPasswordFormDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("InputPasswordFormDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputPasswordFormDialog: public Ui_InputPasswordFormDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTPASSWORDFORM_H
