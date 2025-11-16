/********************************************************************************
** Form generated from reading UI file 'PropertyColorDifferenceForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYCOLORDIFFERENCEFORM_H
#define UI_PROPERTYCOLORDIFFERENCEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyColorDifferenceForm
{
public:
    QLabel *label_31;
    QLabel *labelLibFolderName;
    QLabel *label_30;
    QPushButton *pushButtonEditLibrary;
    QTableWidget *tableWidget;
    QPushButton *pushButtonGetBackAll;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *pushButtonGetBack;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *pushButtonSetFrom;
    QPushButton *pushButtonSetFromAll;
    QTableWidget *tableWidgetLibList;
    QFrame *frame;
    QToolButton *toolButtonShowRegulation;
    QToolButton *toolButtonShowItem;
    QPushButton *pushButtonRegisterOK;
    QPushButton *pushButtonRegisterNG;
    QToolButton *toolButtonRegistInFlow;
    QToolButton *toolButtonSetThresholdHSV;
    QFrame *frame_2;
    QToolButton *toolButtonClearFlow;
    QLabel *label;
    QPushButton *pushButtonSaveFlow;
    QPushButton *pushButtonLoadFlow;
    QPushButton *pushButtonAutoGenerate;

    void setupUi(GUIFormBase *PropertyColorDifferenceForm)
    {
        if (PropertyColorDifferenceForm->objectName().isEmpty())
            PropertyColorDifferenceForm->setObjectName("PropertyColorDifferenceForm");
        PropertyColorDifferenceForm->resize(400, 700);
        label_31 = new QLabel(PropertyColorDifferenceForm);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(230, 80, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelLibFolderName = new QLabel(PropertyColorDifferenceForm);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 40, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        label_30 = new QLabel(PropertyColorDifferenceForm);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 80, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonEditLibrary = new QPushButton(PropertyColorDifferenceForm);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(230, 230, 161, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButtonEditLibrary->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon);
        tableWidget = new QTableWidget(PropertyColorDifferenceForm);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 500, 381, 191));
        pushButtonGetBackAll = new QPushButton(PropertyColorDifferenceForm);
        pushButtonGetBackAll->setObjectName("pushButtonGetBackAll");
        pushButtonGetBackAll->setGeometry(QRect(180, 230, 39, 23));
        tableWidgetGeneratedLibList = new QTableWidget(PropertyColorDifferenceForm);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        tableWidgetGeneratedLibList->setObjectName("tableWidgetGeneratedLibList");
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 100, 161, 121));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonGetBack = new QPushButton(PropertyColorDifferenceForm);
        pushButtonGetBack->setObjectName("pushButtonGetBack");
        pushButtonGetBack->setGeometry(QRect(180, 150, 39, 23));
        pushButtonEditLibFolder = new QPushButton(PropertyColorDifferenceForm);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 40, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon1);
        pushButtonSetFrom = new QPushButton(PropertyColorDifferenceForm);
        pushButtonSetFrom->setObjectName("pushButtonSetFrom");
        pushButtonSetFrom->setGeometry(QRect(180, 120, 39, 23));
        pushButtonSetFromAll = new QPushButton(PropertyColorDifferenceForm);
        pushButtonSetFromAll->setObjectName("pushButtonSetFromAll");
        pushButtonSetFromAll->setGeometry(QRect(180, 200, 39, 23));
        tableWidgetLibList = new QTableWidget(PropertyColorDifferenceForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 100, 161, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame = new QFrame(PropertyColorDifferenceForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 10, 311, 31));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButtonShowRegulation = new QToolButton(frame);
        toolButtonShowRegulation->setObjectName("toolButtonShowRegulation");
        toolButtonShowRegulation->setGeometry(QRect(170, 0, 141, 21));
        toolButtonShowRegulation->setCheckable(true);
        toolButtonShowItem = new QToolButton(frame);
        toolButtonShowItem->setObjectName("toolButtonShowItem");
        toolButtonShowItem->setGeometry(QRect(0, 0, 111, 21));
        toolButtonShowItem->setCheckable(true);
        toolButtonShowItem->setChecked(true);
        pushButtonRegisterOK = new QPushButton(PropertyColorDifferenceForm);
        pushButtonRegisterOK->setObjectName("pushButtonRegisterOK");
        pushButtonRegisterOK->setGeometry(QRect(30, 280, 112, 34));
        pushButtonRegisterNG = new QPushButton(PropertyColorDifferenceForm);
        pushButtonRegisterNG->setObjectName("pushButtonRegisterNG");
        pushButtonRegisterNG->setGeometry(QRect(30, 320, 112, 34));
        toolButtonRegistInFlow = new QToolButton(PropertyColorDifferenceForm);
        toolButtonRegistInFlow->setObjectName("toolButtonRegistInFlow");
        toolButtonRegistInFlow->setGeometry(QRect(200, 270, 191, 41));
        toolButtonRegistInFlow->setCheckable(true);
        toolButtonSetThresholdHSV = new QToolButton(PropertyColorDifferenceForm);
        toolButtonSetThresholdHSV->setObjectName("toolButtonSetThresholdHSV");
        toolButtonSetThresholdHSV->setGeometry(QRect(200, 320, 191, 41));
        toolButtonSetThresholdHSV->setCheckable(false);
        frame_2 = new QFrame(PropertyColorDifferenceForm);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 370, 251, 121));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        toolButtonClearFlow = new QToolButton(frame_2);
        toolButtonClearFlow->setObjectName("toolButtonClearFlow");
        toolButtonClearFlow->setGeometry(QRect(10, 30, 231, 41));
        toolButtonClearFlow->setCheckable(false);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 251, 21));
        label->setAlignment(Qt::AlignCenter);
        pushButtonSaveFlow = new QPushButton(frame_2);
        pushButtonSaveFlow->setObjectName("pushButtonSaveFlow");
        pushButtonSaveFlow->setGeometry(QRect(10, 80, 112, 34));
        pushButtonLoadFlow = new QPushButton(frame_2);
        pushButtonLoadFlow->setObjectName("pushButtonLoadFlow");
        pushButtonLoadFlow->setGeometry(QRect(130, 80, 112, 34));
        pushButtonAutoGenerate = new QPushButton(PropertyColorDifferenceForm);
        pushButtonAutoGenerate->setObjectName("pushButtonAutoGenerate");
        pushButtonAutoGenerate->setGeometry(QRect(280, 370, 112, 111));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        pushButtonAutoGenerate->setFont(font2);

        retranslateUi(PropertyColorDifferenceForm);

        QMetaObject::connectSlotsByName(PropertyColorDifferenceForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyColorDifferenceForm)
    {
        PropertyColorDifferenceForm->setWindowTitle(QCoreApplication::translate("PropertyColorDifferenceForm", "Form", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "LibName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "ItemCount", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "<<=", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "Name", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "<=", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "=>", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "=>>", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "Name", nullptr));
        toolButtonShowRegulation->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\345\237\272\346\272\226\351\240\230\345\237\237", nullptr));
        toolButtonShowItem->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\346\244\234\346\237\273\351\240\230\345\237\237", nullptr));
        pushButtonRegisterOK->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "OK\350\211\262\347\231\273\351\214\262", nullptr));
        pushButtonRegisterNG->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "NG\350\211\262\347\231\273\351\214\262", nullptr));
        toolButtonRegistInFlow->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "OK\346\265\201\345\213\225\347\231\273\351\214\262", nullptr));
        toolButtonSetThresholdHSV->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "HSV\343\201\227\343\201\215\343\201\204\345\200\244\347\265\261\350\250\210\350\250\255\345\256\232", nullptr));
        toolButtonClearFlow->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\351\201\270\346\212\236\343\202\242\343\202\244\343\203\206\343\203\240\343\201\256\346\265\201\345\213\225\343\202\257\343\203\252\343\202\242", nullptr));
        label->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\346\265\201\345\213\225\343\203\207\343\203\274\343\202\277", nullptr));
        pushButtonSaveFlow->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\344\277\235\345\255\230", nullptr));
        pushButtonLoadFlow->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\350\252\255\350\276\274", nullptr));
        pushButtonAutoGenerate->setText(QCoreApplication::translate("PropertyColorDifferenceForm", "\350\207\252\345\213\225\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyColorDifferenceForm: public Ui_PropertyColorDifferenceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYCOLORDIFFERENCEFORM_H
