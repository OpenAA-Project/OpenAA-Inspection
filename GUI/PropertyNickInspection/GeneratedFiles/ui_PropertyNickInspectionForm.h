/********************************************************************************
** Form generated from reading UI file 'PropertyNickInspectionForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYNICKINSPECTIONFORM_H
#define UI_PROPERTYNICKINSPECTIONFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyNickInspectionForm
{
public:
    QTableWidget *tableWidgetItemList;
    QPushButton *pushButtonGetBack;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonSetFrom;
    QPushButton *pushButtonGetBackAll;
    QPushButton *ButtonGenerateLibs;
    QPushButton *pushButtonSetFromAll;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *pushButtonEditLibrary;
    QLabel *labelLibFolderName;
    QTableWidget *tableWidgetGeneratedLibList;
    QLabel *label_30;
    QLabel *label_31;

    void setupUi(GUIFormBase *PropertyNickInspectionForm)
    {
        if (PropertyNickInspectionForm->objectName().isEmpty())
            PropertyNickInspectionForm->setObjectName("PropertyNickInspectionForm");
        PropertyNickInspectionForm->resize(400, 700);
        tableWidgetItemList = new QTableWidget(PropertyNickInspectionForm);
        if (tableWidgetItemList->columnCount() < 3)
            tableWidgetItemList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetItemList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetItemList->setObjectName("tableWidgetItemList");
        tableWidgetItemList->setGeometry(QRect(10, 330, 381, 351));
        tableWidgetItemList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetItemList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonGetBack = new QPushButton(PropertyNickInspectionForm);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 100, 39, 23));
        tableWidgetLibList = new QTableWidget(PropertyNickInspectionForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 60, 161, 141));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonSetFrom = new QPushButton(PropertyNickInspectionForm);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 70, 39, 23));
        pushButtonGetBackAll = new QPushButton(PropertyNickInspectionForm);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 170, 39, 23));
        ButtonGenerateLibs = new QPushButton(PropertyNickInspectionForm);
        ButtonGenerateLibs->setObjectName("ButtonGenerateLibs");
        ButtonGenerateLibs->setGeometry(QRect(80, 250, 301, 71));
        QFont font;
        font.setPointSize(12);
        ButtonGenerateLibs->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonGenerateLibs->setIcon(icon);
        pushButtonSetFromAll = new QPushButton(PropertyNickInspectionForm);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 140, 39, 23));
        pushButtonEditLibFolder = new QPushButton(PropertyNickInspectionForm);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(10, 0, 121, 31));
        pushButtonEditLibFolder->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon1);
        pushButtonEditLibrary = new QPushButton(PropertyNickInspectionForm);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(80, 210, 211, 31));
        pushButtonEditLibrary->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon2);
        labelLibFolderName = new QLabel(PropertyNickInspectionForm);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(130, 0, 261, 31));
        QFont font1;
        font1.setPointSize(16);
        labelLibFolderName->setFont(font1);
        tableWidgetGeneratedLibList = new QTableWidget(PropertyNickInspectionForm);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 60, 161, 141));
        tableWidgetGeneratedLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_30 = new QLabel(PropertyNickInspectionForm);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 40, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_31 = new QLabel(PropertyNickInspectionForm);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 40, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(PropertyNickInspectionForm);

        QMetaObject::connectSlotsByName(PropertyNickInspectionForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyNickInspectionForm)
    {
        PropertyNickInspectionForm->setWindowTitle(QCoreApplication::translate("PropertyNickInspectionForm", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItemList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyNickInspectionForm", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItemList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyNickInspectionForm", "LibName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetItemList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyNickInspectionForm", "Count", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyNickInspectionForm", "<=", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyNickInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyNickInspectionForm", "Name", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyNickInspectionForm", "=>", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyNickInspectionForm", "<<=", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyNickInspectionForm", "\345\217\263\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyNickInspectionForm", "=>>", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyNickInspectionForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyNickInspectionForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyNickInspectionForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyNickInspectionForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyNickInspectionForm", "Name", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyNickInspectionForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyNickInspectionForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyNickInspectionForm: public Ui_PropertyNickInspectionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYNICKINSPECTIONFORM_H
