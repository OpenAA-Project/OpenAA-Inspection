/********************************************************************************
** Form generated from reading UI file 'CreateManualItemForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMANUALITEMFORM_H
#define UI_CREATEMANUALITEMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CreateManualItemFormClass
{
public:
    QLabel *label;
    QSpinBox *spinBoxCellSize;
    QDoubleSpinBox *doubleSpinBoxAdoptRate;
    QLabel *label_2;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label_3;
    QCheckBox *checkBoxFixed;
    QLabel *label_4;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxAverage;
    QDoubleSpinBox *doubleSpinBoxSigma;
    QLabel *label_6;

    void setupUi(QDialog *CreateManualItemFormClass)
    {
        if (CreateManualItemFormClass->objectName().isEmpty())
            CreateManualItemFormClass->setObjectName("CreateManualItemFormClass");
        CreateManualItemFormClass->resize(228, 236);
        label = new QLabel(CreateManualItemFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(19, 10, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxCellSize = new QSpinBox(CreateManualItemFormClass);
        spinBoxCellSize->setObjectName("spinBoxCellSize");
        spinBoxCellSize->setGeometry(QRect(110, 10, 81, 22));
        spinBoxCellSize->setMaximum(999999);
        doubleSpinBoxAdoptRate = new QDoubleSpinBox(CreateManualItemFormClass);
        doubleSpinBoxAdoptRate->setObjectName("doubleSpinBoxAdoptRate");
        doubleSpinBoxAdoptRate->setGeometry(QRect(110, 40, 81, 22));
        doubleSpinBoxAdoptRate->setMaximum(100.000000000000000);
        label_2 = new QLabel(CreateManualItemFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 40, 81, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(CreateManualItemFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 200, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(CreateManualItemFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 200, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        label_3 = new QLabel(CreateManualItemFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(201, 40, 20, 20));
        checkBoxFixed = new QCheckBox(CreateManualItemFormClass);
        checkBoxFixed->setObjectName("checkBoxFixed");
        checkBoxFixed->setGeometry(QRect(20, 80, 191, 17));
        label_4 = new QLabel(CreateManualItemFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(21, 170, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(CreateManualItemFormClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 140, 81, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxAverage = new QDoubleSpinBox(CreateManualItemFormClass);
        doubleSpinBoxAverage->setObjectName("doubleSpinBoxAverage");
        doubleSpinBoxAverage->setGeometry(QRect(110, 140, 81, 22));
        doubleSpinBoxAverage->setMaximum(256.000000000000000);
        doubleSpinBoxSigma = new QDoubleSpinBox(CreateManualItemFormClass);
        doubleSpinBoxSigma->setObjectName("doubleSpinBoxSigma");
        doubleSpinBoxSigma->setGeometry(QRect(110, 170, 81, 22));
        doubleSpinBoxSigma->setMaximum(1000.000000000000000);
        label_6 = new QLabel(CreateManualItemFormClass);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 100, 191, 31));

        retranslateUi(CreateManualItemFormClass);

        QMetaObject::connectSlotsByName(CreateManualItemFormClass);
    } // setupUi

    void retranslateUi(QDialog *CreateManualItemFormClass)
    {
        CreateManualItemFormClass->setWindowTitle(QCoreApplication::translate("CreateManualItemFormClass", "CreateManualItemForm", nullptr));
        label->setText(QCoreApplication::translate("CreateManualItemFormClass", "\345\207\246\347\220\206\343\202\265\343\202\244\343\202\272", nullptr));
        label_2->setText(QCoreApplication::translate("CreateManualItemFormClass", "\346\216\241\347\224\250\347\216\207", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CreateManualItemFormClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateManualItemFormClass", "Cancel", nullptr));
        label_3->setText(QCoreApplication::translate("CreateManualItemFormClass", "%", nullptr));
        checkBoxFixed->setText(QCoreApplication::translate("CreateManualItemFormClass", "\345\233\272\345\256\232\345\200\244", nullptr));
        label_4->setText(QCoreApplication::translate("CreateManualItemFormClass", "\345\233\272\345\256\232\345\201\217\345\267\256", nullptr));
        label_5->setText(QCoreApplication::translate("CreateManualItemFormClass", "\345\233\272\345\256\232\345\271\263\345\235\207\345\200\244", nullptr));
        label_6->setText(QCoreApplication::translate("CreateManualItemFormClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\343\203\201\343\202\247\343\203\203\343\202\257\343\201\227\343\201\252\343\201\221\343\202\214\343\201\260\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\256\345\271\263\345\235\207\350\274\235\345\272\246\343\200\201</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">\346\250\231\346\272\226\345\201\217\345\267\256\343\201\253\344\270\200\350\207\264\343\201\231\343\202\213\343\202\210\343\201"
                        "\206\343\201\252\345\244\211\346\217\233\343\201\253\343\201\252\343\202\213</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateManualItemFormClass: public Ui_CreateManualItemFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMANUALITEMFORM_H
