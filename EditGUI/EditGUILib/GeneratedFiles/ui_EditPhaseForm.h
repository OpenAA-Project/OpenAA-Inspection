/********************************************************************************
** Form generated from reading UI file 'EditPhaseForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPHASEFORM_H
#define UI_EDITPHASEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditPhaseForm
{
public:
    QPushButton *pushButtonCopy;
    QComboBox *comboBoxPhase;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;
    QPushButton *pushButtonPaste;
    QPushButton *pushButtonOK;
    QSpinBox *spinBoxSource;
    QPushButton *pushButtonSaveFilter;

    void setupUi(QWidget *EditPhaseForm)
    {
        if (EditPhaseForm->objectName().isEmpty())
            EditPhaseForm->setObjectName("EditPhaseForm");
        EditPhaseForm->resize(475, 321);
        pushButtonCopy = new QPushButton(EditPhaseForm);
        pushButtonCopy->setObjectName("pushButtonCopy");
        pushButtonCopy->setGeometry(QRect(390, 80, 75, 31));
        comboBoxPhase = new QComboBox(EditPhaseForm);
        comboBoxPhase->setObjectName("comboBoxPhase");
        comboBoxPhase->setGeometry(QRect(140, 10, 91, 22));
        label = new QLabel(EditPhaseForm);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 10, 71, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(EditPhaseForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 40, 71, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        frame = new QFrame(EditPhaseForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 70, 371, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        pushButtonPaste = new QPushButton(EditPhaseForm);
        pushButtonPaste->setObjectName("pushButtonPaste");
        pushButtonPaste->setGeometry(QRect(390, 120, 75, 31));
        pushButtonOK = new QPushButton(EditPhaseForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(130, 280, 131, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);
        spinBoxSource = new QSpinBox(EditPhaseForm);
        spinBoxSource->setObjectName("spinBoxSource");
        spinBoxSource->setGeometry(QRect(140, 40, 91, 22));
        spinBoxSource->setMaximum(9999);
        pushButtonSaveFilter = new QPushButton(EditPhaseForm);
        pushButtonSaveFilter->setObjectName("pushButtonSaveFilter");
        pushButtonSaveFilter->setGeometry(QRect(280, 280, 91, 31));

        retranslateUi(EditPhaseForm);

        QMetaObject::connectSlotsByName(EditPhaseForm);
    } // setupUi

    void retranslateUi(QWidget *EditPhaseForm)
    {
        EditPhaseForm->setWindowTitle(QCoreApplication::translate("EditPhaseForm", "Form", nullptr));
        pushButtonCopy->setText(QCoreApplication::translate("EditPhaseForm", "Copy", nullptr));
        label->setText(QCoreApplication::translate("EditPhaseForm", "Phase", nullptr));
        label_2->setText(QCoreApplication::translate("EditPhaseForm", "Source", nullptr));
        pushButtonPaste->setText(QCoreApplication::translate("EditPhaseForm", "Paste", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("EditPhaseForm", "OK", nullptr));
        pushButtonSaveFilter->setText(QCoreApplication::translate("EditPhaseForm", "Save filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditPhaseForm: public Ui_EditPhaseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPHASEFORM_H
