/********************************************************************************
** Form generated from reading UI file 'PropertyAutoMaskingPIForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYAUTOMASKINGPIFORM_H
#define UI_PROPERTYAUTOMASKINGPIFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyAutoMaskingPIFormClass
{
public:
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QFrame *frame;
    QPushButton *ButtonLibNew;
    QLineEdit *EditLibName;
    QCheckBox *checkBDefaultMask;
    QPushButton *ButtonLibSave;
    QPushButton *ButtonLibDelete;
    QLabel *label_12;
    QSpinBox *EditEnSmallDot;
    QPushButton *ButtonLibSaveNew;
    QLabel *label_10;
    QLabel *label_4;
    QLabel *label_13;
    QSpinBox *EditColDiffRate;
    QSpinBox *EditMinSlitDot;
    QLineEdit *EditLibID;
    QLabel *label_11;
    QSpinBox *EditEnLargeDot;
    QLabel *label_14;
    QSpinBox *EditMinSlitSize;
    QSpinBox *EditMinSlitWidth;
    QLabel *label_15;
    QSpinBox *EditMaxLakeSize;
    QLabel *label_16;
    QSpinBox *EditMinClusterSize;
    QLabel *label_17;
    QLabel *label_18;
    QSpinBox *EditMinClusterArea;
    QLabel *label_19;
    QCheckBox *checkBPickupDarker;
    QLabel *label_20;
    QSpinBox *EditNoizeSize;
    QLabel *label_21;
    QCheckBox *checkEnLargeDot;
    QFrame *frame_2;
    QToolButton *toolButtonIneffectiveMask;
    QToolButton *toolButtonAutoMask;
    QToolButton *toolButtonEffectiveMask;
    QTableWidget *tableWidgetMaskingList;
    QLabel *label;
    QToolButton *toolButtonCompositeMask;
    QPushButton *pushButtonGenerateLib;
    QPushButton *pushButtonGenerateDefault;

    void setupUi(GUIFormBase *PropertyAutoMaskingPIFormClass)
    {
        if (PropertyAutoMaskingPIFormClass->objectName().isEmpty())
            PropertyAutoMaskingPIFormClass->setObjectName("PropertyAutoMaskingPIFormClass");
        PropertyAutoMaskingPIFormClass->resize(400, 731);
        tableWidgetLibList = new QTableWidget(PropertyAutoMaskingPIFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 181, 91));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(PropertyAutoMaskingPIFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 161));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(PropertyAutoMaskingPIFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 180, 381, 371));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        ButtonLibNew = new QPushButton(frame);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 330, 91, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibNew->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon);
        EditLibName = new QLineEdit(frame);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(140, 10, 211, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibName->setFont(font1);
        checkBDefaultMask = new QCheckBox(frame);
        checkBDefaultMask->setObjectName("checkBDefaultMask");
        checkBDefaultMask->setGeometry(QRect(210, 310, 161, 18));
        ButtonLibSave = new QPushButton(frame);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(300, 330, 71, 31));
        ButtonLibSave->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon1);
        ButtonLibDelete = new QPushButton(frame);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(110, 330, 71, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon2);
        label_12 = new QLabel(frame);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 110, 251, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEnSmallDot = new QSpinBox(frame);
        EditEnSmallDot->setObjectName("EditEnSmallDot");
        EditEnSmallDot->setGeometry(QRect(270, 110, 81, 22));
        EditEnSmallDot->setMaximum(1000000);
        ButtonLibSaveNew = new QPushButton(frame);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(190, 330, 101, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon3);
        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 50, 251, 21));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 51, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(frame);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 130, 251, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditColDiffRate = new QSpinBox(frame);
        EditColDiffRate->setObjectName("EditColDiffRate");
        EditColDiffRate->setGeometry(QRect(270, 50, 81, 22));
        EditColDiffRate->setMaximum(1000000);
        EditMinSlitDot = new QSpinBox(frame);
        EditMinSlitDot->setObjectName("EditMinSlitDot");
        EditMinSlitDot->setGeometry(QRect(270, 130, 81, 22));
        EditMinSlitDot->setMaximum(1000000);
        EditLibID = new QLineEdit(frame);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 10, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 90, 251, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEnLargeDot = new QSpinBox(frame);
        EditEnLargeDot->setObjectName("EditEnLargeDot");
        EditEnLargeDot->setGeometry(QRect(270, 90, 81, 22));
        EditEnLargeDot->setMaximum(1000000);
        label_14 = new QLabel(frame);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 150, 251, 21));
        label_14->setFrameShape(QFrame::Panel);
        label_14->setFrameShadow(QFrame::Sunken);
        label_14->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinSlitSize = new QSpinBox(frame);
        EditMinSlitSize->setObjectName("EditMinSlitSize");
        EditMinSlitSize->setGeometry(QRect(270, 150, 81, 22));
        EditMinSlitSize->setMaximum(1000000);
        EditMinSlitWidth = new QSpinBox(frame);
        EditMinSlitWidth->setObjectName("EditMinSlitWidth");
        EditMinSlitWidth->setGeometry(QRect(270, 170, 81, 22));
        EditMinSlitWidth->setMaximum(1000000);
        label_15 = new QLabel(frame);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 170, 251, 21));
        label_15->setFrameShape(QFrame::Panel);
        label_15->setFrameShadow(QFrame::Sunken);
        label_15->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxLakeSize = new QSpinBox(frame);
        EditMaxLakeSize->setObjectName("EditMaxLakeSize");
        EditMaxLakeSize->setGeometry(QRect(270, 200, 81, 22));
        EditMaxLakeSize->setMaximum(1000000);
        label_16 = new QLabel(frame);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 200, 251, 21));
        label_16->setFrameShape(QFrame::Panel);
        label_16->setFrameShadow(QFrame::Sunken);
        label_16->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinClusterSize = new QSpinBox(frame);
        EditMinClusterSize->setObjectName("EditMinClusterSize");
        EditMinClusterSize->setGeometry(QRect(270, 230, 81, 22));
        EditMinClusterSize->setMaximum(1000000);
        label_17 = new QLabel(frame);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 230, 251, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_18 = new QLabel(frame);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 250, 251, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinClusterArea = new QSpinBox(frame);
        EditMinClusterArea->setObjectName("EditMinClusterArea");
        EditMinClusterArea->setGeometry(QRect(270, 250, 81, 22));
        EditMinClusterArea->setMaximum(1000000);
        label_19 = new QLabel(frame);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(10, 270, 251, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBPickupDarker = new QCheckBox(frame);
        checkBPickupDarker->setObjectName("checkBPickupDarker");
        checkBPickupDarker->setGeometry(QRect(270, 270, 81, 20));
        label_20 = new QLabel(frame);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(10, 70, 251, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoizeSize = new QSpinBox(frame);
        EditNoizeSize->setObjectName("EditNoizeSize");
        EditNoizeSize->setGeometry(QRect(270, 70, 81, 22));
        EditNoizeSize->setMaximum(1000000);
        label_21 = new QLabel(frame);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 290, 251, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkEnLargeDot = new QCheckBox(frame);
        checkEnLargeDot->setObjectName("checkEnLargeDot");
        checkEnLargeDot->setGeometry(QRect(270, 290, 81, 20));
        frame_2 = new QFrame(PropertyAutoMaskingPIFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 560, 381, 161));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        toolButtonIneffectiveMask = new QToolButton(frame_2);
        toolButtonIneffectiveMask->setObjectName("toolButtonIneffectiveMask");
        toolButtonIneffectiveMask->setGeometry(QRect(190, 20, 91, 31));
        toolButtonIneffectiveMask->setCheckable(true);
        toolButtonIneffectiveMask->setAutoExclusive(true);
        toolButtonAutoMask = new QToolButton(frame_2);
        toolButtonAutoMask->setObjectName("toolButtonAutoMask");
        toolButtonAutoMask->setGeometry(QRect(10, 20, 91, 31));
        toolButtonAutoMask->setCheckable(true);
        toolButtonAutoMask->setChecked(true);
        toolButtonAutoMask->setAutoExclusive(true);
        toolButtonEffectiveMask = new QToolButton(frame_2);
        toolButtonEffectiveMask->setObjectName("toolButtonEffectiveMask");
        toolButtonEffectiveMask->setGeometry(QRect(100, 20, 91, 31));
        toolButtonEffectiveMask->setCheckable(true);
        toolButtonEffectiveMask->setAutoExclusive(true);
        tableWidgetMaskingList = new QTableWidget(frame_2);
        if (tableWidgetMaskingList->columnCount() < 3)
            tableWidgetMaskingList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetMaskingList->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        tableWidgetMaskingList->setObjectName("tableWidgetMaskingList");
        tableWidgetMaskingList->setGeometry(QRect(10, 60, 361, 91));
        tableWidgetMaskingList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 381, 20));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::NoRole, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::NoRole, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::NoRole, brush);
        label->setPalette(palette);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        toolButtonCompositeMask = new QToolButton(frame_2);
        toolButtonCompositeMask->setObjectName("toolButtonCompositeMask");
        toolButtonCompositeMask->setGeometry(QRect(280, 20, 91, 31));
        toolButtonCompositeMask->setCheckable(true);
        toolButtonCompositeMask->setAutoExclusive(true);
        pushButtonGenerateLib = new QPushButton(PropertyAutoMaskingPIFormClass);
        pushButtonGenerateLib->setObjectName("pushButtonGenerateLib");
        pushButtonGenerateLib->setGeometry(QRect(210, 110, 181, 41));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGenerateLib->setIcon(icon4);
        pushButtonGenerateDefault = new QPushButton(PropertyAutoMaskingPIFormClass);
        pushButtonGenerateDefault->setObjectName("pushButtonGenerateDefault");
        pushButtonGenerateDefault->setGeometry(QRect(210, 150, 181, 21));
        pushButtonGenerateDefault->setIcon(icon4);

        retranslateUi(PropertyAutoMaskingPIFormClass);

        QMetaObject::connectSlotsByName(PropertyAutoMaskingPIFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyAutoMaskingPIFormClass)
    {
        PropertyAutoMaskingPIFormClass->setWindowTitle(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "PropertyAutoMaskingPIForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "Name", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "Clear new", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "Library Name", nullptr));
        checkBDefaultMask->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\343\203\207\343\203\225\343\202\251\343\203\253\343\203\210", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "Update", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "Delete", nullptr));
        label_12->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\345\217\216\347\270\256\343\203\211\343\203\203\343\203\210\357\274\210\345\244\226\345\275\242\343\201\256\350\274\252\351\203\255\351\203\250\345\210\206\343\201\256\351\231\244\345\244\226\343\201\256\343\201\237\343\202\201\357\274\211", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "Save New", nullptr));
        label_10->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\346\212\275\345\207\272\343\201\231\343\202\213\350\274\235\345\272\246\345\267\256\343\201\256\343\203\221\343\203\274\343\202\273\343\203\263\343\203\210\357\274\210\357\274\205\357\274\211", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\345\220\215\347\247\260", nullptr));
        label_13->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\347\204\241\345\212\271\345\214\226\343\201\225\343\201\233\343\201\237\343\201\204\346\234\200\345\260\217\343\202\271\343\203\252\343\203\203\343\203\210\343\203\273\347\251\264\343\201\256\351\235\242\347\251\215\357\274\210\343\203\211\343\203\203\343\203\210\357\274\211", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "12345", nullptr));
        label_11->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210\357\274\210\345\260\217\345\276\204\347\251\264\343\202\222\346\244\234\346\237\273\343\202\250\343\203\252\343\202\242\343\201\253\345\220\253\343\202\201\343\202\213\343\201\237\343\202\201\357\274\211", nullptr));
        label_14->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\347\204\241\345\212\271\345\214\226\343\201\225\343\201\233\343\201\237\343\201\204\346\234\200\345\260\217\343\202\271\343\203\252\343\203\203\343\203\210\343\203\273\347\251\264\343\201\256\351\225\267\343\201\225\357\274\210\343\203\211\343\203\203\343\203\210\357\274\211", nullptr));
        label_15->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\347\204\241\345\212\271\345\214\226\343\201\225\343\201\233\343\201\237\343\201\204\346\234\200\345\260\217\343\202\271\343\203\252\343\203\203\343\203\210\343\201\256\345\271\205\357\274\210\343\203\211\343\203\203\343\203\210\357\274\211", nullptr));
        label_16->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\345\255\244\345\263\266\343\201\256\343\201\202\343\202\213\346\271\226\343\201\256\346\234\200\345\244\247\351\225\267\343\201\225\357\274\210\343\203\211\343\203\203\343\203\210\357\274\211", nullptr));
        label_17->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\346\234\211\345\212\271\343\202\250\343\203\252\343\202\242\343\201\256\346\234\200\345\260\217\351\225\267\343\201\225\357\274\210\343\203\211\343\203\203\343\203\210\357\274\211", nullptr));
        label_18->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\346\234\211\345\212\271\343\202\250\343\203\252\343\202\242\343\201\256\346\234\200\345\260\217\351\235\242\347\251\215\357\274\210\343\203\211\343\203\203\343\203\210\357\274\211", nullptr));
        label_19->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\345\275\261\351\203\250\345\210\206\357\274\210\345\237\272\346\235\277\347\204\241\343\201\227\343\202\210\343\202\212\346\232\227\343\201\204\351\203\250\345\210\206\357\274\211\343\201\256\346\212\275\345\207\272", nullptr));
        label_20->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_21->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\345\244\226\345\275\242\343\201\256\350\274\252\351\203\255\351\203\250\345\210\206\343\201\214PAD\346\212\275\345\207\272\350\211\262\343\201\247\343\201\202\343\201\243\343\201\246\343\202\202\345\217\216\347\270\256", nullptr));
        toolButtonIneffectiveMask->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\346\211\213\345\213\225\347\204\241\345\212\271\343\203\236\343\202\271\343\202\257", nullptr));
        toolButtonAutoMask->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\350\207\252\345\213\225\347\224\237\346\210\220\343\203\236\343\202\271\343\202\257", nullptr));
        toolButtonEffectiveMask->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\346\211\213\345\213\225\346\234\211\345\212\271\343\203\236\343\202\271\343\202\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMaskingList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMaskingList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "Effective", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetMaskingList->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "Area", nullptr));
        label->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\350\241\250\347\244\272", nullptr));
        toolButtonCompositeMask->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\347\265\220\346\236\234\345\220\210\346\210\220\343\203\236\343\202\271\343\202\257", nullptr));
        pushButtonGenerateLib->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\351\201\270\346\212\236\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        pushButtonGenerateDefault->setText(QCoreApplication::translate("PropertyAutoMaskingPIFormClass", "\346\234\200\345\210\235\343\201\256\343\203\207\343\203\225\343\202\251\343\203\253\343\203\210\343\201\247\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAutoMaskingPIFormClass: public Ui_PropertyAutoMaskingPIFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYAUTOMASKINGPIFORM_H
