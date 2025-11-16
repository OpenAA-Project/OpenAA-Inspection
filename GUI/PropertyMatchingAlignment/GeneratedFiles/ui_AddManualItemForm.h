/********************************************************************************
** Form generated from reading UI file 'AddManualItemForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDMANUALITEMFORM_H
#define UI_ADDMANUALITEMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddManualItemFormClass
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxMatchingRate;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxSearchDot;

    void setupUi(QDialog *AddManualItemFormClass)
    {
        if (AddManualItemFormClass->objectName().isEmpty())
            AddManualItemFormClass->setObjectName("AddManualItemFormClass");
        AddManualItemFormClass->resize(210, 215);
        pushButtonOK = new QPushButton(AddManualItemFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 160, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(AddManualItemFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 160, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label = new QLabel(AddManualItemFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 141, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxMatchingRate = new QDoubleSpinBox(AddManualItemFormClass);
        doubleSpinBoxMatchingRate->setObjectName("doubleSpinBoxMatchingRate");
        doubleSpinBoxMatchingRate->setGeometry(QRect(30, 30, 141, 22));
        doubleSpinBoxMatchingRate->setMaximum(100.000000000000000);
        label_2 = new QLabel(AddManualItemFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 191, 31));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(AddManualItemFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 100, 141, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxSearchDot = new QSpinBox(AddManualItemFormClass);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(30, 120, 81, 22));

        retranslateUi(AddManualItemFormClass);

        QMetaObject::connectSlotsByName(AddManualItemFormClass);
    } // setupUi

    void retranslateUi(QDialog *AddManualItemFormClass)
    {
        AddManualItemFormClass->setWindowTitle(QCoreApplication::translate("AddManualItemFormClass", "AddManualItemForm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddManualItemFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddManualItemFormClass", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("AddManualItemFormClass", "\351\201\251\345\220\210\347\216\207", nullptr));
        label_2->setText(QCoreApplication::translate("AddManualItemFormClass", "\343\201\223\343\201\256\351\201\251\345\220\210\347\216\207\344\273\245\344\270\212\343\201\256\347\256\207\346\211\200\343\201\253\345\220\210\350\207\264\343\201\231\343\202\213", nullptr));
        label_3->setText(QCoreApplication::translate("AddManualItemFormClass", "\351\203\250\345\210\206\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddManualItemFormClass: public Ui_AddManualItemFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDMANUALITEMFORM_H
