/********************************************************************************
** Form generated from reading UI file 'SelectCameraDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCAMERADIALOG_H
#define UI_SELECTCAMERADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectCameraDialog
{
public:
    QListWidget *listWidgetCameraList;
    QPushButton *pushButtonSelect;
    QLabel *label;

    void setupUi(QDialog *SelectCameraDialog)
    {
        if (SelectCameraDialog->objectName().isEmpty())
            SelectCameraDialog->setObjectName("SelectCameraDialog");
        SelectCameraDialog->resize(254, 261);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SelectCameraDialog->sizePolicy().hasHeightForWidth());
        SelectCameraDialog->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        SelectCameraDialog->setWindowIcon(icon);
        listWidgetCameraList = new QListWidget(SelectCameraDialog);
        new QListWidgetItem(listWidgetCameraList);
        new QListWidgetItem(listWidgetCameraList);
        new QListWidgetItem(listWidgetCameraList);
        new QListWidgetItem(listWidgetCameraList);
        listWidgetCameraList->setObjectName("listWidgetCameraList");
        listWidgetCameraList->setGeometry(QRect(10, 10, 231, 131));
        QFont font;
        font.setPointSize(12);
        listWidgetCameraList->setFont(font);
        pushButtonSelect = new QPushButton(SelectCameraDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(70, 200, 111, 41));
        QFont font1;
        font1.setPointSize(14);
        pushButtonSelect->setFont(font1);
        label = new QLabel(SelectCameraDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 140, 231, 51));
        label->setWordWrap(true);

        retranslateUi(SelectCameraDialog);

        QMetaObject::connectSlotsByName(SelectCameraDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectCameraDialog)
    {
        SelectCameraDialog->setWindowTitle(QString());

        const bool __sortingEnabled = listWidgetCameraList->isSortingEnabled();
        listWidgetCameraList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetCameraList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("SelectCameraDialog", "L-835", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidgetCameraList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("SelectCameraDialog", "L-836", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidgetCameraList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("SelectCameraDialog", "L-835", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidgetCameraList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("SelectCameraDialog", "L-836", nullptr));
        listWidgetCameraList->setSortingEnabled(__sortingEnabled);

        pushButtonSelect->setText(QCoreApplication::translate("SelectCameraDialog", "\350\265\267\345\213\225", nullptr));
        label->setText(QCoreApplication::translate("SelectCameraDialog", "\344\275\277\347\224\250\343\201\231\343\202\213\343\202\253\343\203\241\343\203\251\343\202\222\351\201\270\346\212\236\343\201\227\343\201\246\343\201\217\343\201\240\343\201\225\343\201\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectCameraDialog: public Ui_SelectCameraDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCAMERADIALOG_H
