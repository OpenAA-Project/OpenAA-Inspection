/********************************************************************************
** Form generated from reading UI file 'SelectFontDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTFONTDIALOG_H
#define UI_SELECTFONTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectFontDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditFont;
    QLineEdit *lineEditStyle;
    QLineEdit *lineEditSize;
    QLabel *label_3;
    QGroupBox *groupBox;
    QCheckBox *checkBoxStrikeOut;
    QCheckBox *checkBoxUnderline;
    QLabel *label_4;
    QComboBox *comboBoxSystem;
    QGroupBox *groupBox_2;
    QLineEdit *lineEditSample;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QListWidget *listWidgetFont;
    QListWidget *listWidgetStyle;
    QListWidget *listWidgetSize;

    void setupUi(QDialog *SelectFontDialog)
    {
        if (SelectFontDialog->objectName().isEmpty())
            SelectFontDialog->setObjectName("SelectFontDialog");
        SelectFontDialog->resize(494, 429);
        label = new QLabel(SelectFontDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 75, 18));
        label_2 = new QLabel(SelectFontDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(210, 10, 111, 18));
        lineEditFont = new QLineEdit(SelectFontDialog);
        lineEditFont->setObjectName("lineEditFont");
        lineEditFont->setGeometry(QRect(10, 30, 191, 31));
        lineEditStyle = new QLineEdit(SelectFontDialog);
        lineEditStyle->setObjectName("lineEditStyle");
        lineEditStyle->setGeometry(QRect(210, 30, 181, 31));
        lineEditSize = new QLineEdit(SelectFontDialog);
        lineEditSize->setObjectName("lineEditSize");
        lineEditSize->setGeometry(QRect(400, 30, 81, 31));
        label_3 = new QLabel(SelectFontDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(400, 10, 81, 18));
        groupBox = new QGroupBox(SelectFontDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 260, 191, 101));
        checkBoxStrikeOut = new QCheckBox(groupBox);
        checkBoxStrikeOut->setObjectName("checkBoxStrikeOut");
        checkBoxStrikeOut->setGeometry(QRect(20, 20, 161, 22));
        checkBoxUnderline = new QCheckBox(groupBox);
        checkBoxUnderline->setObjectName("checkBoxUnderline");
        checkBoxUnderline->setGeometry(QRect(20, 50, 161, 22));
        label_4 = new QLabel(SelectFontDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 370, 181, 18));
        comboBoxSystem = new QComboBox(SelectFontDialog);
        comboBoxSystem->setObjectName("comboBoxSystem");
        comboBoxSystem->setGeometry(QRect(20, 390, 181, 24));
        groupBox_2 = new QGroupBox(SelectFontDialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(210, 259, 271, 101));
        lineEditSample = new QLineEdit(groupBox_2);
        lineEditSample->setObjectName("lineEditSample");
        lineEditSample->setGeometry(QRect(20, 20, 231, 71));
        lineEditSample->setAlignment(Qt::AlignCenter);
        pushButtonOK = new QPushButton(SelectFontDialog);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(230, 380, 112, 34));
        pushButtonCancel = new QPushButton(SelectFontDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(370, 380, 112, 34));
        listWidgetFont = new QListWidget(SelectFontDialog);
        listWidgetFont->setObjectName("listWidgetFont");
        listWidgetFont->setGeometry(QRect(10, 60, 191, 192));
        listWidgetFont->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetStyle = new QListWidget(SelectFontDialog);
        listWidgetStyle->setObjectName("listWidgetStyle");
        listWidgetStyle->setGeometry(QRect(210, 60, 181, 192));
        listWidgetStyle->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidgetSize = new QListWidget(SelectFontDialog);
        listWidgetSize->setObjectName("listWidgetSize");
        listWidgetSize->setGeometry(QRect(400, 60, 81, 192));

        retranslateUi(SelectFontDialog);

        pushButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(SelectFontDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectFontDialog)
    {
        SelectFontDialog->setWindowTitle(QCoreApplication::translate("SelectFontDialog", "\343\203\225\343\202\251\343\203\263\343\203\210\351\201\270\346\212\236", nullptr));
        label->setText(QCoreApplication::translate("SelectFontDialog", "\343\203\225\343\202\251\343\203\263\343\203\210", nullptr));
        label_2->setText(QCoreApplication::translate("SelectFontDialog", "\343\203\225\343\202\251\343\203\263\343\203\210\343\202\271\343\202\277\343\202\244\343\203\253", nullptr));
        label_3->setText(QCoreApplication::translate("SelectFontDialog", "\343\202\265\343\202\244\343\202\272", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SelectFontDialog", "\345\212\271\346\236\234", nullptr));
        checkBoxStrikeOut->setText(QCoreApplication::translate("SelectFontDialog", "\345\274\267\350\252\277", nullptr));
        checkBoxUnderline->setText(QCoreApplication::translate("SelectFontDialog", "\344\270\213\347\267\232", nullptr));
        label_4->setText(QCoreApplication::translate("SelectFontDialog", "\346\217\217\347\224\273\343\202\267\343\202\271\343\203\206\343\203\240", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SelectFontDialog", "\344\276\213", nullptr));
        lineEditSample->setText(QCoreApplication::translate("SelectFontDialog", "AaBbYyZz", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectFontDialog", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectFontDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectFontDialog: public Ui_SelectFontDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTFONTDIALOG_H
