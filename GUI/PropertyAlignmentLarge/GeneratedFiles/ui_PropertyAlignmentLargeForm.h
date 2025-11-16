/********************************************************************************
** Form generated from reading UI file 'PropertyAlignmentLargeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYALIGNMENTLARGEFORM_H
#define UI_PROPERTYALIGNMENTLARGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyAlignmentLargeForm
{
public:
    QFrame *frame_2;
    QLabel *label_4;
    QTableWidget *tableWidgetArea;
    QPushButton *pushButtonSelectAll;
    QPushButton *pushButtonGenerateAreaFromMask;
    QFrame *frame;
    QLabel *label_3;
    QTableWidget *tableWidgetPoint;
    QFrame *frame_3;
    QToolButton *toolButtonArea;
    QToolButton *toolButtonPoint;
    QPushButton *pushButtonGrouping;
    QPushButton *pushButtonUngrouping;
    QLabel *label;
    QPushButton *pushButtonCombination;
    QPushButton *pushButtonEditLibrary;
    QFrame *frame_4;
    QCheckBox *checkBoxUseHeadAlignment;
    QTableWidget *tableWidgetHeadAlignment;
    QLabel *label_2;
    QSpinBox *spinBoxHeadAlignmentDifColor;
    QLabel *label_5;
    QSpinBox *spinBoxHeadAlignmentMinSize;
    QPushButton *pushButtonSetAlignmentHead;
    QPushButton *pushButtonGenerate;

    void setupUi(GUIFormBase *PropertyAlignmentLargeForm)
    {
        if (PropertyAlignmentLargeForm->objectName().isEmpty())
            PropertyAlignmentLargeForm->setObjectName("PropertyAlignmentLargeForm");
        PropertyAlignmentLargeForm->resize(399, 750);
        frame_2 = new QFrame(PropertyAlignmentLargeForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 110, 381, 191));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 0, 81, 20));
        label_4->setFrameShape(QFrame::NoFrame);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignJustify|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetArea = new QTableWidget(frame_2);
        if (tableWidgetArea->columnCount() < 4)
            tableWidgetArea->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetArea->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetArea->setObjectName("tableWidgetArea");
        tableWidgetArea->setGeometry(QRect(0, 20, 381, 171));
        tableWidgetArea->setFocusPolicy(Qt::WheelFocus);
        tableWidgetArea->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetArea->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelectAll = new QPushButton(frame_2);
        pushButtonSelectAll->setObjectName("pushButtonSelectAll");
        pushButtonSelectAll->setGeometry(QRect(0, 0, 51, 21));
        pushButtonGenerateAreaFromMask = new QPushButton(frame_2);
        pushButtonGenerateAreaFromMask->setObjectName("pushButtonGenerateAreaFromMask");
        pushButtonGenerateAreaFromMask->setGeometry(QRect(280, 0, 101, 21));
        frame = new QFrame(PropertyAlignmentLargeForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 340, 381, 251));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 381, 20));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignJustify|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetPoint = new QTableWidget(frame);
        if (tableWidgetPoint->columnCount() < 5)
            tableWidgetPoint->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetPoint->setHorizontalHeaderItem(4, __qtablewidgetitem8);
        tableWidgetPoint->setObjectName("tableWidgetPoint");
        tableWidgetPoint->setGeometry(QRect(0, 30, 381, 211));
        tableWidgetPoint->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPoint->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_3 = new QFrame(PropertyAlignmentLargeForm);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 10, 381, 91));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        toolButtonArea = new QToolButton(frame_3);
        toolButtonArea->setObjectName("toolButtonArea");
        toolButtonArea->setGeometry(QRect(10, 10, 81, 61));
        toolButtonArea->setCheckable(true);
        toolButtonArea->setChecked(false);
        toolButtonArea->setAutoExclusive(true);
        toolButtonPoint = new QToolButton(frame_3);
        toolButtonPoint->setObjectName("toolButtonPoint");
        toolButtonPoint->setGeometry(QRect(100, 10, 81, 61));
        toolButtonPoint->setCheckable(true);
        toolButtonPoint->setChecked(true);
        toolButtonPoint->setAutoExclusive(true);
        pushButtonGrouping = new QPushButton(frame_3);
        pushButtonGrouping->setObjectName("pushButtonGrouping");
        pushButtonGrouping->setGeometry(QRect(190, 10, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Group.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonGrouping->setIcon(icon);
        pushButtonUngrouping = new QPushButton(frame_3);
        pushButtonUngrouping->setObjectName("pushButtonUngrouping");
        pushButtonUngrouping->setGeometry(QRect(290, 10, 81, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/User.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUngrouping->setIcon(icon1);
        label = new QLabel(frame_3);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 70, 181, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonCombination = new QPushButton(frame_3);
        pushButtonCombination->setObjectName("pushButtonCombination");
        pushButtonCombination->setGeometry(QRect(190, 40, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Link.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCombination->setIcon(icon2);
        pushButtonEditLibrary = new QPushButton(frame_3);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(280, 10, 91, 51));
        pushButtonEditLibrary->setIcon(icon1);
        frame_4 = new QFrame(PropertyAlignmentLargeForm);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(0, 590, 401, 161));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        checkBoxUseHeadAlignment = new QCheckBox(frame_4);
        checkBoxUseHeadAlignment->setObjectName("checkBoxUseHeadAlignment");
        checkBoxUseHeadAlignment->setGeometry(QRect(10, 0, 141, 31));
        tableWidgetHeadAlignment = new QTableWidget(frame_4);
        if (tableWidgetHeadAlignment->columnCount() < 2)
            tableWidgetHeadAlignment->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetHeadAlignment->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetHeadAlignment->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        if (tableWidgetHeadAlignment->rowCount() < 2)
            tableWidgetHeadAlignment->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetHeadAlignment->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetHeadAlignment->setVerticalHeaderItem(1, __qtablewidgetitem12);
        tableWidgetHeadAlignment->setObjectName("tableWidgetHeadAlignment");
        tableWidgetHeadAlignment->setGeometry(QRect(10, 30, 201, 121));
        tableWidgetHeadAlignment->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetHeadAlignment->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_2 = new QLabel(frame_4);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(220, 5, 81, 21));
        spinBoxHeadAlignmentDifColor = new QSpinBox(frame_4);
        spinBoxHeadAlignmentDifColor->setObjectName("spinBoxHeadAlignmentDifColor");
        spinBoxHeadAlignmentDifColor->setGeometry(QRect(220, 30, 81, 31));
        spinBoxHeadAlignmentDifColor->setMaximum(255);
        label_5 = new QLabel(frame_4);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(310, 5, 81, 21));
        spinBoxHeadAlignmentMinSize = new QSpinBox(frame_4);
        spinBoxHeadAlignmentMinSize->setObjectName("spinBoxHeadAlignmentMinSize");
        spinBoxHeadAlignmentMinSize->setGeometry(QRect(310, 30, 81, 31));
        spinBoxHeadAlignmentMinSize->setMaximum(10000);
        pushButtonSetAlignmentHead = new QPushButton(frame_4);
        pushButtonSetAlignmentHead->setObjectName("pushButtonSetAlignmentHead");
        pushButtonSetAlignmentHead->setGeometry(QRect(310, 80, 80, 41));
        pushButtonGenerate = new QPushButton(PropertyAlignmentLargeForm);
        pushButtonGenerate->setObjectName("pushButtonGenerate");
        pushButtonGenerate->setGeometry(QRect(140, 310, 111, 22));

        retranslateUi(PropertyAlignmentLargeForm);

        QMetaObject::connectSlotsByName(PropertyAlignmentLargeForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyAlignmentLargeForm)
    {
        PropertyAlignmentLargeForm->setWindowTitle(QCoreApplication::translate("PropertyAlignmentLargeForm", "Property AlignmentLarge", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "\343\202\242\343\203\251\343\202\244\343\203\263\343\203\241\343\203\263\343\203\210\351\240\230\345\237\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetArea->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetArea->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetArea->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetArea->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Size", nullptr));
        pushButtonSelectAll->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "All", nullptr));
        pushButtonGenerateAreaFromMask->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Mask->Area", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "\343\203\235\343\202\244\343\203\263\343\203\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetPoint->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetPoint->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Size", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetPoint->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Group", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetPoint->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Kind", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetPoint->horizontalHeaderItem(4);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Search", nullptr));
        toolButtonArea->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "\351\240\230\345\237\237", nullptr));
        toolButtonPoint->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "\343\203\235\343\202\244\343\203\263\343\203\210", nullptr));
        pushButtonGrouping->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Grouping", nullptr));
        pushButtonUngrouping->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Ungroup", nullptr));
        label->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Operate selecte4d items", nullptr));
        pushButtonCombination->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Combination", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Library", nullptr));
        checkBoxUseHeadAlignment->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "\345\205\210\351\240\255\346\216\242\347\264\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetHeadAlignment->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Skip\351\240\230\345\237\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetHeadAlignment->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "\346\216\242\347\264\242\347\265\202\344\272\206\345\200\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetHeadAlignment->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetHeadAlignment->verticalHeaderItem(1);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Y", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "\350\274\235\345\272\246\345\267\256\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "\345\271\205\346\234\200\345\260\217\343\202\265\343\202\244\343\202\272", nullptr));
        pushButtonSetAlignmentHead->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "\350\250\255\345\256\232", nullptr));
        pushButtonGenerate->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Generate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAlignmentLargeForm: public Ui_PropertyAlignmentLargeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYALIGNMENTLARGEFORM_H
