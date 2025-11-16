/********************************************************************************
** Form generated from reading UI file 'CreateClassForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATECLASSFORM_H
#define UI_CREATECLASSFORM_H

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

class Ui_CreateClassFormDialog
{
public:
    QLineEdit *liedPassword;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *liedClassName;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *CreateClassFormDialog)
    {
        if (CreateClassFormDialog->objectName().isEmpty())
            CreateClassFormDialog->setObjectName("CreateClassFormDialog");
        CreateClassFormDialog->resize(436, 189);
        liedPassword = new QLineEdit(CreateClassFormDialog);
        liedPassword->setObjectName("liedPassword");
        liedPassword->setGeometry(QRect(10, 104, 411, 24));
        label_2 = new QLabel(CreateClassFormDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 73, 411, 22));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        label_2->setFont(font);
        label = new QLabel(CreateClassFormDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 9, 411, 22));
        label->setFont(font);
        liedClassName = new QLineEdit(CreateClassFormDialog);
        liedClassName->setObjectName("liedClassName");
        liedClassName->setGeometry(QRect(10, 40, 411, 24));
        layoutWidget = new QWidget(CreateClassFormDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(18, 140, 401, 36));
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
        okButton->setChecked(false);

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName("cancelButton");

        hboxLayout->addWidget(cancelButton);


        retranslateUi(CreateClassFormDialog);

        QMetaObject::connectSlotsByName(CreateClassFormDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateClassFormDialog)
    {
        CreateClassFormDialog->setWindowTitle(QCoreApplication::translate("CreateClassFormDialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("CreateClassFormDialog", "\343\203\221\343\202\271\343\203\257\343\203\274\343\203\211   \342\200\273\345\215\212\350\247\222\350\213\261\346\225\260\345\255\227", nullptr));
        label->setText(QCoreApplication::translate("CreateClassFormDialog", "\343\202\257\343\203\251\343\202\271\345\220\215\347\247\260", nullptr));
        okButton->setText(QCoreApplication::translate("CreateClassFormDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("CreateClassFormDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateClassFormDialog: public Ui_CreateClassFormDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATECLASSFORM_H
