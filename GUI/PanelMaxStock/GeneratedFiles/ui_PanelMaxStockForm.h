/********************************************************************************
** Form generated from reading UI file 'PanelMaxStockForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELMAXSTOCKFORM_H
#define UI_PANELMAXSTOCKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PanelMaxStockForm
{
public:
    QPushButton *pushButtonSet;

    void setupUi(GUIFormBase *PanelMaxStockForm)
    {
        if (PanelMaxStockForm->objectName().isEmpty())
            PanelMaxStockForm->setObjectName("PanelMaxStockForm");
        PanelMaxStockForm->resize(400, 103);
        pushButtonSet = new QPushButton(PanelMaxStockForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(340, 0, 61, 34));

        retranslateUi(PanelMaxStockForm);

        QMetaObject::connectSlotsByName(PanelMaxStockForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PanelMaxStockForm)
    {
        PanelMaxStockForm->setWindowTitle(QCoreApplication::translate("PanelMaxStockForm", "Form", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("PanelMaxStockForm", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PanelMaxStockForm: public Ui_PanelMaxStockForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELMAXSTOCKFORM_H
