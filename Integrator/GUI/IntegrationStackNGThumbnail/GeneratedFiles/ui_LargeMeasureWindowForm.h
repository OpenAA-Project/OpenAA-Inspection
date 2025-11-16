/********************************************************************************
** Form generated from reading UI file 'LargeMeasureWindowForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LARGEMEASUREWINDOWFORM_H
#define UI_LARGEMEASUREWINDOWFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LargeMeasureWindowForm
{
public:
    QLabel *label_3;
    QPushButton *pushButtonClose;
    QLabel *label_2;
    QPushButton *PushButtonOKbyDistance;
    QPushButton *PushButtonExpand2Side;
    QPushButton *PushButtonExpand1Side;
    QStackedWidget *stackedWidgetMaster;
    QWidget *Horizontal;
    QFrame *frameMasterWholeH;
    QFrame *frameMasteEdge1H;
    QFrame *frameMasteEdge2H;
    QLabel *label_12;
    QLabel *label_13;
    QWidget *Vertical;
    QFrame *frameMasteEdge2V;
    QFrame *frameMasteEdge1V;
    QFrame *frameMasterWholeV;
    QLabel *label;
    QLabel *label_7;
    QStackedWidget *stackedWidgetTarget;
    QWidget *Horizontal1;
    QFrame *frameTargetEdge2H;
    QFrame *frameTargetEdge1H;
    QFrame *frameTargetWholeH;
    QLabel *label_14;
    QLabel *label_15;
    QWidget *Vertical1;
    QFrame *frameTargetWholeV;
    QFrame *frameTargetEdge1V;
    QFrame *frameTargetEdge2V;
    QLabel *label_8;
    QLabel *label_11;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxResultMM;
    QDoubleSpinBox *doubleSpinBoxResult;
    QLabel *label_5;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBoxMinDistance;
    QDoubleSpinBox *doubleSpinBoxMinDistanceMM;
    QLabel *label_9;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBoxMaxDistance;
    QDoubleSpinBox *doubleSpinBoxMaxDistanceMM;

    void setupUi(QWidget *LargeMeasureWindowForm)
    {
        if (LargeMeasureWindowForm->objectName().isEmpty())
            LargeMeasureWindowForm->setObjectName("LargeMeasureWindowForm");
        LargeMeasureWindowForm->resize(893, 599);
        label_3 = new QLabel(LargeMeasureWindowForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(450, 0, 441, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonClose = new QPushButton(LargeMeasureWindowForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(740, 530, 141, 61));
        QFont font;
        font.setPointSize(12);
        pushButtonClose->setFont(font);
        pushButtonClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(120, 254, 180, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        label_2 = new QLabel(LargeMeasureWindowForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 441, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        PushButtonOKbyDistance = new QPushButton(LargeMeasureWindowForm);
        PushButtonOKbyDistance->setObjectName("PushButtonOKbyDistance");
        PushButtonOKbyDistance->setGeometry(QRect(740, 460, 141, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font1.setPointSize(12);
        PushButtonOKbyDistance->setFont(font1);
        PushButtonOKbyDistance->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonOKbyDistance->setCheckable(false);
        PushButtonOKbyDistance->setAutoDefault(false);
        PushButtonOKbyDistance->setFlat(false);
        PushButtonExpand2Side = new QPushButton(LargeMeasureWindowForm);
        PushButtonExpand2Side->setObjectName("PushButtonExpand2Side");
        PushButtonExpand2Side->setGeometry(QRect(590, 460, 141, 61));
        PushButtonExpand2Side->setFont(font1);
        PushButtonExpand2Side->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonExpand2Side->setCheckable(false);
        PushButtonExpand2Side->setAutoDefault(false);
        PushButtonExpand2Side->setFlat(false);
        PushButtonExpand1Side = new QPushButton(LargeMeasureWindowForm);
        PushButtonExpand1Side->setObjectName("PushButtonExpand1Side");
        PushButtonExpand1Side->setGeometry(QRect(440, 460, 141, 61));
        PushButtonExpand1Side->setFont(font1);
        PushButtonExpand1Side->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        PushButtonExpand1Side->setCheckable(false);
        PushButtonExpand1Side->setAutoDefault(false);
        PushButtonExpand1Side->setFlat(false);
        stackedWidgetMaster = new QStackedWidget(LargeMeasureWindowForm);
        stackedWidgetMaster->setObjectName("stackedWidgetMaster");
        stackedWidgetMaster->setGeometry(QRect(0, 20, 441, 431));
        Horizontal = new QWidget();
        Horizontal->setObjectName("Horizontal");
        frameMasterWholeH = new QFrame(Horizontal);
        frameMasterWholeH->setObjectName("frameMasterWholeH");
        frameMasterWholeH->setGeometry(QRect(0, 0, 441, 171));
        frameMasterWholeH->setFrameShape(QFrame::StyledPanel);
        frameMasterWholeH->setFrameShadow(QFrame::Raised);
        frameMasteEdge1H = new QFrame(Horizontal);
        frameMasteEdge1H->setObjectName("frameMasteEdge1H");
        frameMasteEdge1H->setGeometry(QRect(0, 210, 211, 201));
        frameMasteEdge1H->setFrameShape(QFrame::StyledPanel);
        frameMasteEdge1H->setFrameShadow(QFrame::Raised);
        frameMasteEdge2H = new QFrame(Horizontal);
        frameMasteEdge2H->setObjectName("frameMasteEdge2H");
        frameMasteEdge2H->setGeometry(QRect(230, 210, 211, 201));
        frameMasteEdge2H->setFrameShape(QFrame::StyledPanel);
        frameMasteEdge2H->setFrameShadow(QFrame::Raised);
        label_12 = new QLabel(Horizontal);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(0, 190, 211, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_13 = new QLabel(Horizontal);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(230, 190, 211, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        stackedWidgetMaster->addWidget(Horizontal);
        Vertical = new QWidget();
        Vertical->setObjectName("Vertical");
        frameMasteEdge2V = new QFrame(Vertical);
        frameMasteEdge2V->setObjectName("frameMasteEdge2V");
        frameMasteEdge2V->setGeometry(QRect(220, 240, 221, 191));
        frameMasteEdge2V->setFrameShape(QFrame::StyledPanel);
        frameMasteEdge2V->setFrameShadow(QFrame::Raised);
        frameMasteEdge1V = new QFrame(Vertical);
        frameMasteEdge1V->setObjectName("frameMasteEdge1V");
        frameMasteEdge1V->setGeometry(QRect(220, 20, 221, 191));
        frameMasteEdge1V->setFrameShape(QFrame::StyledPanel);
        frameMasteEdge1V->setFrameShadow(QFrame::Raised);
        frameMasterWholeV = new QFrame(Vertical);
        frameMasterWholeV->setObjectName("frameMasterWholeV");
        frameMasterWholeV->setGeometry(QRect(0, 0, 211, 431));
        frameMasterWholeV->setFrameShape(QFrame::StyledPanel);
        frameMasterWholeV->setFrameShadow(QFrame::Raised);
        label = new QLabel(Vertical);
        label->setObjectName("label");
        label->setGeometry(QRect(220, 0, 221, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(Vertical);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(220, 220, 221, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        stackedWidgetMaster->addWidget(Vertical);
        stackedWidgetTarget = new QStackedWidget(LargeMeasureWindowForm);
        stackedWidgetTarget->setObjectName("stackedWidgetTarget");
        stackedWidgetTarget->setGeometry(QRect(450, 20, 441, 431));
        Horizontal1 = new QWidget();
        Horizontal1->setObjectName("Horizontal1");
        frameTargetEdge2H = new QFrame(Horizontal1);
        frameTargetEdge2H->setObjectName("frameTargetEdge2H");
        frameTargetEdge2H->setGeometry(QRect(230, 210, 211, 201));
        frameTargetEdge2H->setFrameShape(QFrame::StyledPanel);
        frameTargetEdge2H->setFrameShadow(QFrame::Raised);
        frameTargetEdge1H = new QFrame(Horizontal1);
        frameTargetEdge1H->setObjectName("frameTargetEdge1H");
        frameTargetEdge1H->setGeometry(QRect(0, 210, 211, 201));
        frameTargetEdge1H->setFrameShape(QFrame::StyledPanel);
        frameTargetEdge1H->setFrameShadow(QFrame::Raised);
        frameTargetWholeH = new QFrame(Horizontal1);
        frameTargetWholeH->setObjectName("frameTargetWholeH");
        frameTargetWholeH->setGeometry(QRect(0, 0, 441, 171));
        frameTargetWholeH->setFrameShape(QFrame::StyledPanel);
        frameTargetWholeH->setFrameShadow(QFrame::Raised);
        label_14 = new QLabel(Horizontal1);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(230, 190, 211, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_15 = new QLabel(Horizontal1);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(0, 190, 211, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        stackedWidgetTarget->addWidget(Horizontal1);
        Vertical1 = new QWidget();
        Vertical1->setObjectName("Vertical1");
        frameTargetWholeV = new QFrame(Vertical1);
        frameTargetWholeV->setObjectName("frameTargetWholeV");
        frameTargetWholeV->setGeometry(QRect(0, 0, 211, 431));
        frameTargetWholeV->setFrameShape(QFrame::StyledPanel);
        frameTargetWholeV->setFrameShadow(QFrame::Raised);
        frameTargetEdge1V = new QFrame(Vertical1);
        frameTargetEdge1V->setObjectName("frameTargetEdge1V");
        frameTargetEdge1V->setGeometry(QRect(220, 20, 221, 191));
        frameTargetEdge1V->setFrameShape(QFrame::StyledPanel);
        frameTargetEdge1V->setFrameShadow(QFrame::Raised);
        frameTargetEdge2V = new QFrame(Vertical1);
        frameTargetEdge2V->setObjectName("frameTargetEdge2V");
        frameTargetEdge2V->setGeometry(QRect(220, 240, 221, 191));
        frameTargetEdge2V->setFrameShape(QFrame::StyledPanel);
        frameTargetEdge2V->setFrameShadow(QFrame::Raised);
        label_8 = new QLabel(Vertical1);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(220, 0, 221, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(Vertical1);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(220, 220, 221, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        stackedWidgetTarget->addWidget(Vertical1);
        label_4 = new QLabel(LargeMeasureWindowForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(190, 460, 81, 31));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        doubleSpinBoxResultMM = new QDoubleSpinBox(LargeMeasureWindowForm);
        doubleSpinBoxResultMM->setObjectName("doubleSpinBoxResultMM");
        doubleSpinBoxResultMM->setGeometry(QRect(190, 530, 81, 31));
        QFont font2;
        font2.setPointSize(14);
        doubleSpinBoxResultMM->setFont(font2);
        doubleSpinBoxResultMM->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxResultMM->setReadOnly(true);
        doubleSpinBoxResultMM->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxResultMM->setMaximum(999999999.000000000000000);
        doubleSpinBoxResult = new QDoubleSpinBox(LargeMeasureWindowForm);
        doubleSpinBoxResult->setObjectName("doubleSpinBoxResult");
        doubleSpinBoxResult->setGeometry(QRect(190, 490, 81, 31));
        doubleSpinBoxResult->setFont(font2);
        doubleSpinBoxResult->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxResult->setReadOnly(true);
        doubleSpinBoxResult->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxResult->setMaximum(999999999.000000000000000);
        label_5 = new QLabel(LargeMeasureWindowForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(280, 490, 61, 31));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(LargeMeasureWindowForm);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(280, 530, 61, 31));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxMinDistance = new QDoubleSpinBox(LargeMeasureWindowForm);
        doubleSpinBoxMinDistance->setObjectName("doubleSpinBoxMinDistance");
        doubleSpinBoxMinDistance->setGeometry(QRect(10, 490, 81, 31));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        QBrush brush2(QColor(240, 240, 240, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        doubleSpinBoxMinDistance->setPalette(palette);
        doubleSpinBoxMinDistance->setFont(font2);
        doubleSpinBoxMinDistance->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxMinDistance->setReadOnly(true);
        doubleSpinBoxMinDistance->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxMinDistance->setMaximum(999999999.000000000000000);
        doubleSpinBoxMinDistanceMM = new QDoubleSpinBox(LargeMeasureWindowForm);
        doubleSpinBoxMinDistanceMM->setObjectName("doubleSpinBoxMinDistanceMM");
        doubleSpinBoxMinDistanceMM->setGeometry(QRect(10, 530, 81, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        doubleSpinBoxMinDistanceMM->setPalette(palette1);
        doubleSpinBoxMinDistanceMM->setFont(font2);
        doubleSpinBoxMinDistanceMM->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxMinDistanceMM->setReadOnly(true);
        doubleSpinBoxMinDistanceMM->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxMinDistanceMM->setMaximum(999999999.000000000000000);
        label_9 = new QLabel(LargeMeasureWindowForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 460, 81, 31));
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(LargeMeasureWindowForm);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(100, 460, 81, 31));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);
        doubleSpinBoxMaxDistance = new QDoubleSpinBox(LargeMeasureWindowForm);
        doubleSpinBoxMaxDistance->setObjectName("doubleSpinBoxMaxDistance");
        doubleSpinBoxMaxDistance->setGeometry(QRect(100, 490, 81, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        doubleSpinBoxMaxDistance->setPalette(palette2);
        doubleSpinBoxMaxDistance->setFont(font2);
        doubleSpinBoxMaxDistance->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxMaxDistance->setReadOnly(true);
        doubleSpinBoxMaxDistance->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxMaxDistance->setMaximum(999999999.000000000000000);
        doubleSpinBoxMaxDistanceMM = new QDoubleSpinBox(LargeMeasureWindowForm);
        doubleSpinBoxMaxDistanceMM->setObjectName("doubleSpinBoxMaxDistanceMM");
        doubleSpinBoxMaxDistanceMM->setGeometry(QRect(100, 530, 81, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        doubleSpinBoxMaxDistanceMM->setPalette(palette3);
        doubleSpinBoxMaxDistanceMM->setFont(font2);
        doubleSpinBoxMaxDistanceMM->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxMaxDistanceMM->setReadOnly(true);
        doubleSpinBoxMaxDistanceMM->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxMaxDistanceMM->setMaximum(999999999.000000000000000);

        retranslateUi(LargeMeasureWindowForm);

        PushButtonOKbyDistance->setDefault(false);
        PushButtonExpand2Side->setDefault(false);
        PushButtonExpand1Side->setDefault(false);
        stackedWidgetMaster->setCurrentIndex(0);
        stackedWidgetTarget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LargeMeasureWindowForm);
    } // setupUi

    void retranslateUi(QWidget *LargeMeasureWindowForm)
    {
        LargeMeasureWindowForm->setWindowTitle(QCoreApplication::translate("LargeMeasureWindowForm", "\346\270\254\351\225\267", nullptr));
        label_3->setText(QCoreApplication::translate("LargeMeasureWindowForm", "NG\351\203\250\345\210\206\343\201\256\347\224\273\345\203\217", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("LargeMeasureWindowForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_2->setText(QCoreApplication::translate("LargeMeasureWindowForm", "\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217", nullptr));
        PushButtonOKbyDistance->setText(QCoreApplication::translate("LargeMeasureWindowForm", "\351\225\267\343\201\225\343\201\247OK", nullptr));
        PushButtonExpand2Side->setText(QCoreApplication::translate("LargeMeasureWindowForm", "2\345\201\264\346\216\242\347\264\242\346\213\241\345\244\247", nullptr));
        PushButtonExpand1Side->setText(QCoreApplication::translate("LargeMeasureWindowForm", "1\345\201\264\346\216\242\347\264\242\346\213\241\345\244\247", nullptr));
        label_12->setText(QCoreApplication::translate("LargeMeasureWindowForm", "Point 1", nullptr));
        label_13->setText(QCoreApplication::translate("LargeMeasureWindowForm", "Point 2", nullptr));
        label->setText(QCoreApplication::translate("LargeMeasureWindowForm", "Point 1", nullptr));
        label_7->setText(QCoreApplication::translate("LargeMeasureWindowForm", "Point 2", nullptr));
        label_14->setText(QCoreApplication::translate("LargeMeasureWindowForm", "Point 2", nullptr));
        label_15->setText(QCoreApplication::translate("LargeMeasureWindowForm", "Point 1", nullptr));
        label_8->setText(QCoreApplication::translate("LargeMeasureWindowForm", "Point 1", nullptr));
        label_11->setText(QCoreApplication::translate("LargeMeasureWindowForm", "Point 2", nullptr));
        label_4->setText(QCoreApplication::translate("LargeMeasureWindowForm", "\346\270\254\351\225\267\347\265\220\346\236\234", nullptr));
        label_5->setText(QCoreApplication::translate("LargeMeasureWindowForm", "\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        label_6->setText(QCoreApplication::translate("LargeMeasureWindowForm", "mm", nullptr));
        label_9->setText(QCoreApplication::translate("LargeMeasureWindowForm", "\344\270\213\351\231\220\345\237\272\346\272\226\345\200\244", nullptr));
        label_10->setText(QCoreApplication::translate("LargeMeasureWindowForm", "\344\270\212\351\231\220\345\237\272\346\272\226\345\200\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LargeMeasureWindowForm: public Ui_LargeMeasureWindowForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LARGEMEASUREWINDOWFORM_H
