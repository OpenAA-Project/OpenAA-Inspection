/********************************************************************************
** Form generated from reading UI file 'ReviewZForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVIEWZFORM_H
#define UI_REVIEWZFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ReviewZForm
{
public:
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QPushButton *pushButton10Up;
    QPushButton *pushButton10Dn;
    QPushButton *pushButton100Up;
    QPushButton *pushButton100Dn;
    QPushButton *pushButtonSet;

    void setupUi(GUIFormBase *ReviewZForm)
    {
        if (ReviewZForm->objectName().isEmpty())
            ReviewZForm->setObjectName(QString::fromUtf8("ReviewZForm"));
        ReviewZForm->resize(227, 79);
        label = new QLabel(ReviewZForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 10, 61, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBox = new QSpinBox(ReviewZForm);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(0, 28, 61, 22));
        spinBox->setMaximum(999999);
        label_2 = new QLabel(ReviewZForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 50, 21, 21));
        pushButton10Up = new QPushButton(ReviewZForm);
        pushButton10Up->setObjectName(QString::fromUtf8("pushButton10Up"));
        pushButton10Up->setGeometry(QRect(126, 8, 51, 31));
        pushButton10Dn = new QPushButton(ReviewZForm);
        pushButton10Dn->setObjectName(QString::fromUtf8("pushButton10Dn"));
        pushButton10Dn->setGeometry(QRect(126, 40, 51, 31));
        pushButton100Up = new QPushButton(ReviewZForm);
        pushButton100Up->setObjectName(QString::fromUtf8("pushButton100Up"));
        pushButton100Up->setGeometry(QRect(176, 8, 51, 31));
        pushButton100Dn = new QPushButton(ReviewZForm);
        pushButton100Dn->setObjectName(QString::fromUtf8("pushButton100Dn"));
        pushButton100Dn->setGeometry(QRect(176, 40, 51, 31));
        pushButtonSet = new QPushButton(ReviewZForm);
        pushButtonSet->setObjectName(QString::fromUtf8("pushButtonSet"));
        pushButtonSet->setGeometry(QRect(70, 20, 51, 41));

        retranslateUi(ReviewZForm);

        QMetaObject::connectSlotsByName(ReviewZForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ReviewZForm)
    {
        ReviewZForm->setWindowTitle(QCoreApplication::translate("ReviewZForm", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ReviewZForm", "Z Height", nullptr));
        label_2->setText(QCoreApplication::translate("ReviewZForm", "um", nullptr));
        pushButton10Up->setText(QCoreApplication::translate("ReviewZForm", "+10up", nullptr));
        pushButton10Dn->setText(QCoreApplication::translate("ReviewZForm", "-10dn", nullptr));
        pushButton100Up->setText(QCoreApplication::translate("ReviewZForm", "+100up", nullptr));
        pushButton100Dn->setText(QCoreApplication::translate("ReviewZForm", "-100dn", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("ReviewZForm", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReviewZForm: public Ui_ReviewZForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVIEWZFORM_H
