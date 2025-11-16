/********************************************************************************
** Form generated from reading UI file 'SetCommandDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETCOMMANDDIALOG_H
#define UI_SETCOMMANDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SetCommandDialog
{
public:
    QTableWidget *tableWidgetComponent;
    QTableWidget *tableWidgetCommand;
    QFrame *frame;
    QLineEdit *lineEditCommand;
    QLineEdit *lineEditArg1;
    QLineEdit *lineEditArg2;
    QLineEdit *lineEditArg3;
    QLineEdit *lineEditArg4;
    QLineEdit *lineEditArg5;
    QLineEdit *lineEditArg8;
    QLineEdit *lineEditArg6;
    QLineEdit *lineEditArg7;
    QLabel *label;
    QLabel *labelArg1;
    QLabel *labelArg2;
    QLabel *labelArg3;
    QLabel *labelArg4;
    QLabel *labelArg5;
    QLabel *labelArg6;
    QLabel *labelArg7;
    QLabel *labelArg8;
    QLineEdit *lineEditArg9;
    QLabel *labelArg9;
    QLabel *labelArg10;
    QLineEdit *lineEditArg10;
    QLineEdit *lineEditArg7_Value;
    QLineEdit *lineEditArg5_Value;
    QLineEdit *lineEditArg3_Value;
    QLineEdit *lineEditArg8_Value;
    QLineEdit *lineEditArg9_Value;
    QLineEdit *lineEditArg6_Value;
    QLineEdit *lineEditArg1_Value;
    QLineEdit *lineEditArg10_Value;
    QLineEdit *lineEditArg4_Value;
    QLineEdit *lineEditArg2_Value;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SetCommandDialog)
    {
        if (SetCommandDialog->objectName().isEmpty())
            SetCommandDialog->setObjectName("SetCommandDialog");
        SetCommandDialog->resize(852, 737);
        tableWidgetComponent = new QTableWidget(SetCommandDialog);
        if (tableWidgetComponent->columnCount() < 2)
            tableWidgetComponent->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetComponent->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetComponent->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetComponent->setObjectName("tableWidgetComponent");
        tableWidgetComponent->setGeometry(QRect(10, 20, 291, 641));
        tableWidgetComponent->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetComponent->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetCommand = new QTableWidget(SetCommandDialog);
        if (tableWidgetCommand->columnCount() < 2)
            tableWidgetCommand->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetCommand->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetCommand->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetCommand->setObjectName("tableWidgetCommand");
        tableWidgetCommand->setGeometry(QRect(320, 20, 521, 281));
        tableWidgetCommand->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetCommand->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(SetCommandDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(320, 310, 521, 351));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        lineEditCommand = new QLineEdit(frame);
        lineEditCommand->setObjectName("lineEditCommand");
        lineEditCommand->setGeometry(QRect(110, 10, 301, 25));
        lineEditCommand->setReadOnly(true);
        lineEditArg1 = new QLineEdit(frame);
        lineEditArg1->setObjectName("lineEditArg1");
        lineEditArg1->setGeometry(QRect(110, 40, 231, 25));
        lineEditArg1->setReadOnly(true);
        lineEditArg2 = new QLineEdit(frame);
        lineEditArg2->setObjectName("lineEditArg2");
        lineEditArg2->setGeometry(QRect(110, 70, 231, 25));
        lineEditArg2->setReadOnly(true);
        lineEditArg3 = new QLineEdit(frame);
        lineEditArg3->setObjectName("lineEditArg3");
        lineEditArg3->setGeometry(QRect(110, 100, 231, 25));
        lineEditArg3->setReadOnly(true);
        lineEditArg4 = new QLineEdit(frame);
        lineEditArg4->setObjectName("lineEditArg4");
        lineEditArg4->setGeometry(QRect(110, 130, 231, 25));
        lineEditArg4->setReadOnly(true);
        lineEditArg5 = new QLineEdit(frame);
        lineEditArg5->setObjectName("lineEditArg5");
        lineEditArg5->setGeometry(QRect(110, 160, 231, 25));
        lineEditArg5->setReadOnly(true);
        lineEditArg8 = new QLineEdit(frame);
        lineEditArg8->setObjectName("lineEditArg8");
        lineEditArg8->setGeometry(QRect(110, 250, 231, 25));
        lineEditArg8->setReadOnly(true);
        lineEditArg6 = new QLineEdit(frame);
        lineEditArg6->setObjectName("lineEditArg6");
        lineEditArg6->setGeometry(QRect(110, 190, 231, 25));
        lineEditArg6->setReadOnly(true);
        lineEditArg7 = new QLineEdit(frame);
        lineEditArg7->setObjectName("lineEditArg7");
        lineEditArg7->setGeometry(QRect(110, 220, 231, 25));
        lineEditArg7->setReadOnly(true);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 25));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        labelArg1 = new QLabel(frame);
        labelArg1->setObjectName("labelArg1");
        labelArg1->setGeometry(QRect(10, 40, 91, 25));
        labelArg1->setFrameShape(QFrame::Panel);
        labelArg1->setFrameShadow(QFrame::Sunken);
        labelArg1->setAlignment(Qt::AlignCenter);
        labelArg2 = new QLabel(frame);
        labelArg2->setObjectName("labelArg2");
        labelArg2->setGeometry(QRect(10, 70, 91, 25));
        labelArg2->setFrameShape(QFrame::Panel);
        labelArg2->setFrameShadow(QFrame::Sunken);
        labelArg2->setAlignment(Qt::AlignCenter);
        labelArg3 = new QLabel(frame);
        labelArg3->setObjectName("labelArg3");
        labelArg3->setGeometry(QRect(10, 100, 91, 25));
        labelArg3->setFrameShape(QFrame::Panel);
        labelArg3->setFrameShadow(QFrame::Sunken);
        labelArg3->setAlignment(Qt::AlignCenter);
        labelArg4 = new QLabel(frame);
        labelArg4->setObjectName("labelArg4");
        labelArg4->setGeometry(QRect(10, 130, 91, 25));
        labelArg4->setFrameShape(QFrame::Panel);
        labelArg4->setFrameShadow(QFrame::Sunken);
        labelArg4->setAlignment(Qt::AlignCenter);
        labelArg5 = new QLabel(frame);
        labelArg5->setObjectName("labelArg5");
        labelArg5->setGeometry(QRect(10, 160, 91, 25));
        labelArg5->setFrameShape(QFrame::Panel);
        labelArg5->setFrameShadow(QFrame::Sunken);
        labelArg5->setAlignment(Qt::AlignCenter);
        labelArg6 = new QLabel(frame);
        labelArg6->setObjectName("labelArg6");
        labelArg6->setGeometry(QRect(10, 190, 91, 25));
        labelArg6->setFrameShape(QFrame::Panel);
        labelArg6->setFrameShadow(QFrame::Sunken);
        labelArg6->setAlignment(Qt::AlignCenter);
        labelArg7 = new QLabel(frame);
        labelArg7->setObjectName("labelArg7");
        labelArg7->setGeometry(QRect(10, 220, 91, 25));
        labelArg7->setFrameShape(QFrame::Panel);
        labelArg7->setFrameShadow(QFrame::Sunken);
        labelArg7->setAlignment(Qt::AlignCenter);
        labelArg8 = new QLabel(frame);
        labelArg8->setObjectName("labelArg8");
        labelArg8->setGeometry(QRect(10, 250, 91, 25));
        labelArg8->setFrameShape(QFrame::Panel);
        labelArg8->setFrameShadow(QFrame::Sunken);
        labelArg8->setAlignment(Qt::AlignCenter);
        lineEditArg9 = new QLineEdit(frame);
        lineEditArg9->setObjectName("lineEditArg9");
        lineEditArg9->setGeometry(QRect(110, 280, 231, 25));
        lineEditArg9->setReadOnly(true);
        labelArg9 = new QLabel(frame);
        labelArg9->setObjectName("labelArg9");
        labelArg9->setGeometry(QRect(10, 280, 91, 25));
        labelArg9->setFrameShape(QFrame::Panel);
        labelArg9->setFrameShadow(QFrame::Sunken);
        labelArg9->setAlignment(Qt::AlignCenter);
        labelArg10 = new QLabel(frame);
        labelArg10->setObjectName("labelArg10");
        labelArg10->setGeometry(QRect(10, 310, 91, 25));
        labelArg10->setFrameShape(QFrame::Panel);
        labelArg10->setFrameShadow(QFrame::Sunken);
        labelArg10->setAlignment(Qt::AlignCenter);
        lineEditArg10 = new QLineEdit(frame);
        lineEditArg10->setObjectName("lineEditArg10");
        lineEditArg10->setGeometry(QRect(110, 310, 231, 25));
        lineEditArg10->setReadOnly(true);
        lineEditArg7_Value = new QLineEdit(frame);
        lineEditArg7_Value->setObjectName("lineEditArg7_Value");
        lineEditArg7_Value->setGeometry(QRect(350, 220, 161, 26));
        lineEditArg5_Value = new QLineEdit(frame);
        lineEditArg5_Value->setObjectName("lineEditArg5_Value");
        lineEditArg5_Value->setGeometry(QRect(350, 160, 161, 26));
        lineEditArg3_Value = new QLineEdit(frame);
        lineEditArg3_Value->setObjectName("lineEditArg3_Value");
        lineEditArg3_Value->setGeometry(QRect(350, 100, 161, 26));
        lineEditArg8_Value = new QLineEdit(frame);
        lineEditArg8_Value->setObjectName("lineEditArg8_Value");
        lineEditArg8_Value->setGeometry(QRect(350, 250, 161, 26));
        lineEditArg9_Value = new QLineEdit(frame);
        lineEditArg9_Value->setObjectName("lineEditArg9_Value");
        lineEditArg9_Value->setGeometry(QRect(350, 280, 161, 26));
        lineEditArg6_Value = new QLineEdit(frame);
        lineEditArg6_Value->setObjectName("lineEditArg6_Value");
        lineEditArg6_Value->setGeometry(QRect(350, 190, 161, 26));
        lineEditArg1_Value = new QLineEdit(frame);
        lineEditArg1_Value->setObjectName("lineEditArg1_Value");
        lineEditArg1_Value->setGeometry(QRect(350, 40, 161, 26));
        lineEditArg10_Value = new QLineEdit(frame);
        lineEditArg10_Value->setObjectName("lineEditArg10_Value");
        lineEditArg10_Value->setGeometry(QRect(350, 310, 161, 26));
        lineEditArg4_Value = new QLineEdit(frame);
        lineEditArg4_Value->setObjectName("lineEditArg4_Value");
        lineEditArg4_Value->setGeometry(QRect(350, 130, 161, 26));
        lineEditArg2_Value = new QLineEdit(frame);
        lineEditArg2_Value->setObjectName("lineEditArg2_Value");
        lineEditArg2_Value->setGeometry(QRect(350, 70, 161, 26));
        pushButtonOK = new QPushButton(SetCommandDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(180, 680, 131, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(SetCommandDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(510, 680, 121, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(SetCommandDialog);

        QMetaObject::connectSlotsByName(SetCommandDialog);
    } // setupUi

    void retranslateUi(QDialog *SetCommandDialog)
    {
        SetCommandDialog->setWindowTitle(QCoreApplication::translate("SetCommandDialog", "Set command", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetComponent->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SetCommandDialog", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetComponent->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SetCommandDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetCommand->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SetCommandDialog", "Command", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetCommand->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SetCommandDialog", "Explain", nullptr));
        label->setText(QCoreApplication::translate("SetCommandDialog", "Command", nullptr));
        labelArg1->setText(QCoreApplication::translate("SetCommandDialog", "ARG 1", nullptr));
        labelArg2->setText(QCoreApplication::translate("SetCommandDialog", "ARG 2", nullptr));
        labelArg3->setText(QCoreApplication::translate("SetCommandDialog", "ARG 3", nullptr));
        labelArg4->setText(QCoreApplication::translate("SetCommandDialog", "ARG 4", nullptr));
        labelArg5->setText(QCoreApplication::translate("SetCommandDialog", "ARG 5", nullptr));
        labelArg6->setText(QCoreApplication::translate("SetCommandDialog", "ARG 6", nullptr));
        labelArg7->setText(QCoreApplication::translate("SetCommandDialog", "ARG 7", nullptr));
        labelArg8->setText(QCoreApplication::translate("SetCommandDialog", "ARG 8", nullptr));
        labelArg9->setText(QCoreApplication::translate("SetCommandDialog", "ARG 9", nullptr));
        labelArg10->setText(QCoreApplication::translate("SetCommandDialog", "ARG 10", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SetCommandDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SetCommandDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetCommandDialog: public Ui_SetCommandDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCOMMANDDIALOG_H
