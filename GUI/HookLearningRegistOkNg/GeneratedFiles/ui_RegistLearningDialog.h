/********************************************************************************
** Form generated from reading UI file 'RegistLearningDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTLEARNINGDIALOG_H
#define UI_REGISTLEARNINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RegistLearningDialog
{
public:
    QFrame *frame;
    QPushButton *pushButtonOK;
    QFrame *frame_2;
    QPushButton *pushButtonNG;
    QFrame *frame_3;
    QPushButton *pushButtonCancel;
    QSlider *horizontalSliderPriority;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QSpinBox *spinBoxPriority;

    void setupUi(QDialog *RegistLearningDialog)
    {
        if (RegistLearningDialog->objectName().isEmpty())
            RegistLearningDialog->setObjectName("RegistLearningDialog");
        RegistLearningDialog->resize(392, 154);
        frame = new QFrame(RegistLearningDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 151, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(frame);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(0, 0, 151, 34));
        frame_2 = new QFrame(RegistLearningDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(170, 10, 151, 41));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButtonNG = new QPushButton(frame_2);
        pushButtonNG->setObjectName("pushButtonNG");
        pushButtonNG->setGeometry(QRect(0, 0, 151, 34));
        frame_3 = new QFrame(RegistLearningDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(0, 60, 391, 91));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        pushButtonCancel = new QPushButton(frame_3);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 50, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        horizontalSliderPriority = new QSlider(frame_3);
        horizontalSliderPriority->setObjectName("horizontalSliderPriority");
        horizontalSliderPriority->setGeometry(QRect(120, 20, 160, 16));
        horizontalSliderPriority->setMaximum(100);
        horizontalSliderPriority->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 20, 41, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(290, 20, 31, 20));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 71, 20));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPriority = new QSpinBox(frame_3);
        spinBoxPriority->setObjectName("spinBoxPriority");
        spinBoxPriority->setGeometry(QRect(330, 11, 51, 31));
        spinBoxPriority->setMaximum(100);

        retranslateUi(RegistLearningDialog);

        QMetaObject::connectSlotsByName(RegistLearningDialog);
    } // setupUi

    void retranslateUi(QDialog *RegistLearningDialog)
    {
        RegistLearningDialog->setWindowTitle(QCoreApplication::translate("RegistLearningDialog", "OK/NG Registration", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RegistLearningDialog", "OK\343\200\200\347\231\273\351\214\262", nullptr));
        pushButtonNG->setText(QCoreApplication::translate("RegistLearningDialog", "NG\343\200\200\347\231\273\351\214\262", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RegistLearningDialog", "Cancel", nullptr));
        label_4->setText(QCoreApplication::translate("RegistLearningDialog", "\351\253\230\343\201\204", nullptr));
        label_3->setText(QCoreApplication::translate("RegistLearningDialog", "\344\275\216\343\201\204", nullptr));
        label_2->setText(QCoreApplication::translate("RegistLearningDialog", "\351\207\215\350\246\201\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistLearningDialog: public Ui_RegistLearningDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTLEARNINGDIALOG_H
