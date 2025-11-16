/********************************************************************************
** Form generated from reading UI file 'EditLineMoveDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLINEMOVEDIALOG_H
#define UI_EDITLINEMOVEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditLineMoveDialog
{
public:
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QPushButton *ButtonOK;
    QPushButton *ButtonCancel;
    QLineEdit *EditName;
    QLabel *label_6;
    QLabel *label_93;
    QLabel *label_95;
    QSpinBox *EditEdgeWidth;
    QDoubleSpinBox *doubleSpinBoxThresholdP;
    QDoubleSpinBox *doubleSpinBoxThresholdM;
    QLabel *label_94;
    QCheckBox *checkBoxPrevailLeft;
    QCheckBox *checkBoxPrevailRight;

    void setupUi(QDialog *EditLineMoveDialog)
    {
        if (EditLineMoveDialog->objectName().isEmpty())
            EditLineMoveDialog->setObjectName("EditLineMoveDialog");
        EditLineMoveDialog->resize(348, 343);
        label_92 = new QLabel(EditLineMoveDialog);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(30, 140, 161, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(EditLineMoveDialog);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(200, 140, 71, 22));
        EditSearchDot->setMaximum(100);
        ButtonOK = new QPushButton(EditLineMoveDialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(20, 270, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon);
        ButtonCancel = new QPushButton(EditLineMoveDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(220, 270, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        EditName = new QLineEdit(EditLineMoveDialog);
        EditName->setObjectName("EditName");
        EditName->setGeometry(QRect(90, 10, 231, 31));
        QFont font;
        font.setPointSize(12);
        EditName->setFont(font);
        label_6 = new QLabel(EditLineMoveDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 10, 81, 31));
        QFont font1;
        font1.setPointSize(9);
        label_6->setFont(font1);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_93 = new QLabel(EditLineMoveDialog);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(30, 50, 161, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_95 = new QLabel(EditLineMoveDialog);
        label_95->setObjectName("label_95");
        label_95->setGeometry(QRect(30, 100, 161, 21));
        label_95->setFrameShape(QFrame::Panel);
        label_95->setFrameShadow(QFrame::Sunken);
        label_95->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditEdgeWidth = new QSpinBox(EditLineMoveDialog);
        EditEdgeWidth->setObjectName("EditEdgeWidth");
        EditEdgeWidth->setGeometry(QRect(200, 100, 71, 22));
        EditEdgeWidth->setMaximum(255);
        doubleSpinBoxThresholdP = new QDoubleSpinBox(EditLineMoveDialog);
        doubleSpinBoxThresholdP->setObjectName("doubleSpinBoxThresholdP");
        doubleSpinBoxThresholdP->setGeometry(QRect(200, 70, 101, 22));
        doubleSpinBoxThresholdP->setMaximum(99999999.000000000000000);
        doubleSpinBoxThresholdM = new QDoubleSpinBox(EditLineMoveDialog);
        doubleSpinBoxThresholdM->setObjectName("doubleSpinBoxThresholdM");
        doubleSpinBoxThresholdM->setGeometry(QRect(200, 50, 101, 22));
        doubleSpinBoxThresholdM->setMaximum(99999999.000000000000000);
        label_94 = new QLabel(EditLineMoveDialog);
        label_94->setObjectName("label_94");
        label_94->setGeometry(QRect(30, 70, 161, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxPrevailLeft = new QCheckBox(EditLineMoveDialog);
        checkBoxPrevailLeft->setObjectName("checkBoxPrevailLeft");
        checkBoxPrevailLeft->setGeometry(QRect(30, 180, 191, 21));
        checkBoxPrevailRight = new QCheckBox(EditLineMoveDialog);
        checkBoxPrevailRight->setObjectName("checkBoxPrevailRight");
        checkBoxPrevailRight->setGeometry(QRect(30, 210, 191, 21));

        retranslateUi(EditLineMoveDialog);

        ButtonOK->setDefault(true);


        QMetaObject::connectSlotsByName(EditLineMoveDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLineMoveDialog)
    {
        EditLineMoveDialog->setWindowTitle(QCoreApplication::translate("EditLineMoveDialog", "Edit LineMove", nullptr));
        label_92->setText(QCoreApplication::translate("EditLineMoveDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        ButtonOK->setText(QCoreApplication::translate("EditLineMoveDialog", "OK", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("EditLineMoveDialog", "Cancel", nullptr));
        EditName->setText(QString());
        label_6->setText(QCoreApplication::translate("EditLineMoveDialog", "\345\200\213\345\210\245\345\220\215\347\247\260", nullptr));
        label_93->setText(QCoreApplication::translate("EditLineMoveDialog", "\343\202\272\343\203\254\343\200\200\344\270\213\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_95->setText(QCoreApplication::translate("EditLineMoveDialog", "\350\274\252\351\203\255\345\271\205", nullptr));
        label_94->setText(QCoreApplication::translate("EditLineMoveDialog", "\343\202\272\343\203\254\343\200\200\344\270\212\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        checkBoxPrevailLeft->setText(QCoreApplication::translate("EditLineMoveDialog", "Prevail left brightness", nullptr));
        checkBoxPrevailRight->setText(QCoreApplication::translate("EditLineMoveDialog", "Prevail right brightness", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLineMoveDialog: public Ui_EditLineMoveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLINEMOVEDIALOG_H
