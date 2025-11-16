/********************************************************************************
** Form generated from reading UI file 'RuleConditionalDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULECONDITIONALDIALOG_H
#define UI_RULECONDITIONALDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_RuleConditionalDialog
{
public:
    QPushButton *pushButtonCancel;
    QFrame *frame;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEditName;
    QLineEdit *lineEditRemark;
    QCheckBox *checkBoxConclusion;
    QPushButton *pushButtonOK;
    QFrame *frame_2;
    QPushButton *pushButtonDelete;
    QTableWidget *tableWidget;
    QComboBox *comboBoxOutputOK;
    QLabel *label_8;
    QSpinBox *spinBoxOutputErrorCode;
    QLabel *label_10;
    QPushButton *pushButtonInsertNew;
    QLabel *label_9;
    QPushButton *pushButtonModify;
    QLabel *label;
    QListWidget *listWidgetCondition;
    QLabel *label_11;
    QCheckBox *checkBoxNGOthers;

    void setupUi(QDialog *RuleConditionalDialog)
    {
        if (RuleConditionalDialog->objectName().isEmpty())
            RuleConditionalDialog->setObjectName("RuleConditionalDialog");
        RuleConditionalDialog->resize(554, 648);
        pushButtonCancel = new QPushButton(RuleConditionalDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(280, 590, 93, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        frame = new QFrame(RuleConditionalDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(120, 480, 261, 101));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 61, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 40, 61, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        lineEditName = new QLineEdit(frame);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(80, 10, 171, 21));
        lineEditRemark = new QLineEdit(frame);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(80, 40, 171, 21));
        checkBoxConclusion = new QCheckBox(frame);
        checkBoxConclusion->setObjectName("checkBoxConclusion");
        checkBoxConclusion->setGeometry(QRect(10, 70, 231, 19));
        pushButtonOK = new QPushButton(RuleConditionalDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(130, 590, 93, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        frame_2 = new QFrame(RuleConditionalDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(180, 20, 361, 441));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        pushButtonDelete = new QPushButton(frame_2);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(290, 400, 61, 28));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon2);
        tableWidget = new QTableWidget(frame_2);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 341, 251));
        comboBoxOutputOK = new QComboBox(frame_2);
        comboBoxOutputOK->addItem(QString());
        comboBoxOutputOK->addItem(QString());
        comboBoxOutputOK->setObjectName("comboBoxOutputOK");
        comboBoxOutputOK->setGeometry(QRect(100, 360, 91, 22));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(100, 340, 91, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        spinBoxOutputErrorCode = new QSpinBox(frame_2);
        spinBoxOutputErrorCode->setObjectName("spinBoxOutputErrorCode");
        spinBoxOutputErrorCode->setGeometry(QRect(210, 360, 101, 22));
        spinBoxOutputErrorCode->setMinimum(-32768);
        spinBoxOutputErrorCode->setMaximum(32767);
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 360, 71, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter);
        pushButtonInsertNew = new QPushButton(frame_2);
        pushButtonInsertNew->setObjectName("pushButtonInsertNew");
        pushButtonInsertNew->setGeometry(QRect(10, 400, 93, 28));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonInsertNew->setIcon(icon3);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(210, 340, 101, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        pushButtonModify = new QPushButton(frame_2);
        pushButtonModify->setObjectName("pushButtonModify");
        pushButtonModify->setGeometry(QRect(150, 400, 93, 28));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonModify->setIcon(icon4);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 270, 341, 21));
        listWidgetCondition = new QListWidget(RuleConditionalDialog);
        listWidgetCondition->setObjectName("listWidgetCondition");
        listWidgetCondition->setGeometry(QRect(10, 40, 161, 391));
        label_11 = new QLabel(RuleConditionalDialog);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 20, 161, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter);
        checkBoxNGOthers = new QCheckBox(RuleConditionalDialog);
        checkBoxNGOthers->setObjectName("checkBoxNGOthers");
        checkBoxNGOthers->setGeometry(QRect(10, 440, 151, 19));

        retranslateUi(RuleConditionalDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(RuleConditionalDialog);
    } // setupUi

    void retranslateUi(QDialog *RuleConditionalDialog)
    {
        RuleConditionalDialog->setWindowTitle(QCoreApplication::translate("RuleConditionalDialog", "Rule Conditional", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RuleConditionalDialog", "Cancel", nullptr));
        label_6->setText(QCoreApplication::translate("RuleConditionalDialog", "Name", nullptr));
        label_7->setText(QCoreApplication::translate("RuleConditionalDialog", "Remark", nullptr));
        checkBoxConclusion->setText(QCoreApplication::translate("RuleConditionalDialog", "Conclusion", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RuleConditionalDialog", "OK", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("RuleConditionalDialog", "Delete", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RuleConditionalDialog", "IN", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RuleConditionalDialog", "Result", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("RuleConditionalDialog", "Error", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("RuleConditionalDialog", "Condition", nullptr));
        comboBoxOutputOK->setItemText(0, QCoreApplication::translate("RuleConditionalDialog", "OK", nullptr));
        comboBoxOutputOK->setItemText(1, QCoreApplication::translate("RuleConditionalDialog", "NG", nullptr));

        label_8->setText(QCoreApplication::translate("RuleConditionalDialog", "Result", nullptr));
        label_10->setText(QCoreApplication::translate("RuleConditionalDialog", "Output", nullptr));
        pushButtonInsertNew->setText(QCoreApplication::translate("RuleConditionalDialog", "Insert new", nullptr));
        label_9->setText(QCoreApplication::translate("RuleConditionalDialog", "Error", nullptr));
        pushButtonModify->setText(QCoreApplication::translate("RuleConditionalDialog", "Modify", nullptr));
        label->setText(QCoreApplication::translate("RuleConditionalDialog", "Condition  0:Ignore ,1:Equal ,2:Larger ,3:Smaller ", nullptr));
        label_11->setText(QCoreApplication::translate("RuleConditionalDialog", "Condition", nullptr));
        checkBoxNGOthers->setText(QCoreApplication::translate("RuleConditionalDialog", "NG for all others", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RuleConditionalDialog: public Ui_RuleConditionalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULECONDITIONALDIALOG_H
