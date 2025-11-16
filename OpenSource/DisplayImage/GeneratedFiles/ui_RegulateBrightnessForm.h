/********************************************************************************
** Form generated from reading UI file 'RegulateBrightnessForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGULATEBRIGHTNESSFORM_H
#define UI_REGULATEBRIGHTNESSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RegulateBrightnessForm
{
public:
    QFrame *frameLayer;
    QFrame *frameBase;
    QSpinBox *spinBoxBlockSize;
    QDoubleSpinBox *doubleSpinBoxAverage;
    QDoubleSpinBox *doubleSpinBoxDeviation;
    QPushButton *pushButtonCancel;
    QLabel *label_3;
    QPushButton *pushButtonOk;
    QLabel *label_2;
    QLabel *label;
    QFrame *frameGraph;

    void setupUi(QDialog *RegulateBrightnessForm)
    {
        if (RegulateBrightnessForm->objectName().isEmpty())
            RegulateBrightnessForm->setObjectName("RegulateBrightnessForm");
        RegulateBrightnessForm->resize(631, 372);
        frameLayer = new QFrame(RegulateBrightnessForm);
        frameLayer->setObjectName("frameLayer");
        frameLayer->setGeometry(QRect(0, 0, 531, 31));
        frameLayer->setFrameShape(QFrame::NoFrame);
        frameLayer->setFrameShadow(QFrame::Raised);
        frameBase = new QFrame(RegulateBrightnessForm);
        frameBase->setObjectName("frameBase");
        frameBase->setGeometry(QRect(0, 30, 631, 341));
        frameBase->setFrameShape(QFrame::StyledPanel);
        frameBase->setFrameShadow(QFrame::Sunken);
        spinBoxBlockSize = new QSpinBox(frameBase);
        spinBoxBlockSize->setObjectName("spinBoxBlockSize");
        spinBoxBlockSize->setGeometry(QRect(360, 270, 81, 22));
        spinBoxBlockSize->setMaximum(99999999);
        spinBoxBlockSize->setValue(100);
        doubleSpinBoxAverage = new QDoubleSpinBox(frameBase);
        doubleSpinBoxAverage->setObjectName("doubleSpinBoxAverage");
        doubleSpinBoxAverage->setGeometry(QRect(170, 270, 81, 22));
        doubleSpinBoxAverage->setMaximum(255.990000000000009);
        doubleSpinBoxAverage->setValue(100.000000000000000);
        doubleSpinBoxDeviation = new QDoubleSpinBox(frameBase);
        doubleSpinBoxDeviation->setObjectName("doubleSpinBoxDeviation");
        doubleSpinBoxDeviation->setGeometry(QRect(260, 270, 81, 22));
        doubleSpinBoxDeviation->setDecimals(3);
        doubleSpinBoxDeviation->setMaximum(99999.998999999996158);
        doubleSpinBoxDeviation->setValue(10.000000000000000);
        pushButtonCancel = new QPushButton(frameBase);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(330, 300, 151, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        label_3 = new QLabel(frameBase);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(360, 250, 81, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOk = new QPushButton(frameBase);
        pushButtonOk->setObjectName("pushButtonOk");
        pushButtonOk->setGeometry(QRect(130, 300, 171, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOk->setIcon(icon1);
        label_2 = new QLabel(frameBase);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 250, 81, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frameBase);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 250, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameGraph = new QFrame(frameBase);
        frameGraph->setObjectName("frameGraph");
        frameGraph->setGeometry(QRect(10, 10, 611, 231));
        frameGraph->setFrameShape(QFrame::NoFrame);
        frameGraph->setFrameShadow(QFrame::Plain);

        retranslateUi(RegulateBrightnessForm);

        QMetaObject::connectSlotsByName(RegulateBrightnessForm);
    } // setupUi

    void retranslateUi(QDialog *RegulateBrightnessForm)
    {
        RegulateBrightnessForm->setWindowTitle(QCoreApplication::translate("RegulateBrightnessForm", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RegulateBrightnessForm", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label_3->setText(QCoreApplication::translate("RegulateBrightnessForm", "\343\203\226\343\203\255\343\203\203\343\202\257\343\202\265\343\202\244\343\202\272", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("RegulateBrightnessForm", "\343\201\223\343\201\256\345\200\244\343\201\253\346\255\243\350\246\217\345\214\226", nullptr));
        label_2->setText(QCoreApplication::translate("RegulateBrightnessForm", "\346\250\231\346\272\226\345\201\217\345\267\256", nullptr));
        label->setText(QCoreApplication::translate("RegulateBrightnessForm", "\345\271\263\345\235\207\350\274\235\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegulateBrightnessForm: public Ui_RegulateBrightnessForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGULATEBRIGHTNESSFORM_H
