/********************************************************************************
** Form generated from reading UI file 'PanelSimpleForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELSIMPLEFORM_H
#define UI_PANELSIMPLEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_PanelSimpleForm
{
public:
    QPushButton *pushButtonUp;
    QPushButton *pushButtonLeft;
    QPushButton *pushButtonRight;
    QPushButton *pushButtonDown;
    QPushButton *pushButtonOrg;
    QPushButton *pushButtonHome;

    void setupUi(GUIFormBase *PanelSimpleForm)
    {
        if (PanelSimpleForm->objectName().isEmpty())
            PanelSimpleForm->setObjectName(QString::fromUtf8("PanelSimpleForm"));
        PanelSimpleForm->resize(217, 149);
        pushButtonUp = new QPushButton(PanelSimpleForm);
        pushButtonUp->setObjectName(QString::fromUtf8("pushButtonUp"));
        pushButtonUp->setGeometry(QRect(80, 10, 61, 41));
        pushButtonLeft = new QPushButton(PanelSimpleForm);
        pushButtonLeft->setObjectName(QString::fromUtf8("pushButtonLeft"));
        pushButtonLeft->setGeometry(QRect(10, 40, 61, 41));
        pushButtonRight = new QPushButton(PanelSimpleForm);
        pushButtonRight->setObjectName(QString::fromUtf8("pushButtonRight"));
        pushButtonRight->setGeometry(QRect(150, 40, 61, 41));
        pushButtonDown = new QPushButton(PanelSimpleForm);
        pushButtonDown->setObjectName(QString::fromUtf8("pushButtonDown"));
        pushButtonDown->setGeometry(QRect(80, 70, 61, 41));
        pushButtonOrg = new QPushButton(PanelSimpleForm);
        pushButtonOrg->setObjectName(QString::fromUtf8("pushButtonOrg"));
        pushButtonOrg->setGeometry(QRect(150, 100, 61, 41));
        pushButtonHome = new QPushButton(PanelSimpleForm);
        pushButtonHome->setObjectName(QString::fromUtf8("pushButtonHome"));
        pushButtonHome->setGeometry(QRect(10, 100, 61, 41));

        retranslateUi(PanelSimpleForm);

        QMetaObject::connectSlotsByName(PanelSimpleForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PanelSimpleForm)
    {
        PanelSimpleForm->setWindowTitle(QCoreApplication::translate("PanelSimpleForm", "Form", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("PanelSimpleForm", "\342\206\221", nullptr));
        pushButtonLeft->setText(QCoreApplication::translate("PanelSimpleForm", "\342\206\220", nullptr));
        pushButtonRight->setText(QCoreApplication::translate("PanelSimpleForm", "\342\206\222", nullptr));
        pushButtonDown->setText(QCoreApplication::translate("PanelSimpleForm", "\342\206\223", nullptr));
        pushButtonOrg->setText(QCoreApplication::translate("PanelSimpleForm", "Origin", nullptr));
        pushButtonHome->setText(QCoreApplication::translate("PanelSimpleForm", "Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PanelSimpleForm: public Ui_PanelSimpleForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELSIMPLEFORM_H
