/********************************************************************************
** Form generated from reading UI file 'SelectSlaveMachineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTSLAVEMACHINEDIALOG_H
#define UI_SELECTSLAVEMACHINEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectSlaveMachineDialog
{
public:
    QFrame *frame;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QCheckBox *checkBoxSlave;
    QFrame *frame_2;
    QPushButton *PushButtonResetSwitchPhase;
    QPushButton *PushButtonResetMakeAverage;
    QCheckBox *checkBoxReGenSlave;
    QCheckBox *checkBoxKeepMark;

    void setupUi(QDialog *SelectSlaveMachineDialog)
    {
        if (SelectSlaveMachineDialog->objectName().isEmpty())
            SelectSlaveMachineDialog->setObjectName("SelectSlaveMachineDialog");
        SelectSlaveMachineDialog->resize(592, 240);
        frame = new QFrame(SelectSlaveMachineDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 170, 591, 71));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(frame);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 10, 151, 51));
        QFont font;
        font.setPointSize(14);
        pushButtonOK->setFont(font);
        pushButtonOK->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(420, 10, 151, 51));
        pushButtonCancel->setFont(font);
        pushButtonCancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        checkBoxSlave = new QCheckBox(SelectSlaveMachineDialog);
        checkBoxSlave->setObjectName("checkBoxSlave");
        checkBoxSlave->setGeometry(QRect(30, 70, 111, 31));
        QFont font1;
        font1.setPointSize(12);
        checkBoxSlave->setFont(font1);
        frame_2 = new QFrame(SelectSlaveMachineDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 0, 591, 61));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        PushButtonResetSwitchPhase = new QPushButton(frame_2);
        PushButtonResetSwitchPhase->setObjectName("PushButtonResetSwitchPhase");
        PushButtonResetSwitchPhase->setGeometry(QRect(10, 10, 161, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Yu Gothic UI")});
        font2.setPointSize(12);
        PushButtonResetSwitchPhase->setFont(font2);
        PushButtonResetSwitchPhase->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonResetSwitchPhase->setCheckable(true);
        PushButtonResetSwitchPhase->setChecked(true);
        PushButtonResetSwitchPhase->setAutoExclusive(false);
        PushButtonResetSwitchPhase->setAutoDefault(false);
        PushButtonResetSwitchPhase->setFlat(false);
        PushButtonResetMakeAverage = new QPushButton(frame_2);
        PushButtonResetMakeAverage->setObjectName("PushButtonResetMakeAverage");
        PushButtonResetMakeAverage->setGeometry(QRect(220, 10, 161, 41));
        PushButtonResetMakeAverage->setFont(font2);
        PushButtonResetMakeAverage->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        PushButtonResetMakeAverage->setCheckable(true);
        PushButtonResetMakeAverage->setChecked(true);
        PushButtonResetMakeAverage->setAutoExclusive(false);
        PushButtonResetMakeAverage->setAutoDefault(false);
        PushButtonResetMakeAverage->setFlat(false);
        checkBoxReGenSlave = new QCheckBox(SelectSlaveMachineDialog);
        checkBoxReGenSlave->setObjectName("checkBoxReGenSlave");
        checkBoxReGenSlave->setGeometry(QRect(220, 70, 91, 31));
        checkBoxReGenSlave->setFont(font1);
        checkBoxKeepMark = new QCheckBox(SelectSlaveMachineDialog);
        checkBoxKeepMark->setObjectName("checkBoxKeepMark");
        checkBoxKeepMark->setGeometry(QRect(360, 70, 191, 31));
        checkBoxKeepMark->setFont(font1);

        retranslateUi(SelectSlaveMachineDialog);

        PushButtonResetSwitchPhase->setDefault(false);
        PushButtonResetMakeAverage->setDefault(false);


        QMetaObject::connectSlotsByName(SelectSlaveMachineDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectSlaveMachineDialog)
    {
        SelectSlaveMachineDialog->setWindowTitle(QCoreApplication::translate("SelectSlaveMachineDialog", "\346\233\264\346\226\260\343\201\231\343\202\213\343\202\253\343\203\241\343\203\251", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectSlaveMachineDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectSlaveMachineDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        checkBoxSlave->setText(QCoreApplication::translate("SelectSlaveMachineDialog", "\345\256\237\350\241\214", nullptr));
        PushButtonResetSwitchPhase->setText(QCoreApplication::translate("SelectSlaveMachineDialog", "\344\270\201\347\225\252\343\203\252\343\202\273\343\203\203\343\203\210", nullptr));
        PushButtonResetMakeAverage->setText(QCoreApplication::translate("SelectSlaveMachineDialog", "\345\271\263\345\235\207\345\214\226\343\203\252\343\202\273\343\203\203\343\203\210", nullptr));
        checkBoxReGenSlave->setText(QCoreApplication::translate("SelectSlaveMachineDialog", "\345\206\215\347\224\237\346\210\220", nullptr));
        checkBoxKeepMark->setText(QCoreApplication::translate("SelectSlaveMachineDialog", "\344\275\215\347\275\256\345\220\210\343\202\217\343\201\233\343\203\236\343\203\274\343\202\257\347\266\255\346\214\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectSlaveMachineDialog: public Ui_SelectSlaveMachineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTSLAVEMACHINEDIALOG_H
