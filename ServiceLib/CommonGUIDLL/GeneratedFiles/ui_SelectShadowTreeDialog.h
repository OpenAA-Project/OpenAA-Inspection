/********************************************************************************
** Form generated from reading UI file 'SelectShadowTreeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTSHADOWTREEDIALOG_H
#define UI_SELECTSHADOWTREEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectShadowTreeDialog
{
public:
    QTreeWidget *treeWidgetShadowTree;
    QFrame *frameBottom;
    QPushButton *pushButtonCancel;
    QLineEdit *lineEditGlobal;
    QPushButton *pushButtonSelect;
    QLabel *label_2;
    QLineEdit *lineEditControlDLL;
    QLabel *label;

    void setupUi(QDialog *SelectShadowTreeDialog)
    {
        if (SelectShadowTreeDialog->objectName().isEmpty())
            SelectShadowTreeDialog->setObjectName("SelectShadowTreeDialog");
        SelectShadowTreeDialog->resize(379, 250);
        treeWidgetShadowTree = new QTreeWidget(SelectShadowTreeDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidgetShadowTree->setHeaderItem(__qtreewidgetitem);
        treeWidgetShadowTree->setObjectName("treeWidgetShadowTree");
        treeWidgetShadowTree->setGeometry(QRect(10, 10, 361, 141));
        frameBottom = new QFrame(SelectShadowTreeDialog);
        frameBottom->setObjectName("frameBottom");
        frameBottom->setGeometry(QRect(0, 150, 381, 101));
        frameBottom->setFrameShape(QFrame::StyledPanel);
        frameBottom->setFrameShadow(QFrame::Raised);
        pushButtonCancel = new QPushButton(frameBottom);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(200, 60, 80, 31));
        lineEditGlobal = new QLineEdit(frameBottom);
        lineEditGlobal->setObjectName("lineEditGlobal");
        lineEditGlobal->setGeometry(QRect(70, 30, 301, 20));
        pushButtonSelect = new QPushButton(frameBottom);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(90, 60, 80, 31));
        label_2 = new QLabel(frameBottom);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 30, 61, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        lineEditControlDLL = new QLineEdit(frameBottom);
        lineEditControlDLL->setObjectName("lineEditControlDLL");
        lineEditControlDLL->setGeometry(QRect(70, 10, 301, 20));
        label = new QLabel(frameBottom);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 61, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);

        retranslateUi(SelectShadowTreeDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectShadowTreeDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectShadowTreeDialog)
    {
        SelectShadowTreeDialog->setWindowTitle(QCoreApplication::translate("SelectShadowTreeDialog", "Select ShadowTree", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectShadowTreeDialog", "Cancel", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectShadowTreeDialog", "Select", nullptr));
        label_2->setText(QCoreApplication::translate("SelectShadowTreeDialog", "Global", nullptr));
        label->setText(QCoreApplication::translate("SelectShadowTreeDialog", "Control", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectShadowTreeDialog: public Ui_SelectShadowTreeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTSHADOWTREEDIALOG_H
