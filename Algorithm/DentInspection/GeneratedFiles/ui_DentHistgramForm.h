/********************************************************************************
** Form generated from reading UI file 'DentHistgramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DENTHISTGRAMFORM_H
#define UI_DENTHISTGRAMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DentHistgramForm
{
public:
    QToolButton *toolButtonSimShowBlock;
    QLineEdit *EditLibID;
    QLineEdit *EditItemName;
    QToolButton *toolButtonSimShowBright;
    QLabel *label_4;
    QPushButton *ButtonClose;
    QLabel *label_5;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QWidget *page_3;
    QPushButton *ButtonRelrectSaveParts;
    QWidget *page_2;
    QPushButton *pushButtonChangeLib;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *pushButtonTransmitItemNameAll;
    QPushButton *ButtonRelrectOnlyBlock;
    QFrame *frame;
    QLabel *label_31;
    QLabel *label;
    QLabel *labelResultNGSize;
    QPushButton *ButtonCalc;
    QLabel *labelResultNGSizeUnit;
    QLabel *labelUnitName_1;
    QLabel *label_9;
    QPushButton *ButtonLoadFromLibrary;
    QFrame *frame_SimImage;
    QLineEdit *EditLibName;
    QPushButton *ButtonReflectAllBlocks;
    QFrame *frameLayer;
    QFrame *frame_2;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBoxMinNGSize;
    QLabel *label_19;
    QDoubleSpinBox *doubleSpinBoxMaxNGSize;
    QSpinBox *EditLinesForAverage;
    QLabel *label_24;
    QDoubleSpinBox *doubleSpinBoxMaxDiffCoef;
    QLabel *label_25;
    QToolButton *toolButtonShowResult;
    QLabel *label_6;
    QLineEdit *EditResultMaxD;
    QLineEdit *EditResultWaveLen;
    QLabel *label_7;

    void setupUi(QWidget *DentHistgramForm)
    {
        if (DentHistgramForm->objectName().isEmpty())
            DentHistgramForm->setObjectName("DentHistgramForm");
        DentHistgramForm->resize(1030, 669);
        toolButtonSimShowBlock = new QToolButton(DentHistgramForm);
        toolButtonSimShowBlock->setObjectName("toolButtonSimShowBlock");
        toolButtonSimShowBlock->setGeometry(QRect(10, 10, 141, 51));
        toolButtonSimShowBlock->setCheckable(true);
        toolButtonSimShowBlock->setChecked(true);
        EditLibID = new QLineEdit(DentHistgramForm);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 540, 61, 21));
        EditLibID->setReadOnly(true);
        EditItemName = new QLineEdit(DentHistgramForm);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(150, 490, 191, 21));
        EditItemName->setReadOnly(false);
        toolButtonSimShowBright = new QToolButton(DentHistgramForm);
        toolButtonSimShowBright->setObjectName("toolButtonSimShowBright");
        toolButtonSimShowBright->setGeometry(QRect(10, 170, 141, 51));
        toolButtonSimShowBright->setCheckable(true);
        toolButtonSimShowBright->setChecked(true);
        label_4 = new QLabel(DentHistgramForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 520, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonClose = new QPushButton(DentHistgramForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(400, 620, 201, 41));
        label_5 = new QLabel(DentHistgramForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 520, 151, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidgetParts = new QStackedWidget(DentHistgramForm);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(10, 580, 181, 41));
        page = new QWidget();
        page->setObjectName("page");
        stackedWidgetParts->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        ButtonRelrectSaveParts = new QPushButton(page_3);
        ButtonRelrectSaveParts->setObjectName("ButtonRelrectSaveParts");
        ButtonRelrectSaveParts->setGeometry(QRect(0, 0, 171, 41));
        stackedWidgetParts->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetParts->addWidget(page_2);
        pushButtonChangeLib = new QPushButton(DentHistgramForm);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(220, 540, 31, 23));
        ButtonSaveToLibrary = new QPushButton(DentHistgramForm);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 620, 171, 41));
        ButtonSaveToLibrary->setAcceptDrops(true);
        pushButtonTransmitItemNameAll = new QPushButton(DentHistgramForm);
        pushButtonTransmitItemNameAll->setObjectName("pushButtonTransmitItemNameAll");
        pushButtonTransmitItemNameAll->setGeometry(QRect(340, 490, 51, 23));
        ButtonRelrectOnlyBlock = new QPushButton(DentHistgramForm);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 580, 171, 41));
        ButtonRelrectOnlyBlock->setAcceptDrops(true);
        frame = new QFrame(DentHistgramForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(770, 460, 241, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_31 = new QLabel(frame);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(0, 0, 241, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 131, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultNGSize = new QLabel(frame);
        labelResultNGSize->setObjectName("labelResultNGSize");
        labelResultNGSize->setGeometry(QRect(150, 30, 81, 21));
        labelResultNGSize->setFrameShape(QFrame::Panel);
        labelResultNGSize->setFrameShadow(QFrame::Sunken);
        labelResultNGSize->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonCalc = new QPushButton(frame);
        ButtonCalc->setObjectName("ButtonCalc");
        ButtonCalc->setGeometry(QRect(50, 90, 161, 31));
        ButtonCalc->setAcceptDrops(true);
        labelResultNGSizeUnit = new QLabel(frame);
        labelResultNGSizeUnit->setObjectName("labelResultNGSizeUnit");
        labelResultNGSizeUnit->setGeometry(QRect(150, 50, 81, 21));
        QPalette palette;
        QBrush brush(QColor(255, 255, 127, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(255, 170, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        labelResultNGSizeUnit->setPalette(palette);
        labelResultNGSizeUnit->setAutoFillBackground(true);
        labelResultNGSizeUnit->setFrameShape(QFrame::Panel);
        labelResultNGSizeUnit->setFrameShadow(QFrame::Sunken);
        labelResultNGSizeUnit->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelUnitName_1 = new QLabel(frame);
        labelUnitName_1->setObjectName("labelUnitName_1");
        labelUnitName_1->setGeometry(QRect(10, 50, 131, 20));
        labelUnitName_1->setFrameShape(QFrame::NoFrame);
        labelUnitName_1->setFrameShadow(QFrame::Sunken);
        labelUnitName_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_9 = new QLabel(DentHistgramForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 490, 141, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLoadFromLibrary = new QPushButton(DentHistgramForm);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(190, 620, 201, 41));
        ButtonLoadFromLibrary->setAcceptDrops(true);
        frame_SimImage = new QFrame(DentHistgramForm);
        frame_SimImage->setObjectName("frame_SimImage");
        frame_SimImage->setGeometry(QRect(160, 10, 861, 431));
        frame_SimImage->setFrameShape(QFrame::StyledPanel);
        frame_SimImage->setFrameShadow(QFrame::Raised);
        EditLibName = new QLineEdit(DentHistgramForm);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(70, 540, 151, 21));
        EditLibName->setReadOnly(true);
        ButtonReflectAllBlocks = new QPushButton(DentHistgramForm);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(190, 580, 201, 41));
        ButtonReflectAllBlocks->setAcceptDrops(true);
        frameLayer = new QFrame(DentHistgramForm);
        frameLayer->setObjectName("frameLayer");
        frameLayer->setGeometry(QRect(20, 450, 171, 41));
        frameLayer->setFrameShape(QFrame::NoFrame);
        frameLayer->setFrameShadow(QFrame::Plain);
        frame_2 = new QFrame(DentHistgramForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(400, 460, 361, 121));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_18 = new QLabel(frame_2);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 10, 221, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxMinNGSize = new QDoubleSpinBox(frame_2);
        doubleSpinBoxMinNGSize->setObjectName("doubleSpinBoxMinNGSize");
        doubleSpinBoxMinNGSize->setGeometry(QRect(240, 10, 111, 24));
        doubleSpinBoxMinNGSize->setDecimals(3);
        doubleSpinBoxMinNGSize->setMaximum(99999999.000000000000000);
        label_19 = new QLabel(frame_2);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(10, 30, 221, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxMaxNGSize = new QDoubleSpinBox(frame_2);
        doubleSpinBoxMaxNGSize->setObjectName("doubleSpinBoxMaxNGSize");
        doubleSpinBoxMaxNGSize->setGeometry(QRect(240, 30, 111, 24));
        doubleSpinBoxMaxNGSize->setDecimals(3);
        doubleSpinBoxMaxNGSize->setMaximum(99999999.000000000000000);
        EditLinesForAverage = new QSpinBox(frame_2);
        EditLinesForAverage->setObjectName("EditLinesForAverage");
        EditLinesForAverage->setGeometry(QRect(240, 90, 111, 20));
        QFont font;
        font.setPointSize(9);
        EditLinesForAverage->setFont(font);
        label_24 = new QLabel(frame_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 60, 221, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxMaxDiffCoef = new QDoubleSpinBox(frame_2);
        doubleSpinBoxMaxDiffCoef->setObjectName("doubleSpinBoxMaxDiffCoef");
        doubleSpinBoxMaxDiffCoef->setGeometry(QRect(240, 60, 111, 24));
        doubleSpinBoxMaxDiffCoef->setDecimals(3);
        doubleSpinBoxMaxDiffCoef->setMaximum(99999999.000000000000000);
        label_25 = new QLabel(frame_2);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 90, 221, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        toolButtonShowResult = new QToolButton(DentHistgramForm);
        toolButtonShowResult->setObjectName("toolButtonShowResult");
        toolButtonShowResult->setGeometry(QRect(10, 60, 141, 51));
        toolButtonShowResult->setCheckable(true);
        toolButtonShowResult->setChecked(true);
        label_6 = new QLabel(DentHistgramForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(11, 260, 141, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditResultMaxD = new QLineEdit(DentHistgramForm);
        EditResultMaxD->setObjectName("EditResultMaxD");
        EditResultMaxD->setGeometry(QRect(70, 280, 81, 21));
        EditResultMaxD->setReadOnly(true);
        EditResultWaveLen = new QLineEdit(DentHistgramForm);
        EditResultWaveLen->setObjectName("EditResultWaveLen");
        EditResultWaveLen->setGeometry(QRect(69, 330, 81, 21));
        EditResultWaveLen->setReadOnly(true);
        label_7 = new QLabel(DentHistgramForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 310, 141, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(DentHistgramForm);

        ButtonClose->setDefault(true);
        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DentHistgramForm);
    } // setupUi

    void retranslateUi(QWidget *DentHistgramForm)
    {
        DentHistgramForm->setWindowTitle(QCoreApplication::translate("DentHistgramForm", "Form", nullptr));
        toolButtonSimShowBlock->setText(QCoreApplication::translate("DentHistgramForm", "Block", nullptr));
        EditLibID->setText(QCoreApplication::translate("DentHistgramForm", "12345", nullptr));
        EditItemName->setText(QCoreApplication::translate("DentHistgramForm", "XXX", nullptr));
        toolButtonSimShowBright->setText(QCoreApplication::translate("DentHistgramForm", "\350\274\235\345\272\246NG", nullptr));
        label_4->setText(QCoreApplication::translate("DentHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        ButtonClose->setText(QCoreApplication::translate("DentHistgramForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_5->setText(QCoreApplication::translate("DentHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("DentHistgramForm", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("DentHistgramForm", "...", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("DentHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        pushButtonTransmitItemNameAll->setText(QCoreApplication::translate("DentHistgramForm", "To all", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("DentHistgramForm", "\343\201\223\343\201\256\351\240\230\345\237\237\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        label_31->setText(QCoreApplication::translate("DentHistgramForm", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\345\210\244\345\256\232\347\265\220\346\236\234", nullptr));
        label->setText(QCoreApplication::translate("DentHistgramForm", "NG\343\202\265\343\202\244\343\202\272", nullptr));
        labelResultNGSize->setText(QCoreApplication::translate("DentHistgramForm", "123", nullptr));
        ButtonCalc->setText(QCoreApplication::translate("DentHistgramForm", "\350\250\210\347\256\227", nullptr));
        labelResultNGSizeUnit->setText(QCoreApplication::translate("DentHistgramForm", "123", nullptr));
        labelUnitName_1->setText(QCoreApplication::translate("DentHistgramForm", "mm", nullptr));
        label_9->setText(QCoreApplication::translate("DentHistgramForm", "Item name", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("DentHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        EditLibName->setText(QCoreApplication::translate("DentHistgramForm", "XXX", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("DentHistgramForm", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\351\240\230\345\237\237\343\201\253\345\217\215\346\230\240", nullptr));
        label_18->setText(QCoreApplication::translate("DentHistgramForm", "Minimum NG size", nullptr));
        label_19->setText(QCoreApplication::translate("DentHistgramForm", "Maximum NG size", nullptr));
        label_24->setText(QCoreApplication::translate("DentHistgramForm", "\346\244\234\345\207\272\343\201\256\346\263\242\351\225\267\345\267\256\347\225\260", nullptr));
        label_25->setText(QCoreApplication::translate("DentHistgramForm", "\347\270\246\346\226\271\345\220\221\343\201\256\345\271\263\345\235\207\345\214\226\343\203\251\343\202\244\343\203\263\346\225\260", nullptr));
        toolButtonShowResult->setText(QCoreApplication::translate("DentHistgramForm", "\350\250\210\347\256\227\347\265\220\346\236\234", nullptr));
        label_6->setText(QCoreApplication::translate("DentHistgramForm", "\343\203\235\343\202\244\343\203\263\343\203\210\345\200\213\346\211\200\343\201\256\345\210\244\345\256\232\345\200\244", nullptr));
        EditResultMaxD->setText(QCoreApplication::translate("DentHistgramForm", "12345", nullptr));
        EditResultWaveLen->setText(QCoreApplication::translate("DentHistgramForm", "12345", nullptr));
        label_7->setText(QCoreApplication::translate("DentHistgramForm", "\343\203\235\343\202\244\343\203\263\343\203\210\345\200\213\346\211\200\343\201\256\346\263\242\351\225\267\345\200\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DentHistgramForm: public Ui_DentHistgramForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DENTHISTGRAMFORM_H
