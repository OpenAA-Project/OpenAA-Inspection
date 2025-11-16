/********************************************************************************
** Form generated from reading UI file 'SelectThresholdParentLevelDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTTHRESHOLDPARENTLEVELDIALOG_H
#define UI_SELECTTHRESHOLDPARENTLEVELDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectThresholdParentLevelDialog
{
public:
    QTreeWidget *treeWidgetLevel;
    QFrame *frame;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonTopRoot;

    void setupUi(QDialog *SelectThresholdParentLevelDialog)
    {
        if (SelectThresholdParentLevelDialog->objectName().isEmpty())
            SelectThresholdParentLevelDialog->setObjectName("SelectThresholdParentLevelDialog");
        SelectThresholdParentLevelDialog->resize(411, 313);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SelectThresholdParentLevelDialog->sizePolicy().hasHeightForWidth());
        SelectThresholdParentLevelDialog->setSizePolicy(sizePolicy);
        treeWidgetLevel = new QTreeWidget(SelectThresholdParentLevelDialog);
        treeWidgetLevel->setObjectName("treeWidgetLevel");
        treeWidgetLevel->setGeometry(QRect(0, 0, 411, 261));
        frame = new QFrame(SelectThresholdParentLevelDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 260, 411, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonCancel = new QPushButton(frame);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(280, 10, 112, 34));
        pushButtonSelect = new QPushButton(frame);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(10, 10, 112, 34));
        pushButtonTopRoot = new QPushButton(SelectThresholdParentLevelDialog);
        pushButtonTopRoot->setObjectName("pushButtonTopRoot");
        pushButtonTopRoot->setGeometry(QRect(0, 0, 101, 31));
        pushButtonTopRoot->setCheckable(true);

        retranslateUi(SelectThresholdParentLevelDialog);

        pushButtonSelect->setDefault(true);


        QMetaObject::connectSlotsByName(SelectThresholdParentLevelDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectThresholdParentLevelDialog)
    {
        SelectThresholdParentLevelDialog->setWindowTitle(QCoreApplication::translate("SelectThresholdParentLevelDialog", "Dialog", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidgetLevel->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("SelectThresholdParentLevelDialog", "Level Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("SelectThresholdParentLevelDialog", "1", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectThresholdParentLevelDialog", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectThresholdParentLevelDialog", "\351\201\270\346\212\236", nullptr));
        pushButtonTopRoot->setText(QCoreApplication::translate("SelectThresholdParentLevelDialog", "Top", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectThresholdParentLevelDialog: public Ui_SelectThresholdParentLevelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTTHRESHOLDPARENTLEVELDIALOG_H
