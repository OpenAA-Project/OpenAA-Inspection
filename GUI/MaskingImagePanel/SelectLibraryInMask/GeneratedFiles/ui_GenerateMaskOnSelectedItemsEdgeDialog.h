/********************************************************************************
** Form generated from reading UI file 'GenerateMaskOnSelectedItemsEdgeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEMASKONSELECTEDITEMSEDGEDIALOG_H
#define UI_GENERATEMASKONSELECTEDITEMSEDGEDIALOG_H

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

class Ui_GenerateMaskOnSelectedItemsEdgeDialog
{
public:
    QFrame *frameLibrary;
    QFrame *frame_2;
    QLabel *label_9;
    QSpinBox *spinBoxOutsideDot_2;
    QLabel *label_10;
    QLabel *labelMM1_2;
    QPushButton *ButtonCancel_2;
    QLabel *label_11;
    QPushButton *ButtonEffective_2;
    QDoubleSpinBox *doubleSpinBoxOutsideMM_2;
    QLabel *labelMM2_2;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBoxInsideMM_2;
    QSpinBox *spinBoxInsideDot_2;
    QPushButton *ButtonNotEffective_2;
    QSpinBox *spinBoxExpansion_2;
    QLabel *label_13;
    QLabel *label_14;
    QFrame *frame;
    QLabel *label_6;
    QSpinBox *spinBoxOutsideDot;
    QLabel *label_3;
    QLabel *labelMM1;
    QPushButton *ButtonCancel;
    QLabel *label_5;
    QPushButton *ButtonEffective;
    QDoubleSpinBox *doubleSpinBoxOutsideMM;
    QLabel *labelMM2;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxInsideMM;
    QSpinBox *spinBoxInsideDot;
    QPushButton *ButtonNotEffective;
    QSpinBox *spinBoxExpansion;
    QLabel *label_7;
    QLabel *label_8;

    void setupUi(QDialog *GenerateMaskOnSelectedItemsEdgeDialog)
    {
        if (GenerateMaskOnSelectedItemsEdgeDialog->objectName().isEmpty())
            GenerateMaskOnSelectedItemsEdgeDialog->setObjectName("GenerateMaskOnSelectedItemsEdgeDialog");
        GenerateMaskOnSelectedItemsEdgeDialog->resize(641, 550);
        frameLibrary = new QFrame(GenerateMaskOnSelectedItemsEdgeDialog);
        frameLibrary->setObjectName("frameLibrary");
        frameLibrary->setGeometry(QRect(0, 0, 641, 421));
        frameLibrary->setFrameShape(QFrame::StyledPanel);
        frameLibrary->setFrameShadow(QFrame::Sunken);
        frame_2 = new QFrame(frameLibrary);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(80, 470, 641, 131));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(190, 90, 37, 31));
        spinBoxOutsideDot_2 = new QSpinBox(frame_2);
        spinBoxOutsideDot_2->setObjectName("spinBoxOutsideDot_2");
        spinBoxOutsideDot_2->setGeometry(QRect(110, 90, 81, 31));
        spinBoxOutsideDot_2->setMaximum(1000);
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 51, 91, 31));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelMM1_2 = new QLabel(frame_2);
        labelMM1_2->setObjectName("labelMM1_2");
        labelMM1_2->setGeometry(QRect(330, 50, 37, 31));
        ButtonCancel_2 = new QPushButton(frame_2);
        ButtonCancel_2->setObjectName("ButtonCancel_2");
        ButtonCancel_2->setGeometry(QRect(530, 10, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel_2->setIcon(icon);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(190, 50, 37, 31));
        ButtonEffective_2 = new QPushButton(frame_2);
        ButtonEffective_2->setObjectName("ButtonEffective_2");
        ButtonEffective_2->setGeometry(QRect(390, 10, 131, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Effect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonEffective_2->setIcon(icon1);
        doubleSpinBoxOutsideMM_2 = new QDoubleSpinBox(frame_2);
        doubleSpinBoxOutsideMM_2->setObjectName("doubleSpinBoxOutsideMM_2");
        doubleSpinBoxOutsideMM_2->setGeometry(QRect(230, 90, 91, 31));
        doubleSpinBoxOutsideMM_2->setMaximum(1000.000000000000000);
        labelMM2_2 = new QLabel(frame_2);
        labelMM2_2->setObjectName("labelMM2_2");
        labelMM2_2->setGeometry(QRect(330, 90, 37, 31));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 90, 91, 31));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxInsideMM_2 = new QDoubleSpinBox(frame_2);
        doubleSpinBoxInsideMM_2->setObjectName("doubleSpinBoxInsideMM_2");
        doubleSpinBoxInsideMM_2->setGeometry(QRect(230, 50, 91, 31));
        doubleSpinBoxInsideMM_2->setMaximum(1000.000000000000000);
        spinBoxInsideDot_2 = new QSpinBox(frame_2);
        spinBoxInsideDot_2->setObjectName("spinBoxInsideDot_2");
        spinBoxInsideDot_2->setGeometry(QRect(110, 50, 81, 31));
        spinBoxInsideDot_2->setMaximum(1000);
        ButtonNotEffective_2 = new QPushButton(frame_2);
        ButtonNotEffective_2->setObjectName("ButtonNotEffective_2");
        ButtonNotEffective_2->setGeometry(QRect(390, 60, 131, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/EffectNG.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonNotEffective_2->setIcon(icon2);
        spinBoxExpansion_2 = new QSpinBox(frame_2);
        spinBoxExpansion_2->setObjectName("spinBoxExpansion_2");
        spinBoxExpansion_2->setGeometry(QRect(110, 10, 81, 31));
        spinBoxExpansion_2->setMinimum(-1000);
        spinBoxExpansion_2->setMaximum(1000);
        label_13 = new QLabel(frame_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 11, 91, 31));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_14 = new QLabel(frame_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(190, 10, 37, 31));
        frame = new QFrame(GenerateMaskOnSelectedItemsEdgeDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 420, 641, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(190, 90, 37, 31));
        spinBoxOutsideDot = new QSpinBox(frame);
        spinBoxOutsideDot->setObjectName("spinBoxOutsideDot");
        spinBoxOutsideDot->setGeometry(QRect(110, 90, 81, 31));
        spinBoxOutsideDot->setMaximum(1000);
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
        ButtonCancel->setIcon(icon);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(190, 50, 37, 31));
        ButtonEffective = new QPushButton(frame);
        ButtonEffective->setObjectName("ButtonEffective");
        ButtonEffective->setGeometry(QRect(390, 10, 131, 41));
        ButtonEffective->setIcon(icon1);
        doubleSpinBoxOutsideMM = new QDoubleSpinBox(frame);
        doubleSpinBoxOutsideMM->setObjectName("doubleSpinBoxOutsideMM");
        doubleSpinBoxOutsideMM->setGeometry(QRect(230, 90, 91, 31));
        doubleSpinBoxOutsideMM->setMaximum(1000.000000000000000);
        labelMM2 = new QLabel(frame);
        labelMM2->setObjectName("labelMM2");
        labelMM2->setGeometry(QRect(330, 90, 37, 31));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 90, 91, 31));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxInsideMM = new QDoubleSpinBox(frame);
        doubleSpinBoxInsideMM->setObjectName("doubleSpinBoxInsideMM");
        doubleSpinBoxInsideMM->setGeometry(QRect(230, 50, 91, 31));
        doubleSpinBoxInsideMM->setMaximum(1000.000000000000000);
        spinBoxInsideDot = new QSpinBox(frame);
        spinBoxInsideDot->setObjectName("spinBoxInsideDot");
        spinBoxInsideDot->setGeometry(QRect(110, 50, 81, 31));
        spinBoxInsideDot->setMaximum(1000);
        ButtonNotEffective = new QPushButton(frame);
        ButtonNotEffective->setObjectName("ButtonNotEffective");
        ButtonNotEffective->setGeometry(QRect(390, 60, 131, 41));
        ButtonNotEffective->setIcon(icon2);
        spinBoxExpansion = new QSpinBox(frame);
        spinBoxExpansion->setObjectName("spinBoxExpansion");
        spinBoxExpansion->setGeometry(QRect(110, 10, 81, 31));
        spinBoxExpansion->setMinimum(-1000);
        spinBoxExpansion->setMaximum(1000);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 11, 91, 31));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(190, 10, 37, 31));

        retranslateUi(GenerateMaskOnSelectedItemsEdgeDialog);

        QMetaObject::connectSlotsByName(GenerateMaskOnSelectedItemsEdgeDialog);
    } // setupUi

    void retranslateUi(QDialog *GenerateMaskOnSelectedItemsEdgeDialog)
    {
        GenerateMaskOnSelectedItemsEdgeDialog->setWindowTitle(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "Dialog", nullptr));
        label_9->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
        label_10->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\350\274\252\351\203\255\345\206\205\345\201\264\343\201\256\345\271\205", nullptr));
        labelMM1_2->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "mm", nullptr));
        ButtonCancel_2->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "Cancel", nullptr));
        label_11->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
        ButtonEffective_2->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "Effective Mask", nullptr));
        labelMM2_2->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "mm", nullptr));
        label_12->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\350\274\252\351\203\255\345\244\226\345\201\264\343\201\256\345\271\205", nullptr));
        ButtonNotEffective_2->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "Not Effective", nullptr));
        label_13->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\351\240\230\345\237\237\350\206\250\345\274\265\351\207\217", nullptr));
        label_14->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
        label_6->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
        label_3->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\350\274\252\351\203\255\345\206\205\345\201\264\343\201\256\345\271\205", nullptr));
        labelMM1->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "mm", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "Cancel", nullptr));
        label_5->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
        ButtonEffective->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "Effective Mask", nullptr));
        labelMM2->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "mm", nullptr));
        label_4->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\350\274\252\351\203\255\345\244\226\345\201\264\343\201\256\345\271\205", nullptr));
        ButtonNotEffective->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "Not Effective", nullptr));
        label_7->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\351\240\230\345\237\237\350\206\250\345\274\265\351\207\217", nullptr));
        label_8->setText(QCoreApplication::translate("GenerateMaskOnSelectedItemsEdgeDialog", "\343\203\211\343\203\203\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerateMaskOnSelectedItemsEdgeDialog: public Ui_GenerateMaskOnSelectedItemsEdgeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEMASKONSELECTEDITEMSEDGEDIALOG_H
