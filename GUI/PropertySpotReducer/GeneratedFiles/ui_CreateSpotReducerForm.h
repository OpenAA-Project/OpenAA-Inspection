/********************************************************************************
** Form generated from reading UI file 'CreateSpotReducerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATESPOTREDUCERFORM_H
#define UI_CREATESPOTREDUCERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CreateSpotReducerFormClass
{
public:
    QLabel *label;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxSpotBrightness;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxReductionLevel;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxSpotArea;
    QSpinBox *spinBoxSpotCount;

    void setupUi(QDialog *CreateSpotReducerFormClass)
    {
        if (CreateSpotReducerFormClass->objectName().isEmpty())
            CreateSpotReducerFormClass->setObjectName("CreateSpotReducerFormClass");
        CreateSpotReducerFormClass->resize(184, 249);
        label = new QLabel(CreateSpotReducerFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 10, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(CreateSpotReducerFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 210, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(CreateSpotReducerFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(100, 210, 75, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        spinBoxSpotBrightness = new QSpinBox(CreateSpotReducerFormClass);
        spinBoxSpotBrightness->setObjectName("spinBoxSpotBrightness");
        spinBoxSpotBrightness->setGeometry(QRect(50, 30, 81, 22));
        spinBoxSpotBrightness->setMaximum(256);
        label_2 = new QLabel(CreateSpotReducerFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 60, 81, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxReductionLevel = new QDoubleSpinBox(CreateSpotReducerFormClass);
        doubleSpinBoxReductionLevel->setObjectName("doubleSpinBoxReductionLevel");
        doubleSpinBoxReductionLevel->setGeometry(QRect(50, 80, 81, 22));
        doubleSpinBoxReductionLevel->setDecimals(1);
        doubleSpinBoxReductionLevel->setMaximum(9999.899999999999636);
        doubleSpinBoxReductionLevel->setValue(50.000000000000000);
        label_3 = new QLabel(CreateSpotReducerFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 110, 81, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(CreateSpotReducerFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 160, 81, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxSpotArea = new QSpinBox(CreateSpotReducerFormClass);
        spinBoxSpotArea->setObjectName("spinBoxSpotArea");
        spinBoxSpotArea->setGeometry(QRect(50, 130, 81, 22));
        spinBoxSpotArea->setMaximum(256);
        spinBoxSpotCount = new QSpinBox(CreateSpotReducerFormClass);
        spinBoxSpotCount->setObjectName("spinBoxSpotCount");
        spinBoxSpotCount->setGeometry(QRect(50, 180, 81, 22));
        spinBoxSpotCount->setMaximum(256);

        retranslateUi(CreateSpotReducerFormClass);

        QMetaObject::connectSlotsByName(CreateSpotReducerFormClass);
    } // setupUi

    void retranslateUi(QDialog *CreateSpotReducerFormClass)
    {
        CreateSpotReducerFormClass->setWindowTitle(QCoreApplication::translate("CreateSpotReducerFormClass", "CreateSpotReducerForm", nullptr));
        label->setText(QCoreApplication::translate("CreateSpotReducerFormClass", "\345\237\272\347\202\271\343\201\256\350\274\235\345\272\246", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CreateSpotReducerFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateSpotReducerFormClass", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("CreateSpotReducerFormClass", "\350\274\235\347\202\271\347\267\251\345\222\214\345\274\267\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("CreateSpotReducerFormClass", "\346\216\242\347\264\242\347\257\204\345\233\262", nullptr));
        label_4->setText(QCoreApplication::translate("CreateSpotReducerFormClass", "\350\274\235\347\202\271\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateSpotReducerFormClass: public Ui_CreateSpotReducerFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATESPOTREDUCERFORM_H
