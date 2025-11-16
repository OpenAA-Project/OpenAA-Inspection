/********************************************************************************
** Form generated from reading UI file 'CopyAlgorithmDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYALGORITHMDIALOG_H
#define UI_COPYALGORITHMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CopyAlgorithmDialog
{
public:
    QFrame *frame;
    QToolButton *toolButtonRx;
    QToolButton *toolButtonTx;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QPushButton *pushButtonTxPC1;
    QPushButton *pushButtonExeTx;
    QPushButton *pushButtonTxPC2;
    QPushButton *pushButtonTxPC3;
    QPushButton *pushButtonTxPC4;

    void setupUi(QDialog *CopyAlgorithmDialog)
    {
        if (CopyAlgorithmDialog->objectName().isEmpty())
            CopyAlgorithmDialog->setObjectName("CopyAlgorithmDialog");
        CopyAlgorithmDialog->resize(331, 286);
        frame = new QFrame(CopyAlgorithmDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 331, 71));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonRx = new QToolButton(frame);
        toolButtonRx->setObjectName("toolButtonRx");
        toolButtonRx->setGeometry(QRect(10, 10, 151, 51));
        QFont font;
        font.setPointSize(16);
        toolButtonRx->setFont(font);
        toolButtonRx->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        toolButtonRx->setCheckable(true);
        toolButtonRx->setChecked(true);
        toolButtonRx->setAutoExclusive(true);
        toolButtonTx = new QToolButton(frame);
        toolButtonTx->setObjectName("toolButtonTx");
        toolButtonTx->setGeometry(QRect(170, 10, 151, 51));
        toolButtonTx->setFont(font);
        toolButtonTx->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QToolButton:checked { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 128, 128, 255), stop:1 rgba(141, 96, 96, 255));\n"
"}"));
        toolButtonTx->setCheckable(true);
        toolButtonTx->setAutoExclusive(true);
        stackedWidget = new QStackedWidget(CopyAlgorithmDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 70, 331, 211));
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        pushButtonTxPC1 = new QPushButton(page_2);
        pushButtonTxPC1->setObjectName("pushButtonTxPC1");
        pushButtonTxPC1->setGeometry(QRect(20, 10, 191, 41));
        pushButtonTxPC1->setFont(font);
        pushButtonTxPC1->setCheckable(true);
        pushButtonExeTx = new QPushButton(page_2);
        pushButtonExeTx->setObjectName("pushButtonExeTx");
        pushButtonExeTx->setGeometry(QRect(230, 10, 80, 91));
        pushButtonExeTx->setFont(font);
        pushButtonTxPC2 = new QPushButton(page_2);
        pushButtonTxPC2->setObjectName("pushButtonTxPC2");
        pushButtonTxPC2->setGeometry(QRect(20, 60, 191, 41));
        pushButtonTxPC2->setFont(font);
        pushButtonTxPC2->setCheckable(true);
        pushButtonTxPC3 = new QPushButton(page_2);
        pushButtonTxPC3->setObjectName("pushButtonTxPC3");
        pushButtonTxPC3->setGeometry(QRect(20, 110, 191, 41));
        pushButtonTxPC3->setFont(font);
        pushButtonTxPC3->setCheckable(true);
        pushButtonTxPC4 = new QPushButton(page_2);
        pushButtonTxPC4->setObjectName("pushButtonTxPC4");
        pushButtonTxPC4->setGeometry(QRect(20, 160, 191, 41));
        pushButtonTxPC4->setFont(font);
        pushButtonTxPC4->setCheckable(true);
        stackedWidget->addWidget(page_2);

        retranslateUi(CopyAlgorithmDialog);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CopyAlgorithmDialog);
    } // setupUi

    void retranslateUi(QDialog *CopyAlgorithmDialog)
    {
        CopyAlgorithmDialog->setWindowTitle(QCoreApplication::translate("CopyAlgorithmDialog", "Copy", nullptr));
        toolButtonRx->setText(QCoreApplication::translate("CopyAlgorithmDialog", "\345\217\227\343\201\221\345\217\226\343\202\213", nullptr));
        toolButtonTx->setText(QCoreApplication::translate("CopyAlgorithmDialog", "\351\200\201\343\202\213", nullptr));
        pushButtonTxPC1->setText(QCoreApplication::translate("CopyAlgorithmDialog", "Top", nullptr));
        pushButtonExeTx->setText(QCoreApplication::translate("CopyAlgorithmDialog", "\351\200\201\344\277\241", nullptr));
        pushButtonTxPC2->setText(QCoreApplication::translate("CopyAlgorithmDialog", "Top", nullptr));
        pushButtonTxPC3->setText(QCoreApplication::translate("CopyAlgorithmDialog", "Top", nullptr));
        pushButtonTxPC4->setText(QCoreApplication::translate("CopyAlgorithmDialog", "Top", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CopyAlgorithmDialog: public Ui_CopyAlgorithmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYALGORITHMDIALOG_H
