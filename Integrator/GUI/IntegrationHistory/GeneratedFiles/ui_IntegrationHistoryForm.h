/********************************************************************************
** Form generated from reading UI file 'IntegrationHistoryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATIONHISTORYFORM_H
#define UI_INTEGRATIONHISTORYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_IntegrationHistoryForm
{
public:
    QFrame *frame;
    QLabel *label_TitleTotal;
    QLabel *label_TitleOK;
    QLabel *label_TitleNG;
    QLabel *label_Total;
    QLabel *label_OK;
    QLabel *label_NG;
    QLabel *label_TitleTotal_2;
    QLabel *label_TMOut;
    QTableWidget *tableWidgetHistory;

    void setupUi(GUIFormBase *IntegrationHistoryForm)
    {
        if (IntegrationHistoryForm->objectName().isEmpty())
            IntegrationHistoryForm->setObjectName("IntegrationHistoryForm");
        IntegrationHistoryForm->resize(332, 419);
        frame = new QFrame(IntegrationHistoryForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 350, 331, 71));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_TitleTotal = new QLabel(frame);
        label_TitleTotal->setObjectName("label_TitleTotal");
        label_TitleTotal->setGeometry(QRect(10, 10, 61, 21));
        label_TitleTotal->setFrameShape(QFrame::Panel);
        label_TitleTotal->setFrameShadow(QFrame::Sunken);
        label_TitleOK = new QLabel(frame);
        label_TitleOK->setObjectName("label_TitleOK");
        label_TitleOK->setGeometry(QRect(180, 10, 51, 21));
        label_TitleOK->setFrameShape(QFrame::Panel);
        label_TitleOK->setFrameShadow(QFrame::Sunken);
        label_TitleNG = new QLabel(frame);
        label_TitleNG->setObjectName("label_TitleNG");
        label_TitleNG->setGeometry(QRect(180, 40, 51, 21));
        label_TitleNG->setFrameShape(QFrame::Panel);
        label_TitleNG->setFrameShadow(QFrame::Sunken);
        label_Total = new QLabel(frame);
        label_Total->setObjectName("label_Total");
        label_Total->setGeometry(QRect(70, 10, 81, 21));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        label_Total->setPalette(palette);
        label_Total->setAutoFillBackground(true);
        label_Total->setFrameShape(QFrame::Panel);
        label_Total->setFrameShadow(QFrame::Sunken);
        label_Total->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_OK = new QLabel(frame);
        label_OK->setObjectName("label_OK");
        label_OK->setGeometry(QRect(230, 10, 75, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        label_OK->setPalette(palette1);
        label_OK->setAutoFillBackground(true);
        label_OK->setFrameShape(QFrame::Panel);
        label_OK->setFrameShadow(QFrame::Sunken);
        label_OK->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_NG = new QLabel(frame);
        label_NG->setObjectName("label_NG");
        label_NG->setGeometry(QRect(230, 40, 75, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        label_NG->setPalette(palette2);
        label_NG->setAutoFillBackground(true);
        label_NG->setFrameShape(QFrame::Panel);
        label_NG->setFrameShadow(QFrame::Sunken);
        label_NG->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_TitleTotal_2 = new QLabel(frame);
        label_TitleTotal_2->setObjectName("label_TitleTotal_2");
        label_TitleTotal_2->setGeometry(QRect(10, 40, 61, 21));
        label_TitleTotal_2->setFrameShape(QFrame::Panel);
        label_TitleTotal_2->setFrameShadow(QFrame::Sunken);
        label_TMOut = new QLabel(frame);
        label_TMOut->setObjectName("label_TMOut");
        label_TMOut->setGeometry(QRect(70, 40, 81, 21));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        label_TMOut->setPalette(palette3);
        label_TMOut->setAutoFillBackground(true);
        label_TMOut->setFrameShape(QFrame::Panel);
        label_TMOut->setFrameShadow(QFrame::Sunken);
        label_TMOut->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tableWidgetHistory = new QTableWidget(IntegrationHistoryForm);
        if (tableWidgetHistory->columnCount() < 3)
            tableWidgetHistory->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetHistory->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetHistory->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetHistory->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetHistory->setObjectName("tableWidgetHistory");
        tableWidgetHistory->setGeometry(QRect(0, 0, 331, 351));
        tableWidgetHistory->setAutoFillBackground(false);
        tableWidgetHistory->setStyleSheet(QString::fromUtf8("QScrollBar:vertical { width: 100px; }"));
        tableWidgetHistory->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidgetHistory->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableWidgetHistory->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetHistory->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetHistory->verticalHeader()->setCascadingSectionResizes(false);
        tableWidgetHistory->verticalHeader()->setMinimumSectionSize(28);
        tableWidgetHistory->verticalHeader()->setDefaultSectionSize(32);
        tableWidgetHistory->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidgetHistory->verticalHeader()->setStretchLastSection(false);

        retranslateUi(IntegrationHistoryForm);

        QMetaObject::connectSlotsByName(IntegrationHistoryForm);
    } // setupUi

    void retranslateUi(GUIFormBase *IntegrationHistoryForm)
    {
        IntegrationHistoryForm->setWindowTitle(QCoreApplication::translate("IntegrationHistoryForm", "Form", nullptr));
        label_TitleTotal->setText(QCoreApplication::translate("IntegrationHistoryForm", "Total", nullptr));
        label_TitleOK->setText(QCoreApplication::translate("IntegrationHistoryForm", "OK", nullptr));
        label_TitleNG->setText(QCoreApplication::translate("IntegrationHistoryForm", "NG", nullptr));
        label_Total->setText(QCoreApplication::translate("IntegrationHistoryForm", "0", nullptr));
        label_OK->setText(QCoreApplication::translate("IntegrationHistoryForm", "0", nullptr));
        label_NG->setText(QCoreApplication::translate("IntegrationHistoryForm", "0", nullptr));
        label_TitleTotal_2->setText(QCoreApplication::translate("IntegrationHistoryForm", "TM", nullptr));
        label_TMOut->setText(QCoreApplication::translate("IntegrationHistoryForm", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetHistory->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("IntegrationHistoryForm", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetHistory->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("IntegrationHistoryForm", "A", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetHistory->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("IntegrationHistoryForm", "B", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntegrationHistoryForm: public Ui_IntegrationHistoryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATIONHISTORYFORM_H
