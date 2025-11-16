/********************************************************************************
** Form generated from reading UI file 'WaitingConnectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITINGCONNECTIONFORM_H
#define UI_WAITINGCONNECTIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaitingConnectionForm
{
public:
    QLabel *label;
    QFrame *frame;
    QToolButton *toolButtonStopLoading;

    void setupUi(QWidget *WaitingConnectionForm)
    {
        if (WaitingConnectionForm->objectName().isEmpty())
            WaitingConnectionForm->setObjectName("WaitingConnectionForm");
        WaitingConnectionForm->resize(367, 203);
        label = new QLabel(WaitingConnectionForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 341, 31));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        frame = new QFrame(WaitingConnectionForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 110, 361, 80));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonStopLoading = new QToolButton(WaitingConnectionForm);
        toolButtonStopLoading->setObjectName("toolButtonStopLoading");
        toolButtonStopLoading->setGeometry(QRect(50, 60, 271, 41));
        toolButtonStopLoading->setCheckable(true);
        toolButtonStopLoading->setChecked(false);

        retranslateUi(WaitingConnectionForm);

        QMetaObject::connectSlotsByName(WaitingConnectionForm);
    } // setupUi

    void retranslateUi(QWidget *WaitingConnectionForm)
    {
        WaitingConnectionForm->setWindowTitle(QCoreApplication::translate("WaitingConnectionForm", "Message", nullptr));
        label->setText(QCoreApplication::translate("WaitingConnectionForm", "\346\216\245\347\266\232\345\276\205\346\251\237\344\270\255", nullptr));
        toolButtonStopLoading->setText(QCoreApplication::translate("WaitingConnectionForm", "\346\234\200\345\276\214\343\201\256\343\203\236\343\202\271\343\202\277\343\203\274\343\203\207\343\203\274\343\202\277\350\252\255\350\276\274\343\202\222\344\270\255\346\255\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WaitingConnectionForm: public Ui_WaitingConnectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITINGCONNECTIONFORM_H
