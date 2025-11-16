/********************************************************************************
** Form generated from reading UI file 'ShowSampleForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSAMPLEFORM_H
#define UI_SHOWSAMPLEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowSampleForm
{
public:
    QFrame *frame;
    QPushButton *pushButtonDeleteSelection;
    QPushButton *pushButtonClose;
    QTableWidget *tableWidget;

    void setupUi(QWidget *ShowSampleForm)
    {
        if (ShowSampleForm->objectName().isEmpty())
            ShowSampleForm->setObjectName("ShowSampleForm");
        ShowSampleForm->resize(720, 533);
        frame = new QFrame(ShowSampleForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(130, 10, 581, 511));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonDeleteSelection = new QPushButton(ShowSampleForm);
        pushButtonDeleteSelection->setObjectName("pushButtonDeleteSelection");
        pushButtonDeleteSelection->setGeometry(QRect(10, 420, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDeleteSelection->setIcon(icon);
        pushButtonClose = new QPushButton(ShowSampleForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(22, 487, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        tableWidget = new QTableWidget(ShowSampleForm);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 111, 401));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(ShowSampleForm);

        QMetaObject::connectSlotsByName(ShowSampleForm);
    } // setupUi

    void retranslateUi(QWidget *ShowSampleForm)
    {
        ShowSampleForm->setWindowTitle(QCoreApplication::translate("ShowSampleForm", "Show Sample", nullptr));
        pushButtonDeleteSelection->setText(QCoreApplication::translate("ShowSampleForm", "Delete selection", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowSampleForm", "Close", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowSampleForm", "Judge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowSampleForm: public Ui_ShowSampleForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSAMPLEFORM_H
