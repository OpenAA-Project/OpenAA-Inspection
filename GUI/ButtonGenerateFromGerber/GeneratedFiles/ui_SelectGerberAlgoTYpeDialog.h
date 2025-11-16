/********************************************************************************
** Form generated from reading UI file 'SelectGerberAlgoTYpeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTGERBERALGOTYPEDIALOG_H
#define UI_SELECTGERBERALGOTYPEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectGerberAlgoTYpeDialog
{
public:
    QGroupBox *groupBox;
    QCheckBox *checkBoxMakeAlgoShiftable;
    QCheckBox *checkBoxMakeAlgoSeparate;
    QCheckBox *checkBoxMakeAlgoEnlarge;
    QCheckBox *checkBoxMakeAlgoShrinked;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectGerberAlgoTYpeDialog)
    {
        if (SelectGerberAlgoTYpeDialog->objectName().isEmpty())
            SelectGerberAlgoTYpeDialog->setObjectName("SelectGerberAlgoTYpeDialog");
        SelectGerberAlgoTYpeDialog->resize(282, 208);
        groupBox = new QGroupBox(SelectGerberAlgoTYpeDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 281, 151));
        checkBoxMakeAlgoShiftable = new QCheckBox(groupBox);
        checkBoxMakeAlgoShiftable->setObjectName("checkBoxMakeAlgoShiftable");
        checkBoxMakeAlgoShiftable->setGeometry(QRect(4, 10, 271, 20));
        checkBoxMakeAlgoShiftable->setCheckable(true);
        checkBoxMakeAlgoShiftable->setChecked(false);
        checkBoxMakeAlgoShiftable->setAutoExclusive(true);
        checkBoxMakeAlgoSeparate = new QCheckBox(groupBox);
        checkBoxMakeAlgoSeparate->setObjectName("checkBoxMakeAlgoSeparate");
        checkBoxMakeAlgoSeparate->setGeometry(QRect(4, 40, 271, 20));
        checkBoxMakeAlgoSeparate->setChecked(true);
        checkBoxMakeAlgoSeparate->setAutoExclusive(true);
        checkBoxMakeAlgoEnlarge = new QCheckBox(groupBox);
        checkBoxMakeAlgoEnlarge->setObjectName("checkBoxMakeAlgoEnlarge");
        checkBoxMakeAlgoEnlarge->setGeometry(QRect(4, 70, 271, 20));
        checkBoxMakeAlgoEnlarge->setAutoExclusive(true);
        checkBoxMakeAlgoShrinked = new QCheckBox(groupBox);
        checkBoxMakeAlgoShrinked->setObjectName("checkBoxMakeAlgoShrinked");
        checkBoxMakeAlgoShrinked->setGeometry(QRect(4, 100, 271, 20));
        checkBoxMakeAlgoShrinked->setAutoExclusive(true);
        pushButtonOK = new QPushButton(SelectGerberAlgoTYpeDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 160, 112, 34));
        pushButtonCancel = new QPushButton(SelectGerberAlgoTYpeDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(160, 160, 112, 34));

        retranslateUi(SelectGerberAlgoTYpeDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectGerberAlgoTYpeDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectGerberAlgoTYpeDialog)
    {
        SelectGerberAlgoTYpeDialog->setWindowTitle(QCoreApplication::translate("SelectGerberAlgoTYpeDialog", "Dialog", nullptr));
        groupBox->setTitle(QString());
        checkBoxMakeAlgoShiftable->setText(QCoreApplication::translate("SelectGerberAlgoTYpeDialog", "Shiftable area", nullptr));
        checkBoxMakeAlgoSeparate->setText(QCoreApplication::translate("SelectGerberAlgoTYpeDialog", "Separate Stable/Unstable", nullptr));
        checkBoxMakeAlgoEnlarge->setText(QCoreApplication::translate("SelectGerberAlgoTYpeDialog", "Enlarge area", nullptr));
        checkBoxMakeAlgoShrinked->setText(QCoreApplication::translate("SelectGerberAlgoTYpeDialog", "Shrinked area", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectGerberAlgoTYpeDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectGerberAlgoTYpeDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectGerberAlgoTYpeDialog: public Ui_SelectGerberAlgoTYpeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTGERBERALGOTYPEDIALOG_H
