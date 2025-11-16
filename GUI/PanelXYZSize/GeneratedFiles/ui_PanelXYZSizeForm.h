/********************************************************************************
** Form generated from reading UI file 'PanelXYZSizeForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELXYZSIZEFORM_H
#define UI_PANELXYZSIZEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_PanelXYZSizeForm
{
public:
    QDoubleSpinBox *doubleSpinBoxX;
    QDoubleSpinBox *doubleSpinBoxY;
    QLabel *label_2;
    QPushButton *pushButtonSet;
    QLabel *label;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBoxZ;

    void setupUi(GUIFormBase *PanelXYZSizeForm)
    {
        if (PanelXYZSizeForm->objectName().isEmpty())
            PanelXYZSizeForm->setObjectName("PanelXYZSizeForm");
        PanelXYZSizeForm->resize(275, 63);
        doubleSpinBoxX = new QDoubleSpinBox(PanelXYZSizeForm);
        doubleSpinBoxX->setObjectName("doubleSpinBoxX");
        doubleSpinBoxX->setGeometry(QRect(120, 0, 81, 22));
        QFont font;
        font.setPointSize(12);
        doubleSpinBoxX->setFont(font);
        doubleSpinBoxX->setMaximum(999.990000000000009);
        doubleSpinBoxY = new QDoubleSpinBox(PanelXYZSizeForm);
        doubleSpinBoxY->setObjectName("doubleSpinBoxY");
        doubleSpinBoxY->setGeometry(QRect(120, 20, 81, 22));
        doubleSpinBoxY->setFont(font);
        doubleSpinBoxY->setMaximum(9999.989999999999782);
        label_2 = new QLabel(PanelXYZSizeForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 111, 21));
        QFont font1;
        font1.setPointSize(10);
        label_2->setFont(font1);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        pushButtonSet = new QPushButton(PanelXYZSizeForm);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(200, 0, 71, 61));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSet->setIcon(icon);
        label = new QLabel(PanelXYZSizeForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 111, 21));
        label->setFont(font1);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(PanelXYZSizeForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 40, 111, 21));
        label_3->setFont(font1);
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        doubleSpinBoxZ = new QDoubleSpinBox(PanelXYZSizeForm);
        doubleSpinBoxZ->setObjectName("doubleSpinBoxZ");
        doubleSpinBoxZ->setGeometry(QRect(120, 40, 81, 22));
        doubleSpinBoxZ->setFont(font);
        doubleSpinBoxZ->setMaximum(9999.989999999999782);

        retranslateUi(PanelXYZSizeForm);

        QMetaObject::connectSlotsByName(PanelXYZSizeForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PanelXYZSizeForm)
    {
        PanelXYZSizeForm->setWindowTitle(QCoreApplication::translate("PanelXYZSizeForm", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("PanelXYZSizeForm", "Length(Y size)", nullptr));
        pushButtonSet->setText(QCoreApplication::translate("PanelXYZSizeForm", "Set", nullptr));
        label->setText(QCoreApplication::translate("PanelXYZSizeForm", "Width(X size)", nullptr));
        label_3->setText(QCoreApplication::translate("PanelXYZSizeForm", "Thickness(Z)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PanelXYZSizeForm: public Ui_PanelXYZSizeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELXYZSIZEFORM_H
