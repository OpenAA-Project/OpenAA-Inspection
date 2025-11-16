/********************************************************************************
** Form generated from reading UI file 'ImageTransformerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGETRANSFORMERDIALOG_H
#define UI_IMAGETRANSFORMERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ImageTransformerDialog
{
public:
    QListWidget *listWidgetPages;
    QLabel *label;
    QPushButton *pushButtonUpsideDown;
    QPushButton *pushButtonLeftsideRight;
    QPushButton *pushButton_3;
    QCheckBox *checkBoxMasterImage;
    QCheckBox *checkBoxTargetImage;

    void setupUi(QDialog *ImageTransformerDialog)
    {
        if (ImageTransformerDialog->objectName().isEmpty())
            ImageTransformerDialog->setObjectName("ImageTransformerDialog");
        ImageTransformerDialog->resize(284, 289);
        listWidgetPages = new QListWidget(ImageTransformerDialog);
        listWidgetPages->setObjectName("listWidgetPages");
        listWidgetPages->setGeometry(QRect(10, 30, 91, 241));
        listWidgetPages->setSelectionMode(QAbstractItemView::MultiSelection);
        listWidgetPages->setSelectionBehavior(QAbstractItemView::SelectRows);
        label = new QLabel(ImageTransformerDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        pushButtonUpsideDown = new QPushButton(ImageTransformerDialog);
        pushButtonUpsideDown->setObjectName("pushButtonUpsideDown");
        pushButtonUpsideDown->setGeometry(QRect(120, 60, 151, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Rotate2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpsideDown->setIcon(icon);
        pushButtonLeftsideRight = new QPushButton(ImageTransformerDialog);
        pushButtonLeftsideRight->setObjectName("pushButtonLeftsideRight");
        pushButtonLeftsideRight->setGeometry(QRect(120, 110, 151, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Rotate.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLeftsideRight->setIcon(icon1);
        pushButton_3 = new QPushButton(ImageTransformerDialog);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(180, 230, 91, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_3->setIcon(icon2);
        checkBoxMasterImage = new QCheckBox(ImageTransformerDialog);
        checkBoxMasterImage->setObjectName("checkBoxMasterImage");
        checkBoxMasterImage->setGeometry(QRect(120, 10, 141, 17));
        checkBoxMasterImage->setChecked(true);
        checkBoxTargetImage = new QCheckBox(ImageTransformerDialog);
        checkBoxTargetImage->setObjectName("checkBoxTargetImage");
        checkBoxTargetImage->setGeometry(QRect(120, 30, 141, 17));
        checkBoxTargetImage->setChecked(true);

        retranslateUi(ImageTransformerDialog);

        QMetaObject::connectSlotsByName(ImageTransformerDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageTransformerDialog)
    {
        ImageTransformerDialog->setWindowTitle(QCoreApplication::translate("ImageTransformerDialog", "Image Transformer", nullptr));
        label->setText(QCoreApplication::translate("ImageTransformerDialog", "Page", nullptr));
        pushButtonUpsideDown->setText(QCoreApplication::translate("ImageTransformerDialog", "\344\270\212\344\270\213\345\217\215\350\273\242", nullptr));
        pushButtonLeftsideRight->setText(QCoreApplication::translate("ImageTransformerDialog", "\345\267\246\345\217\263\345\217\215\350\273\242", nullptr));
        pushButton_3->setText(QCoreApplication::translate("ImageTransformerDialog", "Close", nullptr));
        checkBoxMasterImage->setText(QCoreApplication::translate("ImageTransformerDialog", "Master Image", nullptr));
        checkBoxTargetImage->setText(QCoreApplication::translate("ImageTransformerDialog", "Target Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageTransformerDialog: public Ui_ImageTransformerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGETRANSFORMERDIALOG_H
