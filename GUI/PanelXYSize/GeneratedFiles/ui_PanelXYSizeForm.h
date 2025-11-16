/********************************************************************************
** Form generated from reading UI file 'PanelXYSizeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELXYSIZEFORM_H
#define UI_PANELXYSIZEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PanelXYSizeForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxX;
    QDoubleSpinBox *doubleSpinBoxY;
    QPushButton *pushButtonSet;

    void setupUi(GUIFormBase *PanelXYSizeForm)
    {
        if (PanelXYSizeForm->objectName().isEmpty())
            PanelXYSizeForm->setObjectName("PanelXYSizeForm");
        PanelXYSizeForm->resize(262, 41);
        label = new QLabel(PanelXYSizeForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 101, 21));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(PanelXYSizeForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 111, 21));
        label_2->setFont(font);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxX = new QDoubleSpinBox(PanelXYSizeForm);
        doubleSpinBoxX->setObjectName("doubleSpinBoxX");
        doubleSpinBoxX->setGeometry(QRect(120, 0, 81, 22));
        QFont font1;
        font1.setPointSize(12);
        doubleSpinBoxX->setFont(font1);
        doubleSpinBoxX->setMaximum(999.990000000000009);
        doubleSpinBoxY = new QDoubleSpinBox(PanelXYSizeForm);
        doubleSpinBoxY->setObjectName("doubleSpinBoxY");
        doubleSpinBoxY->setGeometry(QRect(120, 20, 81, 22));
        doubleSpinBoxY->setFont(font1);
        doubleSpinBoxY->setMaximum(9999.989999999999782);
        pushButtonSet = new QPushButton(PanelXYSizeForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(200, 0, 61, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);

        retranslateUi(PanelXYSizeForm);

        QMetaObject::connectSlotsByName(PanelXYSizeForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PanelXYSizeForm)
    {
        PanelXYSizeForm->setWindowTitle(QCoreApplication::translate("PanelXYSizeForm", "Panel XY Size", nullptr));
        label->setText(QCoreApplication::translate("PanelXYSizeForm", "Width(X size)", nullptr));
        label_2->setText(QCoreApplication::translate("PanelXYSizeForm", "Length(Y size)", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("PanelXYSizeForm", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PanelXYSizeForm: public Ui_PanelXYSizeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELXYSIZEFORM_H
