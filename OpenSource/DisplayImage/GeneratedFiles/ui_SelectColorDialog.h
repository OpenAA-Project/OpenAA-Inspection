/********************************************************************************
** Form generated from reading UI file 'SelectColorDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCOLORDIALOG_H
#define UI_SELECTCOLORDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectColorDialog
{
public:
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;
    QStackedWidget *stackedWidget;
    QWidget *Color;
    QSpinBox *spinBoxRed;
    QLabel *label;
    QSpinBox *spinBoxGreen;
    QLabel *label_2;
    QSpinBox *spinBoxBlue;
    QLabel *label_3;
    QPushButton *pushButtonColor;
    QWidget *Monochrome;
    QSpinBox *spinBoxBrightness;
    QLabel *label_4;

    void setupUi(QDialog *SelectColorDialog)
    {
        if (SelectColorDialog->objectName().isEmpty())
            SelectColorDialog->setObjectName("SelectColorDialog");
        SelectColorDialog->resize(210, 123);
        pushButtonCancel = new QPushButton(SelectColorDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 90, 91, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonOK = new QPushButton(SelectColorDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(10, 90, 91, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        stackedWidget = new QStackedWidget(SelectColorDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 191, 81));
        Color = new QWidget();
        Color->setObjectName("Color");
        spinBoxRed = new QSpinBox(Color);
        spinBoxRed->setObjectName("spinBoxRed");
        spinBoxRed->setGeometry(QRect(10, 20, 51, 22));
        spinBoxRed->setMaximum(255);
        label = new QLabel(Color);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 50, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxGreen = new QSpinBox(Color);
        spinBoxGreen->setObjectName("spinBoxGreen");
        spinBoxGreen->setGeometry(QRect(70, 20, 51, 22));
        spinBoxGreen->setMaximum(255);
        label_2 = new QLabel(Color);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 0, 50, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxBlue = new QSpinBox(Color);
        spinBoxBlue->setObjectName("spinBoxBlue");
        spinBoxBlue->setGeometry(QRect(130, 20, 51, 22));
        spinBoxBlue->setMaximum(255);
        label_3 = new QLabel(Color);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 0, 50, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonColor = new QPushButton(Color);
        pushButtonColor->setObjectName("pushButtonColor");
        pushButtonColor->setGeometry(QRect(60, 50, 75, 23));
        stackedWidget->addWidget(Color);
        Monochrome = new QWidget();
        Monochrome->setObjectName("Monochrome");
        spinBoxBrightness = new QSpinBox(Monochrome);
        spinBoxBrightness->setObjectName("spinBoxBrightness");
        spinBoxBrightness->setGeometry(QRect(61, 40, 61, 22));
        spinBoxBrightness->setMaximum(255);
        label_4 = new QLabel(Monochrome);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 20, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget->addWidget(Monochrome);

        retranslateUi(SelectColorDialog);

        pushButtonOK->setDefault(true);
        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SelectColorDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectColorDialog)
    {
        SelectColorDialog->setWindowTitle(QCoreApplication::translate("SelectColorDialog", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectColorDialog", "Cancel", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectColorDialog", "OK", nullptr));
        label->setText(QCoreApplication::translate("SelectColorDialog", "Red", nullptr));
        label_2->setText(QCoreApplication::translate("SelectColorDialog", "Green", nullptr));
        label_3->setText(QCoreApplication::translate("SelectColorDialog", "Blue", nullptr));
        pushButtonColor->setText(QCoreApplication::translate("SelectColorDialog", "Color", nullptr));
        label_4->setText(QCoreApplication::translate("SelectColorDialog", "Brightness", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectColorDialog: public Ui_SelectColorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCOLORDIALOG_H
