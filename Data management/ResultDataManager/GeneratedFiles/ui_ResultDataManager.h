/********************************************************************************
** Form generated from reading UI file 'ResultDataManager.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTDATAMANAGER_H
#define UI_RESULTDATAMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResultDataManagerClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonByLot;
    QPushButton *pushButtonByDayTime;
    QPushButton *pushButtonSetting;
    QPushButton *pushButtonClose;

    void setupUi(QMainWindow *ResultDataManagerClass)
    {
        if (ResultDataManagerClass->objectName().isEmpty())
            ResultDataManagerClass->setObjectName("ResultDataManagerClass");
        ResultDataManagerClass->resize(189, 294);
        ResultDataManagerClass->setMinimumSize(QSize(189, 294));
        ResultDataManagerClass->setMaximumSize(QSize(189, 294));
        centralWidget = new QWidget(ResultDataManagerClass);
        centralWidget->setObjectName("centralWidget");
        pushButtonByLot = new QPushButton(centralWidget);
        pushButtonByLot->setObjectName("pushButtonByLot");
        pushButtonByLot->setGeometry(QRect(20, 20, 151, 51));
        pushButtonByDayTime = new QPushButton(centralWidget);
        pushButtonByDayTime->setObjectName("pushButtonByDayTime");
        pushButtonByDayTime->setEnabled(true);
        pushButtonByDayTime->setGeometry(QRect(20, 80, 151, 51));
        pushButtonSetting = new QPushButton(centralWidget);
        pushButtonSetting->setObjectName("pushButtonSetting");
        pushButtonSetting->setGeometry(QRect(20, 170, 151, 51));
        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(20, 230, 151, 51));
        ResultDataManagerClass->setCentralWidget(centralWidget);

        retranslateUi(ResultDataManagerClass);

        QMetaObject::connectSlotsByName(ResultDataManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ResultDataManagerClass)
    {
        ResultDataManagerClass->setWindowTitle(QCoreApplication::translate("ResultDataManagerClass", "ResultDataManager", nullptr));
        pushButtonByLot->setText(QCoreApplication::translate("ResultDataManagerClass", "\343\203\255\343\203\203\343\203\210\343\201\247\347\256\241\347\220\206", nullptr));
        pushButtonByDayTime->setText(QCoreApplication::translate("ResultDataManagerClass", "\346\227\245\344\273\230\343\201\247\347\256\241\347\220\206", nullptr));
        pushButtonSetting->setText(QCoreApplication::translate("ResultDataManagerClass", "\350\250\255\345\256\232", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ResultDataManagerClass", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResultDataManagerClass: public Ui_ResultDataManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTDATAMANAGER_H
