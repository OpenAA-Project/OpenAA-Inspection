/********************************************************************************
** Form generated from reading UI file 'PropertyCheckEverydayForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYCHECKEVERYDAYFORM_H
#define UI_PROPERTYCHECKEVERYDAYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyCheckEverydayForm
{
public:
    QFrame *frame;
    QToolButton *toolButtonLight;
    QToolButton *toolButtonFocus;
    QStackedWidget *stackedWidget;
    QWidget *Light;
    QTableWidget *tableWidgetLight;
    QWidget *Focus;
    QTableWidget *tableWidgetFocus;
    QPushButton *pushButtonSave;

    void setupUi(GUIFormBase *PropertyCheckEverydayForm)
    {
        if (PropertyCheckEverydayForm->objectName().isEmpty())
            PropertyCheckEverydayForm->setObjectName("PropertyCheckEverydayForm");
        PropertyCheckEverydayForm->resize(400, 700);
        frame = new QFrame(PropertyCheckEverydayForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 381, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonLight = new QToolButton(frame);
        toolButtonLight->setObjectName("toolButtonLight");
        toolButtonLight->setGeometry(QRect(10, 10, 361, 81));
        toolButtonLight->setCheckable(true);
        toolButtonLight->setChecked(true);
        toolButtonLight->setAutoExclusive(true);
        toolButtonFocus = new QToolButton(frame);
        toolButtonFocus->setObjectName("toolButtonFocus");
        toolButtonFocus->setGeometry(QRect(10, 100, 361, 81));
        toolButtonFocus->setCheckable(true);
        toolButtonFocus->setChecked(false);
        toolButtonFocus->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(PropertyCheckEverydayForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 210, 381, 431));
        Light = new QWidget();
        Light->setObjectName("Light");
        tableWidgetLight = new QTableWidget(Light);
        if (tableWidgetLight->columnCount() < 6)
            tableWidgetLight->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLight->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidgetLight->setObjectName("tableWidgetLight");
        tableWidgetLight->setGeometry(QRect(0, 0, 371, 431));
        tableWidgetLight->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLight->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget->addWidget(Light);
        Focus = new QWidget();
        Focus->setObjectName("Focus");
        tableWidgetFocus = new QTableWidget(Focus);
        if (tableWidgetFocus->columnCount() < 5)
            tableWidgetFocus->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetFocus->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetFocus->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetFocus->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetFocus->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetFocus->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        tableWidgetFocus->setObjectName("tableWidgetFocus");
        tableWidgetFocus->setGeometry(QRect(0, 0, 371, 401));
        tableWidgetFocus->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetFocus->setSelectionBehavior(QAbstractItemView::SelectRows);
        stackedWidget->addWidget(Focus);
        pushButtonSave = new QPushButton(PropertyCheckEverydayForm);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(270, 650, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSave->setIcon(icon);

        retranslateUi(PropertyCheckEverydayForm);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PropertyCheckEverydayForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyCheckEverydayForm)
    {
        PropertyCheckEverydayForm->setWindowTitle(QCoreApplication::translate("PropertyCheckEverydayForm", "Property CheckEveryday", nullptr));
        toolButtonLight->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "Light", nullptr));
        toolButtonFocus->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "Focus", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLight->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLight->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLight->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLight->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "BrightHigh", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLight->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "BrightLow", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLight->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "Value", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetFocus->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetFocus->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetFocus->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetFocus->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetFocus->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "Value", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("PropertyCheckEverydayForm", "Save ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyCheckEverydayForm: public Ui_PropertyCheckEverydayForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYCHECKEVERYDAYFORM_H
