/********************************************************************************
** Form generated from reading UI file 'EditLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYDIALOG_H
#define UI_EDITLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditLibraryDialog
{
public:
    QLabel *label_3;
    QComboBox *comboBoxLibTypeSelect;
    QTableWidget *tableWidgetItems;
    QLabel *label_4;
    QSpinBox *spinBoxPage;
    QSpinBox *spinBoxLayer;
    QLabel *label_5;
    QPushButton *pushButtonFindItem;
    QFrame *frame;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEditName;
    QLineEdit *lineEditRemark;
    QCheckBox *checkBox;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *EditLibraryDialog)
    {
        if (EditLibraryDialog->objectName().isEmpty())
            EditLibraryDialog->setObjectName("EditLibraryDialog");
        EditLibraryDialog->resize(283, 538);
        label_3 = new QLabel(EditLibraryDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 261, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        comboBoxLibTypeSelect = new QComboBox(EditLibraryDialog);
        comboBoxLibTypeSelect->setObjectName("comboBoxLibTypeSelect");
        comboBoxLibTypeSelect->setGeometry(QRect(10, 30, 261, 22));
        tableWidgetItems = new QTableWidget(EditLibraryDialog);
        if (tableWidgetItems->columnCount() < 2)
            tableWidgetItems->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetItems->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetItems->setObjectName("tableWidgetItems");
        tableWidgetItems->setGeometry(QRect(10, 170, 256, 192));
        label_4 = new QLabel(EditLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 70, 171, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        spinBoxPage = new QSpinBox(EditLibraryDialog);
        spinBoxPage->setObjectName("spinBoxPage");
        spinBoxPage->setGeometry(QRect(190, 70, 61, 22));
        spinBoxLayer = new QSpinBox(EditLibraryDialog);
        spinBoxLayer->setObjectName("spinBoxLayer");
        spinBoxLayer->setGeometry(QRect(190, 100, 61, 22));
        label_5 = new QLabel(EditLibraryDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 100, 171, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        pushButtonFindItem = new QPushButton(EditLibraryDialog);
        pushButtonFindItem->setObjectName("pushButtonFindItem");
        pushButtonFindItem->setGeometry(QRect(80, 130, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonFindItem->setIcon(icon);
        frame = new QFrame(EditLibraryDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 380, 251, 101));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 61, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 40, 61, 21));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        lineEditName = new QLineEdit(frame);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(80, 10, 161, 21));
        lineEditRemark = new QLineEdit(frame);
        lineEditRemark->setObjectName("lineEditRemark");
        lineEditRemark->setGeometry(QRect(80, 40, 161, 21));
        checkBox = new QCheckBox(frame);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(10, 70, 231, 19));
        pushButtonOK = new QPushButton(EditLibraryDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(20, 490, 93, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon1);
        pushButtonCancel = new QPushButton(EditLibraryDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(150, 490, 93, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon2);

        retranslateUi(EditLibraryDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryDialog)
    {
        EditLibraryDialog->setWindowTitle(QCoreApplication::translate("EditLibraryDialog", "Edit Library", nullptr));
        label_3->setText(QCoreApplication::translate("EditLibraryDialog", "Select library - source", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetItems->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryDialog", "ItemID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetItems->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryDialog", "ItemName", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryDialog", "Page", nullptr));
        label_5->setText(QCoreApplication::translate("EditLibraryDialog", "Layer", nullptr));
        pushButtonFindItem->setText(QCoreApplication::translate("EditLibraryDialog", "Find item", nullptr));
        label_6->setText(QCoreApplication::translate("EditLibraryDialog", "Name", nullptr));
        label_7->setText(QCoreApplication::translate("EditLibraryDialog", "Remark", nullptr));
        checkBox->setText(QCoreApplication::translate("EditLibraryDialog", "Conclusion", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditLibraryDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditLibraryDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryDialog: public Ui_EditLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYDIALOG_H
