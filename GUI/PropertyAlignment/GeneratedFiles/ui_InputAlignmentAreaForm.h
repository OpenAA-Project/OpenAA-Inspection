/********************************************************************************
** Form generated from reading UI file 'InputAlignmentAreaForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTALIGNMENTAREAFORM_H
#define UI_INPUTALIGNMENTAREAFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_InputAlignmentAreaFormClass
{
public:
    QLabel *label;
    QLineEdit *EditAreaName;
    QLabel *label_4;
    QFrame *frameLibrary;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
    QPushButton *ButtonDelete;
    QGroupBox *groupBox;
    QRadioButton *radioButtonPriorityHigh;
    QRadioButton *radioButtonPriorityMiddle;
    QRadioButton *radioButtonPriorityLow;

    void setupUi(QDialog *InputAlignmentAreaFormClass)
    {
        if (InputAlignmentAreaFormClass->objectName().isEmpty())
            InputAlignmentAreaFormClass->setObjectName("InputAlignmentAreaFormClass");
        InputAlignmentAreaFormClass->resize(493, 605);
        label = new QLabel(InputAlignmentAreaFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 261, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAreaName = new QLineEdit(InputAlignmentAreaFormClass);
        EditAreaName->setObjectName("EditAreaName");
        EditAreaName->setGeometry(QRect(20, 30, 261, 21));
        label_4 = new QLabel(InputAlignmentAreaFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 60, 451, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frameLibrary = new QFrame(InputAlignmentAreaFormClass);
        frameLibrary->setObjectName("frameLibrary");
        frameLibrary->setGeometry(QRect(20, 80, 451, 361));
        frameLibrary->setFrameShape(QFrame::StyledPanel);
        frameLibrary->setFrameShadow(QFrame::Sunken);
        ButtonOK = new QPushButton(InputAlignmentAreaFormClass);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(120, 560, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(InputAlignmentAreaFormClass);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(380, 560, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        ButtonDelete = new QPushButton(InputAlignmentAreaFormClass);
        ButtonDelete->setObjectName("ButtonDelete");
        ButtonDelete->setEnabled(false);
        ButtonDelete->setGeometry(QRect(260, 560, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonDelete->setIcon(icon2);
        groupBox = new QGroupBox(InputAlignmentAreaFormClass);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(130, 450, 341, 91));
        radioButtonPriorityHigh = new QRadioButton(groupBox);
        radioButtonPriorityHigh->setObjectName("radioButtonPriorityHigh");
        radioButtonPriorityHigh->setGeometry(QRect(20, 20, 251, 17));
        radioButtonPriorityHigh->setChecked(false);
        radioButtonPriorityMiddle = new QRadioButton(groupBox);
        radioButtonPriorityMiddle->setObjectName("radioButtonPriorityMiddle");
        radioButtonPriorityMiddle->setGeometry(QRect(20, 40, 231, 17));
        radioButtonPriorityMiddle->setChecked(true);
        radioButtonPriorityLow = new QRadioButton(groupBox);
        radioButtonPriorityLow->setObjectName("radioButtonPriorityLow");
        radioButtonPriorityLow->setGeometry(QRect(20, 60, 221, 17));
        radioButtonPriorityLow->setChecked(false);

        retranslateUi(InputAlignmentAreaFormClass);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(InputAlignmentAreaFormClass);
    } // setupUi

    void retranslateUi(QDialog *InputAlignmentAreaFormClass)
    {
        InputAlignmentAreaFormClass->setWindowTitle(QCoreApplication::translate("InputAlignmentAreaFormClass", "InputAlignmentAreaForm", nullptr));
        label->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "\343\202\250\343\203\252\343\202\242\345\220\215\347\247\260", nullptr));
        label_4->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\224\343\201\250\343\201\256\343\202\242\343\203\251\343\202\244\343\203\263\343\203\241\343\203\263\343\203\210", nullptr));
        ButtonOK->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Cancel", nullptr));
        ButtonDelete->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Delete", nullptr));
        groupBox->setTitle(QCoreApplication::translate("InputAlignmentAreaFormClass", "Priority", nullptr));
        radioButtonPriorityHigh->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "High( Exp. BGA, special part)", nullptr));
        radioButtonPriorityMiddle->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Middle (General)", nullptr));
        radioButtonPriorityLow->setText(QCoreApplication::translate("InputAlignmentAreaFormClass", "Low (Only parts fitting)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputAlignmentAreaFormClass: public Ui_InputAlignmentAreaFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTALIGNMENTAREAFORM_H
