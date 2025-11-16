/********************************************************************************
** Form generated from reading UI file 'TestSequenceDLLDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTSEQUENCEDLLDIALOG_H
#define UI_TESTSEQUENCEDLLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestSequenceDLLDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEditCommand;
    QStackedWidget *stackedWidgetParam1;
    QWidget *page;
    QLineEdit *lineEditParam1;
    QWidget *page_2;
    QSpinBox *spinBoxParam1;
    QStackedWidget *stackedWidgetParam2;
    QWidget *page_3;
    QLineEdit *lineEditParam2;
    QWidget *page_4;
    QSpinBox *spinBoxParam2;
    QStackedWidget *stackedWidgetParam3;
    QWidget *page_5;
    QLineEdit *lineEditParam3;
    QWidget *page_6;
    QSpinBox *spinBoxParam3;
    QPushButton *pushButtonTest;
    QPushButton *pushButtonClose;
    QComboBox *comboBoxFunction;

    void setupUi(QDialog *TestSequenceDLLDialog)
    {
        if (TestSequenceDLLDialog->objectName().isEmpty())
            TestSequenceDLLDialog->setObjectName("TestSequenceDLLDialog");
        TestSequenceDLLDialog->resize(400, 226);
        label = new QLabel(TestSequenceDLLDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 40, 101, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(TestSequenceDLLDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 10, 101, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(TestSequenceDLLDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 80, 101, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(TestSequenceDLLDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 110, 101, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(TestSequenceDLLDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 140, 101, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        lineEditCommand = new QLineEdit(TestSequenceDLLDialog);
        lineEditCommand->setObjectName("lineEditCommand");
        lineEditCommand->setGeometry(QRect(140, 40, 221, 20));
        stackedWidgetParam1 = new QStackedWidget(TestSequenceDLLDialog);
        stackedWidgetParam1->setObjectName("stackedWidgetParam1");
        stackedWidgetParam1->setGeometry(QRect(140, 80, 231, 31));
        page = new QWidget();
        page->setObjectName("page");
        lineEditParam1 = new QLineEdit(page);
        lineEditParam1->setObjectName("lineEditParam1");
        lineEditParam1->setGeometry(QRect(0, 0, 211, 20));
        stackedWidgetParam1->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        spinBoxParam1 = new QSpinBox(page_2);
        spinBoxParam1->setObjectName("spinBoxParam1");
        spinBoxParam1->setGeometry(QRect(0, 0, 81, 22));
        spinBoxParam1->setMinimum(-65535);
        spinBoxParam1->setMaximum(65535);
        stackedWidgetParam1->addWidget(page_2);
        stackedWidgetParam2 = new QStackedWidget(TestSequenceDLLDialog);
        stackedWidgetParam2->setObjectName("stackedWidgetParam2");
        stackedWidgetParam2->setGeometry(QRect(140, 110, 231, 31));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        lineEditParam2 = new QLineEdit(page_3);
        lineEditParam2->setObjectName("lineEditParam2");
        lineEditParam2->setGeometry(QRect(0, 0, 211, 20));
        stackedWidgetParam2->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        spinBoxParam2 = new QSpinBox(page_4);
        spinBoxParam2->setObjectName("spinBoxParam2");
        spinBoxParam2->setGeometry(QRect(0, 0, 81, 22));
        spinBoxParam2->setMinimum(-65535);
        spinBoxParam2->setMaximum(65535);
        stackedWidgetParam2->addWidget(page_4);
        stackedWidgetParam3 = new QStackedWidget(TestSequenceDLLDialog);
        stackedWidgetParam3->setObjectName("stackedWidgetParam3");
        stackedWidgetParam3->setGeometry(QRect(140, 140, 231, 31));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        lineEditParam3 = new QLineEdit(page_5);
        lineEditParam3->setObjectName("lineEditParam3");
        lineEditParam3->setGeometry(QRect(0, 0, 211, 20));
        stackedWidgetParam3->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        spinBoxParam3 = new QSpinBox(page_6);
        spinBoxParam3->setObjectName("spinBoxParam3");
        spinBoxParam3->setGeometry(QRect(0, 0, 81, 22));
        spinBoxParam3->setMinimum(-65535);
        spinBoxParam3->setMaximum(65535);
        stackedWidgetParam3->addWidget(page_6);
        pushButtonTest = new QPushButton(TestSequenceDLLDialog);
        pushButtonTest->setObjectName("pushButtonTest");
        pushButtonTest->setGeometry(QRect(80, 180, 111, 31));
        pushButtonClose = new QPushButton(TestSequenceDLLDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(220, 180, 111, 31));
        comboBoxFunction = new QComboBox(TestSequenceDLLDialog);
        comboBoxFunction->setObjectName("comboBoxFunction");
        comboBoxFunction->setGeometry(QRect(140, 10, 221, 22));

        retranslateUi(TestSequenceDLLDialog);

        stackedWidgetParam1->setCurrentIndex(1);
        stackedWidgetParam2->setCurrentIndex(1);
        stackedWidgetParam3->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TestSequenceDLLDialog);
    } // setupUi

    void retranslateUi(QDialog *TestSequenceDLLDialog)
    {
        TestSequenceDLLDialog->setWindowTitle(QCoreApplication::translate("TestSequenceDLLDialog", "Test SequenceDLL", nullptr));
        label->setText(QCoreApplication::translate("TestSequenceDLLDialog", "Command Param", nullptr));
        label_2->setText(QCoreApplication::translate("TestSequenceDLLDialog", "Function", nullptr));
        label_3->setText(QCoreApplication::translate("TestSequenceDLLDialog", "Param 1", nullptr));
        label_4->setText(QCoreApplication::translate("TestSequenceDLLDialog", "Param 2", nullptr));
        label_5->setText(QCoreApplication::translate("TestSequenceDLLDialog", "Param 3", nullptr));
        pushButtonTest->setText(QCoreApplication::translate("TestSequenceDLLDialog", "Test", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("TestSequenceDLLDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestSequenceDLLDialog: public Ui_TestSequenceDLLDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTSEQUENCEDLLDIALOG_H
