/********************************************************************************
** Form generated from reading UI file 'SelectExpandableAlgorithmForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTEXPANDABLEALGORITHMFORM_H
#define UI_SELECTEXPANDABLEALGORITHMFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectExpandableAlgorithmFormClass
{
public:
    QFrame *frameCheckbox;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *SelectExpandableAlgorithmFormClass)
    {
        if (SelectExpandableAlgorithmFormClass->objectName().isEmpty())
            SelectExpandableAlgorithmFormClass->setObjectName("SelectExpandableAlgorithmFormClass");
        SelectExpandableAlgorithmFormClass->resize(369, 290);
        frameCheckbox = new QFrame(SelectExpandableAlgorithmFormClass);
        frameCheckbox->setObjectName("frameCheckbox");
        frameCheckbox->setGeometry(QRect(10, 10, 351, 231));
        frameCheckbox->setFrameShape(QFrame::StyledPanel);
        frameCheckbox->setFrameShadow(QFrame::Sunken);
        pushButtonOK = new QPushButton(SelectExpandableAlgorithmFormClass);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(140, 250, 77, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon);

        retranslateUi(SelectExpandableAlgorithmFormClass);

        QMetaObject::connectSlotsByName(SelectExpandableAlgorithmFormClass);
    } // setupUi

    void retranslateUi(QDialog *SelectExpandableAlgorithmFormClass)
    {
        SelectExpandableAlgorithmFormClass->setWindowTitle(QCoreApplication::translate("SelectExpandableAlgorithmFormClass", "Select expandable Algorithm", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("SelectExpandableAlgorithmFormClass", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectExpandableAlgorithmFormClass: public Ui_SelectExpandableAlgorithmFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTEXPANDABLEALGORITHMFORM_H
