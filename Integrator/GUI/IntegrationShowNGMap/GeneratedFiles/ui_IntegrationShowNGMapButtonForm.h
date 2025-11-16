/********************************************************************************
** Form generated from reading UI file 'IntegrationShowNGMapButtonForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONSHOWNGMAPBUTTONFORM_H
#define UI_INTEGRATIONSHOWNGMAPBUTTONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_IntegrationShowNGMapButtonForm
{
public:
    QPushButton *PushButtonNGMap;

    void setupUi(GUIFormBase *IntegrationShowNGMapButtonForm)
    {
        if (IntegrationShowNGMapButtonForm->objectName().isEmpty())
            IntegrationShowNGMapButtonForm->setObjectName("IntegrationShowNGMapButtonForm");
        IntegrationShowNGMapButtonForm->resize(194, 54);
        PushButtonNGMap = new QPushButton(IntegrationShowNGMapButtonForm);
        PushButtonNGMap->setObjectName("PushButtonNGMap");
        PushButtonNGMap->setGeometry(QRect(0, 0, 191, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(20);
        PushButtonNGMap->setFont(font);
        PushButtonNGMap->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonNGMap->setCheckable(false);
        PushButtonNGMap->setChecked(false);
        PushButtonNGMap->setAutoDefault(false);
        PushButtonNGMap->setFlat(false);

        retranslateUi(IntegrationShowNGMapButtonForm);

        PushButtonNGMap->setDefault(false);


        QMetaObject::connectSlotsByName(IntegrationShowNGMapButtonForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationShowNGMapButtonForm)
    {
        IntegrationShowNGMapButtonForm->setWindowTitle(QCoreApplication::translate("IntegrationShowNGMapButtonForm", "Form", nullptr));
        PushButtonNGMap->setText(QCoreApplication::translate("IntegrationShowNGMapButtonForm", "Set threshold", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationShowNGMapButtonForm: public Ui_IntegrationShowNGMapButtonForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONSHOWNGMAPBUTTONFORM_H
