/********************************************************************************
** Form generated from reading UI file 'EditRxLineDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITRXLINEDIALOG_H
#define UI_EDITRXLINEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditRxLineDialog
{
public:
    QLabel *label_6;
    QLineEdit *EditLibID;
    QPushButton *pushButtonChangeLib;
    QPushButton *ButtonReflectAllBlocks;
    QPushButton *ButtonRelrectOnlyBlock;
    QLabel *label_7;
    QFrame *frame;
    QLabel *label_92;
    QLineEdit *EditName;
    QLabel *label_4;
    QCheckBox *checkBoxEnable;
    QLabel *label_8;
    QLineEdit *EditItemID;
    QLabel *labelUnitName_4;
    QLabel *label_99;
    QSpinBox *spinBoxHookedItemID;
    QDoubleSpinBox *doubleSpinBoxRxValue;
    QLabel *label_93;
    QSpinBox *spinBoxRxID;
    QPushButton *pushButtonUpdateRxValue;
    QPushButton *pushButtonChangeItemID;
    QFrame *frame_2;
    QPushButton *pushButtonTest;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *labelPosDiffX;
    QLabel *labelPosDiffY;
    QLabel *labelPosDiffYUnit;
    QLabel *labelPosDiffXUnit;
    QLabel *labelUnitName_7;
    QLabel *labelUnitName_8;
    QPushButton *ButtonClose;
    QLineEdit *Edit_LibName;

    void setupUi(QWidget *EditRxLineDialog)
    {
        if (EditRxLineDialog->objectName().isEmpty())
            EditRxLineDialog->setObjectName("EditRxLineDialog");
        EditRxLineDialog->resize(680, 294);
        label_6 = new QLabel(EditRxLineDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 62, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(EditRxLineDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 30, 61, 21));
        EditLibID->setReadOnly(true);
        pushButtonChangeLib = new QPushButton(EditRxLineDialog);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(310, 30, 31, 23));
        ButtonReflectAllBlocks = new QPushButton(EditRxLineDialog);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(180, 240, 201, 41));
        ButtonRelrectOnlyBlock = new QPushButton(EditRxLineDialog);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 240, 161, 41));
        label_7 = new QLabel(EditRxLineDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 10, 241, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(EditRxLineDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 60, 421, 171));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_92 = new QLabel(frame);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(0, 120, 161, 31));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditName = new QLineEdit(frame);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(200, 10, 211, 31));
        QFont font;
        font.setPointSize(12);
        EditName->setFont(font);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(120, 10, 81, 31));
        QFont font1;
        font1.setPointSize(9);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxEnable = new QCheckBox(frame);
        checkBoxEnable->setObjectName("checkBoxEnable");
        checkBoxEnable->setGeometry(QRect(10, 50, 191, 21));
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 62, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditItemID = new QLineEdit(frame);
        EditItemID->setObjectName("EditItemID");
        EditItemID->setGeometry(QRect(0, 20, 61, 21));
        EditItemID->setReadOnly(true);
        labelUnitName_4 = new QLabel(frame);
        labelUnitName_4->setObjectName("labelUnitName_4");
        labelUnitName_4->setGeometry(QRect(370, 90, 31, 20));
        labelUnitName_4->setFrameShape(QFrame::NoFrame);
        labelUnitName_4->setFrameShadow(QFrame::Sunken);
        labelUnitName_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_99 = new QLabel(frame);
        label_99->setObjectName("label_99");
        label_99->setGeometry(QRect(260, 60, 111, 21));
        label_99->setFrameShape(QFrame::Panel);
        label_99->setFrameShadow(QFrame::Sunken);
        label_99->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxHookedItemID = new QSpinBox(frame);
        spinBoxHookedItemID->setObjectName("spinBoxHookedItemID");
        spinBoxHookedItemID->setGeometry(QRect(170, 120, 81, 31));
        spinBoxHookedItemID->setMaximum(2000);
        doubleSpinBoxRxValue = new QDoubleSpinBox(frame);
        doubleSpinBoxRxValue->setObjectName("doubleSpinBoxRxValue");
        doubleSpinBoxRxValue->setGeometry(QRect(260, 80, 111, 31));
        QPalette palette;
        QBrush brush(QColor(255, 170, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxRxValue->setPalette(palette);
        doubleSpinBoxRxValue->setMaximum(9999999999.000000000000000);
        label_93 = new QLabel(frame);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(0, 80, 161, 31));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxRxID = new QSpinBox(frame);
        spinBoxRxID->setObjectName("spinBoxRxID");
        spinBoxRxID->setGeometry(QRect(170, 80, 81, 31));
        spinBoxRxID->setMaximum(2000);
        pushButtonUpdateRxValue = new QPushButton(frame);
        pushButtonUpdateRxValue->setObjectName("pushButtonUpdateRxValue");
        pushButtonUpdateRxValue->setGeometry(QRect(279, 120, 81, 31));
        pushButtonChangeItemID = new QPushButton(frame);
        pushButtonChangeItemID->setObjectName("pushButtonChangeItemID");
        pushButtonChangeItemID->setGeometry(QRect(60, 20, 31, 22));
        frame_2 = new QFrame(EditRxLineDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(440, 60, 231, 151));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        pushButtonTest = new QPushButton(frame_2);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(30, 10, 151, 31));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 50, 121, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 100, 121, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffX = new QLabel(frame_2);
        labelPosDiffX->setObjectName("labelPosDiffX");
        labelPosDiffX->setGeometry(QRect(140, 50, 81, 21));
        labelPosDiffX->setFrameShape(QFrame::Panel);
        labelPosDiffX->setFrameShadow(QFrame::Sunken);
        labelPosDiffX->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffY = new QLabel(frame_2);
        labelPosDiffY->setObjectName("labelPosDiffY");
        labelPosDiffY->setGeometry(QRect(140, 100, 81, 21));
        labelPosDiffY->setFrameShape(QFrame::Panel);
        labelPosDiffY->setFrameShadow(QFrame::Sunken);
        labelPosDiffY->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffYUnit = new QLabel(frame_2);
        labelPosDiffYUnit->setObjectName("labelPosDiffYUnit");
        labelPosDiffYUnit->setGeometry(QRect(140, 120, 81, 21));
        QPalette palette1;
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        labelPosDiffYUnit->setPalette(palette1);
        labelPosDiffYUnit->setAutoFillBackground(true);
        labelPosDiffYUnit->setFrameShape(QFrame::Panel);
        labelPosDiffYUnit->setFrameShadow(QFrame::Sunken);
        labelPosDiffYUnit->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffXUnit = new QLabel(frame_2);
        labelPosDiffXUnit->setObjectName("labelPosDiffXUnit");
        labelPosDiffXUnit->setGeometry(QRect(140, 70, 81, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        labelPosDiffXUnit->setPalette(palette2);
        labelPosDiffXUnit->setAutoFillBackground(true);
        labelPosDiffXUnit->setFrameShape(QFrame::Panel);
        labelPosDiffXUnit->setFrameShadow(QFrame::Sunken);
        labelPosDiffXUnit->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelUnitName_7 = new QLabel(frame_2);
        labelUnitName_7->setObjectName("labelUnitName_7");
        labelUnitName_7->setGeometry(QRect(40, 70, 91, 20));
        labelUnitName_7->setFrameShape(QFrame::NoFrame);
        labelUnitName_7->setFrameShadow(QFrame::Sunken);
        labelUnitName_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelUnitName_8 = new QLabel(frame_2);
        labelUnitName_8->setObjectName("labelUnitName_8");
        labelUnitName_8->setGeometry(QRect(40, 120, 91, 20));
        labelUnitName_8->setFrameShape(QFrame::NoFrame);
        labelUnitName_8->setFrameShadow(QFrame::Sunken);
        labelUnitName_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ButtonClose = new QPushButton(EditRxLineDialog);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(490, 240, 171, 41));
        Edit_LibName = new QLineEdit(EditRxLineDialog);
        Edit_LibName->setObjectName("Edit_LibName");
        Edit_LibName->setGeometry(QRect(70, 30, 241, 21));
        Edit_LibName->setReadOnly(true);

        retranslateUi(EditRxLineDialog);

        QMetaObject::connectSlotsByName(EditRxLineDialog);
    } // setupUi

    void retranslateUi(QWidget *EditRxLineDialog)
    {
        EditRxLineDialog->setWindowTitle(QCoreApplication::translate("EditRxLineDialog", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("EditRxLineDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditRxLineDialog", "12345", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("EditRxLineDialog", "...", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("EditRxLineDialog", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\347\267\232\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("EditRxLineDialog", "\343\201\223\343\201\256\347\267\232\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        label_7->setText(QCoreApplication::translate("EditRxLineDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        label_92->setText(QCoreApplication::translate("EditRxLineDialog", "\343\203\225\343\203\203\343\202\257\343\203\251\343\202\244\343\203\263ID", nullptr));
        EditName->setText(QString());
        label_4->setText(QCoreApplication::translate("EditRxLineDialog", "\345\200\213\345\210\245\345\220\215\347\247\260", nullptr));
        checkBoxEnable->setText(QCoreApplication::translate("EditRxLineDialog", "Enable", nullptr));
        label_8->setText(QCoreApplication::translate("EditRxLineDialog", "ItemID", nullptr));
        EditItemID->setText(QCoreApplication::translate("EditRxLineDialog", "12345", nullptr));
        labelUnitName_4->setText(QCoreApplication::translate("EditRxLineDialog", "mm", nullptr));
        label_99->setText(QCoreApplication::translate("EditRxLineDialog", "Value", nullptr));
        label_93->setText(QCoreApplication::translate("EditRxLineDialog", "\345\217\227\344\277\241ItemID", nullptr));
        pushButtonUpdateRxValue->setText(QCoreApplication::translate("EditRxLineDialog", "\346\233\264\346\226\260", nullptr));
        pushButtonChangeItemID->setText(QCoreApplication::translate("EditRxLineDialog", "...", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("EditRxLineDialog", "Test", nullptr));
        label_10->setText(QCoreApplication::translate("EditRxLineDialog", "\357\274\270\346\226\271\345\220\221\344\275\215\347\275\256\343\202\272\343\203\254", nullptr));
        label_11->setText(QCoreApplication::translate("EditRxLineDialog", "\357\274\271\346\226\271\345\220\221\344\275\215\347\275\256\343\202\272\343\203\254", nullptr));
        labelPosDiffX->setText(QString());
        labelPosDiffY->setText(QString());
        labelPosDiffYUnit->setText(QString());
        labelPosDiffXUnit->setText(QString());
        labelUnitName_7->setText(QCoreApplication::translate("EditRxLineDialog", "mm", nullptr));
        labelUnitName_8->setText(QCoreApplication::translate("EditRxLineDialog", "mm", nullptr));
        ButtonClose->setText(QCoreApplication::translate("EditRxLineDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        Edit_LibName->setText(QCoreApplication::translate("EditRxLineDialog", "XXX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditRxLineDialog: public Ui_EditRxLineDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITRXLINEDIALOG_H
