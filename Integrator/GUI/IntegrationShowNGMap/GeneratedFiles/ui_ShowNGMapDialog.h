/********************************************************************************
** Form generated from reading UI file 'ShowNGMapDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWNGMAPDIALOG_H
#define UI_SHOWNGMAPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShowNGMapDialog
{
public:
    QFrame *frame;
    QPushButton *pushButtonClose;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxMatrixSizeMM;
    QPushButton *pushButtonReview;
    QProgressBar *progressBar;

    void setupUi(QDialog *ShowNGMapDialog)
    {
        if (ShowNGMapDialog->objectName().isEmpty())
            ShowNGMapDialog->setObjectName("ShowNGMapDialog");
        ShowNGMapDialog->resize(671, 732);
        frame = new QFrame(ShowNGMapDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 660, 671, 71));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonClose = new QPushButton(frame);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(560, 10, 101, 51));
        QFont font;
        font.setPointSize(12);
        pushButtonClose->setFont(font);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 111, 20));
        label->setFont(font);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxMatrixSizeMM = new QDoubleSpinBox(frame);
        doubleSpinBoxMatrixSizeMM->setObjectName("doubleSpinBoxMatrixSizeMM");
        doubleSpinBoxMatrixSizeMM->setGeometry(QRect(10, 30, 111, 31));
        doubleSpinBoxMatrixSizeMM->setFont(font);
        doubleSpinBoxMatrixSizeMM->setMinimum(0.010000000000000);
        doubleSpinBoxMatrixSizeMM->setMaximum(1000.000000000000000);
        doubleSpinBoxMatrixSizeMM->setSingleStep(1.000000000000000);
        doubleSpinBoxMatrixSizeMM->setValue(10.000000000000000);
        pushButtonReview = new QPushButton(frame);
        pushButtonReview->setObjectName("pushButtonReview");
        pushButtonReview->setGeometry(QRect(130, 10, 101, 51));
        pushButtonReview->setFont(font);
        progressBar = new QProgressBar(frame);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(240, 22, 291, 31));
        progressBar->setValue(24);

        retranslateUi(ShowNGMapDialog);

        QMetaObject::connectSlotsByName(ShowNGMapDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowNGMapDialog)
    {
        ShowNGMapDialog->setWindowTitle(QCoreApplication::translate("ShowNGMapDialog", "Dialog", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ShowNGMapDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        label->setText(QCoreApplication::translate("ShowNGMapDialog", "\345\215\207\347\233\256\343\202\265\343\202\244\343\202\272", nullptr));
        pushButtonReview->setText(QCoreApplication::translate("ShowNGMapDialog", "\345\206\215\350\241\250\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowNGMapDialog: public Ui_ShowNGMapDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWNGMAPDIALOG_H
