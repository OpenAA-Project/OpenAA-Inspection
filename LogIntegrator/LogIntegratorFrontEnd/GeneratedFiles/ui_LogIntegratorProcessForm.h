/********************************************************************************
** Form generated from reading UI file 'LogIntegratorProcessForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINTEGRATORPROCESSFORM_H
#define UI_LOGINTEGRATORPROCESSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogIntegratorProcessFormClass
{
public:
    QProgressBar *pgbProcessing;
    QLabel *label;
    QLabel *lbLotNo;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *lbNo;
    QLabel *lbCount;

    void setupUi(QWidget *LogIntegratorProcessFormClass)
    {
        if (LogIntegratorProcessFormClass->objectName().isEmpty())
            LogIntegratorProcessFormClass->setObjectName(QString::fromUtf8("LogIntegratorProcessFormClass"));
        LogIntegratorProcessFormClass->resize(400, 123);
        pgbProcessing = new QProgressBar(LogIntegratorProcessFormClass);
        pgbProcessing->setObjectName(QString::fromUtf8("pgbProcessing"));
        pgbProcessing->setGeometry(QRect(20, 80, 371, 31));
        pgbProcessing->setValue(0);
        label = new QLabel(LogIntegratorProcessFormClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(155, 14, 91, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        lbLotNo = new QLabel(LogIntegratorProcessFormClass);
        lbLotNo->setObjectName(QString::fromUtf8("lbLotNo"));
        lbLotNo->setGeometry(QRect(50, 40, 151, 31));
        lbLotNo->setMaximumSize(QSize(291, 41));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        lbLotNo->setFont(font1);
        lbLotNo->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(LogIntegratorProcessFormClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(200, 40, 81, 31));
        label_2->setMaximumSize(QSize(291, 41));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(LogIntegratorProcessFormClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(290, 40, 21, 31));
        label_3->setMaximumSize(QSize(291, 41));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(LogIntegratorProcessFormClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(370, 40, 21, 31));
        label_4->setMaximumSize(QSize(291, 41));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(LogIntegratorProcessFormClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(330, 40, 21, 31));
        label_5->setMaximumSize(QSize(291, 41));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        lbNo = new QLabel(LogIntegratorProcessFormClass);
        lbNo->setObjectName(QString::fromUtf8("lbNo"));
        lbNo->setGeometry(QRect(310, 40, 21, 31));
        lbNo->setMaximumSize(QSize(291, 41));
        lbNo->setFont(font);
        lbNo->setAlignment(Qt::AlignCenter);
        lbCount = new QLabel(LogIntegratorProcessFormClass);
        lbCount->setObjectName(QString::fromUtf8("lbCount"));
        lbCount->setGeometry(QRect(350, 40, 21, 31));
        lbCount->setMaximumSize(QSize(291, 41));
        lbCount->setFont(font);
        lbCount->setAlignment(Qt::AlignCenter);

        retranslateUi(LogIntegratorProcessFormClass);

        QMetaObject::connectSlotsByName(LogIntegratorProcessFormClass);
    } // setupUi

    void retranslateUi(QWidget *LogIntegratorProcessFormClass)
    {
        LogIntegratorProcessFormClass->setWindowTitle(QCoreApplication::translate("LogIntegratorProcessFormClass", "\345\207\246\347\220\206\344\270\255", nullptr));
        label->setText(QCoreApplication::translate("LogIntegratorProcessFormClass", "\343\203\255\343\203\203\343\203\210\347\225\252\345\217\267", nullptr));
        lbLotNo->setText(QCoreApplication::translate("LogIntegratorProcessFormClass", "??????????", nullptr));
        label_2->setText(QCoreApplication::translate("LogIntegratorProcessFormClass", "\343\202\222\345\207\246\347\220\206\344\270\255", nullptr));
        label_3->setText(QCoreApplication::translate("LogIntegratorProcessFormClass", "\357\274\210", nullptr));
        label_4->setText(QCoreApplication::translate("LogIntegratorProcessFormClass", "\357\274\211", nullptr));
        label_5->setText(QCoreApplication::translate("LogIntegratorProcessFormClass", "/", nullptr));
        lbNo->setText(QCoreApplication::translate("LogIntegratorProcessFormClass", "99", nullptr));
        lbCount->setText(QCoreApplication::translate("LogIntegratorProcessFormClass", "99", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogIntegratorProcessFormClass: public Ui_LogIntegratorProcessFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINTEGRATORPROCESSFORM_H
