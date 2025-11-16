/********************************************************************************
** Form generated from reading UI file 'LiveCameraArtCam_035IMX_WOMForm.ui'
**
** Created: Fri Feb 21 20:53:34 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIVECAMERAARTCAM_035IMX_WOMFORM_H
#define UI_LIVECAMERAARTCAM_035IMX_WOMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_LiveCameraArtCam_035IMX_WOMClass
{
public:
    QGridLayout *gridLayout;
    QLabel *lbCameraImage;

    void setupUi(QWidget *LiveCameraArtCam_035IMX_WOMClass)
    {
        if (LiveCameraArtCam_035IMX_WOMClass->objectName().isEmpty())
            LiveCameraArtCam_035IMX_WOMClass->setObjectName(QString::fromUtf8("LiveCameraArtCam_035IMX_WOMClass"));
        LiveCameraArtCam_035IMX_WOMClass->resize(642, 488);
        gridLayout = new QGridLayout(LiveCameraArtCam_035IMX_WOMClass);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbCameraImage = new QLabel(LiveCameraArtCam_035IMX_WOMClass);
        lbCameraImage->setObjectName(QString::fromUtf8("lbCameraImage"));
        lbCameraImage->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbCameraImage, 0, 0, 1, 1);


        retranslateUi(LiveCameraArtCam_035IMX_WOMClass);

        QMetaObject::connectSlotsByName(LiveCameraArtCam_035IMX_WOMClass);
    } // setupUi

    void retranslateUi(QWidget *LiveCameraArtCam_035IMX_WOMClass)
    {
        LiveCameraArtCam_035IMX_WOMClass->setWindowTitle(QApplication::translate("LiveCameraArtCam_035IMX_WOMClass", "LiveCameraArtCam_035IMX_WOM", 0, QApplication::UnicodeUTF8));
        lbCameraImage->setText(QApplication::translate("LiveCameraArtCam_035IMX_WOMClass", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LiveCameraArtCam_035IMX_WOMClass: public Ui_LiveCameraArtCam_035IMX_WOMClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVECAMERAARTCAM_035IMX_WOMFORM_H
