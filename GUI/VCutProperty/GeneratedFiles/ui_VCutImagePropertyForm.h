/********************************************************************************
** Form generated from reading UI file 'VCutImagePropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VCUTIMAGEPROPERTYFORM_H
#define UI_VCUTIMAGEPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_VCutImagePropertyFormClass
{
public:
    QFrame *frame_2;
    QTableWidget *tableWidgetVCutList;
    QLabel *label;
    QFrame *frame;
    QPushButton *ButtonLibNew;
    QLineEdit *EditLibName;
    QPushButton *ButtonLibSave;
    QPushButton *ButtonLibDelete;
    QLabel *label_12;
    QSpinBox *EditThresholdLength;
    QPushButton *ButtonLibSaveNew;
    QLabel *label_10;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QLabel *label_11;
    QSpinBox *EditThresholdShift;
    QCheckBox *checkBoxGenDynamicMask;
    QLabel *label_13;
    QSpinBox *EditExpandGenMask;
    QDoubleSpinBox *EditThresholdLevel;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;

    void setupUi(GUIFormBase *VCutImagePropertyFormClass)
    {
        if (VCutImagePropertyFormClass->objectName().isEmpty())
            VCutImagePropertyFormClass->setObjectName("VCutImagePropertyFormClass");
        VCutImagePropertyFormClass->resize(401, 639);
        frame_2 = new QFrame(VCutImagePropertyFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 460, 381, 171));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        tableWidgetVCutList = new QTableWidget(frame_2);
        if (tableWidgetVCutList->columnCount() < 6)
            tableWidgetVCutList->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetVCutList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetVCutList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetVCutList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetVCutList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetVCutList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetVCutList->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidgetVCutList->setObjectName("tableWidgetVCutList");
        tableWidgetVCutList->setGeometry(QRect(10, 30, 361, 131));
        tableWidgetVCutList->setSelectionBehavior(QAbstractItemView::SelectRows);
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
        frame = new QFrame(VCutImagePropertyFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 210, 381, 231));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        ButtonLibNew = new QPushButton(frame);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 180, 91, 31));
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
        ButtonLibSave = new QPushButton(frame);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(290, 180, 81, 31));
        ButtonLibSave->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon1);
        ButtonLibDelete = new QPushButton(frame);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(110, 180, 71, 31));
        ButtonLibDelete->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon2);
        label_12 = new QLabel(frame);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 94, 251, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditThresholdLength = new QSpinBox(frame);
        EditThresholdLength->setObjectName("EditThresholdLength");
        EditThresholdLength->setGeometry(QRect(270, 94, 81, 22));
        EditThresholdLength->setMaximum(1000000);
        ButtonLibSaveNew = new QPushButton(frame);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(190, 180, 91, 31));
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
        EditLibID = new QLineEdit(frame);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 10, 81, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 72, 251, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditThresholdShift = new QSpinBox(frame);
        EditThresholdShift->setObjectName("EditThresholdShift");
        EditThresholdShift->setGeometry(QRect(270, 72, 81, 22));
        EditThresholdShift->setMaximum(1000000);
        checkBoxGenDynamicMask = new QCheckBox(frame);
        checkBoxGenDynamicMask->setObjectName("checkBoxGenDynamicMask");
        checkBoxGenDynamicMask->setGeometry(QRect(20, 120, 341, 22));
        label_13 = new QLabel(frame);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 150, 251, 21));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditExpandGenMask = new QSpinBox(frame);
        EditExpandGenMask->setObjectName("EditExpandGenMask");
        EditExpandGenMask->setGeometry(QRect(270, 150, 81, 22));
        EditExpandGenMask->setMinimum(-100);
        EditExpandGenMask->setMaximum(100);
        EditThresholdLevel = new QDoubleSpinBox(frame);
        EditThresholdLevel->setObjectName("EditThresholdLevel");
        EditThresholdLevel->setGeometry(QRect(270, 50, 101, 22));
        EditThresholdLevel->setDecimals(3);
        EditThresholdLevel->setMaximum(99999999.000000000000000);
        frameLibFolder = new QFrame(VCutImagePropertyFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 181));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(VCutImagePropertyFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 20, 181, 171));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(VCutImagePropertyFormClass);

        QMetaObject::connectSlotsByName(VCutImagePropertyFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *VCutImagePropertyFormClass)
    {
        VCutImagePropertyFormClass->setWindowTitle(QCoreApplication::translate("VCutImagePropertyFormClass", "VCutImagePropertyForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetVCutList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Phase", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetVCutList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetVCutList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Area", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetVCutList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Level", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetVCutList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Shift", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetVCutList->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Length", nullptr));
        label->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "\350\241\250\347\244\272", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Clear new", nullptr));
        EditLibName->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Library Name", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Update", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Delete", nullptr));
        label_12->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "V\343\202\253\343\203\203\343\203\210\347\204\241\343\201\227\343\201\256\350\250\261\345\256\271\351\225\267\343\201\225", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Save New", nullptr));
        label_10->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "\346\212\275\345\207\272\343\203\254\343\203\231\343\203\253", nullptr));
        label_4->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "12345", nullptr));
        label_11->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "\344\275\215\347\275\256\343\201\232\343\202\214\350\250\261\345\256\271\343\203\224\343\202\257\343\202\273\343\203\253", nullptr));
        checkBoxGenDynamicMask->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "DynamicMask\347\224\237\346\210\220", nullptr));
        label_13->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "\347\224\237\346\210\220\343\203\236\343\202\271\343\202\257\343\201\256\350\206\250\345\274\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("VCutImagePropertyFormClass", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VCutImagePropertyFormClass: public Ui_VCutImagePropertyFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VCUTIMAGEPROPERTYFORM_H
