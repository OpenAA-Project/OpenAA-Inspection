/********************************************************************************
** Form generated from reading UI file 'AutoSaveImageViewListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSAVEIMAGEVIEWLISTFORM_H
#define UI_AUTOSAVEIMAGEVIEWLISTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoSaveImageViewListFormClass
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonUpdate;
    QFrame *frame;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QSpinBox *txtStartX;
    QSpinBox *txtStartY;
    QSpinBox *txtWidth;
    QSpinBox *txtHeight;
    QPushButton *pushButton_Load;
    QPushButton *pushButton_Save;

    void setupUi(QWidget *AutoSaveImageViewListFormClass)
    {
        if (AutoSaveImageViewListFormClass->objectName().isEmpty())
            AutoSaveImageViewListFormClass->setObjectName("AutoSaveImageViewListFormClass");
        AutoSaveImageViewListFormClass->resize(192, 640);
        tableWidget = new QTableWidget(AutoSaveImageViewListFormClass);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 50, 191, 461));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonUpdate = new QPushButton(AutoSaveImageViewListFormClass);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(0, 0, 191, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);
        frame = new QFrame(AutoSaveImageViewListFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 510, 181, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_22 = new QLabel(frame);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 10, 71, 21));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(frame);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 30, 71, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_24 = new QLabel(frame);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 50, 71, 21));
        label_24->setFrameShape(QFrame::Panel);
        label_24->setFrameShadow(QFrame::Sunken);
        label_24->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(frame);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 70, 71, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        txtStartX = new QSpinBox(frame);
        txtStartX->setObjectName("txtStartX");
        txtStartX->setGeometry(QRect(90, 10, 81, 22));
        txtStartX->setMaximum(100000);
        txtStartX->setValue(916);
        txtStartY = new QSpinBox(frame);
        txtStartY->setObjectName("txtStartY");
        txtStartY->setGeometry(QRect(90, 30, 81, 22));
        txtStartY->setMaximum(100000);
        txtStartY->setValue(609);
        txtWidth = new QSpinBox(frame);
        txtWidth->setObjectName("txtWidth");
        txtWidth->setGeometry(QRect(90, 50, 81, 22));
        txtWidth->setMaximum(100000);
        txtWidth->setValue(1000);
        txtHeight = new QSpinBox(frame);
        txtHeight->setObjectName("txtHeight");
        txtHeight->setGeometry(QRect(90, 70, 81, 22));
        txtHeight->setMaximum(100000);
        txtHeight->setValue(1000);
        pushButton_Load = new QPushButton(frame);
        pushButton_Load->setObjectName("pushButton_Load");
        pushButton_Load->setGeometry(QRect(20, 100, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_Load->setIcon(icon1);
        pushButton_Save = new QPushButton(frame);
        pushButton_Save->setObjectName("pushButton_Save");
        pushButton_Save->setGeometry(QRect(100, 100, 75, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_Save->setIcon(icon2);

        retranslateUi(AutoSaveImageViewListFormClass);

        QMetaObject::connectSlotsByName(AutoSaveImageViewListFormClass);
    } // setupUi

    void retranslateUi(QWidget *AutoSaveImageViewListFormClass)
    {
        AutoSaveImageViewListFormClass->setWindowTitle(QCoreApplication::translate("AutoSaveImageViewListFormClass", "AutoSaveImageViewListForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AutoSaveImageViewListFormClass", "No", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AutoSaveImageViewListFormClass", "Id", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("AutoSaveImageViewListFormClass", "\346\233\264\346\226\260", nullptr));
        label_22->setText(QCoreApplication::translate("AutoSaveImageViewListFormClass", "\351\226\213\345\247\213\346\250\252", nullptr));
        label_23->setText(QCoreApplication::translate("AutoSaveImageViewListFormClass", "\351\226\213\345\247\213\347\270\246", nullptr));
        label_24->setText(QCoreApplication::translate("AutoSaveImageViewListFormClass", "\345\271\205", nullptr));
        label_25->setText(QCoreApplication::translate("AutoSaveImageViewListFormClass", "\351\253\230\343\201\225", nullptr));
        pushButton_Load->setText(QCoreApplication::translate("AutoSaveImageViewListFormClass", "Load", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("AutoSaveImageViewListFormClass", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoSaveImageViewListFormClass: public Ui_AutoSaveImageViewListFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSAVEIMAGEVIEWLISTFORM_H
