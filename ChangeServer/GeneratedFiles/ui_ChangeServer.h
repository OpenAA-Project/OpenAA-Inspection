/********************************************************************************
** Form generated from reading UI file 'ChangeServer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGESERVER_H
#define UI_CHANGESERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeServerClass
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidgetServers;
    QFrame *frame;
    QLineEdit *lineEditRemark;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEditServerName;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonEdit;

    void setupUi(QMainWindow *ChangeServerClass)
    {
        if (ChangeServerClass->objectName().isEmpty())
            ChangeServerClass->setObjectName("ChangeServerClass");
        ChangeServerClass->resize(364, 393);
        centralWidget = new QWidget(ChangeServerClass);
        centralWidget->setObjectName("centralWidget");
        tableWidgetServers = new QTableWidget(centralWidget);
        if (tableWidgetServers->columnCount() < 2)
            tableWidgetServers->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetServers->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetServers->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetServers->setObjectName("tableWidgetServers");
        tableWidgetServers->setGeometry(QRect(10, 110, 341, 192));
        tableWidgetServers->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetServers->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 30, 341, 61));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        lineEditRemark = new QLineEdit(frame);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(140, 30, 191, 20));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(192, 192, 192, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditRemark->setPalette(palette);
        lineEditRemark->setReadOnly(true);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 10, 191, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 131, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditServerName = new QLineEdit(frame);
        lineEditServerName->setObjectName("lineEditServerName");
        lineEditServerName->setGeometry(QRect(10, 30, 131, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditServerName->setPalette(palette1);
        lineEditServerName->setReadOnly(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 341, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(140, 350, 91, 31));
        pushButtonSelect = new QPushButton(centralWidget);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(50, 310, 91, 31));
        pushButtonEdit = new QPushButton(centralWidget);
        pushButtonEdit->setObjectName("pushButtonEdit");
        pushButtonEdit->setGeometry(QRect(220, 310, 91, 31));
        ChangeServerClass->setCentralWidget(centralWidget);

        retranslateUi(ChangeServerClass);

        QMetaObject::connectSlotsByName(ChangeServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChangeServerClass)
    {
        ChangeServerClass->setWindowTitle(QCoreApplication::translate("ChangeServerClass", "ChangeServer", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetServers->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ChangeServerClass", "Server Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetServers->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ChangeServerClass", "Remark", nullptr));
        label_2->setText(QCoreApplication::translate("ChangeServerClass", "Remark", nullptr));
        label->setText(QCoreApplication::translate("ChangeServerClass", "Server Name", nullptr));
        label_3->setText(QCoreApplication::translate("ChangeServerClass", "Current setting", nullptr));
        pushButton->setText(QCoreApplication::translate("ChangeServerClass", "Close", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("ChangeServerClass", "Select", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("ChangeServerClass", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeServerClass: public Ui_ChangeServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGESERVER_H
