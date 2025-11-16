/********************************************************************************
** Form generated from reading UI file 'StatisticBrightHistogramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICBRIGHTHISTOGRAMFORM_H
#define UI_STATISTICBRIGHTHISTOGRAMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_StatisticBrightHistogramFormClass
{
public:
    QPushButton *ButtonClose;
    QSpinBox *EditPickupL;
    QFrame *frameLineGraph;
    QSpinBox *EditPickupH;
    QLabel *label_8;
    QGroupBox *groupBox;
    QRadioButton *radioButtonDarkSide1;
    QRadioButton *radioButtonLightSide1;
    QPushButton *ButtonReflect;
    QLabel *label_7;

    void setupUi(QDialog *StatisticBrightHistogramFormClass)
    {
        if (StatisticBrightHistogramFormClass->objectName().isEmpty())
            StatisticBrightHistogramFormClass->setObjectName("StatisticBrightHistogramFormClass");
        StatisticBrightHistogramFormClass->resize(730, 522);
        ButtonClose = new QPushButton(StatisticBrightHistogramFormClass);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(530, 480, 171, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonClose->setIcon(icon);
        EditPickupL = new QSpinBox(StatisticBrightHistogramFormClass);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(190, 460, 61, 22));
        EditPickupL->setMaximum(255);
        frameLineGraph = new QFrame(StatisticBrightHistogramFormClass);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(10, 10, 711, 381));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        EditPickupH = new QSpinBox(StatisticBrightHistogramFormClass);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(190, 490, 61, 22));
        EditPickupH->setMaximum(255);
        label_8 = new QLabel(StatisticBrightHistogramFormClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(70, 490, 111, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox = new QGroupBox(StatisticBrightHistogramFormClass);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(70, 410, 151, 41));
        radioButtonDarkSide1 = new QRadioButton(groupBox);
        radioButtonDarkSide1->setObjectName("radioButtonDarkSide1");
        radioButtonDarkSide1->setGeometry(QRect(10, 10, 51, 18));
        radioButtonDarkSide1->setChecked(true);
        radioButtonLightSide1 = new QRadioButton(groupBox);
        radioButtonLightSide1->setObjectName("radioButtonLightSide1");
        radioButtonLightSide1->setGeometry(QRect(80, 10, 51, 18));
        radioButtonLightSide1->setChecked(false);
        ButtonReflect = new QPushButton(StatisticBrightHistogramFormClass);
        ButtonReflect->setObjectName("ButtonReflect");
        ButtonReflect->setGeometry(QRect(530, 430, 171, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Reflection.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonReflect->setIcon(icon1);
        label_7 = new QLabel(StatisticBrightHistogramFormClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 460, 111, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(StatisticBrightHistogramFormClass);

        QMetaObject::connectSlotsByName(StatisticBrightHistogramFormClass);
    } // setupUi

    void retranslateUi(QDialog *StatisticBrightHistogramFormClass)
    {
        StatisticBrightHistogramFormClass->setWindowTitle(QCoreApplication::translate("StatisticBrightHistogramFormClass", "StatisticBrightHistogramForm", nullptr));
        ButtonClose->setText(QCoreApplication::translate("StatisticBrightHistogramFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_8->setText(QCoreApplication::translate("StatisticBrightHistogramFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        radioButtonDarkSide1->setText(QCoreApplication::translate("StatisticBrightHistogramFormClass", "Dark", nullptr));
        radioButtonLightSide1->setText(QCoreApplication::translate("StatisticBrightHistogramFormClass", "Light", nullptr));
        ButtonReflect->setText(QCoreApplication::translate("StatisticBrightHistogramFormClass", "\345\217\215\346\230\240", nullptr));
        label_7->setText(QCoreApplication::translate("StatisticBrightHistogramFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatisticBrightHistogramFormClass: public Ui_StatisticBrightHistogramFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICBRIGHTHISTOGRAMFORM_H
