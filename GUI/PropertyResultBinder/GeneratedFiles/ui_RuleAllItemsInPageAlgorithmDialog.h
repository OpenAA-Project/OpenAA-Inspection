/********************************************************************************
** Form generated from reading UI file 'RuleAllItemsInPageAlgorithmDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEALLITEMSINPAGEALGORITHMDIALOG_H
#define UI_RULEALLITEMSINPAGEALGORITHMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RuleAllItemsInPageAlgorithmDialog
{
public:
    QLabel *label_4;
    QComboBox *comboBoxLibTypeSelect;
    QPushButton *pushButtonCancel;
    QFrame *frame;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEditName;
    QLineEdit *lineEditRemark;
    QCheckBox *checkBoxConclusion;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxPage;
    QLabel *label_3;
    QPushButton *pushButtonDelete;

    void setupUi(QDialog *RuleAllItemsInPageAlgorithmDialog)
    {
        if (RuleAllItemsInPageAlgorithmDialog->objectName().isEmpty())
            RuleAllItemsInPageAlgorithmDialog->setObjectName("RuleAllItemsInPageAlgorithmDialog");
        RuleAllItemsInPageAlgorithmDialog->resize(279, 263);
        label_4 = new QLabel(RuleAllItemsInPageAlgorithmDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 70, 171, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        comboBoxLibTypeSelect = new QComboBox(RuleAllItemsInPageAlgorithmDialog);
        comboBoxLibTypeSelect->setObjectName("comboBoxLibTypeSelect");
        comboBoxLibTypeSelect->setGeometry(QRect(10, 30, 261, 22));
        pushButtonCancel = new QPushButton(RuleAllItemsInPageAlgorithmDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(192, 210, 81, 41));
        QFont font;
        font.setPointSize(11);
        pushButtonCancel->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        frame = new QFrame(RuleAllItemsInPageAlgorithmDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 100, 261, 101));
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
        pushButtonOK = new QPushButton(RuleAllItemsInPageAlgorithmDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 210, 81, 41));
        pushButtonOK->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        spinBoxPage = new QSpinBox(RuleAllItemsInPageAlgorithmDialog);
        spinBoxPage->setObjectName("spinBoxPage");
        spinBoxPage->setGeometry(QRect(190, 70, 61, 22));
        label_3 = new QLabel(RuleAllItemsInPageAlgorithmDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 261, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonDelete = new QPushButton(RuleAllItemsInPageAlgorithmDialog);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(100, 210, 81, 41));
        pushButtonDelete->setFont(font);
        pushButtonDelete->setIcon(icon1);
        pushButtonDelete->setAutoDefault(false);

        retranslateUi(RuleAllItemsInPageAlgorithmDialog);

        pushButtonOK->setDefault(true);
        pushButtonDelete->setDefault(false);


        QMetaObject::connectSlotsByName(RuleAllItemsInPageAlgorithmDialog);
    } // setupUi

    void retranslateUi(QDialog *RuleAllItemsInPageAlgorithmDialog)
    {
        RuleAllItemsInPageAlgorithmDialog->setWindowTitle(QCoreApplication::translate("RuleAllItemsInPageAlgorithmDialog", "Rule all Items in Page Algorithm", nullptr));
        label_4->setText(QCoreApplication::translate("RuleAllItemsInPageAlgorithmDialog", "Page", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RuleAllItemsInPageAlgorithmDialog", "Cancel", nullptr));
        label_6->setText(QCoreApplication::translate("RuleAllItemsInPageAlgorithmDialog", "Name", nullptr));
        label_7->setText(QCoreApplication::translate("RuleAllItemsInPageAlgorithmDialog", "Remark", nullptr));
        checkBoxConclusion->setText(QCoreApplication::translate("RuleAllItemsInPageAlgorithmDialog", "Conclusion", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RuleAllItemsInPageAlgorithmDialog", "OK", nullptr));
        label_3->setText(QCoreApplication::translate("RuleAllItemsInPageAlgorithmDialog", "Select library - source", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("RuleAllItemsInPageAlgorithmDialog", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RuleAllItemsInPageAlgorithmDialog: public Ui_RuleAllItemsInPageAlgorithmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEALLITEMSINPAGEALGORITHMDIALOG_H
