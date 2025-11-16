/********************************************************************************
** Form generated from reading UI file 'EditRemainTimeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITREMAINTIMEFORM_H
#define UI_EDITREMAINTIMEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditRemainTimeClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *sbHour;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *sbMinuite;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *sbSecond;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *sbMiliSecond;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *EditRemainTimeClass)
    {
        if (EditRemainTimeClass->objectName().isEmpty())
            EditRemainTimeClass->setObjectName("EditRemainTimeClass");
        EditRemainTimeClass->resize(222, 206);
        gridLayout = new QGridLayout(EditRemainTimeClass);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(EditRemainTimeClass);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        sbHour = new QSpinBox(EditRemainTimeClass);
        sbHour->setObjectName("sbHour");
        sbHour->setMaximum(999999999);

        horizontalLayout->addWidget(sbHour);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(EditRemainTimeClass);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        sbMinuite = new QSpinBox(EditRemainTimeClass);
        sbMinuite->setObjectName("sbMinuite");
        sbMinuite->setMaximum(59);

        horizontalLayout_2->addWidget(sbMinuite);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(EditRemainTimeClass);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        sbSecond = new QSpinBox(EditRemainTimeClass);
        sbSecond->setObjectName("sbSecond");
        sbSecond->setMaximum(59);

        horizontalLayout_3->addWidget(sbSecond);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(EditRemainTimeClass);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        sbMiliSecond = new QSpinBox(EditRemainTimeClass);
        sbMiliSecond->setObjectName("sbMiliSecond");
        sbMiliSecond->setMaximum(999);

        horizontalLayout_4->addWidget(sbMiliSecond);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName("hboxLayout");
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(EditRemainTimeClass);
        okButton->setObjectName("okButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        okButton->setIcon(icon);

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(EditRemainTimeClass);
        cancelButton->setObjectName("cancelButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        cancelButton->setIcon(icon1);

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 4, 0, 1, 1);


        retranslateUi(EditRemainTimeClass);
        QObject::connect(okButton, &QPushButton::clicked, EditRemainTimeClass, qOverload<>(&QDialog::accept));
        QObject::connect(cancelButton, &QPushButton::clicked, EditRemainTimeClass, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(EditRemainTimeClass);
    } // setupUi

    void retranslateUi(QDialog *EditRemainTimeClass)
    {
        EditRemainTimeClass->setWindowTitle(QCoreApplication::translate("EditRemainTimeClass", "EditRemainTimeForm", nullptr));
        label->setText(QCoreApplication::translate("EditRemainTimeClass", "Hour", nullptr));
        label_2->setText(QCoreApplication::translate("EditRemainTimeClass", "Minuite", nullptr));
        label_3->setText(QCoreApplication::translate("EditRemainTimeClass", "Second", nullptr));
        label_4->setText(QCoreApplication::translate("EditRemainTimeClass", "Mili Second", nullptr));
        okButton->setText(QCoreApplication::translate("EditRemainTimeClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("EditRemainTimeClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditRemainTimeClass: public Ui_EditRemainTimeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITREMAINTIMEFORM_H
