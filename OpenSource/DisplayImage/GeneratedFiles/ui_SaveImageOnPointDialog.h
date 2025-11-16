/********************************************************************************
** Form generated from reading UI file 'SaveImageOnPointDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEIMAGEONPOINTDIALOG_H
#define UI_SAVEIMAGEONPOINTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SaveImageOnPointDialog
{
public:
    QLabel *label_6;
    QGroupBox *groupBox_2;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *comboBoxXCount;
    QComboBox *comboBoxYCount;
    QGroupBox *groupBox;
    QSpinBox *spinBoxXDot;
    QSpinBox *spinBoxYDot;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QPushButton *pushButtonOK;
    QComboBox *comboBoxFormat;

    void setupUi(QDialog *SaveImageOnPointDialog)
    {
        if (SaveImageOnPointDialog->objectName().isEmpty())
            SaveImageOnPointDialog->setObjectName("SaveImageOnPointDialog");
        SaveImageOnPointDialog->resize(400, 206);
        label_6 = new QLabel(SaveImageOnPointDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(230, 90, 101, 16));
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBox_2 = new QGroupBox(SaveImageOnPointDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(190, 10, 191, 80));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 20, 101, 16));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 50, 101, 16));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBoxXCount = new QComboBox(groupBox_2);
        comboBoxXCount->addItem(QString());
        comboBoxXCount->addItem(QString());
        comboBoxXCount->addItem(QString());
        comboBoxXCount->addItem(QString());
        comboBoxXCount->addItem(QString());
        comboBoxXCount->setObjectName("comboBoxXCount");
        comboBoxXCount->setGeometry(QRect(113, 20, 51, 22));
        comboBoxYCount = new QComboBox(groupBox_2);
        comboBoxYCount->addItem(QString());
        comboBoxYCount->addItem(QString());
        comboBoxYCount->addItem(QString());
        comboBoxYCount->addItem(QString());
        comboBoxYCount->addItem(QString());
        comboBoxYCount->setObjectName("comboBoxYCount");
        comboBoxYCount->setGeometry(QRect(113, 50, 51, 22));
        groupBox = new QGroupBox(SaveImageOnPointDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 161, 80));
        spinBoxXDot = new QSpinBox(groupBox);
        spinBoxXDot->setObjectName("spinBoxXDot");
        spinBoxXDot->setGeometry(QRect(80, 20, 71, 22));
        spinBoxXDot->setMaximum(99999999);
        spinBoxYDot = new QSpinBox(groupBox);
        spinBoxYDot->setObjectName("spinBoxYDot");
        spinBoxYDot->setGeometry(QRect(80, 50, 71, 22));
        spinBoxYDot->setMaximum(99999999);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 71, 16));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 50, 71, 16));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton_2 = new QPushButton(SaveImageOnPointDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(230, 150, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_2->setIcon(icon);
        pushButtonOK = new QPushButton(SaveImageOnPointDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(50, 150, 131, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        comboBoxFormat = new QComboBox(SaveImageOnPointDialog);
        comboBoxFormat->addItem(QString());
        comboBoxFormat->addItem(QString());
        comboBoxFormat->addItem(QString());
        comboBoxFormat->setObjectName("comboBoxFormat");
        comboBoxFormat->setGeometry(QRect(240, 110, 111, 22));

        retranslateUi(SaveImageOnPointDialog);

        QMetaObject::connectSlotsByName(SaveImageOnPointDialog);
    } // setupUi

    void retranslateUi(QDialog *SaveImageOnPointDialog)
    {
        SaveImageOnPointDialog->setWindowTitle(QCoreApplication::translate("SaveImageOnPointDialog", "Dialog", nullptr));
        label_6->setText(QCoreApplication::translate("SaveImageOnPointDialog", "\344\277\235\345\255\230\347\250\256\351\241\236", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SaveImageOnPointDialog", "\344\270\200\345\272\246\343\201\253\344\277\235\345\255\230\343\201\231\343\202\213\347\224\273\345\203\217\343\201\256\346\236\232\346\225\260", nullptr));
        label_4->setText(QCoreApplication::translate("SaveImageOnPointDialog", "\346\250\252\343\201\256\347\224\273\345\203\217\346\225\260", nullptr));
        label_5->setText(QCoreApplication::translate("SaveImageOnPointDialog", "\347\270\246\343\201\256\347\224\273\345\203\217\346\225\260", nullptr));
        comboBoxXCount->setItemText(0, QCoreApplication::translate("SaveImageOnPointDialog", "1", nullptr));
        comboBoxXCount->setItemText(1, QCoreApplication::translate("SaveImageOnPointDialog", "3", nullptr));
        comboBoxXCount->setItemText(2, QCoreApplication::translate("SaveImageOnPointDialog", "5", nullptr));
        comboBoxXCount->setItemText(3, QCoreApplication::translate("SaveImageOnPointDialog", "7", nullptr));
        comboBoxXCount->setItemText(4, QCoreApplication::translate("SaveImageOnPointDialog", "9", nullptr));

        comboBoxYCount->setItemText(0, QCoreApplication::translate("SaveImageOnPointDialog", "1", nullptr));
        comboBoxYCount->setItemText(1, QCoreApplication::translate("SaveImageOnPointDialog", "3", nullptr));
        comboBoxYCount->setItemText(2, QCoreApplication::translate("SaveImageOnPointDialog", "5", nullptr));
        comboBoxYCount->setItemText(3, QCoreApplication::translate("SaveImageOnPointDialog", "7", nullptr));
        comboBoxYCount->setItemText(4, QCoreApplication::translate("SaveImageOnPointDialog", "9", nullptr));

        groupBox->setTitle(QCoreApplication::translate("SaveImageOnPointDialog", "\357\274\221\343\201\244\343\201\256\347\224\273\345\203\217\343\201\256\343\202\265\343\202\244\343\202\272", nullptr));
        label_2->setText(QCoreApplication::translate("SaveImageOnPointDialog", "\346\250\252\343\201\256\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("SaveImageOnPointDialog", "\347\270\246\343\201\256\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SaveImageOnPointDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SaveImageOnPointDialog", "\350\250\255\345\256\232\343\203\273\344\277\235\345\255\230", nullptr));
        comboBoxFormat->setItemText(0, QCoreApplication::translate("SaveImageOnPointDialog", "Bitmap(Bmp)", nullptr));
        comboBoxFormat->setItemText(1, QCoreApplication::translate("SaveImageOnPointDialog", "JPEG(Jpg)", nullptr));
        comboBoxFormat->setItemText(2, QCoreApplication::translate("SaveImageOnPointDialog", "PNG(Png)", nullptr));

    } // retranslateUi

};

namespace Ui {
    class SaveImageOnPointDialog: public Ui_SaveImageOnPointDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEIMAGEONPOINTDIALOG_H
