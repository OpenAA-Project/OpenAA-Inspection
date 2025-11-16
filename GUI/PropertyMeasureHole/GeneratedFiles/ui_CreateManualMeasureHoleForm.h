/********************************************************************************
** Form generated from reading UI file 'CreateManualMeasureHoleForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMANUALMEASUREHOLEFORM_H
#define UI_CREATEMANUALMEASUREHOLEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateManualMeasureHoleFormClass
{
public:
    QSpinBox *EditNoiseSize;
    QSpinBox *EditMaxDiameter;
    QLabel *label_89;
    QLabel *label_90;
    QLabel *label_92;
    QLabel *label_91;
    QSpinBox *EditSearchDot;
    QFrame *frameColorCube;
    QSpinBox *EditMinDiameter;
    QFrame *frameColorSample;
    QPushButton *pushButtonEliminateColor;
    QPushButton *pushButtonAddColor;
    QLabel *label_8;
    QListWidget *listWidgetBaseColor;
    QListWidget *listWidgetEliminatedColor;
    QLabel *label_7;
    QFrame *framePicked;
    QLabel *label_36;
    QPushButton *pushButtonSubPickupColor;
    QPushButton *pushButtonAddPickupColor;
    QSpinBox *spinBoxMerginAddPickupColor;
    QSpinBox *spinBoxMerginSubPickupColor;
    QLabel *label_37;
    QFrame *framePickupColor;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QTableWidget *tableWidgetLibList;
    QFrame *frameLibFolder;
    QLabel *label_4;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;

    void setupUi(QDialog *CreateManualMeasureHoleFormClass)
    {
        if (CreateManualMeasureHoleFormClass->objectName().isEmpty())
            CreateManualMeasureHoleFormClass->setObjectName("CreateManualMeasureHoleFormClass");
        CreateManualMeasureHoleFormClass->resize(792, 593);
        EditNoiseSize = new QSpinBox(CreateManualMeasureHoleFormClass);
        EditNoiseSize->setObjectName("EditNoiseSize");
        EditNoiseSize->setGeometry(QRect(430, 470, 81, 22));
        EditNoiseSize->setMaximum(10);
        EditMaxDiameter = new QSpinBox(CreateManualMeasureHoleFormClass);
        EditMaxDiameter->setObjectName("EditMaxDiameter");
        EditMaxDiameter->setGeometry(QRect(430, 440, 81, 22));
        EditMaxDiameter->setMaximum(1000000);
        label_89 = new QLabel(CreateManualMeasureHoleFormClass);
        label_89->setObjectName("label_89");
        label_89->setGeometry(QRect(220, 410, 201, 21));
        label_89->setFrameShape(QFrame::Panel);
        label_89->setFrameShadow(QFrame::Sunken);
        label_89->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_90 = new QLabel(CreateManualMeasureHoleFormClass);
        label_90->setObjectName("label_90");
        label_90->setGeometry(QRect(220, 440, 201, 21));
        label_90->setFrameShape(QFrame::Panel);
        label_90->setFrameShadow(QFrame::Sunken);
        label_90->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_92 = new QLabel(CreateManualMeasureHoleFormClass);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(220, 500, 201, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_91 = new QLabel(CreateManualMeasureHoleFormClass);
        label_91->setObjectName("label_91");
        label_91->setGeometry(QRect(220, 470, 201, 21));
        label_91->setFrameShape(QFrame::Panel);
        label_91->setFrameShadow(QFrame::Sunken);
        label_91->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(CreateManualMeasureHoleFormClass);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(430, 500, 81, 22));
        EditSearchDot->setMaximum(100);
        frameColorCube = new QFrame(CreateManualMeasureHoleFormClass);
        frameColorCube->setObjectName("frameColorCube");
        frameColorCube->setGeometry(QRect(220, 10, 351, 261));
        frameColorCube->setFrameShape(QFrame::NoFrame);
        frameColorCube->setFrameShadow(QFrame::Sunken);
        EditMinDiameter = new QSpinBox(CreateManualMeasureHoleFormClass);
        EditMinDiameter->setObjectName("EditMinDiameter");
        EditMinDiameter->setGeometry(QRect(430, 410, 81, 22));
        EditMinDiameter->setMaximum(1000000);
        frameColorSample = new QFrame(CreateManualMeasureHoleFormClass);
        frameColorSample->setObjectName("frameColorSample");
        frameColorSample->setGeometry(QRect(580, 10, 205, 511));
        frameColorSample->setFrameShape(QFrame::StyledPanel);
        frameColorSample->setFrameShadow(QFrame::Sunken);
        pushButtonEliminateColor = new QPushButton(frameColorSample);
        pushButtonEliminateColor->setObjectName("pushButtonEliminateColor");
        pushButtonEliminateColor->setGeometry(QRect(20, 480, 161, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/ColorDelete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEliminateColor->setIcon(icon);
        pushButtonAddColor = new QPushButton(frameColorSample);
        pushButtonAddColor->setObjectName("pushButtonAddColor");
        pushButtonAddColor->setGeometry(QRect(20, 450, 161, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/ColorAdd.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonAddColor->setIcon(icon1);
        label_8 = new QLabel(CreateManualMeasureHoleFormClass);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(490, 280, 61, 20));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetBaseColor = new QListWidget(CreateManualMeasureHoleFormClass);
        listWidgetBaseColor->setObjectName("listWidgetBaseColor");
        listWidgetBaseColor->setGeometry(QRect(420, 300, 61, 61));
        listWidgetEliminatedColor = new QListWidget(CreateManualMeasureHoleFormClass);
        listWidgetEliminatedColor->setObjectName("listWidgetEliminatedColor");
        listWidgetEliminatedColor->setGeometry(QRect(490, 300, 61, 61));
        label_7 = new QLabel(CreateManualMeasureHoleFormClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(420, 280, 61, 20));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        framePicked = new QFrame(CreateManualMeasureHoleFormClass);
        framePicked->setObjectName("framePicked");
        framePicked->setGeometry(QRect(220, 280, 191, 111));
        framePicked->setFrameShape(QFrame::StyledPanel);
        framePicked->setFrameShadow(QFrame::Sunken);
        label_36 = new QLabel(framePicked);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(0, 0, 191, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSubPickupColor = new QPushButton(framePicked);
        pushButtonSubPickupColor->setObjectName("pushButtonSubPickupColor");
        pushButtonSubPickupColor->setGeometry(QRect(40, 80, 75, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Color.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSubPickupColor->setIcon(icon2);
        pushButtonAddPickupColor = new QPushButton(framePicked);
        pushButtonAddPickupColor->setObjectName("pushButtonAddPickupColor");
        pushButtonAddPickupColor->setGeometry(QRect(40, 50, 75, 23));
        pushButtonAddPickupColor->setIcon(icon1);
        spinBoxMerginAddPickupColor = new QSpinBox(framePicked);
        spinBoxMerginAddPickupColor->setObjectName("spinBoxMerginAddPickupColor");
        spinBoxMerginAddPickupColor->setGeometry(QRect(120, 50, 61, 22));
        spinBoxMerginAddPickupColor->setValue(10);
        spinBoxMerginSubPickupColor = new QSpinBox(framePicked);
        spinBoxMerginSubPickupColor->setObjectName("spinBoxMerginSubPickupColor");
        spinBoxMerginSubPickupColor->setGeometry(QRect(120, 80, 61, 22));
        spinBoxMerginSubPickupColor->setValue(10);
        label_37 = new QLabel(framePicked);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(120, 30, 64, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        framePickupColor = new QFrame(framePicked);
        framePickupColor->setObjectName("framePickupColor");
        framePickupColor->setGeometry(QRect(10, 30, 21, 71));
        framePickupColor->setFrameShape(QFrame::NoFrame);
        framePickupColor->setFrameShadow(QFrame::Plain);
        pushButtonOK = new QPushButton(CreateManualMeasureHoleFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(250, 540, 101, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon3);
        pushButtonCancel = new QPushButton(CreateManualMeasureHoleFormClass);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(530, 540, 91, 41));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon4);
        tableWidgetLibList = new QTableWidget(CreateManualMeasureHoleFormClass);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(10, 160, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frameLibFolder = new QFrame(CreateManualMeasureHoleFormClass);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 201, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(CreateManualMeasureHoleFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 320, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_4->setFont(font);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(CreateManualMeasureHoleFormClass);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(10, 400, 201, 31));
        EditLibName->setFont(font);
        EditLibID = new QLineEdit(CreateManualMeasureHoleFormClass);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(10, 360, 81, 31));
        EditLibID->setFont(font);
        EditLibID->setReadOnly(true);

        retranslateUi(CreateManualMeasureHoleFormClass);

        QMetaObject::connectSlotsByName(CreateManualMeasureHoleFormClass);
    } // setupUi

    void retranslateUi(QDialog *CreateManualMeasureHoleFormClass)
    {
        CreateManualMeasureHoleFormClass->setWindowTitle(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "CreateManualMeasureHoleForm", nullptr));
        label_89->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\346\234\200\345\260\217\350\250\261\345\256\271\345\276\204", nullptr));
        label_90->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\346\234\200\345\244\247\350\250\261\345\256\271\345\276\204", nullptr));
        label_92->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_91->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272\343\203\211\343\203\203\343\203\210", nullptr));
        pushButtonEliminateColor->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "Eliminate color", nullptr));
        pushButtonAddColor->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "Add Color", nullptr));
        label_8->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\351\231\244\345\244\226\350\211\262", nullptr));
        label_7->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\350\277\275\345\212\240\350\211\262", nullptr));
        label_36->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\343\203\224\343\203\203\343\202\257\343\202\242\343\203\203\343\203\227\350\211\262\343\201\256\350\277\275\345\212\240\343\203\273\351\231\244\345\244\226", nullptr));
        pushButtonSubPickupColor->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "Sub =>", nullptr));
        pushButtonAddPickupColor->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "Add =>", nullptr));
        label_37->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\343\203\236\343\203\274\343\202\270\343\203\263\350\274\235\345\272\246", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\344\275\234\346\210\220", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "\345\220\215\347\247\260", nullptr));
        EditLibName->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "Library Name", nullptr));
        EditLibID->setText(QCoreApplication::translate("CreateManualMeasureHoleFormClass", "12345", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateManualMeasureHoleFormClass: public Ui_CreateManualMeasureHoleFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMANUALMEASUREHOLEFORM_H
