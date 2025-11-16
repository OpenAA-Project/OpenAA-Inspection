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
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddManualItemFormClass
{
public:
    QFrame *frameCurrentItem;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QLabel *label;
    QSpinBox *spinBoxEnsmall;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxEnlarge;
    QPushButton *pushButtonSetMergin;
    QSpinBox *spinBoxMergin;
    QLabel *label_4;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *AddManualItemFormClass)
    {
        if (AddManualItemFormClass->objectName().isEmpty())
            AddManualItemFormClass->setObjectName("AddManualItemFormClass");
        AddManualItemFormClass->resize(638, 529);
        frameCurrentItem = new QFrame(AddManualItemFormClass);
        frameCurrentItem->setObjectName("frameCurrentItem");
        frameCurrentItem->setGeometry(QRect(10, 10, 391, 321));
        frameCurrentItem->setFrameShape(QFrame::StyledPanel);
        frameCurrentItem->setFrameShadow(QFrame::Sunken);
        frameColorSample = new QFrame(AddManualItemFormClass);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(420, 10, 205, 511));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(10, 480, 181, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(10, 450, 181, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon1);
        label = new QLabel(AddManualItemFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(39, 340, 241, 16));
        spinBoxEnsmall = new QSpinBox(AddManualItemFormClass);
        spinBoxEnsmall->setObjectName("spinBoxEnsmall");
        spinBoxEnsmall->setGeometry(QRect(140, 420, 61, 22));
        label_2 = new QLabel(AddManualItemFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 420, 101, 16));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(AddManualItemFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 450, 101, 16));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxEnlarge = new QSpinBox(AddManualItemFormClass);
        spinBoxEnlarge->setObjectName("spinBoxEnlarge");
        spinBoxEnlarge->setGeometry(QRect(140, 450, 61, 22));
        pushButtonSetMergin = new QPushButton(AddManualItemFormClass);
        pushButtonSetMergin->setObjectName("pushButtonSetMergin");
        pushButtonSetMergin->setGeometry(QRect(240, 360, 171, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetMergin->setIcon(icon2);
        spinBoxMergin = new QSpinBox(AddManualItemFormClass);
        spinBoxMergin->setObjectName("spinBoxMergin");
        spinBoxMergin->setGeometry(QRect(140, 380, 61, 22));
        label_4 = new QLabel(AddManualItemFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(130, 360, 101, 16));
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(AddManualItemFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(90, 480, 121, 41));
        pushButtonOK->setIcon(icon2);
        pushButtonCancel = new QPushButton(AddManualItemFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(270, 480, 111, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon3);
        QWidget::setTabOrder(spinBoxMergin, spinBoxEnsmall);
        QWidget::setTabOrder(spinBoxEnsmall, spinBoxEnlarge);
        QWidget::setTabOrder(spinBoxEnlarge, pushButtonSetMergin);
        QWidget::setTabOrder(pushButtonSetMergin, pushButtonOK);
        QWidget::setTabOrder(pushButtonOK, pushButtonCancel);
        QWidget::setTabOrder(pushButtonCancel, pushButtonAddColor);
        QWidget::setTabOrder(pushButtonAddColor, pushButtonEliminateColor);

        retranslateUi(AddManualItemFormClass);

        QMetaObject::connectSlotsByName(AddManualItemFormClass);
    } // setupUi

    void retranslateUi(QDialog *AddManualItemFormClass)
    {
        AddManualItemFormClass->setWindowTitle(QCoreApplication::translate("AddManualItemFormClass", "AddManualItemForm", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("AddManualItemFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("AddManualItemFormClass", "Add Color", nullptr));
        label->setText(QCoreApplication::translate("AddManualItemFormClass", "\343\201\223\343\201\256\350\274\235\345\272\246\347\257\204\345\233\262\343\201\214\343\203\236\343\202\271\343\202\257\343\201\225\343\202\214\343\202\213", nullptr));
        label_2->setText(QCoreApplication::translate("AddManualItemFormClass", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("AddManualItemFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        pushButtonSetMergin->setText(QCoreApplication::translate("AddManualItemFormClass", "\343\201\223\343\201\256\343\203\236\343\203\274\343\202\270\343\203\263\343\202\222\350\250\255\345\256\232", nullptr));
        label_4->setText(QCoreApplication::translate("AddManualItemFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddManualItemFormClass", "\350\250\255\345\256\232", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddManualItemFormClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddManualItemFormClass: public Ui_AddManualItemFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDMANUALITEMFORM_H
