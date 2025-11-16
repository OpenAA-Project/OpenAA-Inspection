/********************************************************************************
** Form generated from reading UI file 'RegistColorLibForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTCOLORLIBFORM_H
#define UI_REGISTCOLORLIBFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistColorLibForm
{
public:
    QFrame *frameRegistPanel;
    QStackedWidget *stackedWidget;
    QWidget *RGB;
    QFrame *frameRGBPanel;
    QWidget *ColorSpace;
    QFrame *frameColorPanel;
    QPushButton *pushButtonClose;

    void setupUi(QWidget *RegistColorLibForm)
    {
        if (RegistColorLibForm->objectName().isEmpty())
            RegistColorLibForm->setObjectName("RegistColorLibForm");
        RegistColorLibForm->resize(648, 465);
        frameRegistPanel = new QFrame(RegistColorLibForm);
        frameRegistPanel->setObjectName("frameRegistPanel");
        frameRegistPanel->setGeometry(QRect(430, 10, 204, 444));
        frameRegistPanel->setFrameShape(QFrame::StyledPanel);
        frameRegistPanel->setFrameShadow(QFrame::Raised);
        stackedWidget = new QStackedWidget(RegistColorLibForm);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(-10, 0, 431, 411));
        RGB = new QWidget();
        RGB->setObjectName("RGB");
        frameRGBPanel = new QFrame(RGB);
        frameRGBPanel->setObjectName("frameRGBPanel");
        frameRGBPanel->setGeometry(QRect(10, 10, 420, 356));
        frameRGBPanel->setFrameShape(QFrame::StyledPanel);
        frameRGBPanel->setFrameShadow(QFrame::Raised);
        stackedWidget->addWidget(RGB);
        ColorSpace = new QWidget();
        ColorSpace->setObjectName("ColorSpace");
        frameColorPanel = new QFrame(ColorSpace);
        frameColorPanel->setObjectName("frameColorPanel");
        frameColorPanel->setGeometry(QRect(10, 10, 420, 356));
        frameColorPanel->setFrameShape(QFrame::StyledPanel);
        frameColorPanel->setFrameShadow(QFrame::Raised);
        stackedWidget->addWidget(ColorSpace);
        pushButtonClose = new QPushButton(RegistColorLibForm);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(180, 430, 91, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon);

        retranslateUi(RegistColorLibForm);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(RegistColorLibForm);
    } // setupUi

    void retranslateUi(QWidget *RegistColorLibForm)
    {
        RegistColorLibForm->setWindowTitle(QCoreApplication::translate("RegistColorLibForm", "Form", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("RegistColorLibForm", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistColorLibForm: public Ui_RegistColorLibForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTCOLORLIBFORM_H
