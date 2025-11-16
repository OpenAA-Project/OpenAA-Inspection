/********************************************************************************
** Form generated from reading UI file 'frm3d.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM3D_H
#define UI_FRM3D_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frm3dClass
{
public:
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *txtPageIdx;
    QFrame *frame;
    QWidget *layoutWidget_2;
    QHBoxLayout *hboxLayout1;
    QLabel *label_3;
    QComboBox *cmbLine_2;
    QPushButton *btnLine_2;
    QWidget *layoutWidget1;
    QHBoxLayout *hboxLayout2;
    QLabel *label_2;
    QComboBox *cmbLine_1;
    QPushButton *btnLine_1;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QSpinBox *avgx;
    QLabel *label_5;
    QSpinBox *avgy;
    QPushButton *pushButton_2;

    void setupUi(QWidget *frm3dClass)
    {
        if (frm3dClass->objectName().isEmpty())
            frm3dClass->setObjectName("frm3dClass");
        frm3dClass->resize(1255, 954);
        pushButton = new QPushButton(frm3dClass);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1170, 920, 75, 23));
        layoutWidget = new QWidget(frm3dClass);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 920, 168, 22));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        hboxLayout->addWidget(label);

        txtPageIdx = new QLineEdit(layoutWidget);
        txtPageIdx->setObjectName("txtPageIdx");

        hboxLayout->addWidget(txtPageIdx);

        frame = new QFrame(frm3dClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 1231, 901));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget_2 = new QWidget(frm3dClass);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(450, 920, 215, 25));
        hboxLayout1 = new QHBoxLayout(layoutWidget_2);
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(11, 11, 11, 11);
        hboxLayout1->setObjectName("hboxLayout1");
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName("label_3");

        hboxLayout1->addWidget(label_3);

        cmbLine_2 = new QComboBox(layoutWidget_2);
        cmbLine_2->setObjectName("cmbLine_2");

        hboxLayout1->addWidget(cmbLine_2);

        btnLine_2 = new QPushButton(layoutWidget_2);
        btnLine_2->setObjectName("btnLine_2");

        hboxLayout1->addWidget(btnLine_2);

        layoutWidget1 = new QWidget(frm3dClass);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(221, 920, 215, 25));
        hboxLayout2 = new QHBoxLayout(layoutWidget1);
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(11, 11, 11, 11);
        hboxLayout2->setObjectName("hboxLayout2");
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");

        hboxLayout2->addWidget(label_2);

        cmbLine_1 = new QComboBox(layoutWidget1);
        cmbLine_1->setObjectName("cmbLine_1");

        hboxLayout2->addWidget(cmbLine_1);

        btnLine_1 = new QPushButton(layoutWidget1);
        btnLine_1->setObjectName("btnLine_1");

        hboxLayout2->addWidget(btnLine_1);

        widget = new QWidget(frm3dClass);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(701, 920, 242, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        horizontalLayout->addWidget(label_4);

        avgx = new QSpinBox(widget);
        avgx->setObjectName("avgx");
        avgx->setValue(3);

        horizontalLayout->addWidget(avgx);

        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");

        horizontalLayout->addWidget(label_5);

        avgy = new QSpinBox(widget);
        avgy->setObjectName("avgy");
        avgy->setValue(3);

        horizontalLayout->addWidget(avgy);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);


        retranslateUi(frm3dClass);

        QMetaObject::connectSlotsByName(frm3dClass);
    } // setupUi

    void retranslateUi(QWidget *frm3dClass)
    {
        frm3dClass->setWindowTitle(QCoreApplication::translate("frm3dClass", "frm3d", nullptr));
        pushButton->setText(QCoreApplication::translate("frm3dClass", "Close(&C)", nullptr));
        label->setText(QCoreApplication::translate("frm3dClass", "PageIndex", nullptr));
        label_3->setText(QCoreApplication::translate("frm3dClass", "Y AXISLine", nullptr));
        btnLine_2->setText(QCoreApplication::translate("frm3dClass", "X LineCSV", nullptr));
        label_2->setText(QCoreApplication::translate("frm3dClass", "X AXISLine", nullptr));
        btnLine_1->setText(QCoreApplication::translate("frm3dClass", "Y LineCSV", nullptr));
        label_4->setText(QCoreApplication::translate("frm3dClass", "Average", nullptr));
        label_5->setText(QCoreApplication::translate("frm3dClass", "\303\227", nullptr));
        pushButton_2->setText(QCoreApplication::translate("frm3dClass", "AverageView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frm3dClass: public Ui_frm3dClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM3D_H
