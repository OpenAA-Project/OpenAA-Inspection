/********************************************************************************
** Form generated from reading UI file 'SaveMasterDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEMASTERDIALOG_H
#define UI_SAVEMASTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_SaveMasterDialog
{
public:
    QLabel *label_3;
    QPushButton *pushButtonInputPanel;
    QTableView *tableView;
    QLineEdit *lineEditSearchByName;
    QFrame *frame;
    QLineEdit *EditMasterName;
    QLabel *labelRemark;
    QLabel *labelName;
    QLineEdit *EditRemark;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSaveNew;
    QFrame *frameView;
    QPushButton *pushButtonInputPanelName;
    QPushButton *pushButtonInputPanelRemark;
    QLabel *label_4;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxSizeX;
    QDoubleSpinBox *doubleSpinBoxSizeY;
    QLabel *label_6;
    QPushButton *pushButtonInputPanelSizeX;
    QPushButton *pushButtonInputPanelSizeY;
    QLabel *labelNumber;
    QPushButton *pushButtonInputPanelNumber;
    QLineEdit *EditMasterNumber;

    void setupUi(QDialog *SaveMasterDialog)
    {
        if (SaveMasterDialog->objectName().isEmpty())
            SaveMasterDialog->setObjectName("SaveMasterDialog");
        SaveMasterDialog->resize(1102, 813);
        label_3 = new QLabel(SaveMasterDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 400, 91, 41));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        pushButtonInputPanel = new QPushButton(SaveMasterDialog);
        pushButtonInputPanel->setObjectName("pushButtonInputPanel");
        pushButtonInputPanel->setGeometry(QRect(490, 400, 61, 41));
        tableView = new QTableView(SaveMasterDialog);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(10, 450, 1081, 361));
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        lineEditSearchByName = new QLineEdit(SaveMasterDialog);
        lineEditSearchByName->setObjectName("lineEditSearchByName");
        lineEditSearchByName->setGeometry(QRect(120, 400, 361, 41));
        frame = new QFrame(SaveMasterDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 1081, 381));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        EditMasterName = new QLineEdit(frame);
        EditMasterName->setObjectName("EditMasterName");
        EditMasterName->setGeometry(QRect(190, 60, 271, 41));
        QFont font;
        font.setPointSize(12);
        EditMasterName->setFont(font);
        labelRemark = new QLabel(frame);
        labelRemark->setObjectName("labelRemark");
        labelRemark->setGeometry(QRect(10, 110, 171, 41));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        labelRemark->setFont(font1);
        labelRemark->setFrameShape(QFrame::Panel);
        labelRemark->setFrameShadow(QFrame::Sunken);
        labelRemark->setAlignment(Qt::AlignCenter);
        labelName = new QLabel(frame);
        labelName->setObjectName("labelName");
        labelName->setGeometry(QRect(10, 60, 171, 41));
        labelName->setFont(font1);
        labelName->setFrameShape(QFrame::Panel);
        labelName->setFrameShadow(QFrame::Sunken);
        labelName->setAlignment(Qt::AlignCenter);
        EditRemark = new QLineEdit(frame);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(190, 110, 271, 41));
        EditRemark->setFont(font);
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(190, 310, 151, 61));
        pushButtonUpdate->setFont(font1);
        pushButtonUpdate->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(400, 310, 141, 61));
        pushButtonCancel->setFont(font1);
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
        pushButtonSaveNew = new QPushButton(frame);
        pushButtonSaveNew->setObjectName("pushButtonSaveNew");
        pushButtonSaveNew->setGeometry(QRect(20, 310, 151, 61));
        pushButtonSaveNew->setFont(font1);
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
        frameView = new QFrame(frame);
        frameView->setObjectName("frameView");
        frameView->setGeometry(QRect(560, 10, 512, 256));
        frameView->setFrameShape(QFrame::StyledPanel);
        frameView->setFrameShadow(QFrame::Raised);
        pushButtonInputPanelName = new QPushButton(frame);
        pushButtonInputPanelName->setObjectName("pushButtonInputPanelName");
        pushButtonInputPanelName->setGeometry(QRect(470, 60, 61, 41));
        pushButtonInputPanelRemark = new QPushButton(frame);
        pushButtonInputPanelRemark->setObjectName("pushButtonInputPanelRemark");
        pushButtonInputPanelRemark->setGeometry(QRect(470, 110, 61, 41));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 200, 291, 41));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 250, 291, 41));
        label_5->setFont(font1);
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        doubleSpinBoxSizeX = new QDoubleSpinBox(frame);
        doubleSpinBoxSizeX->setObjectName("doubleSpinBoxSizeX");
        doubleSpinBoxSizeX->setGeometry(QRect(320, 200, 121, 41));
        QFont font2;
        font2.setPointSize(16);
        doubleSpinBoxSizeX->setFont(font2);
        doubleSpinBoxSizeX->setDecimals(1);
        doubleSpinBoxSizeX->setMaximum(500.000000000000000);
        doubleSpinBoxSizeX->setValue(100.000000000000000);
        doubleSpinBoxSizeY = new QDoubleSpinBox(frame);
        doubleSpinBoxSizeY->setObjectName("doubleSpinBoxSizeY");
        doubleSpinBoxSizeY->setGeometry(QRect(320, 250, 121, 41));
        doubleSpinBoxSizeY->setFont(font2);
        doubleSpinBoxSizeY->setDecimals(1);
        doubleSpinBoxSizeY->setMaximum(900.000000000000000);
        doubleSpinBoxSizeY->setValue(100.000000000000000);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 160, 521, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(170, 170, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_6->setPalette(palette);
        label_6->setFont(font1);
        label_6->setAutoFillBackground(true);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        pushButtonInputPanelSizeX = new QPushButton(frame);
        pushButtonInputPanelSizeX->setObjectName("pushButtonInputPanelSizeX");
        pushButtonInputPanelSizeX->setGeometry(QRect(450, 200, 61, 41));
        pushButtonInputPanelSizeY = new QPushButton(frame);
        pushButtonInputPanelSizeY->setObjectName("pushButtonInputPanelSizeY");
        pushButtonInputPanelSizeY->setGeometry(QRect(450, 250, 61, 41));
        labelNumber = new QLabel(frame);
        labelNumber->setObjectName("labelNumber");
        labelNumber->setGeometry(QRect(10, 10, 171, 41));
        labelNumber->setFont(font1);
        labelNumber->setFrameShape(QFrame::Panel);
        labelNumber->setFrameShadow(QFrame::Sunken);
        labelNumber->setAlignment(Qt::AlignCenter);
        pushButtonInputPanelNumber = new QPushButton(frame);
        pushButtonInputPanelNumber->setObjectName("pushButtonInputPanelNumber");
        pushButtonInputPanelNumber->setGeometry(QRect(470, 10, 61, 41));
        EditMasterNumber = new QLineEdit(frame);
        EditMasterNumber->setObjectName("EditMasterNumber");
        EditMasterNumber->setGeometry(QRect(190, 10, 271, 41));
        EditMasterNumber->setFont(font);

        retranslateUi(SaveMasterDialog);

        QMetaObject::connectSlotsByName(SaveMasterDialog);
    } // setupUi

    void retranslateUi(QDialog *SaveMasterDialog)
    {
        SaveMasterDialog->setWindowTitle(QCoreApplication::translate("SaveMasterDialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("SaveMasterDialog", "\345\220\215\347\247\260\346\244\234\347\264\242", nullptr));
        pushButtonInputPanel->setText(QCoreApplication::translate("SaveMasterDialog", "...", nullptr));
        labelRemark->setText(QCoreApplication::translate("SaveMasterDialog", "\345\202\231\350\200\203", nullptr));
        labelName->setText(QCoreApplication::translate("SaveMasterDialog", "\345\223\201\347\225\252", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("SaveMasterDialog", "\344\270\212\346\233\270\343\201\215\346\233\264\346\226\260", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SaveMasterDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        pushButtonSaveNew->setText(QCoreApplication::translate("SaveMasterDialog", "\346\226\260\350\246\217\344\277\235\345\255\230", nullptr));
        pushButtonInputPanelName->setText(QCoreApplication::translate("SaveMasterDialog", "...", nullptr));
        pushButtonInputPanelRemark->setText(QCoreApplication::translate("SaveMasterDialog", "...", nullptr));
        label_4->setText(QCoreApplication::translate("SaveMasterDialog", "\346\250\252\345\271\205 mm", nullptr));
        label_5->setText(QCoreApplication::translate("SaveMasterDialog", "\347\270\246\357\274\210\346\265\201\343\202\214\346\226\271\345\220\221\357\274\211mm", nullptr));
        label_6->setText(QCoreApplication::translate("SaveMasterDialog", "\343\203\257\343\203\274\343\202\257\343\202\265\343\202\244\343\202\272", nullptr));
        pushButtonInputPanelSizeX->setText(QCoreApplication::translate("SaveMasterDialog", "...", nullptr));
        pushButtonInputPanelSizeY->setText(QCoreApplication::translate("SaveMasterDialog", "...", nullptr));
        labelNumber->setText(QCoreApplication::translate("SaveMasterDialog", "\343\202\263\343\203\274\343\203\211No", nullptr));
        pushButtonInputPanelNumber->setText(QCoreApplication::translate("SaveMasterDialog", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SaveMasterDialog: public Ui_SaveMasterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEMASTERDIALOG_H
