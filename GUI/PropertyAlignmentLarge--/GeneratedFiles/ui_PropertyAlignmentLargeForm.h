/********************************************************************************
** Form generated from reading UI file 'PropertyAlignmentLargeForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYALIGNMENTLARGEFORM_H
#define UI_PROPERTYALIGNMENTLARGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
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
    QComboBox *comboBoxAngle;
    QLabel *label_2;

    void setupUi(GUIFormBase *PropertyAlignmentLargeForm)
    {
        if (PropertyAlignmentLargeForm->objectName().isEmpty())
            PropertyAlignmentLargeForm->setObjectName(QString::fromUtf8("PropertyAlignmentLargeForm"));
        PropertyAlignmentLargeForm->resize(399, 700);
        frame_2 = new QFrame(PropertyAlignmentLargeForm);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(10, 110, 381, 271));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 0, 381, 20));
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
        tableWidgetArea->setObjectName(QString::fromUtf8("tableWidgetArea"));
        tableWidgetArea->setGeometry(QRect(0, 20, 381, 251));
        tableWidgetArea->setFocusPolicy(Qt::WheelFocus);
        tableWidgetArea->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetArea->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSelectAll = new QPushButton(frame_2);
        pushButtonSelectAll->setObjectName(QString::fromUtf8("pushButtonSelectAll"));
        pushButtonSelectAll->setGeometry(QRect(10, 0, 51, 21));
        frame = new QFrame(PropertyAlignmentLargeForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 430, 381, 261));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
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
        tableWidgetPoint->setObjectName(QString::fromUtf8("tableWidgetPoint"));
        tableWidgetPoint->setGeometry(QRect(0, 30, 381, 231));
        tableWidgetPoint->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPoint->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_3 = new QFrame(PropertyAlignmentLargeForm);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(10, 10, 381, 91));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        toolButtonArea = new QToolButton(frame_3);
        toolButtonArea->setObjectName(QString::fromUtf8("toolButtonArea"));
        toolButtonArea->setGeometry(QRect(10, 10, 81, 61));
        toolButtonArea->setCheckable(true);
        toolButtonArea->setChecked(false);
        toolButtonArea->setAutoExclusive(true);
        toolButtonPoint = new QToolButton(frame_3);
        toolButtonPoint->setObjectName(QString::fromUtf8("toolButtonPoint"));
        toolButtonPoint->setGeometry(QRect(100, 10, 81, 61));
        toolButtonPoint->setCheckable(true);
        toolButtonPoint->setChecked(true);
        toolButtonPoint->setAutoExclusive(true);
        pushButtonGrouping = new QPushButton(frame_3);
        pushButtonGrouping->setObjectName(QString::fromUtf8("pushButtonGrouping"));
        pushButtonGrouping->setGeometry(QRect(190, 10, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Group.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonGrouping->setIcon(icon);
        pushButtonUngrouping = new QPushButton(frame_3);
        pushButtonUngrouping->setObjectName(QString::fromUtf8("pushButtonUngrouping"));
        pushButtonUngrouping->setGeometry(QRect(290, 10, 81, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/User.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonUngrouping->setIcon(icon1);
        label = new QLabel(frame_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 70, 181, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonCombination = new QPushButton(frame_3);
        pushButtonCombination->setObjectName(QString::fromUtf8("pushButtonCombination"));
        pushButtonCombination->setGeometry(QRect(190, 40, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Link.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCombination->setIcon(icon2);
        pushButtonEditLibrary = new QPushButton(frame_3);
        pushButtonEditLibrary->setObjectName(QString::fromUtf8("pushButtonEditLibrary"));
        pushButtonEditLibrary->setGeometry(QRect(280, 10, 91, 51));
        pushButtonEditLibrary->setIcon(icon1);
        comboBoxAngle = new QComboBox(PropertyAlignmentLargeForm);
        comboBoxAngle->setObjectName(QString::fromUtf8("comboBoxAngle"));
        comboBoxAngle->setGeometry(QRect(130, 393, 92, 31));
        label_2 = new QLabel(PropertyAlignmentLargeForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 397, 75, 21));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

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
        label_2->setText(QCoreApplication::translate("PropertyAlignmentLargeForm", "Angle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyAlignmentLargeForm: public Ui_PropertyAlignmentLargeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYALIGNMENTLARGEFORM_H
