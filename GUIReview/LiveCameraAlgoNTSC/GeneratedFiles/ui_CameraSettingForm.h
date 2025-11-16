/********************************************************************************
** Form generated from reading UI file 'CameraSettingForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASETTINGFORM_H
#define UI_CAMERASETTINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraSettingClass
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *OkCancelLayout;
    QSpacerItem *spOkCancel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lbRed;
    QSlider *hsRed;
    QSpinBox *sbRed;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbGreen;
    QSlider *hsGreen;
    QSpinBox *sbGreen;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbBlue;
    QSlider *hsBlue;
    QSpinBox *sbBlue;

    void setupUi(QDialog *CameraSettingClass)
    {
        if (CameraSettingClass->objectName().isEmpty())
            CameraSettingClass->setObjectName(QString::fromUtf8("CameraSettingClass"));
        CameraSettingClass->resize(370, 160);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CameraSettingClass->sizePolicy().hasHeightForWidth());
        CameraSettingClass->setSizePolicy(sizePolicy);
        CameraSettingClass->setMinimumSize(QSize(370, 160));
        CameraSettingClass->setMaximumSize(QSize(370, 160));
        CameraSettingClass->setBaseSize(QSize(370, 160));
        layoutWidget = new QWidget(CameraSettingClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 110, 331, 35));
        OkCancelLayout = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
        OkCancelLayout->setSpacing(6);
#endif
        OkCancelLayout->setContentsMargins(0, 0, 0, 0);
        OkCancelLayout->setObjectName(QString::fromUtf8("OkCancelLayout"));
        OkCancelLayout->setContentsMargins(0, 0, 0, 0);
        spOkCancel = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        OkCancelLayout->addItem(spOkCancel);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        OkCancelLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon);

        OkCancelLayout->addWidget(cancelButton);

        layoutWidget_2 = new QWidget(CameraSettingClass);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 20, 331, 85));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lbRed = new QLabel(layoutWidget_2);
        lbRed->setObjectName(QString::fromUtf8("lbRed"));
        sizePolicy.setHeightForWidth(lbRed->sizePolicy().hasHeightForWidth());
        lbRed->setSizePolicy(sizePolicy);
        lbRed->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(lbRed);

        hsRed = new QSlider(layoutWidget_2);
        hsRed->setObjectName(QString::fromUtf8("hsRed"));
        hsRed->setMinimum(-255);
        hsRed->setMaximum(255);
        hsRed->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(hsRed);

        sbRed = new QSpinBox(layoutWidget_2);
        sbRed->setObjectName(QString::fromUtf8("sbRed"));
        sbRed->setMinimum(-255);
        sbRed->setMaximum(255);

        horizontalLayout->addWidget(sbRed);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lbGreen = new QLabel(layoutWidget_2);
        lbGreen->setObjectName(QString::fromUtf8("lbGreen"));
        sizePolicy.setHeightForWidth(lbGreen->sizePolicy().hasHeightForWidth());
        lbGreen->setSizePolicy(sizePolicy);
        lbGreen->setMinimumSize(QSize(40, 0));

        horizontalLayout_2->addWidget(lbGreen);

        hsGreen = new QSlider(layoutWidget_2);
        hsGreen->setObjectName(QString::fromUtf8("hsGreen"));
        hsGreen->setMinimum(-255);
        hsGreen->setMaximum(255);
        hsGreen->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(hsGreen);

        sbGreen = new QSpinBox(layoutWidget_2);
        sbGreen->setObjectName(QString::fromUtf8("sbGreen"));
        sbGreen->setMinimum(-255);
        sbGreen->setMaximum(255);

        horizontalLayout_2->addWidget(sbGreen);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lbBlue = new QLabel(layoutWidget_2);
        lbBlue->setObjectName(QString::fromUtf8("lbBlue"));
        sizePolicy.setHeightForWidth(lbBlue->sizePolicy().hasHeightForWidth());
        lbBlue->setSizePolicy(sizePolicy);
        lbBlue->setMinimumSize(QSize(40, 0));

        horizontalLayout_3->addWidget(lbBlue);

        hsBlue = new QSlider(layoutWidget_2);
        hsBlue->setObjectName(QString::fromUtf8("hsBlue"));
        hsBlue->setMinimum(-255);
        hsBlue->setMaximum(255);
        hsBlue->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(hsBlue);

        sbBlue = new QSpinBox(layoutWidget_2);
        sbBlue->setObjectName(QString::fromUtf8("sbBlue"));
        sbBlue->setMinimum(-255);
        sbBlue->setMaximum(255);

        horizontalLayout_3->addWidget(sbBlue);


        verticalLayout->addLayout(horizontalLayout_3);

        QWidget::setTabOrder(sbRed, sbGreen);
        QWidget::setTabOrder(sbGreen, sbBlue);
        QWidget::setTabOrder(sbBlue, hsRed);
        QWidget::setTabOrder(hsRed, hsGreen);
        QWidget::setTabOrder(hsGreen, hsBlue);
        QWidget::setTabOrder(hsBlue, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(CameraSettingClass);
        QObject::connect(okButton, SIGNAL(clicked()), CameraSettingClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), CameraSettingClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(CameraSettingClass);
    } // setupUi

    void retranslateUi(QDialog *CameraSettingClass)
    {
        CameraSettingClass->setWindowTitle(QCoreApplication::translate("CameraSettingClass", "CameraSettingForm", nullptr));
        okButton->setText(QCoreApplication::translate("CameraSettingClass", "Save", nullptr));
        cancelButton->setText(QCoreApplication::translate("CameraSettingClass", "\343\202\255\343\203\243\343\203\263\343\202\273\343\203\253", nullptr));
        lbRed->setText(QCoreApplication::translate("CameraSettingClass", "Red", nullptr));
        lbGreen->setText(QCoreApplication::translate("CameraSettingClass", "Green", nullptr));
        lbBlue->setText(QCoreApplication::translate("CameraSettingClass", "Blue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraSettingClass: public Ui_CameraSettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASETTINGFORM_H
