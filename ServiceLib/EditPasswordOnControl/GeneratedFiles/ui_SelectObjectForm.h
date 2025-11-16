/********************************************************************************
** Form generated from reading UI file 'SelectObjectForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTOBJECTFORM_H
#define UI_SELECTOBJECTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectObjectForm
{
public:
    QTreeWidget *treeWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditType;
    QLineEdit *lineEditObject;
    QLineEdit *lineEditText;
    QLabel *label_4;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;
    QComboBox *comboBoxControlMode;

    void setupUi(QDialog *SelectObjectForm)
    {
        if (SelectObjectForm->objectName().isEmpty())
            SelectObjectForm->setObjectName("SelectObjectForm");
        SelectObjectForm->resize(544, 463);
        treeWidget = new QTreeWidget(SelectObjectForm);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setGeometry(QRect(10, 10, 521, 261));
        treeWidget->setTabKeyNavigation(false);
        treeWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        treeWidget->setTextElideMode(Qt::ElideNone);
        treeWidget->header()->setVisible(false);
        label = new QLabel(SelectObjectForm);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 310, 131, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(SelectObjectForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(170, 310, 141, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(SelectObjectForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(320, 310, 211, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        lineEditType = new QLineEdit(SelectObjectForm);
        lineEditType->setObjectName("lineEditType");
        lineEditType->setGeometry(QRect(30, 330, 131, 20));
        lineEditObject = new QLineEdit(SelectObjectForm);
        lineEditObject->setObjectName("lineEditObject");
        lineEditObject->setGeometry(QRect(170, 330, 141, 20));
        lineEditText = new QLineEdit(SelectObjectForm);
        lineEditText->setObjectName("lineEditText");
        lineEditText->setGeometry(QRect(320, 330, 211, 20));
        label_4 = new QLabel(SelectObjectForm);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(130, 280, 291, 16));
        pushButtonSelect = new QPushButton(SelectObjectForm);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(60, 410, 121, 31));
        pushButtonCancel = new QPushButton(SelectObjectForm);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(370, 410, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        comboBoxControlMode = new QComboBox(SelectObjectForm);
        comboBoxControlMode->addItem(QString());
        comboBoxControlMode->addItem(QString());
        comboBoxControlMode->setObjectName("comboBoxControlMode");
        comboBoxControlMode->setGeometry(QRect(30, 360, 221, 22));

        retranslateUi(SelectObjectForm);

        QMetaObject::connectSlotsByName(SelectObjectForm);
    } // setupUi

    void retranslateUi(QDialog *SelectObjectForm)
    {
        SelectObjectForm->setWindowTitle(QCoreApplication::translate("SelectObjectForm", "Select object", nullptr));
        label->setText(QCoreApplication::translate("SelectObjectForm", "Type", nullptr));
        label_2->setText(QCoreApplication::translate("SelectObjectForm", "Obect Name", nullptr));
        label_3->setText(QCoreApplication::translate("SelectObjectForm", "Text", nullptr));
        label_4->setText(QCoreApplication::translate("SelectObjectForm", "Select with double click", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectObjectForm", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectObjectForm", "Cancel", nullptr));
        comboBoxControlMode->setItemText(0, QCoreApplication::translate("SelectObjectForm", "Normal check password", nullptr));
        comboBoxControlMode->setItemText(1, QCoreApplication::translate("SelectObjectForm", "Expire password", nullptr));

    } // retranslateUi

};

namespace Ui {
    class SelectObjectForm: public Ui_SelectObjectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTOBJECTFORM_H
