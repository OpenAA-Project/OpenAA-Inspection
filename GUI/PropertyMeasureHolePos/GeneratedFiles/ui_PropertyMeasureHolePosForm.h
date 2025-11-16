/********************************************************************************
** Form generated from reading UI file 'PropertyMeasureHolePosForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYMEASUREHOLEPOSFORM_H
#define UI_PROPERTYMEASUREHOLEPOSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyMeasureHolePosFormClass
{
public:
    QTableWidget *tableWidgetBlockInf;
    QLabel *label_32;
    QPushButton *pushButtonEditLibFolder;
    QLabel *labelLibFolderName;
    QFrame *frame_2;
    QToolButton *toolButtonArea;
    QToolButton *toolButtonHole;
    QToolButton *toolButtonEdge;
    QPushButton *pushButtonEditLibrary;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QTableWidget *tableWidgetHoleList;
    QWidget *tab;
    QFrame *frameBlockInfoOnMouse;
    QLabel *label_33;
    QFrame *frame;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;
    QLabel *label_34;
    QDoubleSpinBox *doubleSpinBoxPosPrecision;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_92;
    QLabel *label;
    QSpinBox *spinBoxNoiseSize;
    QSpinBox *EditSearchDot;
    QDoubleSpinBox *doubleSpinBoxDiaPrecision;
    QStackedWidget *stackedWidget;
    QWidget *Color;
    QFrame *frameColorCube;
    QPushButton *pushButtonNColor;
    QPushButton *pushButtonCreateNew;
    QPushButton *pushButtonUpdate;
    QWidget *Mono;
    QLabel *label_93;
    QSpinBox *EditPickupH;
    QLabel *label_94;
    QSpinBox *EditPickupL;
    QPushButton *pushButtonUpdateMono;
    QPushButton *pushButtonCreateNewMono;
    QSpinBox *spinBoxBandWidth;
    QLabel *label_4;

    void setupUi(GUIFormBase *PropertyMeasureHolePosFormClass)
    {
        if (PropertyMeasureHolePosFormClass->objectName().isEmpty())
            PropertyMeasureHolePosFormClass->setObjectName("PropertyMeasureHolePosFormClass");
        PropertyMeasureHolePosFormClass->resize(401, 700);
        tableWidgetBlockInf = new QTableWidget(PropertyMeasureHolePosFormClass);
        if (tableWidgetBlockInf->columnCount() < 3)
            tableWidgetBlockInf->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetBlockInf->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetBlockInf->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetBlockInf->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetBlockInf->setObjectName("tableWidgetBlockInf");
        tableWidgetBlockInf->setGeometry(QRect(10, 130, 381, 131));
        tableWidgetBlockInf->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBlockInf->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_32 = new QLabel(PropertyMeasureHolePosFormClass);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 110, 381, 21));
        QFont font;
        font.setPointSize(12);
        label_32->setFont(font);
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonEditLibFolder = new QPushButton(PropertyMeasureHolePosFormClass);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(10, 70, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        labelLibFolderName = new QLabel(PropertyMeasureHolePosFormClass);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(120, 70, 241, 31));
        QFont font1;
        font1.setPointSize(16);
        labelLibFolderName->setFont(font1);
        frame_2 = new QFrame(PropertyMeasureHolePosFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 281, 51));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        toolButtonArea = new QToolButton(frame_2);
        toolButtonArea->setObjectName("toolButtonArea");
        toolButtonArea->setGeometry(QRect(10, 10, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/draw_pen_64.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonArea->setIcon(icon1);
        toolButtonArea->setCheckable(true);
        toolButtonArea->setChecked(true);
        toolButtonArea->setAutoExclusive(true);
        toolButtonArea->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButtonHole = new QToolButton(frame_2);
        toolButtonHole->setObjectName("toolButtonHole");
        toolButtonHole->setGeometry(QRect(100, 10, 81, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Hole.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonHole->setIcon(icon2);
        toolButtonHole->setCheckable(true);
        toolButtonHole->setChecked(false);
        toolButtonHole->setAutoExclusive(true);
        toolButtonHole->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButtonEdge = new QToolButton(frame_2);
        toolButtonEdge->setObjectName("toolButtonEdge");
        toolButtonEdge->setGeometry(QRect(190, 10, 81, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonEdge->setIcon(icon3);
        toolButtonEdge->setCheckable(true);
        toolButtonEdge->setChecked(false);
        toolButtonEdge->setAutoExclusive(true);
        toolButtonEdge->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pushButtonEditLibrary = new QPushButton(PropertyMeasureHolePosFormClass);
        pushButtonEditLibrary->setObjectName("pushButtonEditLibrary");
        pushButtonEditLibrary->setGeometry(QRect(300, 20, 91, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibrary->setIcon(icon4);
        tabWidget = new QTabWidget(PropertyMeasureHolePosFormClass);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 270, 381, 421));
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tableWidgetHoleList = new QTableWidget(tab_2);
        if (tableWidgetHoleList->columnCount() < 4)
            tableWidgetHoleList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetHoleList->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetHoleList->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetHoleList->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetHoleList->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        tableWidgetHoleList->setObjectName("tableWidgetHoleList");
        tableWidgetHoleList->setGeometry(QRect(0, 0, 381, 401));
        tableWidgetHoleList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetHoleList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        frameBlockInfoOnMouse = new QFrame(tab);
        frameBlockInfoOnMouse->setObjectName("frameBlockInfoOnMouse");
        frameBlockInfoOnMouse->setGeometry(QRect(0, 0, 381, 401));
        frameBlockInfoOnMouse->setFrameShape(QFrame::StyledPanel);
        frameBlockInfoOnMouse->setFrameShadow(QFrame::Sunken);
        label_33 = new QLabel(frameBlockInfoOnMouse);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(0, 0, 381, 31));
        label_33->setFont(font);
        label_33->setFrameShape(QFrame::Panel);
        label_33->setFrameShadow(QFrame::Sunken);
        label_33->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(frameBlockInfoOnMouse);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 40, 361, 351));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        EditLibName = new QLineEdit(frame);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(120, 10, 231, 31));
        EditLibName->setFont(font);
        EditLibID = new QLineEdit(frame);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(60, 10, 61, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);
        label_34 = new QLabel(frame);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(10, 10, 51, 31));
        label_34->setFont(font);
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxPosPrecision = new QDoubleSpinBox(frame);
        doubleSpinBoxPosPrecision->setObjectName("doubleSpinBoxPosPrecision");
        doubleSpinBoxPosPrecision->setGeometry(QRect(230, 70, 81, 22));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 70, 181, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 90, 181, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_92 = new QLabel(frame);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(40, 140, 181, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 50, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxNoiseSize = new QSpinBox(frame);
        spinBoxNoiseSize->setObjectName("spinBoxNoiseSize");
        spinBoxNoiseSize->setGeometry(QRect(230, 90, 81, 22));
        EditSearchDot = new QSpinBox(frame);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(230, 140, 81, 22));
        EditSearchDot->setMaximum(100);
        doubleSpinBoxDiaPrecision = new QDoubleSpinBox(frame);
        doubleSpinBoxDiaPrecision->setObjectName("doubleSpinBoxDiaPrecision");
        doubleSpinBoxDiaPrecision->setGeometry(QRect(230, 50, 81, 22));
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(30, 170, 311, 171));
        Color = new QWidget();
        Color->setObjectName("Color");
        frameColorCube = new QFrame(Color);
        frameColorCube->setObjectName("frameColorCube");
        frameColorCube->setGeometry(QRect(60, 0, 231, 131));
        frameColorCube->setFrameShape(QFrame::NoFrame);
        frameColorCube->setFrameShadow(QFrame::Raised);
        pushButtonNColor = new QPushButton(Color);
        pushButtonNColor->setObjectName("pushButtonNColor");
        pushButtonNColor->setGeometry(QRect(0, 20, 51, 25));
        pushButtonCreateNew = new QPushButton(Color);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(50, 140, 91, 31));
        pushButtonUpdate = new QPushButton(Color);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(170, 140, 91, 31));
        stackedWidget->addWidget(Color);
        Mono = new QWidget();
        Mono->setObjectName("Mono");
        label_93 = new QLabel(Mono);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(10, 10, 131, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupH = new QSpinBox(Mono);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(220, 30, 81, 22));
        EditPickupH->setMaximum(100);
        label_94 = new QLabel(Mono);
        label_94->setObjectName("label_94");
        label_94->setGeometry(QRect(180, 10, 131, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPickupL = new QSpinBox(Mono);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(50, 30, 81, 22));
        EditPickupL->setMaximum(100);
        pushButtonUpdateMono = new QPushButton(Mono);
        pushButtonUpdateMono->setObjectName("pushButtonUpdateMono");
        pushButtonUpdateMono->setGeometry(QRect(170, 70, 91, 31));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdateMono->setIcon(icon5);
        pushButtonCreateNewMono = new QPushButton(Mono);
        pushButtonCreateNewMono->setObjectName("pushButtonCreateNewMono");
        pushButtonCreateNewMono->setGeometry(QRect(50, 70, 91, 31));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCreateNewMono->setIcon(icon6);
        stackedWidget->addWidget(Mono);
        spinBoxBandWidth = new QSpinBox(frame);
        spinBoxBandWidth->setObjectName("spinBoxBandWidth");
        spinBoxBandWidth->setGeometry(QRect(230, 110, 81, 22));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 110, 181, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget->addTab(tab, QString());

        retranslateUi(PropertyMeasureHolePosFormClass);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PropertyMeasureHolePosFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyMeasureHolePosFormClass)
    {
        PropertyMeasureHolePosFormClass->setWindowTitle(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "PropertyMeasureHolePosForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetBlockInf->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetBlockInf->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetBlockInf->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\343\203\226\343\203\255\343\203\203\343\202\257\347\267\217\346\225\260", nullptr));
        label_32->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\344\275\277\347\224\250\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\347\251\264\346\244\234\346\237\273\351\240\230\345\237\237", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\357\274\270\357\274\270\357\274\270", nullptr));
        toolButtonArea->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\346\217\217\347\224\273\351\240\230\345\237\237", nullptr));
        toolButtonHole->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\347\251\264\351\240\230\345\237\237", nullptr));
        toolButtonEdge->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\346\216\242\347\264\242\351\240\230\345\237\237", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Edit Library", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetHoleList->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetHoleList->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetHoleList->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetHoleList->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Search", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\347\251\264\343\203\252\343\202\271\343\203\210", nullptr));
        label_33->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\343\203\236\343\202\246\343\202\271\343\202\253\343\203\274\343\202\275\343\203\253\344\275\215\347\275\256\343\201\256\347\251\264\346\244\234\346\237\273\346\203\205\345\240\261", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Library Name", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "12345", nullptr));
        label_34->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\345\220\215\347\247\260", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\344\275\215\347\275\256\347\262\276\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_92->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\347\251\264\345\276\204\347\262\276\345\272\246", nullptr));
        pushButtonNColor->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Color", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Create new", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Update", nullptr));
        label_93->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        label_94->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        pushButtonUpdateMono->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Update", nullptr));
        pushButtonCreateNewMono->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "Create new", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\345\270\257\345\271\205", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PropertyMeasureHolePosFormClass", "\350\251\263\347\264\260\346\203\205\345\240\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyMeasureHolePosFormClass: public Ui_PropertyMeasureHolePosFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYMEASUREHOLEPOSFORM_H
