/********************************************************************************
** Form generated from reading UI file 'PropertyMaskingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYMASKINGFORM_H
#define UI_PROPERTYMASKINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropertyMaskingFormClass
{
public:
    QTableWidget *tableWidgetMaskingList;
    QFrame *frameButton;
    QPushButton *pushButton;
    QFrame *frame;
    QPushButton *ButtonGenerateMaskFromSameColor;
    QFrame *frameGenerateMask;
    QLabel *label_3;
    QLabel *label_2;
    QSpinBox *spinBoxPickupColorWidth;
    QSpinBox *spinBoxExpandedDot;
    QPushButton *pushButtonLimited;
    QLabel *labelPourMessage;
    QFrame *frame_2;
    QToolButton *toolButtonGenerateExclusive;
    QToolButton *toolButtonGenerateOnClick;
    QLabel *label_5;
    QSpinBox *spinBoxMinSize;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBoxMinSizeMM;
    QDoubleSpinBox *doubleSpinBoxExpandedDotMM;
    QLabel *label_9;
    QLabel *label_10;
    QSpinBox *spinBoxPickupNoiseSize;
    QPushButton *ButtonGenerateMaskOnSelectedItemsEdge;
    QPushButton *ButtonGenerateMaskPatternEdgeOnSelected;
    QPushButton *pushButtonEditLibrary;
    QLabel *label;
    QPushButton *pushButtonMakeBackGroundMaster;
    QPushButton *pushButtonMakeBackGroundTarget;
    QToolButton *toolButtonShowBackGround;
    QPushButton *pushButtonClearBackGround;
    QPushButton *pushButtonSelectByLimited;
    QPushButton *pushButtonSelectAll;
    QPushButton *pushButtonShowOnlyLibID;

    void setupUi(QWidget *PropertyMaskingFormClass)
    {
        if (PropertyMaskingFormClass->objectName().isEmpty())
            PropertyMaskingFormClass->setObjectName("PropertyMaskingFormClass");
        PropertyMaskingFormClass->resize(400, 800);
        tableWidgetMaskingList = new QTableWidget(PropertyMaskingFormClass);
        if (tableWidgetMaskingList->columnCount() < 5)
            tableWidgetMaskingList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetMaskingList->setObjectName("tableWidgetMaskingList");
        tableWidgetMaskingList->setGeometry(QRect(10, 130, 381, 291));
        tableWidgetMaskingList->setFrameShape(QFrame::Panel);
        tableWidgetMaskingList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetMaskingList->setWordWrap(false);
        tableWidgetMaskingList->setCornerButtonEnabled(false);
        frameButton = new QFrame(PropertyMaskingFormClass);
        frameButton->setObjectName("frameButton");
        frameButton->setGeometry(QRect(10, 0, 381, 41));
        frameButton->setFrameShape(QFrame::StyledPanel);
        frameButton->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frameButton);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Hole.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        frame = new QFrame(PropertyMaskingFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 450, 381, 321));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        ButtonGenerateMaskFromSameColor = new QPushButton(frame);
        ButtonGenerateMaskFromSameColor->setObjectName("ButtonGenerateMaskFromSameColor");
        ButtonGenerateMaskFromSameColor->setGeometry(QRect(60, 200, 251, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateMaskFromSameColor->setIcon(icon1);
        frameGenerateMask = new QFrame(frame);
        frameGenerateMask->setObjectName("frameGenerateMask");
        frameGenerateMask->setGeometry(QRect(4, 6, 371, 191));
        QPalette palette;
        frameGenerateMask->setPalette(palette);
        frameGenerateMask->setFrameShape(QFrame::StyledPanel);
        frameGenerateMask->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frameGenerateMask);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 87, 91, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(frameGenerateMask);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 87, 61, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPickupColorWidth = new QSpinBox(frameGenerateMask);
        spinBoxPickupColorWidth->setObjectName("spinBoxPickupColorWidth");
        spinBoxPickupColorWidth->setGeometry(QRect(10, 107, 61, 22));
        spinBoxPickupColorWidth->setMaximum(256);
        spinBoxPickupColorWidth->setValue(30);
        spinBoxExpandedDot = new QSpinBox(frameGenerateMask);
        spinBoxExpandedDot->setObjectName("spinBoxExpandedDot");
        spinBoxExpandedDot->setGeometry(QRect(80, 107, 71, 22));
        spinBoxExpandedDot->setMinimum(-100);
        spinBoxExpandedDot->setMaximum(100);
        pushButtonLimited = new QPushButton(frameGenerateMask);
        pushButtonLimited->setObjectName("pushButtonLimited");
        pushButtonLimited->setGeometry(QRect(10, 156, 211, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Mask.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLimited->setIcon(icon2);
        labelPourMessage = new QLabel(frameGenerateMask);
        labelPourMessage->setObjectName("labelPourMessage");
        labelPourMessage->setGeometry(QRect(230, 159, 131, 27));
        labelPourMessage->setFrameShape(QFrame::Panel);
        labelPourMessage->setFrameShadow(QFrame::Sunken);
        labelPourMessage->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame_2 = new QFrame(frameGenerateMask);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 351, 71));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        toolButtonGenerateExclusive = new QToolButton(frame_2);
        toolButtonGenerateExclusive->setObjectName("toolButtonGenerateExclusive");
        toolButtonGenerateExclusive->setGeometry(QRect(0, 40, 351, 31));
        toolButtonGenerateExclusive->setCheckable(true);
        toolButtonGenerateExclusive->setChecked(false);
        toolButtonGenerateExclusive->setAutoExclusive(false);
        toolButtonGenerateOnClick = new QToolButton(frame_2);
        toolButtonGenerateOnClick->setObjectName("toolButtonGenerateOnClick");
        toolButtonGenerateOnClick->setGeometry(QRect(0, 0, 351, 31));
        toolButtonGenerateOnClick->setCheckable(true);
        toolButtonGenerateOnClick->setChecked(false);
        toolButtonGenerateOnClick->setAutoExclusive(false);
        label_5 = new QLabel(frameGenerateMask);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(180, 87, 101, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMinSize = new QSpinBox(frameGenerateMask);
        spinBoxMinSize->setObjectName("spinBoxMinSize");
        spinBoxMinSize->setGeometry(QRect(180, 107, 71, 22));
        spinBoxMinSize->setMaximum(2000000000);
        spinBoxMinSize->setValue(30);
        label_4 = new QLabel(frameGenerateMask);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(150, 107, 31, 18));
        label_6 = new QLabel(frameGenerateMask);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(150, 130, 31, 18));
        label_7 = new QLabel(frameGenerateMask);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(250, 110, 31, 18));
        label_8 = new QLabel(frameGenerateMask);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(250, 130, 38, 18));
        doubleSpinBoxMinSizeMM = new QDoubleSpinBox(frameGenerateMask);
        doubleSpinBoxMinSizeMM->setObjectName("doubleSpinBoxMinSizeMM");
        doubleSpinBoxMinSizeMM->setGeometry(QRect(180, 130, 71, 24));
        doubleSpinBoxMinSizeMM->setMaximum(2000000000.000000000000000);
        doubleSpinBoxExpandedDotMM = new QDoubleSpinBox(frameGenerateMask);
        doubleSpinBoxExpandedDotMM->setObjectName("doubleSpinBoxExpandedDotMM");
        doubleSpinBoxExpandedDotMM->setGeometry(QRect(80, 130, 71, 24));
        doubleSpinBoxExpandedDotMM->setMinimum(-100.000000000000000);
        doubleSpinBoxExpandedDotMM->setMaximum(100.000000000000000);
        label_9 = new QLabel(frameGenerateMask);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(284, 87, 71, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_10 = new QLabel(frameGenerateMask);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(344, 110, 21, 18));
        spinBoxPickupNoiseSize = new QSpinBox(frameGenerateMask);
        spinBoxPickupNoiseSize->setObjectName("spinBoxPickupNoiseSize");
        spinBoxPickupNoiseSize->setGeometry(QRect(284, 107, 61, 22));
        spinBoxPickupNoiseSize->setMaximum(20);
        spinBoxPickupNoiseSize->setValue(3);
        ButtonGenerateMaskOnSelectedItemsEdge = new QPushButton(frame);
        ButtonGenerateMaskOnSelectedItemsEdge->setObjectName("ButtonGenerateMaskOnSelectedItemsEdge");
        ButtonGenerateMaskOnSelectedItemsEdge->setGeometry(QRect(60, 240, 251, 31));
        ButtonGenerateMaskOnSelectedItemsEdge->setIcon(icon1);
        ButtonGenerateMaskPatternEdgeOnSelected = new QPushButton(frame);
        ButtonGenerateMaskPatternEdgeOnSelected->setObjectName("ButtonGenerateMaskPatternEdgeOnSelected");
        ButtonGenerateMaskPatternEdgeOnSelected->setGeometry(QRect(60, 280, 251, 31));
        ButtonGenerateMaskPatternEdgeOnSelected->setIcon(icon1);
        pushButtonEditLibrary = new QPushButton(PropertyMaskingFormClass);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(260, 50, 131, 34));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon3);
        label = new QLabel(PropertyMaskingFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 430, 381, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonMakeBackGroundMaster = new QPushButton(PropertyMaskingFormClass);
        pushButtonMakeBackGroundMaster->setObjectName("pushButtonMakeBackGroundMaster");
        pushButtonMakeBackGroundMaster->setGeometry(QRect(10, 90, 81, 34));
        pushButtonMakeBackGroundTarget = new QPushButton(PropertyMaskingFormClass);
        pushButtonMakeBackGroundTarget->setObjectName("pushButtonMakeBackGroundTarget");
        pushButtonMakeBackGroundTarget->setGeometry(QRect(100, 90, 81, 34));
        toolButtonShowBackGround = new QToolButton(PropertyMaskingFormClass);
        toolButtonShowBackGround->setObjectName("toolButtonShowBackGround");
        toolButtonShowBackGround->setGeometry(QRect(300, 90, 81, 34));
        toolButtonShowBackGround->setCheckable(true);
        pushButtonClearBackGround = new QPushButton(PropertyMaskingFormClass);
        pushButtonClearBackGround->setObjectName("pushButtonClearBackGround");
        pushButtonClearBackGround->setGeometry(QRect(190, 90, 81, 34));
        pushButtonSelectByLimited = new QPushButton(PropertyMaskingFormClass);
        pushButtonSelectByLimited->setObjectName("pushButtonSelectByLimited");
        pushButtonSelectByLimited->setGeometry(QRect(100, 50, 151, 34));
        pushButtonSelectAll = new QPushButton(PropertyMaskingFormClass);
        pushButtonSelectAll->setObjectName("pushButtonSelectAll");
        pushButtonSelectAll->setGeometry(QRect(10, 50, 81, 34));
        pushButtonShowOnlyLibID = new QPushButton(PropertyMaskingFormClass);
        pushButtonShowOnlyLibID->setObjectName("pushButtonShowOnlyLibID");
        pushButtonShowOnlyLibID->setGeometry(QRect(10, 130, 171, 34));
        pushButtonShowOnlyLibID->setCheckable(true);
        pushButtonShowOnlyLibID->raise();
        tableWidgetMaskingList->raise();
        frameButton->raise();
        frame->raise();
        pushButtonEditLibrary->raise();
        label->raise();
        pushButtonMakeBackGroundMaster->raise();
        pushButtonMakeBackGroundTarget->raise();
        toolButtonShowBackGround->raise();
        pushButtonClearBackGround->raise();
        pushButtonSelectByLimited->raise();
        pushButtonSelectAll->raise();

        retranslateUi(PropertyMaskingFormClass);

        QMetaObject::connectSlotsByName(PropertyMaskingFormClass);
    } // setupUi

    void retranslateUi(QWidget *PropertyMaskingFormClass)
    {
        PropertyMaskingFormClass->setWindowTitle(QCoreApplication::translate("PropertyMaskingFormClass", "PropertyMaskingForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetMaskingList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyMaskingFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetMaskingList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyMaskingFormClass", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMaskingList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyMaskingFormClass", "Effective", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMaskingList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyMaskingFormClass", "Limited", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetMaskingList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyMaskingFormClass", "Area", nullptr));
        pushButton->setText(QCoreApplication::translate("PropertyMaskingFormClass", "PushButton", nullptr));
        ButtonGenerateMaskFromSameColor->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\345\220\214\344\270\200\350\274\235\345\272\246\343\201\213\343\202\211\343\201\256\343\203\236\343\202\271\343\202\257\347\224\237\346\210\220", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\350\274\235\345\272\246\345\271\205", nullptr));
        pushButtonLimited->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\346\234\211\345\212\271\357\274\217\347\204\241\345\212\271\357\274\217\351\231\220\345\256\232\343\203\236\343\202\271\343\202\257", nullptr));
        labelPourMessage->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\346\234\211\345\212\271\343\203\236\343\202\271\343\202\257", nullptr));
        toolButtonGenerateExclusive->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\343\202\257\343\203\252\343\203\203\343\202\257\344\275\215\347\275\256\343\201\256\350\211\262\357\274\210\350\274\235\345\272\246\357\274\211\343\202\222\351\231\244\345\244\226\343\201\231\343\202\213\351\240\230\345\237\237\347\224\237\346\210\220", nullptr));
        toolButtonGenerateOnClick->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\343\202\257\343\203\252\343\203\203\343\202\257\344\275\215\347\275\256\343\201\256\350\211\262\357\274\210\350\274\235\345\272\246\357\274\211\343\202\222\345\237\272\346\272\226\343\201\250\343\201\227\343\201\237\351\240\230\345\237\237\347\224\237\346\210\220", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyMaskingFormClass", "Dot", nullptr));
        label_6->setText(QCoreApplication::translate("PropertyMaskingFormClass", "mm", nullptr));
        label_7->setText(QCoreApplication::translate("PropertyMaskingFormClass", "Dot", nullptr));
        label_8->setText(QCoreApplication::translate("PropertyMaskingFormClass", "mm2", nullptr));
        label_9->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\351\231\244\345\216\273\343\203\216\343\202\244\343\202\272", nullptr));
        label_10->setText(QCoreApplication::translate("PropertyMaskingFormClass", "Dot", nullptr));
        ButtonGenerateMaskOnSelectedItemsEdge->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\351\201\270\346\212\236\351\240\230\345\237\237\343\201\256\350\274\252\351\203\255\351\203\250\345\210\206\343\201\253\347\224\237\346\210\220", nullptr));
        ButtonGenerateMaskPatternEdgeOnSelected->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\351\201\270\346\212\236\351\240\230\345\237\237\343\201\256\343\203\221\343\202\277\343\203\274\343\203\263\345\242\203\347\225\214\351\203\250\345\210\206\343\201\253\347\224\237\346\210\220", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyMaskingFormClass", "Edit library", nullptr));
        label->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\343\203\236\343\202\271\343\202\257\347\224\237\346\210\220", nullptr));
        pushButtonMakeBackGroundMaster->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\350\203\214\346\231\257-M", nullptr));
        pushButtonMakeBackGroundTarget->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\350\203\214\346\231\257-T", nullptr));
        toolButtonShowBackGround->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\350\203\214\346\231\257\350\241\250\347\244\272", nullptr));
        pushButtonClearBackGround->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\350\203\214\346\231\257\346\266\210\345\216\273", nullptr));
        pushButtonSelectByLimited->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\351\231\220\345\256\232\351\201\270\346\212\236", nullptr));
        pushButtonSelectAll->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\345\205\250\351\203\250\351\201\270\346\212\236", nullptr));
        pushButtonShowOnlyLibID->setText(QCoreApplication::translate("PropertyMaskingFormClass", "\351\201\270\346\212\236\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\256\343\201\277\350\241\250\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyMaskingFormClass: public Ui_PropertyMaskingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYMASKINGFORM_H
