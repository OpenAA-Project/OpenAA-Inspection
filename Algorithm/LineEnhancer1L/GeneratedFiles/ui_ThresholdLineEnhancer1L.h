/********************************************************************************
** Form generated from reading UI file 'ThresholdLineEnhancer1L.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THRESHOLDLINEENHANCER1L_H
#define UI_THRESHOLDLINEENHANCER1L_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThresholdLineEnhancer1L
{
public:
    QPushButton *ButtonReflectAllBlocks;
    QPushButton *ButtonClose;
    QLabel *label_4;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonReflectOnlyBlock;
    QWidget *page_3;
    QPushButton *ButtonReflectSaveParts;
    QWidget *page_2;
    QPushButton *pushButtonChangeLib;
    QFrame *frame_2;
    QSpinBox *EditSelfSearch;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBoxEmphasizeRate;
    QLabel *label_33;
    QSpinBox *EditMaxLineWidth;
    QLabel *label_38;
    QLabel *label_34;
    QLabel *label_35;
    QCheckBox *checkBoxExcludeDynamicMask;
    QCheckBox *checkBoxFixedAngle;
    QDoubleSpinBox *EditStartAngle;
    QDoubleSpinBox *EditEndAngle;
    QLineEdit *EditLibName;
    QLabel *label_5;
    QPushButton *ButtonLoadFromLibrary;
    QPushButton *ButtonSaveToLibrary;
    QLineEdit *EditLibID;

    void setupUi(QWidget *ThresholdLineEnhancer1L)
    {
        if (ThresholdLineEnhancer1L->objectName().isEmpty())
            ThresholdLineEnhancer1L->setObjectName("ThresholdLineEnhancer1L");
        ThresholdLineEnhancer1L->resize(566, 390);
        ButtonReflectAllBlocks = new QPushButton(ThresholdLineEnhancer1L);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(300, 270, 231, 31));
        ButtonClose = new QPushButton(ThresholdLineEnhancer1L);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(360, 350, 171, 31));
        label_4 = new QLabel(ThresholdLineEnhancer1L);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 62, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidgetParts = new QStackedWidget(ThresholdLineEnhancer1L);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(40, 270, 251, 31));
        page = new QWidget();
        page->setObjectName("page");
        ButtonReflectOnlyBlock = new QPushButton(page);
        ButtonReflectOnlyBlock->setObjectName("ButtonReflectOnlyBlock");
        ButtonReflectOnlyBlock->setGeometry(QRect(0, 0, 221, 31));
        stackedWidgetParts->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        ButtonReflectSaveParts = new QPushButton(page_3);
        ButtonReflectSaveParts->setObjectName("ButtonReflectSaveParts");
        ButtonReflectSaveParts->setGeometry(QRect(0, 0, 221, 31));
        stackedWidgetParts->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetParts->addWidget(page_2);
        pushButtonChangeLib = new QPushButton(ThresholdLineEnhancer1L);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(510, 30, 31, 23));
        frame_2 = new QFrame(ThresholdLineEnhancer1L);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 60, 541, 201));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        EditSelfSearch = new QSpinBox(frame_2);
        EditSelfSearch->setObjectName("EditSelfSearch");
        EditSelfSearch->setGeometry(QRect(370, 40, 61, 22));
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
        label_38->setGeometry(QRect(260, 40, 111, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_34 = new QLabel(frame_2);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(10, 110, 431, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35 = new QLabel(frame_2);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(10, 130, 431, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxExcludeDynamicMask = new QCheckBox(frame_2);
        checkBoxExcludeDynamicMask->setObjectName("checkBoxExcludeDynamicMask");
        checkBoxExcludeDynamicMask->setGeometry(QRect(10, 170, 521, 17));
        checkBoxFixedAngle = new QCheckBox(frame_2);
        checkBoxFixedAngle->setObjectName("checkBoxFixedAngle");
        checkBoxFixedAngle->setGeometry(QRect(10, 90, 261, 17));
        EditStartAngle = new QDoubleSpinBox(frame_2);
        EditStartAngle->setObjectName("EditStartAngle");
        EditStartAngle->setGeometry(QRect(450, 110, 81, 22));
        EditStartAngle->setMinimum(-360.000000000000000);
        EditStartAngle->setMaximum(360.000000000000000);
        EditEndAngle = new QDoubleSpinBox(frame_2);
        EditEndAngle->setObjectName("EditEndAngle");
        EditEndAngle->setGeometry(QRect(450, 130, 81, 22));
        EditEndAngle->setMinimum(-360.000000000000000);
        EditEndAngle->setMaximum(360.000000000000000);
        EditLibName = new QLineEdit(ThresholdLineEnhancer1L);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(70, 30, 441, 21));
        EditLibName->setReadOnly(true);
        label_5 = new QLabel(ThresholdLineEnhancer1L);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 10, 441, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonLoadFromLibrary = new QPushButton(ThresholdLineEnhancer1L);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(300, 310, 231, 31));
        ButtonSaveToLibrary = new QPushButton(ThresholdLineEnhancer1L);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(40, 310, 221, 31));
        EditLibID = new QLineEdit(ThresholdLineEnhancer1L);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 30, 61, 21));
        EditLibID->setReadOnly(true);

        retranslateUi(ThresholdLineEnhancer1L);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ThresholdLineEnhancer1L);
    } // setupUi

    void retranslateUi(QWidget *ThresholdLineEnhancer1L)
    {
        ThresholdLineEnhancer1L->setWindowTitle(QCoreApplication::translate("ThresholdLineEnhancer1L", "LineEnhancer Threshold", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonClose->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_4->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        ButtonReflectOnlyBlock->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonReflectSaveParts->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "...", nullptr));
        label_30->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\345\274\267\350\252\277\344\277\202\346\225\260", nullptr));
        label_33->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\347\267\232\345\271\205", nullptr));
        label_38->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\346\216\242\347\264\242\350\267\235\351\233\242", nullptr));
        label_34->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\345\217\263\346\226\271\345\220\221\343\202\222\357\274\220\345\272\246\343\201\250\343\201\227\343\201\237\345\217\215\346\231\202\350\250\210\345\233\236\343\202\212\343\201\247\343\200\201\350\250\210\347\256\227\351\226\213\345\247\213\350\247\222\345\272\246", nullptr));
        label_35->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\345\217\263\346\226\271\345\220\221\343\202\222\357\274\220\345\272\246\343\201\250\343\201\227\343\201\237\345\217\215\346\231\202\350\250\210\345\233\236\343\202\212\343\201\247\343\200\201\350\250\210\347\256\227\347\265\202\344\272\206\350\247\222\345\272\246", nullptr));
        checkBoxExcludeDynamicMask->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\345\213\225\347\232\204\343\203\236\343\202\271\343\202\257\351\240\230\345\237\237\343\202\222\346\216\222\351\231\244", nullptr));
        checkBoxFixedAngle->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\345\233\272\345\256\232\350\247\222", nullptr));
        EditLibName->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "XXX", nullptr));
        label_5->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        EditLibID->setText(QCoreApplication::translate("ThresholdLineEnhancer1L", "12345", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThresholdLineEnhancer1L: public Ui_ThresholdLineEnhancer1L {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THRESHOLDLINEENHANCER1L_H
