/********************************************************************************
** Form generated from reading UI file 'SelectLearningImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLEARNINGIMAGEFORM_H
#define UI_SELECTLEARNINGIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLearningImageFormClass
{
public:
    QListWidget *listWidget;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonEdit;

    void setupUi(QWidget *SelectLearningImageFormClass)
    {
        if (SelectLearningImageFormClass->objectName().isEmpty())
            SelectLearningImageFormClass->setObjectName("SelectLearningImageFormClass");
        SelectLearningImageFormClass->resize(268, 214);
        listWidget = new QListWidget(SelectLearningImageFormClass);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 10, 151, 192));
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonClose = new QPushButton(SelectLearningImageFormClass);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(180, 170, 81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClose->setIcon(icon);
        pushButtonUpdate = new QPushButton(SelectLearningImageFormClass);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(180, 90, 81, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon1);
        pushButtonDelete = new QPushButton(SelectLearningImageFormClass);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(180, 130, 81, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon2);
        pushButtonEdit = new QPushButton(SelectLearningImageFormClass);
        pushButtonEdit->setObjectName("pushButtonEdit");
        pushButtonEdit->setGeometry(QRect(180, 20, 81, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Edit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonEdit->setIcon(icon3);

        retranslateUi(SelectLearningImageFormClass);

        QMetaObject::connectSlotsByName(SelectLearningImageFormClass);
    } // setupUi

    void retranslateUi(QWidget *SelectLearningImageFormClass)
    {
        SelectLearningImageFormClass->setWindowTitle(QCoreApplication::translate("SelectLearningImageFormClass", "SelectLearningImageForm", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SelectLearningImageFormClass", "\351\226\211\343\201\230\343\202\213", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("SelectLearningImageFormClass", "\346\233\264\346\226\260", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("SelectLearningImageFormClass", "\351\201\270\346\212\236\345\211\212\351\231\244", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("SelectLearningImageFormClass", "\347\267\250\351\233\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLearningImageFormClass: public Ui_SelectLearningImageFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLEARNINGIMAGEFORM_H
