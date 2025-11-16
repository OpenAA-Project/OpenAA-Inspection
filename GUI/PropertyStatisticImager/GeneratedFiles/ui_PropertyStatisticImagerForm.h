/********************************************************************************
** Form generated from reading UI file 'PropertyStatisticImagerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYSTATISTICIMAGERFORM_H
#define UI_PROPERTYSTATISTICIMAGERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyStatisticImagerFormClass
{
public:
    QPushButton *pushButtonCreateIdealMasterImage;
    QFrame *frame;
    QToolButton *toolButtonMaster;
    QToolButton *toolButtonAverage;
    QToolButton *toolButtonDark;
    QToolButton *toolButtonLight;
    QToolButton *toolButtonDisorder;

    void setupUi(GUIFormBase *PropertyStatisticImagerFormClass)
    {
        if (PropertyStatisticImagerFormClass->objectName().isEmpty())
            PropertyStatisticImagerFormClass->setObjectName("PropertyStatisticImagerFormClass");
        PropertyStatisticImagerFormClass->resize(400, 700);
        pushButtonCreateIdealMasterImage = new QPushButton(PropertyStatisticImagerFormClass);
        pushButtonCreateIdealMasterImage->setObjectName("pushButtonCreateIdealMasterImage");
        pushButtonCreateIdealMasterImage->setGeometry(QRect(100, 430, 181, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Image.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCreateIdealMasterImage->setIcon(icon);
        frame = new QFrame(PropertyStatisticImagerFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(60, 20, 261, 291));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonMaster = new QToolButton(frame);
        toolButtonMaster->setObjectName("toolButtonMaster");
        toolButtonMaster->setGeometry(QRect(40, 20, 181, 41));
        toolButtonMaster->setCheckable(true);
        toolButtonMaster->setChecked(true);
        toolButtonMaster->setAutoExclusive(true);
        toolButtonAverage = new QToolButton(frame);
        toolButtonAverage->setObjectName("toolButtonAverage");
        toolButtonAverage->setGeometry(QRect(40, 70, 181, 41));
        toolButtonAverage->setCheckable(true);
        toolButtonAverage->setAutoExclusive(true);
        toolButtonDark = new QToolButton(frame);
        toolButtonDark->setObjectName("toolButtonDark");
        toolButtonDark->setGeometry(QRect(40, 120, 181, 41));
        toolButtonDark->setCheckable(true);
        toolButtonDark->setAutoExclusive(true);
        toolButtonLight = new QToolButton(frame);
        toolButtonLight->setObjectName("toolButtonLight");
        toolButtonLight->setGeometry(QRect(40, 170, 181, 41));
        toolButtonLight->setCheckable(true);
        toolButtonLight->setAutoExclusive(true);
        toolButtonDisorder = new QToolButton(frame);
        toolButtonDisorder->setObjectName("toolButtonDisorder");
        toolButtonDisorder->setGeometry(QRect(40, 220, 181, 41));
        toolButtonDisorder->setCheckable(true);
        toolButtonDisorder->setAutoExclusive(true);

        retranslateUi(PropertyStatisticImagerFormClass);

        QMetaObject::connectSlotsByName(PropertyStatisticImagerFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyStatisticImagerFormClass)
    {
        PropertyStatisticImagerFormClass->setWindowTitle(QCoreApplication::translate("PropertyStatisticImagerFormClass", "PropertyStatisticImagerForm", nullptr));
        pushButtonCreateIdealMasterImage->setText(QCoreApplication::translate("PropertyStatisticImagerFormClass", "\345\271\263\345\235\207\347\224\273\345\203\217\347\224\237\346\210\220", nullptr));
        toolButtonMaster->setText(QCoreApplication::translate("PropertyStatisticImagerFormClass", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        toolButtonAverage->setText(QCoreApplication::translate("PropertyStatisticImagerFormClass", "\345\271\263\345\235\207\345\214\226\347\224\273\345\203\217", nullptr));
        toolButtonDark->setText(QCoreApplication::translate("PropertyStatisticImagerFormClass", "\346\232\227\343\201\204\347\224\273\345\203\217", nullptr));
        toolButtonLight->setText(QCoreApplication::translate("PropertyStatisticImagerFormClass", "\346\230\216\343\202\213\343\201\204\347\224\273\345\203\217", nullptr));
        toolButtonDisorder->setText(QCoreApplication::translate("PropertyStatisticImagerFormClass", "\343\201\260\343\202\211\343\201\244\343\201\215\347\224\273\345\203\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyStatisticImagerFormClass: public Ui_PropertyStatisticImagerFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYSTATISTICIMAGERFORM_H
