/********************************************************************************
** Form generated from reading UI file 'BrightHistogramForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRIGHTHISTOGRAMFORM_H
#define UI_BRIGHTHISTOGRAMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BrightHistogramForm
{
public:
    QFrame *frameLineGraph;
    QSpinBox *EditPickupH;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *ButtonReflect;
    QSpinBox *EditPickupL;
    QPushButton *ButtonClose;

    void setupUi(QDialog *BrightHistogramForm)
    {
        if (BrightHistogramForm->objectName().isEmpty())
            BrightHistogramForm->setObjectName("BrightHistogramForm");
        BrightHistogramForm->resize(731, 531);
        frameLineGraph = new QFrame(BrightHistogramForm);
        frameLineGraph->setObjectName("frameLineGraph");
        frameLineGraph->setGeometry(QRect(10, 10, 711, 381));
        frameLineGraph->setFrameShape(QFrame::NoFrame);
        frameLineGraph->setFrameShadow(QFrame::Plain);
        EditPickupH = new QSpinBox(BrightHistogramForm);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(190, 490, 61, 22));
        EditPickupH->setMaximum(255);
        label_7 = new QLabel(BrightHistogramForm);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 460, 111, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(BrightHistogramForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(70, 490, 111, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonReflect = new QPushButton(BrightHistogramForm);
        ButtonReflect->setObjectName("ButtonReflect");
        ButtonReflect->setGeometry(QRect(530, 430, 171, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Reflection.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonReflect->setIcon(icon);
        EditPickupL = new QSpinBox(BrightHistogramForm);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(190, 460, 61, 22));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(192, 192, 192, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        EditPickupL->setPalette(palette);
        EditPickupL->setMaximum(255);
        ButtonClose = new QPushButton(BrightHistogramForm);
        ButtonClose->setObjectName("ButtonClose");
        ButtonClose->setGeometry(QRect(530, 480, 171, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonClose->setIcon(icon1);

        retranslateUi(BrightHistogramForm);

        QMetaObject::connectSlotsByName(BrightHistogramForm);
    } // setupUi

    void retranslateUi(QDialog *BrightHistogramForm)
    {
        BrightHistogramForm->setWindowTitle(QCoreApplication::translate("BrightHistogramForm", "Bright Histogram", nullptr));
        label_7->setText(QCoreApplication::translate("BrightHistogramForm", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        label_8->setText(QCoreApplication::translate("BrightHistogramForm", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        ButtonReflect->setText(QCoreApplication::translate("BrightHistogramForm", "\345\217\215\346\230\240", nullptr));
        ButtonClose->setText(QCoreApplication::translate("BrightHistogramForm", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BrightHistogramForm: public Ui_BrightHistogramForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRIGHTHISTOGRAMFORM_H
