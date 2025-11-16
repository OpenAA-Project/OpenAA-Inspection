/********************************************************************************
** Form generated from reading UI file 'SettingForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFORM_H
#define UI_SETTINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpinBox *sbRowCount;
    QLabel *label_2;
    QSpinBox *sbColumnCount;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *cbMasterVisible;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QSpinBox *sbNGSingSize;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_4;
    QComboBox *cbSortOrder;
    QFrame *line_3;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;

    void setupUi(QDialog *SettingClass)
    {
        if (SettingClass->objectName().isEmpty())
            SettingClass->setObjectName(QString::fromUtf8("SettingClass"));
        SettingClass->resize(255, 214);
        gridLayout = new QGridLayout(SettingClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(SettingClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        sbRowCount = new QSpinBox(SettingClass);
        sbRowCount->setObjectName(QString::fromUtf8("sbRowCount"));
        sbRowCount->setMinimum(1);

        horizontalLayout->addWidget(sbRowCount);

        label_2 = new QLabel(SettingClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);

        sbColumnCount = new QSpinBox(SettingClass);
        sbColumnCount->setObjectName(QString::fromUtf8("sbColumnCount"));
        sbColumnCount->setMinimum(1);

        horizontalLayout->addWidget(sbColumnCount);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        line = new QFrame(SettingClass);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        cbMasterVisible = new QCheckBox(SettingClass);
        cbMasterVisible->setObjectName(QString::fromUtf8("cbMasterVisible"));
        cbMasterVisible->setChecked(false);

        horizontalLayout_2->addWidget(cbMasterVisible);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        line_4 = new QFrame(SettingClass);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_4, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_3 = new QLabel(SettingClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_3);

        sbNGSingSize = new QSpinBox(SettingClass);
        sbNGSingSize->setObjectName(QString::fromUtf8("sbNGSingSize"));
        sbNGSingSize->setMinimum(2);
        sbNGSingSize->setValue(10);

        horizontalLayout_4->addWidget(sbNGSingSize);


        gridLayout->addLayout(horizontalLayout_4, 4, 0, 1, 1);

        line_2 = new QFrame(SettingClass);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 5, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        label_4 = new QLabel(SettingClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_4);

        cbSortOrder = new QComboBox(SettingClass);
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->addItem(QString());
        cbSortOrder->setObjectName(QString::fromUtf8("cbSortOrder"));
        cbSortOrder->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(cbSortOrder);


        gridLayout->addLayout(horizontalLayout_3, 6, 0, 1, 1);

        line_3 = new QFrame(SettingClass);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 7, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(SettingClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon);

        hboxLayout->addWidget(okButton);


        gridLayout->addLayout(hboxLayout, 8, 0, 1, 1);


        retranslateUi(SettingClass);
        QObject::connect(okButton, SIGNAL(clicked()), SettingClass, SLOT(accept()));

        QMetaObject::connectSlotsByName(SettingClass);
    } // setupUi

    void retranslateUi(QDialog *SettingClass)
    {
        SettingClass->setWindowTitle(QCoreApplication::translate("SettingClass", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingClass", "Rows", nullptr));
        label_2->setText(QCoreApplication::translate("SettingClass", "Columns", nullptr));
        cbMasterVisible->setText(QCoreApplication::translate("SettingClass", "view Master Piece", nullptr));
        label_3->setText(QCoreApplication::translate("SettingClass", "NG Mark Size", nullptr));
        label_4->setText(QCoreApplication::translate("SettingClass", "Sort Order", nullptr));
        cbSortOrder->setItemText(0, QCoreApplication::translate("SettingClass", "Y(TopToDown)", nullptr));
        cbSortOrder->setItemText(1, QCoreApplication::translate("SettingClass", "Y(DownToTop)", nullptr));
        cbSortOrder->setItemText(2, QCoreApplication::translate("SettingClass", "Lib(Lesser)", nullptr));
        cbSortOrder->setItemText(3, QCoreApplication::translate("SettingClass", "Lib(Greater)", nullptr));
        cbSortOrder->setItemText(4, QCoreApplication::translate("SettingClass", "NGCause(Lesser)", nullptr));
        cbSortOrder->setItemText(5, QCoreApplication::translate("SettingClass", "NGCause(Greater)", nullptr));

        okButton->setText(QCoreApplication::translate("SettingClass", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingClass: public Ui_SettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFORM_H
