/********************************************************************************
** Form generated from reading UI file 'NewMasterDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMASTERDIALOG_H
#define UI_NEWMASTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NewMasterDialog
{
public:
    QLabel *label_6;
    QLabel *labelTitleName;
    QDoubleSpinBox *doubleSpinBoxSizeY;
    QLabel *label_5;
    QPushButton *pushButtonSaveNew;
    QLineEdit *EditNumber;
    QPushButton *pushButtonInputPanelNumber;
    QPushButton *pushButtonInputPanelName;
    QDoubleSpinBox *doubleSpinBoxSizeX;
    QLabel *labelTitleNumber;
    QLineEdit *EditMasterName;
    QLabel *label_4;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonInputPanelSizeX;
    QPushButton *pushButtonInputPanelSizeY;
    QLineEdit *EditRemark;
    QLabel *labelTitleRemark;
    QPushButton *pushButtonInputPanelRemark;

    void setupUi(QDialog *NewMasterDialog)
    {
        if (NewMasterDialog->objectName().isEmpty())
            NewMasterDialog->setObjectName("NewMasterDialog");
        NewMasterDialog->resize(555, 438);
        label_6 = new QLabel(NewMasterDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 200, 521, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label_6->setFont(font);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        labelTitleName = new QLabel(NewMasterDialog);
        labelTitleName->setObjectName("labelTitleName");
        labelTitleName->setGeometry(QRect(10, 60, 161, 41));
        labelTitleName->setFont(font);
        labelTitleName->setFrameShape(QFrame::Panel);
        labelTitleName->setFrameShadow(QFrame::Sunken);
        labelTitleName->setAlignment(Qt::AlignCenter);
        doubleSpinBoxSizeY = new QDoubleSpinBox(NewMasterDialog);
        doubleSpinBoxSizeY->setObjectName("doubleSpinBoxSizeY");
        doubleSpinBoxSizeY->setGeometry(QRect(250, 290, 121, 41));
        QFont font1;
        font1.setPointSize(16);
        doubleSpinBoxSizeY->setFont(font1);
        doubleSpinBoxSizeY->setDecimals(1);
        doubleSpinBoxSizeY->setMaximum(2000.000000000000000);
        doubleSpinBoxSizeY->setValue(100.000000000000000);
        label_5 = new QLabel(NewMasterDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 290, 231, 41));
        label_5->setFont(font);
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        pushButtonSaveNew = new QPushButton(NewMasterDialog);
        pushButtonSaveNew->setObjectName("pushButtonSaveNew");
        pushButtonSaveNew->setGeometry(QRect(60, 350, 171, 71));
        pushButtonSaveNew->setFont(font);
        pushButtonSaveNew->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        EditNumber = new QLineEdit(NewMasterDialog);
        EditNumber->setObjectName("EditNumber");
        EditNumber->setGeometry(QRect(190, 10, 271, 41));
        QFont font2;
        font2.setPointSize(12);
        EditNumber->setFont(font2);
        EditNumber->setMaxLength(31);
        pushButtonInputPanelNumber = new QPushButton(NewMasterDialog);
        pushButtonInputPanelNumber->setObjectName("pushButtonInputPanelNumber");
        pushButtonInputPanelNumber->setGeometry(QRect(470, 10, 61, 41));
        pushButtonInputPanelName = new QPushButton(NewMasterDialog);
        pushButtonInputPanelName->setObjectName("pushButtonInputPanelName");
        pushButtonInputPanelName->setGeometry(QRect(470, 60, 61, 41));
        doubleSpinBoxSizeX = new QDoubleSpinBox(NewMasterDialog);
        doubleSpinBoxSizeX->setObjectName("doubleSpinBoxSizeX");
        doubleSpinBoxSizeX->setGeometry(QRect(250, 240, 121, 41));
        doubleSpinBoxSizeX->setFont(font1);
        doubleSpinBoxSizeX->setDecimals(1);
        doubleSpinBoxSizeX->setMaximum(2000.000000000000000);
        doubleSpinBoxSizeX->setValue(100.000000000000000);
        labelTitleNumber = new QLabel(NewMasterDialog);
        labelTitleNumber->setObjectName("labelTitleNumber");
        labelTitleNumber->setGeometry(QRect(10, 10, 161, 41));
        labelTitleNumber->setFont(font);
        labelTitleNumber->setFrameShape(QFrame::Panel);
        labelTitleNumber->setFrameShadow(QFrame::Sunken);
        labelTitleNumber->setAlignment(Qt::AlignCenter);
        EditMasterName = new QLineEdit(NewMasterDialog);
        EditMasterName->setObjectName("EditMasterName");
        EditMasterName->setGeometry(QRect(190, 60, 271, 41));
        EditMasterName->setFont(font2);
        EditMasterName->setMaxLength(31);
        label_4 = new QLabel(NewMasterDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 240, 231, 41));
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonCancel = new QPushButton(NewMasterDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(310, 350, 161, 71));
        pushButtonCancel->setFont(font);
        pushButtonCancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonInputPanelSizeX = new QPushButton(NewMasterDialog);
        pushButtonInputPanelSizeX->setObjectName("pushButtonInputPanelSizeX");
        pushButtonInputPanelSizeX->setGeometry(QRect(380, 240, 61, 41));
        pushButtonInputPanelSizeY = new QPushButton(NewMasterDialog);
        pushButtonInputPanelSizeY->setObjectName("pushButtonInputPanelSizeY");
        pushButtonInputPanelSizeY->setGeometry(QRect(380, 290, 61, 41));
        EditRemark = new QLineEdit(NewMasterDialog);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(190, 110, 271, 41));
        EditRemark->setFont(font2);
        EditRemark->setMaxLength(31);
        labelTitleRemark = new QLabel(NewMasterDialog);
        labelTitleRemark->setObjectName("labelTitleRemark");
        labelTitleRemark->setGeometry(QRect(10, 110, 161, 41));
        labelTitleRemark->setFont(font);
        labelTitleRemark->setFrameShape(QFrame::Panel);
        labelTitleRemark->setFrameShadow(QFrame::Sunken);
        labelTitleRemark->setAlignment(Qt::AlignCenter);
        pushButtonInputPanelRemark = new QPushButton(NewMasterDialog);
        pushButtonInputPanelRemark->setObjectName("pushButtonInputPanelRemark");
        pushButtonInputPanelRemark->setGeometry(QRect(470, 110, 61, 41));

        retranslateUi(NewMasterDialog);

        QMetaObject::connectSlotsByName(NewMasterDialog);
    } // setupUi

    void retranslateUi(QDialog *NewMasterDialog)
    {
        NewMasterDialog->setWindowTitle(QCoreApplication::translate("NewMasterDialog", "Dialog", nullptr));
        label_6->setText(QCoreApplication::translate("NewMasterDialog", "\343\203\257\343\203\274\343\202\257\343\202\265\343\202\244\343\202\272", nullptr));
        labelTitleName->setText(QCoreApplication::translate("NewMasterDialog", "\345\223\201\345\220\215", nullptr));
        label_5->setText(QCoreApplication::translate("NewMasterDialog", "\347\270\246\357\274\210\346\265\201\343\202\214\346\226\271\345\220\221\357\274\211mm", nullptr));
        pushButtonSaveNew->setText(QCoreApplication::translate("NewMasterDialog", "\346\226\260\350\246\217\344\277\235\345\255\230", nullptr));
        pushButtonInputPanelNumber->setText(QCoreApplication::translate("NewMasterDialog", "...", nullptr));
        pushButtonInputPanelName->setText(QCoreApplication::translate("NewMasterDialog", "...", nullptr));
        labelTitleNumber->setText(QCoreApplication::translate("NewMasterDialog", "\345\223\201\347\225\252", nullptr));
        label_4->setText(QCoreApplication::translate("NewMasterDialog", "\346\250\252\345\271\205(\345\271\205\346\226\271\345\220\221\357\274\211 mm", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("NewMasterDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        pushButtonInputPanelSizeX->setText(QCoreApplication::translate("NewMasterDialog", "...", nullptr));
        pushButtonInputPanelSizeY->setText(QCoreApplication::translate("NewMasterDialog", "...", nullptr));
        labelTitleRemark->setText(QCoreApplication::translate("NewMasterDialog", "\345\202\231\350\200\203", nullptr));
        pushButtonInputPanelRemark->setText(QCoreApplication::translate("NewMasterDialog", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewMasterDialog: public Ui_NewMasterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMASTERDIALOG_H
