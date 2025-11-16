/********************************************************************************
** Form generated from reading UI file 'TimingChartForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMINGCHARTFORM_H
#define UI_TIMINGCHARTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimingChartForm
{
public:
    QScrollArea *scrollAreaTitle;
    QWidget *scrollAreaWidgetContents;
    QScrollBar *horizontalScrollBar;
    QComboBox *comboBoxTimeUnit;
    QFrame *frameScale;
    QScrollArea *scrollAreaSignal;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *pushButtonUpdate;

    void setupUi(QWidget *TimingChartForm)
    {
        if (TimingChartForm->objectName().isEmpty())
            TimingChartForm->setObjectName(QString::fromUtf8("TimingChartForm"));
        TimingChartForm->resize(931, 591);
        scrollAreaTitle = new QScrollArea(TimingChartForm);
        scrollAreaTitle->setObjectName(QString::fromUtf8("scrollAreaTitle"));
        scrollAreaTitle->setGeometry(QRect(0, 24, 191, 541));
        scrollAreaTitle->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 189, 539));
        scrollAreaTitle->setWidget(scrollAreaWidgetContents);
        horizontalScrollBar = new QScrollBar(TimingChartForm);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(190, 0, 741, 24));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        comboBoxTimeUnit = new QComboBox(TimingChartForm);
        comboBoxTimeUnit->addItem(QString());
        comboBoxTimeUnit->addItem(QString());
        comboBoxTimeUnit->addItem(QString());
        comboBoxTimeUnit->addItem(QString());
        comboBoxTimeUnit->setObjectName(QString::fromUtf8("comboBoxTimeUnit"));
        comboBoxTimeUnit->setGeometry(QRect(0, 0, 191, 24));
        frameScale = new QFrame(TimingChartForm);
        frameScale->setObjectName(QString::fromUtf8("frameScale"));
        frameScale->setGeometry(QRect(190, 566, 731, 24));
        frameScale->setFrameShape(QFrame::StyledPanel);
        frameScale->setFrameShadow(QFrame::Raised);
        scrollAreaSignal = new QScrollArea(TimingChartForm);
        scrollAreaSignal->setObjectName(QString::fromUtf8("scrollAreaSignal"));
        scrollAreaSignal->setGeometry(QRect(190, 24, 741, 541));
        scrollAreaSignal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaSignal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaSignal->setWidgetResizable(false);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 739, 539));
        scrollAreaSignal->setWidget(scrollAreaWidgetContents_2);
        pushButtonUpdate = new QPushButton(TimingChartForm);
        pushButtonUpdate->setObjectName(QString::fromUtf8("pushButtonUpdate"));
        pushButtonUpdate->setGeometry(QRect(1, 566, 191, 24));

        retranslateUi(TimingChartForm);

        QMetaObject::connectSlotsByName(TimingChartForm);
    } // setupUi

    void retranslateUi(QWidget *TimingChartForm)
    {
        TimingChartForm->setWindowTitle(QCoreApplication::translate("TimingChartForm", "Form", nullptr));
        comboBoxTimeUnit->setItemText(0, QCoreApplication::translate("TimingChartForm", "1ms", nullptr));
        comboBoxTimeUnit->setItemText(1, QCoreApplication::translate("TimingChartForm", "10ms", nullptr));
        comboBoxTimeUnit->setItemText(2, QCoreApplication::translate("TimingChartForm", "100ms", nullptr));
        comboBoxTimeUnit->setItemText(3, QCoreApplication::translate("TimingChartForm", "1s", nullptr));

        pushButtonUpdate->setText(QCoreApplication::translate("TimingChartForm", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimingChartForm: public Ui_TimingChartForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMINGCHARTFORM_H
