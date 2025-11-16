/********************************************************************************
** Form generated from reading UI file 'AddAreaDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDAREADIALOG_H
#define UI_ADDAREADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddAreaDialog
{
public:
    QFrame *framePicked;
    QLabel *label_36;
    QPushButton *pushButtonAddPickupColor;
    QFrame *framePickupColor;
    QFrame *frame;
    QFrame *frameColor;
    QLabel *label_37;
    QLabel *label_38;
    QLabel *label_39;
    QSpinBox *spinBoxR;
    QSpinBox *spinBoxG;
    QSpinBox *spinBoxB;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *AddAreaDialog)
    {
        if (AddAreaDialog->objectName().isEmpty())
            AddAreaDialog->setObjectName("AddAreaDialog");
        AddAreaDialog->resize(341, 246);
        framePicked = new QFrame(AddAreaDialog);
        framePicked->setObjectName("framePicked");
        framePicked->setGeometry(QRect(170, 10, 161, 111));
        framePicked->setFrameShape(QFrame::StyledPanel);
        framePicked->setFrameShadow(QFrame::Sunken);
        label_36 = new QLabel(framePicked);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(0, 0, 161, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonAddPickupColor = new QPushButton(framePicked);
        pushButtonAddPickupColor->setObjectName("pushButtonAddPickupColor");
        pushButtonAddPickupColor->setGeometry(QRect(10, 50, 75, 23));
        framePickupColor = new QFrame(framePicked);
        framePickupColor->setObjectName("framePickupColor");
        framePickupColor->setGeometry(QRect(90, 30, 61, 71));
        framePickupColor->setFrameShape(QFrame::NoFrame);
        framePickupColor->setFrameShadow(QFrame::Plain);
        frame = new QFrame(AddAreaDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 141, 111));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frameColor = new QFrame(frame);
        frameColor->setObjectName("frameColor");
        frameColor->setGeometry(QRect(10, 10, 121, 91));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::NoRole, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::NoRole, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::NoRole, brush);
        frameColor->setPalette(palette);
        frameColor->setFrameShape(QFrame::NoFrame);
        frameColor->setFrameShadow(QFrame::Plain);
        label_37 = new QLabel(AddAreaDialog);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(10, 130, 41, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_38 = new QLabel(AddAreaDialog);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(60, 130, 41, 21));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setFrameShadow(QFrame::Sunken);
        label_38->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_39 = new QLabel(AddAreaDialog);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(110, 130, 41, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxR = new QSpinBox(AddAreaDialog);
        spinBoxR->setObjectName("spinBoxR");
        spinBoxR->setGeometry(QRect(10, 150, 46, 22));
        spinBoxR->setMaximum(255);
        spinBoxG = new QSpinBox(AddAreaDialog);
        spinBoxG->setObjectName("spinBoxG");
        spinBoxG->setGeometry(QRect(60, 150, 41, 22));
        spinBoxG->setMaximum(255);
        spinBoxB = new QSpinBox(AddAreaDialog);
        spinBoxB->setObjectName("spinBoxB");
        spinBoxB->setGeometry(QRect(110, 150, 41, 22));
        spinBoxB->setMaximum(255);
        pushButtonOk = new QPushButton(AddAreaDialog);
        pushButtonOk->setObjectName("pushButtonOk");
        pushButtonOk->setGeometry(QRect(50, 190, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOk->setIcon(icon);
        pushButtonCancel = new QPushButton(AddAreaDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(210, 190, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);

        retranslateUi(AddAreaDialog);

        pushButtonOk->setDefault(true);


        QMetaObject::connectSlotsByName(AddAreaDialog);
    } // setupUi

    void retranslateUi(QDialog *AddAreaDialog)
    {
        AddAreaDialog->setWindowTitle(QCoreApplication::translate("AddAreaDialog", "Add Area", nullptr));
        label_36->setText(QCoreApplication::translate("AddAreaDialog", "\343\203\224\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\211\262", nullptr));
        pushButtonAddPickupColor->setText(QCoreApplication::translate("AddAreaDialog", "<- Set", nullptr));
        label_37->setText(QCoreApplication::translate("AddAreaDialog", "R", nullptr));
        label_38->setText(QCoreApplication::translate("AddAreaDialog", "G", nullptr));
        label_39->setText(QCoreApplication::translate("AddAreaDialog", "B", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("AddAreaDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddAreaDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddAreaDialog: public Ui_AddAreaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDAREADIALOG_H
