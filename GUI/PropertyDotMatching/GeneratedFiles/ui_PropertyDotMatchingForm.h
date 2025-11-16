/********************************************************************************
** Form generated from reading UI file 'PropertyDotMatchingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYDOTMATCHINGFORM_H
#define UI_PROPERTYDOTMATCHINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyDotMatchingForm
{
public:
    QLabel *label_31;
    QLabel *label_30;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonGetBackAll;
    QLabel *labelLibFolderName;
    QPushButton *ButtonPickupTest;
    QPushButton *pushButtonSetFromAll;
    QPushButton *pushButtonEditLibrary;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *ButtonGenerateLibs;
    QPushButton *pushButtonSetFrom;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *ButtonPickupClearTest;
    QTableWidget *tableWidgetLibList;

    void setupUi(GUIFormBase *PropertyDotMatchingForm)
    {
        if (PropertyDotMatchingForm->objectName().isEmpty())
            PropertyDotMatchingForm->setObjectName("PropertyDotMatchingForm");
        PropertyDotMatchingForm->resize(398, 363);
        label_31 = new QLabel(PropertyDotMatchingForm);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 50, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(PropertyDotMatchingForm);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 50, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonGetBack = new QPushButton(PropertyDotMatchingForm);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 120, 39, 23));
        pushButtonGetBackAll = new QPushButton(PropertyDotMatchingForm);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 200, 39, 23));
        labelLibFolderName = new QLabel(PropertyDotMatchingForm);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 10, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        ButtonPickupTest = new QPushButton(PropertyDotMatchingForm);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 264, 181, 51));
        QFont font1;
        font1.setPointSize(11);
        ButtonPickupTest->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon);
        pushButtonSetFromAll = new QPushButton(PropertyDotMatchingForm);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 170, 39, 23));
        pushButtonEditLibrary = new QPushButton(PropertyDotMatchingForm);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(200, 240, 191, 31));
        QFont font2;
        font2.setPointSize(12);
        pushButtonEditLibrary->setFont(font2);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon1);
        pushButtonEditLibFolder = new QPushButton(PropertyDotMatchingForm);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 10, 101, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon2);
        ButtonGenerateLibs = new QPushButton(PropertyDotMatchingForm);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(200, 280, 191, 71));
        ButtonGenerateLibs->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon3);
        pushButtonSetFrom = new QPushButton(PropertyDotMatchingForm);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 90, 39, 23));
        tableWidgetGeneratedLibList = new QTableWidget(PropertyDotMatchingForm);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 70, 161, 161));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonPickupClearTest = new QPushButton(PropertyDotMatchingForm);
        ButtonPickupClearTest->setObjectName("ButtonPickupClearTest");
        ButtonPickupClearTest->setGeometry(QRect(10, 320, 181, 31));
        ButtonPickupClearTest->setFont(font1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupClearTest->setIcon(icon4);
        tableWidgetLibList = new QTableWidget(PropertyDotMatchingForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 70, 161, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);

        retranslateUi(PropertyDotMatchingForm);

        QMetaObject::connectSlotsByName(PropertyDotMatchingForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyDotMatchingForm)
    {
        PropertyDotMatchingForm->setWindowTitle(QCoreApplication::translate("PropertyDotMatchingForm", "Property DotMatching", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyDotMatchingForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyDotMatchingForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyDotMatchingForm", "<=", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyDotMatchingForm", "<<=", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyDotMatchingForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyDotMatchingForm", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyDotMatchingForm", "=>>", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyDotMatchingForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyDotMatchingForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyDotMatchingForm", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyDotMatchingForm", "=>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyDotMatchingForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyDotMatchingForm", "Name", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyDotMatchingForm", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyDotMatchingForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyDotMatchingForm", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyDotMatchingForm: public Ui_PropertyDotMatchingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYDOTMATCHINGFORM_H
