/********************************************************************************
** Form generated from reading UI file 'PropertyDentForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYDENTFORM_H
#define UI_PROPERTYDENTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyDentForm
{
public:
    QPushButton *pushButtonEditLibrary;
    QTableWidget *tableWidget;
    QLabel *labelLibFolderName;
    QLabel *label_30;
    QPushButton *ButtonPickupClearTest;
    QPushButton *pushButtonGetBack;
    QPushButton *ButtonGenerateLibs;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *pushButtonGetBackAll;
    QPushButton *ButtonPickupTest;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *pushButtonSetFrom;
    QLabel *label_31;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonSetFromAll;

    void setupUi(GUIFormBase *PropertyDentForm)
    {
        if (PropertyDentForm->objectName().isEmpty())
            PropertyDentForm->setObjectName("PropertyDentForm");
        PropertyDentForm->resize(400, 700);
        pushButtonEditLibrary = new QPushButton(PropertyDentForm);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(200, 240, 191, 31));
        QFont font;
        font.setPointSize(12);
        pushButtonEditLibrary->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon);
        tableWidget = new QTableWidget(PropertyDentForm);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 390, 381, 301));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        labelLibFolderName = new QLabel(PropertyDentForm);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 10, 241, 31));
        QFont font1;
        font1.setPointSize(16);
        labelLibFolderName->setFont(font1);
        label_30 = new QLabel(PropertyDentForm);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 50, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonPickupClearTest = new QPushButton(PropertyDentForm);
        ButtonPickupClearTest->setObjectName("ButtonPickupClearTest");
        ButtonPickupClearTest->setGeometry(QRect(10, 320, 181, 31));
        QFont font2;
        font2.setPointSize(11);
        ButtonPickupClearTest->setFont(font2);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupClearTest->setIcon(icon1);
        pushButtonGetBack = new QPushButton(PropertyDentForm);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 120, 39, 23));
        ButtonGenerateLibs = new QPushButton(PropertyDentForm);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(200, 280, 191, 71));
        ButtonGenerateLibs->setFont(font2);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon2);
        tableWidgetGeneratedLibList = new QTableWidget(PropertyDentForm);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 70, 161, 161));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonGetBackAll = new QPushButton(PropertyDentForm);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 200, 39, 23));
        ButtonPickupTest = new QPushButton(PropertyDentForm);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 264, 181, 51));
        ButtonPickupTest->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon3);
        pushButtonEditLibFolder = new QPushButton(PropertyDentForm);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 10, 101, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon4);
        pushButtonSetFrom = new QPushButton(PropertyDentForm);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 90, 39, 23));
        label_31 = new QLabel(PropertyDentForm);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 50, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tableWidgetLibList = new QTableWidget(PropertyDentForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 70, 161, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSetFromAll = new QPushButton(PropertyDentForm);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 170, 39, 23));

        retranslateUi(PropertyDentForm);

        QMetaObject::connectSlotsByName(PropertyDentForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyDentForm)
    {
        PropertyDentForm->setWindowTitle(QCoreApplication::translate("PropertyDentForm", "Form", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyDentForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyDentForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyDentForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyDentForm", "ItemName", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyDentForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyDentForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyDentForm", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyDentForm", "<=", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyDentForm", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyDentForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyDentForm", "Name", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyDentForm", "<<=", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyDentForm", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyDentForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyDentForm", "=>", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyDentForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyDentForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyDentForm", "Name", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyDentForm", "=>>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyDentForm: public Ui_PropertyDentForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYDENTFORM_H
