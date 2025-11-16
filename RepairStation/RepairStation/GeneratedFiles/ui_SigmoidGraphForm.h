/********************************************************************************
** Form generated from reading UI file 'SigmoidGraphForm.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGMOIDGRAPHFORM_H
#define UI_SIGMOIDGRAPHFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QWidget>
#include "passwordpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_SigmoidGraphFormClass
{
public:
    QDockWidget *dwSigGraph;
    QWidget *dockWidgetContents;
    PasswordPushButton *pbOK;
    PasswordPushButton *pbCancel;
    QFrame *frame;
    QSpinBox *sbBrightness;
    QLineEdit *leVolume;
    QLineEdit *leBrightness;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *dsbVolume;

    void setupUi(QDialog *SigmoidGraphFormClass)
    {
        if (SigmoidGraphFormClass->objectName().isEmpty())
            SigmoidGraphFormClass->setObjectName(QString::fromUtf8("SigmoidGraphFormClass"));
        SigmoidGraphFormClass->resize(752, 690);
        dwSigGraph = new QDockWidget(SigmoidGraphFormClass);
        dwSigGraph->setObjectName(QString::fromUtf8("dwSigGraph"));
        dwSigGraph->setGeometry(QRect(140, 10, 601, 622));
        dwSigGraph->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dwSigGraph->setWidget(dockWidgetContents);
        pbOK = new PasswordPushButton(SigmoidGraphFormClass);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));
        pbOK->setGeometry(QRect(540, 640, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbOK->setIcon(icon);
        pbCancel = new PasswordPushButton(SigmoidGraphFormClass);
        pbCancel->setObjectName(QString::fromUtf8("pbCancel"));
        pbCancel->setGeometry(QRect(650, 640, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbCancel->setIcon(icon1);
        frame = new QFrame(SigmoidGraphFormClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 120, 621));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        sbBrightness = new QSpinBox(frame);
        sbBrightness->setObjectName(QString::fromUtf8("sbBrightness"));
        sbBrightness->setGeometry(QRect(20, 170, 81, 22));
        sbBrightness->setMaximum(255);
        leVolume = new QLineEdit(frame);
        leVolume->setObjectName(QString::fromUtf8("leVolume"));
        leVolume->setGeometry(QRect(20, 50, 81, 20));
        leVolume->setAlignment(Qt::AlignCenter);
        leVolume->setReadOnly(true);
        leBrightness = new QLineEdit(frame);
        leBrightness->setObjectName(QString::fromUtf8("leBrightness"));
        leBrightness->setGeometry(QRect(20, 150, 81, 20));
        leBrightness->setAlignment(Qt::AlignCenter);
        leBrightness->setReadOnly(true);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(19, 98, 91, 16));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 194, 54, 16));
        dsbVolume = new QDoubleSpinBox(frame);
        dsbVolume->setObjectName(QString::fromUtf8("dsbVolume"));
        dsbVolume->setGeometry(QRect(20, 70, 81, 22));
        dsbVolume->setMaximum(1e+06);

        retranslateUi(SigmoidGraphFormClass);

        QMetaObject::connectSlotsByName(SigmoidGraphFormClass);
    } // setupUi

    void retranslateUi(QDialog *SigmoidGraphFormClass)
    {
        SigmoidGraphFormClass->setWindowTitle(QApplication::translate("SigmoidGraphFormClass", "SigmoidGraphForm", 0, QApplication::UnicodeUTF8));
        pbOK->setText(QApplication::translate("SigmoidGraphFormClass", "OK", 0, QApplication::UnicodeUTF8));
        pbCancel->setText(QApplication::translate("SigmoidGraphFormClass", "Cancel", 0, QApplication::UnicodeUTF8));
        leVolume->setText(QApplication::translate("SigmoidGraphFormClass", "Volume", 0, QApplication::UnicodeUTF8));
        leBrightness->setText(QApplication::translate("SigmoidGraphFormClass", "Brightness", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SigmoidGraphFormClass", "( 0 - 999999.99)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SigmoidGraphFormClass", "( 0 - 255 )", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SigmoidGraphFormClass: public Ui_SigmoidGraphFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGMOIDGRAPHFORM_H
