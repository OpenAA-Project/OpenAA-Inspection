/********************************************************************************
** Form generated from reading UI file 'ShowSignalForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSIGNALFORM_H
#define UI_SHOWSIGNALFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollBar>

QT_BEGIN_NAMESPACE

class Ui_ShowSignalForm
{
public:
    QScrollBar *horizontalScrollBar;
    QComboBox *comboBox;
    QLabel *label;
    QFrame *frame;
    QScrollBar *verticalScrollBar;
    QLineEdit *lineEditCurrentMilisec;

    void setupUi(QDialog *ShowSignalForm)
    {
        if (ShowSignalForm->objectName().isEmpty())
            ShowSignalForm->setObjectName("ShowSignalForm");
        ShowSignalForm->resize(737, 634);
        horizontalScrollBar = new QScrollBar(ShowSignalForm);
        horizontalScrollBar->setObjectName("horizontalScrollBar");
        horizontalScrollBar->setGeometry(QRect(170, 0, 571, 20));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        comboBox = new QComboBox(ShowSignalForm);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(0, 0, 74, 22));
        label = new QLabel(ShowSignalForm);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 0, 21, 16));
        frame = new QFrame(ShowSignalForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 20, 721, 611));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        verticalScrollBar = new QScrollBar(ShowSignalForm);
        verticalScrollBar->setObjectName("verticalScrollBar");
        verticalScrollBar->setGeometry(QRect(720, 20, 16, 611));
        verticalScrollBar->setOrientation(Qt::Vertical);
        lineEditCurrentMilisec = new QLineEdit(ShowSignalForm);
        lineEditCurrentMilisec->setObjectName("lineEditCurrentMilisec");
        lineEditCurrentMilisec->setGeometry(QRect(100, 0, 71, 20));
        QPalette palette;
        QBrush brush(QColor(85, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditCurrentMilisec->setPalette(palette);
        lineEditCurrentMilisec->setReadOnly(true);

        retranslateUi(ShowSignalForm);

        comboBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ShowSignalForm);
    } // setupUi

    void retranslateUi(QDialog *ShowSignalForm)
    {
        ShowSignalForm->setWindowTitle(QCoreApplication::translate("ShowSignalForm", "Dialog", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ShowSignalForm", "1", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ShowSignalForm", "10", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("ShowSignalForm", "100", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("ShowSignalForm", "1000", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("ShowSignalForm", "60000", nullptr));

        label->setText(QCoreApplication::translate("ShowSignalForm", "ms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowSignalForm: public Ui_ShowSignalForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSIGNALFORM_H
