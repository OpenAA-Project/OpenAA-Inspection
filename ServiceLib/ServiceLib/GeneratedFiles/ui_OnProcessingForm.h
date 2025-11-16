/********************************************************************************
** Form generated from reading UI file 'OnProcessingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONPROCESSINGFORM_H
#define UI_ONPROCESSINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OnProcessingForm
{
public:
    QFrame *frameBottom;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonCancel;
    QLabel *labelMessage;
    QLabel *labelProcessing;
    QLabel *label;
    QProgressBar *progressBarProcessing;

    void setupUi(QWidget *OnProcessingForm)
    {
        if (OnProcessingForm->objectName().isEmpty())
            OnProcessingForm->setObjectName("OnProcessingForm");
        OnProcessingForm->resize(368, 143);
        frameBottom = new QFrame(OnProcessingForm);
        frameBottom->setObjectName("frameBottom");
        frameBottom->setGeometry(QRect(10, 80, 331, 61));
        frameBottom->setFrameShape(QFrame::StyledPanel);
        frameBottom->setFrameShadow(QFrame::Raised);
        pushButtonClose = new QPushButton(frameBottom);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(190, 30, 101, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon);
        pushButtonCancel = new QPushButton(frameBottom);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(60, 30, 101, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        pushButtonCancel->setAutoDefault(true);
        labelMessage = new QLabel(frameBottom);
        labelMessage->setObjectName("labelMessage");
        labelMessage->setGeometry(QRect(10, 10, 321, 20));
        labelMessage->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelProcessing = new QLabel(OnProcessingForm);
        labelProcessing->setObjectName("labelProcessing");
        labelProcessing->setGeometry(QRect(20, 10, 321, 26));
        QFont font;
        font.setPointSize(18);
        labelProcessing->setFont(font);
        labelProcessing->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(OnProcessingForm);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 50, 62, 15));
        progressBarProcessing = new QProgressBar(OnProcessingForm);
        progressBarProcessing->setObjectName("progressBarProcessing");
        progressBarProcessing->setGeometry(QRect(90, 50, 241, 23));
        progressBarProcessing->setMaximum(0);
        progressBarProcessing->setValue(0);

        retranslateUi(OnProcessingForm);

        pushButtonCancel->setDefault(true);


        QMetaObject::connectSlotsByName(OnProcessingForm);
    } // setupUi

    void retranslateUi(QWidget *OnProcessingForm)
    {
        OnProcessingForm->setWindowTitle(QCoreApplication::translate("OnProcessingForm", "Form", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("OnProcessingForm", "\351\226\211\343\201\230\343\202\213", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("OnProcessingForm", "Cancel", nullptr));
        labelMessage->setText(QCoreApplication::translate("OnProcessingForm", "\345\207\246\347\220\206\344\270\255", nullptr));
        labelProcessing->setText(QCoreApplication::translate("OnProcessingForm", "On Processing...", nullptr));
        label->setText(QCoreApplication::translate("OnProcessingForm", "Page 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OnProcessingForm: public Ui_OnProcessingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONPROCESSINGFORM_H
