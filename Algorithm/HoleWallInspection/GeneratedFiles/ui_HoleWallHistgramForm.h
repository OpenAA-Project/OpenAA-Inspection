/********************************************************************************
** Form generated from reading UI file 'HoleWallHistgramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOLEWALLHISTGRAMFORM_H
#define UI_HOLEWALLHISTGRAMFORM_H

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

class Ui_HoleWallHistgramForm
{
public:
    QFrame *frame_SimImage;
    QToolButton *toolButtonSimShowNGMark;
    QToolButton *toolButtonSimShowBlock;
    QPushButton *pushButtonSimShowCenterPos;
    QPushButton *ButtonRelrectOnlyBlock;
    QPushButton *pushButtonRestore;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QWidget *page_3;
    QPushButton *ButtonRelrectSaveParts;
    QWidget *page_2;
    QFrame *frame;
    QLabel *label_31;
    QPushButton *ButtonCalc;
    QLabel *labelUnitName_11;
    QLabel *labelResultNGSize;
    QLabel *label_11;
    QLabel *labelResultNGSizeUnit;
    QPushButton *ButtonReflectAllBlocks;
    QPushButton *ButtonClose;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonSaveToLibrary;
    QLabel *label_5;
    QLabel *label_9;
    QLineEdit *EditLibName;
    QLineEdit *EditItemName;
    QLineEdit *EditLibID;
    QSpinBox *EditSearchDot;
    QLabel *label_27;
    QDoubleSpinBox *doubleSpinBoxSearchDotMM;
    QLabel *labelUnitName_4;
    QLabel *label_37;
    QLabel *labelUnitName_3;
    QDoubleSpinBox *doubleSpinBoxNGSizeMM;
    QSpinBox *EditNGSize;
    QFrame *frameLayer;
    QPushButton *pushButtonTransmitItemNameAll;
    QPushButton *pushButtonChangeLib;

    void setupUi(QWidget *HoleWallHistgramForm)
    {
        if (HoleWallHistgramForm->objectName().isEmpty())
            HoleWallHistgramForm->setObjectName("HoleWallHistgramForm");
        HoleWallHistgramForm->resize(795, 784);
        frame_SimImage = new QFrame(HoleWallHistgramForm);
        frame_SimImage->setObjectName("frame_SimImage");
        frame_SimImage->setGeometry(QRect(10, 60, 771, 461));
        frame_SimImage->setFrameShape(QFrame::StyledPanel);
        frame_SimImage->setFrameShadow(QFrame::Sunken);
        toolButtonSimShowNGMark = new QToolButton(HoleWallHistgramForm);
        toolButtonSimShowNGMark->setObjectName("toolButtonSimShowNGMark");
        toolButtonSimShowNGMark->setGeometry(QRect(200, 10, 141, 41));
        toolButtonSimShowNGMark->setCheckable(true);
        toolButtonSimShowNGMark->setChecked(true);
        toolButtonSimShowBlock = new QToolButton(HoleWallHistgramForm);
        toolButtonSimShowBlock->setObjectName("toolButtonSimShowBlock");
        toolButtonSimShowBlock->setGeometry(QRect(50, 10, 141, 41));
        toolButtonSimShowBlock->setCheckable(true);
        toolButtonSimShowBlock->setChecked(true);
        pushButtonSimShowCenterPos = new QPushButton(HoleWallHistgramForm);
        pushButtonSimShowCenterPos->setObjectName("pushButtonSimShowCenterPos");
        pushButtonSimShowCenterPos->setGeometry(QRect(390, 10, 111, 41));
        ButtonRelrectOnlyBlock = new QPushButton(HoleWallHistgramForm);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(10, 680, 171, 41));
        ButtonRelrectOnlyBlock->setAcceptDrops(true);
        pushButtonRestore = new QPushButton(HoleWallHistgramForm);
        pushButtonRestore->setObjectName("pushButtonRestore");
        pushButtonRestore->setGeometry(QRect(390, 730, 171, 41));
        pushButtonRestore->setAcceptDrops(true);
        stackedWidgetParts = new QStackedWidget(HoleWallHistgramForm);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(10, 750, 181, 41));
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
        frame = new QFrame(HoleWallHistgramForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(570, 530, 211, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_31 = new QLabel(frame);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(0, 0, 201, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonCalc = new QPushButton(frame);
        ButtonCalc->setObjectName("ButtonCalc");
        ButtonCalc->setGeometry(QRect(50, 90, 121, 31));
        ButtonCalc->setAcceptDrops(true);
        labelUnitName_11 = new QLabel(frame);
        labelUnitName_11->setObjectName("labelUnitName_11");
        labelUnitName_11->setGeometry(QRect(10, 50, 51, 20));
        labelUnitName_11->setFrameShape(QFrame::NoFrame);
        labelUnitName_11->setFrameShadow(QFrame::Sunken);
        labelUnitName_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelResultNGSize = new QLabel(frame);
        labelResultNGSize->setObjectName("labelResultNGSize");
        labelResultNGSize->setGeometry(QRect(120, 30, 81, 21));
        labelResultNGSize->setFrameShape(QFrame::Panel);
        labelResultNGSize->setFrameShadow(QFrame::Sunken);
        labelResultNGSize->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 30, 101, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultNGSizeUnit = new QLabel(frame);
        labelResultNGSizeUnit->setObjectName("labelResultNGSizeUnit");
        labelResultNGSizeUnit->setEnabled(false);
        labelResultNGSizeUnit->setGeometry(QRect(120, 50, 81, 21));
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
        ButtonReflectAllBlocks = new QPushButton(HoleWallHistgramForm);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(190, 680, 171, 41));
        ButtonReflectAllBlocks->setAcceptDrops(true);
        ButtonClose = new QPushButton(HoleWallHistgramForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(610, 720, 171, 51));
        ButtonLoadFromLibrary = new QPushButton(HoleWallHistgramForm);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(190, 730, 171, 41));
        ButtonLoadFromLibrary->setAcceptDrops(true);
        ButtonSaveToLibrary = new QPushButton(HoleWallHistgramForm);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 730, 171, 41));
        ButtonSaveToLibrary->setAcceptDrops(true);
        label_5 = new QLabel(HoleWallHistgramForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(80, 620, 101, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_9 = new QLabel(HoleWallHistgramForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 570, 191, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(HoleWallHistgramForm);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(80, 640, 101, 21));
        EditLibName->setReadOnly(true);
        EditItemName = new QLineEdit(HoleWallHistgramForm);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(20, 590, 141, 21));
        EditItemName->setReadOnly(false);
        EditLibID = new QLineEdit(HoleWallHistgramForm);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(20, 640, 61, 21));
        EditLibID->setReadOnly(true);
        EditSearchDot = new QSpinBox(HoleWallHistgramForm);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(260, 600, 81, 22));
        EditSearchDot->setMaximum(255);
        label_27 = new QLabel(HoleWallHistgramForm);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(250, 570, 291, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxSearchDotMM = new QDoubleSpinBox(HoleWallHistgramForm);
        doubleSpinBoxSearchDotMM->setObjectName("doubleSpinBoxSearchDotMM");
        doubleSpinBoxSearchDotMM->setGeometry(QRect(360, 600, 91, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        QBrush brush2(QColor(240, 240, 240, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        doubleSpinBoxSearchDotMM->setPalette(palette1);
        doubleSpinBoxSearchDotMM->setReadOnly(true);
        doubleSpinBoxSearchDotMM->setMaximum(9999999999.000000000000000);
        labelUnitName_4 = new QLabel(HoleWallHistgramForm);
        labelUnitName_4->setObjectName("labelUnitName_4");
        labelUnitName_4->setGeometry(QRect(450, 600, 91, 20));
        labelUnitName_4->setFrameShape(QFrame::NoFrame);
        labelUnitName_4->setFrameShadow(QFrame::Sunken);
        labelUnitName_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_37 = new QLabel(HoleWallHistgramForm);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(240, 640, 121, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelUnitName_3 = new QLabel(HoleWallHistgramForm);
        labelUnitName_3->setObjectName("labelUnitName_3");
        labelUnitName_3->setGeometry(QRect(450, 620, 91, 20));
        labelUnitName_3->setFrameShape(QFrame::NoFrame);
        labelUnitName_3->setFrameShadow(QFrame::Sunken);
        labelUnitName_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxNGSizeMM = new QDoubleSpinBox(HoleWallHistgramForm);
        doubleSpinBoxNGSizeMM->setObjectName("doubleSpinBoxNGSizeMM");
        doubleSpinBoxNGSizeMM->setGeometry(QRect(460, 640, 91, 22));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        doubleSpinBoxNGSizeMM->setPalette(palette2);
        doubleSpinBoxNGSizeMM->setMaximum(9999999999.000000000000000);
        EditNGSize = new QSpinBox(HoleWallHistgramForm);
        EditNGSize->setObjectName("EditNGSize");
        EditNGSize->setGeometry(QRect(370, 640, 91, 22));
        EditNGSize->setMinimum(-9999);
        EditNGSize->setMaximum(99999999);
        frameLayer = new QFrame(HoleWallHistgramForm);
        frameLayer->setObjectName("frameLayer");
        frameLayer->setGeometry(QRect(30, 530, 181, 41));
        frameLayer->setFrameShape(QFrame::NoFrame);
        frameLayer->setFrameShadow(QFrame::Plain);
        pushButtonTransmitItemNameAll = new QPushButton(HoleWallHistgramForm);
        pushButtonTransmitItemNameAll->setObjectName("pushButtonTransmitItemNameAll");
        pushButtonTransmitItemNameAll->setGeometry(QRect(160, 590, 51, 23));
        pushButtonChangeLib = new QPushButton(HoleWallHistgramForm);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(180, 640, 31, 23));

        retranslateUi(HoleWallHistgramForm);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(HoleWallHistgramForm);
    } // setupUi

    void retranslateUi(QWidget *HoleWallHistgramForm)
    {
        HoleWallHistgramForm->setWindowTitle(QCoreApplication::translate("HoleWallHistgramForm", "Form", nullptr));
        toolButtonSimShowNGMark->setText(QCoreApplication::translate("HoleWallHistgramForm", "NG mark", nullptr));
        toolButtonSimShowBlock->setText(QCoreApplication::translate("HoleWallHistgramForm", "Block", nullptr));
        pushButtonSimShowCenterPos->setText(QCoreApplication::translate("HoleWallHistgramForm", "\345\276\251\345\270\260", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("HoleWallHistgramForm", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        pushButtonRestore->setText(QCoreApplication::translate("HoleWallHistgramForm", "Restore", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("HoleWallHistgramForm", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        label_31->setText(QCoreApplication::translate("HoleWallHistgramForm", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\345\210\244\345\256\232\347\265\220\346\236\234", nullptr));
        ButtonCalc->setText(QCoreApplication::translate("HoleWallHistgramForm", "\350\250\210\347\256\227", nullptr));
        labelUnitName_11->setText(QCoreApplication::translate("HoleWallHistgramForm", "mm", nullptr));
        labelResultNGSize->setText(QCoreApplication::translate("HoleWallHistgramForm", "123", nullptr));
        label_11->setText(QCoreApplication::translate("HoleWallHistgramForm", "NG\343\202\265\343\202\244\343\202\272", nullptr));
        labelResultNGSizeUnit->setText(QCoreApplication::translate("HoleWallHistgramForm", "123", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("HoleWallHistgramForm", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\351\240\230\345\237\237\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonClose->setText(QCoreApplication::translate("HoleWallHistgramForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("HoleWallHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("HoleWallHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        label_5->setText(QCoreApplication::translate("HoleWallHistgramForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        label_9->setText(QCoreApplication::translate("HoleWallHistgramForm", "Item name", nullptr));
        EditLibName->setText(QCoreApplication::translate("HoleWallHistgramForm", "XXX", nullptr));
        EditItemName->setText(QCoreApplication::translate("HoleWallHistgramForm", "XXX", nullptr));
        EditLibID->setText(QCoreApplication::translate("HoleWallHistgramForm", "12345", nullptr));
        label_27->setText(QCoreApplication::translate("HoleWallHistgramForm", "Search area (Pixel)", nullptr));
        labelUnitName_4->setText(QCoreApplication::translate("HoleWallHistgramForm", "mm", nullptr));
        label_37->setText(QCoreApplication::translate("HoleWallHistgramForm", "NG size", nullptr));
        labelUnitName_3->setText(QCoreApplication::translate("HoleWallHistgramForm", "mm", nullptr));
        pushButtonTransmitItemNameAll->setText(QCoreApplication::translate("HoleWallHistgramForm", "To all", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("HoleWallHistgramForm", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HoleWallHistgramForm: public Ui_HoleWallHistgramForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOLEWALLHISTGRAMFORM_H
