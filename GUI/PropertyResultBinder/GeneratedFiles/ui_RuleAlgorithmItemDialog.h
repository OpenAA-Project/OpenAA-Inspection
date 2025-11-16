/********************************************************************************
** Form generated from reading UI file 'RuleAlgorithmItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEALGORITHMITEMDIALOG_H
#define UI_RULEALGORITHMITEMDIALOG_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_RuleAlgorithmItemDialog
{
public:
    QSpinBox *spinBoxPage;
    QLabel *label_3;
    QPushButton *pushButtonCancel;
    QTableWidget *tableWidgetItems;
    QComboBox *comboBoxLibTypeSelect;
    QFrame *frame;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEditName;
    QLineEdit *lineEditRemark;
    QCheckBox *checkBoxConclusion;
    QLabel *label_5;
    QPushButton *pushButtonFindItem;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxLayer;
    QLabel *label_4;
    QPushButton *pushButtonDelete;

    void setupUi(QDialog *RuleAlgorithmItemDialog)
    {
        if (RuleAlgorithmItemDialog->objectName().isEmpty())
            RuleAlgorithmItemDialog->setObjectName("RuleAlgorithmItemDialog");
        RuleAlgorithmItemDialog->resize(276, 546);
        spinBoxPage = new QSpinBox(RuleAlgorithmItemDialog);
        spinBoxPage->setObjectName("spinBoxPage");
        spinBoxPage->setGeometry(QRect(190, 70, 61, 22));
        label_3 = new QLabel(RuleAlgorithmItemDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 261, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(RuleAlgorithmItemDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(190, 490, 71, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        tableWidgetItems = new QTableWidget(RuleAlgorithmItemDialog);
        if (tableWidgetItems->columnCount() < 2)
            tableWidgetItems->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetItems->setObjectName("tableWidgetItems");
        tableWidgetItems->setGeometry(QRect(10, 170, 256, 192));
        tableWidgetItems->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItems->setSelectionBehavior(QAbstractItemView::SelectRows);
        comboBoxLibTypeSelect = new QComboBox(RuleAlgorithmItemDialog);
        comboBoxLibTypeSelect->setObjectName("comboBoxLibTypeSelect");
        comboBoxLibTypeSelect->setGeometry(QRect(10, 30, 261, 22));
        frame = new QFrame(RuleAlgorithmItemDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 380, 251, 101));
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
        lineEditName->setGeometry(QRect(80, 10, 161, 21));
        lineEditRemark = new QLineEdit(frame);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(80, 40, 161, 21));
        checkBoxConclusion = new QCheckBox(frame);
        checkBoxConclusion->setObjectName("checkBoxConclusion");
        checkBoxConclusion->setGeometry(QRect(10, 70, 231, 19));
        label_5 = new QLabel(RuleAlgorithmItemDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 100, 171, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        pushButtonFindItem = new QPushButton(RuleAlgorithmItemDialog);
        pushButtonFindItem->setObjectName("pushButtonFindItem");
        pushButtonFindItem->setGeometry(QRect(80, 130, 111, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonFindItem->setIcon(icon1);
        pushButtonOK = new QPushButton(RuleAlgorithmItemDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 490, 81, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon2);
        spinBoxLayer = new QSpinBox(RuleAlgorithmItemDialog);
        spinBoxLayer->setObjectName("spinBoxLayer");
        spinBoxLayer->setGeometry(QRect(190, 100, 61, 22));
        label_4 = new QLabel(RuleAlgorithmItemDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 70, 171, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonDelete = new QPushButton(RuleAlgorithmItemDialog);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(100, 490, 81, 41));
        pushButtonDelete->setIcon(icon2);
        pushButtonDelete->setAutoDefault(false);

        retranslateUi(RuleAlgorithmItemDialog);

        pushButtonOK->setDefault(true);
        pushButtonDelete->setDefault(false);


        QMetaObject::connectSlotsByName(RuleAlgorithmItemDialog);
    } // setupUi

    void retranslateUi(QDialog *RuleAlgorithmItemDialog)
    {
        RuleAlgorithmItemDialog->setWindowTitle(QCoreApplication::translate("RuleAlgorithmItemDialog", "Rule AlgorithmItem", nullptr));
        label_3->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "Select library - source", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItems->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItems->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "ItemName", nullptr));
        label_6->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "Name", nullptr));
        label_7->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "Remark", nullptr));
        checkBoxConclusion->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "Conclusion", nullptr));
        label_5->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "Layer", nullptr));
        pushButtonFindItem->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "Find item", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "OK", nullptr));
        label_4->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "Page", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("RuleAlgorithmItemDialog", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RuleAlgorithmItemDialog: public Ui_RuleAlgorithmItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEALGORITHMITEMDIALOG_H
