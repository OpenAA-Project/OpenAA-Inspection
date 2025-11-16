/********************************************************************************
** Form generated from reading UI file 'PropertyMultiFileMapForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYMULTIFILEMAPFORM_H
#define UI_PROPERTYMULTIFILEMAPFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyMultiFileMapForm
{
public:
    QPushButton *pushButton_2;
    QFrame *frame;
    QLabel *label_2;
    QLineEdit *lineEditPosX;
    QLineEdit *lineEditPosY;
    QLineEdit *lineEditFileName;
    QLabel *label_3;
    QLineEdit *lineEditOverlapY;
    QLineEdit *lineEditOverlapX;
    QLabel *label_4;
    QFrame *frame_2;
    QLineEdit *lineEditInspName;
    QLabel *label_6;
    QLineEdit *lineEditImgNum_Y;
    QLineEdit *lineEditImgNum_X;
    QLabel *label_7;
    QLineEdit *lineEditProduct;
    QLabel *label_8;

    void setupUi(GUIFormBase *PropertyMultiFileMapForm)
    {
        if (PropertyMultiFileMapForm->objectName().isEmpty())
            PropertyMultiFileMapForm->setObjectName("PropertyMultiFileMapForm");
        PropertyMultiFileMapForm->resize(400, 700);
        pushButton_2 = new QPushButton(PropertyMultiFileMapForm);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(100, 20, 191, 46));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Library.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_2->setIcon(icon);
        frame = new QFrame(PropertyMultiFileMapForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 410, 381, 271));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 191, 24));
        lineEditPosX = new QLineEdit(frame);
        lineEditPosX->setObjectName("lineEditPosX");
        lineEditPosX->setGeometry(QRect(50, 30, 113, 30));
        lineEditPosY = new QLineEdit(frame);
        lineEditPosY->setObjectName("lineEditPosY");
        lineEditPosY->setGeometry(QRect(190, 30, 113, 30));
        lineEditFileName = new QLineEdit(frame);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(50, 110, 321, 30));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 80, 191, 24));
        lineEditOverlapY = new QLineEdit(frame);
        lineEditOverlapY->setObjectName("lineEditOverlapY");
        lineEditOverlapY->setGeometry(QRect(190, 180, 113, 30));
        lineEditOverlapX = new QLineEdit(frame);
        lineEditOverlapX->setObjectName("lineEditOverlapX");
        lineEditOverlapX->setGeometry(QRect(50, 180, 113, 30));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 150, 191, 24));
        frame_2 = new QFrame(PropertyMultiFileMapForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 80, 381, 271));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        lineEditInspName = new QLineEdit(frame_2);
        lineEditInspName->setObjectName("lineEditInspName");
        lineEditInspName->setGeometry(QRect(40, 110, 321, 30));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 80, 191, 24));
        lineEditImgNum_Y = new QLineEdit(frame_2);
        lineEditImgNum_Y->setObjectName("lineEditImgNum_Y");
        lineEditImgNum_Y->setGeometry(QRect(180, 190, 113, 30));
        lineEditImgNum_X = new QLineEdit(frame_2);
        lineEditImgNum_X->setObjectName("lineEditImgNum_X");
        lineEditImgNum_X->setGeometry(QRect(40, 190, 113, 30));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 150, 261, 24));
        lineEditProduct = new QLineEdit(frame_2);
        lineEditProduct->setObjectName("lineEditProduct");
        lineEditProduct->setGeometry(QRect(40, 30, 321, 30));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 0, 191, 24));

        retranslateUi(PropertyMultiFileMapForm);

        QMetaObject::connectSlotsByName(PropertyMultiFileMapForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyMultiFileMapForm)
    {
        PropertyMultiFileMapForm->setWindowTitle(QCoreApplication::translate("PropertyMultiFileMapForm", "Property MultiFileMap", nullptr));
        pushButton_2->setText(QCoreApplication::translate("PropertyMultiFileMapForm", "Library", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyMultiFileMapForm", "Position", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyMultiFileMapForm", "FileName", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyMultiFileMapForm", "Overlap", nullptr));
        label_6->setText(QCoreApplication::translate("PropertyMultiFileMapForm", "Path / Folder", nullptr));
        label_7->setText(QCoreApplication::translate("PropertyMultiFileMapForm", "\347\224\273\345\203\217\351\207\215\343\201\255\345\220\210\343\202\217\343\201\233\346\236\232\346\225\260", nullptr));
        label_8->setText(QCoreApplication::translate("PropertyMultiFileMapForm", "\350\243\275\345\223\201\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyMultiFileMapForm: public Ui_PropertyMultiFileMapForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYMULTIFILEMAPFORM_H
