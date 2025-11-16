/********************************************************************************
** Form generated from reading UI file 'ListHistorySyncForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTHISTORYSYNCFORM_H
#define UI_LISTHISTORYSYNCFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListHistorySyncFormClass
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *labelOK;
    QLabel *label_6;
    QLabel *labelNG;
    QLabel *label_3;
    QLabel *labelSUM;
    QPushButton *ButtonReset;
    QTableWidget *tableWidgetHistory;

    void setupUi(GUIFormBase *ListHistorySyncFormClass)
    {
        if (ListHistorySyncFormClass->objectName().isEmpty())
            ListHistorySyncFormClass->setObjectName("ListHistorySyncFormClass");
        ListHistorySyncFormClass->resize(254, 361);
        frame = new QFrame(ListHistorySyncFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 310, 251, 41));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 61, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelOK = new QLabel(frame);
        labelOK->setObjectName("labelOK");
        labelOK->setGeometry(QRect(70, 0, 51, 20));
        labelOK->setFont(font);
        labelOK->setFrameShape(QFrame::Panel);
        labelOK->setFrameShadow(QFrame::Sunken);
        labelOK->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 20, 61, 20));
        label_6->setFont(font);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelNG = new QLabel(frame);
        labelNG->setObjectName("labelNG");
        labelNG->setGeometry(QRect(70, 20, 51, 20));
        labelNG->setFont(font);
        labelNG->setFrameShape(QFrame::Panel);
        labelNG->setFrameShadow(QFrame::Sunken);
        labelNG->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 0, 61, 20));
        label_3->setFont(font);
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelSUM = new QLabel(frame);
        labelSUM->setObjectName("labelSUM");
        labelSUM->setGeometry(QRect(190, 0, 51, 20));
        labelSUM->setFont(font);
        labelSUM->setFrameShape(QFrame::Panel);
        labelSUM->setFrameShadow(QFrame::Sunken);
        labelSUM->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonReset = new QPushButton(frame);
        ButtonReset->setObjectName("ButtonReset");
        ButtonReset->setGeometry(QRect(140, 20, 91, 21));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Reload.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonReset->setIcon(icon);
        tableWidgetHistory = new QTableWidget(ListHistorySyncFormClass);
        if (tableWidgetHistory->columnCount() < 4)
            tableWidgetHistory->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetHistory->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetHistory->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetHistory->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetHistory->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetHistory->setObjectName("tableWidgetHistory");
        tableWidgetHistory->setGeometry(QRect(0, 0, 251, 311));

        retranslateUi(ListHistorySyncFormClass);

        QMetaObject::connectSlotsByName(ListHistorySyncFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ListHistorySyncFormClass)
    {
        ListHistorySyncFormClass->setWindowTitle(QCoreApplication::translate("ListHistorySyncFormClass", "ListHistorySyncForm", nullptr));
        label->setText(QCoreApplication::translate("ListHistorySyncFormClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:12pt; font-weight:600; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:400; color:#008000;\">OK</span></p></body></html>", nullptr));
        labelOK->setText(QCoreApplication::translate("ListHistorySyncFormClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:12pt; font-weight:600; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:400;\">100</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("ListHistorySyncFormClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:12pt; font-weight:600; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:400; color:#ff0000;\">NG</span></p></body></html>", nullptr));
        labelNG->setText(QCoreApplication::translate("ListHistorySyncFormClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:12pt; font-weight:600; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:400;\">100</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("ListHistorySyncFormClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:12pt; font-weight:600; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:400;\">SUM</span></p></body></html>", nullptr));
        labelSUM->setText(QCoreApplication::translate("ListHistorySyncFormClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:12pt; font-weight:600; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:400;\">200</span></p></body></html>", nullptr));
        ButtonReset->setText(QCoreApplication::translate("ListHistorySyncFormClass", "Reset", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetHistory->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ListHistorySyncFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetHistory->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ListHistorySyncFormClass", "Date/Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetHistory->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ListHistorySyncFormClass", "NG", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetHistory->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ListHistorySyncFormClass", "SV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListHistorySyncFormClass: public Ui_ListHistorySyncFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTHISTORYSYNCFORM_H
