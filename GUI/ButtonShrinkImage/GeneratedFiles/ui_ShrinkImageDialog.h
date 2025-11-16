/********************************************************************************
** Form generated from reading UI file 'ShrinkImageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHRINKIMAGEDIALOG_H
#define UI_SHRINKIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShrinkImageDialogClass
{
public:
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxRate;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;
    QCheckBox *checkBoxExeMaster;
    QCheckBox *checkBoxExeTarget;

    void setupUi(QDialog *ShrinkImageDialogClass)
    {
        if (ShrinkImageDialogClass->objectName().isEmpty())
            ShrinkImageDialogClass->setObjectName("ShrinkImageDialogClass");
        ShrinkImageDialogClass->resize(169, 158);
        label = new QLabel(ShrinkImageDialogClass);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 60, 101, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxRate = new QDoubleSpinBox(ShrinkImageDialogClass);
        doubleSpinBoxRate->setObjectName("doubleSpinBoxRate");
        doubleSpinBoxRate->setGeometry(QRect(30, 80, 101, 22));
        doubleSpinBoxRate->setDecimals(3);
        doubleSpinBoxRate->setMaximum(1.000000000000000);
        doubleSpinBoxRate->setValue(0.500000000000000);
        pushButtonOk = new QPushButton(ShrinkImageDialogClass);
        pushButtonOk->setObjectName("pushButtonOk");
        pushButtonOk->setGeometry(QRect(10, 110, 75, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOk->setIcon(icon);
        pushButtonCancel = new QPushButton(ShrinkImageDialogClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(90, 110, 71, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        checkBoxExeMaster = new QCheckBox(ShrinkImageDialogClass);
        checkBoxExeMaster->setObjectName("checkBoxExeMaster");
        checkBoxExeMaster->setGeometry(QRect(30, 10, 111, 18));
        checkBoxExeMaster->setChecked(true);
        checkBoxExeTarget = new QCheckBox(ShrinkImageDialogClass);
        checkBoxExeTarget->setObjectName("checkBoxExeTarget");
        checkBoxExeTarget->setGeometry(QRect(30, 30, 111, 18));
        checkBoxExeTarget->setChecked(true);

        retranslateUi(ShrinkImageDialogClass);

        QMetaObject::connectSlotsByName(ShrinkImageDialogClass);
    } // setupUi

    void retranslateUi(QDialog *ShrinkImageDialogClass)
    {
        ShrinkImageDialogClass->setWindowTitle(QCoreApplication::translate("ShrinkImageDialogClass", "ShrinkImageDialog", nullptr));
        label->setText(QCoreApplication::translate("ShrinkImageDialogClass", "\345\217\216\347\270\256\347\216\207", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("ShrinkImageDialogClass", "\345\256\237\350\241\214", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ShrinkImageDialogClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        checkBoxExeMaster->setText(QCoreApplication::translate("ShrinkImageDialogClass", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        checkBoxExeTarget->setText(QCoreApplication::translate("ShrinkImageDialogClass", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShrinkImageDialogClass: public Ui_ShrinkImageDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHRINKIMAGEDIALOG_H
