/********************************************************************************
** Form generated from reading UI file 'InspectionDataForm.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSPECTIONDATAFORM_H
#define UI_INSPECTIONDATAFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>
#include "PasswordPushButton.h"

QT_BEGIN_NAMESPACE

class Ui_InspectionDataFormClass
{
public:
    PasswordPushButton *pbEnter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *leSumInsDataF;
    QLabel *label_2;
    QLineEdit *leOKInsDataF;
    QLabel *label_3;
    QLineEdit *leNGInsDataF;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout1;
    QLabel *label_4;
    QLineEdit *leSumInsDataB;
    QLabel *label_5;
    QLineEdit *leOKInsDataB;
    QLabel *label_6;
    QLineEdit *leNGInsDataB;
    QTextEdit *teMessage;

    void setupUi(QDialog *InspectionDataFormClass)
    {
        if (InspectionDataFormClass->objectName().isEmpty())
            InspectionDataFormClass->setObjectName(QString::fromUtf8("InspectionDataFormClass"));
        InspectionDataFormClass->resize(490, 370);
        pbEnter = new PasswordPushButton(InspectionDataFormClass);
        pbEnter->setObjectName(QString::fromUtf8("pbEnter"));
        pbEnter->setGeometry(QRect(130, 210, 231, 61));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        pbEnter->setFont(font);
        pbEnter->setDefault(true);
        groupBox = new QGroupBox(InspectionDataFormClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(80, 20, 161, 181));
        QFont font1;
        font1.setPointSize(12);
        groupBox->setFont(font1);
        groupBox->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        leSumInsDataF = new QLineEdit(groupBox);
        leSumInsDataF->setObjectName(QString::fromUtf8("leSumInsDataF"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        leSumInsDataF->setFont(font2);
        leSumInsDataF->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leSumInsDataF->setReadOnly(true);

        gridLayout->addWidget(leSumInsDataF, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        leOKInsDataF = new QLineEdit(groupBox);
        leOKInsDataF->setObjectName(QString::fromUtf8("leOKInsDataF"));
        leOKInsDataF->setFont(font2);
        leOKInsDataF->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leOKInsDataF->setReadOnly(true);

        gridLayout->addWidget(leOKInsDataF, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        leNGInsDataF = new QLineEdit(groupBox);
        leNGInsDataF->setObjectName(QString::fromUtf8("leNGInsDataF"));
        leNGInsDataF->setFont(font2);
        leNGInsDataF->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leNGInsDataF->setReadOnly(true);

        gridLayout->addWidget(leNGInsDataF, 2, 1, 1, 1);

        groupBox_2 = new QGroupBox(InspectionDataFormClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(250, 20, 161, 181));
        groupBox_2->setFont(font1);
        groupBox_2->setAlignment(Qt::AlignCenter);
        gridLayout1 = new QGridLayout(groupBox_2);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout1->addWidget(label_4, 0, 0, 1, 1);

        leSumInsDataB = new QLineEdit(groupBox_2);
        leSumInsDataB->setObjectName(QString::fromUtf8("leSumInsDataB"));
        leSumInsDataB->setFont(font2);
        leSumInsDataB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leSumInsDataB->setReadOnly(true);

        gridLayout1->addWidget(leSumInsDataB, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout1->addWidget(label_5, 1, 0, 1, 1);

        leOKInsDataB = new QLineEdit(groupBox_2);
        leOKInsDataB->setObjectName(QString::fromUtf8("leOKInsDataB"));
        leOKInsDataB->setFont(font2);
        leOKInsDataB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leOKInsDataB->setReadOnly(true);

        gridLayout1->addWidget(leOKInsDataB, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout1->addWidget(label_6, 2, 0, 1, 1);

        leNGInsDataB = new QLineEdit(groupBox_2);
        leNGInsDataB->setObjectName(QString::fromUtf8("leNGInsDataB"));
        leNGInsDataB->setFont(font2);
        leNGInsDataB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leNGInsDataB->setReadOnly(true);

        gridLayout1->addWidget(leNGInsDataB, 2, 1, 1, 1);

        teMessage = new QTextEdit(InspectionDataFormClass);
        teMessage->setObjectName(QString::fromUtf8("teMessage"));
        teMessage->setGeometry(QRect(10, 280, 471, 81));
        teMessage->setFont(font);
        teMessage->setReadOnly(true);

        retranslateUi(InspectionDataFormClass);

        QMetaObject::connectSlotsByName(InspectionDataFormClass);
    } // setupUi

    void retranslateUi(QDialog *InspectionDataFormClass)
    {
        InspectionDataFormClass->setWindowTitle(QApplication::translate("InspectionDataFormClass", "\346\244\234\346\237\273\343\203\207\343\203\274\343\202\277\350\241\250\347\244\272", 0, QApplication::UnicodeUTF8));
        pbEnter->setText(QApplication::translate("InspectionDataFormClass", "Close at Enter key", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("InspectionDataFormClass", "Front side", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("InspectionDataFormClass", "Total", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("InspectionDataFormClass", "OK count", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("InspectionDataFormClass", "NG count", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("InspectionDataFormClass", "Back side", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("InspectionDataFormClass", "Total", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("InspectionDataFormClass", "OK count", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("InspectionDataFormClass", "NG count", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InspectionDataFormClass: public Ui_InspectionDataFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSPECTIONDATAFORM_H
