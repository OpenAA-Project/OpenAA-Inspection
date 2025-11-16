/********************************************************************************
** Form generated from reading UI file 'GUITurnUpDownForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUITURNUPDOWNFORM_H
#define UI_GUITURNUPDOWNFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GUITurnUpDownForm
{
public:
    QLabel *label_3;
    QListWidget *listWidgetList;
    QPushButton *pushButtonUp;
    QPushButton *pushButtonDown;
    QComboBox *comboBTabSheet;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *GUITurnUpDownForm)
    {
        if (GUITurnUpDownForm->objectName().isEmpty())
            GUITurnUpDownForm->setObjectName("GUITurnUpDownForm");
        GUITurnUpDownForm->resize(285, 230);
        label_3 = new QLabel(GUITurnUpDownForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 10, 81, 16));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        listWidgetList = new QListWidget(GUITurnUpDownForm);
        listWidgetList->setObjectName("listWidgetList");
        listWidgetList->setGeometry(QRect(10, 60, 181, 121));
        listWidgetList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonUp = new QPushButton(GUITurnUpDownForm);
        pushButtonUp->setObjectName("pushButtonUp");
        pushButtonUp->setGeometry(QRect(200, 90, 81, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Up.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUp->setIcon(icon);
        pushButtonDown = new QPushButton(GUITurnUpDownForm);
        pushButtonDown->setObjectName("pushButtonDown");
        pushButtonDown->setGeometry(QRect(200, 120, 81, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Down.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDown->setIcon(icon1);
        comboBTabSheet = new QComboBox(GUITurnUpDownForm);
        comboBTabSheet->setObjectName("comboBTabSheet");
        comboBTabSheet->setGeometry(QRect(10, 30, 181, 22));
        pushButtonOK = new QPushButton(GUITurnUpDownForm);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(70, 190, 91, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonOK->setIcon(icon2);

        retranslateUi(GUITurnUpDownForm);

        QMetaObject::connectSlotsByName(GUITurnUpDownForm);
    } // setupUi

    void retranslateUi(QDialog *GUITurnUpDownForm)
    {
        GUITurnUpDownForm->setWindowTitle(QCoreApplication::translate("GUITurnUpDownForm", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("GUITurnUpDownForm", "TabSheet", nullptr));
        pushButtonUp->setText(QCoreApplication::translate("GUITurnUpDownForm", "Up", nullptr));
        pushButtonDown->setText(QCoreApplication::translate("GUITurnUpDownForm", "Down", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("GUITurnUpDownForm", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUITurnUpDownForm: public Ui_GUITurnUpDownForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUITURNUPDOWNFORM_H
