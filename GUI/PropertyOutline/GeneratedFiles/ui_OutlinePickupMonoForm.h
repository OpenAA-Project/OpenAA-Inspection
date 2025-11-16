/********************************************************************************
** Form generated from reading UI file 'OutlinePickupMonoForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTLINEPICKUPMONOFORM_H
#define UI_OUTLINEPICKUPMONOFORM_H

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

class Ui_OutlinePickupMonoForm
{
public:
    QPushButton *ButtonReflect;
    QGroupBox *groupBox;
    QRadioButton *radioButtonDarkSide1;
    QRadioButton *radioButtonLightSide1;
    QSpinBox *EditPickupH;
    QSpinBox *EditPickupL;
    QFrame *frameLineGraph;
    QPushButton *ButtonClose;
    QLabel *label_8;
    QLabel *label_7;

    void setupUi(QDialog *OutlinePickupMonoForm)
    {
        if (OutlinePickupMonoForm->objectName().isEmpty())
            OutlinePickupMonoForm->setObjectName("OutlinePickupMonoForm");
        OutlinePickupMonoForm->resize(732, 524);
        ButtonReflect = new QPushButton(OutlinePickupMonoForm);
        ButtonReflect->setObjectName("ButtonReflect");
        ButtonReflect->setGeometry(QRect(530, 430, 171, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Reflection.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonReflect->setIcon(icon);
        groupBox = new QGroupBox(OutlinePickupMonoForm);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(70, 410, 201, 41));
        radioButtonDarkSide1 = new QRadioButton(groupBox);
        radioButtonDarkSide1->setObjectName("radioButtonDarkSide1");
        radioButtonDarkSide1->setGeometry(QRect(10, 8, 81, 22));
        radioButtonDarkSide1->setChecked(true);
        radioButtonLightSide1 = new QRadioButton(groupBox);
        radioButtonLightSide1->setObjectName("radioButtonLightSide1");
        radioButtonLightSide1->setGeometry(QRect(100, 8, 91, 22));
        radioButtonLightSide1->setChecked(false);
        EditPickupH = new QSpinBox(OutlinePickupMonoForm);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(190, 490, 61, 22));
        EditPickupH->setMaximum(500);
        EditPickupL = new QSpinBox(OutlinePickupMonoForm);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(190, 460, 61, 22));
        EditPickupL->setMaximum(255);
        frameLineGraph = new QFrame(OutlinePickupMonoForm);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(10, 10, 711, 381));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        ButtonClose = new QPushButton(OutlinePickupMonoForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(530, 480, 171, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonClose->setIcon(icon1);
        label_8 = new QLabel(OutlinePickupMonoForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 490, 161, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(OutlinePickupMonoForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 460, 161, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(OutlinePickupMonoForm);

        QMetaObject::connectSlotsByName(OutlinePickupMonoForm);
    } // setupUi

    void retranslateUi(QDialog *OutlinePickupMonoForm)
    {
        OutlinePickupMonoForm->setWindowTitle(QCoreApplication::translate("OutlinePickupMonoForm", "Dialog", nullptr));
        ButtonReflect->setText(QCoreApplication::translate("OutlinePickupMonoForm", "\345\217\215\346\230\240", nullptr));
        radioButtonDarkSide1->setText(QCoreApplication::translate("OutlinePickupMonoForm", "Dark", nullptr));
        radioButtonLightSide1->setText(QCoreApplication::translate("OutlinePickupMonoForm", "Light", nullptr));
        ButtonClose->setText(QCoreApplication::translate("OutlinePickupMonoForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_8->setText(QCoreApplication::translate("OutlinePickupMonoForm", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        label_7->setText(QCoreApplication::translate("OutlinePickupMonoForm", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutlinePickupMonoForm: public Ui_OutlinePickupMonoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTLINEPICKUPMONOFORM_H
