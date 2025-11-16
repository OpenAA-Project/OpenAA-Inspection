/********************************************************************************
** Form generated from reading UI file 'logintegratorfrontend.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINTEGRATORFRONTEND_H
#define UI_LOGINTEGRATORFRONTEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogIntegratorFrontEndClass
{
public:
    QAction *actionShowSettingDialog;
    QAction *actionQuit;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *pushButton_Run;
    QLineEdit *lineEdit_LotNo;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_DateRun;
    QDateEdit *dateEdit_Date;
    QPushButton *pbClose;
    QMenuBar *menuBar;
    QMenu *menu_S;

    void setupUi(QMainWindow *LogIntegratorFrontEndClass)
    {
        if (LogIntegratorFrontEndClass->objectName().isEmpty())
            LogIntegratorFrontEndClass->setObjectName(QString::fromUtf8("LogIntegratorFrontEndClass"));
        LogIntegratorFrontEndClass->resize(265, 373);
        actionShowSettingDialog = new QAction(LogIntegratorFrontEndClass);
        actionShowSettingDialog->setObjectName(QString::fromUtf8("actionShowSettingDialog"));
        actionQuit = new QAction(LogIntegratorFrontEndClass);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(LogIntegratorFrontEndClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 20, 201, 131));
        pushButton_Run = new QPushButton(groupBox);
        pushButton_Run->setObjectName(QString::fromUtf8("pushButton_Run"));
        pushButton_Run->setGeometry(QRect(50, 70, 111, 41));
        pushButton_Run->setAutoDefault(true);
        lineEdit_LotNo = new QLineEdit(groupBox);
        lineEdit_LotNo->setObjectName(QString::fromUtf8("lineEdit_LotNo"));
        lineEdit_LotNo->setGeometry(QRect(50, 30, 110, 21));
        lineEdit_LotNo->setMaxLength(36767);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 160, 201, 131));
        pushButton_DateRun = new QPushButton(groupBox_2);
        pushButton_DateRun->setObjectName(QString::fromUtf8("pushButton_DateRun"));
        pushButton_DateRun->setGeometry(QRect(50, 70, 111, 41));
        pushButton_DateRun->setAutoDefault(true);
        dateEdit_Date = new QDateEdit(groupBox_2);
        dateEdit_Date->setObjectName(QString::fromUtf8("dateEdit_Date"));
        dateEdit_Date->setGeometry(QRect(50, 30, 110, 22));
        dateEdit_Date->setCalendarPopup(true);
        pbClose = new QPushButton(centralWidget);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));
        pbClose->setGeometry(QRect(140, 310, 91, 31));
        LogIntegratorFrontEndClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LogIntegratorFrontEndClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 265, 18));
        menu_S = new QMenu(menuBar);
        menu_S->setObjectName(QString::fromUtf8("menu_S"));
        LogIntegratorFrontEndClass->setMenuBar(menuBar);
        QWidget::setTabOrder(lineEdit_LotNo, pushButton_Run);
        QWidget::setTabOrder(pushButton_Run, dateEdit_Date);
        QWidget::setTabOrder(dateEdit_Date, pushButton_DateRun);
        QWidget::setTabOrder(pushButton_DateRun, pbClose);

        menuBar->addAction(menu_S->menuAction());
        menu_S->addAction(actionShowSettingDialog);
        menu_S->addSeparator();
        menu_S->addAction(actionQuit);

        retranslateUi(LogIntegratorFrontEndClass);

        pushButton_Run->setDefault(true);
        pushButton_DateRun->setDefault(true);


        QMetaObject::connectSlotsByName(LogIntegratorFrontEndClass);
    } // setupUi

    void retranslateUi(QMainWindow *LogIntegratorFrontEndClass)
    {
        LogIntegratorFrontEndClass->setWindowTitle(QCoreApplication::translate("LogIntegratorFrontEndClass", "\343\203\255\343\202\260\347\265\261\345\220\210\343\202\275\343\203\225\343\203\210", nullptr));
        actionShowSettingDialog->setText(QCoreApplication::translate("LogIntegratorFrontEndClass", "\345\210\235\346\234\237\350\250\255\345\256\232(&I)", nullptr));
        actionShowSettingDialog->setIconText(QCoreApplication::translate("LogIntegratorFrontEndClass", "\345\210\235\346\234\237\350\250\255\345\256\232(I)", nullptr));
#if QT_CONFIG(tooltip)
        actionShowSettingDialog->setToolTip(QCoreApplication::translate("LogIntegratorFrontEndClass", "\343\203\255\343\202\260\343\201\256\343\201\202\343\202\213HD\343\202\204\345\207\272\345\212\233\345\205\210\343\203\225\343\202\251\343\203\253\343\203\200\343\202\222\350\250\255\345\256\232\343\201\227\343\201\276\343\201\231", nullptr));
#endif // QT_CONFIG(tooltip)
        actionQuit->setText(QCoreApplication::translate("LogIntegratorFrontEndClass", "\347\265\202\344\272\206(&Q)", nullptr));
#if QT_CONFIG(tooltip)
        actionQuit->setToolTip(QCoreApplication::translate("LogIntegratorFrontEndClass", "\343\203\255\343\202\260\347\265\261\345\220\210\343\202\275\343\203\225\343\203\210\343\202\222\347\265\202\344\272\206\343\201\227\343\201\276\343\201\231", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("LogIntegratorFrontEndClass", "\343\203\255\343\203\203\343\203\210\347\225\252\345\217\267\343\201\247\346\214\207\345\256\232", nullptr));
        pushButton_Run->setText(QCoreApplication::translate("LogIntegratorFrontEndClass", "\345\207\246\347\220\206\351\226\213\345\247\213", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_Run->setShortcut(QCoreApplication::translate("LogIntegratorFrontEndClass", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBox_2->setTitle(QCoreApplication::translate("LogIntegratorFrontEndClass", "\346\227\245\344\273\230\343\201\247\346\214\207\345\256\232", nullptr));
        pushButton_DateRun->setText(QCoreApplication::translate("LogIntegratorFrontEndClass", "\345\207\246\347\220\206\351\226\213\345\247\213", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_DateRun->setShortcut(QCoreApplication::translate("LogIntegratorFrontEndClass", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        pbClose->setText(QCoreApplication::translate("LogIntegratorFrontEndClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        menu_S->setTitle(QCoreApplication::translate("LogIntegratorFrontEndClass", "\343\202\267\343\202\271\343\203\206\343\203\240(&S)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogIntegratorFrontEndClass: public Ui_LogIntegratorFrontEndClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINTEGRATORFRONTEND_H
