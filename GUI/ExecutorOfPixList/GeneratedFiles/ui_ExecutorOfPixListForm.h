/********************************************************************************
** Form generated from reading UI file 'ExecutorOfPixListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXECUTOROFPIXLISTFORM_H
#define UI_EXECUTOROFPIXLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ExecutorOfPixListForm
{
public:
    QFrame *frame;
    QPushButton *pushButtonExecute;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelOKCount;
    QLabel *labelNGCount;
    QPushButton *pushButtonDeleteList;
    QPushButton *pushButtonAddFolder;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonAll;
    QToolButton *toolButtonCancel;
    QToolButton *toolButtonFilter;
    QTableWidget *tableWidget;

    void setupUi(GUIFormBase *ExecutorOfPixListForm)
    {
        if (ExecutorOfPixListForm->objectName().isEmpty())
            ExecutorOfPixListForm->setObjectName("ExecutorOfPixListForm");
        ExecutorOfPixListForm->resize(400, 330);
        frame = new QFrame(ExecutorOfPixListForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 270, 401, 61));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonExecute = new QPushButton(frame);
        pushButtonExecute->setObjectName("pushButtonExecute");
        pushButtonExecute->setGeometry(QRect(160, 0, 112, 41));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(280, 10, 51, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(280, 30, 51, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        labelOKCount = new QLabel(frame);
        labelOKCount->setObjectName("labelOKCount");
        labelOKCount->setGeometry(QRect(330, 10, 61, 21));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        labelOKCount->setPalette(palette);
        labelOKCount->setAutoFillBackground(true);
        labelOKCount->setFrameShape(QFrame::WinPanel);
        labelOKCount->setFrameShadow(QFrame::Sunken);
        labelNGCount = new QLabel(frame);
        labelNGCount->setObjectName("labelNGCount");
        labelNGCount->setGeometry(QRect(330, 30, 61, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        labelNGCount->setPalette(palette1);
        labelNGCount->setAutoFillBackground(true);
        labelNGCount->setFrameShape(QFrame::WinPanel);
        labelNGCount->setFrameShadow(QFrame::Sunken);
        pushButtonDeleteList = new QPushButton(frame);
        pushButtonDeleteList->setObjectName("pushButtonDeleteList");
        pushButtonDeleteList->setGeometry(QRect(10, 4, 24, 24));
        pushButtonAddFolder = new QPushButton(frame);
        pushButtonAddFolder->setObjectName("pushButtonAddFolder");
        pushButtonAddFolder->setGeometry(QRect(40, 4, 24, 24));
        pushButtonUpdate = new QPushButton(frame);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(80, 0, 71, 30));
        pushButtonAll = new QPushButton(frame);
        pushButtonAll->setObjectName("pushButtonAll");
        pushButtonAll->setGeometry(QRect(80, 36, 71, 21));
        toolButtonCancel = new QToolButton(frame);
        toolButtonCancel->setObjectName("toolButtonCancel");
        toolButtonCancel->setGeometry(QRect(160, 40, 111, 20));
        toolButtonFilter = new QToolButton(frame);
        toolButtonFilter->setObjectName("toolButtonFilter");
        toolButtonFilter->setGeometry(QRect(10, 30, 61, 24));
        tableWidget = new QTableWidget(ExecutorOfPixListForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 401, 261));
        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(ExecutorOfPixListForm);

        pushButtonExecute->setDefault(true);


        QMetaObject::connectSlotsByName(ExecutorOfPixListForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ExecutorOfPixListForm)
    {
        ExecutorOfPixListForm->setWindowTitle(QCoreApplication::translate("ExecutorOfPixListForm", "Form", nullptr));
        pushButtonExecute->setText(QCoreApplication::translate("ExecutorOfPixListForm", "Execute", nullptr));
        label->setText(QCoreApplication::translate("ExecutorOfPixListForm", "OK", nullptr));
        label_2->setText(QCoreApplication::translate("ExecutorOfPixListForm", "NG", nullptr));
        labelOKCount->setText(QCoreApplication::translate("ExecutorOfPixListForm", "XXXX", nullptr));
        labelNGCount->setText(QCoreApplication::translate("ExecutorOfPixListForm", "XXXX", nullptr));
        pushButtonDeleteList->setText(QCoreApplication::translate("ExecutorOfPixListForm", "-", nullptr));
        pushButtonAddFolder->setText(QCoreApplication::translate("ExecutorOfPixListForm", "+", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("ExecutorOfPixListForm", "Update", nullptr));
        pushButtonAll->setText(QCoreApplication::translate("ExecutorOfPixListForm", "All", nullptr));
        toolButtonCancel->setText(QCoreApplication::translate("ExecutorOfPixListForm", "Cancel", nullptr));
        toolButtonFilter->setText(QCoreApplication::translate("ExecutorOfPixListForm", "Filter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ExecutorOfPixListForm", "Folder", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ExecutorOfPixListForm", "File", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ExecutorOfPixListForm", "Judge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExecutorOfPixListForm: public Ui_ExecutorOfPixListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXECUTOROFPIXLISTFORM_H
