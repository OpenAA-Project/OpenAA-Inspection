/********************************************************************************
** Form generated from reading UI file 'IntegrationInputLotForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONINPUTLOTFORM_H
#define UI_INTEGRATIONINPUTLOTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationInputLotForm
{
public:
    QLineEdit *lineEditLotNumber;
    QLineEdit *lineEditSubCode;
    QToolButton *toolButtonGenerateLot;
    QPushButton *pushButtonLotNumber;
    QPushButton *pushButtonSubCode;
    QPushButton *pushButtonLotID;
    QLineEdit *lineEditLotID;
    QPushButton *pushButtonTitleLotID;
    QPushButton *pushButtonTitleLotNumber;
    QPushButton *pushButtonTitleSubCode;

    void setupUi(GUIFormBase *IntegrationInputLotForm)
    {
        if (IntegrationInputLotForm->objectName().isEmpty())
            IntegrationInputLotForm->setObjectName("IntegrationInputLotForm");
        IntegrationInputLotForm->resize(567, 93);
        lineEditLotNumber = new QLineEdit(IntegrationInputLotForm);
        lineEditLotNumber->setObjectName("lineEditLotNumber");
        lineEditLotNumber->setGeometry(QRect(110, 30, 291, 32));
        lineEditSubCode = new QLineEdit(IntegrationInputLotForm);
        lineEditSubCode->setObjectName("lineEditSubCode");
        lineEditSubCode->setGeometry(QRect(110, 60, 291, 32));
        toolButtonGenerateLot = new QToolButton(IntegrationInputLotForm);
        toolButtonGenerateLot->setObjectName("toolButtonGenerateLot");
        toolButtonGenerateLot->setGeometry(QRect(460, 10, 101, 71));
        pushButtonLotNumber = new QPushButton(IntegrationInputLotForm);
        pushButtonLotNumber->setObjectName("pushButtonLotNumber");
        pushButtonLotNumber->setGeometry(QRect(410, 30, 41, 32));
        pushButtonSubCode = new QPushButton(IntegrationInputLotForm);
        pushButtonSubCode->setObjectName("pushButtonSubCode");
        pushButtonSubCode->setGeometry(QRect(410, 60, 41, 32));
        pushButtonLotID = new QPushButton(IntegrationInputLotForm);
        pushButtonLotID->setObjectName("pushButtonLotID");
        pushButtonLotID->setGeometry(QRect(410, 0, 41, 32));
        lineEditLotID = new QLineEdit(IntegrationInputLotForm);
        lineEditLotID->setObjectName("lineEditLotID");
        lineEditLotID->setGeometry(QRect(110, 0, 291, 32));
        pushButtonTitleLotID = new QPushButton(IntegrationInputLotForm);
        pushButtonTitleLotID->setObjectName("pushButtonTitleLotID");
        pushButtonTitleLotID->setGeometry(QRect(0, 0, 101, 32));
        pushButtonTitleLotNumber = new QPushButton(IntegrationInputLotForm);
        pushButtonTitleLotNumber->setObjectName("pushButtonTitleLotNumber");
        pushButtonTitleLotNumber->setGeometry(QRect(0, 30, 101, 32));
        pushButtonTitleSubCode = new QPushButton(IntegrationInputLotForm);
        pushButtonTitleSubCode->setObjectName("pushButtonTitleSubCode");
        pushButtonTitleSubCode->setGeometry(QRect(0, 60, 101, 32));
        QWidget::setTabOrder(lineEditLotID, pushButtonLotID);
        QWidget::setTabOrder(pushButtonLotID, lineEditLotNumber);
        QWidget::setTabOrder(lineEditLotNumber, pushButtonLotNumber);
        QWidget::setTabOrder(pushButtonLotNumber, lineEditSubCode);
        QWidget::setTabOrder(lineEditSubCode, pushButtonSubCode);
        QWidget::setTabOrder(pushButtonSubCode, toolButtonGenerateLot);

        retranslateUi(IntegrationInputLotForm);

        QMetaObject::connectSlotsByName(IntegrationInputLotForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationInputLotForm)
    {
        IntegrationInputLotForm->setWindowTitle(QCoreApplication::translate("IntegrationInputLotForm", "Form", nullptr));
        toolButtonGenerateLot->setText(QCoreApplication::translate("IntegrationInputLotForm", "\347\224\237\346\210\220", nullptr));
        pushButtonLotNumber->setText(QCoreApplication::translate("IntegrationInputLotForm", "...", nullptr));
        pushButtonSubCode->setText(QCoreApplication::translate("IntegrationInputLotForm", "...", nullptr));
        pushButtonLotID->setText(QCoreApplication::translate("IntegrationInputLotForm", "...", nullptr));
        pushButtonTitleLotID->setText(QCoreApplication::translate("IntegrationInputLotForm", "Lot ID", nullptr));
        pushButtonTitleLotNumber->setText(QCoreApplication::translate("IntegrationInputLotForm", "Lot number", nullptr));
        pushButtonTitleSubCode->setText(QCoreApplication::translate("IntegrationInputLotForm", "Sub code", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationInputLotForm: public Ui_IntegrationInputLotForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONINPUTLOTFORM_H
