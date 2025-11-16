/********************************************************************************
** Form generated from reading UI file 'SelectPageLayer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPAGELAYER_H
#define UI_SELECTPAGELAYER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectPageLayer
{
public:
    QListWidget *listWidgetPage;
    QLabel *label_2;
    QListWidget *listWidgetLayer;
    QLabel *label;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSelect;

    void setupUi(QDialog *SelectPageLayer)
    {
        if (SelectPageLayer->objectName().isEmpty())
            SelectPageLayer->setObjectName("SelectPageLayer");
        SelectPageLayer->resize(209, 269);
        listWidgetPage = new QListWidget(SelectPageLayer);
        listWidgetPage->setObjectName("listWidgetPage");
        listWidgetPage->setGeometry(QRect(10, 30, 91, 192));
        label_2 = new QLabel(SelectPageLayer);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 10, 91, 16));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetLayer = new QListWidget(SelectPageLayer);
        listWidgetLayer->setObjectName("listWidgetLayer");
        listWidgetLayer->setGeometry(QRect(110, 30, 91, 192));
        label = new QLabel(SelectPageLayer);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 91, 16));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCancel = new QPushButton(SelectPageLayer);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(110, 230, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonSelect = new QPushButton(SelectPageLayer);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(10, 230, 91, 31));

        retranslateUi(SelectPageLayer);

        QMetaObject::connectSlotsByName(SelectPageLayer);
    } // setupUi

    void retranslateUi(QDialog *SelectPageLayer)
    {
        SelectPageLayer->setWindowTitle(QCoreApplication::translate("SelectPageLayer", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("SelectPageLayer", "Layer", nullptr));
        label->setText(QCoreApplication::translate("SelectPageLayer", "Page", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectPageLayer", "Cancel", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectPageLayer", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectPageLayer: public Ui_SelectPageLayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPAGELAYER_H
