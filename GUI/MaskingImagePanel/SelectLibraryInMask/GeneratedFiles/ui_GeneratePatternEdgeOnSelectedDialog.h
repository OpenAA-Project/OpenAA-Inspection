/********************************************************************************
** Form generated from reading UI file 'GeneratePatternEdgeOnSelectedDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEPATTERNEDGEONSELECTEDDIALOG_H
#define UI_GENERATEPATTERNEDGEONSELECTEDDIALOG_H

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

class Ui_GeneratePatternEdgeOnSelectedDialog
{
public:
    QFrame *frameLibrary;
    QFrame *frame;
    QLabel *label_3;
    QLabel *labelMM1;
    QPushButton *ButtonCancel;
    QLabel *label_5;
    QPushButton *ButtonEffective;
    QDoubleSpinBox *doubleSpinBoxWidthMM;
    QSpinBox *spinBoxWidthDot;
    QPushButton *ButtonNotEffective;
    QLabel *label_9;
    QSpinBox *spinBoxBoundaryDiff;

    void setupUi(QDialog *GeneratePatternEdgeOnSelectedDialog)
    {
        if (GeneratePatternEdgeOnSelectedDialog->objectName().isEmpty())
            GeneratePatternEdgeOnSelectedDialog->setObjectName("GeneratePatternEdgeOnSelectedDialog");
        GeneratePatternEdgeOnSelectedDialog->resize(660, 540);
        frameLibrary = new QFrame(GeneratePatternEdgeOnSelectedDialog);
        frameLibrary->setObjectName("frameLibrary");
        frameLibrary->setGeometry(QRect(10, 10, 641, 421));
        frameLibrary->setFrameShape(QFrame::StyledPanel);
        frameLibrary->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(GeneratePatternEdgeOnSelectedDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 430, 641, 111));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 51, 91, 31));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelMM1 = new QLabel(frame);
        labelMM1->setObjectName("labelMM1");
        labelMM1->setGeometry(QRect(330, 50, 37, 31));
        ButtonCancel = new QPushButton(frame);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(530, 10, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(190, 50, 37, 31));
        ButtonEffective = new QPushButton(frame);
        ButtonEffective->setObjectName("ButtonEffective");
        ButtonEffective->setGeometry(QRect(390, 10, 131, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Effect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonEffective->setIcon(icon1);
        doubleSpinBoxWidthMM = new QDoubleSpinBox(frame);
        doubleSpinBoxWidthMM->setObjectName("doubleSpinBoxWidthMM");
        doubleSpinBoxWidthMM->setGeometry(QRect(230, 50, 91, 31));
        doubleSpinBoxWidthMM->setMaximum(1000.000000000000000);
        spinBoxWidthDot = new QSpinBox(frame);
        spinBoxWidthDot->setObjectName("spinBoxWidthDot");
        spinBoxWidthDot->setGeometry(QRect(110, 50, 81, 31));
        spinBoxWidthDot->setMaximum(1000);
        ButtonNotEffective = new QPushButton(frame);
        ButtonNotEffective->setObjectName("ButtonNotEffective");
        ButtonNotEffective->setGeometry(QRect(390, 60, 131, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/EffectNG.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonNotEffective->setIcon(icon2);
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 11, 91, 31));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxBoundaryDiff = new QSpinBox(frame);
        spinBoxBoundaryDiff->setObjectName("spinBoxBoundaryDiff");
        spinBoxBoundaryDiff->setGeometry(QRect(110, 10, 81, 31));
        spinBoxBoundaryDiff->setMinimum(-1000);
        spinBoxBoundaryDiff->setMaximum(1000);

        retranslateUi(GeneratePatternEdgeOnSelectedDialog);

        QMetaObject::connectSlotsByName(GeneratePatternEdgeOnSelectedDialog);
    } // setupUi

    void retranslateUi(QDialog *GeneratePatternEdgeOnSelectedDialog)
    {
        GeneratePatternEdgeOnSelectedDialog->setWindowTitle(QCoreApplication::translate("GeneratePatternEdgeOnSelectedDialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("GeneratePatternEdgeOnSelectedDialog", "\350\274\252\351\203\255\343\201\256\345\271\205", nullptr));
        labelMM1->setText(QCoreApplication::translate("GeneratePatternEdgeOnSelectedDialog", "mm", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("GeneratePatternEdgeOnSelectedDialog", "Cancel", nullptr));
        label_5->setText(QCoreApplication::translate("GeneratePatternEdgeOnSelectedDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
        ButtonEffective->setText(QCoreApplication::translate("GeneratePatternEdgeOnSelectedDialog", "Effective Mask", nullptr));
        ButtonNotEffective->setText(QCoreApplication::translate("GeneratePatternEdgeOnSelectedDialog", "Not Effective", nullptr));
        label_9->setText(QCoreApplication::translate("GeneratePatternEdgeOnSelectedDialog", "\345\242\203\347\225\214\345\210\206\351\233\242\345\200\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeneratePatternEdgeOnSelectedDialog: public Ui_GeneratePatternEdgeOnSelectedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEPATTERNEDGEONSELECTEDDIALOG_H
