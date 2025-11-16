/********************************************************************************
** Form generated from reading UI file 'NegPosImageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEGPOSIMAGEDIALOG_H
#define UI_NEGPOSIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NegPosImageDialog
{
public:
    QPushButton *pushButtonConvert;
    QCheckBox *checkBoxMaster;
    QCheckBox *checkBoxTarget;

    void setupUi(QDialog *NegPosImageDialog)
    {
        if (NegPosImageDialog->objectName().isEmpty())
            NegPosImageDialog->setObjectName("NegPosImageDialog");
        NegPosImageDialog->resize(138, 120);
        pushButtonConvert = new QPushButton(NegPosImageDialog);
        pushButtonConvert->setObjectName("pushButtonConvert");
        pushButtonConvert->setGeometry(QRect(10, 72, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Convert.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonConvert->setIcon(icon);
        checkBoxMaster = new QCheckBox(NegPosImageDialog);
        checkBoxMaster->setObjectName("checkBoxMaster");
        checkBoxMaster->setGeometry(QRect(10, 10, 111, 18));
        checkBoxMaster->setChecked(true);
        checkBoxTarget = new QCheckBox(NegPosImageDialog);
        checkBoxTarget->setObjectName("checkBoxTarget");
        checkBoxTarget->setGeometry(QRect(10, 40, 111, 18));
        checkBoxTarget->setChecked(true);

        retranslateUi(NegPosImageDialog);

        QMetaObject::connectSlotsByName(NegPosImageDialog);
    } // setupUi

    void retranslateUi(QDialog *NegPosImageDialog)
    {
        NegPosImageDialog->setWindowTitle(QCoreApplication::translate("NegPosImageDialog", "Dialog", nullptr));
        pushButtonConvert->setText(QCoreApplication::translate("NegPosImageDialog", "Convert", nullptr));
        checkBoxMaster->setText(QCoreApplication::translate("NegPosImageDialog", "Master Image", nullptr));
        checkBoxTarget->setText(QCoreApplication::translate("NegPosImageDialog", "Target Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NegPosImageDialog: public Ui_NegPosImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEGPOSIMAGEDIALOG_H
