/********************************************************************************
** Form generated from reading UI file 'LogIntegratorSettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINTEGRATORSETTINGDIALOG_H
#define UI_LOGINTEGRATORSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LogIntegratorSettingDialogClass
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *lineEdit_LowerLogHD;
    QPushButton *pushButton_SelectOutputDir;
    QLineEdit *lineEdit_UpperLogHD;
    QPushButton *pushButton_SelectUpperLogHD;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_OutputDir;
    QPushButton *pushButton_SelectLowerLogHD;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Cancel;

    void setupUi(QDialog *LogIntegratorSettingDialogClass)
    {
        if (LogIntegratorSettingDialogClass->objectName().isEmpty())
            LogIntegratorSettingDialogClass->setObjectName(QString::fromUtf8("LogIntegratorSettingDialogClass"));
        LogIntegratorSettingDialogClass->setWindowModality(Qt::ApplicationModal);
        LogIntegratorSettingDialogClass->resize(371, 161);
        LogIntegratorSettingDialogClass->setModal(true);
        groupBox = new QGroupBox(LogIntegratorSettingDialogClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 351, 111));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 101, 21));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_LowerLogHD = new QLineEdit(groupBox);
        lineEdit_LowerLogHD->setObjectName(QString::fromUtf8("lineEdit_LowerLogHD"));
        lineEdit_LowerLogHD->setGeometry(QRect(120, 50, 171, 21));
        lineEdit_LowerLogHD->setMaxLength(1000);
        pushButton_SelectOutputDir = new QPushButton(groupBox);
        pushButton_SelectOutputDir->setObjectName(QString::fromUtf8("pushButton_SelectOutputDir"));
        pushButton_SelectOutputDir->setGeometry(QRect(300, 80, 40, 23));
        lineEdit_UpperLogHD = new QLineEdit(groupBox);
        lineEdit_UpperLogHD->setObjectName(QString::fromUtf8("lineEdit_UpperLogHD"));
        lineEdit_UpperLogHD->setGeometry(QRect(120, 20, 171, 21));
        lineEdit_UpperLogHD->setMaxLength(1000);
        pushButton_SelectUpperLogHD = new QPushButton(groupBox);
        pushButton_SelectUpperLogHD->setObjectName(QString::fromUtf8("pushButton_SelectUpperLogHD"));
        pushButton_SelectUpperLogHD->setGeometry(QRect(300, 20, 40, 23));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 101, 21));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 80, 101, 21));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_OutputDir = new QLineEdit(groupBox);
        lineEdit_OutputDir->setObjectName(QString::fromUtf8("lineEdit_OutputDir"));
        lineEdit_OutputDir->setGeometry(QRect(120, 80, 171, 21));
        pushButton_SelectLowerLogHD = new QPushButton(groupBox);
        pushButton_SelectLowerLogHD->setObjectName(QString::fromUtf8("pushButton_SelectLowerLogHD"));
        pushButton_SelectLowerLogHD->setGeometry(QRect(300, 50, 40, 23));
        pushButton_OK = new QPushButton(LogIntegratorSettingDialogClass);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(194, 130, 81, 25));
        pushButton_Cancel = new QPushButton(LogIntegratorSettingDialogClass);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(280, 130, 81, 25));
        pushButton_Cancel->setAutoDefault(false);
        QWidget::setTabOrder(lineEdit_UpperLogHD, pushButton_SelectUpperLogHD);
        QWidget::setTabOrder(pushButton_SelectUpperLogHD, lineEdit_LowerLogHD);
        QWidget::setTabOrder(lineEdit_LowerLogHD, pushButton_SelectLowerLogHD);
        QWidget::setTabOrder(pushButton_SelectLowerLogHD, lineEdit_OutputDir);
        QWidget::setTabOrder(lineEdit_OutputDir, pushButton_SelectOutputDir);
        QWidget::setTabOrder(pushButton_SelectOutputDir, pushButton_OK);
        QWidget::setTabOrder(pushButton_OK, pushButton_Cancel);

        retranslateUi(LogIntegratorSettingDialogClass);

        pushButton_OK->setDefault(true);


        QMetaObject::connectSlotsByName(LogIntegratorSettingDialogClass);
    } // setupUi

    void retranslateUi(QDialog *LogIntegratorSettingDialogClass)
    {
        LogIntegratorSettingDialogClass->setWindowTitle(QCoreApplication::translate("LogIntegratorSettingDialogClass", "\350\250\255\345\256\232\343\203\200\343\202\244\343\202\242\343\203\255\343\202\260", nullptr));
        groupBox->setTitle(QCoreApplication::translate("LogIntegratorSettingDialogClass", "\345\205\245\345\207\272\345\212\233\350\250\255\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "\344\270\212\351\235\242\343\203\255\343\202\260\343\201\256\343\201\202\343\202\213HD\357\274\232", nullptr));
        lineEdit_LowerLogHD->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "F:\\", nullptr));
        pushButton_SelectOutputDir->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "\345\217\202\347\205\247", nullptr));
        lineEdit_UpperLogHD->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "E:\\", nullptr));
        pushButton_SelectUpperLogHD->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "\345\217\202\347\205\247", nullptr));
        label_2->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "\344\270\213\351\235\242\343\203\255\343\202\260\343\201\256\343\201\202\343\202\213HD\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "\343\203\255\343\202\260\345\207\272\345\212\233\345\205\210\343\203\225\343\202\251\343\203\253\343\203\200\357\274\232", nullptr));
        lineEdit_OutputDir->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "D:\\", nullptr));
        pushButton_SelectLowerLogHD->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "\345\217\202\347\205\247", nullptr));
        pushButton_OK->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "&OK", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("LogIntegratorSettingDialogClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253(&C)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogIntegratorSettingDialogClass: public Ui_LogIntegratorSettingDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINTEGRATORSETTINGDIALOG_H
