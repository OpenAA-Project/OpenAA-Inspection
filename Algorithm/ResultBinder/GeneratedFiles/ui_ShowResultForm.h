/********************************************************************************
** Form generated from reading UI file 'ShowResultForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULTFORM_H
#define UI_SHOWRESULTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowResultForm
{
public:
    QFrame *frame;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEditRuleName;
    QLineEdit *lineEditRuleRemark;
    QLabel *label_8;
    QPushButton *pushButtonOK;
    QLineEdit *lineEditItemName;
    QLabel *label_9;

    void setupUi(QWidget *ShowResultForm)
    {
        if (ShowResultForm->objectName().isEmpty())
            ShowResultForm->setObjectName("ShowResultForm");
        ShowResultForm->resize(279, 181);
        frame = new QFrame(ShowResultForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 40, 261, 91));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 30, 61, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 60, 61, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        lineEditRuleName = new QLineEdit(frame);
        lineEditRuleName->setObjectName("lineEditRuleName");
        lineEditRuleName->setGeometry(QRect(70, 30, 181, 21));
        lineEditRuleRemark = new QLineEdit(frame);
        lineEditRuleRemark->setObjectName("lineEditRuleRemark");
        lineEditRuleRemark->setGeometry(QRect(70, 60, 181, 21));
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 261, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(ShowResultForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(90, 130, 93, 41));
        lineEditItemName = new QLineEdit(ShowResultForm);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(100, 10, 161, 21));
        label_9 = new QLabel(ShowResultForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 10, 81, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);

        retranslateUi(ShowResultForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ShowResultForm);
    } // setupUi

    void retranslateUi(QWidget *ShowResultForm)
    {
        ShowResultForm->setWindowTitle(QCoreApplication::translate("ShowResultForm", "Set ResultBinder", nullptr));
        label_6->setText(QCoreApplication::translate("ShowResultForm", "Name", nullptr));
        label_7->setText(QCoreApplication::translate("ShowResultForm", "Remark", nullptr));
        label_8->setText(QCoreApplication::translate("ShowResultForm", "Conclusion", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ShowResultForm", "OK", nullptr));
        label_9->setText(QCoreApplication::translate("ShowResultForm", "Item name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowResultForm: public Ui_ShowResultForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULTFORM_H
