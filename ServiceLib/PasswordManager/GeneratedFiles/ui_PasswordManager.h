/********************************************************************************
** Form generated from reading UI file 'PasswordManager.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDMANAGER_H
#define UI_PASSWORDMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PasswordManager
{
public:
    QLabel *laDragDrop;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *laClassName;
    QLineEdit *liedClassName;
    QLabel *lbPassword;
    QLineEdit *liedPassword;
    QPushButton *btnDelItem;
    QPushButton *btnFileSave;
    QTableWidget *tableItems;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *laClassList;
    QListWidget *listClassNames;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddClass;
    QPushButton *btnUpdateClassInfo;
    QPushButton *btnDelClass;
    QFrame *frmDrag;

    void setupUi(QWidget *PasswordManager)
    {
        if (PasswordManager->objectName().isEmpty())
            PasswordManager->setObjectName("PasswordManager");
        PasswordManager->resize(652, 448);
        laDragDrop = new QLabel(PasswordManager);
        laDragDrop->setObjectName("laDragDrop");
        laDragDrop->setGeometry(QRect(525, 200, 121, 16));
        layoutWidget = new QWidget(PasswordManager);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(275, 10, 341, 113));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        laClassName = new QLabel(layoutWidget);
        laClassName->setObjectName("laClassName");

        verticalLayout->addWidget(laClassName);

        liedClassName = new QLineEdit(layoutWidget);
        liedClassName->setObjectName("liedClassName");
        liedClassName->setAcceptDrops(false);

        verticalLayout->addWidget(liedClassName);

        lbPassword = new QLabel(layoutWidget);
        lbPassword->setObjectName("lbPassword");

        verticalLayout->addWidget(lbPassword);

        liedPassword = new QLineEdit(layoutWidget);
        liedPassword->setObjectName("liedPassword");
        liedPassword->setAcceptDrops(false);
        liedPassword->setEchoMode(QLineEdit::Normal);

        verticalLayout->addWidget(liedPassword);

        btnDelItem = new QPushButton(PasswordManager);
        btnDelItem->setObjectName("btnDelItem");
        btnDelItem->setGeometry(QRect(525, 280, 91, 31));
        btnFileSave = new QPushButton(PasswordManager);
        btnFileSave->setObjectName("btnFileSave");
        btnFileSave->setGeometry(QRect(525, 340, 91, 31));
        tableItems = new QTableWidget(PasswordManager);
        tableItems->setObjectName("tableItems");
        tableItems->setGeometry(QRect(15, 180, 491, 251));
        tableItems->setSelectionBehavior(QAbstractItemView::SelectRows);
        layoutWidget_2 = new QWidget(PasswordManager);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(5, 10, 261, 141));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        laClassList = new QLabel(layoutWidget_2);
        laClassList->setObjectName("laClassList");

        verticalLayout_2->addWidget(laClassList);

        listClassNames = new QListWidget(layoutWidget_2);
        listClassNames->setObjectName("listClassNames");

        verticalLayout_2->addWidget(listClassNames);

        layoutWidget_3 = new QWidget(PasswordManager);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(280, 130, 341, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget_3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnAddClass = new QPushButton(layoutWidget_3);
        btnAddClass->setObjectName("btnAddClass");

        horizontalLayout->addWidget(btnAddClass);

        btnUpdateClassInfo = new QPushButton(layoutWidget_3);
        btnUpdateClassInfo->setObjectName("btnUpdateClassInfo");

        horizontalLayout->addWidget(btnUpdateClassInfo);

        btnDelClass = new QPushButton(layoutWidget_3);
        btnDelClass->setObjectName("btnDelClass");

        horizontalLayout->addWidget(btnDelClass);

        frmDrag = new QFrame(PasswordManager);
        frmDrag->setObjectName("frmDrag");
        frmDrag->setGeometry(QRect(550, 220, 32, 32));
        frmDrag->setMinimumSize(QSize(32, 32));
        frmDrag->setMaximumSize(QSize(32, 32));
        frmDrag->setLayoutDirection(Qt::LeftToRight);
        frmDrag->setFrameShape(QFrame::StyledPanel);
        frmDrag->setFrameShadow(QFrame::Raised);

        retranslateUi(PasswordManager);

        QMetaObject::connectSlotsByName(PasswordManager);
    } // setupUi

    void retranslateUi(QWidget *PasswordManager)
    {
        PasswordManager->setWindowTitle(QCoreApplication::translate("PasswordManager", "Form", nullptr));
        laDragDrop->setText(QCoreApplication::translate("PasswordManager", "\343\203\211\343\203\251\343\203\203\343\202\260\357\274\206\343\203\211\343\203\255\343\203\203\343\203\227", nullptr));
        laClassName->setText(QCoreApplication::translate("PasswordManager", "\343\202\257\343\203\251\343\202\271\345\220\215", nullptr));
        lbPassword->setText(QCoreApplication::translate("PasswordManager", "\343\203\221\343\202\271\343\203\257\343\203\274\343\203\211", nullptr));
        btnDelItem->setText(QCoreApplication::translate("PasswordManager", "\345\211\212\351\231\244", nullptr));
        btnFileSave->setText(QCoreApplication::translate("PasswordManager", "\344\277\235\345\255\230", nullptr));
        laClassList->setText(QCoreApplication::translate("PasswordManager", "\343\202\257\343\203\251\343\202\271\344\270\200\350\246\247", nullptr));
        btnAddClass->setText(QCoreApplication::translate("PasswordManager", "\343\202\257\343\203\251\343\202\271\350\277\275\345\212\240", nullptr));
        btnUpdateClassInfo->setText(QCoreApplication::translate("PasswordManager", "\351\201\251\347\224\250", nullptr));
        btnDelClass->setText(QCoreApplication::translate("PasswordManager", "\343\202\257\343\203\251\343\202\271\345\211\212\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasswordManager: public Ui_PasswordManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDMANAGER_H
