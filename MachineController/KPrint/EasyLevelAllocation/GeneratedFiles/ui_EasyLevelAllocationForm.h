/********************************************************************************
** Form generated from reading UI file 'EasyLevelAllocationForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYLEVELALLOCATIONFORM_H
#define UI_EASYLEVELALLOCATIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_EasyLevelAllocationForm
{
public:
    QPushButton *PushButtonOpen;

    void setupUi(GUIFormBase *EasyLevelAllocationForm)
    {
        if (EasyLevelAllocationForm->objectName().isEmpty())
            EasyLevelAllocationForm->setObjectName("EasyLevelAllocationForm");
        EasyLevelAllocationForm->resize(145, 81);
        PushButtonOpen = new QPushButton(EasyLevelAllocationForm);
        PushButtonOpen->setObjectName("PushButtonOpen");
        PushButtonOpen->setGeometry(QRect(0, 0, 141, 81));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font.setPointSize(24);
        PushButtonOpen->setFont(font);
        PushButtonOpen->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOpen->setCheckable(false);
        PushButtonOpen->setChecked(false);
        PushButtonOpen->setAutoDefault(false);
        PushButtonOpen->setFlat(false);

        retranslateUi(EasyLevelAllocationForm);

        PushButtonOpen->setDefault(false);


        QMetaObject::connectSlotsByName(EasyLevelAllocationForm);
    } // setupUi

    void retranslateUi(GUIFormBase *EasyLevelAllocationForm)
    {
        EasyLevelAllocationForm->setWindowTitle(QCoreApplication::translate("EasyLevelAllocationForm", "Form", nullptr));
        PushButtonOpen->setText(QCoreApplication::translate("EasyLevelAllocationForm", "\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EasyLevelAllocationForm: public Ui_EasyLevelAllocationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYLEVELALLOCATIONFORM_H
