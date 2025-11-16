/********************************************************************************
** Form generated from reading UI file 'WorkerSelectForm.ui'
**
** Created: Mon Aug 20 16:22:46 2012
**      by: Qt User Interface Compiler version 4.7.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKERSELECTFORM_H
#define UI_WORKERSELECTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include "passwordpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_WorkerSelectClass
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QLabel *lbID;
    QLabel *leID;
    QLabel *lbSection;
    QLineEdit *leSection;
    QLabel *lbName;
    QLineEdit *leName;
    QLabel *lbRemark;
    QLineEdit *leRemark;
    QLabel *lbNichiji;
    QLabel *leUpdateTime;
    QFrame *line;
    QSpacerItem *spacerItem;
    PasswordPushButton *pbOK;
    QSpacerItem *spacerItem1;
    QTableWidget *twWorkerList;

    void setupUi(QDialog *WorkerSelectClass)
    {
        if (WorkerSelectClass->objectName().isEmpty())
            WorkerSelectClass->setObjectName(QString::fromUtf8("WorkerSelectClass"));
        WorkerSelectClass->resize(318, 372);
        gridLayout = new QGridLayout(WorkerSelectClass);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout1 = new QGridLayout();
#ifndef Q_OS_MAC
        gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout1->setContentsMargins(0, 0, 0, 0);
#endif
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        lbID = new QLabel(WorkerSelectClass);
        lbID->setObjectName(QString::fromUtf8("lbID"));

        gridLayout1->addWidget(lbID, 0, 0, 1, 1);

        leID = new QLabel(WorkerSelectClass);
        leID->setObjectName(QString::fromUtf8("leID"));
        QFont font;
        font.setFamily(QString::fromUtf8("Helvetica"));
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(true);
        font.setWeight(50);
        font.setStrikeOut(false);
        leID->setFont(font);

        gridLayout1->addWidget(leID, 0, 1, 1, 1);

        lbSection = new QLabel(WorkerSelectClass);
        lbSection->setObjectName(QString::fromUtf8("lbSection"));

        gridLayout1->addWidget(lbSection, 1, 0, 1, 1);

        leSection = new QLineEdit(WorkerSelectClass);
        leSection->setObjectName(QString::fromUtf8("leSection"));
        leSection->setMaxLength(64);
        leSection->setReadOnly(true);

        gridLayout1->addWidget(leSection, 1, 1, 1, 1);

        lbName = new QLabel(WorkerSelectClass);
        lbName->setObjectName(QString::fromUtf8("lbName"));

        gridLayout1->addWidget(lbName, 2, 0, 1, 1);

        leName = new QLineEdit(WorkerSelectClass);
        leName->setObjectName(QString::fromUtf8("leName"));
        leName->setMaxLength(64);
        leName->setReadOnly(true);

        gridLayout1->addWidget(leName, 2, 1, 1, 1);

        lbRemark = new QLabel(WorkerSelectClass);
        lbRemark->setObjectName(QString::fromUtf8("lbRemark"));

        gridLayout1->addWidget(lbRemark, 3, 0, 1, 1);

        leRemark = new QLineEdit(WorkerSelectClass);
        leRemark->setObjectName(QString::fromUtf8("leRemark"));
        leRemark->setMaxLength(64);
        leRemark->setReadOnly(true);

        gridLayout1->addWidget(leRemark, 3, 1, 1, 1);

        lbNichiji = new QLabel(WorkerSelectClass);
        lbNichiji->setObjectName(QString::fromUtf8("lbNichiji"));

        gridLayout1->addWidget(lbNichiji, 4, 0, 1, 1);

        leUpdateTime = new QLabel(WorkerSelectClass);
        leUpdateTime->setObjectName(QString::fromUtf8("leUpdateTime"));
        leUpdateTime->setFont(font);

        gridLayout1->addWidget(leUpdateTime, 4, 1, 1, 1);


        gridLayout->addLayout(gridLayout1, 0, 0, 1, 3);

        line = new QFrame(WorkerSelectClass);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 3);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 3, 0, 1, 1);

        pbOK = new PasswordPushButton(WorkerSelectClass);
        pbOK->setObjectName(QString::fromUtf8("pbOK"));
        pbOK->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbOK->setIcon(icon);
        pbOK->setDefault(true);

        gridLayout->addWidget(pbOK, 3, 1, 1, 1);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem1, 3, 2, 1, 1);

        twWorkerList = new QTableWidget(WorkerSelectClass);
        twWorkerList->setObjectName(QString::fromUtf8("twWorkerList"));

        gridLayout->addWidget(twWorkerList, 1, 0, 1, 3);


        retranslateUi(WorkerSelectClass);

        QMetaObject::connectSlotsByName(WorkerSelectClass);
    } // setupUi

    void retranslateUi(QDialog *WorkerSelectClass)
    {
        WorkerSelectClass->setWindowTitle(QApplication::translate("WorkerSelectClass", "Dialog", 0, QApplication::UnicodeUTF8));
        lbID->setText(QApplication::translate("WorkerSelectClass", "Worker ID", 0, QApplication::UnicodeUTF8));
        leID->setText(QString());
        lbSection->setText(QApplication::translate("WorkerSelectClass", "Worker Section", 0, QApplication::UnicodeUTF8));
        lbName->setText(QApplication::translate("WorkerSelectClass", "Worker Name", 0, QApplication::UnicodeUTF8));
        lbRemark->setText(QApplication::translate("WorkerSelectClass", "Remark", 0, QApplication::UnicodeUTF8));
        lbNichiji->setText(QApplication::translate("WorkerSelectClass", "Update Time", 0, QApplication::UnicodeUTF8));
        leUpdateTime->setText(QString());
        pbOK->setText(QApplication::translate("WorkerSelectClass", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WorkerSelectClass: public Ui_WorkerSelectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKERSELECTFORM_H
