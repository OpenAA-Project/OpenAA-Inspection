/********************************************************************************
** Form generated from reading UI file 'HookDrawRegulationLineForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOOKDRAWREGULATIONLINEFORM_H
#define UI_HOOKDRAWREGULATIONLINEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_HookDrawRegulationLineForm
{
public:
    QToolButton *toolButton;

    void setupUi(GUIFormBase *HookDrawRegulationLineForm)
    {
        if (HookDrawRegulationLineForm->objectName().isEmpty())
            HookDrawRegulationLineForm->setObjectName("HookDrawRegulationLineForm");
        HookDrawRegulationLineForm->resize(48, 48);
        toolButton = new QToolButton(HookDrawRegulationLineForm);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(0, 0, 48, 48));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Resources/Nothing.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(48, 48));

        retranslateUi(HookDrawRegulationLineForm);

        QMetaObject::connectSlotsByName(HookDrawRegulationLineForm);
    } // setupUi

    void retranslateUi(GUIFormBase *HookDrawRegulationLineForm)
    {
        HookDrawRegulationLineForm->setWindowTitle(QCoreApplication::translate("HookDrawRegulationLineForm", "Form", nullptr));
        toolButton->setText(QCoreApplication::translate("HookDrawRegulationLineForm", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HookDrawRegulationLineForm: public Ui_HookDrawRegulationLineForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOOKDRAWREGULATIONLINEFORM_H
