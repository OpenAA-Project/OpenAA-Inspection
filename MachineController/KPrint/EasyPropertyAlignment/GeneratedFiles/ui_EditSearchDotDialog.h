/********************************************************************************
** Form generated from reading UI file 'EditSearchDotDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSEARCHDOTDIALOG_H
#define UI_EDITSEARCHDOTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditSearchDotDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxMoveDotX;
    QSpinBox *spinBoxMoveDotY;
    QDoubleSpinBox *doubleSpinBoxMoveDotXMM;
    QLabel *labelUnit1;
    QLabel *labelUnit2;
    QDoubleSpinBox *doubleSpinBoxMoveDotYMM;
    QLabel *labelUnit4;
    QSpinBox *spinBoxMoveDotY2;
    QLabel *labelUnit3;
    QDoubleSpinBox *doubleSpinBoxMoveDotY2MM;
    QSpinBox *spinBoxMoveDotX2;
    QDoubleSpinBox *doubleSpinBoxMoveDotX2MM;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QCheckBox *checkBoxJudgeWithBrDif;
    QCheckBox *checkBoxCharacterMode;

    void setupUi(QDialog *EditSearchDotDialog)
    {
        if (EditSearchDotDialog->objectName().isEmpty())
            EditSearchDotDialog->setObjectName("EditSearchDotDialog");
        EditSearchDotDialog->resize(400, 329);
        label = new QLabel(EditSearchDotDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 81, 31));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(EditSearchDotDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 110, 81, 31));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(EditSearchDotDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(100, 10, 81, 31));
        label_4 = new QLabel(EditSearchDotDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(250, 10, 91, 31));
        spinBoxMoveDotX = new QSpinBox(EditSearchDotDialog);
        spinBoxMoveDotX->setObjectName("spinBoxMoveDotX");
        spinBoxMoveDotX->setGeometry(QRect(100, 40, 81, 31));
        spinBoxMoveDotX->setMaximum(99999999);
        spinBoxMoveDotY = new QSpinBox(EditSearchDotDialog);
        spinBoxMoveDotY->setObjectName("spinBoxMoveDotY");
        spinBoxMoveDotY->setGeometry(QRect(250, 40, 81, 31));
        spinBoxMoveDotY->setMaximum(99999999);
        doubleSpinBoxMoveDotXMM = new QDoubleSpinBox(EditSearchDotDialog);
        doubleSpinBoxMoveDotXMM->setObjectName("doubleSpinBoxMoveDotXMM");
        doubleSpinBoxMoveDotXMM->setGeometry(QRect(100, 70, 91, 31));
        labelUnit1 = new QLabel(EditSearchDotDialog);
        labelUnit1->setObjectName("labelUnit1");
        labelUnit1->setGeometry(QRect(200, 70, 41, 31));
        labelUnit2 = new QLabel(EditSearchDotDialog);
        labelUnit2->setObjectName("labelUnit2");
        labelUnit2->setGeometry(QRect(350, 70, 41, 31));
        doubleSpinBoxMoveDotYMM = new QDoubleSpinBox(EditSearchDotDialog);
        doubleSpinBoxMoveDotYMM->setObjectName("doubleSpinBoxMoveDotYMM");
        doubleSpinBoxMoveDotYMM->setGeometry(QRect(250, 70, 91, 31));
        labelUnit4 = new QLabel(EditSearchDotDialog);
        labelUnit4->setObjectName("labelUnit4");
        labelUnit4->setGeometry(QRect(350, 140, 41, 31));
        spinBoxMoveDotY2 = new QSpinBox(EditSearchDotDialog);
        spinBoxMoveDotY2->setObjectName("spinBoxMoveDotY2");
        spinBoxMoveDotY2->setGeometry(QRect(250, 110, 81, 31));
        spinBoxMoveDotY2->setMaximum(99999999);
        labelUnit3 = new QLabel(EditSearchDotDialog);
        labelUnit3->setObjectName("labelUnit3");
        labelUnit3->setGeometry(QRect(200, 140, 41, 31));
        doubleSpinBoxMoveDotY2MM = new QDoubleSpinBox(EditSearchDotDialog);
        doubleSpinBoxMoveDotY2MM->setObjectName("doubleSpinBoxMoveDotY2MM");
        doubleSpinBoxMoveDotY2MM->setGeometry(QRect(250, 140, 91, 31));
        spinBoxMoveDotX2 = new QSpinBox(EditSearchDotDialog);
        spinBoxMoveDotX2->setObjectName("spinBoxMoveDotX2");
        spinBoxMoveDotX2->setGeometry(QRect(100, 110, 81, 31));
        spinBoxMoveDotX2->setMaximum(99999999);
        doubleSpinBoxMoveDotX2MM = new QDoubleSpinBox(EditSearchDotDialog);
        doubleSpinBoxMoveDotX2MM->setObjectName("doubleSpinBoxMoveDotX2MM");
        doubleSpinBoxMoveDotX2MM->setGeometry(QRect(100, 140, 91, 31));
        pushButtonOK = new QPushButton(EditSearchDotDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(80, 270, 111, 41));
        pushButtonCancel = new QPushButton(EditSearchDotDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(210, 270, 111, 41));
        checkBoxJudgeWithBrDif = new QCheckBox(EditSearchDotDialog);
        checkBoxJudgeWithBrDif->setObjectName("checkBoxJudgeWithBrDif");
        checkBoxJudgeWithBrDif->setGeometry(QRect(70, 180, 251, 31));
        checkBoxCharacterMode = new QCheckBox(EditSearchDotDialog);
        checkBoxCharacterMode->setObjectName("checkBoxCharacterMode");
        checkBoxCharacterMode->setGeometry(QRect(70, 220, 261, 31));

        retranslateUi(EditSearchDotDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditSearchDotDialog);
    } // setupUi

    void retranslateUi(QDialog *EditSearchDotDialog)
    {
        EditSearchDotDialog->setWindowTitle(QCoreApplication::translate("EditSearchDotDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("EditSearchDotDialog", "\346\216\242\347\264\242\347\257\204\345\233\262\357\274\221", nullptr));
        label_2->setText(QCoreApplication::translate("EditSearchDotDialog", "\346\216\242\347\264\242\347\257\204\345\233\262\357\274\222", nullptr));
        label_3->setText(QCoreApplication::translate("EditSearchDotDialog", "X\346\226\271\345\220\221", nullptr));
        label_4->setText(QCoreApplication::translate("EditSearchDotDialog", "Y\346\226\271\345\220\221", nullptr));
        labelUnit1->setText(QCoreApplication::translate("EditSearchDotDialog", "mm", nullptr));
        labelUnit2->setText(QCoreApplication::translate("EditSearchDotDialog", "mm", nullptr));
        labelUnit4->setText(QCoreApplication::translate("EditSearchDotDialog", "mm", nullptr));
        labelUnit3->setText(QCoreApplication::translate("EditSearchDotDialog", "mm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditSearchDotDialog", "\350\250\255\345\256\232OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditSearchDotDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        checkBoxJudgeWithBrDif->setText(QCoreApplication::translate("EditSearchDotDialog", "\350\211\262\343\201\247\343\203\236\343\203\203\343\203\201\343\203\263\343\202\260", nullptr));
        checkBoxCharacterMode->setText(QCoreApplication::translate("EditSearchDotDialog", "\346\226\207\345\255\227\343\201\247\343\203\236\343\203\203\343\203\201\343\203\263\343\202\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditSearchDotDialog: public Ui_EditSearchDotDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSEARCHDOTDIALOG_H
