/********************************************************************************
** Form generated from reading UI file 'Haspviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HASPVIEWER_H
#define UI_HASPVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HaspViewerClass
{
public:
    QPushButton *pbEND;
    QLabel *lbHaspViewer;
    QFrame *frame;
    QLabel *lbID;
    QLabel *lb2_2;
    QLabel *lb3;
    QLabel *lb4;
    QLabel *lbPlayerDate;
    QLabel *lbEditorDate;
    QLabel *lbRepairDate;
    QLabel *lbPlayerNO;
    QLabel *lbEditorNO;
    QLabel *lbRepairNO;
    QLabel *lbPlayerOK;
    QLabel *lbEditorOK;
    QLabel *lbRepairOK;
    QPushButton *pbUpdate;
    QLabel *lbEnd;
    QLabel *lbType;
    QLabel *lbID_2;

    void setupUi(QWidget *HaspViewerClass)
    {
        if (HaspViewerClass->objectName().isEmpty())
            HaspViewerClass->setObjectName("HaspViewerClass");
        HaspViewerClass->resize(760, 479);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        HaspViewerClass->setPalette(palette);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        HaspViewerClass->setFont(font);
        HaspViewerClass->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
""));
        pbEND = new QPushButton(HaspViewerClass);
        pbEND->setObjectName("pbEND");
        pbEND->setGeometry(QRect(680, 435, 61, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Georgia")});
        font1.setPointSize(11);
        pbEND->setFont(font1);
        pbEND->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 15px;\n"
"     border-color: rgb(70, 70, 70);\n"
"     background-color: rgb(20, 20, 20);\n"
"	 \n"
"	color: rgb(240, 240, 240);\n"
"}\n"
"QPushButton:pressed {     \n"
"     \n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        lbHaspViewer = new QLabel(HaspViewerClass);
        lbHaspViewer->setObjectName("lbHaspViewer");
        lbHaspViewer->setGeometry(QRect(180, 425, 401, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Georgia")});
        font2.setPointSize(28);
        lbHaspViewer->setFont(font2);
        lbHaspViewer->setStyleSheet(QString::fromUtf8("color: rgb(200, 200, 200);"));
        lbHaspViewer->setAlignment(Qt::AlignCenter);
        frame = new QFrame(HaspViewerClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(90, 40, 621, 381));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        lbID = new QLabel(frame);
        lbID->setObjectName("lbID");
        lbID->setGeometry(QRect(150, 40, 301, 51));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(26);
        lbID->setFont(font3);
        lbID->setAlignment(Qt::AlignCenter);
        lb2_2 = new QLabel(frame);
        lb2_2->setObjectName("lb2_2");
        lb2_2->setGeometry(QRect(10, 150, 181, 51));
        lb2_2->setFont(font3);
        lb2_2->setAlignment(Qt::AlignCenter);
        lb3 = new QLabel(frame);
        lb3->setObjectName("lb3");
        lb3->setGeometry(QRect(210, 150, 181, 51));
        lb3->setFont(font3);
        lb3->setAlignment(Qt::AlignCenter);
        lb4 = new QLabel(frame);
        lb4->setObjectName("lb4");
        lb4->setGeometry(QRect(420, 150, 181, 51));
        lb4->setFont(font3);
        lb4->setAlignment(Qt::AlignCenter);
        lbPlayerDate = new QLabel(frame);
        lbPlayerDate->setObjectName("lbPlayerDate");
        lbPlayerDate->setGeometry(QRect(10, 290, 191, 51));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial")});
        font4.setPointSize(23);
        lbPlayerDate->setFont(font4);
        lbPlayerDate->setAlignment(Qt::AlignCenter);
        lbEditorDate = new QLabel(frame);
        lbEditorDate->setObjectName("lbEditorDate");
        lbEditorDate->setGeometry(QRect(220, 290, 191, 51));
        lbEditorDate->setFont(font4);
        lbEditorDate->setAlignment(Qt::AlignCenter);
        lbRepairDate = new QLabel(frame);
        lbRepairDate->setObjectName("lbRepairDate");
        lbRepairDate->setGeometry(QRect(420, 290, 191, 51));
        lbRepairDate->setFont(font4);
        lbRepairDate->setAlignment(Qt::AlignCenter);
        lbPlayerNO = new QLabel(frame);
        lbPlayerNO->setObjectName("lbPlayerNO");
        lbPlayerNO->setGeometry(QRect(70, 210, 61, 41));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Arial")});
        font5.setPointSize(50);
        lbPlayerNO->setFont(font5);
        lbPlayerNO->setAlignment(Qt::AlignCenter);
        lbEditorNO = new QLabel(frame);
        lbEditorNO->setObjectName("lbEditorNO");
        lbEditorNO->setGeometry(QRect(270, 210, 61, 41));
        lbEditorNO->setFont(font5);
        lbEditorNO->setAlignment(Qt::AlignCenter);
        lbRepairNO = new QLabel(frame);
        lbRepairNO->setObjectName("lbRepairNO");
        lbRepairNO->setGeometry(QRect(480, 210, 61, 41));
        lbRepairNO->setFont(font5);
        lbRepairNO->setAlignment(Qt::AlignCenter);
        lbPlayerOK = new QLabel(frame);
        lbPlayerOK->setObjectName("lbPlayerOK");
        lbPlayerOK->setGeometry(QRect(70, 200, 61, 51));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Arial")});
        font6.setPointSize(50);
        font6.setBold(false);
        font6.setItalic(false);
        font6.setUnderline(false);
        font6.setStrikeOut(false);
        lbPlayerOK->setFont(font6);
        lbPlayerOK->setAlignment(Qt::AlignCenter);
        lbEditorOK = new QLabel(frame);
        lbEditorOK->setObjectName("lbEditorOK");
        lbEditorOK->setGeometry(QRect(270, 200, 61, 51));
        lbEditorOK->setFont(font6);
        lbEditorOK->setAlignment(Qt::AlignCenter);
        lbRepairOK = new QLabel(frame);
        lbRepairOK->setObjectName("lbRepairOK");
        lbRepairOK->setGeometry(QRect(480, 200, 61, 51));
        lbRepairOK->setFont(font6);
        lbRepairOK->setAlignment(Qt::AlignCenter);
        lbRepairOK->raise();
        lbEditorOK->raise();
        lbPlayerOK->raise();
        lbID->raise();
        lb2_2->raise();
        lb3->raise();
        lb4->raise();
        lbPlayerDate->raise();
        lbEditorDate->raise();
        lbRepairDate->raise();
        lbPlayerNO->raise();
        lbEditorNO->raise();
        lbRepairNO->raise();
        pbUpdate = new QPushButton(HaspViewerClass);
        pbUpdate->setObjectName("pbUpdate");
        pbUpdate->setGeometry(QRect(20, 435, 61, 31));
        pbUpdate->setFont(font1);
        pbUpdate->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 15px;\n"
"     border-color: rgb(70, 70, 70);\n"
"     background-color: rgb(20, 20, 20);\n"
"	 \n"
"	color: rgb(240, 240, 240);\n"
"}\n"
"QPushButton:pressed {     \n"
"     \n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        lbEnd = new QLabel(HaspViewerClass);
        lbEnd->setObjectName("lbEnd");
        lbEnd->setGeometry(QRect(5, 330, 81, 51));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Georgia")});
        font7.setPointSize(22);
        lbEnd->setFont(font7);
        lbEnd->setStyleSheet(QString::fromUtf8("color: rgb(200, 200, 200);"));
        lbEnd->setAlignment(Qt::AlignCenter);
        lbType = new QLabel(HaspViewerClass);
        lbType->setObjectName("lbType");
        lbType->setGeometry(QRect(5, 185, 81, 51));
        lbType->setFont(font7);
        lbType->setStyleSheet(QString::fromUtf8("color: rgb(200, 200, 200);"));
        lbType->setAlignment(Qt::AlignCenter);
        lbID_2 = new QLabel(HaspViewerClass);
        lbID_2->setObjectName("lbID_2");
        lbID_2->setGeometry(QRect(0, 75, 81, 51));
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Georgia")});
        font8.setPointSize(26);
        lbID_2->setFont(font8);
        lbID_2->setStyleSheet(QString::fromUtf8("color: rgb(200, 200, 200);"));
        lbID_2->setAlignment(Qt::AlignCenter);

        retranslateUi(HaspViewerClass);

        QMetaObject::connectSlotsByName(HaspViewerClass);
    } // setupUi

    void retranslateUi(QWidget *HaspViewerClass)
    {
        HaspViewerClass->setWindowTitle(QCoreApplication::translate("HaspViewerClass", "HaspViewer", nullptr));
        pbEND->setText(QCoreApplication::translate("HaspViewerClass", "END", nullptr));
        lbHaspViewer->setText(QCoreApplication::translate("HaspViewerClass", "HaspViewer", nullptr));
        lbID->setText(QString());
        lb2_2->setText(QCoreApplication::translate("HaspViewerClass", "Player", nullptr));
        lb3->setText(QCoreApplication::translate("HaspViewerClass", "Editor", nullptr));
        lb4->setText(QCoreApplication::translate("HaspViewerClass", "Repair", nullptr));
        lbPlayerDate->setText(QString());
        lbEditorDate->setText(QString());
        lbRepairDate->setText(QString());
        lbPlayerNO->setText(QCoreApplication::translate("HaspViewerClass", "\303\227", nullptr));
        lbEditorNO->setText(QCoreApplication::translate("HaspViewerClass", "\303\227", nullptr));
        lbRepairNO->setText(QCoreApplication::translate("HaspViewerClass", "\303\227", nullptr));
        lbPlayerOK->setText(QCoreApplication::translate("HaspViewerClass", "\342\227\213", nullptr));
        lbEditorOK->setText(QCoreApplication::translate("HaspViewerClass", "\342\227\213", nullptr));
        lbRepairOK->setText(QCoreApplication::translate("HaspViewerClass", "\342\227\213", nullptr));
        pbUpdate->setText(QCoreApplication::translate("HaspViewerClass", "Update", nullptr));
        lbEnd->setText(QCoreApplication::translate("HaspViewerClass", "End", nullptr));
        lbType->setText(QCoreApplication::translate("HaspViewerClass", "Type", nullptr));
        lbID_2->setText(QCoreApplication::translate("HaspViewerClass", "ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HaspViewerClass: public Ui_HaspViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HASPVIEWER_H
