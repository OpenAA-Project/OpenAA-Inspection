/********************************************************************************
** Form generated from reading UI file 'MasterCategoryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASTERCATEGORYFORM_H
#define UI_MASTERCATEGORYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MasterCategoryForm
{
public:
    QLabel *SelectedRemark;
    QTreeWidget *treeWidget;
    QLabel *label_3;
    QPushButton *pushButtonUpdateButton;
    QLabel *SelectedFolderName;
    QPushButton *pushButton;

    void setupUi(QWidget *MasterCategoryForm)
    {
        if (MasterCategoryForm->objectName().isEmpty())
            MasterCategoryForm->setObjectName("MasterCategoryForm");
        MasterCategoryForm->resize(373, 187);
        SelectedRemark = new QLabel(MasterCategoryForm);
        SelectedRemark->setObjectName("SelectedRemark");
        SelectedRemark->setGeometry(QRect(150, 160, 131, 20));
        SelectedRemark->setFrameShape(QFrame::Panel);
        SelectedRemark->setFrameShadow(QFrame::Sunken);
        treeWidget = new QTreeWidget(MasterCategoryForm);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setGeometry(QRect(10, 30, 351, 121));
        label_3 = new QLabel(MasterCategoryForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 271, 20));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        pushButtonUpdateButton = new QPushButton(MasterCategoryForm);
        pushButtonUpdateButton->setObjectName("pushButtonUpdateButton");
        pushButtonUpdateButton->setGeometry(QRect(286, 8, 75, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdateButton->setIcon(icon);
        SelectedFolderName = new QLabel(MasterCategoryForm);
        SelectedFolderName->setObjectName("SelectedFolderName");
        SelectedFolderName->setGeometry(QRect(10, 160, 131, 20));
        SelectedFolderName->setFrameShape(QFrame::Panel);
        SelectedFolderName->setFrameShadow(QFrame::Sunken);
        pushButton = new QPushButton(MasterCategoryForm);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(290, 160, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Change.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon1);

        retranslateUi(MasterCategoryForm);

        QMetaObject::connectSlotsByName(MasterCategoryForm);
    } // setupUi

    void retranslateUi(QWidget *MasterCategoryForm)
    {
        MasterCategoryForm->setWindowTitle(QCoreApplication::translate("MasterCategoryForm", "Form", nullptr));
        SelectedRemark->setText(QCoreApplication::translate("MasterCategoryForm", "Remark", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MasterCategoryForm", "1", nullptr));
        label_3->setText(QCoreApplication::translate("MasterCategoryForm", "Saved category", nullptr));
        pushButtonUpdateButton->setText(QCoreApplication::translate("MasterCategoryForm", "Update", nullptr));
        SelectedFolderName->setText(QCoreApplication::translate("MasterCategoryForm", "FolderName", nullptr));
        pushButton->setText(QCoreApplication::translate("MasterCategoryForm", "Change", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MasterCategoryForm: public Ui_MasterCategoryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASTERCATEGORYFORM_H
