/********************************************************************************
** Form generated from reading UI file 'VideoControllerForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOCONTROLLERFORM_H
#define UI_VIDEOCONTROLLERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_VideoControllerForm
{
public:
    QToolButton *toolButtonRunMovie;
    QToolButton *toolButtonForwardMovie;
    QSlider *horizontalSliderMovie;
    QToolButton *toolButtonBackwardMovie;
    QToolButton *toolButtonOpenFile;

    void setupUi(GUIFormBase *VideoControllerForm)
    {
        if (VideoControllerForm->objectName().isEmpty())
            VideoControllerForm->setObjectName("VideoControllerForm");
        VideoControllerForm->resize(568, 48);
        toolButtonRunMovie = new QToolButton(VideoControllerForm);
        toolButtonRunMovie->setObjectName("toolButtonRunMovie");
        toolButtonRunMovie->setGeometry(QRect(50, 0, 42, 42));
        QFont font;
        font.setPointSize(22);
        toolButtonRunMovie->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/PlayN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/PauseS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonRunMovie->setIcon(icon);
        toolButtonRunMovie->setIconSize(QSize(42, 42));
        toolButtonRunMovie->setCheckable(true);
        toolButtonRunMovie->setChecked(false);
        toolButtonRunMovie->setAutoExclusive(false);
        toolButtonForwardMovie = new QToolButton(VideoControllerForm);
        toolButtonForwardMovie->setObjectName("toolButtonForwardMovie");
        toolButtonForwardMovie->setGeometry(QRect(100, 0, 41, 42));
        toolButtonForwardMovie->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/ForwardN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon1.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/ForwardS.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        toolButtonForwardMovie->setIcon(icon1);
        toolButtonForwardMovie->setIconSize(QSize(42, 42));
        toolButtonForwardMovie->setCheckable(true);
        toolButtonForwardMovie->setChecked(false);
        toolButtonForwardMovie->setAutoExclusive(false);
        horizontalSliderMovie = new QSlider(VideoControllerForm);
        horizontalSliderMovie->setObjectName("horizontalSliderMovie");
        horizontalSliderMovie->setGeometry(QRect(150, 10, 351, 22));
        horizontalSliderMovie->setOrientation(Qt::Horizontal);
        toolButtonBackwardMovie = new QToolButton(VideoControllerForm);
        toolButtonBackwardMovie->setObjectName("toolButtonBackwardMovie");
        toolButtonBackwardMovie->setGeometry(QRect(0, 0, 42, 42));
        toolButtonBackwardMovie->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Normal/Resources/Normal/RewindN.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon2.addFile(QString::fromUtf8(":/Resources/Select/Resources/Select/RewindS.png"), QSize(), QIcon::Mode::Disabled, QIcon::State::Off);
        toolButtonBackwardMovie->setIcon(icon2);
        toolButtonBackwardMovie->setIconSize(QSize(42, 42));
        toolButtonBackwardMovie->setCheckable(true);
        toolButtonBackwardMovie->setChecked(false);
        toolButtonBackwardMovie->setAutoExclusive(false);
        toolButtonOpenFile = new QToolButton(VideoControllerForm);
        toolButtonOpenFile->setObjectName("toolButtonOpenFile");
        toolButtonOpenFile->setGeometry(QRect(520, 0, 42, 42));
        toolButtonOpenFile->setFont(font);
        toolButtonOpenFile->setIconSize(QSize(42, 42));
        toolButtonOpenFile->setCheckable(false);
        toolButtonOpenFile->setChecked(false);

        retranslateUi(VideoControllerForm);

        QMetaObject::connectSlotsByName(VideoControllerForm);
    } // setupUi

    void retranslateUi(GUIFormBase *VideoControllerForm)
    {
        VideoControllerForm->setWindowTitle(QCoreApplication::translate("VideoControllerForm", "Form", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonRunMovie->setToolTip(QCoreApplication::translate("VideoControllerForm", "\345\206\215\347\224\237\343\203\273\344\270\200\346\231\202\345\201\234\346\255\242", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonRunMovie->setText(QCoreApplication::translate("VideoControllerForm", "?", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonForwardMovie->setToolTip(QCoreApplication::translate("VideoControllerForm", "\346\227\251\351\200\201\343\202\212", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonForwardMovie->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonBackwardMovie->setToolTip(QCoreApplication::translate("VideoControllerForm", "\345\267\273\343\201\215\346\210\273\343\201\227", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonBackwardMovie->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonOpenFile->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        toolButtonOpenFile->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VideoControllerForm: public Ui_VideoControllerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOCONTROLLERFORM_H
