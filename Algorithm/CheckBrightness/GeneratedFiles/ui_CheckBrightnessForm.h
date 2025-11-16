/********************************************************************************
** Form generated from reading UI file 'CheckBrightnessForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKBRIGHTNESSFORM_H
#define UI_CHECKBRIGHTNESSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckBrightnessForm
{
public:
    QSpinBox *spinBoxThreshL;
    QLabel *label_2;
    QSpinBox *spinBoxRegNumber;
    QComboBox *comboBoxCondition;
    QSpinBox *spinBoxRepeatableCount;
    QLabel *label_3;
    QLabel *label_5;
    QSpinBox *spinBoxThreshH;
    QLabel *label_4;
    QLineEdit *lineEditItemName;
    QLabel *label;
    QPushButton *ButtonClose;
    QPushButton *ButtonReflectAllBlocks;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonRelrectOnlyBlock;
    QWidget *page_3;
    QPushButton *ButtonRelrectSaveParts;
    QWidget *page_2;
    QFrame *frame;
    QPushButton *pushButtonSetThresholdAll;
    QSpinBox *spinBoxWidthH;
    QPushButton *pushButtonSetThresholdOne;
    QLabel *label_6;
    QLabel *label_7;
    QSpinBox *spinBoxWidthL;
    QLabel *label_8;

    void setupUi(QWidget *CheckBrightnessForm)
    {
        if (CheckBrightnessForm->objectName().isEmpty())
            CheckBrightnessForm->setObjectName("CheckBrightnessForm");
        CheckBrightnessForm->resize(378, 415);
        spinBoxThreshL = new QSpinBox(CheckBrightnessForm);
        spinBoxThreshL->setObjectName("spinBoxThreshL");
        spinBoxThreshL->setGeometry(QRect(10, 80, 46, 22));
        spinBoxThreshL->setMaximum(255);
        spinBoxThreshL->setValue(255);
        label_2 = new QLabel(CheckBrightnessForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 60, 46, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        spinBoxRegNumber = new QSpinBox(CheckBrightnessForm);
        spinBoxRegNumber->setObjectName("spinBoxRegNumber");
        spinBoxRegNumber->setGeometry(QRect(10, 130, 46, 22));
        spinBoxRegNumber->setMinimum(400);
        spinBoxRegNumber->setMaximum(499);
        spinBoxRegNumber->setValue(400);
        comboBoxCondition = new QComboBox(CheckBrightnessForm);
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->addItem(QString());
        comboBoxCondition->setObjectName("comboBoxCondition");
        comboBoxCondition->setGeometry(QRect(120, 70, 161, 22));
        spinBoxRepeatableCount = new QSpinBox(CheckBrightnessForm);
        spinBoxRepeatableCount->setObjectName("spinBoxRepeatableCount");
        spinBoxRepeatableCount->setGeometry(QRect(60, 130, 81, 22));
        spinBoxRepeatableCount->setMinimum(0);
        spinBoxRepeatableCount->setMaximum(1000000);
        spinBoxRepeatableCount->setValue(1);
        label_3 = new QLabel(CheckBrightnessForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 46, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(CheckBrightnessForm);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 271, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxThreshH = new QSpinBox(CheckBrightnessForm);
        spinBoxThreshH->setObjectName("spinBoxThreshH");
        spinBoxThreshH->setGeometry(QRect(60, 80, 46, 22));
        spinBoxThreshH->setMaximum(255);
        spinBoxThreshH->setValue(255);
        label_4 = new QLabel(CheckBrightnessForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(60, 110, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        lineEditItemName = new QLineEdit(CheckBrightnessForm);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(10, 30, 271, 20));
        label = new QLabel(CheckBrightnessForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 60, 46, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        ButtonClose = new QPushButton(CheckBrightnessForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(100, 360, 171, 41));
        ButtonReflectAllBlocks = new QPushButton(CheckBrightnessForm);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(190, 170, 171, 41));
        ButtonReflectAllBlocks->setAcceptDrops(true);
        stackedWidgetParts = new QStackedWidget(CheckBrightnessForm);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(10, 170, 181, 41));
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
        frame = new QFrame(CheckBrightnessForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 240, 321, 101));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        pushButtonSetThresholdAll = new QPushButton(frame);
        pushButtonSetThresholdAll->setObjectName("pushButtonSetThresholdAll");
        pushButtonSetThresholdAll->setGeometry(QRect(140, 60, 171, 28));
        spinBoxWidthH = new QSpinBox(frame);
        spinBoxWidthH->setObjectName("spinBoxWidthH");
        spinBoxWidthH->setGeometry(QRect(70, 50, 51, 22));
        spinBoxWidthH->setMaximum(255);
        spinBoxWidthH->setValue(255);
        pushButtonSetThresholdOne = new QPushButton(frame);
        pushButtonSetThresholdOne->setObjectName("pushButtonSetThresholdOne");
        pushButtonSetThresholdOne->setGeometry(QRect(140, 30, 171, 28));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(70, 30, 51, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(15, 30, 51, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        spinBoxWidthL = new QSpinBox(frame);
        spinBoxWidthL->setObjectName("spinBoxWidthL");
        spinBoxWidthL->setGeometry(QRect(15, 50, 51, 22));
        spinBoxWidthL->setMaximum(255);
        spinBoxWidthL->setValue(255);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 321, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);

        retranslateUi(CheckBrightnessForm);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CheckBrightnessForm);
    } // setupUi

    void retranslateUi(QWidget *CheckBrightnessForm)
    {
        CheckBrightnessForm->setWindowTitle(QCoreApplication::translate("CheckBrightnessForm", "Threshold CheckBrightness", nullptr));
        label_2->setText(QCoreApplication::translate("CheckBrightnessForm", "H", nullptr));
        comboBoxCondition->setItemText(0, QCoreApplication::translate("CheckBrightnessForm", "Average must be inside", nullptr));
        comboBoxCondition->setItemText(1, QCoreApplication::translate("CheckBrightnessForm", "All must be inside", nullptr));
        comboBoxCondition->setItemText(2, QCoreApplication::translate("CheckBrightnessForm", "One must be inside at least", nullptr));
        comboBoxCondition->setItemText(3, QCoreApplication::translate("CheckBrightnessForm", "Average must be outside", nullptr));
        comboBoxCondition->setItemText(4, QCoreApplication::translate("CheckBrightnessForm", "All must be outside", nullptr));
        comboBoxCondition->setItemText(5, QCoreApplication::translate("CheckBrightnessForm", "One must be outside at least", nullptr));

        label_3->setText(QCoreApplication::translate("CheckBrightnessForm", "Reg No", nullptr));
        label_5->setText(QCoreApplication::translate("CheckBrightnessForm", "Item name", nullptr));
        label_4->setText(QCoreApplication::translate("CheckBrightnessForm", "Repeatable NG", nullptr));
        label->setText(QCoreApplication::translate("CheckBrightnessForm", "L", nullptr));
        ButtonClose->setText(QCoreApplication::translate("CheckBrightnessForm", "Close", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("CheckBrightnessForm", "Reflect all items", nullptr));
        ButtonRelrectOnlyBlock->setText(QCoreApplication::translate("CheckBrightnessForm", "Reflect only this", nullptr));
        ButtonRelrectSaveParts->setText(QCoreApplication::translate("CheckBrightnessForm", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        pushButtonSetThresholdAll->setText(QCoreApplication::translate("CheckBrightnessForm", "Set threshold for all", nullptr));
        pushButtonSetThresholdOne->setText(QCoreApplication::translate("CheckBrightnessForm", "Set threshold in this", nullptr));
        label_6->setText(QCoreApplication::translate("CheckBrightnessForm", "H width", nullptr));
        label_7->setText(QCoreApplication::translate("CheckBrightnessForm", "L width", nullptr));
        label_8->setText(QCoreApplication::translate("CheckBrightnessForm", "Set threshold with master image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckBrightnessForm: public Ui_CheckBrightnessForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKBRIGHTNESSFORM_H
