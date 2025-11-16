/********************************************************************************
** Form generated from reading UI file 'ThresholdLineEnhancer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THRESHOLDLINEENHANCER_H
#define UI_THRESHOLDLINEENHANCER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThresholdLineEnhancerClass
{
public:
    QFrame *frame_2;
    QSpinBox *EditSelfSearch;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBoxEmphasizeRate;
    QLabel *label_33;
    QSpinBox *EditMaxLineWidth;
    QLabel *label_38;
    QPushButton *ButtonReflectAllBlocks;
    QPushButton *ButtonClose;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *ButtonLoadFromLibrary;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonReflectOnlyBlock;
    QWidget *page_3;
    QPushButton *ButtonReflectSaveParts;
    QWidget *page_2;
    QPushButton *pushButtonChangeLib;
    QLineEdit *EditLibID;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *EditLibName;

    void setupUi(QWidget *ThresholdLineEnhancerClass)
    {
        if (ThresholdLineEnhancerClass->objectName().isEmpty())
            ThresholdLineEnhancerClass->setObjectName("ThresholdLineEnhancerClass");
        ThresholdLineEnhancerClass->resize(402, 265);
        frame_2 = new QFrame(ThresholdLineEnhancerClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 60, 381, 71));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        EditSelfSearch = new QSpinBox(frame_2);
        EditSelfSearch->setObjectName("EditSelfSearch");
        EditSelfSearch->setGeometry(QRect(320, 40, 51, 22));
        EditSelfSearch->setMaximum(255);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 10, 121, 21));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxEmphasizeRate = new QDoubleSpinBox(frame_2);
        doubleSpinBoxEmphasizeRate->setObjectName("doubleSpinBoxEmphasizeRate");
        doubleSpinBoxEmphasizeRate->setGeometry(QRect(130, 10, 62, 22));
        doubleSpinBoxEmphasizeRate->setDecimals(4);
        doubleSpinBoxEmphasizeRate->setMinimum(-99.989999999999995);
        label_33 = new QLabel(frame_2);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, 40, 121, 21));
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxLineWidth = new QSpinBox(frame_2);
        EditMaxLineWidth->setObjectName("EditMaxLineWidth");
        EditMaxLineWidth->setGeometry(QRect(130, 40, 61, 22));
        EditMaxLineWidth->setMaximum(255);
        label_38 = new QLabel(frame_2);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(210, 40, 111, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonReflectAllBlocks = new QPushButton(ThresholdLineEnhancerClass);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(220, 140, 171, 31));
        ButtonClose = new QPushButton(ThresholdLineEnhancerClass);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(220, 220, 171, 31));
        ButtonSaveToLibrary = new QPushButton(ThresholdLineEnhancerClass);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(10, 180, 171, 31));
        ButtonLoadFromLibrary = new QPushButton(ThresholdLineEnhancerClass);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(220, 180, 171, 31));
        stackedWidgetParts = new QStackedWidget(ThresholdLineEnhancerClass);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(10, 140, 181, 31));
        page = new QWidget();
        page->setObjectName("page");
        ButtonReflectOnlyBlock = new QPushButton(page);
        ButtonReflectOnlyBlock->setObjectName("ButtonReflectOnlyBlock");
        ButtonReflectOnlyBlock->setGeometry(QRect(0, 0, 171, 31));
        stackedWidgetParts->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        ButtonReflectSaveParts = new QPushButton(page_3);
        ButtonReflectSaveParts->setObjectName("ButtonReflectSaveParts");
        ButtonReflectSaveParts->setGeometry(QRect(0, 0, 171, 31));
        stackedWidgetParts->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetParts->addWidget(page_2);
        pushButtonChangeLib = new QPushButton(ThresholdLineEnhancerClass);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(170, 30, 31, 23));
        EditLibID = new QLineEdit(ThresholdLineEnhancerClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 30, 61, 21));
        EditLibID->setReadOnly(true);
        label_4 = new QLabel(ThresholdLineEnhancerClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(ThresholdLineEnhancerClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 10, 101, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(ThresholdLineEnhancerClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(70, 30, 101, 21));
        EditLibName->setReadOnly(true);

        retranslateUi(ThresholdLineEnhancerClass);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ThresholdLineEnhancerClass);
    } // setupUi

    void retranslateUi(QWidget *ThresholdLineEnhancerClass)
    {
        ThresholdLineEnhancerClass->setWindowTitle(QCoreApplication::translate("ThresholdLineEnhancerClass", "ThresholdLineEnhancer", nullptr));
        label_30->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\345\274\267\350\252\277\344\277\202\346\225\260", nullptr));
        label_33->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\347\267\232\345\271\205", nullptr));
        label_38->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\346\216\242\347\264\242\350\267\235\351\233\242", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonClose->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonReflectOnlyBlock->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonReflectSaveParts->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "...", nullptr));
        EditLibID->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "12345", nullptr));
        label_4->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        label_5->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        EditLibName->setText(QCoreApplication::translate("ThresholdLineEnhancerClass", "XXX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThresholdLineEnhancerClass: public Ui_ThresholdLineEnhancerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THRESHOLDLINEENHANCER_H
