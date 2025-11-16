/********************************************************************************
** Form generated from reading UI file 'FormDirectionOnEachPage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMDIRECTIONONEACHPAGE_H
#define UI_FORMDIRECTIONONEACHPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormDirectionOnEachPage
{
public:
    QFrame *frameDirection;
    QPushButton *OKButton;
    QLabel *label_6;
    QPushButton *CancelButton;

    void setupUi(QWidget *FormDirectionOnEachPage)
    {
        if (FormDirectionOnEachPage->objectName().isEmpty())
            FormDirectionOnEachPage->setObjectName("FormDirectionOnEachPage");
        FormDirectionOnEachPage->resize(331, 261);
        frameDirection = new QFrame(FormDirectionOnEachPage);
        frameDirection->setObjectName("frameDirection");
        frameDirection->setGeometry(QRect(10, 20, 311, 181));
        frameDirection->setFrameShape(QFrame::NoFrame);
        frameDirection->setFrameShadow(QFrame::Plain);
        OKButton = new QPushButton(FormDirectionOnEachPage);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(20, 210, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        OKButton->setIcon(icon);
        OKButton->setAutoDefault(true);
        label_6 = new QLabel(FormDirectionOnEachPage);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 0, 311, 20));
        CancelButton = new QPushButton(FormDirectionOnEachPage);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(230, 210, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        CancelButton->setIcon(icon1);

        retranslateUi(FormDirectionOnEachPage);

        QMetaObject::connectSlotsByName(FormDirectionOnEachPage);
    } // setupUi

    void retranslateUi(QWidget *FormDirectionOnEachPage)
    {
        FormDirectionOnEachPage->setWindowTitle(QCoreApplication::translate("FormDirectionOnEachPage", "Form", nullptr));
        OKButton->setText(QCoreApplication::translate("FormDirectionOnEachPage", "OK", nullptr));
        label_6->setText(QCoreApplication::translate("FormDirectionOnEachPage", "Independent from Camera setting", nullptr));
        CancelButton->setText(QCoreApplication::translate("FormDirectionOnEachPage", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormDirectionOnEachPage: public Ui_FormDirectionOnEachPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDIRECTIONONEACHPAGE_H
