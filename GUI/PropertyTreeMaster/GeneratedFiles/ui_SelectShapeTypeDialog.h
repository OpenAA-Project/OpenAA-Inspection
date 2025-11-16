/********************************************************************************
** Form generated from reading UI file 'SelectShapeTypeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTSHAPETYPEDIALOG_H
#define UI_SELECTSHAPETYPEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SelectShapeTypeDialog
{
public:
    QDoubleSpinBox *doubleSpinBoxThreShape;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxThreColor;
    QPushButton *pushButtonSetColorArea;
    QFrame *frame;
    QPushButton *pushButtonSetShapeArea;
    QLabel *label_3;
    QSpinBox *spinBoxSearchDot;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SelectShapeTypeDialog)
    {
        if (SelectShapeTypeDialog->objectName().isEmpty())
            SelectShapeTypeDialog->setObjectName("SelectShapeTypeDialog");
        SelectShapeTypeDialog->resize(215, 273);
        doubleSpinBoxThreShape = new QDoubleSpinBox(SelectShapeTypeDialog);
        doubleSpinBoxThreShape->setObjectName("doubleSpinBoxThreShape");
        doubleSpinBoxThreShape->setGeometry(QRect(10, 30, 81, 22));
        doubleSpinBoxThreShape->setMaximum(1.000000000000000);
        label = new QLabel(SelectShapeTypeDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 16));
        label_2 = new QLabel(SelectShapeTypeDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 10, 91, 16));
        doubleSpinBoxThreColor = new QDoubleSpinBox(SelectShapeTypeDialog);
        doubleSpinBoxThreColor->setObjectName("doubleSpinBoxThreColor");
        doubleSpinBoxThreColor->setGeometry(QRect(110, 30, 81, 22));
        doubleSpinBoxThreColor->setMaximum(1.000000000000000);
        pushButtonSetColorArea = new QPushButton(SelectShapeTypeDialog);
        pushButtonSetColorArea->setObjectName("pushButtonSetColorArea");
        pushButtonSetColorArea->setGeometry(QRect(20, 70, 161, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetColorArea->setIcon(icon);
        frame = new QFrame(SelectShapeTypeDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 120, 181, 91));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        pushButtonSetShapeArea = new QPushButton(frame);
        pushButtonSetShapeArea->setObjectName("pushButtonSetShapeArea");
        pushButtonSetShapeArea->setGeometry(QRect(10, 10, 161, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Block.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetShapeArea->setIcon(icon1);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 60, 71, 21));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxSearchDot = new QSpinBox(frame);
        spinBoxSearchDot->setObjectName("spinBoxSearchDot");
        spinBoxSearchDot->setGeometry(QRect(100, 60, 61, 22));
        spinBoxSearchDot->setMaximum(9999);
        pushButtonCancel = new QPushButton(SelectShapeTypeDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(60, 230, 75, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon2);

        retranslateUi(SelectShapeTypeDialog);

        QMetaObject::connectSlotsByName(SelectShapeTypeDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectShapeTypeDialog)
    {
        SelectShapeTypeDialog->setWindowTitle(QCoreApplication::translate("SelectShapeTypeDialog", "\351\201\270\346\212\236", nullptr));
        label->setText(QCoreApplication::translate("SelectShapeTypeDialog", "\345\275\242\347\212\266\345\210\244\345\256\232\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        label_2->setText(QCoreApplication::translate("SelectShapeTypeDialog", "\350\211\262\345\210\244\345\256\232\343\201\227\343\201\215\343\201\204\345\200\244", nullptr));
        pushButtonSetColorArea->setText(QCoreApplication::translate("SelectShapeTypeDialog", "\350\211\262\345\210\244\345\256\232\351\240\230\345\237\237\343\201\250\343\201\227\343\201\246\350\250\255\345\256\232", nullptr));
        pushButtonSetShapeArea->setText(QCoreApplication::translate("SelectShapeTypeDialog", "\345\275\242\347\212\266\345\210\244\345\256\232\351\240\230\345\237\237\343\201\250\343\201\227\343\201\246\350\250\255\345\256\232", nullptr));
        label_3->setText(QCoreApplication::translate("SelectShapeTypeDialog", "\346\216\242\347\264\242\351\240\230\345\237\237", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectShapeTypeDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectShapeTypeDialog: public Ui_SelectShapeTypeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTSHAPETYPEDIALOG_H
