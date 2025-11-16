/********************************************************************************
** Form generated from reading UI file 'ImageBankListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEBANKLISTFORM_H
#define UI_IMAGEBANKLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageBankListForm
{
public:
    QFrame *frame;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonRetry;
    QPushButton *pushButtonCountSet;
    QSpinBox *spinBoxCount;
    QPushButton *pushButtonSaveAll;
    QPushButton *pushButtonClose;
    QFrame *frame_2;
    QToolButton *toolButtonStoreOnlyNG;
    QToolButton *toolButtonStoreOnlyOK;
    QTableWidget *tableWidgetImages;

    void setupUi(QWidget *ImageBankListForm)
    {
        if (ImageBankListForm->objectName().isEmpty())
            ImageBankListForm->setObjectName("ImageBankListForm");
        ImageBankListForm->resize(461, 450);
        frame = new QFrame(ImageBankListForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 320, 461, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonClear = new QPushButton(frame);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(10, 50, 112, 34));
        pushButtonRetry = new QPushButton(frame);
        pushButtonRetry->setObjectName("pushButtonRetry");
        pushButtonRetry->setGeometry(QRect(140, 50, 112, 34));
        pushButtonCountSet = new QPushButton(frame);
        pushButtonCountSet->setObjectName("pushButtonCountSet");
        pushButtonCountSet->setGeometry(QRect(280, 50, 91, 34));
        spinBoxCount = new QSpinBox(frame);
        spinBoxCount->setObjectName("spinBoxCount");
        spinBoxCount->setGeometry(QRect(380, 50, 71, 31));
        spinBoxCount->setMaximum(1000);
        pushButtonSaveAll = new QPushButton(frame);
        pushButtonSaveAll->setObjectName("pushButtonSaveAll");
        pushButtonSaveAll->setGeometry(QRect(10, 90, 112, 34));
        pushButtonClose = new QPushButton(frame);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(340, 90, 112, 34));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 341, 31));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        toolButtonStoreOnlyNG = new QToolButton(frame_2);
        toolButtonStoreOnlyNG->setObjectName("toolButtonStoreOnlyNG");
        toolButtonStoreOnlyNG->setGeometry(QRect(150, 0, 141, 31));
        toolButtonStoreOnlyNG->setCheckable(true);
        toolButtonStoreOnlyOK = new QToolButton(frame_2);
        toolButtonStoreOnlyOK->setObjectName("toolButtonStoreOnlyOK");
        toolButtonStoreOnlyOK->setGeometry(QRect(0, 0, 141, 31));
        toolButtonStoreOnlyOK->setCheckable(true);
        tableWidgetImages = new QTableWidget(ImageBankListForm);
        if (tableWidgetImages->columnCount() < 3)
            tableWidgetImages->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetImages->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetImages->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetImages->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetImages->setObjectName("tableWidgetImages");
        tableWidgetImages->setGeometry(QRect(0, 0, 461, 321));
        tableWidgetImages->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetImages->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(ImageBankListForm);

        QMetaObject::connectSlotsByName(ImageBankListForm);
    } // setupUi

    void retranslateUi(QWidget *ImageBankListForm)
    {
        ImageBankListForm->setWindowTitle(QCoreApplication::translate("ImageBankListForm", "Form", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("ImageBankListForm", "Clear", nullptr));
        pushButtonRetry->setText(QCoreApplication::translate("ImageBankListForm", "Retry", nullptr));
        pushButtonCountSet->setText(QCoreApplication::translate("ImageBankListForm", "Count Set", nullptr));
        pushButtonSaveAll->setText(QCoreApplication::translate("ImageBankListForm", "Save all", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ImageBankListForm", "Close", nullptr));
        toolButtonStoreOnlyNG->setText(QCoreApplication::translate("ImageBankListForm", "Store only NG", nullptr));
        toolButtonStoreOnlyOK->setText(QCoreApplication::translate("ImageBankListForm", "Store only OK", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetImages->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ImageBankListForm", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetImages->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ImageBankListForm", "InspectionID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetImages->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ImageBankListForm", "Result", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageBankListForm: public Ui_ImageBankListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEBANKLISTFORM_H
