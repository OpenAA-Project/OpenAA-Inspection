/********************************************************************************
** Form generated from reading UI file 'SelectLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYDIALOG_H
#define UI_SELECTLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibraryDialog
{
public:
    QFrame *frameLibFolder;
    QPushButton *ButtonSelect;
    QPushButton *ButtonCancel;
    QTableWidget *tableWidgetLibList;
    QFrame *frame;
    QLabel *label;
    QLineEdit *lineEditLayerTypeName;
    QLabel *label_2;
    QSpinBox *spinBoxMaxEnlargeDot;
    QSpinBox *spinBoxMaxShrinkageDot;
    QLabel *label_3;
    QSpinBox *spinBoxMaxShiftDot;
    QLabel *label_4;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxMaxAngleRadius;
    QDoubleSpinBox *doubleSpinBoxMaxUnstableZone;
    QLabel *label_6;
    QLineEdit *lineEditLayerTypeLibID;
    QPushButton *ButtonClear;
    QPushButton *pushButtonEditLibrary;

    void setupUi(QDialog *SelectLibraryDialog)
    {
        if (SelectLibraryDialog->objectName().isEmpty())
            SelectLibraryDialog->setObjectName("SelectLibraryDialog");
        SelectLibraryDialog->resize(877, 388);
        frameLibFolder = new QFrame(SelectLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(0, 10, 191, 371));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonSelect = new QPushButton(SelectLibraryDialog);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(500, 350, 121, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelect->setIcon(icon);
        ButtonCancel = new QPushButton(SelectLibraryDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(770, 350, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        tableWidgetLibList = new QTableWidget(SelectLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(200, 10, 281, 371));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(SelectLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(490, 10, 381, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 71, 21));
        lineEditLayerTypeName = new QLineEdit(frame);
        lineEditLayerTypeName->setObjectName("lineEditLayerTypeName");
        lineEditLayerTypeName->setGeometry(QRect(160, 10, 211, 21));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 101, 21));
        spinBoxMaxEnlargeDot = new QSpinBox(frame);
        spinBoxMaxEnlargeDot->setObjectName("spinBoxMaxEnlargeDot");
        spinBoxMaxEnlargeDot->setGeometry(QRect(160, 40, 101, 22));
        spinBoxMaxEnlargeDot->setReadOnly(true);
        spinBoxMaxEnlargeDot->setMaximum(99999999);
        spinBoxMaxShrinkageDot = new QSpinBox(frame);
        spinBoxMaxShrinkageDot->setObjectName("spinBoxMaxShrinkageDot");
        spinBoxMaxShrinkageDot->setGeometry(QRect(160, 70, 101, 22));
        spinBoxMaxShrinkageDot->setReadOnly(true);
        spinBoxMaxShrinkageDot->setMaximum(99999999);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 101, 21));
        spinBoxMaxShiftDot = new QSpinBox(frame);
        spinBoxMaxShiftDot->setObjectName("spinBoxMaxShiftDot");
        spinBoxMaxShiftDot->setGeometry(QRect(160, 100, 101, 22));
        spinBoxMaxShiftDot->setReadOnly(true);
        spinBoxMaxShiftDot->setMaximum(99999999);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 101, 21));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 130, 101, 21));
        doubleSpinBoxMaxAngleRadius = new QDoubleSpinBox(frame);
        doubleSpinBoxMaxAngleRadius->setObjectName("doubleSpinBoxMaxAngleRadius");
        doubleSpinBoxMaxAngleRadius->setGeometry(QRect(160, 130, 101, 22));
        doubleSpinBoxMaxAngleRadius->setReadOnly(true);
        doubleSpinBoxMaxAngleRadius->setMaximum(99999999.000000000000000);
        doubleSpinBoxMaxUnstableZone = new QDoubleSpinBox(frame);
        doubleSpinBoxMaxUnstableZone->setObjectName("doubleSpinBoxMaxUnstableZone");
        doubleSpinBoxMaxUnstableZone->setGeometry(QRect(160, 160, 101, 22));
        doubleSpinBoxMaxUnstableZone->setReadOnly(true);
        doubleSpinBoxMaxUnstableZone->setMaximum(99999999.000000000000000);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 160, 141, 21));
        lineEditLayerTypeLibID = new QLineEdit(frame);
        lineEditLayerTypeLibID->setObjectName("lineEditLayerTypeLibID");
        lineEditLayerTypeLibID->setGeometry(QRect(100, 10, 61, 21));
        ButtonClear = new QPushButton(SelectLibraryDialog);
        ButtonClear->setObjectName("ButtonClear");
        ButtonClear->setGeometry(QRect(640, 350, 111, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonClear->setIcon(icon2);
        pushButtonEditLibrary = new QPushButton(SelectLibraryDialog);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(500, 310, 231, 28));

        retranslateUi(SelectLibraryDialog);

        QMetaObject::connectSlotsByName(SelectLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibraryDialog)
    {
        SelectLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectLibraryDialog", "Select Library", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectLibraryDialog", "Select", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectLibraryDialog", "Close", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectLibraryDialog", "Name", nullptr));
        label->setText(QCoreApplication::translate("SelectLibraryDialog", "Type name", nullptr));
        label_2->setText(QCoreApplication::translate("SelectLibraryDialog", "Max enlarge dot", nullptr));
        label_3->setText(QCoreApplication::translate("SelectLibraryDialog", "Max shrinkage dot", nullptr));
        label_4->setText(QCoreApplication::translate("SelectLibraryDialog", "Max shift dot", nullptr));
        label_5->setText(QCoreApplication::translate("SelectLibraryDialog", "Max angle Radius", nullptr));
        label_6->setText(QCoreApplication::translate("SelectLibraryDialog", "Max unstable outline area", nullptr));
        ButtonClear->setText(QCoreApplication::translate("SelectLibraryDialog", "Clear", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("SelectLibraryDialog", "Create/Edit Layer library", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryDialog: public Ui_SelectLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYDIALOG_H
