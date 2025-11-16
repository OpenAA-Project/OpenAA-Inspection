/********************************************************************************
** Form generated from reading UI file 'SHowFlowGraphDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWFLOWGRAPHDIALOG_H
#define UI_SHOWFLOWGRAPHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_SHowFlowGraphDialog
{
public:
    QFrame *frameH;
    QFrame *frameS;
    QFrame *frameV;
    QFrame *frameE;
    QFrame *frameHeader;
    QLabel *label_Flow;
    QLabel *label_Target;
    QLabel *label_Thresh;
    QLabel *labelH;
    QLabel *labelS;
    QLabel *labelV;
    QLabel *labelE;

    void setupUi(QDialog *SHowFlowGraphDialog)
    {
        if (SHowFlowGraphDialog->objectName().isEmpty())
            SHowFlowGraphDialog->setObjectName("SHowFlowGraphDialog");
        SHowFlowGraphDialog->resize(1069, 558);
        frameH = new QFrame(SHowFlowGraphDialog);
        frameH->setObjectName("frameH");
        frameH->setGeometry(QRect(30, 70, 1071, 141));
        frameH->setFrameShape(QFrame::Panel);
        frameH->setFrameShadow(QFrame::Sunken);
        frameS = new QFrame(SHowFlowGraphDialog);
        frameS->setObjectName("frameS");
        frameS->setGeometry(QRect(50, 220, 1071, 141));
        frameS->setFrameShape(QFrame::Panel);
        frameS->setFrameShadow(QFrame::Sunken);
        frameV = new QFrame(SHowFlowGraphDialog);
        frameV->setObjectName("frameV");
        frameV->setGeometry(QRect(50, 350, 1071, 141));
        frameV->setFrameShape(QFrame::Panel);
        frameV->setFrameShadow(QFrame::Sunken);
        frameE = new QFrame(SHowFlowGraphDialog);
        frameE->setObjectName("frameE");
        frameE->setGeometry(QRect(40, 490, 1071, 141));
        frameE->setFrameShape(QFrame::Panel);
        frameE->setFrameShadow(QFrame::Sunken);
        frameHeader = new QFrame(SHowFlowGraphDialog);
        frameHeader->setObjectName("frameHeader");
        frameHeader->setGeometry(QRect(0, 0, 1071, 41));
        frameHeader->setFrameShape(QFrame::StyledPanel);
        frameHeader->setFrameShadow(QFrame::Raised);
        label_Flow = new QLabel(frameHeader);
        label_Flow->setObjectName("label_Flow");
        label_Flow->setGeometry(QRect(20, 10, 101, 21));
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        label_Flow->setPalette(palette);
        label_Flow->setAutoFillBackground(true);
        label_Flow->setAlignment(Qt::AlignCenter);
        label_Target = new QLabel(frameHeader);
        label_Target->setObjectName("label_Target");
        label_Target->setGeometry(QRect(130, 10, 101, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        QBrush brush2(QColor(0, 170, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush2);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        label_Target->setPalette(palette1);
        label_Target->setAutoFillBackground(true);
        label_Target->setAlignment(Qt::AlignCenter);
        label_Thresh = new QLabel(frameHeader);
        label_Thresh->setObjectName("label_Thresh");
        label_Thresh->setGeometry(QRect(240, 10, 101, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        QBrush brush3(QColor(255, 0, 0, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush3);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush3);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush3);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush3);
        label_Thresh->setPalette(palette2);
        label_Thresh->setAutoFillBackground(true);
        label_Thresh->setAlignment(Qt::AlignCenter);
        labelH = new QLabel(SHowFlowGraphDialog);
        labelH->setObjectName("labelH");
        labelH->setGeometry(QRect(-10, 70, 41, 141));
        QFont font;
        font.setPointSize(12);
        labelH->setFont(font);
        labelH->setAlignment(Qt::AlignCenter);
        labelS = new QLabel(SHowFlowGraphDialog);
        labelS->setObjectName("labelS");
        labelS->setGeometry(QRect(0, 220, 21, 131));
        labelS->setFont(font);
        labelS->setAlignment(Qt::AlignCenter);
        labelV = new QLabel(SHowFlowGraphDialog);
        labelV->setObjectName("labelV");
        labelV->setGeometry(QRect(0, 360, 41, 121));
        labelV->setFont(font);
        labelV->setAlignment(Qt::AlignCenter);
        labelE = new QLabel(SHowFlowGraphDialog);
        labelE->setObjectName("labelE");
        labelE->setGeometry(QRect(0, 490, 41, 71));
        labelE->setFont(font);
        labelE->setAlignment(Qt::AlignCenter);

        retranslateUi(SHowFlowGraphDialog);

        QMetaObject::connectSlotsByName(SHowFlowGraphDialog);
    } // setupUi

    void retranslateUi(QDialog *SHowFlowGraphDialog)
    {
        SHowFlowGraphDialog->setWindowTitle(QCoreApplication::translate("SHowFlowGraphDialog", "\346\265\201\345\213\225\343\202\265\343\203\263\343\203\227\343\203\253\347\265\261\350\250\210\343\202\260\343\203\251\343\203\225", nullptr));
        label_Flow->setText(QCoreApplication::translate("SHowFlowGraphDialog", "\346\265\201\345\213\225", nullptr));
        label_Target->setText(QCoreApplication::translate("SHowFlowGraphDialog", "\347\217\276\345\234\250\346\244\234\346\237\273", nullptr));
        label_Thresh->setText(QCoreApplication::translate("SHowFlowGraphDialog", "\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        labelH->setText(QCoreApplication::translate("SHowFlowGraphDialog", "H", nullptr));
        labelS->setText(QCoreApplication::translate("SHowFlowGraphDialog", "S", nullptr));
        labelV->setText(QCoreApplication::translate("SHowFlowGraphDialog", "V", nullptr));
        labelE->setText(QCoreApplication::translate("SHowFlowGraphDialog", "\316\224E", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SHowFlowGraphDialog: public Ui_SHowFlowGraphDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWFLOWGRAPHDIALOG_H
