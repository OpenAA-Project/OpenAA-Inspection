/********************************************************************************
** Form generated from reading UI file 'JDTUnpacker.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JDTUNPACKER_H
#define UI_JDTUNPACKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_JDTUnpackerClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *lbInfo;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *leJDTFilePath;
    QPushButton *pbOpen;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbExec;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *cbAutoUnpack;

    void setupUi(QDialog *JDTUnpackerClass)
    {
        if (JDTUnpackerClass->objectName().isEmpty())
            JDTUnpackerClass->setObjectName("JDTUnpackerClass");
        JDTUnpackerClass->resize(472, 110);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(JDTUnpackerClass->sizePolicy().hasHeightForWidth());
        JDTUnpackerClass->setSizePolicy(sizePolicy);
        JDTUnpackerClass->setMinimumSize(QSize(0, 110));
        JDTUnpackerClass->setMaximumSize(QSize(16777215, 110));
        JDTUnpackerClass->setAcceptDrops(true);
        gridLayout = new QGridLayout(JDTUnpackerClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(JDTUnpackerClass);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        lbInfo = new QLabel(JDTUnpackerClass);
        lbInfo->setObjectName("lbInfo");

        horizontalLayout->addWidget(lbInfo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(JDTUnpackerClass);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 4);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        leJDTFilePath = new QLineEdit(JDTUnpackerClass);
        leJDTFilePath->setObjectName("leJDTFilePath");
        leJDTFilePath->setAcceptDrops(true);

        horizontalLayout_2->addWidget(leJDTFilePath);

        pbOpen = new QPushButton(JDTUnpackerClass);
        pbOpen->setObjectName("pbOpen");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pbOpen->sizePolicy().hasHeightForWidth());
        pbOpen->setSizePolicy(sizePolicy2);
        pbOpen->setMinimumSize(QSize(30, 0));
        pbOpen->setMaximumSize(QSize(30, 16777215));
        pbOpen->setAcceptDrops(true);

        horizontalLayout_2->addWidget(pbOpen);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 4);

        horizontalSpacer_2 = new QSpacerItem(110, 22, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 0, 1, 1);

        pbExec = new QPushButton(JDTUnpackerClass);
        pbExec->setObjectName("pbExec");

        gridLayout->addWidget(pbExec, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(110, 22, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 2, 1, 1);

        cbAutoUnpack = new QCheckBox(JDTUnpackerClass);
        cbAutoUnpack->setObjectName("cbAutoUnpack");
        cbAutoUnpack->setChecked(true);
        cbAutoUnpack->setTristate(false);

        gridLayout->addWidget(cbAutoUnpack, 3, 3, 1, 1);


        retranslateUi(JDTUnpackerClass);

        QMetaObject::connectSlotsByName(JDTUnpackerClass);
    } // setupUi

    void retranslateUi(QDialog *JDTUnpackerClass)
    {
        JDTUnpackerClass->setWindowTitle(QCoreApplication::translate("JDTUnpackerClass", "JDTUnpacker", nullptr));
        label_2->setText(QCoreApplication::translate("JDTUnpackerClass", "Info:", nullptr));
        lbInfo->setText(QCoreApplication::translate("JDTUnpackerClass", "Idle", nullptr));
        label->setText(QCoreApplication::translate("JDTUnpackerClass", "ver 1.1b", nullptr));
        pbOpen->setText(QCoreApplication::translate("JDTUnpackerClass", "...", nullptr));
        pbExec->setText(QCoreApplication::translate("JDTUnpackerClass", "UnPack", nullptr));
        cbAutoUnpack->setText(QCoreApplication::translate("JDTUnpackerClass", "Drop to Soon Unpack", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JDTUnpackerClass: public Ui_JDTUnpackerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JDTUNPACKER_H
