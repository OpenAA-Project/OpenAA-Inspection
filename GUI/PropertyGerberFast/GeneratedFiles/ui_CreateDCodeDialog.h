/********************************************************************************
** Form generated from reading UI file 'CreateDCodeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEDCODEDIALOG_H
#define UI_CREATEDCODEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateDCodeDialog
{
public:
    QComboBox *comboBoxType;
    QSpinBox *spinBoxDCode;
    QLabel *label;
    QStackedWidget *stackedWidget;
    QWidget *Circle;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxCircleDiameterPixel;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxCircleDiameterMM;
    QLabel *label_4;
    QWidget *Rectangle;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxRectangleWidthPixel;
    QDoubleSpinBox *doubleSpinBoxRectangleWidthMM;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBoxRectangleHeightMM;
    QDoubleSpinBox *doubleSpinBoxRectangleHeightPixel;
    QWidget *Obround;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBoxObroundWidthMM;
    QLabel *label_15;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBoxObroundWidthPixel;
    QDoubleSpinBox *doubleSpinBoxObroundHeightPixel;
    QDoubleSpinBox *doubleSpinBoxObroundHeightMM;
    QWidget *Polygon;
    QLabel *label_17;
    QDoubleSpinBox *doubleSpinBoxPolygonDiameterPixel;
    QDoubleSpinBox *doubleSpinBoxPolygonDiameterMM;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QSpinBox *spinBoxPolygonSides;
    QPushButton *pushButtonCreate;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *CreateDCodeDialog)
    {
        if (CreateDCodeDialog->objectName().isEmpty())
            CreateDCodeDialog->setObjectName("CreateDCodeDialog");
        CreateDCodeDialog->resize(261, 250);
        comboBoxType = new QComboBox(CreateDCodeDialog);
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->setObjectName("comboBoxType");
        comboBoxType->setGeometry(QRect(10, 10, 111, 22));
        spinBoxDCode = new QSpinBox(CreateDCodeDialog);
        spinBoxDCode->setObjectName("spinBoxDCode");
        spinBoxDCode->setGeometry(QRect(170, 40, 71, 22));
        spinBoxDCode->setMaximum(999999);
        label = new QLabel(CreateDCodeDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 151, 21));
        label->setAlignment(Qt::AlignCenter);
        stackedWidget = new QStackedWidget(CreateDCodeDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 70, 251, 131));
        Circle = new QWidget();
        Circle->setObjectName("Circle");
        label_2 = new QLabel(Circle);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 20, 71, 16));
        doubleSpinBoxCircleDiameterPixel = new QDoubleSpinBox(Circle);
        doubleSpinBoxCircleDiameterPixel->setObjectName("doubleSpinBoxCircleDiameterPixel");
        doubleSpinBoxCircleDiameterPixel->setGeometry(QRect(100, 20, 91, 22));
        doubleSpinBoxCircleDiameterPixel->setMaximum(99999999.000000000000000);
        label_3 = new QLabel(Circle);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(200, 20, 71, 16));
        doubleSpinBoxCircleDiameterMM = new QDoubleSpinBox(Circle);
        doubleSpinBoxCircleDiameterMM->setObjectName("doubleSpinBoxCircleDiameterMM");
        doubleSpinBoxCircleDiameterMM->setGeometry(QRect(100, 50, 91, 22));
        doubleSpinBoxCircleDiameterMM->setMaximum(99999999.000000000000000);
        label_4 = new QLabel(Circle);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(200, 50, 71, 16));
        stackedWidget->addWidget(Circle);
        Rectangle = new QWidget();
        Rectangle->setObjectName("Rectangle");
        label_5 = new QLabel(Rectangle);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 71, 16));
        doubleSpinBoxRectangleWidthPixel = new QDoubleSpinBox(Rectangle);
        doubleSpinBoxRectangleWidthPixel->setObjectName("doubleSpinBoxRectangleWidthPixel");
        doubleSpinBoxRectangleWidthPixel->setGeometry(QRect(80, 0, 91, 22));
        doubleSpinBoxRectangleWidthPixel->setMaximum(99999999.000000000000000);
        doubleSpinBoxRectangleWidthMM = new QDoubleSpinBox(Rectangle);
        doubleSpinBoxRectangleWidthMM->setObjectName("doubleSpinBoxRectangleWidthMM");
        doubleSpinBoxRectangleWidthMM->setGeometry(QRect(80, 30, 91, 22));
        doubleSpinBoxRectangleWidthMM->setMaximum(99999999.000000000000000);
        label_6 = new QLabel(Rectangle);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(180, 30, 71, 16));
        label_7 = new QLabel(Rectangle);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(180, 0, 71, 16));
        label_8 = new QLabel(Rectangle);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(180, 100, 71, 16));
        label_9 = new QLabel(Rectangle);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(0, 70, 71, 16));
        label_10 = new QLabel(Rectangle);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(180, 70, 71, 16));
        doubleSpinBoxRectangleHeightMM = new QDoubleSpinBox(Rectangle);
        doubleSpinBoxRectangleHeightMM->setObjectName("doubleSpinBoxRectangleHeightMM");
        doubleSpinBoxRectangleHeightMM->setGeometry(QRect(80, 100, 91, 22));
        doubleSpinBoxRectangleHeightMM->setMaximum(99999999.000000000000000);
        doubleSpinBoxRectangleHeightPixel = new QDoubleSpinBox(Rectangle);
        doubleSpinBoxRectangleHeightPixel->setObjectName("doubleSpinBoxRectangleHeightPixel");
        doubleSpinBoxRectangleHeightPixel->setGeometry(QRect(80, 70, 91, 22));
        doubleSpinBoxRectangleHeightPixel->setMaximum(99999999.000000000000000);
        stackedWidget->addWidget(Rectangle);
        Obround = new QWidget();
        Obround->setObjectName("Obround");
        label_11 = new QLabel(Obround);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(190, 100, 71, 16));
        label_12 = new QLabel(Obround);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(190, 70, 71, 16));
        label_13 = new QLabel(Obround);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(190, 30, 71, 16));
        label_14 = new QLabel(Obround);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 0, 71, 16));
        doubleSpinBoxObroundWidthMM = new QDoubleSpinBox(Obround);
        doubleSpinBoxObroundWidthMM->setObjectName("doubleSpinBoxObroundWidthMM");
        doubleSpinBoxObroundWidthMM->setGeometry(QRect(90, 30, 91, 22));
        doubleSpinBoxObroundWidthMM->setMaximum(99999999.000000000000000);
        label_15 = new QLabel(Obround);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(190, 0, 71, 16));
        label_16 = new QLabel(Obround);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 70, 71, 16));
        doubleSpinBoxObroundWidthPixel = new QDoubleSpinBox(Obround);
        doubleSpinBoxObroundWidthPixel->setObjectName("doubleSpinBoxObroundWidthPixel");
        doubleSpinBoxObroundWidthPixel->setGeometry(QRect(90, 0, 91, 22));
        doubleSpinBoxObroundWidthPixel->setMaximum(99999999.000000000000000);
        doubleSpinBoxObroundHeightPixel = new QDoubleSpinBox(Obround);
        doubleSpinBoxObroundHeightPixel->setObjectName("doubleSpinBoxObroundHeightPixel");
        doubleSpinBoxObroundHeightPixel->setGeometry(QRect(90, 70, 91, 22));
        doubleSpinBoxObroundHeightPixel->setMaximum(99999999.000000000000000);
        doubleSpinBoxObroundHeightMM = new QDoubleSpinBox(Obround);
        doubleSpinBoxObroundHeightMM->setObjectName("doubleSpinBoxObroundHeightMM");
        doubleSpinBoxObroundHeightMM->setGeometry(QRect(90, 100, 91, 22));
        doubleSpinBoxObroundHeightMM->setMaximum(99999999.000000000000000);
        stackedWidget->addWidget(Obround);
        Polygon = new QWidget();
        Polygon->setObjectName("Polygon");
        label_17 = new QLabel(Polygon);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(0, 0, 71, 16));
        doubleSpinBoxPolygonDiameterPixel = new QDoubleSpinBox(Polygon);
        doubleSpinBoxPolygonDiameterPixel->setObjectName("doubleSpinBoxPolygonDiameterPixel");
        doubleSpinBoxPolygonDiameterPixel->setGeometry(QRect(80, 0, 91, 22));
        doubleSpinBoxPolygonDiameterPixel->setMaximum(99999999.000000000000000);
        doubleSpinBoxPolygonDiameterMM = new QDoubleSpinBox(Polygon);
        doubleSpinBoxPolygonDiameterMM->setObjectName("doubleSpinBoxPolygonDiameterMM");
        doubleSpinBoxPolygonDiameterMM->setGeometry(QRect(80, 30, 91, 22));
        doubleSpinBoxPolygonDiameterMM->setMaximum(99999999.000000000000000);
        label_18 = new QLabel(Polygon);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(180, 30, 71, 16));
        label_19 = new QLabel(Polygon);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(180, 0, 71, 16));
        label_20 = new QLabel(Polygon);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(0, 60, 71, 16));
        spinBoxPolygonSides = new QSpinBox(Polygon);
        spinBoxPolygonSides->setObjectName("spinBoxPolygonSides");
        spinBoxPolygonSides->setGeometry(QRect(92, 60, 81, 22));
        stackedWidget->addWidget(Polygon);
        pushButtonCreate = new QPushButton(CreateDCodeDialog);
        pushButtonCreate->setObjectName("pushButtonCreate");
        pushButtonCreate->setGeometry(QRect(20, 210, 101, 28));
        pushButtonCancel = new QPushButton(CreateDCodeDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 210, 101, 28));

        retranslateUi(CreateDCodeDialog);

        stackedWidget->setCurrentIndex(2);
        pushButtonCreate->setDefault(true);


        QMetaObject::connectSlotsByName(CreateDCodeDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateDCodeDialog)
    {
        CreateDCodeDialog->setWindowTitle(QCoreApplication::translate("CreateDCodeDialog", "Create DCode", nullptr));
        comboBoxType->setItemText(0, QCoreApplication::translate("CreateDCodeDialog", "Circle", nullptr));
        comboBoxType->setItemText(1, QCoreApplication::translate("CreateDCodeDialog", "Rectangle", nullptr));
        comboBoxType->setItemText(2, QCoreApplication::translate("CreateDCodeDialog", "Obround", nullptr));
        comboBoxType->setItemText(3, QCoreApplication::translate("CreateDCodeDialog", "Polygon", nullptr));

        label->setText(QCoreApplication::translate("CreateDCodeDialog", "D-Code number", nullptr));
        label_2->setText(QCoreApplication::translate("CreateDCodeDialog", "Diameter", nullptr));
        label_3->setText(QCoreApplication::translate("CreateDCodeDialog", "Pixels", nullptr));
        label_4->setText(QCoreApplication::translate("CreateDCodeDialog", "mm", nullptr));
        label_5->setText(QCoreApplication::translate("CreateDCodeDialog", "Width", nullptr));
        label_6->setText(QCoreApplication::translate("CreateDCodeDialog", "mm", nullptr));
        label_7->setText(QCoreApplication::translate("CreateDCodeDialog", "Pixels", nullptr));
        label_8->setText(QCoreApplication::translate("CreateDCodeDialog", "mm", nullptr));
        label_9->setText(QCoreApplication::translate("CreateDCodeDialog", "Height", nullptr));
        label_10->setText(QCoreApplication::translate("CreateDCodeDialog", "Pixels", nullptr));
        label_11->setText(QCoreApplication::translate("CreateDCodeDialog", "mm", nullptr));
        label_12->setText(QCoreApplication::translate("CreateDCodeDialog", "Pixels", nullptr));
        label_13->setText(QCoreApplication::translate("CreateDCodeDialog", "mm", nullptr));
        label_14->setText(QCoreApplication::translate("CreateDCodeDialog", "Width", nullptr));
        label_15->setText(QCoreApplication::translate("CreateDCodeDialog", "Pixels", nullptr));
        label_16->setText(QCoreApplication::translate("CreateDCodeDialog", "Height", nullptr));
        label_17->setText(QCoreApplication::translate("CreateDCodeDialog", "Diameter", nullptr));
        label_18->setText(QCoreApplication::translate("CreateDCodeDialog", "mm", nullptr));
        label_19->setText(QCoreApplication::translate("CreateDCodeDialog", "Pixels", nullptr));
        label_20->setText(QCoreApplication::translate("CreateDCodeDialog", "Sides", nullptr));
        pushButtonCreate->setText(QCoreApplication::translate("CreateDCodeDialog", "Create", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateDCodeDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateDCodeDialog: public Ui_CreateDCodeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEDCODEDIALOG_H
