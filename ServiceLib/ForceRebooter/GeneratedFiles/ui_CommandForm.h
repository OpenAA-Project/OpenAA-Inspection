/********************************************************************************
** Form generated from reading UI file 'CommandForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMANDFORM_H
#define UI_COMMANDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommandForm
{
public:
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(QWidget *CommandForm)
    {
        if (CommandForm->objectName().isEmpty())
            CommandForm->setObjectName("CommandForm");
        CommandForm->resize(190, 50);
        progressBar = new QProgressBar(CommandForm);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 20, 171, 23));
        progressBar->setMaximum(10);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        label = new QLabel(CommandForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 171, 18));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(CommandForm);

        QMetaObject::connectSlotsByName(CommandForm);
    } // setupUi

    void retranslateUi(QWidget *CommandForm)
    {
        CommandForm->setWindowTitle(QCoreApplication::translate("CommandForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("CommandForm", "XXX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CommandForm: public Ui_CommandForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMANDFORM_H
