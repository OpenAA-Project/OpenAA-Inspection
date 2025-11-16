/********************************************************************************
** Form generated from reading UI file 'ButtonToSetFilterForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONTOSETFILTERFORM_H
#define UI_BUTTONTOSETFILTERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonToSetFilterForm
{
public:
    QPushButton *pushButtonFilter;

    void setupUi(GUIFormBase *ButtonToSetFilterForm)
    {
        if (ButtonToSetFilterForm->objectName().isEmpty())
            ButtonToSetFilterForm->setObjectName("ButtonToSetFilterForm");
        ButtonToSetFilterForm->resize(131, 42);
        pushButtonFilter = new QPushButton(ButtonToSetFilterForm);
        pushButtonFilter->setObjectName("pushButtonFilter");
        pushButtonFilter->setGeometry(QRect(0, 0, 131, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/ButtonToSetFilter.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonFilter->setIcon(icon);

        retranslateUi(ButtonToSetFilterForm);

        QMetaObject::connectSlotsByName(ButtonToSetFilterForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ButtonToSetFilterForm)
    {
        ButtonToSetFilterForm->setWindowTitle(QCoreApplication::translate("ButtonToSetFilterForm", "Set filter", nullptr));
        pushButtonFilter->setText(QCoreApplication::translate("ButtonToSetFilterForm", "Filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonToSetFilterForm: public Ui_ButtonToSetFilterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONTOSETFILTERFORM_H
