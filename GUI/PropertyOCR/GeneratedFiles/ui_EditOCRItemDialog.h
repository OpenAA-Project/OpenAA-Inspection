/********************************************************************************
** Form generated from reading UI file 'EditOCRItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOCRITEMDIALOG_H
#define UI_EDITOCRITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditOCRItemDialog
{
public:
    QGroupBox *groupBox;
    QCheckBox *checkBoxInspectMatching;
    QCheckBox *checkBoxSaveIntoResult;
    QCheckBox *checkBoxOKByFailingRecognition;
    QFrame *frame;
    QLabel *label;
    QListWidget *listWidgetMatchingList;
    QPushButton *ButtonDeleteItem;
    QPushButton *pushButtonClose;
    QPushButton *ButtonSaveNewItem;
    QPushButton *ButtonUpdateItem;
    QFrame *frame_2;
    QSpinBox *spinBoxRegNumber;
    QLabel *label_3;
    QPushButton *pushButtonAddMatchingList;
    QPushButton *pushButtonSubMatchingList;
    QLineEdit *lineEditItemName;
    QLabel *label_4;
    QPushButton *pushButtonPickupColor;
    QPushButton *pushButtonPickupBrightness;
    QFrame *frame_3;
    QPushButton *pushButtonRotation90;
    QPushButton *pushButtonRotation0;
    QPushButton *pushButton180;
    QPushButton *pushButton270;
    QLabel *label_5;
    QSpinBox *spinBoxRotation;

    void setupUi(QDialog *EditOCRItemDialog)
    {
        if (EditOCRItemDialog->objectName().isEmpty())
            EditOCRItemDialog->setObjectName("EditOCRItemDialog");
        EditOCRItemDialog->resize(431, 724);
        groupBox = new QGroupBox(EditOCRItemDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 40, 291, 81));
        checkBoxInspectMatching = new QCheckBox(groupBox);
        checkBoxInspectMatching->setObjectName("checkBoxInspectMatching");
        checkBoxInspectMatching->setGeometry(QRect(20, 10, 161, 22));
        checkBoxSaveIntoResult = new QCheckBox(groupBox);
        checkBoxSaveIntoResult->setObjectName("checkBoxSaveIntoResult");
        checkBoxSaveIntoResult->setGeometry(QRect(20, 30, 211, 22));
        checkBoxOKByFailingRecognition = new QCheckBox(groupBox);
        checkBoxOKByFailingRecognition->setObjectName("checkBoxOKByFailingRecognition");
        checkBoxOKByFailingRecognition->setGeometry(QRect(20, 50, 241, 22));
        frame = new QFrame(EditOCRItemDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 130, 291, 301));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 291, 31));
        label->setAlignment(Qt::AlignCenter);
        listWidgetMatchingList = new QListWidget(frame);
        listWidgetMatchingList->setObjectName("listWidgetMatchingList");
        listWidgetMatchingList->setGeometry(QRect(10, 40, 271, 251));
        ButtonDeleteItem = new QPushButton(EditOCRItemDialog);
        ButtonDeleteItem->setObjectName("ButtonDeleteItem");
        ButtonDeleteItem->setGeometry(QRect(40, 640, 121, 31));
        QFont font;
        font.setPointSize(11);
        ButtonDeleteItem->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonDeleteItem->setIcon(icon);
        pushButtonClose = new QPushButton(EditOCRItemDialog);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(310, 680, 101, 31));
        pushButtonClose->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon1);
        ButtonSaveNewItem = new QPushButton(EditOCRItemDialog);
        ButtonSaveNewItem->setObjectName("ButtonSaveNewItem");
        ButtonSaveNewItem->setGeometry(QRect(170, 640, 131, 31));
        ButtonSaveNewItem->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSaveNewItem->setIcon(icon2);
        ButtonUpdateItem = new QPushButton(EditOCRItemDialog);
        ButtonUpdateItem->setObjectName("ButtonUpdateItem");
        ButtonUpdateItem->setGeometry(QRect(310, 640, 101, 31));
        ButtonUpdateItem->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonUpdateItem->setIcon(icon3);
        frame_2 = new QFrame(EditOCRItemDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(310, 130, 111, 91));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        spinBoxRegNumber = new QSpinBox(frame_2);
        spinBoxRegNumber->setObjectName("spinBoxRegNumber");
        spinBoxRegNumber->setGeometry(QRect(10, 30, 91, 22));
        spinBoxRegNumber->setMinimum(400);
        spinBoxRegNumber->setMaximum(499);
        spinBoxRegNumber->setValue(400);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 91, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonAddMatchingList = new QPushButton(EditOCRItemDialog);
        pushButtonAddMatchingList->setObjectName("pushButtonAddMatchingList");
        pushButtonAddMatchingList->setGeometry(QRect(50, 440, 51, 34));
        pushButtonSubMatchingList = new QPushButton(EditOCRItemDialog);
        pushButtonSubMatchingList->setObjectName("pushButtonSubMatchingList");
        pushButtonSubMatchingList->setGeometry(QRect(210, 440, 51, 34));
        lineEditItemName = new QLineEdit(EditOCRItemDialog);
        lineEditItemName->setObjectName("lineEditItemName");
        lineEditItemName->setGeometry(QRect(150, 10, 221, 24));
        label_4 = new QLabel(EditOCRItemDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 10, 121, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonPickupColor = new QPushButton(EditOCRItemDialog);
        pushButtonPickupColor->setObjectName("pushButtonPickupColor");
        pushButtonPickupColor->setGeometry(QRect(310, 230, 112, 51));
        pushButtonPickupBrightness = new QPushButton(EditOCRItemDialog);
        pushButtonPickupBrightness->setObjectName("pushButtonPickupBrightness");
        pushButtonPickupBrightness->setGeometry(QRect(310, 290, 112, 51));
        frame_3 = new QFrame(EditOCRItemDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 480, 411, 111));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        pushButtonRotation90 = new QPushButton(frame_3);
        pushButtonRotation90->setObjectName("pushButtonRotation90");
        pushButtonRotation90->setGeometry(QRect(10, 40, 41, 41));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Deg270.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonRotation90->setIcon(icon4);
        pushButtonRotation0 = new QPushButton(frame_3);
        pushButtonRotation0->setObjectName("pushButtonRotation0");
        pushButtonRotation0->setGeometry(QRect(60, 10, 41, 41));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Deg0.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonRotation0->setIcon(icon5);
        pushButton180 = new QPushButton(frame_3);
        pushButton180->setObjectName("pushButton180");
        pushButton180->setGeometry(QRect(60, 60, 41, 41));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Deg180.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton180->setIcon(icon6);
        pushButton270 = new QPushButton(frame_3);
        pushButton270->setObjectName("pushButton270");
        pushButton270->setGeometry(QRect(110, 40, 41, 41));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Qtres/Deg90.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton270->setIcon(icon7);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(210, 20, 91, 20));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        spinBoxRotation = new QSpinBox(frame_3);
        spinBoxRotation->setObjectName("spinBoxRotation");
        spinBoxRotation->setGeometry(QRect(210, 40, 91, 22));
        spinBoxRotation->setMinimum(0);
        spinBoxRotation->setMaximum(359);
        spinBoxRotation->setValue(0);

        retranslateUi(EditOCRItemDialog);

        QMetaObject::connectSlotsByName(EditOCRItemDialog);
    } // setupUi

    void retranslateUi(QDialog *EditOCRItemDialog)
    {
        EditOCRItemDialog->setWindowTitle(QCoreApplication::translate("EditOCRItemDialog", "Dialog", nullptr));
        groupBox->setTitle(QString());
        checkBoxInspectMatching->setText(QCoreApplication::translate("EditOCRItemDialog", "Inspect matching", nullptr));
        checkBoxSaveIntoResult->setText(QCoreApplication::translate("EditOCRItemDialog", "Save into result", nullptr));
        checkBoxOKByFailingRecognition->setText(QCoreApplication::translate("EditOCRItemDialog", "OK by failing recognition", nullptr));
        label->setText(QCoreApplication::translate("EditOCRItemDialog", "Matching list (Regular expression)", nullptr));
        ButtonDeleteItem->setText(QCoreApplication::translate("EditOCRItemDialog", "Delete", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditOCRItemDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
        ButtonSaveNewItem->setText(QCoreApplication::translate("EditOCRItemDialog", "Create New", nullptr));
        ButtonUpdateItem->setText(QCoreApplication::translate("EditOCRItemDialog", "Update", nullptr));
        label_3->setText(QCoreApplication::translate("EditOCRItemDialog", "Reg No (Q)", nullptr));
        pushButtonAddMatchingList->setText(QCoreApplication::translate("EditOCRItemDialog", "+", nullptr));
        pushButtonSubMatchingList->setText(QCoreApplication::translate("EditOCRItemDialog", "-", nullptr));
        label_4->setText(QCoreApplication::translate("EditOCRItemDialog", "Item name", nullptr));
        pushButtonPickupColor->setText(QCoreApplication::translate("EditOCRItemDialog", "Color map", nullptr));
        pushButtonPickupBrightness->setText(QCoreApplication::translate("EditOCRItemDialog", "Brightness", nullptr));
        pushButtonRotation90->setText(QString());
        pushButtonRotation0->setText(QString());
        pushButton180->setText(QString());
        pushButton270->setText(QString());
        label_5->setText(QCoreApplication::translate("EditOCRItemDialog", "Rotation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditOCRItemDialog: public Ui_EditOCRItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOCRITEMDIALOG_H
