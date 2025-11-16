/********************************************************************************
** Form generated from reading UI file 'PropertyDotColorMatchingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYDOTCOLORMATCHINGFORM_H
#define UI_PROPERTYDOTCOLORMATCHINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyDotColorMatchingForm
{
public:
    QPushButton *ButtonPickupTest;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonEditLibrary;
    QPushButton *pushButtonSetFrom;
    QLabel *label_30;
    QPushButton *ButtonGenerateLibs;
    QPushButton *ButtonPickupClearTest;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonGetBackAll;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *pushButtonSetFromAll;
    QLabel *label_31;
    QPushButton *pushButtonEditLibFolder;
    QLabel *labelLibFolderName;
    QTableWidget *tableWidget;
    QToolButton *toolButtonShowArea;
    QToolButton *toolButtonShowDiv;
    QToolButton *toolButtonShowFlat;
    QToolButton *toolButtonShowRotation;
    QToolButton *toolButtonShowBackGround;
    QPushButton *pushButtonBlockList;

    void setupUi(GUIFormBase *PropertyDotColorMatchingForm)
    {
        if (PropertyDotColorMatchingForm->objectName().isEmpty())
            PropertyDotColorMatchingForm->setObjectName("PropertyDotColorMatchingForm");
        PropertyDotColorMatchingForm->resize(401, 700);
        ButtonPickupTest = new QPushButton(PropertyDotColorMatchingForm);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 294, 181, 51));
        QFont font;
        font.setPointSize(11);
        ButtonPickupTest->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon);
        tableWidgetLibList = new QTableWidget(PropertyDotColorMatchingForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 100, 161, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonEditLibrary = new QPushButton(PropertyDotColorMatchingForm);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(200, 270, 191, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibrary->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon1);
        pushButtonSetFrom = new QPushButton(PropertyDotColorMatchingForm);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 120, 39, 23));
        label_30 = new QLabel(PropertyDotColorMatchingForm);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 80, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonGenerateLibs = new QPushButton(PropertyDotColorMatchingForm);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(200, 310, 191, 71));
        ButtonGenerateLibs->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon2);
        ButtonPickupClearTest = new QPushButton(PropertyDotColorMatchingForm);
        ButtonPickupClearTest->setObjectName("ButtonPickupClearTest");
        ButtonPickupClearTest->setGeometry(QRect(10, 350, 181, 31));
        ButtonPickupClearTest->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupClearTest->setIcon(icon3);
        pushButtonGetBack = new QPushButton(PropertyDotColorMatchingForm);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 150, 39, 23));
        pushButtonGetBackAll = new QPushButton(PropertyDotColorMatchingForm);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 230, 39, 23));
        tableWidgetGeneratedLibList = new QTableWidget(PropertyDotColorMatchingForm);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 100, 161, 161));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSetFromAll = new QPushButton(PropertyDotColorMatchingForm);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 200, 39, 23));
        label_31 = new QLabel(PropertyDotColorMatchingForm);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 80, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonEditLibFolder = new QPushButton(PropertyDotColorMatchingForm);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 40, 101, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon4);
        labelLibFolderName = new QLabel(PropertyDotColorMatchingForm);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 40, 241, 31));
        QFont font2;
        font2.setPointSize(16);
        labelLibFolderName->setFont(font2);
        tableWidget = new QTableWidget(PropertyDotColorMatchingForm);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 390, 381, 261));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        toolButtonShowArea = new QToolButton(PropertyDotColorMatchingForm);
        toolButtonShowArea->setObjectName("toolButtonShowArea");
        toolButtonShowArea->setGeometry(QRect(20, 10, 71, 21));
        toolButtonShowArea->setCheckable(true);
        toolButtonShowArea->setChecked(true);
        toolButtonShowDiv = new QToolButton(PropertyDotColorMatchingForm);
        toolButtonShowDiv->setObjectName("toolButtonShowDiv");
        toolButtonShowDiv->setGeometry(QRect(180, 10, 51, 21));
        toolButtonShowDiv->setCheckable(true);
        toolButtonShowFlat = new QToolButton(PropertyDotColorMatchingForm);
        toolButtonShowFlat->setObjectName("toolButtonShowFlat");
        toolButtonShowFlat->setGeometry(QRect(240, 10, 51, 21));
        toolButtonShowFlat->setCheckable(true);
        toolButtonShowRotation = new QToolButton(PropertyDotColorMatchingForm);
        toolButtonShowRotation->setObjectName("toolButtonShowRotation");
        toolButtonShowRotation->setGeometry(QRect(100, 10, 71, 21));
        toolButtonShowRotation->setCheckable(true);
        toolButtonShowRotation->setChecked(false);
        toolButtonShowBackGround = new QToolButton(PropertyDotColorMatchingForm);
        toolButtonShowBackGround->setObjectName("toolButtonShowBackGround");
        toolButtonShowBackGround->setGeometry(QRect(300, 10, 51, 21));
        toolButtonShowBackGround->setCheckable(true);
        pushButtonBlockList = new QPushButton(PropertyDotColorMatchingForm);
        pushButtonBlockList->setObjectName("pushButtonBlockList");
        pushButtonBlockList->setGeometry(QRect(110, 660, 171, 31));

        retranslateUi(PropertyDotColorMatchingForm);

        QMetaObject::connectSlotsByName(PropertyDotColorMatchingForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyDotColorMatchingForm)
    {
        PropertyDotColorMatchingForm->setWindowTitle(QCoreApplication::translate("PropertyDotColorMatchingForm", "Form", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "Name", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "=>", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "<=", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "<<=", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "Name", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "=>>", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "LibName", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "ItemCount", nullptr));
        toolButtonShowArea->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\346\244\234\346\237\273\351\240\230\345\237\237", nullptr));
        toolButtonShowDiv->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\345\244\211\345\214\226\347\202\271", nullptr));
        toolButtonShowFlat->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\345\235\207\344\270\200", nullptr));
        toolButtonShowRotation->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\345\233\236\350\273\242\351\240\230\345\237\237", nullptr));
        toolButtonShowBackGround->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\350\203\214\346\231\257", nullptr));
        pushButtonBlockList->setText(QCoreApplication::translate("PropertyDotColorMatchingForm", "\343\203\226\343\203\255\343\203\203\343\202\257\343\203\252\343\202\271\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyDotColorMatchingForm: public Ui_PropertyDotColorMatchingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYDOTCOLORMATCHINGFORM_H
