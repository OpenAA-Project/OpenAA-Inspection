/********************************************************************************
** Form generated from reading UI file 'ThresholdAreaShader.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THRESHOLDAREASHADER_H
#define UI_THRESHOLDAREASHADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThresholdAreaShader
{
public:
    QSpinBox *spinBoxCellSize;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_6;
    QCheckBox *checkBoxFixed;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxSigma;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxAdoptRate;
    QDoubleSpinBox *doubleSpinBoxAverage;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QPushButton *pushButtonChangeLib;
    QPushButton *ButtonClose;
    QStackedWidget *stackedWidgetParts;
    QWidget *page;
    QPushButton *ButtonReflectOnlyBlock;
    QWidget *page_3;
    QPushButton *ButtonReflectSaveParts;
    QWidget *page_2;
    QPushButton *ButtonSaveToLibrary;
    QPushButton *ButtonReflectAllBlocks;
    QPushButton *ButtonLoadFromLibrary;
    QLabel *label_9;

    void setupUi(QWidget *ThresholdAreaShader)
    {
        if (ThresholdAreaShader->objectName().isEmpty())
            ThresholdAreaShader->setObjectName("ThresholdAreaShader");
        ThresholdAreaShader->resize(393, 374);
        spinBoxCellSize = new QSpinBox(ThresholdAreaShader);
        spinBoxCellSize->setObjectName("spinBoxCellSize");
        spinBoxCellSize->setGeometry(QRect(100, 70, 61, 22));
        spinBoxCellSize->setMaximum(999999);
        label_5 = new QLabel(ThresholdAreaShader);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 180, 81, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(ThresholdAreaShader);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(21, 210, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(ThresholdAreaShader);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(140, 140, 191, 31));
        checkBoxFixed = new QCheckBox(ThresholdAreaShader);
        checkBoxFixed->setObjectName("checkBoxFixed");
        checkBoxFixed->setGeometry(QRect(20, 140, 111, 17));
        label_2 = new QLabel(ThresholdAreaShader);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(200, 70, 91, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(ThresholdAreaShader);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(360, 70, 20, 20));
        doubleSpinBoxSigma = new QDoubleSpinBox(ThresholdAreaShader);
        doubleSpinBoxSigma->setObjectName("doubleSpinBoxSigma");
        doubleSpinBoxSigma->setGeometry(QRect(110, 210, 81, 22));
        doubleSpinBoxSigma->setMaximum(1000.000000000000000);
        label = new QLabel(ThresholdAreaShader);
        label->setObjectName("label");
        label->setGeometry(QRect(19, 70, 81, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxAdoptRate = new QDoubleSpinBox(ThresholdAreaShader);
        doubleSpinBoxAdoptRate->setObjectName("doubleSpinBoxAdoptRate");
        doubleSpinBoxAdoptRate->setGeometry(QRect(290, 70, 61, 22));
        doubleSpinBoxAdoptRate->setMaximum(100.000000000000000);
        doubleSpinBoxAverage = new QDoubleSpinBox(ThresholdAreaShader);
        doubleSpinBoxAverage->setObjectName("doubleSpinBoxAverage");
        doubleSpinBoxAverage->setGeometry(QRect(110, 180, 81, 22));
        doubleSpinBoxAverage->setMaximum(256.000000000000000);
        label_7 = new QLabel(ThresholdAreaShader);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 10, 62, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(ThresholdAreaShader);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(70, 10, 271, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(ThresholdAreaShader);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 30, 61, 21));
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(ThresholdAreaShader);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(70, 30, 271, 21));
        EditLibName->setReadOnly(true);
        pushButtonChangeLib = new QPushButton(ThresholdAreaShader);
        pushButtonChangeLib->setObjectName("pushButtonChangeLib");
        pushButtonChangeLib->setGeometry(QRect(340, 30, 31, 23));
        ButtonClose = new QPushButton(ThresholdAreaShader);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(210, 330, 171, 31));
        stackedWidgetParts = new QStackedWidget(ThresholdAreaShader);
        stackedWidgetParts->setObjectName("stackedWidgetParts");
        stackedWidgetParts->setGeometry(QRect(20, 250, 181, 31));
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
        ButtonSaveToLibrary = new QPushButton(ThresholdAreaShader);
        ButtonSaveToLibrary->setObjectName("ButtonSaveToLibrary");
        ButtonSaveToLibrary->setGeometry(QRect(20, 290, 171, 31));
        ButtonReflectAllBlocks = new QPushButton(ThresholdAreaShader);
        ButtonReflectAllBlocks->setObjectName("ButtonReflectAllBlocks");
        ButtonReflectAllBlocks->setGeometry(QRect(210, 250, 171, 31));
        ButtonLoadFromLibrary = new QPushButton(ThresholdAreaShader);
        ButtonLoadFromLibrary->setObjectName("ButtonLoadFromLibrary");
        ButtonLoadFromLibrary->setGeometry(QRect(210, 290, 171, 31));
        label_9 = new QLabel(ThresholdAreaShader);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 90, 271, 31));

        retranslateUi(ThresholdAreaShader);

        stackedWidgetParts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ThresholdAreaShader);
    } // setupUi

    void retranslateUi(QWidget *ThresholdAreaShader)
    {
        ThresholdAreaShader->setWindowTitle(QCoreApplication::translate("ThresholdAreaShader", "Threshold AreaShader", nullptr));
        label_5->setText(QCoreApplication::translate("ThresholdAreaShader", "\345\233\272\345\256\232\345\271\263\345\235\207\345\200\244", nullptr));
        label_4->setText(QCoreApplication::translate("ThresholdAreaShader", "\345\233\272\345\256\232\345\201\217\345\267\256", nullptr));
        label_6->setText(QCoreApplication::translate("ThresholdAreaShader", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\343\203\201\343\202\247\343\203\203\343\202\257\343\201\227\343\201\252\343\201\221\343\202\214\343\201\260\343\203\236\343\202\271\343\202\277\343\203\274\347\224\273\345\203\217\343\201\256\345\271\263\345\235\207\350\274\235\345\272\246\343\200\201</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">\346\250\231\346\272\226\345\201\217\345\267\256\343\201\253\344\270\200\350\207\264\343\201\231\343\202\213\343\202\210\343\201"
                        "\206\343\201\252\345\244\211\346\217\233\343\201\253\343\201\252\343\202\213</p></body></html>", nullptr));
        checkBoxFixed->setText(QCoreApplication::translate("ThresholdAreaShader", "\345\233\272\345\256\232\345\200\244", nullptr));
        label_2->setText(QCoreApplication::translate("ThresholdAreaShader", "\346\216\241\347\224\250\347\216\207", nullptr));
        label_3->setText(QCoreApplication::translate("ThresholdAreaShader", "%", nullptr));
        label->setText(QCoreApplication::translate("ThresholdAreaShader", "\345\207\246\347\220\206\343\202\265\343\202\244\343\202\272", nullptr));
        label_7->setText(QCoreApplication::translate("ThresholdAreaShader", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\357\274\251\357\274\244", nullptr));
        label_8->setText(QCoreApplication::translate("ThresholdAreaShader", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("ThresholdAreaShader", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("ThresholdAreaShader", "XXX", nullptr));
        pushButtonChangeLib->setText(QCoreApplication::translate("ThresholdAreaShader", "...", nullptr));
        ButtonClose->setText(QCoreApplication::translate("ThresholdAreaShader", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonReflectOnlyBlock->setText(QCoreApplication::translate("ThresholdAreaShader", "\343\201\223\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\240\343\201\221\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonReflectSaveParts->setText(QCoreApplication::translate("ThresholdAreaShader", "\351\203\250\345\223\201\344\277\235\345\255\230", nullptr));
        ButtonSaveToLibrary->setText(QCoreApplication::translate("ThresholdAreaShader", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\253\344\277\235\345\255\230", nullptr));
        ButtonReflectAllBlocks->setText(QCoreApplication::translate("ThresholdAreaShader", "\345\220\214\344\270\200\347\250\256\351\241\236\343\201\256\343\203\226\343\203\255\343\203\203\343\202\257\343\201\253\345\217\215\346\230\240", nullptr));
        ButtonLoadFromLibrary->setText(QCoreApplication::translate("ThresholdAreaShader", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\213\343\202\211\350\252\255\343\201\277\345\207\272\343\201\227", nullptr));
        label_9->setText(QCoreApplication::translate("ThresholdAreaShader", "\345\207\246\347\220\206\343\202\265\343\202\244\343\202\272\343\202\222\345\244\211\346\233\264\343\201\231\343\202\214\343\201\260\343\200\201\347\267\250\351\233\206\347\242\272\345\256\232\346\223\215\344\275\234\343\201\214\345\277\205\350\246\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThresholdAreaShader: public Ui_ThresholdAreaShader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THRESHOLDAREASHADER_H
