/********************************************************************************
** Form generated from reading UI file 'EditDatabaseListForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDATABASELISTFORM_H
#define UI_EDITDATABASELISTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditDatabaseListFormClass
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButtonNew;
    QPushButton *pushButtonMod;
    QPushButton *pushButtonDel;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditName;
    QLineEdit *lineEditIP;
    QLineEdit *lineEditFileName;
    QPushButton *pushButtonClose;
    QLabel *label_4;
    QSpinBox *spinBoxPortNo;

    void setupUi(QDialog *EditDatabaseListFormClass)
    {
        if (EditDatabaseListFormClass->objectName().isEmpty())
            EditDatabaseListFormClass->setObjectName("EditDatabaseListFormClass");
        EditDatabaseListFormClass->resize(343, 419);
        tableWidget = new QTableWidget(EditDatabaseListFormClass);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 321, 192));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonNew = new QPushButton(EditDatabaseListFormClass);
        pushButtonNew->setObjectName("pushButtonNew");
        pushButtonNew->setGeometry(QRect(10, 260, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonNew->setIcon(icon);
        pushButtonMod = new QPushButton(EditDatabaseListFormClass);
        pushButtonMod->setObjectName("pushButtonMod");
        pushButtonMod->setGeometry(QRect(10, 300, 121, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Row.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonMod->setIcon(icon1);
        pushButtonDel = new QPushButton(EditDatabaseListFormClass);
        pushButtonDel->setObjectName("pushButtonDel");
        pushButtonDel->setGeometry(QRect(10, 340, 121, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDel->setIcon(icon2);
        label = new QLabel(EditDatabaseListFormClass);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 210, 171, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(EditDatabaseListFormClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 260, 171, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(EditDatabaseListFormClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(160, 310, 171, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditName = new QLineEdit(EditDatabaseListFormClass);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(160, 230, 171, 20));
        lineEditIP = new QLineEdit(EditDatabaseListFormClass);
        lineEditIP->setObjectName("lineEditIP");
        lineEditIP->setGeometry(QRect(160, 280, 171, 20));
        lineEditFileName = new QLineEdit(EditDatabaseListFormClass);
        lineEditFileName->setObjectName("lineEditFileName");
        lineEditFileName->setGeometry(QRect(160, 330, 171, 20));
        pushButtonClose = new QPushButton(EditDatabaseListFormClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(10, 380, 121, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon3);
        label_4 = new QLabel(EditDatabaseListFormClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(160, 360, 171, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPortNo = new QSpinBox(EditDatabaseListFormClass);
        spinBoxPortNo->setObjectName("spinBoxPortNo");
        spinBoxPortNo->setGeometry(QRect(200, 380, 91, 22));
        spinBoxPortNo->setMinimum(1000);
        spinBoxPortNo->setMaximum(65535);
        spinBoxPortNo->setValue(3050);

        retranslateUi(EditDatabaseListFormClass);

        QMetaObject::connectSlotsByName(EditDatabaseListFormClass);
    } // setupUi

    void retranslateUi(QDialog *EditDatabaseListFormClass)
    {
        EditDatabaseListFormClass->setWindowTitle(QCoreApplication::translate("EditDatabaseListFormClass", "EditDatabaseListForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditDatabaseListFormClass", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditDatabaseListFormClass", "IP/Server", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EditDatabaseListFormClass", "Port", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EditDatabaseListFormClass", "File", nullptr));
        pushButtonNew->setText(QCoreApplication::translate("EditDatabaseListFormClass", "\347\251\272\347\231\275\350\241\214\350\277\275\345\212\240", nullptr));
        pushButtonMod->setText(QCoreApplication::translate("EditDatabaseListFormClass", "\351\201\270\346\212\236\350\241\214\343\201\256\344\277\256\346\255\243\347\231\273\351\214\262", nullptr));
        pushButtonDel->setText(QCoreApplication::translate("EditDatabaseListFormClass", "\351\201\270\346\212\236\350\241\214\343\201\256\345\211\212\351\231\244", nullptr));
        label->setText(QCoreApplication::translate("EditDatabaseListFormClass", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("EditDatabaseListFormClass", "IP/Server", nullptr));
        label_3->setText(QCoreApplication::translate("EditDatabaseListFormClass", "File", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditDatabaseListFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        label_4->setText(QCoreApplication::translate("EditDatabaseListFormClass", "Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditDatabaseListFormClass: public Ui_EditDatabaseListFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDATABASELISTFORM_H
