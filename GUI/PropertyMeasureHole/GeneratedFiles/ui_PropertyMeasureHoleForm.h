/********************************************************************************
** Form generated from reading UI file 'PropertyMeasureHoleForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYMEASUREHOLEFORM_H
#define UI_PROPERTYMEASUREHOLEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyMeasureHoleFormClass
{
public:
    QPushButton *pushButtonEditLibFolder;
    QTableWidget *tableWidgetLibList;
    QLabel *labelLibFolderName;
    QLabel *label_30;
    QFrame *frame;
    QLabel *label_89;
    QSpinBox *EditMinDiameter;
    QSpinBox *EditMaxDiameter;
    QLabel *label_90;
    QLabel *label_91;
    QSpinBox *EditNoiseSize;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QLabel *label_18;
    QLineEdit *EditLibID;
    QLineEdit *EditLibName;
    QStackedWidget *stackedWidget;
    QWidget *Mono;
    QSpinBox *EditPickupH;
    QSpinBox *EditPickupL;
    QLabel *label_94;
    QLabel *label_93;
    QPushButton *pushButtonCreateNewMono;
    QPushButton *pushButtonUpdateMono;
    QWidget *Color;
    QPushButton *pushButtonUpdate;
    QFrame *frameColorCube;
    QPushButton *pushButtonCreateNew;
    QWidget *page_2;

    void setupUi(GUIFormBase *PropertyMeasureHoleFormClass)
    {
        if (PropertyMeasureHoleFormClass->objectName().isEmpty())
            PropertyMeasureHoleFormClass->setObjectName("PropertyMeasureHoleFormClass");
        PropertyMeasureHoleFormClass->resize(401, 700);
        pushButtonEditLibFolder = new QPushButton(PropertyMeasureHoleFormClass);
        pushButtonEditLibFolder->setObjectName("pushButtonEditLibFolder");
        pushButtonEditLibFolder->setGeometry(QRect(20, 10, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEditLibFolder->setIcon(icon);
        tableWidgetLibList = new QTableWidget(PropertyMeasureHoleFormClass);
        if (tableWidgetLibList->columnCount() < 4)
            tableWidgetLibList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 70, 381, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        labelLibFolderName = new QLabel(PropertyMeasureHoleFormClass);
        labelLibFolderName->setObjectName("labelLibFolderName");
        labelLibFolderName->setGeometry(QRect(140, 10, 241, 31));
        QFont font;
        font.setPointSize(16);
        labelLibFolderName->setFont(font);
        label_30 = new QLabel(PropertyMeasureHoleFormClass);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 50, 381, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        frame = new QFrame(PropertyMeasureHoleFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 240, 381, 451));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_89 = new QLabel(frame);
        label_89->setObjectName("label_89");
        label_89->setGeometry(QRect(40, 60, 201, 21));
        label_89->setFrameShape(QFrame::Panel);
        label_89->setFrameShadow(QFrame::Sunken);
        label_89->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinDiameter = new QSpinBox(frame);
        EditMinDiameter->setObjectName("EditMinDiameter");
        EditMinDiameter->setGeometry(QRect(250, 60, 81, 22));
        EditMinDiameter->setMaximum(1000000);
        EditMaxDiameter = new QSpinBox(frame);
        EditMaxDiameter->setObjectName("EditMaxDiameter");
        EditMaxDiameter->setGeometry(QRect(250, 90, 81, 22));
        EditMaxDiameter->setMaximum(1000000);
        label_90 = new QLabel(frame);
        label_90->setObjectName("label_90");
        label_90->setGeometry(QRect(40, 90, 201, 21));
        label_90->setFrameShape(QFrame::Panel);
        label_90->setFrameShadow(QFrame::Sunken);
        label_90->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_91 = new QLabel(frame);
        label_91->setObjectName("label_91");
        label_91->setGeometry(QRect(40, 120, 201, 21));
        label_91->setFrameShape(QFrame::Panel);
        label_91->setFrameShadow(QFrame::Sunken);
        label_91->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditNoiseSize = new QSpinBox(frame);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(250, 120, 81, 22));
        EditNoiseSize->setMaximum(10);
        label_92 = new QLabel(frame);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(40, 150, 201, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(250, 150, 81, 22));
        EditSearchDot->setMaximum(100);
        label_18 = new QLabel(frame);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 10, 61, 31));
        QFont font1;
        font1.setPointSize(12);
        label_18->setFont(font1);
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(70, 10, 61, 31));
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        EditLibName = new QLineEdit(frame);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(130, 10, 231, 31));
        EditLibName->setFont(font1);
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 180, 361, 261));
        Mono = new QWidget();
        Mono->setObjectName("Mono");
        EditPickupH = new QSpinBox(Mono);
        EditPickupH->setObjectName("EditPickupH");
        EditPickupH->setGeometry(QRect(230, 30, 81, 22));
        EditPickupH->setMaximum(100);
        EditPickupL = new QSpinBox(Mono);
        EditPickupL->setObjectName("EditPickupL");
        EditPickupL->setGeometry(QRect(60, 30, 81, 22));
        EditPickupL->setMaximum(100);
        label_94 = new QLabel(Mono);
        label_94->setObjectName("label_94");
        label_94->setGeometry(QRect(190, 10, 131, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_93 = new QLabel(Mono);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(20, 10, 131, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonCreateNewMono = new QPushButton(Mono);
        pushButtonCreateNewMono->setObjectName("pushButtonCreateNewMono");
        pushButtonCreateNewMono->setGeometry(QRect(70, 70, 91, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCreateNewMono->setIcon(icon1);
        pushButtonUpdateMono = new QPushButton(Mono);
        pushButtonUpdateMono->setObjectName("pushButtonUpdateMono");
        pushButtonUpdateMono->setGeometry(QRect(190, 70, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdateMono->setIcon(icon2);
        stackedWidget->addWidget(Mono);
        Color = new QWidget();
        Color->setObjectName("Color");
        pushButtonUpdate = new QPushButton(Color);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(190, 230, 91, 31));
        pushButtonUpdate->setIcon(icon2);
        frameColorCube = new QFrame(Color);
        frameColorCube->setObjectName("frameColorCube");
        frameColorCube->setGeometry(QRect(0, 0, 361, 221));
        frameColorCube->setFrameShape(QFrame::NoFrame);
        frameColorCube->setFrameShadow(QFrame::Sunken);
        pushButtonCreateNew = new QPushButton(Color);
        pushButtonCreateNew->setObjectName("pushButtonCreateNew");
        pushButtonCreateNew->setGeometry(QRect(70, 230, 91, 31));
        pushButtonCreateNew->setIcon(icon1);
        stackedWidget->addWidget(Color);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        retranslateUi(PropertyMeasureHoleFormClass);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PropertyMeasureHoleFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyMeasureHoleFormClass)
    {
        PropertyMeasureHoleFormClass->setWindowTitle(QCoreApplication::translate("PropertyMeasureHoleFormClass", "PropertyMeasureHoleForm", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "MinD", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "MaxD", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\357\274\270\357\274\270\357\274\270", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        label_89->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\346\234\200\345\260\217\350\250\261\345\256\271\345\276\204(\316\274\357\275\215)", nullptr));
        label_90->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\346\234\200\345\244\247\350\250\261\345\256\271\345\276\204\357\274\210\316\274\357\275\215\357\274\211", nullptr));
        label_91->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272\343\203\211\343\203\203\343\203\210", nullptr));
        label_92->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_18->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "12345", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "Library Name", nullptr));
        label_94->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\230\216\345\201\264", nullptr));
        label_93->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "\346\212\275\345\207\272\350\274\235\345\272\246\343\200\200\346\232\227\345\201\264", nullptr));
        pushButtonCreateNewMono->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "Create new", nullptr));
        pushButtonUpdateMono->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "Update", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "Update", nullptr));
        pushButtonCreateNew->setText(QCoreApplication::translate("PropertyMeasureHoleFormClass", "Create new", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyMeasureHoleFormClass: public Ui_PropertyMeasureHoleFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYMEASUREHOLEFORM_H
