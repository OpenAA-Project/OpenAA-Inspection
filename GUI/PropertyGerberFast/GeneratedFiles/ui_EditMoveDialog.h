/********************************************************************************
** Form generated from reading UI file 'EditMoveDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMOVEDIALOG_H
#define UI_EDITMOVEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_EditMoveDialog
{
public:
    QGroupBox *groupBox;
    QRadioButton *radioButtonPixel;
    QRadioButton *radioButtonMilimeter;
    QDoubleSpinBox *doubleSpinBoxXDir;
    QDoubleSpinBox *doubleSpinBoxYDir;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditMoveDialog)
    {
        if (EditMoveDialog->objectName().isEmpty())
            EditMoveDialog->setObjectName("EditMoveDialog");
        EditMoveDialog->resize(220, 245);
        groupBox = new QGroupBox(EditMoveDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 201, 65));
        radioButtonPixel = new QRadioButton(groupBox);
        radioButtonPixel->setObjectName("radioButtonPixel");
        radioButtonPixel->setGeometry(QRect(10, 10, 181, 20));
        radioButtonPixel->setChecked(true);
        radioButtonMilimeter = new QRadioButton(groupBox);
        radioButtonMilimeter->setObjectName("radioButtonMilimeter");
        radioButtonMilimeter->setGeometry(QRect(10, 36, 181, 20));
        doubleSpinBoxXDir = new QDoubleSpinBox(EditMoveDialog);
        doubleSpinBoxXDir->setObjectName("doubleSpinBoxXDir");
        doubleSpinBoxXDir->setGeometry(QRect(20, 110, 91, 21));
        doubleSpinBoxXDir->setDecimals(3);
        doubleSpinBoxXDir->setMinimum(-99999999.000000000000000);
        doubleSpinBoxXDir->setMaximum(99999999.000000000000000);
        doubleSpinBoxYDir = new QDoubleSpinBox(EditMoveDialog);
        doubleSpinBoxYDir->setObjectName("doubleSpinBoxYDir");
        doubleSpinBoxYDir->setGeometry(QRect(120, 110, 91, 21));
        doubleSpinBoxYDir->setDecimals(3);
        doubleSpinBoxYDir->setMinimum(-99999999.000000000000000);
        doubleSpinBoxYDir->setMaximum(99999999.000000000000000);
        label = new QLabel(EditMoveDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 90, 89, 16));
        label_2 = new QLabel(EditMoveDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 90, 89, 16));
        label_3 = new QLabel(EditMoveDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 140, 84, 14));
        label_4 = new QLabel(EditMoveDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 160, 84, 14));
        label_5 = new QLabel(EditMoveDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(124, 140, 84, 14));
        label_6 = new QLabel(EditMoveDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(124, 160, 84, 14));
        pushButtonOK = new QPushButton(EditMoveDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 190, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(EditMoveDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 190, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(EditMoveDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditMoveDialog);
    } // setupUi

    void retranslateUi(QDialog *EditMoveDialog)
    {
        EditMoveDialog->setWindowTitle(QCoreApplication::translate("EditMoveDialog", "Move Gerber", nullptr));
        groupBox->setTitle(QString());
        radioButtonPixel->setText(QCoreApplication::translate("EditMoveDialog", "Pixel", nullptr));
        radioButtonMilimeter->setText(QCoreApplication::translate("EditMoveDialog", "Milimeter", nullptr));
        label->setText(QCoreApplication::translate("EditMoveDialog", "X direction", nullptr));
        label_2->setText(QCoreApplication::translate("EditMoveDialog", "Y direction", nullptr));
        label_3->setText(QCoreApplication::translate("EditMoveDialog", "- : Left", nullptr));
        label_4->setText(QCoreApplication::translate("EditMoveDialog", "+ : Right", nullptr));
        label_5->setText(QCoreApplication::translate("EditMoveDialog", "- : Upper", nullptr));
        label_6->setText(QCoreApplication::translate("EditMoveDialog", "+ : Lower", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditMoveDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditMoveDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditMoveDialog: public Ui_EditMoveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMOVEDIALOG_H
