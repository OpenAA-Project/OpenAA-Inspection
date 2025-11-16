/********************************************************************************
** Form generated from reading UI file 'RotateImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROTATEIMAGEFORM_H
#define UI_ROTATEIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RotateImageForm
{
public:
    QPushButton *pushButtonCancel;
    QLabel *label;
    QPushButton *pushButtonGo;
    QCheckBox *checkBoxMaster;
    QCheckBox *checkBoxTarget;
    QDoubleSpinBox *doubleSpinBoxAngle;
    QLabel *label_2;

    void setupUi(QDialog *RotateImageForm)
    {
        if (RotateImageForm->objectName().isEmpty())
            RotateImageForm->setObjectName("RotateImageForm");
        RotateImageForm->resize(190, 186);
        pushButtonCancel = new QPushButton(RotateImageForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(100, 140, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        label = new QLabel(RotateImageForm);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 60, 77, 16));
        label->setAlignment(Qt::AlignCenter);
        pushButtonGo = new QPushButton(RotateImageForm);
        pushButtonGo->setObjectName("pushButtonGo");
        pushButtonGo->setGeometry(QRect(10, 140, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGo->setIcon(icon1);
        checkBoxMaster = new QCheckBox(RotateImageForm);
        checkBoxMaster->setObjectName("checkBoxMaster");
        checkBoxMaster->setGeometry(QRect(50, 10, 131, 18));
        checkBoxMaster->setChecked(true);
        checkBoxTarget = new QCheckBox(RotateImageForm);
        checkBoxTarget->setObjectName("checkBoxTarget");
        checkBoxTarget->setGeometry(QRect(50, 30, 141, 18));
        checkBoxTarget->setChecked(true);
        doubleSpinBoxAngle = new QDoubleSpinBox(RotateImageForm);
        doubleSpinBoxAngle->setObjectName("doubleSpinBoxAngle");
        doubleSpinBoxAngle->setGeometry(QRect(50, 80, 81, 22));
        doubleSpinBoxAngle->setMinimum(-360.000000000000000);
        doubleSpinBoxAngle->setMaximum(360.000000000000000);
        label_2 = new QLabel(RotateImageForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 110, 141, 16));
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(RotateImageForm);

        QMetaObject::connectSlotsByName(RotateImageForm);
    } // setupUi

    void retranslateUi(QDialog *RotateImageForm)
    {
        RotateImageForm->setWindowTitle(QCoreApplication::translate("RotateImageForm", "Rotate image", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RotateImageForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("RotateImageForm", "\345\233\236\350\273\242\350\247\222\345\272\246", nullptr));
        pushButtonGo->setText(QCoreApplication::translate("RotateImageForm", "Go", nullptr));
        checkBoxMaster->setText(QCoreApplication::translate("RotateImageForm", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        checkBoxTarget->setText(QCoreApplication::translate("RotateImageForm", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        label_2->setText(QCoreApplication::translate("RotateImageForm", "\346\234\254\345\221\275\344\273\244\343\201\257UNDO\343\201\247\343\201\215\343\201\276\343\201\233\343\202\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RotateImageForm: public Ui_RotateImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROTATEIMAGEFORM_H
