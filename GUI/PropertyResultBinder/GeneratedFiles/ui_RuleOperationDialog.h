/********************************************************************************
** Form generated from reading UI file 'RuleOperationDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEOPERATIONDIALOG_H
#define UI_RULEOPERATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RuleOperationDialog
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

    void setupUi(QDialog *RuleOperationDialog)
    {
        if (RuleOperationDialog->objectName().isEmpty())
            RuleOperationDialog->setObjectName("RuleOperationDialog");
        RuleOperationDialog->resize(283, 173);
        pushButtonCancel = new QPushButton(RuleOperationDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(170, 120, 93, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        frame = new QFrame(RuleOperationDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 261, 101));
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
        pushButtonOK = new QPushButton(RuleOperationDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 120, 93, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);

        retranslateUi(RuleOperationDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(RuleOperationDialog);
    } // setupUi

    void retranslateUi(QDialog *RuleOperationDialog)
    {
        RuleOperationDialog->setWindowTitle(QCoreApplication::translate("RuleOperationDialog", "Rule Operation", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RuleOperationDialog", "Cancel", nullptr));
        label_6->setText(QCoreApplication::translate("RuleOperationDialog", "Name", nullptr));
        label_7->setText(QCoreApplication::translate("RuleOperationDialog", "Remark", nullptr));
        checkBoxConclusion->setText(QCoreApplication::translate("RuleOperationDialog", "Conclusion", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RuleOperationDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RuleOperationDialog: public Ui_RuleOperationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEOPERATIONDIALOG_H
