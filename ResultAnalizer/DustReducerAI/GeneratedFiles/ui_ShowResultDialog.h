/********************************************************************************
** Form generated from reading UI file 'ShowResultDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULTDIALOG_H
#define UI_SHOWRESULTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowResultDialog
{
public:
    QLabel *label;
    QTableWidget *tableWidgetResult;
    QLabel *label_2;
    QPushButton *pushButtonRegOK;
    QLabel *label_5;
    QLineEdit *lineEditCurrentComment;
    QPushButton *pushButtonRegNG;
    QPushButton *pushButtonLoadRegPack;
    QPushButton *pushButtonSaveRegPack;
    QPushButton *pushButtonClearRegPack;
    QPushButton *pushButtonClose;
    QLabel *label_6;
    QFrame *frame_3;
    QPushButton *pushButtonDeleteReg;
    QLabel *label_3;
    QPushButton *pushButtonChangeReg;
    QLabel *label_4;
    QLineEdit *lineEditRegComment;
    QComboBox *comboBoxJudge;
    QLabel *labelRegPanel;
    QLabel *labelCurrentPanel;

    void setupUi(QDialog *ShowResultDialog)
    {
        if (ShowResultDialog->objectName().isEmpty())
            ShowResultDialog->setObjectName("ShowResultDialog");
        ShowResultDialog->resize(963, 518);
        label = new QLabel(ShowResultDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 261, 18));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        tableWidgetResult = new QTableWidget(ShowResultDialog);
        if (tableWidgetResult->columnCount() < 4)
            tableWidgetResult->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetResult->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetResult->setObjectName("tableWidgetResult");
        tableWidgetResult->setGeometry(QRect(290, 30, 371, 401));
        tableWidgetResult->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetResult->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_2 = new QLabel(ShowResultDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(290, 10, 661, 18));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        pushButtonRegOK = new QPushButton(ShowResultDialog);
        pushButtonRegOK->setObjectName("pushButtonRegOK");
        pushButtonRegOK->setGeometry(QRect(100, 340, 112, 34));
        label_5 = new QLabel(ShowResultDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 300, 81, 31));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        lineEditCurrentComment = new QLineEdit(ShowResultDialog);
        lineEditCurrentComment->setObjectName("lineEditCurrentComment");
        lineEditCurrentComment->setGeometry(QRect(100, 300, 171, 31));
        pushButtonRegNG = new QPushButton(ShowResultDialog);
        pushButtonRegNG->setObjectName("pushButtonRegNG");
        pushButtonRegNG->setGeometry(QRect(100, 380, 112, 34));
        pushButtonLoadRegPack = new QPushButton(ShowResultDialog);
        pushButtonLoadRegPack->setObjectName("pushButtonLoadRegPack");
        pushButtonLoadRegPack->setGeometry(QRect(290, 470, 101, 34));
        pushButtonSaveRegPack = new QPushButton(ShowResultDialog);
        pushButtonSaveRegPack->setObjectName("pushButtonSaveRegPack");
        pushButtonSaveRegPack->setGeometry(QRect(400, 470, 101, 34));
        pushButtonClearRegPack = new QPushButton(ShowResultDialog);
        pushButtonClearRegPack->setObjectName("pushButtonClearRegPack");
        pushButtonClearRegPack->setGeometry(QRect(510, 470, 101, 34));
        pushButtonClose = new QPushButton(ShowResultDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(830, 470, 121, 34));
        label_6 = new QLabel(ShowResultDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(290, 450, 321, 18));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        frame_3 = new QFrame(ShowResultDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(670, 30, 281, 411));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        pushButtonDeleteReg = new QPushButton(frame_3);
        pushButtonDeleteReg->setObjectName("pushButtonDeleteReg");
        pushButtonDeleteReg->setGeometry(QRect(150, 370, 112, 34));
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 280, 81, 31));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonChangeReg = new QPushButton(frame_3);
        pushButtonChangeReg->setObjectName("pushButtonChangeReg");
        pushButtonChangeReg->setGeometry(QRect(30, 370, 111, 31));
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 320, 81, 31));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        lineEditRegComment = new QLineEdit(frame_3);
        lineEditRegComment->setObjectName("lineEditRegComment");
        lineEditRegComment->setGeometry(QRect(100, 280, 171, 31));
        comboBoxJudge = new QComboBox(frame_3);
        comboBoxJudge->addItem(QString());
        comboBoxJudge->addItem(QString());
        comboBoxJudge->setObjectName("comboBoxJudge");
        comboBoxJudge->setGeometry(QRect(100, 320, 171, 31));
        labelRegPanel = new QLabel(frame_3);
        labelRegPanel->setObjectName("labelRegPanel");
        labelRegPanel->setGeometry(QRect(10, 10, 256, 256));
        labelCurrentPanel = new QLabel(ShowResultDialog);
        labelCurrentPanel->setObjectName("labelCurrentPanel");
        labelCurrentPanel->setGeometry(QRect(20, 30, 256, 256));

        retranslateUi(ShowResultDialog);

        QMetaObject::connectSlotsByName(ShowResultDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowResultDialog)
    {
        ShowResultDialog->setWindowTitle(QCoreApplication::translate("ShowResultDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ShowResultDialog", "\347\217\276\345\234\250\347\224\273\345\203\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetResult->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowResultDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetResult->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowResultDialog", "Comment", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetResult->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ShowResultDialog", "\351\201\251\345\220\210\347\216\207", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetResult->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ShowResultDialog", "\345\210\206\351\241\236", nullptr));
        label_2->setText(QCoreApplication::translate("ShowResultDialog", "\347\231\273\351\214\262\347\224\273\345\203\217", nullptr));
        pushButtonRegOK->setText(QCoreApplication::translate("ShowResultDialog", "OK\347\231\273\351\214\262", nullptr));
        label_5->setText(QCoreApplication::translate("ShowResultDialog", "Comment", nullptr));
        pushButtonRegNG->setText(QCoreApplication::translate("ShowResultDialog", "NG\347\231\273\351\214\262", nullptr));
        pushButtonLoadRegPack->setText(QCoreApplication::translate("ShowResultDialog", "\350\252\255\350\276\274", nullptr));
        pushButtonSaveRegPack->setText(QCoreApplication::translate("ShowResultDialog", "\344\277\235\345\255\230", nullptr));
        pushButtonClearRegPack->setText(QCoreApplication::translate("ShowResultDialog", "\343\202\257\343\203\252\343\202\242", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowResultDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_6->setText(QCoreApplication::translate("ShowResultDialog", "\347\231\273\351\214\262\343\203\252\343\202\271\343\203\210", nullptr));
        pushButtonDeleteReg->setText(QCoreApplication::translate("ShowResultDialog", "\345\211\212\351\231\244", nullptr));
        label_3->setText(QCoreApplication::translate("ShowResultDialog", "Comment", nullptr));
        pushButtonChangeReg->setText(QCoreApplication::translate("ShowResultDialog", "\345\244\211\346\233\264", nullptr));
        label_4->setText(QCoreApplication::translate("ShowResultDialog", "\345\210\206\351\241\236", nullptr));
        comboBoxJudge->setItemText(0, QCoreApplication::translate("ShowResultDialog", "OK", nullptr));
        comboBoxJudge->setItemText(1, QCoreApplication::translate("ShowResultDialog", "NG", nullptr));

        labelRegPanel->setText(QString());
        labelCurrentPanel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ShowResultDialog: public Ui_ShowResultDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULTDIALOG_H
