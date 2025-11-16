/********************************************************************************
** Form generated from reading UI file 'AutoStartParamList.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSTARTPARAMLIST_H
#define UI_AUTOSTARTPARAMLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoStartParamListClass
{
public:
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxLoopCount;
    QLabel *label;
    QTableWidget *tableWidget;
    QPushButton *pushButtonAdd;
    QFrame *frame;
    QLabel *label_2;
    QCheckBox *checkBoxAllDesktopArea;
    QSpinBox *spinBoxAreaTop;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxAreaLeft;
    QLabel *label_5;
    QSpinBox *spinBoxAreaRight;
    QLabel *label_6;
    QSpinBox *spinBoxAreaBottom;
    QCheckBox *checkBoxTasktray;

    void setupUi(QDialog *AutoStartParamListClass)
    {
        if (AutoStartParamListClass->objectName().isEmpty())
            AutoStartParamListClass->setObjectName("AutoStartParamListClass");
        AutoStartParamListClass->resize(982, 481);
        pushButtonOK = new QPushButton(AutoStartParamListClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(430, 440, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/AutoStartList/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        spinBoxLoopCount = new QSpinBox(AutoStartParamListClass);
        spinBoxLoopCount->setObjectName("spinBoxLoopCount");
        spinBoxLoopCount->setGeometry(QRect(170, 220, 81, 22));
        spinBoxLoopCount->setMaximum(999999);
        label = new QLabel(AutoStartParamListClass);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 220, 131, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidget = new QTableWidget(AutoStartParamListClass);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 961, 192));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonAdd = new QPushButton(AutoStartParamListClass);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(430, 210, 93, 31));
        frame = new QFrame(AutoStartParamListClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 260, 271, 201));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 271, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxAllDesktopArea = new QCheckBox(frame);
        checkBoxAllDesktopArea->setObjectName("checkBoxAllDesktopArea");
        checkBoxAllDesktopArea->setGeometry(QRect(10, 20, 171, 19));
        spinBoxAreaTop = new QSpinBox(frame);
        spinBoxAreaTop->setObjectName("spinBoxAreaTop");
        spinBoxAreaTop->setGeometry(QRect(80, 70, 81, 22));
        spinBoxAreaTop->setMaximum(999999);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 50, 81, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 100, 81, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxAreaLeft = new QSpinBox(frame);
        spinBoxAreaLeft->setObjectName("spinBoxAreaLeft");
        spinBoxAreaLeft->setGeometry(QRect(20, 120, 81, 22));
        spinBoxAreaLeft->setMaximum(999999);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(150, 100, 81, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxAreaRight = new QSpinBox(frame);
        spinBoxAreaRight->setObjectName("spinBoxAreaRight");
        spinBoxAreaRight->setGeometry(QRect(150, 120, 81, 22));
        spinBoxAreaRight->setMaximum(999999);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(80, 150, 81, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxAreaBottom = new QSpinBox(frame);
        spinBoxAreaBottom->setObjectName("spinBoxAreaBottom");
        spinBoxAreaBottom->setGeometry(QRect(80, 170, 81, 22));
        spinBoxAreaBottom->setMaximum(999999);
        checkBoxTasktray = new QCheckBox(AutoStartParamListClass);
        checkBoxTasktray->setObjectName("checkBoxTasktray");
        checkBoxTasktray->setGeometry(QRect(360, 340, 201, 19));

        retranslateUi(AutoStartParamListClass);

        QMetaObject::connectSlotsByName(AutoStartParamListClass);
    } // setupUi

    void retranslateUi(QDialog *AutoStartParamListClass)
    {
        AutoStartParamListClass->setWindowTitle(QCoreApplication::translate("AutoStartParamListClass", "Executional list", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AutoStartParamListClass", "OK", nullptr));
        label->setText(QCoreApplication::translate("AutoStartParamListClass", "\345\276\205\346\251\237\347\247\222\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AutoStartParamListClass", "Path", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AutoStartParamListClass", "Exe file", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AutoStartParamListClass", "Parameter", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AutoStartParamListClass", "Location", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("AutoStartParamListClass", "Add", nullptr));
        label_2->setText(QCoreApplication::translate("AutoStartParamListClass", "\350\250\255\345\256\232\351\240\230\345\237\237", nullptr));
        checkBoxAllDesktopArea->setText(QCoreApplication::translate("AutoStartParamListClass", "All desktop area", nullptr));
        label_3->setText(QCoreApplication::translate("AutoStartParamListClass", "Top", nullptr));
        label_4->setText(QCoreApplication::translate("AutoStartParamListClass", "Left", nullptr));
        label_5->setText(QCoreApplication::translate("AutoStartParamListClass", "Right", nullptr));
        label_6->setText(QCoreApplication::translate("AutoStartParamListClass", "Bottom", nullptr));
        checkBoxTasktray->setText(QCoreApplication::translate("AutoStartParamListClass", "Tasktray on booting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoStartParamListClass: public Ui_AutoStartParamListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSTARTPARAMLIST_H
