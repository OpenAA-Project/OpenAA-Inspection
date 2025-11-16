/********************************************************************************
** Form generated from reading UI file 'CreatePatternEdgeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEPATTERNEDGEDIALOG_H
#define UI_CREATEPATTERNEDGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CreatePatternEdgeDialog
{
public:
    QFrame *frameLibrary;
    QFrame *frame;
    QPushButton *pushButtonGenerate;
    QPushButton *pushButtonCancel;
    QLabel *label_3;
    QLabel *label_5;
    QSpinBox *spinBoxBoundaryDiff;
    QSpinBox *spinBoxWidthDot;
    QDoubleSpinBox *doubleSpinBoxWidthMM;
    QLabel *labelMM1;
    QLabel *label_9;

    void setupUi(QDialog *CreatePatternEdgeDialog)
    {
        if (CreatePatternEdgeDialog->objectName().isEmpty())
            CreatePatternEdgeDialog->setObjectName("CreatePatternEdgeDialog");
        CreatePatternEdgeDialog->resize(660, 579);
        frameLibrary = new QFrame(CreatePatternEdgeDialog);
        frameLibrary->setObjectName("frameLibrary");
        frameLibrary->setGeometry(QRect(10, 10, 641, 421));
        frameLibrary->setFrameShape(QFrame::StyledPanel);
        frameLibrary->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(CreatePatternEdgeDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 430, 661, 151));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonGenerate = new QPushButton(frame);
        pushButtonGenerate->setObjectName("pushButtonGenerate");
        pushButtonGenerate->setGeometry(QRect(90, 90, 141, 51));
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(440, 90, 141, 51));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 50, 151, 31));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(250, 49, 37, 31));
        spinBoxBoundaryDiff = new QSpinBox(frame);
        spinBoxBoundaryDiff->setObjectName("spinBoxBoundaryDiff");
        spinBoxBoundaryDiff->setGeometry(QRect(170, 9, 81, 31));
        spinBoxBoundaryDiff->setMinimum(-1000);
        spinBoxBoundaryDiff->setMaximum(1000);
        spinBoxWidthDot = new QSpinBox(frame);
        spinBoxWidthDot->setObjectName("spinBoxWidthDot");
        spinBoxWidthDot->setGeometry(QRect(170, 49, 81, 31));
        spinBoxWidthDot->setMaximum(1000);
        doubleSpinBoxWidthMM = new QDoubleSpinBox(frame);
        doubleSpinBoxWidthMM->setObjectName("doubleSpinBoxWidthMM");
        doubleSpinBoxWidthMM->setGeometry(QRect(290, 49, 91, 31));
        doubleSpinBoxWidthMM->setMaximum(1000.000000000000000);
        labelMM1 = new QLabel(frame);
        labelMM1->setObjectName("labelMM1");
        labelMM1->setGeometry(QRect(390, 49, 37, 31));
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 10, 151, 31));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(CreatePatternEdgeDialog);

        QMetaObject::connectSlotsByName(CreatePatternEdgeDialog);
    } // setupUi

    void retranslateUi(QDialog *CreatePatternEdgeDialog)
    {
        CreatePatternEdgeDialog->setWindowTitle(QCoreApplication::translate("CreatePatternEdgeDialog", "Dialog", nullptr));
        pushButtonGenerate->setText(QCoreApplication::translate("CreatePatternEdgeDialog", "\347\224\237\346\210\220", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreatePatternEdgeDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label_3->setText(QCoreApplication::translate("CreatePatternEdgeDialog", "\350\274\252\351\203\255\343\201\256\345\271\205", nullptr));
        label_5->setText(QCoreApplication::translate("CreatePatternEdgeDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
        labelMM1->setText(QCoreApplication::translate("CreatePatternEdgeDialog", "mm", nullptr));
        label_9->setText(QCoreApplication::translate("CreatePatternEdgeDialog", "\345\242\203\347\225\214\345\210\206\351\233\242\345\200\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreatePatternEdgeDialog: public Ui_CreatePatternEdgeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPATTERNEDGEDIALOG_H
