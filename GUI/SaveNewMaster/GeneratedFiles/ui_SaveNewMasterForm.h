/********************************************************************************
** Form generated from reading UI file 'SaveNewMasterForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVENEWMASTERFORM_H
#define UI_SAVENEWMASTERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_SaveNewMasterFormClass
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *lbMasterID;
    QLabel *label_2;
    QLineEdit *leMasterName;
    QLabel *label_3;
    QLineEdit *leRemarks;
    QSpacerItem *spacerItem;
    QPushButton *pbSave;

    void setupUi(GUIFormBase *SaveNewMasterFormClass)
    {
        if (SaveNewMasterFormClass->objectName().isEmpty())
            SaveNewMasterFormClass->setObjectName("SaveNewMasterFormClass");
        SaveNewMasterFormClass->resize(256, 121);
        gridLayout = new QGridLayout(SaveNewMasterFormClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(SaveNewMasterFormClass);
        label->setObjectName("label");
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lbMasterID = new QLabel(SaveNewMasterFormClass);
        lbMasterID->setObjectName("lbMasterID");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbMasterID->sizePolicy().hasHeightForWidth());
        lbMasterID->setSizePolicy(sizePolicy);
        lbMasterID->setFrameShape(QFrame::Panel);
        lbMasterID->setFrameShadow(QFrame::Sunken);
        lbMasterID->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lbMasterID, 0, 1, 1, 2);

        label_2 = new QLabel(SaveNewMasterFormClass);
        label_2->setObjectName("label_2");
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        leMasterName = new QLineEdit(SaveNewMasterFormClass);
        leMasterName->setObjectName("leMasterName");

        gridLayout->addWidget(leMasterName, 1, 1, 1, 2);

        label_3 = new QLabel(SaveNewMasterFormClass);
        label_3->setObjectName("label_3");
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        leRemarks = new QLineEdit(SaveNewMasterFormClass);
        leRemarks->setObjectName("leRemarks");

        gridLayout->addWidget(leRemarks, 2, 1, 1, 2);

        spacerItem = new QSpacerItem(151, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(spacerItem, 3, 0, 1, 2);

        pbSave = new QPushButton(SaveNewMasterFormClass);
        pbSave->setObjectName("pbSave");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pbSave->sizePolicy().hasHeightForWidth());
        pbSave->setSizePolicy(sizePolicy1);
        pbSave->setMinimumSize(QSize(81, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbSave->setIcon(icon);

        gridLayout->addWidget(pbSave, 3, 2, 1, 1);


        retranslateUi(SaveNewMasterFormClass);

        QMetaObject::connectSlotsByName(SaveNewMasterFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *SaveNewMasterFormClass)
    {
        SaveNewMasterFormClass->setWindowTitle(QCoreApplication::translate("SaveNewMasterFormClass", "SaveNewMasterForm", nullptr));
        label->setText(QCoreApplication::translate("SaveNewMasterFormClass", "\343\203\236\343\202\271\343\202\277\343\203\274ID", nullptr));
        label_2->setText(QCoreApplication::translate("SaveNewMasterFormClass", "\343\203\236\343\202\271\343\202\277\343\203\274\345\220\215\347\247\260", nullptr));
        label_3->setText(QCoreApplication::translate("SaveNewMasterFormClass", "\345\202\231\350\200\203", nullptr));
        pbSave->setText(QCoreApplication::translate("SaveNewMasterFormClass", "\346\226\260\350\246\217\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SaveNewMasterFormClass: public Ui_SaveNewMasterFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVENEWMASTERFORM_H
