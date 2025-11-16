/********************************************************************************
** Form generated from reading UI file 'EditShearDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSHEARDIALOG_H
#define UI_EDITSHEARDIALOG_H

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

class Ui_EditShearDialog
{
public:
    QPushButton *pushButtonOK;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxShear;
    QPushButton *pushButtonCancel;
    QGroupBox *groupBox;
    QRadioButton *radioButtonXDir;
    QRadioButton *radioButtonYDir;

    void setupUi(QDialog *EditShearDialog)
    {
        if (EditShearDialog->objectName().isEmpty())
            EditShearDialog->setObjectName("EditShearDialog");
        EditShearDialog->resize(209, 174);
        pushButtonOK = new QPushButton(EditShearDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 120, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        label = new QLabel(EditShearDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 60, 151, 16));
        doubleSpinBoxShear = new QDoubleSpinBox(EditShearDialog);
        doubleSpinBoxShear->setObjectName("doubleSpinBoxShear");
        doubleSpinBoxShear->setGeometry(QRect(60, 80, 91, 21));
        doubleSpinBoxShear->setDecimals(3);
        doubleSpinBoxShear->setMinimum(0.000000000000000);
        doubleSpinBoxShear->setMaximum(360.000000000000000);
        pushButtonCancel = new QPushButton(EditShearDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 120, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        groupBox = new QGroupBox(EditShearDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 191, 41));
        radioButtonXDir = new QRadioButton(groupBox);
        radioButtonXDir->setObjectName("radioButtonXDir");
        radioButtonXDir->setGeometry(QRect(10, 10, 81, 20));
        radioButtonXDir->setChecked(true);
        radioButtonYDir = new QRadioButton(groupBox);
        radioButtonYDir->setObjectName("radioButtonYDir");
        radioButtonYDir->setGeometry(QRect(100, 10, 81, 20));

        retranslateUi(EditShearDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditShearDialog);
    } // setupUi

    void retranslateUi(QDialog *EditShearDialog)
    {
        EditShearDialog->setWindowTitle(QCoreApplication::translate("EditShearDialog", "Shear gerber", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditShearDialog", "OK", nullptr));
        label->setText(QCoreApplication::translate("EditShearDialog", "Rotated degree", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditShearDialog", "Cancel", nullptr));
        groupBox->setTitle(QString());
        radioButtonXDir->setText(QCoreApplication::translate("EditShearDialog", "X dir", nullptr));
        radioButtonYDir->setText(QCoreApplication::translate("EditShearDialog", "Y dir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditShearDialog: public Ui_EditShearDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSHEARDIALOG_H
