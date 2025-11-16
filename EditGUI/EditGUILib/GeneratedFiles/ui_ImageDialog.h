/********************************************************************************
** Form generated from reading UI file 'ImageDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEDIALOG_H
#define UI_IMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ImageDialog
{
public:
    QPushButton *pushButtonSave;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonClear;
    QLabel *labelImage;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *ImageDialog)
    {
        if (ImageDialog->objectName().isEmpty())
            ImageDialog->setObjectName("ImageDialog");
        ImageDialog->resize(222, 286);
        pushButtonSave = new QPushButton(ImageDialog);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(10, 220, 91, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSave->setIcon(icon);
        pushButtonLoad = new QPushButton(ImageDialog);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(120, 220, 91, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoad->setIcon(icon1);
        pushButtonClear = new QPushButton(ImageDialog);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(10, 250, 91, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClear->setIcon(icon2);
        labelImage = new QLabel(ImageDialog);
        labelImage->setObjectName("labelImage");
        labelImage->setGeometry(QRect(10, 10, 201, 201));
        labelImage->setFrameShape(QFrame::Panel);
        labelImage->setFrameShadow(QFrame::Sunken);
        labelImage->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(ImageDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(120, 250, 91, 23));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon3);

        retranslateUi(ImageDialog);

        QMetaObject::connectSlotsByName(ImageDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageDialog)
    {
        ImageDialog->setWindowTitle(QCoreApplication::translate("ImageDialog", "Dialog", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("ImageDialog", "Save", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("ImageDialog", "Load", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("ImageDialog", "Clear", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("ImageDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageDialog: public Ui_ImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEDIALOG_H
