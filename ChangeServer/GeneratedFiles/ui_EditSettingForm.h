/********************************************************************************
** Form generated from reading UI file 'EditSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSETTINGFORM_H
#define UI_EDITSETTINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_EditSettingFormClass
{
public:
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEditRemark;
    QLineEdit *lineEditServerName;
    QPushButton *pushButtonCreateNew;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonCancel;
    QGroupBox *groupBox;
    QRadioButton *radioButtonFromBAT;
    QRadioButton *radioButton_2;
    QLineEdit *lineEditExeFilePath;
    QLabel *label_3;
    QPushButton *pushButtonFile;
    QPlainTextEdit *textEditCommandLine;
    QLabel *label_4;

    void setupUi(QDialog *EditSettingFormClass)
    {
        if (EditSettingFormClass->objectName().isEmpty())
            EditSettingFormClass->setObjectName("EditSettingFormClass");
        EditSettingFormClass->resize(357, 608);
        label_2 = new QLabel(EditSettingFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 10, 191, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(EditSettingFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 131, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditRemark = new QLineEdit(EditSettingFormClass);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(140, 30, 191, 20));
        lineEditServerName = new QLineEdit(EditSettingFormClass);
        lineEditServerName->setObjectName("lineEditServerName");
        lineEditServerName->setGeometry(QRect(10, 30, 131, 20));
        pushButtonCreateNew = new QPushButton(EditSettingFormClass);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(20, 530, 101, 31));
        pushButtonUpdate = new QPushButton(EditSettingFormClass);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(130, 530, 101, 31));
        pushButtonDelete = new QPushButton(EditSettingFormClass);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(240, 530, 101, 31));
        pushButtonCancel = new QPushButton(EditSettingFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(240, 570, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        groupBox = new QGroupBox(EditSettingFormClass);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 110, 321, 401));
        radioButtonFromBAT = new QRadioButton(groupBox);
        radioButtonFromBAT->setObjectName("radioButtonFromBAT");
        radioButtonFromBAT->setGeometry(QRect(10, 20, 221, 18));
        radioButtonFromBAT->setChecked(true);
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(10, 100, 281, 18));
        lineEditExeFilePath = new QLineEdit(groupBox);
        lineEditExeFilePath->setObjectName("lineEditExeFilePath");
        lineEditExeFilePath->setGeometry(QRect(30, 60, 261, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 40, 261, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonFile = new QPushButton(groupBox);
        pushButtonFile->setObjectName("pushButtonFile");
        pushButtonFile->setGeometry(QRect(290, 60, 21, 23));
        textEditCommandLine = new QPlainTextEdit(groupBox);
        textEditCommandLine->setObjectName("textEditCommandLine");
        textEditCommandLine->setGeometry(QRect(30, 120, 281, 271));
        label_4 = new QLabel(EditSettingFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 110, 16, 41));
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(EditSettingFormClass);

        QMetaObject::connectSlotsByName(EditSettingFormClass);
    } // setupUi

    void retranslateUi(QDialog *EditSettingFormClass)
    {
        EditSettingFormClass->setWindowTitle(QCoreApplication::translate("EditSettingFormClass", "EditSettingForm", nullptr));
        label_2->setText(QCoreApplication::translate("EditSettingFormClass", "Remark", nullptr));
        label->setText(QCoreApplication::translate("EditSettingFormClass", "Server Name", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("EditSettingFormClass", "Create new", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("EditSettingFormClass", "Update", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EditSettingFormClass", "Delete", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditSettingFormClass", "Cancel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("EditSettingFormClass", "GroupBox", nullptr));
        radioButtonFromBAT->setText(QCoreApplication::translate("EditSettingFormClass", "From outside BAT/EXE file", nullptr));
        radioButton_2->setText(QCoreApplication::translate("EditSettingFormClass", "Direct command line", nullptr));
        label_3->setText(QCoreApplication::translate("EditSettingFormClass", "Execute with param", nullptr));
        pushButtonFile->setText(QCoreApplication::translate("EditSettingFormClass", "...", nullptr));
        label_4->setText(QCoreApplication::translate("EditSettingFormClass", "\351\201\270\n"
"\346\212\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditSettingFormClass: public Ui_EditSettingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSETTINGFORM_H
