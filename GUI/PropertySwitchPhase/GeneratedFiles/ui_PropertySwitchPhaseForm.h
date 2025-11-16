/********************************************************************************
** Form generated from reading UI file 'PropertySwitchPhaseForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYSWITCHPHASEFORM_H
#define UI_PROPERTYSWITCHPHASEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertySwitchPhaseForm
{
public:
    QTableWidget *tableWidgetPhaseList;
    QPushButton *pushButtonAddPhase;
    QPushButton *pushButtonDelPhase;
    QPushButton *pushButtonGoUp;
    QPushButton *pushButtonGoDown;
    QTableWidget *tableWidgetMarkList;
    QLabel *label;
    QLabel *label_2;
    QToolButton *toolButtonCapture;
    QLabel *label_CaptureNo;
    QLabel *label_4;
    QPushButton *pushButtonShowMatching;
    QPushButton *pushButtonAutoGeneration;
    QPushButton *pushButtonDeleteAll;

    void setupUi(GUIFormBase *PropertySwitchPhaseForm)
    {
        if (PropertySwitchPhaseForm->objectName().isEmpty())
            PropertySwitchPhaseForm->setObjectName("PropertySwitchPhaseForm");
        PropertySwitchPhaseForm->resize(400, 700);
        tableWidgetPhaseList = new QTableWidget(PropertySwitchPhaseForm);
        if (tableWidgetPhaseList->columnCount() < 2)
            tableWidgetPhaseList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPhaseList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPhaseList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidgetPhaseList->rowCount() < 1)
            tableWidgetPhaseList->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPhaseList->setVerticalHeaderItem(0, __qtablewidgetitem2);
        tableWidgetPhaseList->setObjectName("tableWidgetPhaseList");
        tableWidgetPhaseList->setGeometry(QRect(10, 100, 381, 291));
        tableWidgetPhaseList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPhaseList->setSelectionBehavior(QAbstractItemView::SelectItems);
        pushButtonAddPhase = new QPushButton(PropertySwitchPhaseForm);
        pushButtonAddPhase->setObjectName("pushButtonAddPhase");
        pushButtonAddPhase->setGeometry(QRect(10, 400, 121, 34));
        pushButtonDelPhase = new QPushButton(PropertySwitchPhaseForm);
        pushButtonDelPhase->setObjectName("pushButtonDelPhase");
        pushButtonDelPhase->setGeometry(QRect(271, 400, 121, 34));
        pushButtonGoUp = new QPushButton(PropertySwitchPhaseForm);
        pushButtonGoUp->setObjectName("pushButtonGoUp");
        pushButtonGoUp->setGeometry(QRect(160, 400, 41, 34));
        pushButtonGoDown = new QPushButton(PropertySwitchPhaseForm);
        pushButtonGoDown->setObjectName("pushButtonGoDown");
        pushButtonGoDown->setGeometry(QRect(210, 400, 41, 34));
        tableWidgetMarkList = new QTableWidget(PropertySwitchPhaseForm);
        if (tableWidgetMarkList->columnCount() < 4)
            tableWidgetMarkList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetMarkList->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        tableWidgetMarkList->setObjectName("tableWidgetMarkList");
        tableWidgetMarkList->setGeometry(QRect(10, 520, 381, 171));
        tableWidgetMarkList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetMarkList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(PropertySwitchPhaseForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 490, 381, 31));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(PropertySwitchPhaseForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 381, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        toolButtonCapture = new QToolButton(PropertySwitchPhaseForm);
        toolButtonCapture->setObjectName("toolButtonCapture");
        toolButtonCapture->setGeometry(QRect(10, 30, 161, 31));
        toolButtonCapture->setCheckable(true);
        label_CaptureNo = new QLabel(PropertySwitchPhaseForm);
        label_CaptureNo->setObjectName("label_CaptureNo");
        label_CaptureNo->setGeometry(QRect(210, 30, 51, 31));
        label_CaptureNo->setFrameShape(QFrame::Panel);
        label_CaptureNo->setFrameShadow(QFrame::Sunken);
        label_CaptureNo->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(PropertySwitchPhaseForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(270, 30, 121, 31));
        pushButtonShowMatching = new QPushButton(PropertySwitchPhaseForm);
        pushButtonShowMatching->setObjectName("pushButtonShowMatching");
        pushButtonShowMatching->setGeometry(QRect(10, 60, 161, 34));
        pushButtonAutoGeneration = new QPushButton(PropertySwitchPhaseForm);
        pushButtonAutoGeneration->setObjectName("pushButtonAutoGeneration");
        pushButtonAutoGeneration->setGeometry(QRect(10, 440, 151, 34));
        pushButtonDeleteAll = new QPushButton(PropertySwitchPhaseForm);
        pushButtonDeleteAll->setObjectName("pushButtonDeleteAll");
        pushButtonDeleteAll->setGeometry(QRect(170, 440, 221, 34));

        retranslateUi(PropertySwitchPhaseForm);

        QMetaObject::connectSlotsByName(PropertySwitchPhaseForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertySwitchPhaseForm)
    {
        PropertySwitchPhaseForm->setWindowTitle(QCoreApplication::translate("PropertySwitchPhaseForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPhaseList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPhaseList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Page0", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPhaseList->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Phase0", nullptr));
        pushButtonAddPhase->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Add phase", nullptr));
        pushButtonDelPhase->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Delete phase", nullptr));
        pushButtonGoUp->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "\342\206\221", nullptr));
        pushButtonGoDown->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "\342\206\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMarkList->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetMarkList->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetMarkList->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "SearchDot", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetMarkList->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Matching", nullptr));
        label->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Matching mark", nullptr));
        label_2->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "\346\244\234\346\237\273\347\224\273\345\203\217\343\202\222Phase\343\201\256\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\253\343\201\231\343\202\213", nullptr));
        toolButtonCapture->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "1\347\225\252\347\233\256\343\201\213\343\202\211\346\222\256\345\275\261", nullptr));
        label_CaptureNo->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "nn", nullptr));
        label_4->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "\347\217\276\345\234\250\343\201\256\347\225\252\345\217\267", nullptr));
        pushButtonShowMatching->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "\344\270\200\350\207\264\347\216\207\343\201\256\350\241\250\347\244\272", nullptr));
        pushButtonAutoGeneration->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Auto generation", nullptr));
        pushButtonDeleteAll->setText(QCoreApplication::translate("PropertySwitchPhaseForm", "Delete all mark in all phases", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertySwitchPhaseForm: public Ui_PropertySwitchPhaseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYSWITCHPHASEFORM_H
