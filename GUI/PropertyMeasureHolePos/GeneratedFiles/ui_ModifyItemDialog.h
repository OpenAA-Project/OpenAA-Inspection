/********************************************************************************
** Form generated from reading UI file 'ModifyItemDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYITEMDIALOG_H
#define UI_MODIFYITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ModifyItemDialog
{
public:
    QLineEdit *EditName;
    QLabel *label_6;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxDiaPrecision;
    QLabel *label_5;
    QSpinBox *spinBoxBandWidth;
    QSpinBox *spinBoxNoiseSize;
    QDoubleSpinBox *doubleSpinBoxPosPrecision;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;

    void setupUi(QDialog *ModifyItemDialog)
    {
        if (ModifyItemDialog->objectName().isEmpty())
            ModifyItemDialog->setObjectName("ModifyItemDialog");
        ModifyItemDialog->resize(344, 237);
        EditName = new QLineEdit(ModifyItemDialog);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(100, 10, 231, 31));
        QFont font;
        font.setPointSize(12);
        EditName->setFont(font);
        label_6 = new QLabel(ModifyItemDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 10, 81, 31));
        QFont font1;
        font1.setPointSize(9);
        label_6->setFont(font1);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_92 = new QLabel(ModifyItemDialog);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(40, 140, 181, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(ModifyItemDialog);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(230, 140, 81, 22));
        EditSearchDot->setMaximum(100);
        label = new QLabel(ModifyItemDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 50, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxDiaPrecision = new QDoubleSpinBox(ModifyItemDialog);
        doubleSpinBoxDiaPrecision->setObjectName("doubleSpinBoxDiaPrecision");
        doubleSpinBoxDiaPrecision->setGeometry(QRect(230, 50, 81, 22));
        label_5 = new QLabel(ModifyItemDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 110, 181, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxBandWidth = new QSpinBox(ModifyItemDialog);
        spinBoxBandWidth->setObjectName("spinBoxBandWidth");
        spinBoxBandWidth->setGeometry(QRect(230, 110, 81, 22));
        spinBoxNoiseSize = new QSpinBox(ModifyItemDialog);
        spinBoxNoiseSize->setObjectName("spinBoxNoiseSize");
        spinBoxNoiseSize->setGeometry(QRect(230, 90, 81, 22));
        doubleSpinBoxPosPrecision = new QDoubleSpinBox(ModifyItemDialog);
        doubleSpinBoxPosPrecision->setObjectName("doubleSpinBoxPosPrecision");
        doubleSpinBoxPosPrecision->setGeometry(QRect(230, 70, 81, 22));
        label_3 = new QLabel(ModifyItemDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 90, 181, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(ModifyItemDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 70, 181, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonOK = new QPushButton(ModifyItemDialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(30, 180, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(ModifyItemDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(210, 180, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);

        retranslateUi(ModifyItemDialog);

        QMetaObject::connectSlotsByName(ModifyItemDialog);
    } // setupUi

    void retranslateUi(QDialog *ModifyItemDialog)
    {
        ModifyItemDialog->setWindowTitle(QCoreApplication::translate("ModifyItemDialog", "Modify Item", nullptr));
        EditName->setText(QString());
        label_6->setText(QCoreApplication::translate("ModifyItemDialog", "\345\200\213\345\210\245\345\220\215\347\247\260", nullptr));
        label_92->setText(QCoreApplication::translate("ModifyItemDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label->setText(QCoreApplication::translate("ModifyItemDialog", "\347\251\264\345\276\204\347\262\276\345\272\246", nullptr));
        label_5->setText(QCoreApplication::translate("ModifyItemDialog", "\345\270\257\345\271\205", nullptr));
        label_3->setText(QCoreApplication::translate("ModifyItemDialog", "\343\203\216\343\202\244\343\202\272\343\202\265\343\202\244\343\202\272", nullptr));
        label_2->setText(QCoreApplication::translate("ModifyItemDialog", "\344\275\215\347\275\256\347\262\276\345\272\246", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ModifyItemDialog", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ModifyItemDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModifyItemDialog: public Ui_ModifyItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYITEMDIALOG_H
