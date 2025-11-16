/********************************************************************************
** Form generated from reading UI file 'IntegrationCopyImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONCOPYIMAGEFORM_H
#define UI_INTEGRATIONCOPYIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_IntegrationCopyImageForm
{
public:
    QPushButton *PushButtonCopy;

    void setupUi(GUIFormBase *IntegrationCopyImageForm)
    {
        if (IntegrationCopyImageForm->objectName().isEmpty())
            IntegrationCopyImageForm->setObjectName("IntegrationCopyImageForm");
        IntegrationCopyImageForm->resize(194, 52);
        PushButtonCopy = new QPushButton(IntegrationCopyImageForm);
        PushButtonCopy->setObjectName("PushButtonCopy");
        PushButtonCopy->setGeometry(QRect(0, 0, 191, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(20);
        PushButtonCopy->setFont(font);
        PushButtonCopy->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonCopy->setCheckable(false);
        PushButtonCopy->setChecked(false);
        PushButtonCopy->setAutoDefault(false);
        PushButtonCopy->setFlat(false);

        retranslateUi(IntegrationCopyImageForm);

        PushButtonCopy->setDefault(false);


        QMetaObject::connectSlotsByName(IntegrationCopyImageForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationCopyImageForm)
    {
        IntegrationCopyImageForm->setWindowTitle(QCoreApplication::translate("IntegrationCopyImageForm", "Form", nullptr));
        PushButtonCopy->setText(QCoreApplication::translate("IntegrationCopyImageForm", "Copy", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationCopyImageForm: public Ui_IntegrationCopyImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONCOPYIMAGEFORM_H
