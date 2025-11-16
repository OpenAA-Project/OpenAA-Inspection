/********************************************************************************
** Form generated from reading UI file 'EditHolePosDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITHOLEPOSDIALOG_H
#define UI_EDITHOLEPOSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditHolePosDialog
{
public:
    QLabel *label_40;
    QListWidget *listWidgetHistList;
    QFrame *frame;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxDiaPrecision;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxPosPrecision;
    QLabel *label_3;
    QSpinBox *spinBoxNoiseSize;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QSpinBox *spinBoxBandWidth;
    QLabel *label_5;
    QLineEdit *EditName;
    QLabel *label_4;
    QSpinBox *spinBoxBandWidthLib;
    QSpinBox *EditSearchDotLib;
    QDoubleSpinBox *doubleSpinBoxPosPrecisionLib;
    QDoubleSpinBox *doubleSpinBoxDiaPrecisionLib;
    QSpinBox *spinBoxNoiseSizeLib;
    QLabel *label_16;
    QLabel *label_95;
    QComboBox *comboBoxCalcMode;
    QLabel *label_6;
    QLineEdit *EditLibID;
    QPushButton *pushButtonChangeLib;
    QLabel *label_7;
    QLineEdit *Edit_LibName;
    QFrame *frame_2;
    QPushButton *pushButtonTest;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *labelHoleV;
    QLabel *labelHoleH;
    QLabel *labelPosDiffX;
    QLabel *labelPosDiffY;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonReflectAllBlocks;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *ButtonClose;
    QPushButton *ButtonRelrectOnlyBlock;

    void setupUi(QWidget *EditHolePosDialog)
    {
        if (EditHolePosDialog->objectName().isEmpty())
            EditHolePosDialog->setObjectName("EditHolePosDialog");
        EditHolePosDialog->resize(571, 401);
        label_40 = new QLabel(EditHolePosDialog);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(360, 240, 201, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetHistList = new QListWidget(EditHolePosDialog);
        listWidgetHistList->setObjectName("listWidgetHistList");
        listWidgetHistList->setGeometry(QRect(360, 260, 201, 71));
        frame = new QFrame(EditHolePosDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 60, 331, 231));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 70, 151, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxDiaPrecision = new QDoubleSpinBox(frame);
        doubleSpinBoxDiaPrecision->setObjectName("doubleSpinBoxDiaPrecision");
        doubleSpinBoxDiaPrecision->setGeometry(QRect(180, 70, 71, 22));
        doubleSpinBoxDiaPrecision->setReadOnly(false);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 90, 151, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxPosPrecision = new QDoubleSpinBox(frame);
        doubleSpinBoxPosPrecision->setObjectName("doubleSpinBoxPosPrecision");
        doubleSpinBoxPosPrecision->setGeometry(QRect(180, 90, 71, 22));
        doubleSpinBoxPosPrecision->setReadOnly(false);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 110, 151, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxNoiseSize = new QSpinBox(frame);
        spinBoxNoiseSize->setObjectName("spinBoxNoiseSize");
        spinBoxNoiseSize->setGeometry(QRect(180, 110, 71, 22));
        spinBoxNoiseSize->setReadOnly(false);
        label_92 = new QLabel(frame);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(20, 160, 151, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(180, 160, 71, 22));
        EditSearchDot->setReadOnly(false);
        EditSearchDot->setMaximum(100);
        spinBoxBandWidth = new QSpinBox(frame);
        spinBoxBandWidth->setObjectName("spinBoxBandWidth");
        spinBoxBandWidth->setGeometry(QRect(180, 130, 71, 22));
        spinBoxBandWidth->setReadOnly(false);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 130, 151, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditName = new QLineEdit(frame);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(100, 10, 211, 31));
        QFont font;
        font.setPointSize(12);
        EditName->setFont(font);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 10, 81, 31));
        QFont font1;
        font1.setPointSize(9);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxBandWidthLib = new QSpinBox(frame);
        spinBoxBandWidthLib->setObjectName("spinBoxBandWidthLib");
        spinBoxBandWidthLib->setGeometry(QRect(250, 130, 71, 22));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        spinBoxBandWidthLib->setPalette(palette);
        spinBoxBandWidthLib->setReadOnly(true);
        EditSearchDotLib = new QSpinBox(frame);
        EditSearchDotLib->setObjectName("EditSearchDotLib");
        EditSearchDotLib->setGeometry(QRect(250, 160, 71, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditSearchDotLib->setPalette(palette1);
        EditSearchDotLib->setReadOnly(true);
        EditSearchDotLib->setMaximum(100);
        doubleSpinBoxPosPrecisionLib = new QDoubleSpinBox(frame);
        doubleSpinBoxPosPrecisionLib->setObjectName("doubleSpinBoxPosPrecisionLib");
        doubleSpinBoxPosPrecisionLib->setGeometry(QRect(250, 90, 71, 22));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxPosPrecisionLib->setPalette(palette2);
        doubleSpinBoxPosPrecisionLib->setReadOnly(true);
        doubleSpinBoxDiaPrecisionLib = new QDoubleSpinBox(frame);
        doubleSpinBoxDiaPrecisionLib->setObjectName("doubleSpinBoxDiaPrecisionLib");
        doubleSpinBoxDiaPrecisionLib->setGeometry(QRect(250, 70, 71, 22));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxDiaPrecisionLib->setPalette(palette3);
        doubleSpinBoxDiaPrecisionLib->setReadOnly(true);
        spinBoxNoiseSizeLib = new QSpinBox(frame);
        spinBoxNoiseSizeLib->setObjectName("spinBoxNoiseSizeLib");
        spinBoxNoiseSizeLib->setGeometry(QRect(250, 110, 71, 22));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        spinBoxNoiseSizeLib->setPalette(palette4);
        spinBoxNoiseSizeLib->setReadOnly(true);
        label_16 = new QLabel(frame);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(250, 50, 71, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_95 = new QLabel(frame);
        label_95->setObjectName("label_95");
        label_95->setGeometry(QRect(20, 190, 151, 21));
        label_95->setFrameShape(QFrame::Panel);
        label_95->setFrameShadow(QFrame::Sunken);
        label_95->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxCalcMode = new QComboBox(frame);
        comboBoxCalcMode->addItem(QString());
        comboBoxCalcMode->addItem(QString());
        comboBoxCalcMode->setObjectName("comboBoxCalcMode");
        comboBoxCalcMode->setGeometry(QRect(180, 190, 141, 22));
        label_6 = new QLabel(EditHolePosDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 62, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(EditHolePosDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 30, 61, 21));
        EditLibID->setReadOnly(true);
        pushButtonChangeLib = new QPushButton(EditHolePosDialog);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(310, 30, 31, 23));
        label_7 = new QLabel(EditHolePosDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 10, 241, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Edit_LibName = new QLineEdit(EditHolePosDialog);
        Edit_LibName->setObjectName("Edit_LibName");
        Edit_LibName->setGeometry(QRect(70, 30, 241, 21));
        Edit_LibName->setReadOnly(true);
        frame_2 = new QFrame(EditHolePosDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(360, 60, 201, 141));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        pushButtonTest = new QPushButton(frame_2);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(30, 10, 151, 31));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 50, 121, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 70, 121, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 90, 121, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 110, 121, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelHoleV = new QLabel(frame_2);
        labelHoleV->setObjectName("labelHoleV");
        labelHoleV->setGeometry(QRect(140, 50, 41, 21));
        labelHoleV->setFrameShape(QFrame::Panel);
        labelHoleV->setFrameShadow(QFrame::Sunken);
        labelHoleV->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelHoleH = new QLabel(frame_2);
        labelHoleH->setObjectName("labelHoleH");
        labelHoleH->setGeometry(QRect(140, 70, 41, 21));
        labelHoleH->setFrameShape(QFrame::Panel);
        labelHoleH->setFrameShadow(QFrame::Sunken);
        labelHoleH->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffX = new QLabel(frame_2);
        labelPosDiffX->setObjectName("labelPosDiffX");
        labelPosDiffX->setGeometry(QRect(140, 90, 41, 21));
        labelPosDiffX->setFrameShape(QFrame::Panel);
        labelPosDiffX->setFrameShadow(QFrame::Sunken);
        labelPosDiffX->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelPosDiffY = new QLabel(frame_2);
        labelPosDiffY->setObjectName("labelPosDiffY");
        labelPosDiffY->setGeometry(QRect(140, 110, 41, 21));
        labelPosDiffY->setFrameShape(QFrame::Panel);
        labelPosDiffY->setFrameShadow(QFrame::Sunken);
        labelPosDiffY->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLoadFromLibrary = new QPushButton(EditHolePosDialog);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(180, 350, 161, 41));
        ButtonReflectAllBlocks = new QPushButton(EditHolePosDialog);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(180, 300, 161, 41));
        ButtonSaveToLibrary = new QPushButton(EditHolePosDialog);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 350, 161, 41));
        ButtonClose = new QPushButton(EditHolePosDialog);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(390, 350, 171, 41));
        ButtonRelrectOnlyBlock = new QPushButton(EditHolePosDialog);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 300, 161, 41));

        retranslateUi(EditHolePosDialog);

        QMetaObject::connectSlotsByName(EditHolePosDialog);
    } // setupUi

    void retranslateUi(QWidget *EditHolePosDialog)
    {
        EditHolePosDialog->setWindowTitle(QCoreApplication::translate("EditHolePosDialog", "Threshold MeasureHolePos", nullptr));
        label_40->setText(QCoreApplication::translate("EditHolePosDialog", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\343\203\220\343\203\251\343\201\244\343\201\215\343\202\260\343\203\251\343\203\225", nullptr));
        label->setText(QCoreApplication::translate("EditHolePosDialog", "\347\251\264\345\276\204\347\262\276\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("EditHolePosDialog", "\344\275\215\347\275\256\347\262\276\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("EditHolePosDialog", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_92->setText(QCoreApplication::translate("EditHolePosDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_5->setText(QCoreApplication::translate("EditHolePosDialog", "\345\270\257\345\271\205", nullptr));
        EditName->setText(QString());
        label_4->setText(QCoreApplication::translate("EditHolePosDialog", "\345\200\213\345\210\245\345\220\215\347\247\260", nullptr));
        label_16->setText(QCoreApplication::translate("EditHolePosDialog", "Library", nullptr));
        label_95->setText(QCoreApplication::translate("EditHolePosDialog", "\350\250\210\346\270\254\346\226\271\346\263\225", nullptr));
        comboBoxCalcMode->setItemText(0, QCoreApplication::translate("EditHolePosDialog", "\351\253\230\351\200\237\350\250\210\346\270\254", nullptr));
        comboBoxCalcMode->setItemText(1, QCoreApplication::translate("EditHolePosDialog", "\351\253\230\347\262\276\345\272\246", nullptr));

        label_6->setText(QCoreApplication::translate("EditHolePosDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditHolePosDialog", "12345", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("EditHolePosDialog", "...", nullptr));
        label_7->setText(QCoreApplication::translate("EditHolePosDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        Edit_LibName->setText(QCoreApplication::translate("EditHolePosDialog", "XXX", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("EditHolePosDialog", "Test", nullptr));
        label_8->setText(QCoreApplication::translate("EditHolePosDialog", "\347\251\264\343\200\200\347\270\246\345\276\204", nullptr));
        label_9->setText(QCoreApplication::translate("EditHolePosDialog", "\347\251\264\343\200\200\346\250\252\345\276\204", nullptr));
        label_10->setText(QCoreApplication::translate("EditHolePosDialog", "\357\274\270\346\226\271\345\220\221\344\275\215\347\275\256\343\202\272\343\203\254", nullptr));
        label_11->setText(QCoreApplication::translate("EditHolePosDialog", "\357\274\271\346\226\271\345\220\221\344\275\215\347\275\256\343\202\272\343\203\254", nullptr));
        labelHoleV->setText(QString());
        labelHoleH->setText(QString());
        labelPosDiffX->setText(QString());
        labelPosDiffY->setText(QString());
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("EditHolePosDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("EditHolePosDialog", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\347\251\264\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("EditHolePosDialog", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonClose->setText(QCoreApplication::translate("EditHolePosDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("EditHolePosDialog", "\343\201\223\343\201\256\347\251\264\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditHolePosDialog: public Ui_EditHolePosDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITHOLEPOSDIALOG_H
