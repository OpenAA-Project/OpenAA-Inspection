/********************************************************************************
** Form generated from reading UI file 'ChooseAutoGenerationDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEAUTOGENERATIONDIALOG_H
#define UI_CHOOSEAUTOGENERATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChooseAutoGenerationDialog
{
public:
    QPushButton *PushButtonAutoGenerate;
    QPushButton *PushButtonNext;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *ChooseAutoGenerationDialog)
    {
        if (ChooseAutoGenerationDialog->objectName().isEmpty())
            ChooseAutoGenerationDialog->setObjectName("ChooseAutoGenerationDialog");
        ChooseAutoGenerationDialog->resize(376, 217);
        PushButtonAutoGenerate = new QPushButton(ChooseAutoGenerationDialog);
        PushButtonAutoGenerate->setObjectName("PushButtonAutoGenerate");
        PushButtonAutoGenerate->setGeometry(QRect(10, 50, 161, 71));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Unicode MS")});
        font.setPointSize(24);
        PushButtonAutoGenerate->setFont(font);
        PushButtonAutoGenerate->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(100,254, 100, 255), stop:1 rgba(60, 165, 60, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(60, 165, 60, 255), stop:1 rgba(100, 254, 100, 255));\n"
"}"));
        PushButtonAutoGenerate->setCheckable(false);
        PushButtonAutoGenerate->setChecked(false);
        PushButtonAutoGenerate->setAutoExclusive(false);
        PushButtonAutoGenerate->setAutoDefault(false);
        PushButtonAutoGenerate->setFlat(false);
        PushButtonNext = new QPushButton(ChooseAutoGenerationDialog);
        PushButtonNext->setObjectName("PushButtonNext");
        PushButtonNext->setGeometry(QRect(190, 50, 171, 71));
        PushButtonNext->setFont(font);
        PushButtonNext->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 25px;\n"
"	border-color: gray;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(254, 100, 100, 255), stop:1 rgba(160, 80, 80, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(160, 80, 80, 255), stop:1 rgba(220, 100, 100, 60));\n"
"}"));
        PushButtonNext->setCheckable(false);
        PushButtonNext->setChecked(false);
        PushButtonNext->setAutoExclusive(false);
        PushButtonNext->setAutoDefault(false);
        PushButtonNext->setFlat(false);
        label = new QLabel(ChooseAutoGenerationDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 130, 301, 71));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label->setWordWrap(true);
        label_2 = new QLabel(ChooseAutoGenerationDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 7, 301, 31));
        QFont font2;
        font2.setPointSize(14);
        label_2->setFont(font2);

        retranslateUi(ChooseAutoGenerationDialog);

        PushButtonAutoGenerate->setDefault(false);
        PushButtonNext->setDefault(false);


        QMetaObject::connectSlotsByName(ChooseAutoGenerationDialog);
    } // setupUi

    void retranslateUi(QDialog *ChooseAutoGenerationDialog)
    {
        ChooseAutoGenerationDialog->setWindowTitle(QCoreApplication::translate("ChooseAutoGenerationDialog", "Dialog", nullptr));
        PushButtonAutoGenerate->setText(QCoreApplication::translate("ChooseAutoGenerationDialog", "\343\201\257\343\201\204", nullptr));
        PushButtonNext->setText(QCoreApplication::translate("ChooseAutoGenerationDialog", "\343\201\204\343\201\204\343\201\210", nullptr));
        label->setText(QCoreApplication::translate("ChooseAutoGenerationDialog", "CAD\343\203\207\343\203\274\343\202\277\343\200\201\343\203\236\343\202\271\343\202\257\343\200\201\344\275\215\347\275\256\345\220\210\343\202\217\343\201\233\343\202\222\345\244\211\346\233\264\343\201\227\343\201\237\345\240\264\345\220\210\343\200\201\350\207\252\345\213\225\347\224\237\346\210\220\343\201\214\345\277\205\350\246\201\343\201\247\343\201\231\343\200\202", nullptr));
        label_2->setText(QCoreApplication::translate("ChooseAutoGenerationDialog", "\350\207\252\345\213\225\347\224\237\346\210\220\343\201\227\343\201\276\343\201\231\343\201\213\357\274\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseAutoGenerationDialog: public Ui_ChooseAutoGenerationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEAUTOGENERATIONDIALOG_H
