/********************************************************************************
** Form generated from reading UI file 'EditProgramLineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPROGRAMLINEDIALOG_H
#define UI_EDITPROGRAMLINEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditProgramLineDialog
{
public:
    QLabel *label;
    QLineEdit *lineEditPathFileName;
    QLineEdit *lineEditArmuments;
    QLabel *label_2;
    QLineEdit *lineEditWorkingPath;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxWatchTerm;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSelectPathFile;
    QPushButton *pushButtonSelectWorkingPath;

    void setupUi(QDialog *EditProgramLineDialog)
    {
        if (EditProgramLineDialog->objectName().isEmpty())
            EditProgramLineDialog->setObjectName("EditProgramLineDialog");
        EditProgramLineDialog->resize(594, 300);
        label = new QLabel(EditProgramLineDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 551, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditPathFileName = new QLineEdit(EditProgramLineDialog);
        lineEditPathFileName->setObjectName("lineEditPathFileName");
        lineEditPathFileName->setGeometry(QRect(20, 40, 531, 20));
        lineEditArmuments = new QLineEdit(EditProgramLineDialog);
        lineEditArmuments->setObjectName("lineEditArmuments");
        lineEditArmuments->setGeometry(QRect(20, 90, 551, 20));
        label_2 = new QLabel(EditProgramLineDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 70, 551, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        lineEditWorkingPath = new QLineEdit(EditProgramLineDialog);
        lineEditWorkingPath->setObjectName("lineEditWorkingPath");
        lineEditWorkingPath->setGeometry(QRect(20, 140, 531, 20));
        label_3 = new QLabel(EditProgramLineDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 120, 551, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(EditProgramLineDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 180, 111, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        spinBoxWatchTerm = new QSpinBox(EditProgramLineDialog);
        spinBoxWatchTerm->setObjectName("spinBoxWatchTerm");
        spinBoxWatchTerm->setGeometry(QRect(20, 200, 111, 22));
        spinBoxWatchTerm->setMaximum(99999999);
        pushButtonOK = new QPushButton(EditProgramLineDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(90, 250, 81, 31));
        pushButtonCancel = new QPushButton(EditProgramLineDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(420, 250, 81, 31));
        pushButtonSelectPathFile = new QPushButton(EditProgramLineDialog);
        pushButtonSelectPathFile->setObjectName("pushButtonSelectPathFile");
        pushButtonSelectPathFile->setGeometry(QRect(550, 40, 21, 23));
        pushButtonSelectWorkingPath = new QPushButton(EditProgramLineDialog);
        pushButtonSelectWorkingPath->setObjectName("pushButtonSelectWorkingPath");
        pushButtonSelectWorkingPath->setGeometry(QRect(550, 140, 21, 23));

        retranslateUi(EditProgramLineDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditProgramLineDialog);
    } // setupUi

    void retranslateUi(QDialog *EditProgramLineDialog)
    {
        EditProgramLineDialog->setWindowTitle(QCoreApplication::translate("EditProgramLineDialog", "Edit Program Line", nullptr));
        label->setText(QCoreApplication::translate("EditProgramLineDialog", "Program Path and File name", nullptr));
        label_2->setText(QCoreApplication::translate("EditProgramLineDialog", "Argmuments", nullptr));
        label_3->setText(QCoreApplication::translate("EditProgramLineDialog", "Working path", nullptr));
        label_4->setText(QCoreApplication::translate("EditProgramLineDialog", "Watch term(sec)", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditProgramLineDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditProgramLineDialog", "Cancel", nullptr));
        pushButtonSelectPathFile->setText(QCoreApplication::translate("EditProgramLineDialog", "...", nullptr));
        pushButtonSelectWorkingPath->setText(QCoreApplication::translate("EditProgramLineDialog", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditProgramLineDialog: public Ui_EditProgramLineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPROGRAMLINEDIALOG_H
