/********************************************************************************
** Form generated from reading UI file 'ClosingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOSINGFORM_H
#define UI_CLOSINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClosingForm
{
public:
    QLabel *label;

    void setupUi(QWidget *ClosingForm)
    {
        if (ClosingForm->objectName().isEmpty())
            ClosingForm->setObjectName("ClosingForm");
        ClosingForm->resize(414, 115);
        label = new QLabel(ClosingForm);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 381, 81));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS UI Gothic")});
        font.setPointSize(30);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(ClosingForm);

        QMetaObject::connectSlotsByName(ClosingForm);
    } // setupUi

    void retranslateUi(QWidget *ClosingForm)
    {
        ClosingForm->setWindowTitle(QCoreApplication::translate("ClosingForm", "Closing...", nullptr));
        label->setText(QCoreApplication::translate("ClosingForm", "\347\265\202\344\272\206\344\270\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClosingForm: public Ui_ClosingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOSINGFORM_H
