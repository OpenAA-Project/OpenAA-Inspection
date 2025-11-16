/********************************************************************************
** Form generated from reading UI file 'SelectLevelDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLEVELDIALOG_H
#define UI_SELECTLEVELDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLevelDialog
{
public:
    QTreeWidget *treeWidgetLevel;

    void setupUi(QDialog *SelectLevelDialog)
    {
        if (SelectLevelDialog->objectName().isEmpty())
            SelectLevelDialog->setObjectName("SelectLevelDialog");
        SelectLevelDialog->resize(428, 226);
        treeWidgetLevel = new QTreeWidget(SelectLevelDialog);
        treeWidgetLevel->setObjectName("treeWidgetLevel");
        treeWidgetLevel->setGeometry(QRect(0, 0, 401, 192));

        retranslateUi(SelectLevelDialog);

        QMetaObject::connectSlotsByName(SelectLevelDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLevelDialog)
    {
        SelectLevelDialog->setWindowTitle(QCoreApplication::translate("SelectLevelDialog", "Select Level", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidgetLevel->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("SelectLevelDialog", "Level Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("SelectLevelDialog", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLevelDialog: public Ui_SelectLevelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLEVELDIALOG_H
