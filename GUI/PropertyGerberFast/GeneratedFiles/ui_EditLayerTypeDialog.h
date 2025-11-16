/********************************************************************************
** Form generated from reading UI file 'EditLayerTypeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLAYERTYPEDIALOG_H
#define UI_EDITLAYERTYPEDIALOG_H

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

class Ui_EditLayerTypeDialog
{
public:
    QPushButton *pushButtonSaveNew;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonClose;
    QFrame *frame;
    QLabel *label;
    QLineEdit *lineEditLibName;
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
    QLineEdit *lineEditLibID;
    QFrame *frameLibFolder;
    QTableWidget *tableWidgetLibList;

    void setupUi(QDialog *EditLayerTypeDialog)
    {
        if (EditLayerTypeDialog->objectName().isEmpty())
            EditLayerTypeDialog->setObjectName("EditLayerTypeDialog");
        EditLayerTypeDialog->resize(348, 753);
        pushButtonSaveNew = new QPushButton(EditLayerTypeDialog);
        pushButtonSaveNew->setObjectName("pushButtonSaveNew");
        pushButtonSaveNew->setGeometry(QRect(10, 670, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSaveNew->setIcon(icon);
        pushButtonUpdate = new QPushButton(EditLayerTypeDialog);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(125, 670, 111, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon1);
        pushButtonDelete = new QPushButton(EditLayerTypeDialog);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(240, 670, 101, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon2);
        pushButtonClose = new QPushButton(EditLayerTypeDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(240, 710, 101, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon3);
        frame = new QFrame(EditLayerTypeDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 449, 331, 211));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 71, 21));
        lineEditLibName = new QLineEdit(frame);
        lineEditLibName->setObjectName("lineEditLibName");
        lineEditLibName->setGeometry(QRect(160, 10, 161, 21));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 208, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxMaxEnlargeDot = new QSpinBox(frame);
        spinBoxMaxEnlargeDot->setObjectName("spinBoxMaxEnlargeDot");
        spinBoxMaxEnlargeDot->setGeometry(QRect(220, 40, 101, 22));
        spinBoxMaxEnlargeDot->setMaximum(99999999);
        spinBoxMaxShrinkageDot = new QSpinBox(frame);
        spinBoxMaxShrinkageDot->setObjectName("spinBoxMaxShrinkageDot");
        spinBoxMaxShrinkageDot->setGeometry(QRect(220, 70, 101, 22));
        spinBoxMaxShrinkageDot->setMaximum(99999999);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 208, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        spinBoxMaxShiftDot = new QSpinBox(frame);
        spinBoxMaxShiftDot->setObjectName("spinBoxMaxShiftDot");
        spinBoxMaxShiftDot->setGeometry(QRect(220, 100, 101, 22));
        spinBoxMaxShiftDot->setMaximum(99999999);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 208, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 130, 208, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxMaxAngleRadius = new QDoubleSpinBox(frame);
        doubleSpinBoxMaxAngleRadius->setObjectName("doubleSpinBoxMaxAngleRadius");
        doubleSpinBoxMaxAngleRadius->setGeometry(QRect(220, 130, 101, 22));
        doubleSpinBoxMaxAngleRadius->setMaximum(99999999.000000000000000);
        doubleSpinBoxMaxUnstableZone = new QDoubleSpinBox(frame);
        doubleSpinBoxMaxUnstableZone->setObjectName("doubleSpinBoxMaxUnstableZone");
        doubleSpinBoxMaxUnstableZone->setGeometry(QRect(220, 160, 101, 22));
        doubleSpinBoxMaxUnstableZone->setMaximum(99999999.000000000000000);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 160, 208, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        lineEditLibID = new QLineEdit(frame);
        lineEditLibID->setObjectName("lineEditLibID");
        lineEditLibID->setGeometry(QRect(100, 10, 61, 21));
        lineEditLibID->setReadOnly(true);
        frameLibFolder = new QFrame(EditLayerTypeDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 331, 231));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        tableWidgetLibList = new QTableWidget(EditLayerTypeDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 250, 331, 191));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(EditLayerTypeDialog);

        QMetaObject::connectSlotsByName(EditLayerTypeDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLayerTypeDialog)
    {
        EditLayerTypeDialog->setWindowTitle(QCoreApplication::translate("EditLayerTypeDialog", "Edit gerber type", nullptr));
        pushButtonSaveNew->setText(QCoreApplication::translate("EditLayerTypeDialog", "Save new", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("EditLayerTypeDialog", "Update", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EditLayerTypeDialog", "Delete", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditLayerTypeDialog", "Close", nullptr));
        label->setText(QCoreApplication::translate("EditLayerTypeDialog", "Type name", nullptr));
        label_2->setText(QCoreApplication::translate("EditLayerTypeDialog", "Max enlarge dot", nullptr));
        label_3->setText(QCoreApplication::translate("EditLayerTypeDialog", "Max shrinkage dot", nullptr));
        label_4->setText(QCoreApplication::translate("EditLayerTypeDialog", "Max shift dot", nullptr));
        label_5->setText(QCoreApplication::translate("EditLayerTypeDialog", "Max angle Radius", nullptr));
        label_6->setText(QCoreApplication::translate("EditLayerTypeDialog", "Max unstable outline area", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLayerTypeDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLayerTypeDialog", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLayerTypeDialog: public Ui_EditLayerTypeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLAYERTYPEDIALOG_H
