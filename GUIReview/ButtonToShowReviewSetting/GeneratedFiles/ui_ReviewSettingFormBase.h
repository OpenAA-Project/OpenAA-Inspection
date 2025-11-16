/********************************************************************************
** Form generated from reading UI file 'ReviewSettingFormBase.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVIEWSETTINGFORMBASE_H
#define UI_REVIEWSETTINGFORMBASE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReviewSettingClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QTabWidget *tabWidget;
    QWidget *tabGlobal;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *pbReviewStructure;
    QPushButton *pbListMasterDataAndLoad;
    QPushButton *pbSelectLotForReview;
    QPushButton *pbShowHistoryListForReview;
    QPushButton *pbWholeImageForReview;
    QPushButton *pbListStatisticNG;
    QPushButton *pbButtonToShowTotalNGMap;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tabStandard;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pbNGImageListForReview;
    QPushButton *pbNGImageForReview;
    QSpacerItem *horizontalSpacer_4;
    QWidget *tabThumbnail;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pbShowThumbnail;
    QSpacerItem *horizontalSpacer_6;
    QWidget *tabVRS;
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pbLiveCameraAlgoNTSC;
    QPushButton *pbShowVRSOperation;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *ReviewSettingClass)
    {
        if (ReviewSettingClass->objectName().isEmpty())
            ReviewSettingClass->setObjectName(QString::fromUtf8("ReviewSettingClass"));
        ReviewSettingClass->resize(344, 367);
        gridLayout = new QGridLayout(ReviewSettingClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(ReviewSettingClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon);

        hboxLayout->addWidget(okButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        tabWidget = new QTabWidget(ReviewSettingClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabGlobal = new QWidget();
        tabGlobal->setObjectName(QString::fromUtf8("tabGlobal"));
        gridLayout_2 = new QGridLayout(tabGlobal);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(44, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pbReviewStructure = new QPushButton(tabGlobal);
        pbReviewStructure->setObjectName(QString::fromUtf8("pbReviewStructure"));

        verticalLayout->addWidget(pbReviewStructure);

        pbListMasterDataAndLoad = new QPushButton(tabGlobal);
        pbListMasterDataAndLoad->setObjectName(QString::fromUtf8("pbListMasterDataAndLoad"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbListMasterDataAndLoad->sizePolicy().hasHeightForWidth());
        pbListMasterDataAndLoad->setSizePolicy(sizePolicy);
        pbListMasterDataAndLoad->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(pbListMasterDataAndLoad);

        pbSelectLotForReview = new QPushButton(tabGlobal);
        pbSelectLotForReview->setObjectName(QString::fromUtf8("pbSelectLotForReview"));
        sizePolicy.setHeightForWidth(pbSelectLotForReview->sizePolicy().hasHeightForWidth());
        pbSelectLotForReview->setSizePolicy(sizePolicy);
        pbSelectLotForReview->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(pbSelectLotForReview);

        pbShowHistoryListForReview = new QPushButton(tabGlobal);
        pbShowHistoryListForReview->setObjectName(QString::fromUtf8("pbShowHistoryListForReview"));
        sizePolicy.setHeightForWidth(pbShowHistoryListForReview->sizePolicy().hasHeightForWidth());
        pbShowHistoryListForReview->setSizePolicy(sizePolicy);
        pbShowHistoryListForReview->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(pbShowHistoryListForReview);

        pbWholeImageForReview = new QPushButton(tabGlobal);
        pbWholeImageForReview->setObjectName(QString::fromUtf8("pbWholeImageForReview"));
        sizePolicy.setHeightForWidth(pbWholeImageForReview->sizePolicy().hasHeightForWidth());
        pbWholeImageForReview->setSizePolicy(sizePolicy);
        pbWholeImageForReview->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(pbWholeImageForReview);

        pbListStatisticNG = new QPushButton(tabGlobal);
        pbListStatisticNG->setObjectName(QString::fromUtf8("pbListStatisticNG"));
        sizePolicy.setHeightForWidth(pbListStatisticNG->sizePolicy().hasHeightForWidth());
        pbListStatisticNG->setSizePolicy(sizePolicy);
        pbListStatisticNG->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(pbListStatisticNG);

        pbButtonToShowTotalNGMap = new QPushButton(tabGlobal);
        pbButtonToShowTotalNGMap->setObjectName(QString::fromUtf8("pbButtonToShowTotalNGMap"));
        sizePolicy.setHeightForWidth(pbButtonToShowTotalNGMap->sizePolicy().hasHeightForWidth());
        pbButtonToShowTotalNGMap->setSizePolicy(sizePolicy);
        pbButtonToShowTotalNGMap->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(pbButtonToShowTotalNGMap);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(44, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        tabWidget->addTab(tabGlobal, QString());
        tabStandard = new QWidget();
        tabStandard->setObjectName(QString::fromUtf8("tabStandard"));
        gridLayout_3 = new QGridLayout(tabStandard);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pbNGImageListForReview = new QPushButton(tabStandard);
        pbNGImageListForReview->setObjectName(QString::fromUtf8("pbNGImageListForReview"));

        verticalLayout_2->addWidget(pbNGImageListForReview);

        pbNGImageForReview = new QPushButton(tabStandard);
        pbNGImageForReview->setObjectName(QString::fromUtf8("pbNGImageForReview"));

        verticalLayout_2->addWidget(pbNGImageForReview);


        gridLayout_3->addLayout(verticalLayout_2, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(89, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        tabWidget->addTab(tabStandard, QString());
        tabThumbnail = new QWidget();
        tabThumbnail->setObjectName(QString::fromUtf8("tabThumbnail"));
        gridLayout_4 = new QGridLayout(tabThumbnail);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(114, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        pbShowThumbnail = new QPushButton(tabThumbnail);
        pbShowThumbnail->setObjectName(QString::fromUtf8("pbShowThumbnail"));

        gridLayout_4->addWidget(pbShowThumbnail, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(114, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        tabWidget->addTab(tabThumbnail, QString());
        tabVRS = new QWidget();
        tabVRS->setObjectName(QString::fromUtf8("tabVRS"));
        gridLayout_5 = new QGridLayout(tabVRS);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalSpacer_7 = new QSpacerItem(93, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_7, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pbLiveCameraAlgoNTSC = new QPushButton(tabVRS);
        pbLiveCameraAlgoNTSC->setObjectName(QString::fromUtf8("pbLiveCameraAlgoNTSC"));

        verticalLayout_3->addWidget(pbLiveCameraAlgoNTSC);

        pbShowVRSOperation = new QPushButton(tabVRS);
        pbShowVRSOperation->setObjectName(QString::fromUtf8("pbShowVRSOperation"));

        verticalLayout_3->addWidget(pbShowVRSOperation);


        gridLayout_5->addLayout(verticalLayout_3, 0, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(93, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_8, 0, 2, 1, 1);

        tabWidget->addTab(tabVRS, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(ReviewSettingClass);
        QObject::connect(okButton, SIGNAL(clicked()), ReviewSettingClass, SLOT(accept()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ReviewSettingClass);
    } // setupUi

    void retranslateUi(QDialog *ReviewSettingClass)
    {
        ReviewSettingClass->setWindowTitle(QCoreApplication::translate("ReviewSettingClass", "ReviewSettingForm", nullptr));
        okButton->setText(QCoreApplication::translate("ReviewSettingClass", "Close", nullptr));
        pbReviewStructure->setText(QCoreApplication::translate("ReviewSettingClass", "ReviewStructure", nullptr));
        pbListMasterDataAndLoad->setText(QCoreApplication::translate("ReviewSettingClass", "ListMasterDataAndLoad", nullptr));
        pbSelectLotForReview->setText(QCoreApplication::translate("ReviewSettingClass", "SelectLotForReview", nullptr));
        pbShowHistoryListForReview->setText(QCoreApplication::translate("ReviewSettingClass", "ShowHistoryListForReview", nullptr));
        pbWholeImageForReview->setText(QCoreApplication::translate("ReviewSettingClass", "WholeImageForReview", nullptr));
        pbListStatisticNG->setText(QCoreApplication::translate("ReviewSettingClass", "ListStatisticNG", nullptr));
        pbButtonToShowTotalNGMap->setText(QCoreApplication::translate("ReviewSettingClass", "ButtonToShowTotalNGMap", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGlobal), QCoreApplication::translate("ReviewSettingClass", "Global", nullptr));
        pbNGImageListForReview->setText(QCoreApplication::translate("ReviewSettingClass", "NGImageListForReview", nullptr));
        pbNGImageForReview->setText(QCoreApplication::translate("ReviewSettingClass", "NGImageForReview", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabStandard), QCoreApplication::translate("ReviewSettingClass", "Standard", nullptr));
        pbShowThumbnail->setText(QCoreApplication::translate("ReviewSettingClass", "ShowThumbnail", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabThumbnail), QCoreApplication::translate("ReviewSettingClass", "Thumbnail", nullptr));
        pbLiveCameraAlgoNTSC->setText(QCoreApplication::translate("ReviewSettingClass", "LiveCameraAlgoNTSC", nullptr));
        pbShowVRSOperation->setText(QCoreApplication::translate("ReviewSettingClass", "ShowVRSOperation", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabVRS), QCoreApplication::translate("ReviewSettingClass", "VRS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReviewSettingClass: public Ui_ReviewSettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVIEWSETTINGFORMBASE_H
