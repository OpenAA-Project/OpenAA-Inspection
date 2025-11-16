/********************************************************************************
** Form generated from reading UI file 'XMLServerCommForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XMLSERVERCOMMFORM_H
#define UI_XMLSERVERCOMMFORM_H

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

class Ui_XMLServerCommClass
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout_2;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLineEdit *leAddress;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QLineEdit *lePort;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *XMLServerCommClass)
    {
        if (XMLServerCommClass->objectName().isEmpty())
            XMLServerCommClass->setObjectName("XMLServerCommClass");
        XMLServerCommClass->resize(331, 183);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(XMLServerCommClass->sizePolicy().hasHeightForWidth());
        XMLServerCommClass->setSizePolicy(sizePolicy);
        XMLServerCommClass->setMinimumSize(QSize(331, 183));
        XMLServerCommClass->setMaximumSize(QSize(331, 183));
        horizontalLayout_3 = new QHBoxLayout(XMLServerCommClass);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(XMLServerCommClass);
        okButton->setObjectName("okButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        okButton->setIcon(icon);

        hboxLayout->addWidget(okButton);


        gridLayout_2->addLayout(hboxLayout, 5, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(XMLServerCommClass);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        leAddress = new QLineEdit(XMLServerCommClass);
        leAddress->setObjectName("leAddress");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leAddress->sizePolicy().hasHeightForWidth());
        leAddress->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(leAddress);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_2 = new QLabel(XMLServerCommClass);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);

        lePort = new QLineEdit(XMLServerCommClass);
        lePort->setObjectName("lePort");
        sizePolicy2.setHeightForWidth(lePort->sizePolicy().hasHeightForWidth());
        lePort->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(lePort);


        gridLayout_2->addLayout(horizontalLayout, 4, 0, 1, 1);

        label_3 = new QLabel(XMLServerCommClass);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(XMLServerCommClass);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(XMLServerCommClass);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_2);


        retranslateUi(XMLServerCommClass);
        QObject::connect(okButton, &QPushButton::clicked, XMLServerCommClass, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(XMLServerCommClass);
    } // setupUi

    void retranslateUi(QDialog *XMLServerCommClass)
    {
        XMLServerCommClass->setWindowTitle(QCoreApplication::translate("XMLServerCommClass", "check connection to XMLServer", nullptr));
        okButton->setText(QCoreApplication::translate("XMLServerCommClass", "OK", nullptr));
        label->setText(QCoreApplication::translate("XMLServerCommClass", "Address", nullptr));
        label_2->setText(QCoreApplication::translate("XMLServerCommClass", "Port", nullptr));
        label_3->setText(QCoreApplication::translate("XMLServerCommClass", "2. check param to XMLServer", nullptr));
        label_4->setText(QCoreApplication::translate("XMLServerCommClass", "Failuer to connect XMLServer", nullptr));
        label_5->setText(QCoreApplication::translate("XMLServerCommClass", "1. check XMLServer is executed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XMLServerCommClass: public Ui_XMLServerCommClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XMLSERVERCOMMFORM_H
