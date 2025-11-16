/********************************************************************************
** Form generated from reading UI file 'SettingParamDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGPARAMDIALOG_H
#define UI_SETTINGPARAMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SettingParamDialog
{
public:
    QSpinBox *spinBoxYLen;
    QSpinBox *spinBoxXLen;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButtonOK;
    QLineEdit *lineEditRegPackFileName;
    QPushButton *pushButtonSelectFile;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxMinMatchRate;
    QFrame *frame;
    QToolButton *toolButtonLayer0;
    QToolButton *toolButtonLayer1;
    QToolButton *toolButtonLayer2;
    QLabel *label_5;

    void setupUi(QDialog *SettingParamDialog)
    {
        if (SettingParamDialog->objectName().isEmpty())
            SettingParamDialog->setObjectName("SettingParamDialog");
        SettingParamDialog->resize(369, 261);
        spinBoxYLen = new QSpinBox(SettingParamDialog);
        spinBoxYLen->setObjectName("spinBoxYLen");
        spinBoxYLen->setGeometry(QRect(250, 40, 101, 24));
        spinBoxYLen->setMaximum(10000);
        spinBoxXLen = new QSpinBox(SettingParamDialog);
        spinBoxXLen->setObjectName("spinBoxXLen");
        spinBoxXLen->setGeometry(QRect(250, 10, 101, 24));
        spinBoxXLen->setMaximum(10000);
        pushButtonCancel = new QPushButton(SettingParamDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(210, 220, 112, 34));
        label = new QLabel(SettingParamDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 231, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(SettingParamDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 231, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(SettingParamDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 231, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        pushButtonOK = new QPushButton(SettingParamDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 220, 112, 34));
        lineEditRegPackFileName = new QLineEdit(SettingParamDialog);
        lineEditRegPackFileName->setObjectName("lineEditRegPackFileName");
        lineEditRegPackFileName->setGeometry(QRect(60, 90, 241, 31));
        pushButtonSelectFile = new QPushButton(SettingParamDialog);
        pushButtonSelectFile->setObjectName("pushButtonSelectFile");
        pushButtonSelectFile->setGeometry(QRect(310, 90, 41, 34));
        label_4 = new QLabel(SettingParamDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 130, 231, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxMinMatchRate = new QDoubleSpinBox(SettingParamDialog);
        doubleSpinBoxMinMatchRate->setObjectName("doubleSpinBoxMinMatchRate");
        doubleSpinBoxMinMatchRate->setGeometry(QRect(250, 130, 101, 24));
        doubleSpinBoxMinMatchRate->setDecimals(5);
        doubleSpinBoxMinMatchRate->setMinimum(-1.000000000000000);
        doubleSpinBoxMinMatchRate->setMaximum(1.000000000000000);
        frame = new QFrame(SettingParamDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 180, 331, 31));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonLayer0 = new QToolButton(frame);
        toolButtonLayer0->setObjectName("toolButtonLayer0");
        toolButtonLayer0->setGeometry(QRect(0, 0, 71, 21));
        toolButtonLayer0->setCheckable(true);
        toolButtonLayer1 = new QToolButton(frame);
        toolButtonLayer1->setObjectName("toolButtonLayer1");
        toolButtonLayer1->setGeometry(QRect(80, 0, 71, 21));
        toolButtonLayer1->setCheckable(true);
        toolButtonLayer2 = new QToolButton(frame);
        toolButtonLayer2->setObjectName("toolButtonLayer2");
        toolButtonLayer2->setGeometry(QRect(160, 0, 71, 21));
        toolButtonLayer2->setCheckable(true);
        label_5 = new QLabel(SettingParamDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 160, 331, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);

        retranslateUi(SettingParamDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SettingParamDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingParamDialog)
    {
        SettingParamDialog->setWindowTitle(QCoreApplication::translate("SettingParamDialog", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SettingParamDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingParamDialog", "\350\251\225\344\276\241\343\201\231\343\202\213\351\240\230\345\237\237\343\201\256X\346\226\271\345\220\221\343\202\265\343\202\244\343\202\272", nullptr));
        label_2->setText(QCoreApplication::translate("SettingParamDialog", "\350\251\225\344\276\241\343\201\231\343\202\213\351\240\230\345\237\237\343\201\256X\346\226\271\345\220\221\343\202\265\343\202\244\343\202\272", nullptr));
        label_3->setText(QCoreApplication::translate("SettingParamDialog", "\347\231\273\351\214\262\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\225\343\202\241\343\202\244\343\203\253\345\220\215", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SettingParamDialog", "OK", nullptr));
        pushButtonSelectFile->setText(QCoreApplication::translate("SettingParamDialog", "...", nullptr));
        label_4->setText(QCoreApplication::translate("SettingParamDialog", "\345\210\244\345\256\232\346\261\272\345\256\232\346\231\202\343\201\256\346\234\200\344\275\216\351\201\251\345\220\210\347\216\207", nullptr));
        toolButtonLayer0->setText(QCoreApplication::translate("SettingParamDialog", "LY0", nullptr));
        toolButtonLayer1->setText(QCoreApplication::translate("SettingParamDialog", "LY1", nullptr));
        toolButtonLayer2->setText(QCoreApplication::translate("SettingParamDialog", "LY2", nullptr));
        label_5->setText(QCoreApplication::translate("SettingParamDialog", "\344\275\277\347\224\250\343\201\231\343\202\213\343\203\254\343\202\244\343\203\244\343\203\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingParamDialog: public Ui_SettingParamDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGPARAMDIALOG_H
