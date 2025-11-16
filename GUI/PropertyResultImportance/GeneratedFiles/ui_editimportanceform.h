/********************************************************************************
** Form generated from reading UI file 'editimportanceform.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITIMPORTANCEFORM_H
#define UI_EDITIMPORTANCEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditImportanceForm
{
public:
    QPushButton *pushButtonCancel;
    QGroupBox *groupBox;
    QRadioButton *radioButtonVeryHigh;
    QRadioButton *radioButtonHigh;
    QRadioButton *radioButtonNormal;
    QRadioButton *radioButtonNotSoHigh;
    QPushButton *pushButtonOK;
    QGroupBox *groupBox_2;
    QSpinBox *spinBoxLevel;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonOKLevel;

    void setupUi(QDialog *EditImportanceForm)
    {
        if (EditImportanceForm->objectName().isEmpty())
            EditImportanceForm->setObjectName("EditImportanceForm");
        EditImportanceForm->resize(352, 196);
        pushButtonCancel = new QPushButton(EditImportanceForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 160, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        groupBox = new QGroupBox(EditImportanceForm);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 171, 151));
        radioButtonVeryHigh = new QRadioButton(groupBox);
        radioButtonVeryHigh->setObjectName("radioButtonVeryHigh");
        radioButtonVeryHigh->setGeometry(QRect(10, 17, 121, 20));
        radioButtonHigh = new QRadioButton(groupBox);
        radioButtonHigh->setObjectName("radioButtonHigh");
        radioButtonHigh->setGeometry(QRect(10, 37, 121, 20));
        radioButtonNormal = new QRadioButton(groupBox);
        radioButtonNormal->setObjectName("radioButtonNormal");
        radioButtonNormal->setGeometry(QRect(10, 57, 121, 20));
        radioButtonNormal->setChecked(true);
        radioButtonNotSoHigh = new QRadioButton(groupBox);
        radioButtonNotSoHigh->setObjectName("radioButtonNotSoHigh");
        radioButtonNotSoHigh->setGeometry(QRect(10, 77, 121, 20));
        pushButtonOK = new QPushButton(groupBox);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(40, 110, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        groupBox_2 = new QGroupBox(EditImportanceForm);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(190, 0, 151, 151));
        spinBoxLevel = new QSpinBox(groupBox_2);
        spinBoxLevel->setObjectName("spinBoxLevel");
        spinBoxLevel->setGeometry(QRect(40, 40, 71, 22));
        spinBoxLevel->setMaximum(255);
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 12, 131, 20));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 70, 131, 16));
        pushButtonOKLevel = new QPushButton(groupBox_2);
        pushButtonOKLevel->setObjectName("pushButtonOKLevel");
        pushButtonOKLevel->setGeometry(QRect(30, 110, 91, 31));
        pushButtonOKLevel->setIcon(icon1);

        retranslateUi(EditImportanceForm);

        pushButtonOK->setDefault(true);
        pushButtonOKLevel->setDefault(false);


        QMetaObject::connectSlotsByName(EditImportanceForm);
    } // setupUi

    void retranslateUi(QDialog *EditImportanceForm)
    {
        EditImportanceForm->setWindowTitle(QCoreApplication::translate("EditImportanceForm", "Edit Importance", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditImportanceForm", "Cancel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("EditImportanceForm", "Importance", nullptr));
        radioButtonVeryHigh->setText(QCoreApplication::translate("EditImportanceForm", "Very high (10)", nullptr));
        radioButtonHigh->setText(QCoreApplication::translate("EditImportanceForm", "High(50)", nullptr));
        radioButtonNormal->setText(QCoreApplication::translate("EditImportanceForm", "Normal (100)", nullptr));
        radioButtonNotSoHigh->setText(QCoreApplication::translate("EditImportanceForm", "Not so high (200)", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditImportanceForm", "OK", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("EditImportanceForm", "Level", nullptr));
        label->setText(QCoreApplication::translate("EditImportanceForm", "Importance level", nullptr));
        label_2->setText(QCoreApplication::translate("EditImportanceForm", "Smaller number is higher", nullptr));
        pushButtonOKLevel->setText(QCoreApplication::translate("EditImportanceForm", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditImportanceForm: public Ui_EditImportanceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITIMPORTANCEFORM_H
