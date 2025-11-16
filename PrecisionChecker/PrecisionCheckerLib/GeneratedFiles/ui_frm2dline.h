/********************************************************************************
** Form generated from reading UI file 'frm2dline.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM2DLINE_H
#define UI_FRM2DLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frm2DLineClass
{
public:
    QPushButton *pushButton;
    QTableView *tableView;
    QDockWidget *dwShowGraph;
    QWidget *dockWidgetContents;
    QWidget *widget;
    QHBoxLayout *hboxLayout;
    QLabel *lblThreshold;
    QLineEdit *txtThreshold;

    void setupUi(QWidget *frm2DLineClass)
    {
        if (frm2DLineClass->objectName().isEmpty())
            frm2DLineClass->setObjectName("frm2DLineClass");
        frm2DLineClass->resize(1255, 954);
        pushButton = new QPushButton(frm2DLineClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1170, 910, 75, 23));
        tableView = new QTableView(frm2DLineClass);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(10, 10, 141, 881));
        dwShowGraph = new QDockWidget(frm2DLineClass);
        dwShowGraph->setObjectName("dwShowGraph");
        dwShowGraph->setGeometry(QRect(160, 10, 1081, 891));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        dwShowGraph->setWidget(dockWidgetContents);
        widget = new QWidget(frm2DLineClass);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(760, 910, 168, 22));
        hboxLayout = new QHBoxLayout(widget);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        lblThreshold = new QLabel(widget);
        lblThreshold->setObjectName("lblThreshold");

        hboxLayout->addWidget(lblThreshold);

        txtThreshold = new QLineEdit(widget);
        txtThreshold->setObjectName("txtThreshold");

        hboxLayout->addWidget(txtThreshold);


        retranslateUi(frm2DLineClass);

        QMetaObject::connectSlotsByName(frm2DLineClass);
    } // setupUi

    void retranslateUi(QWidget *frm2DLineClass)
    {
        frm2DLineClass->setWindowTitle(QCoreApplication::translate("frm2DLineClass", "frm2DLine", nullptr));
        pushButton->setText(QCoreApplication::translate("frm2DLineClass", "Close(&C)", nullptr));
        lblThreshold->setText(QCoreApplication::translate("frm2DLineClass", "Threshold", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frm2DLineClass: public Ui_frm2DLineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM2DLINE_H
