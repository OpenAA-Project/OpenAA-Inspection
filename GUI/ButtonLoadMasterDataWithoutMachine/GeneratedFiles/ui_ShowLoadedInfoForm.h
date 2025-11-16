/********************************************************************************
** Form generated from reading UI file 'ShowLoadedInfoForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWLOADEDINFOFORM_H
#define UI_SHOWLOADEDINFOFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowLoadedInfoFormClass
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonOK;
    QFrame *frame;
    QToolButton *toolButtonByPage;
    QToolButton *toolButtonByName;

    void setupUi(QWidget *ShowLoadedInfoFormClass)
    {
        if (ShowLoadedInfoFormClass->objectName().isEmpty())
            ShowLoadedInfoFormClass->setObjectName("ShowLoadedInfoFormClass");
        ShowLoadedInfoFormClass->resize(463, 711);
        tableWidget = new QTableWidget(ShowLoadedInfoFormClass);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 50, 461, 611));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonOK = new QPushButton(ShowLoadedInfoFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(160, 670, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        frame = new QFrame(ShowLoadedInfoFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(100, 0, 271, 51));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        toolButtonByPage = new QToolButton(frame);
        toolButtonByPage->setObjectName("toolButtonByPage");
        toolButtonByPage->setGeometry(QRect(20, 10, 111, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SortNumber.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonByPage->setIcon(icon1);
        toolButtonByPage->setCheckable(true);
        toolButtonByPage->setChecked(true);
        toolButtonByPage->setAutoExclusive(true);
        toolButtonByPage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButtonByName = new QToolButton(frame);
        toolButtonByName->setObjectName("toolButtonByName");
        toolButtonByName->setGeometry(QRect(140, 10, 111, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/SortText.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonByName->setIcon(icon2);
        toolButtonByName->setCheckable(true);
        toolButtonByName->setAutoExclusive(true);
        toolButtonByName->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        retranslateUi(ShowLoadedInfoFormClass);

        QMetaObject::connectSlotsByName(ShowLoadedInfoFormClass);
    } // setupUi

    void retranslateUi(QWidget *ShowLoadedInfoFormClass)
    {
        ShowLoadedInfoFormClass->setWindowTitle(QCoreApplication::translate("ShowLoadedInfoFormClass", "ShowLoadedInfoForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowLoadedInfoFormClass", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowLoadedInfoFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowLoadedInfoFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowLoadedInfoFormClass", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ShowLoadedInfoFormClass", "State", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ShowLoadedInfoFormClass", "OK", nullptr));
        toolButtonByPage->setText(QCoreApplication::translate("ShowLoadedInfoFormClass", "Sort by Page", nullptr));
        toolButtonByName->setText(QCoreApplication::translate("ShowLoadedInfoFormClass", "Sort by Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowLoadedInfoFormClass: public Ui_ShowLoadedInfoFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWLOADEDINFOFORM_H
