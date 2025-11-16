/********************************************************************************
** Form generated from reading UI file 'MoveImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOVEIMAGEFORM_H
#define UI_MOVEIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MoveImageForm
{
public:
    QSpinBox *spinBoxYDir;
    QLabel *label_2;
    QLabel *label;
    QCheckBox *checkBoxMaster;
    QLabel *label_3;
    QCheckBox *checkBoxTarget;
    QPushButton *pushButtonCancel;
    QSpinBox *spinBoxXDir;
    QPushButton *pushButtonGo;

    void setupUi(QWidget *MoveImageForm)
    {
        if (MoveImageForm->objectName().isEmpty())
            MoveImageForm->setObjectName("MoveImageForm");
        MoveImageForm->resize(213, 195);
        spinBoxYDir = new QSpinBox(MoveImageForm);
        spinBoxYDir->setObjectName("spinBoxYDir");
        spinBoxYDir->setGeometry(QRect(120, 80, 81, 22));
        spinBoxYDir->setMinimum(-999999);
        spinBoxYDir->setMaximum(999999);
        label_2 = new QLabel(MoveImageForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 60, 81, 16));
        label = new QLabel(MoveImageForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 77, 16));
        checkBoxMaster = new QCheckBox(MoveImageForm);
        checkBoxMaster->setObjectName("checkBoxMaster");
        checkBoxMaster->setGeometry(QRect(50, 10, 131, 18));
        checkBoxMaster->setChecked(true);
        label_3 = new QLabel(MoveImageForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 120, 151, 16));
        checkBoxTarget = new QCheckBox(MoveImageForm);
        checkBoxTarget->setObjectName("checkBoxTarget");
        checkBoxTarget->setGeometry(QRect(50, 30, 141, 18));
        checkBoxTarget->setChecked(true);
        pushButtonCancel = new QPushButton(MoveImageForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(114, 150, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        spinBoxXDir = new QSpinBox(MoveImageForm);
        spinBoxXDir->setObjectName("spinBoxXDir");
        spinBoxXDir->setGeometry(QRect(10, 80, 81, 22));
        spinBoxXDir->setMinimum(-999999);
        spinBoxXDir->setMaximum(999999);
        pushButtonGo = new QPushButton(MoveImageForm);
        pushButtonGo->setObjectName("pushButtonGo");
        pushButtonGo->setGeometry(QRect(10, 150, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGo->setIcon(icon1);

        retranslateUi(MoveImageForm);

        pushButtonGo->setDefault(true);


        QMetaObject::connectSlotsByName(MoveImageForm);
    } // setupUi

    void retranslateUi(QWidget *MoveImageForm)
    {
        MoveImageForm->setWindowTitle(QCoreApplication::translate("MoveImageForm", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("MoveImageForm", "Y\346\226\271\345\220\221\343\201\256\347\247\273\345\213\225\351\207\217", nullptr));
        label->setText(QCoreApplication::translate("MoveImageForm", "X\346\226\271\345\220\221\343\201\256\347\247\273\345\213\225\351\207\217", nullptr));
        checkBoxMaster->setText(QCoreApplication::translate("MoveImageForm", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        label_3->setText(QCoreApplication::translate("MoveImageForm", "\345\217\263\343\203\273\344\270\213\346\226\271\345\220\221\343\201\214\343\203\227\343\203\251\343\202\271", nullptr));
        checkBoxTarget->setText(QCoreApplication::translate("MoveImageForm", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("MoveImageForm", "Cancel", nullptr));
        pushButtonGo->setText(QCoreApplication::translate("MoveImageForm", "Go", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MoveImageForm: public Ui_MoveImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOVEIMAGEFORM_H
