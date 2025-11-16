/********************************************************************************
** Form generated from reading UI file 'ShowConnectionInfoForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWCONNECTIONINFOFORM_H
#define UI_SHOWCONNECTIONINFOFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShowConnectionInfoForm
{
public:
    QFrame *frame;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *lineEditDLLRootFrom;
    QLineEdit *lineEditDLLNameFrom;
    QLineEdit *lineEditUniqueNameFrom;
    QLabel *label_7;
    QLineEdit *lineEditConnectionFrom;
    QLabel *label_9;
    QFrame *frame_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEditDLLRootTo;
    QLineEdit *lineEditDLLNameTo;
    QLineEdit *lineEditUniqueNameTo;
    QLabel *label_8;
    QLineEdit *lineEditConnectionTo;
    QLabel *label_10;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonDelete;

    void setupUi(QDialog *ShowConnectionInfoForm)
    {
        if (ShowConnectionInfoForm->objectName().isEmpty())
            ShowConnectionInfoForm->setObjectName("ShowConnectionInfoForm");
        ShowConnectionInfoForm->resize(335, 343);
        frame = new QFrame(ShowConnectionInfoForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 311, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 81, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 81, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 311, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        lineEditDLLRootFrom = new QLineEdit(frame);
        lineEditDLLRootFrom->setObjectName("lineEditDLLRootFrom");
        lineEditDLLRootFrom->setGeometry(QRect(90, 30, 211, 20));
        QPalette palette;
        QBrush brush(QColor(85, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditDLLRootFrom->setPalette(palette);
        lineEditDLLRootFrom->setReadOnly(true);
        lineEditDLLNameFrom = new QLineEdit(frame);
        lineEditDLLNameFrom->setObjectName("lineEditDLLNameFrom");
        lineEditDLLNameFrom->setGeometry(QRect(90, 50, 211, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditDLLNameFrom->setPalette(palette1);
        lineEditDLLNameFrom->setReadOnly(true);
        lineEditUniqueNameFrom = new QLineEdit(frame);
        lineEditUniqueNameFrom->setObjectName("lineEditUniqueNameFrom");
        lineEditUniqueNameFrom->setGeometry(QRect(90, 70, 211, 20));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditUniqueNameFrom->setPalette(palette2);
        lineEditUniqueNameFrom->setReadOnly(true);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 70, 81, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        lineEditConnectionFrom = new QLineEdit(frame);
        lineEditConnectionFrom->setObjectName("lineEditConnectionFrom");
        lineEditConnectionFrom->setGeometry(QRect(90, 100, 211, 20));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditConnectionFrom->setPalette(palette3);
        lineEditConnectionFrom->setReadOnly(true);
        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 100, 81, 21));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(ShowConnectionInfoForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 150, 311, 131));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 50, 81, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 30, 81, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 311, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        lineEditDLLRootTo = new QLineEdit(frame_2);
        lineEditDLLRootTo->setObjectName("lineEditDLLRootTo");
        lineEditDLLRootTo->setGeometry(QRect(90, 30, 211, 20));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditDLLRootTo->setPalette(palette4);
        lineEditDLLRootTo->setReadOnly(true);
        lineEditDLLNameTo = new QLineEdit(frame_2);
        lineEditDLLNameTo->setObjectName("lineEditDLLNameTo");
        lineEditDLLNameTo->setGeometry(QRect(90, 50, 211, 20));
        QPalette palette5;
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditDLLNameTo->setPalette(palette5);
        lineEditDLLNameTo->setReadOnly(true);
        lineEditUniqueNameTo = new QLineEdit(frame_2);
        lineEditUniqueNameTo->setObjectName("lineEditUniqueNameTo");
        lineEditUniqueNameTo->setGeometry(QRect(90, 70, 211, 20));
        QPalette palette6;
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditUniqueNameTo->setPalette(palette6);
        lineEditUniqueNameTo->setReadOnly(true);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 70, 81, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);
        lineEditConnectionTo = new QLineEdit(frame_2);
        lineEditConnectionTo->setObjectName("lineEditConnectionTo");
        lineEditConnectionTo->setGeometry(QRect(90, 100, 211, 20));
        QPalette palette7;
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditConnectionTo->setPalette(palette7);
        lineEditConnectionTo->setReadOnly(true);
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 100, 81, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(ShowConnectionInfoForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(160, 290, 161, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        pushButtonDelete = new QPushButton(ShowConnectionInfoForm);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(10, 290, 101, 41));

        retranslateUi(ShowConnectionInfoForm);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(ShowConnectionInfoForm);
    } // setupUi

    void retranslateUi(QDialog *ShowConnectionInfoForm)
    {
        ShowConnectionInfoForm->setWindowTitle(QCoreApplication::translate("ShowConnectionInfoForm", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("ShowConnectionInfoForm", "DLL Name", nullptr));
        label->setText(QCoreApplication::translate("ShowConnectionInfoForm", "DLL Root", nullptr));
        label_3->setText(QCoreApplication::translate("ShowConnectionInfoForm", "From", nullptr));
        label_7->setText(QCoreApplication::translate("ShowConnectionInfoForm", "Unique Name", nullptr));
        label_9->setText(QCoreApplication::translate("ShowConnectionInfoForm", "Connection", nullptr));
        label_4->setText(QCoreApplication::translate("ShowConnectionInfoForm", "DLL Name", nullptr));
        label_5->setText(QCoreApplication::translate("ShowConnectionInfoForm", "DLL Root", nullptr));
        label_6->setText(QCoreApplication::translate("ShowConnectionInfoForm", "To", nullptr));
        label_8->setText(QCoreApplication::translate("ShowConnectionInfoForm", "Unique Name", nullptr));
        label_10->setText(QCoreApplication::translate("ShowConnectionInfoForm", "Connection", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("ShowConnectionInfoForm", "OK", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("ShowConnectionInfoForm", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowConnectionInfoForm: public Ui_ShowConnectionInfoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCONNECTIONINFOFORM_H
