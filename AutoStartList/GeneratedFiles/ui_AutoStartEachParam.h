/********************************************************************************
** Form generated from reading UI file 'AutoStartEachParam.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSTARTEACHPARAM_H
#define UI_AUTOSTARTEACHPARAM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AutoStartEachParamClass
{
public:
    QLineEdit *lineEditExeFilePath;
    QLineEdit *lineEditWorkingPath;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonFile;
    QComboBox *comboBoxLocation;
    QLabel *label_3;
    QLineEdit *lineEditParameters;
    QLabel *label_4;
    QSpinBox *spinBoxBootingWaitTime;
    QLabel *label_5;

    void setupUi(QDialog *AutoStartEachParamClass)
    {
        if (AutoStartEachParamClass->objectName().isEmpty())
            AutoStartEachParamClass->setObjectName("AutoStartEachParamClass");
        AutoStartEachParamClass->resize(400, 338);
        lineEditExeFilePath = new QLineEdit(AutoStartEachParamClass);
        lineEditExeFilePath->setObjectName("lineEditExeFilePath");
        lineEditExeFilePath->setGeometry(QRect(10, 30, 351, 20));
        lineEditWorkingPath = new QLineEdit(AutoStartEachParamClass);
        lineEditWorkingPath->setObjectName("lineEditWorkingPath");
        lineEditWorkingPath->setGeometry(QRect(10, 140, 371, 20));
        label = new QLabel(AutoStartEachParamClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 371, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(AutoStartEachParamClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 120, 371, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonOK = new QPushButton(AutoStartEachParamClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(74, 290, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/AutoStartList/Qtres/flash_swf_128.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonCancel = new QPushButton(AutoStartEachParamClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(240, 290, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/AutoStartList/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        pushButtonFile = new QPushButton(AutoStartEachParamClass);
        pushButtonFile->setObjectName("pushButtonFile");
        pushButtonFile->setGeometry(QRect(360, 30, 21, 23));
        comboBoxLocation = new QComboBox(AutoStartEachParamClass);
        comboBoxLocation->addItem(QString());
        comboBoxLocation->addItem(QString());
        comboBoxLocation->addItem(QString());
        comboBoxLocation->addItem(QString());
        comboBoxLocation->addItem(QString());
        comboBoxLocation->addItem(QString());
        comboBoxLocation->addItem(QString());
        comboBoxLocation->addItem(QString());
        comboBoxLocation->addItem(QString());
        comboBoxLocation->addItem(QString());
        comboBoxLocation->setObjectName("comboBoxLocation");
        comboBoxLocation->setGeometry(QRect(10, 180, 201, 22));
        label_3 = new QLabel(AutoStartEachParamClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 60, 371, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditParameters = new QLineEdit(AutoStartEachParamClass);
        lineEditParameters->setObjectName("lineEditParameters");
        lineEditParameters->setGeometry(QRect(10, 80, 371, 20));
        label_4 = new QLabel(AutoStartEachParamClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 210, 371, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxBootingWaitTime = new QSpinBox(AutoStartEachParamClass);
        spinBoxBootingWaitTime->setObjectName("spinBoxBootingWaitTime");
        spinBoxBootingWaitTime->setGeometry(QRect(10, 230, 81, 22));
        spinBoxBootingWaitTime->setMaximum(99999999);
        label_5 = new QLabel(AutoStartEachParamClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 230, 31, 20));

        retranslateUi(AutoStartEachParamClass);

        QMetaObject::connectSlotsByName(AutoStartEachParamClass);
    } // setupUi

    void retranslateUi(QDialog *AutoStartEachParamClass)
    {
        AutoStartEachParamClass->setWindowTitle(QCoreApplication::translate("AutoStartEachParamClass", "AutoStartEachParam", nullptr));
        label->setText(QCoreApplication::translate("AutoStartEachParamClass", "Path & exe file name", nullptr));
        label_2->setText(QCoreApplication::translate("AutoStartEachParamClass", "Working folder", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("AutoStartEachParamClass", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AutoStartEachParamClass", "Cancel", nullptr));
        pushButtonFile->setText(QCoreApplication::translate("AutoStartEachParamClass", "...", nullptr));
        comboBoxLocation->setItemText(0, QCoreApplication::translate("AutoStartEachParamClass", "Single", nullptr));
        comboBoxLocation->setItemText(1, QCoreApplication::translate("AutoStartEachParamClass", "Left", nullptr));
        comboBoxLocation->setItemText(2, QCoreApplication::translate("AutoStartEachParamClass", "Right", nullptr));
        comboBoxLocation->setItemText(3, QCoreApplication::translate("AutoStartEachParamClass", "Top", nullptr));
        comboBoxLocation->setItemText(4, QCoreApplication::translate("AutoStartEachParamClass", "Bottom", nullptr));
        comboBoxLocation->setItemText(5, QCoreApplication::translate("AutoStartEachParamClass", "Client", nullptr));
        comboBoxLocation->setItemText(6, QCoreApplication::translate("AutoStartEachParamClass", "LeftClient", nullptr));
        comboBoxLocation->setItemText(7, QCoreApplication::translate("AutoStartEachParamClass", "RightClient", nullptr));
        comboBoxLocation->setItemText(8, QCoreApplication::translate("AutoStartEachParamClass", "TopClient", nullptr));
        comboBoxLocation->setItemText(9, QCoreApplication::translate("AutoStartEachParamClass", "BottomClient", nullptr));

        label_3->setText(QCoreApplication::translate("AutoStartEachParamClass", "Parameter", nullptr));
        label_4->setText(QCoreApplication::translate("AutoStartEachParamClass", "Booting confirming time", nullptr));
        label_5->setText(QCoreApplication::translate("AutoStartEachParamClass", "ms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoStartEachParamClass: public Ui_AutoStartEachParamClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSTARTEACHPARAM_H
