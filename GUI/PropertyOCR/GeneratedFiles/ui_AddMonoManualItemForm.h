/********************************************************************************
** Form generated from reading UI file 'AddMonoManualItemForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDMONOMANUALITEMFORM_H
#define UI_ADDMONOMANUALITEMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddMonoManualItemFormClass
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_8;
    QSpinBox *spinBoxEnsmall;
    QSpinBox *spinBoxDark;
    QLabel *label_5;
    QPushButton *pushButtonCancel;
    QLabel *label_3;
    QPushButton *pushButtonOK;
    QLabel *label_4;
    QLabel *label_2;
    QSpinBox *spinBoxLight;
    QSpinBox *spinBoxBlockHeight;
    QSpinBox *spinBoxBlockWidth;
    QSpinBox *spinBoxEnlarge;
    QLabel *label_7;
    QLabel *label_15;
    QSpinBox *spinBoxMinSize;
    QLabel *label_6;
    QSpinBox *spinBoxDarkG;
    QSpinBox *spinBoxLightG;
    QLabel *label_17;
    QSpinBox *spinBoxDarkB;
    QSpinBox *spinBoxLightB;
    QLabel *label_18;
    QWidget *page_2;
    QPushButton *pushButtonCancelDrawMask;
    QPushButton *pushButtonOKDrawMask;
    QWidget *page_3;
    QLabel *label_10;
    QLabel *label_11;
    QSpinBox *spinBoxLight_2;
    QSpinBox *spinBoxDark_2;
    QSpinBox *spinBoxEnlarge_2;
    QSpinBox *spinBoxEnsmall_2;
    QLabel *label_12;
    QLabel *label_13;
    QPushButton *pushButtonOK_2;
    QPushButton *pushButtonCancel_2;
    QSpinBox *spinBoxBlockHeight_2;
    QSpinBox *spinBoxBlockWidth_2;
    QSpinBox *spinBoxMinSize_2;
    QLabel *label_9;
    QLabel *label_14;
    QLabel *label_16;

    void setupUi(QDialog *AddMonoManualItemFormClass)
    {
        if (AddMonoManualItemFormClass->objectName().isEmpty())
            AddMonoManualItemFormClass->setObjectName("AddMonoManualItemFormClass");
        AddMonoManualItemFormClass->resize(278, 341);
        stackedWidget = new QStackedWidget(AddMonoManualItemFormClass);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 261, 321));
        page = new QWidget();
        page->setObjectName("page");
        label_8 = new QLabel(page);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 190, 191, 20));
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxEnsmall = new QSpinBox(page);
        spinBoxEnsmall->setObjectName("spinBoxEnsmall");
        spinBoxEnsmall->setGeometry(QRect(190, 100, 61, 22));
        spinBoxDark = new QSpinBox(page);
        spinBoxDark->setObjectName("spinBoxDark");
        spinBoxDark->setGeometry(QRect(70, 20, 81, 22));
        spinBoxDark->setMaximum(255);
        label_5 = new QLabel(page);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(170, 0, 81, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(page);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 270, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonCancel->setAutoDefault(false);
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 130, 151, 16));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(page);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 270, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 0, 81, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 100, 151, 16));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxLight = new QSpinBox(page);
        spinBoxLight->setObjectName("spinBoxLight");
        spinBoxLight->setGeometry(QRect(170, 21, 81, 21));
        spinBoxLight->setMaximum(255);
        spinBoxBlockHeight = new QSpinBox(page);
        spinBoxBlockHeight->setObjectName("spinBoxBlockHeight");
        spinBoxBlockHeight->setGeometry(QRect(190, 190, 61, 22));
        spinBoxBlockHeight->setMinimum(1);
        spinBoxBlockHeight->setMaximum(300);
        spinBoxBlockHeight->setValue(1);
        spinBoxBlockWidth = new QSpinBox(page);
        spinBoxBlockWidth->setObjectName("spinBoxBlockWidth");
        spinBoxBlockWidth->setGeometry(QRect(190, 160, 61, 22));
        spinBoxBlockWidth->setMinimum(1);
        spinBoxBlockWidth->setMaximum(300);
        spinBoxBlockWidth->setValue(1);
        spinBoxEnlarge = new QSpinBox(page);
        spinBoxEnlarge->setObjectName("spinBoxEnlarge");
        spinBoxEnlarge->setGeometry(QRect(190, 130, 61, 22));
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 160, 191, 20));
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_15 = new QLabel(page);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(20, 230, 141, 20));
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxMinSize = new QSpinBox(page);
        spinBoxMinSize->setObjectName("spinBoxMinSize");
        spinBoxMinSize->setGeometry(QRect(170, 230, 81, 22));
        spinBoxMinSize->setMinimum(0);
        spinBoxMinSize->setMaximum(99999999);
        spinBoxMinSize->setValue(1);
        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 20, 61, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxDarkG = new QSpinBox(page);
        spinBoxDarkG->setObjectName("spinBoxDarkG");
        spinBoxDarkG->setGeometry(QRect(70, 40, 81, 22));
        spinBoxDarkG->setMaximum(255);
        spinBoxLightG = new QSpinBox(page);
        spinBoxLightG->setObjectName("spinBoxLightG");
        spinBoxLightG->setGeometry(QRect(170, 41, 81, 21));
        spinBoxLightG->setMaximum(255);
        label_17 = new QLabel(page);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(0, 40, 61, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxDarkB = new QSpinBox(page);
        spinBoxDarkB->setObjectName("spinBoxDarkB");
        spinBoxDarkB->setGeometry(QRect(70, 60, 81, 22));
        spinBoxDarkB->setMaximum(255);
        spinBoxLightB = new QSpinBox(page);
        spinBoxLightB->setObjectName("spinBoxLightB");
        spinBoxLightB->setGeometry(QRect(170, 61, 81, 21));
        spinBoxLightB->setMaximum(255);
        label_18 = new QLabel(page);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(0, 60, 61, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        pushButtonCancelDrawMask = new QPushButton(page_2);
        pushButtonCancelDrawMask->setObjectName("pushButtonCancelDrawMask");
        pushButtonCancelDrawMask->setGeometry(QRect(130, 180, 111, 41));
        pushButtonCancelDrawMask->setIcon(icon);
        pushButtonCancelDrawMask->setAutoDefault(false);
        pushButtonOKDrawMask = new QPushButton(page_2);
        pushButtonOKDrawMask->setObjectName("pushButtonOKDrawMask");
        pushButtonOKDrawMask->setGeometry(QRect(0, 180, 111, 41));
        pushButtonOKDrawMask->setIcon(icon1);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_10 = new QLabel(page_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(30, 20, 91, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11 = new QLabel(page_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(140, 20, 91, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxLight_2 = new QSpinBox(page_3);
        spinBoxLight_2->setObjectName("spinBoxLight_2");
        spinBoxLight_2->setGeometry(QRect(140, 40, 91, 22));
        spinBoxLight_2->setMaximum(255);
        spinBoxDark_2 = new QSpinBox(page_3);
        spinBoxDark_2->setObjectName("spinBoxDark_2");
        spinBoxDark_2->setGeometry(QRect(30, 40, 91, 22));
        spinBoxDark_2->setMaximum(255);
        spinBoxEnlarge_2 = new QSpinBox(page_3);
        spinBoxEnlarge_2->setObjectName("spinBoxEnlarge_2");
        spinBoxEnlarge_2->setGeometry(QRect(190, 110, 61, 22));
        spinBoxEnsmall_2 = new QSpinBox(page_3);
        spinBoxEnsmall_2->setObjectName("spinBoxEnsmall_2");
        spinBoxEnsmall_2->setGeometry(QRect(190, 80, 61, 22));
        label_12 = new QLabel(page_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 80, 171, 20));
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(page_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 110, 171, 20));
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK_2 = new QPushButton(page_3);
        pushButtonOK_2->setObjectName("pushButtonOK_2");
        pushButtonOK_2->setGeometry(QRect(10, 260, 121, 41));
        pushButtonOK_2->setIcon(icon1);
        pushButtonCancel_2 = new QPushButton(page_3);
        pushButtonCancel_2->setObjectName("pushButtonCancel_2");
        pushButtonCancel_2->setGeometry(QRect(140, 260, 111, 41));
        pushButtonCancel_2->setIcon(icon);
        pushButtonCancel_2->setAutoDefault(false);
        spinBoxBlockHeight_2 = new QSpinBox(page_3);
        spinBoxBlockHeight_2->setObjectName("spinBoxBlockHeight_2");
        spinBoxBlockHeight_2->setGeometry(QRect(190, 170, 61, 22));
        spinBoxBlockHeight_2->setMinimum(1);
        spinBoxBlockHeight_2->setMaximum(300);
        spinBoxBlockHeight_2->setValue(1);
        spinBoxBlockWidth_2 = new QSpinBox(page_3);
        spinBoxBlockWidth_2->setObjectName("spinBoxBlockWidth_2");
        spinBoxBlockWidth_2->setGeometry(QRect(190, 140, 61, 22));
        spinBoxBlockWidth_2->setMinimum(1);
        spinBoxBlockWidth_2->setMaximum(300);
        spinBoxBlockWidth_2->setValue(1);
        spinBoxMinSize_2 = new QSpinBox(page_3);
        spinBoxMinSize_2->setObjectName("spinBoxMinSize_2");
        spinBoxMinSize_2->setGeometry(QRect(170, 210, 81, 22));
        spinBoxMinSize_2->setMinimum(0);
        spinBoxMinSize_2->setMaximum(99999999);
        spinBoxMinSize_2->setValue(1);
        label_9 = new QLabel(page_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(0, 140, 191, 20));
        label_9->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_14 = new QLabel(page_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(0, 170, 191, 20));
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_16 = new QLabel(page_3);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(20, 210, 141, 20));
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget->addWidget(page_3);
        QWidget::setTabOrder(spinBoxDark, spinBoxLight);
        QWidget::setTabOrder(spinBoxLight, spinBoxEnsmall);
        QWidget::setTabOrder(spinBoxEnsmall, spinBoxEnlarge);
        QWidget::setTabOrder(spinBoxEnlarge, spinBoxBlockWidth);
        QWidget::setTabOrder(spinBoxBlockWidth, spinBoxBlockHeight);
        QWidget::setTabOrder(spinBoxBlockHeight, pushButtonOK);
        QWidget::setTabOrder(pushButtonOK, pushButtonCancel);

        retranslateUi(AddMonoManualItemFormClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AddMonoManualItemFormClass);
    } // setupUi

    void retranslateUi(QDialog *AddMonoManualItemFormClass)
    {
        AddMonoManualItemFormClass->setWindowTitle(QCoreApplication::translate("AddMonoManualItemFormClass", "AddMonoManualItemForm", nullptr));
        label_8->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\234\200\345\260\217\343\201\256\347\270\246\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        label_5->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\230\216\345\201\264\350\274\235\345\272\246", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label_3->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\350\250\255\345\256\232", nullptr));
        label_4->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\232\227\345\201\264\350\274\235\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_7->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\234\200\345\260\217\343\201\256\346\250\252\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        label_15->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\234\200\345\260\217\343\203\224\343\202\257\343\202\273\343\203\253\346\225\260", nullptr));
        label_6->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "LY0", nullptr));
        label_17->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "LY1", nullptr));
        label_18->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "LY2", nullptr));
        pushButtonCancelDrawMask->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        pushButtonOKDrawMask->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\350\250\255\345\256\232", nullptr));
        label_10->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\232\227\345\201\264\350\274\235\345\272\246", nullptr));
        label_11->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\230\216\345\201\264\350\274\235\345\272\246", nullptr));
        label_12->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_13->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        pushButtonOK_2->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\350\250\255\345\256\232", nullptr));
        pushButtonCancel_2->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        label_9->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\234\200\345\260\217\343\201\256\346\250\252\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        label_14->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\234\200\345\260\217\343\201\256\347\270\246\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        label_16->setText(QCoreApplication::translate("AddMonoManualItemFormClass", "\346\234\200\345\260\217\343\203\224\343\202\257\343\202\273\343\203\253\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddMonoManualItemFormClass: public Ui_AddMonoManualItemFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDMONOMANUALITEMFORM_H
