/********************************************************************************
** Form generated from reading UI file 'InputSavingFileNameForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTSAVINGFILENAMEFORM_H
#define UI_INPUTSAVINGFILENAMEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputSavingFileNameForm
{
public:
    QPushButton *pushButtonOK;
    QLineEdit *lineEditFileName;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *InputSavingFileNameForm)
    {
        if (InputSavingFileNameForm->objectName().isEmpty())
            InputSavingFileNameForm->setObjectName("InputSavingFileNameForm");
        InputSavingFileNameForm->resize(350, 79);
        pushButtonOK = new QPushButton(InputSavingFileNameForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 40, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        lineEditFileName = new QLineEdit(InputSavingFileNameForm);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(10, 10, 331, 20));
        pushButtonCancel = new QPushButton(InputSavingFileNameForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(230, 40, 111, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(InputSavingFileNameForm);

        QMetaObject::connectSlotsByName(InputSavingFileNameForm);
    } // setupUi

    void retranslateUi(QDialog *InputSavingFileNameForm)
    {
        InputSavingFileNameForm->setWindowTitle(QCoreApplication::translate("InputSavingFileNameForm", "Dialog", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("InputSavingFileNameForm", "OK(Save)", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputSavingFileNameForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputSavingFileNameForm: public Ui_InputSavingFileNameForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTSAVINGFILENAMEFORM_H
