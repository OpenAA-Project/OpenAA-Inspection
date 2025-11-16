/********************************************************************************
** Form generated from reading UI file 'ChangeNewMasterDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGENEWMASTERDIALOG_H
#define UI_CHANGENEWMASTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChangeNewMasterDialog
{
public:
    QPushButton *PushButtonCreateNewMaster;
    QPushButton *PushButtonOnlyImage;

    void setupUi(QDialog *ChangeNewMasterDialog)
    {
        if (ChangeNewMasterDialog->objectName().isEmpty())
            ChangeNewMasterDialog->setObjectName("ChangeNewMasterDialog");
        ChangeNewMasterDialog->resize(357, 175);
        PushButtonCreateNewMaster = new QPushButton(ChangeNewMasterDialog);
        PushButtonCreateNewMaster->setObjectName("PushButtonCreateNewMaster");
        PushButtonCreateNewMaster->setGeometry(QRect(10, 10, 331, 71));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font.setPointSize(24);
        PushButtonCreateNewMaster->setFont(font);
        PushButtonCreateNewMaster->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(100,254, 100, 255), stop:1 rgba(60, 165, 60, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(60, 165, 60, 255), stop:1 rgba(100, 254, 100, 255));\n"
"}"));
        PushButtonCreateNewMaster->setCheckable(false);
        PushButtonCreateNewMaster->setChecked(false);
        PushButtonCreateNewMaster->setAutoExclusive(false);
        PushButtonCreateNewMaster->setAutoDefault(false);
        PushButtonCreateNewMaster->setFlat(false);
        PushButtonOnlyImage = new QPushButton(ChangeNewMasterDialog);
        PushButtonOnlyImage->setObjectName("PushButtonOnlyImage");
        PushButtonOnlyImage->setGeometry(QRect(10, 90, 331, 71));
        PushButtonOnlyImage->setFont(font);
        PushButtonOnlyImage->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(254, 100, 100, 255), stop:1 rgba(160, 80, 80, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(160, 80, 80, 255), stop:1 rgba(220, 100, 100, 60));\n"
"}"));
        PushButtonOnlyImage->setCheckable(false);
        PushButtonOnlyImage->setChecked(false);
        PushButtonOnlyImage->setAutoExclusive(false);
        PushButtonOnlyImage->setAutoDefault(false);
        PushButtonOnlyImage->setFlat(false);

        retranslateUi(ChangeNewMasterDialog);

        PushButtonCreateNewMaster->setDefault(false);
        PushButtonOnlyImage->setDefault(false);


        QMetaObject::connectSlotsByName(ChangeNewMasterDialog);
    } // setupUi

    void retranslateUi(QDialog *ChangeNewMasterDialog)
    {
        ChangeNewMasterDialog->setWindowTitle(QCoreApplication::translate("ChangeNewMasterDialog", "Change image", nullptr));
        PushButtonCreateNewMaster->setText(QCoreApplication::translate("ChangeNewMasterDialog", "\346\226\260\350\246\217\343\203\236\343\202\271\343\202\277\343\203\274\343\203\207\343\203\274\343\202\277", nullptr));
        PushButtonOnlyImage->setText(QCoreApplication::translate("ChangeNewMasterDialog", "\347\224\273\345\203\217\346\233\264\346\226\260\343\201\256\343\201\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeNewMasterDialog: public Ui_ChangeNewMasterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGENEWMASTERDIALOG_H
