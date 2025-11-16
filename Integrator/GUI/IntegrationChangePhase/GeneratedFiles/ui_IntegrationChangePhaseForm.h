/********************************************************************************
** Form generated from reading UI file 'IntegrationChangePhaseForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONCHANGEPHASEFORM_H
#define UI_INTEGRATIONCHANGEPHASEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationChangePhaseForm
{
public:
    QTableWidget *tableWidget;
    QFrame *frame;
    QPushButton *pushButtonAddPhase;
    QPushButton *pushButtonSubPhase;
    QPushButton *pushButtonGetCurrent;

    void setupUi(GUIFormBase *IntegrationChangePhaseForm)
    {
        if (IntegrationChangePhaseForm->objectName().isEmpty())
            IntegrationChangePhaseForm->setObjectName("IntegrationChangePhaseForm");
        IntegrationChangePhaseForm->resize(200, 322);
        tableWidget = new QTableWidget(IntegrationChangePhaseForm);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 199, 192));
        QFont font;
        font.setPointSize(12);
        tableWidget->setFont(font);
        tableWidget->verticalHeader()->setMinimumSectionSize(45);
        tableWidget->verticalHeader()->setDefaultSectionSize(45);
        frame = new QFrame(IntegrationChangePhaseForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 190, 201, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonAddPhase = new QPushButton(frame);
        pushButtonAddPhase->setObjectName("pushButtonAddPhase");
        pushButtonAddPhase->setGeometry(QRect(10, 10, 81, 51));
        QFont font1;
        font1.setPointSize(24);
        pushButtonAddPhase->setFont(font1);
        pushButtonAddPhase->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonSubPhase = new QPushButton(frame);
        pushButtonSubPhase->setObjectName("pushButtonSubPhase");
        pushButtonSubPhase->setGeometry(QRect(110, 10, 81, 51));
        pushButtonSubPhase->setFont(font1);
        pushButtonSubPhase->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonGetCurrent = new QPushButton(frame);
        pushButtonGetCurrent->setObjectName("pushButtonGetCurrent");
        pushButtonGetCurrent->setGeometry(QRect(10, 70, 181, 51));
        QFont font2;
        font2.setPointSize(16);
        pushButtonGetCurrent->setFont(font2);
        pushButtonGetCurrent->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonGetCurrent->setCheckable(true);

        retranslateUi(IntegrationChangePhaseForm);

        QMetaObject::connectSlotsByName(IntegrationChangePhaseForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationChangePhaseForm)
    {
        IntegrationChangePhaseForm->setWindowTitle(QCoreApplication::translate("IntegrationChangePhaseForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("IntegrationChangePhaseForm", "\345\210\207\343\202\212\346\233\277\343\201\210", nullptr));
        pushButtonAddPhase->setText(QCoreApplication::translate("IntegrationChangePhaseForm", "+", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonSubPhase->setToolTip(QCoreApplication::translate("IntegrationChangePhaseForm", "<html><head/><body><p>\351\201\270\346\212\236\343\201\225\343\202\214\343\201\237Phase\343\202\222\345\211\212\351\231\244\343\201\227\343\201\276\343\201\231\343\200\202</p><p>1\347\225\252\347\233\256\343\201\256Phase\343\201\257\345\211\212\351\231\244\343\201\247\343\201\215\343\201\276\343\201\233\343\202\223</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSubPhase->setText(QCoreApplication::translate("IntegrationChangePhaseForm", "-", nullptr));
        pushButtonGetCurrent->setText(QCoreApplication::translate("IntegrationChangePhaseForm", "\351\201\270\346\212\236\344\270\255\343\201\256\350\241\250\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationChangePhaseForm: public Ui_IntegrationChangePhaseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONCHANGEPHASEFORM_H
