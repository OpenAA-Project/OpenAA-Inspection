/********************************************************************************
** Form generated from reading UI file 'PropertyProjectedInspectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYPROJECTEDINSPECTIONFORM_H
#define UI_PROPERTYPROJECTEDINSPECTIONFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyProjectedInspectionForm
{
public:
    QLabel *labelLibFolderName;
    QLabel *label_31;
    QPushButton *pushButtonEditLibrary;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonSetFrom;
    QTableWidget *tableWidgetGeneratedLibList;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonSetFromAll;
    QPushButton *pushButtonEditLibFolder;
    QLabel *label_30;
    QPushButton *pushButtonGetBackAll;
    QTableWidget *tableWidgetAllItems;
    QPushButton *ButtonPickupClearTest;
    QPushButton *ButtonGenerateLibs;
    QPushButton *ButtonPickupTest;

    void setupUi(GUIFormBase *PropertyProjectedInspectionForm)
    {
        if (PropertyProjectedInspectionForm->objectName().isEmpty())
            PropertyProjectedInspectionForm->setObjectName("PropertyProjectedInspectionForm");
        PropertyProjectedInspectionForm->resize(405, 595);
        labelLibFolderName = new QLabel(PropertyProjectedInspectionForm);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 10, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        label_31 = new QLabel(PropertyProjectedInspectionForm);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 50, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonEditLibrary = new QPushButton(PropertyProjectedInspectionForm);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(230, 200, 161, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibrary->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon);
        pushButtonGetBack = new QPushButton(PropertyProjectedInspectionForm);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 120, 39, 23));
        pushButtonSetFrom = new QPushButton(PropertyProjectedInspectionForm);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 90, 39, 23));
        tableWidgetGeneratedLibList = new QTableWidget(PropertyProjectedInspectionForm);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 70, 161, 121));
        tableWidgetGeneratedLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetLibList = new QTableWidget(PropertyProjectedInspectionForm);
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
        pushButtonSetFromAll = new QPushButton(PropertyProjectedInspectionForm);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 170, 39, 23));
        pushButtonEditLibFolder = new QPushButton(PropertyProjectedInspectionForm);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 10, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon1);
        label_30 = new QLabel(PropertyProjectedInspectionForm);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 50, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonGetBackAll = new QPushButton(PropertyProjectedInspectionForm);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 200, 39, 23));
        tableWidgetAllItems = new QTableWidget(PropertyProjectedInspectionForm);
        if (tableWidgetAllItems->columnCount() < 5)
            tableWidgetAllItems->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetAllItems->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetAllItems->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetAllItems->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetAllItems->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetAllItems->setHorizontalHeaderItem(4, __qtablewidgetitem8);
        tableWidgetAllItems->setObjectName("tableWidgetAllItems");
        tableWidgetAllItems->setGeometry(QRect(10, 360, 381, 192));
        tableWidgetAllItems->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetAllItems->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonPickupClearTest = new QPushButton(PropertyProjectedInspectionForm);
        ButtonPickupClearTest->setObjectName("ButtonPickupClearTest");
        ButtonPickupClearTest->setGeometry(QRect(10, 306, 189, 31));
        QFont font2;
        font2.setPointSize(11);
        ButtonPickupClearTest->setFont(font2);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupClearTest->setIcon(icon2);
        ButtonGenerateLibs = new QPushButton(PropertyProjectedInspectionForm);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(200, 266, 199, 71));
        ButtonGenerateLibs->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon3);
        ButtonPickupTest = new QPushButton(PropertyProjectedInspectionForm);
        ButtonPickupTest->setObjectName("ButtonPickupTest");
        ButtonPickupTest->setGeometry(QRect(10, 250, 189, 51));
        ButtonPickupTest->setFont(font2);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Extract.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPickupTest->setIcon(icon4);

        retranslateUi(PropertyProjectedInspectionForm);

        QMetaObject::connectSlotsByName(PropertyProjectedInspectionForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyProjectedInspectionForm)
    {
        PropertyProjectedInspectionForm->setWindowTitle(QCoreApplication::translate("PropertyProjectedInspectionForm", "Property ProjectedInspection", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "<=", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "=>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "Name", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "=>>", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "<<=", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetAllItems->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetAllItems->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "Layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetAllItems->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetAllItems->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetAllItems->horizontalHeaderItem(4);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "Angle", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyProjectedInspectionForm", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyProjectedInspectionForm: public Ui_PropertyProjectedInspectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYPROJECTEDINSPECTIONFORM_H
