/********************************************************************************
** Form generated from reading UI file 'ReportDisk.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTDISK_H
#define UI_REPORTDISK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReportDiskClass
{
public:
    QWidget *centralWidget;
    QComboBox *comboBoxDrive1;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxAlertSpace1;
    QLabel *label_3;
    QPushButton *pushButtonOK;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *spinBoxAlertSpace2;
    QComboBox *comboBoxDrive2;
    QSpinBox *spinBoxAlertSpace3;
    QComboBox *comboBoxDrive3;
    QSpinBox *spinBoxAlertSpace4;
    QComboBox *comboBoxDrive4;
    QLabel *label_7;
    QLineEdit *lineEditIPAddress;
    QLineEdit *lineEditComputerName;
    QFrame *frame;
    QLabel *label_9;
    QSpinBox *spinBoxYear;
    QLabel *label_10;
    QLabel *label_11;
    QSpinBox *spinBoxMonth;
    QLabel *label_12;
    QSpinBox *spinBoxDay;
    QLabel *label_13;
    QSpinBox *spinBoxHour;
    QLabel *label_14;
    QSpinBox *spinBoxMinute;
    QLabel *label_15;
    QSpinBox *spinBoxSecond;
    QCheckBox *checkBoxExecuteDelete;
    QFrame *frameDestination;
    QListWidget *listWidgetDestination;
    QLabel *label_16;
    QPushButton *pushButtonDeleteDestination;
    QPushButton *pushButtonAddDestination;
    QCheckBox *checkBoxAutoMode;
    QPushButton *pushButtonForceExecute;

    void setupUi(QMainWindow *ReportDiskClass)
    {
        if (ReportDiskClass->objectName().isEmpty())
            ReportDiskClass->setObjectName("ReportDiskClass");
        ReportDiskClass->resize(421, 559);
        centralWidget = new QWidget(ReportDiskClass);
        centralWidget->setObjectName("centralWidget");
        comboBoxDrive1 = new QComboBox(centralWidget);
        comboBoxDrive1->setObjectName("comboBoxDrive1");
        comboBoxDrive1->setGeometry(QRect(10, 60, 71, 22));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(90, 40, 131, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxAlertSpace1 = new QSpinBox(centralWidget);
        spinBoxAlertSpace1->setObjectName("spinBoxAlertSpace1");
        spinBoxAlertSpace1->setGeometry(QRect(90, 60, 91, 22));
        spinBoxAlertSpace1->setMaximum(1000000000);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(180, 60, 21, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(centralWidget);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(150, 510, 121, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(180, 80, 21, 21));
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(180, 100, 21, 21));
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(180, 120, 21, 21));
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxAlertSpace2 = new QSpinBox(centralWidget);
        spinBoxAlertSpace2->setObjectName("spinBoxAlertSpace2");
        spinBoxAlertSpace2->setGeometry(QRect(90, 80, 91, 22));
        spinBoxAlertSpace2->setMaximum(100000000);
        comboBoxDrive2 = new QComboBox(centralWidget);
        comboBoxDrive2->setObjectName("comboBoxDrive2");
        comboBoxDrive2->setGeometry(QRect(10, 80, 71, 22));
        spinBoxAlertSpace3 = new QSpinBox(centralWidget);
        spinBoxAlertSpace3->setObjectName("spinBoxAlertSpace3");
        spinBoxAlertSpace3->setGeometry(QRect(90, 100, 91, 22));
        spinBoxAlertSpace3->setMaximum(100000000);
        comboBoxDrive3 = new QComboBox(centralWidget);
        comboBoxDrive3->setObjectName("comboBoxDrive3");
        comboBoxDrive3->setGeometry(QRect(10, 100, 71, 22));
        spinBoxAlertSpace4 = new QSpinBox(centralWidget);
        spinBoxAlertSpace4->setObjectName("spinBoxAlertSpace4");
        spinBoxAlertSpace4->setGeometry(QRect(90, 120, 91, 22));
        spinBoxAlertSpace4->setMaximum(100000000);
        comboBoxDrive4 = new QComboBox(centralWidget);
        comboBoxDrive4->setObjectName("comboBoxDrive4");
        comboBoxDrive4->setGeometry(QRect(10, 120, 71, 22));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(230, 40, 181, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditIPAddress = new QLineEdit(centralWidget);
        lineEditIPAddress->setObjectName("lineEditIPAddress");
        lineEditIPAddress->setGeometry(QRect(230, 60, 181, 20));
        lineEditComputerName = new QLineEdit(centralWidget);
        lineEditComputerName->setObjectName("lineEditComputerName");
        lineEditComputerName->setGeometry(QRect(10, 10, 211, 20));
        lineEditComputerName->setReadOnly(true);
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 180, 401, 311));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 10, 191, 21));
        spinBoxYear = new QSpinBox(frame);
        spinBoxYear->setObjectName("spinBoxYear");
        spinBoxYear->setGeometry(QRect(10, 40, 61, 22));
        spinBoxYear->setMinimum(2000);
        spinBoxYear->setMaximum(2099);
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(70, 40, 21, 21));
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(150, 40, 21, 21));
        spinBoxMonth = new QSpinBox(frame);
        spinBoxMonth->setObjectName("spinBoxMonth");
        spinBoxMonth->setGeometry(QRect(90, 40, 50, 22));
        spinBoxMonth->setMinimum(1);
        spinBoxMonth->setMaximum(12);
        spinBoxMonth->setValue(1);
        label_12 = new QLabel(frame);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(240, 40, 21, 21));
        spinBoxDay = new QSpinBox(frame);
        spinBoxDay->setObjectName("spinBoxDay");
        spinBoxDay->setGeometry(QRect(180, 40, 50, 22));
        spinBoxDay->setMinimum(1);
        spinBoxDay->setMaximum(31);
        label_13 = new QLabel(frame);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(70, 70, 21, 21));
        spinBoxHour = new QSpinBox(frame);
        spinBoxHour->setObjectName("spinBoxHour");
        spinBoxHour->setGeometry(QRect(10, 70, 50, 22));
        spinBoxHour->setMaximum(23);
        label_14 = new QLabel(frame);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(150, 70, 21, 21));
        spinBoxMinute = new QSpinBox(frame);
        spinBoxMinute->setObjectName("spinBoxMinute");
        spinBoxMinute->setGeometry(QRect(90, 70, 50, 22));
        spinBoxMinute->setMaximum(59);
        label_15 = new QLabel(frame);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(240, 70, 21, 21));
        spinBoxSecond = new QSpinBox(frame);
        spinBoxSecond->setObjectName("spinBoxSecond");
        spinBoxSecond->setGeometry(QRect(180, 70, 50, 22));
        spinBoxSecond->setMaximum(59);
        checkBoxExecuteDelete = new QCheckBox(frame);
        checkBoxExecuteDelete->setObjectName("checkBoxExecuteDelete");
        checkBoxExecuteDelete->setGeometry(QRect(10, 110, 251, 19));
        frameDestination = new QFrame(frame);
        frameDestination->setObjectName("frameDestination");
        frameDestination->setGeometry(QRect(0, 130, 401, 151));
        frameDestination->setFrameShape(QFrame::StyledPanel);
        frameDestination->setFrameShadow(QFrame::Raised);
        listWidgetDestination = new QListWidget(frameDestination);
        listWidgetDestination->setObjectName("listWidgetDestination");
        listWidgetDestination->setGeometry(QRect(10, 20, 381, 101));
        label_16 = new QLabel(frameDestination);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 0, 251, 21));
        pushButtonDeleteDestination = new QPushButton(frameDestination);
        pushButtonDeleteDestination->setObjectName("pushButtonDeleteDestination");
        pushButtonDeleteDestination->setGeometry(QRect(300, 120, 93, 28));
        pushButtonAddDestination = new QPushButton(frameDestination);
        pushButtonAddDestination->setObjectName("pushButtonAddDestination");
        pushButtonAddDestination->setGeometry(QRect(10, 120, 111, 28));
        checkBoxAutoMode = new QCheckBox(centralWidget);
        checkBoxAutoMode->setObjectName("checkBoxAutoMode");
        checkBoxAutoMode->setGeometry(QRect(10, 160, 291, 19));
        pushButtonForceExecute = new QPushButton(centralWidget);
        pushButtonForceExecute->setObjectName("pushButtonForceExecute");
        pushButtonForceExecute->setGeometry(QRect(320, 150, 93, 28));
        ReportDiskClass->setCentralWidget(centralWidget);

        retranslateUi(ReportDiskClass);

        QMetaObject::connectSlotsByName(ReportDiskClass);
    } // setupUi

    void retranslateUi(QMainWindow *ReportDiskClass)
    {
        ReportDiskClass->setWindowTitle(QCoreApplication::translate("ReportDiskClass", "ReportDisk", nullptr));
        label->setText(QCoreApplication::translate("ReportDiskClass", "Drive", nullptr));
        label_2->setText(QCoreApplication::translate("ReportDiskClass", "\350\255\246\345\221\212\345\256\271\351\207\217", nullptr));
        label_3->setText(QCoreApplication::translate("ReportDiskClass", "KB", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ReportDiskClass", "\350\250\255\345\256\232\344\277\235\345\255\230", nullptr));
        label_4->setText(QCoreApplication::translate("ReportDiskClass", "KB", nullptr));
        label_5->setText(QCoreApplication::translate("ReportDiskClass", "KB", nullptr));
        label_6->setText(QCoreApplication::translate("ReportDiskClass", "KB", nullptr));
        label_7->setText(QCoreApplication::translate("ReportDiskClass", "\347\231\272\345\240\261\345\205\210", nullptr));
        label_9->setText(QCoreApplication::translate("ReportDiskClass", "\343\201\223\343\202\214\343\202\210\343\202\212\345\217\244\343\201\204\343\203\225\343\202\241\343\202\244\343\203\253\343\202\222\347\247\273\345\213\225\343\203\273\345\211\212\351\231\244", nullptr));
        label_10->setText(QCoreApplication::translate("ReportDiskClass", "\345\271\264", nullptr));
        label_11->setText(QCoreApplication::translate("ReportDiskClass", "\346\234\210", nullptr));
        label_12->setText(QCoreApplication::translate("ReportDiskClass", "\346\227\245", nullptr));
        label_13->setText(QCoreApplication::translate("ReportDiskClass", "\346\231\202", nullptr));
        label_14->setText(QCoreApplication::translate("ReportDiskClass", "\345\210\206", nullptr));
        label_15->setText(QCoreApplication::translate("ReportDiskClass", "\347\247\222", nullptr));
        checkBoxExecuteDelete->setText(QCoreApplication::translate("ReportDiskClass", "\345\211\212\351\231\244\343\202\222\345\256\237\350\241\214", nullptr));
        label_16->setText(QCoreApplication::translate("ReportDiskClass", "\347\247\273\345\213\225\345\205\210", nullptr));
        pushButtonDeleteDestination->setText(QCoreApplication::translate("ReportDiskClass", "\347\247\273\345\213\225\345\205\210\345\211\212\351\231\244", nullptr));
        pushButtonAddDestination->setText(QCoreApplication::translate("ReportDiskClass", "\347\247\273\345\213\225\345\205\210\343\202\222\350\277\275\345\212\240", nullptr));
        checkBoxAutoMode->setText(QCoreApplication::translate("ReportDiskClass", "\350\207\252\345\213\225\347\247\273\345\213\225\343\203\273\345\211\212\351\231\244", nullptr));
        pushButtonForceExecute->setText(QCoreApplication::translate("ReportDiskClass", "\345\274\267\345\210\266\345\256\237\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReportDiskClass: public Ui_ReportDiskClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTDISK_H
