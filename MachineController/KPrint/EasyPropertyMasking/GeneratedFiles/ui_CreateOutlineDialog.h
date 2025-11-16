/********************************************************************************
** Form generated from reading UI file 'CreateOutlineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEOUTLINEDIALOG_H
#define UI_CREATEOUTLINEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CreateOutlineDialog
{
public:
    QFrame *frameLibrary;
    QFrame *frame;
    QLabel *label_7;
    QLabel *labelMM2;
    QPushButton *pushButtonGenerate;
    QLabel *label_3;
    QSpinBox *spinBoxInsideDot;
    QLabel *label_6;
    QLabel *labelMM1;
    QSpinBox *spinBoxOutsideDot;
    QDoubleSpinBox *doubleSpinBoxOutsideMM;
    QLabel *label_8;
    QPushButton *pushButtonCancel;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxInsideMM;
    QLabel *label_5;
    QSpinBox *spinBoxExpansion;

    void setupUi(QDialog *CreateOutlineDialog)
    {
        if (CreateOutlineDialog->objectName().isEmpty())
            CreateOutlineDialog->setObjectName("CreateOutlineDialog");
        CreateOutlineDialog->resize(659, 629);
        frameLibrary = new QFrame(CreateOutlineDialog);
        frameLibrary->setObjectName("frameLibrary");
        frameLibrary->setGeometry(QRect(10, 10, 641, 421));
        frameLibrary->setFrameShape(QFrame::StyledPanel);
        frameLibrary->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(CreateOutlineDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 430, 661, 201));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 10, 91, 31));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelMM2 = new QLabel(frame);
        labelMM2->setObjectName("labelMM2");
        labelMM2->setGeometry(QRect(390, 89, 37, 31));
        pushButtonGenerate = new QPushButton(frame);
        pushButtonGenerate->setObjectName("pushButtonGenerate");
        pushButtonGenerate->setGeometry(QRect(110, 139, 141, 51));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 50, 91, 31));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxInsideDot = new QSpinBox(frame);
        spinBoxInsideDot->setObjectName("spinBoxInsideDot");
        spinBoxInsideDot->setGeometry(QRect(170, 49, 81, 31));
        spinBoxInsideDot->setMaximum(1000);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(250, 89, 37, 31));
        labelMM1 = new QLabel(frame);
        labelMM1->setObjectName("labelMM1");
        labelMM1->setGeometry(QRect(390, 49, 37, 31));
        spinBoxOutsideDot = new QSpinBox(frame);
        spinBoxOutsideDot->setObjectName("spinBoxOutsideDot");
        spinBoxOutsideDot->setGeometry(QRect(170, 89, 81, 31));
        spinBoxOutsideDot->setMaximum(1000);
        doubleSpinBoxOutsideMM = new QDoubleSpinBox(frame);
        doubleSpinBoxOutsideMM->setObjectName("doubleSpinBoxOutsideMM");
        doubleSpinBoxOutsideMM->setGeometry(QRect(290, 89, 91, 31));
        doubleSpinBoxOutsideMM->setMaximum(1000.000000000000000);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(250, 9, 37, 31));
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(460, 139, 141, 51));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 89, 91, 31));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxInsideMM = new QDoubleSpinBox(frame);
        doubleSpinBoxInsideMM->setObjectName("doubleSpinBoxInsideMM");
        doubleSpinBoxInsideMM->setGeometry(QRect(290, 49, 91, 31));
        doubleSpinBoxInsideMM->setMaximum(1000.000000000000000);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(250, 49, 37, 31));
        spinBoxExpansion = new QSpinBox(frame);
        spinBoxExpansion->setObjectName("spinBoxExpansion");
        spinBoxExpansion->setGeometry(QRect(170, 9, 81, 31));
        spinBoxExpansion->setMinimum(-1000);
        spinBoxExpansion->setMaximum(1000);

        retranslateUi(CreateOutlineDialog);

        QMetaObject::connectSlotsByName(CreateOutlineDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateOutlineDialog)
    {
        CreateOutlineDialog->setWindowTitle(QCoreApplication::translate("CreateOutlineDialog", "Dialog", nullptr));
        label_7->setText(QCoreApplication::translate("CreateOutlineDialog", "\351\240\230\345\237\237\350\206\250\345\274\265\351\207\217", nullptr));
        labelMM2->setText(QCoreApplication::translate("CreateOutlineDialog", "mm", nullptr));
        pushButtonGenerate->setText(QCoreApplication::translate("CreateOutlineDialog", "\347\224\237\346\210\220", nullptr));
        label_3->setText(QCoreApplication::translate("CreateOutlineDialog", "\350\274\252\351\203\255\345\206\205\345\201\264\343\201\256\345\271\205", nullptr));
        label_6->setText(QCoreApplication::translate("CreateOutlineDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
        labelMM1->setText(QCoreApplication::translate("CreateOutlineDialog", "mm", nullptr));
        label_8->setText(QCoreApplication::translate("CreateOutlineDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateOutlineDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label_4->setText(QCoreApplication::translate("CreateOutlineDialog", "\350\274\252\351\203\255\345\244\226\345\201\264\343\201\256\345\271\205", nullptr));
        label_5->setText(QCoreApplication::translate("CreateOutlineDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateOutlineDialog: public Ui_CreateOutlineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEOUTLINEDIALOG_H
