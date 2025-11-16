/********************************************************************************
** Form generated from reading UI file 'ProjectionMapForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTIONMAPFORM_H
#define UI_PROJECTIONMAPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectionMapForm
{
public:
    QFrame *frameLineGraph;
    QPushButton *pushButtonTransmitItemNameAll;
    QPushButton *pushButtonChangeLib;
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *EditItemName;
    QLabel *label_9;
    QPushButton *ButtonClose;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonReflectAllBlocks;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonRelrectOnlyBlock;
    QWidget *page_3;
    QPushButton *ButtonRelrectSaveParts;
    QWidget *page_2;
    QListWidget *listWidgetHistList;
    QLabel *label_40;
    QFrame *frame;
    QLabel *label_10;
    QLabel *label_38;
    QSpinBox *EditTransitWidth;
    QLabel *label_33;
    QLabel *label_39;
    QLabel *label_34;
    QDoubleSpinBox *doubleSpinBoxAngle;
    QCheckBox *checkBoxUseAbsolute;
    QLabel *label_35;
    QSpinBox *EditEvenLength;
    QDoubleSpinBox *doubleSpinBoxPartialSwingAngle;
    QLabel *label_36;
    QDoubleSpinBox *EditOKWidthDiffereceL;
    QDoubleSpinBox *EditOKWidthDiffereceH;
    QLabel *label_7;
    QLabel *label_8;
    QFrame *frame_2;
    QLabel *label_31;
    QLabel *label;
    QLabel *labelResultMaxDIfference;
    QPushButton *ButtonCalc;

    void setupUi(QWidget *ProjectionMapForm)
    {
        if (ProjectionMapForm->objectName().isEmpty())
            ProjectionMapForm->setObjectName("ProjectionMapForm");
        ProjectionMapForm->resize(1201, 746);
        frameLineGraph = new QFrame(ProjectionMapForm);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(20, 40, 1181, 351));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        pushButtonTransmitItemNameAll = new QPushButton(ProjectionMapForm);
        pushButtonTransmitItemNameAll->setObjectName("pushButtonTransmitItemNameAll");
        pushButtonTransmitItemNameAll->setGeometry(QRect(170, 430, 51, 23));
        pushButtonChangeLib = new QPushButton(ProjectionMapForm);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(190, 480, 31, 23));
        EditLibID = new QLineEdit(ProjectionMapForm);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(30, 480, 61, 21));
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(ProjectionMapForm);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(90, 480, 101, 21));
        EditLibName->setReadOnly(true);
        label_4 = new QLabel(ProjectionMapForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 460, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(ProjectionMapForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(90, 460, 101, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditItemName = new QLineEdit(ProjectionMapForm);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(30, 430, 141, 21));
        EditItemName->setReadOnly(false);
        label_9 = new QLabel(ProjectionMapForm);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 410, 191, 20));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonClose = new QPushButton(ProjectionMapForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(390, 650, 171, 41));
        ButtonSaveToLibrary = new QPushButton(ProjectionMapForm);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(30, 700, 171, 41));
        ButtonSaveToLibrary->setAcceptDrops(true);
        ButtonLoadFromLibrary = new QPushButton(ProjectionMapForm);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(210, 700, 171, 41));
        ButtonLoadFromLibrary->setAcceptDrops(true);
        ButtonReflectAllBlocks = new QPushButton(ProjectionMapForm);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(210, 650, 171, 41));
        ButtonReflectAllBlocks->setAcceptDrops(true);
        stackedWidgetParts = new QStackedWidget(ProjectionMapForm);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(30, 650, 181, 41));
        page = new QWidget();
        page->setObjectName("page");
        ButtonRelrectOnlyBlock = new QPushButton(page);
        ButtonRelrectOnlyBlock->setObjectName("ButtonRelrectOnlyBlock");
        ButtonRelrectOnlyBlock->setGeometry(QRect(0, 0, 171, 41));
        ButtonRelrectOnlyBlock->setAcceptDrops(true);
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
        listWidgetHistList = new QListWidget(ProjectionMapForm);
        listWidgetHistList->setObjectName("listWidgetHistList");
        listWidgetHistList->setGeometry(QRect(580, 430, 181, 91));
        label_40 = new QLabel(ProjectionMapForm);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(580, 410, 181, 21));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setFrameShadow(QFrame::Sunken);
        label_40->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(ProjectionMapForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(260, 410, 301, 231));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(0, 0, 301, 20));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_38 = new QLabel(frame);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(10, 60, 201, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditTransitWidth = new QSpinBox(frame);
        EditTransitWidth->setObjectName("EditTransitWidth");
        EditTransitWidth->setGeometry(QRect(220, 110, 71, 22));
        EditTransitWidth->setMaximum(255);
        label_33 = new QLabel(frame);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, 110, 201, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_39 = new QLabel(frame);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(10, 80, 201, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_34 = new QLabel(frame);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(10, 140, 201, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxAngle = new QDoubleSpinBox(frame);
        doubleSpinBoxAngle->setObjectName("doubleSpinBoxAngle");
        doubleSpinBoxAngle->setGeometry(QRect(221, 140, 71, 22));
        doubleSpinBoxAngle->setMaximum(360.000000000000000);
        checkBoxUseAbsolute = new QCheckBox(frame);
        checkBoxUseAbsolute->setObjectName("checkBoxUseAbsolute");
        checkBoxUseAbsolute->setGeometry(QRect(20, 30, 271, 22));
        label_35 = new QLabel(frame);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(10, 170, 191, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEvenLength = new QSpinBox(frame);
        EditEvenLength->setObjectName("EditEvenLength");
        EditEvenLength->setGeometry(QRect(210, 170, 81, 22));
        EditEvenLength->setMaximum(200000000);
        doubleSpinBoxPartialSwingAngle = new QDoubleSpinBox(frame);
        doubleSpinBoxPartialSwingAngle->setObjectName("doubleSpinBoxPartialSwingAngle");
        doubleSpinBoxPartialSwingAngle->setGeometry(QRect(230, 200, 62, 22));
        doubleSpinBoxPartialSwingAngle->setMaximum(360.000000000000000);
        label_36 = new QLabel(frame);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(10, 200, 211, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditOKWidthDiffereceL = new QDoubleSpinBox(frame);
        EditOKWidthDiffereceL->setObjectName("EditOKWidthDiffereceL");
        EditOKWidthDiffereceL->setGeometry(QRect(221, 60, 71, 22));
        EditOKWidthDiffereceL->setMaximum(360.000000000000000);
        EditOKWidthDiffereceH = new QDoubleSpinBox(frame);
        EditOKWidthDiffereceH->setObjectName("EditOKWidthDiffereceH");
        EditOKWidthDiffereceH->setGeometry(QRect(220, 80, 71, 22));
        EditOKWidthDiffereceH->setMaximum(360.000000000000000);
        label_7 = new QLabel(ProjectionMapForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(30, 10, 131, 21));
        label_8 = new QLabel(ProjectionMapForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(190, 10, 131, 21));
        frame_2 = new QFrame(ProjectionMapForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(840, 410, 241, 131));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_31 = new QLabel(frame_2);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(0, 0, 241, 21));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 131, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelResultMaxDIfference = new QLabel(frame_2);
        labelResultMaxDIfference->setObjectName("labelResultMaxDIfference");
        labelResultMaxDIfference->setGeometry(QRect(150, 40, 81, 21));
        labelResultMaxDIfference->setFrameShape(QFrame::Panel);
        labelResultMaxDIfference->setFrameShadow(QFrame::Sunken);
        labelResultMaxDIfference->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonCalc = new QPushButton(frame_2);
        ButtonCalc->setObjectName("ButtonCalc");
        ButtonCalc->setGeometry(QRect(40, 80, 161, 31));
        ButtonCalc->setAcceptDrops(true);

        retranslateUi(ProjectionMapForm);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ProjectionMapForm);
    } // setupUi

    void retranslateUi(QWidget *ProjectionMapForm)
    {
        ProjectionMapForm->setWindowTitle(QCoreApplication::translate("ProjectionMapForm", "Threshold Projection", nullptr));
        pushButtonTransmitItemNameAll->setText(QCoreApplication::translate("ProjectionMapForm", "To all", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("ProjectionMapForm", "...", nullptr));
        EditLibID->setText(QCoreApplication::translate("ProjectionMapForm", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("ProjectionMapForm", "XXX", nullptr));
        label_4->setText(QCoreApplication::translate("ProjectionMapForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        label_5->setText(QCoreApplication::translate("ProjectionMapForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        EditItemName->setText(QCoreApplication::translate("ProjectionMapForm", "XXX", nullptr));
        label_9->setText(QCoreApplication::translate("ProjectionMapForm", "Item name", nullptr));
        ButtonClose->setText(QCoreApplication::translate("ProjectionMapForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("ProjectionMapForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("ProjectionMapForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("ProjectionMapForm", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("ProjectionMapForm", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("ProjectionMapForm", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        label_40->setText(QCoreApplication::translate("ProjectionMapForm", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\343\203\220\343\203\251\343\201\244\343\201\215\343\202\260\343\203\251\343\203\225", nullptr));
        label_10->setText(QCoreApplication::translate("ProjectionMapForm", "Threshold", nullptr));
        label_38->setText(QCoreApplication::translate("ProjectionMapForm", "Brightness difference Dark", nullptr));
        label_33->setText(QCoreApplication::translate("ProjectionMapForm", "Transit wdth", nullptr));
        label_39->setText(QCoreApplication::translate("ProjectionMapForm", "Brightness difference Light", nullptr));
        label_34->setText(QCoreApplication::translate("ProjectionMapForm", "Angle degree", nullptr));
        checkBoxUseAbsolute->setText(QCoreApplication::translate("ProjectionMapForm", "Absolute brightness", nullptr));
        label_35->setText(QCoreApplication::translate("ProjectionMapForm", "Even Length", nullptr));
        label_36->setText(QCoreApplication::translate("ProjectionMapForm", "Swing angle range", nullptr));
        label_7->setText(QCoreApplication::translate("ProjectionMapForm", "\346\244\234\346\237\273\347\224\273\345\203\217", nullptr));
        label_8->setText(QCoreApplication::translate("ProjectionMapForm", "\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_31->setText(QCoreApplication::translate("ProjectionMapForm", "\345\275\223\350\251\262\347\256\207\346\211\200\343\201\256\345\210\244\345\256\232\347\265\220\346\236\234", nullptr));
        label->setText(QCoreApplication::translate("ProjectionMapForm", "\350\274\235\345\272\246\345\267\256\343\201\256\346\234\200\345\244\247", nullptr));
        labelResultMaxDIfference->setText(QCoreApplication::translate("ProjectionMapForm", "123", nullptr));
        ButtonCalc->setText(QCoreApplication::translate("ProjectionMapForm", "\350\250\210\347\256\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectionMapForm: public Ui_ProjectionMapForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTIONMAPFORM_H
