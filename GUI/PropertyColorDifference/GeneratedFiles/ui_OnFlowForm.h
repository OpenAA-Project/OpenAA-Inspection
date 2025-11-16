/********************************************************************************
** Form generated from reading UI file 'OnFlowForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONFLOWFORM_H
#define UI_ONFLOWFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OnFlowForm
{
public:
    QLabel *label;

    void setupUi(QWidget *OnFlowForm)
    {
        if (OnFlowForm->objectName().isEmpty())
            OnFlowForm->setObjectName("OnFlowForm");
        OnFlowForm->resize(400, 72);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(255, 170, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        OnFlowForm->setPalette(palette);
        OnFlowForm->setAutoFillBackground(true);
        label = new QLabel(OnFlowForm);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 291, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(OnFlowForm);

        QMetaObject::connectSlotsByName(OnFlowForm);
    } // setupUi

    void retranslateUi(QWidget *OnFlowForm)
    {
        OnFlowForm->setWindowTitle(QCoreApplication::translate("OnFlowForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("OnFlowForm", "\346\265\201\345\213\225\343\203\207\343\203\274\343\202\277\346\216\241\351\233\206\344\270\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OnFlowForm: public Ui_OnFlowForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONFLOWFORM_H
