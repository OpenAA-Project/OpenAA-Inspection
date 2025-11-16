/********************************************************************************
** Form generated from reading UI file 'ShowCurrentOpinionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWCURRENTOPINIONFORM_H
#define UI_SHOWCURRENTOPINIONFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ShowCurrentOpinionFormClass
{
public:
    QTableWidget *tableWidgetGUI;
    QListWidget *listWidgetMode;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonUpdate;
    QListWidget *listWidgetCommentOpinionList;
    QFrame *frame_3;
    QLabel *label_5;
    QTextEdit *textEditCommentNow;

    void setupUi(GUIFormBase *ShowCurrentOpinionFormClass)
    {
        if (ShowCurrentOpinionFormClass->objectName().isEmpty())
            ShowCurrentOpinionFormClass->setObjectName("ShowCurrentOpinionFormClass");
        ShowCurrentOpinionFormClass->resize(543, 380);
        tableWidgetGUI = new QTableWidget(ShowCurrentOpinionFormClass);
        if (tableWidgetGUI->columnCount() < 3)
            tableWidgetGUI->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGUI->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGUI->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGUI->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetGUI->setObjectName("tableWidgetGUI");
        tableWidgetGUI->setGeometry(QRect(0, 20, 321, 192));
        tableWidgetGUI->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetGUI->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetMode = new QListWidget(ShowCurrentOpinionFormClass);
        listWidgetMode->setObjectName("listWidgetMode");
        listWidgetMode->setGeometry(QRect(380, 20, 151, 192));
        label = new QLabel(ShowCurrentOpinionFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(-1, 0, 321, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(ShowCurrentOpinionFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(330, 0, 201, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonUpdate = new QPushButton(ShowCurrentOpinionFormClass);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(230, 350, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);
        listWidgetCommentOpinionList = new QListWidget(ShowCurrentOpinionFormClass);
        listWidgetCommentOpinionList->setObjectName("listWidgetCommentOpinionList");
        listWidgetCommentOpinionList->setGeometry(QRect(330, 20, 51, 192));
        frame_3 = new QFrame(ShowCurrentOpinionFormClass);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(0, 220, 531, 121));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 511, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        textEditCommentNow = new QTextEdit(frame_3);
        textEditCommentNow->setObjectName("textEditCommentNow");
        textEditCommentNow->setGeometry(QRect(10, 30, 511, 81));

        retranslateUi(ShowCurrentOpinionFormClass);

        QMetaObject::connectSlotsByName(ShowCurrentOpinionFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ShowCurrentOpinionFormClass)
    {
        ShowCurrentOpinionFormClass->setWindowTitle(QCoreApplication::translate("ShowCurrentOpinionFormClass", "ShowCurrentOpinionForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGUI->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowCurrentOpinionFormClass", "DLLRoot", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGUI->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowCurrentOpinionFormClass", "DLLName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGUI->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowCurrentOpinionFormClass", "InstName", nullptr));
        label->setText(QCoreApplication::translate("ShowCurrentOpinionFormClass", "Where", nullptr));
        label_2->setText(QCoreApplication::translate("ShowCurrentOpinionFormClass", "Object path", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("ShowCurrentOpinionFormClass", "Update", nullptr));
        label_5->setText(QCoreApplication::translate("ShowCurrentOpinionFormClass", "\343\202\263\343\203\241\343\203\263\343\203\210\343\203\273\343\203\241\343\203\203\343\202\273\343\203\274\343\202\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowCurrentOpinionFormClass: public Ui_ShowCurrentOpinionFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCURRENTOPINIONFORM_H
