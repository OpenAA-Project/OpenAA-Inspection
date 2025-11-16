/********************************************************************************
** Form generated from reading UI file 'FormScanStrategy.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSCANSTRATEGY_H
#define UI_FORMSCANSTRATEGY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormScanStrategy
{
public:
    QFrame *frameBase;
    QLabel *label_6;
    QSpinBox *SpinBoxMaxStrategyNumb;
    QLabel *label_5;
    QTabWidget *tabWidget;
    QWidget *Scan;
    QFrame *frameStrategy;
    QWidget *Calc;
    QFrame *frameCalcStrategy;
    QPushButton *CancelButton;
    QFrame *frame;
    QLabel *label_7;
    QFrame *frameAllocCam;
    QPushButton *OKButton;

    void setupUi(QWidget *FormScanStrategy)
    {
        if (FormScanStrategy->objectName().isEmpty())
            FormScanStrategy->setObjectName("FormScanStrategy");
        FormScanStrategy->resize(470, 395);
        frameBase = new QFrame(FormScanStrategy);
        frameBase->setObjectName("frameBase");
        frameBase->setGeometry(QRect(160, 10, 301, 321));
        frameBase->setFrameShape(QFrame::StyledPanel);
        frameBase->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frameBase);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 40, 262, 16));
        SpinBoxMaxStrategyNumb = new QSpinBox(frameBase);
        SpinBoxMaxStrategyNumb->setObjectName("SpinBoxMaxStrategyNumb");
        SpinBoxMaxStrategyNumb->setGeometry(QRect(230, 10, 46, 22));
        label_5 = new QLabel(frameBase);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 211, 22));
        label_5->setFrameShape(QFrame::StyledPanel);
        label_5->setFrameShadow(QFrame::Sunken);
        tabWidget = new QTabWidget(frameBase);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 60, 281, 251));
        Scan = new QWidget();
        Scan->setObjectName("Scan");
        frameStrategy = new QFrame(Scan);
        frameStrategy->setObjectName("frameStrategy");
        frameStrategy->setGeometry(QRect(0, 0, 281, 231));
        frameStrategy->setFrameShape(QFrame::NoFrame);
        frameStrategy->setFrameShadow(QFrame::Plain);
        tabWidget->addTab(Scan, QString());
        Calc = new QWidget();
        Calc->setObjectName("Calc");
        frameCalcStrategy = new QFrame(Calc);
        frameCalcStrategy->setObjectName("frameCalcStrategy");
        frameCalcStrategy->setGeometry(QRect(0, 0, 281, 231));
        frameCalcStrategy->setFrameShape(QFrame::NoFrame);
        frameCalcStrategy->setFrameShadow(QFrame::Plain);
        tabWidget->addTab(Calc, QString());
        CancelButton = new QPushButton(FormScanStrategy);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(330, 340, 111, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        CancelButton->setIcon(icon);
        frame = new QFrame(FormScanStrategy);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 9, 141, 321));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 141, 22));
        label_7->setFrameShape(QFrame::StyledPanel);
        label_7->setFrameShadow(QFrame::Sunken);
        frameAllocCam = new QFrame(frame);
        frameAllocCam->setObjectName("frameAllocCam");
        frameAllocCam->setGeometry(QRect(10, 30, 121, 281));
        frameAllocCam->setFrameShape(QFrame::NoFrame);
        frameAllocCam->setFrameShadow(QFrame::Raised);
        OKButton = new QPushButton(FormScanStrategy);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(190, 340, 111, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        OKButton->setIcon(icon1);
        OKButton->setAutoDefault(true);

        retranslateUi(FormScanStrategy);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FormScanStrategy);
    } // setupUi

    void retranslateUi(QWidget *FormScanStrategy)
    {
        FormScanStrategy->setWindowTitle(QCoreApplication::translate("FormScanStrategy", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("FormScanStrategy", "After 1 strategy, inspection calculation is executed", nullptr));
        label_5->setText(QCoreApplication::translate("FormScanStrategy", "Scanning Strategy Number", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Scan), QCoreApplication::translate("FormScanStrategy", "Scan", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Calc), QCoreApplication::translate("FormScanStrategy", "Calc", nullptr));
        CancelButton->setText(QCoreApplication::translate("FormScanStrategy", "Cancel", nullptr));
        label_7->setText(QCoreApplication::translate("FormScanStrategy", "Allocate Camera in Page", nullptr));
        OKButton->setText(QCoreApplication::translate("FormScanStrategy", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormScanStrategy: public Ui_FormScanStrategy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSCANSTRATEGY_H
