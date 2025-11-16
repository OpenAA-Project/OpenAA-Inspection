/********************************************************************************
** Form generated from reading UI file 'networkdriveautoconnect.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKDRIVEAUTOCONNECT_H
#define UI_NETWORKDRIVEAUTOCONNECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkDriveAutoConnectClass
{
public:
    QWidget *centralWidget;
    QPushButton *QBtnExitButton;
    QProgressBar *progressBar;
    QLabel *label_5;
    QLineEdit *QLiedRetryTime;
    QPushButton *QBtnSaveDefault;
    QLabel *QLblStateInfo;
    QLabel *label_6;
    QPushButton *QBtnConnectNow;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *QLiedLocalDriveName;
    QLabel *label_2;
    QLineEdit *QLiedConctFolderPass;
    QLabel *label_3;
    QLineEdit *QLiedLogon_UserName;
    QLabel *label_4;
    QLineEdit *QLiedLogon_Password;
    QPushButton *QBtnConnectStart;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NetworkDriveAutoConnectClass)
    {
        if (NetworkDriveAutoConnectClass->objectName().isEmpty())
            NetworkDriveAutoConnectClass->setObjectName("NetworkDriveAutoConnectClass");
        NetworkDriveAutoConnectClass->resize(599, 241);
        centralWidget = new QWidget(NetworkDriveAutoConnectClass);
        centralWidget->setObjectName("centralWidget");
        QBtnExitButton = new QPushButton(centralWidget);
        QBtnExitButton->setObjectName("QBtnExitButton");
        QBtnExitButton->setGeometry(QRect(450, 130, 75, 25));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(320, 80, 250, 20));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setBaseSize(QSize(200, 20));
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setMaximum(1000);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing);
        progressBar->setTextVisible(false);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setTextDirection(QProgressBar::TopToBottom);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(350, 40, 81, 16));
        label_5->setMinimumSize(QSize(61, 16));
        QLiedRetryTime = new QLineEdit(centralWidget);
        QLiedRetryTime->setObjectName("QLiedRetryTime");
        QLiedRetryTime->setGeometry(QRect(440, 40, 71, 20));
        QLiedRetryTime->setAcceptDrops(false);
        QBtnSaveDefault = new QPushButton(centralWidget);
        QBtnSaveDefault->setObjectName("QBtnSaveDefault");
        QBtnSaveDefault->setGeometry(QRect(39, 130, 121, 25));
        QLblStateInfo = new QLabel(centralWidget);
        QLblStateInfo->setObjectName("QLblStateInfo");
        QLblStateInfo->setGeometry(QRect(99, 170, 431, 51));
        QLblStateInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(39, 170, 51, 20));
        label_6->setAlignment(Qt::AlignLeading);
        QBtnConnectNow = new QPushButton(centralWidget);
        QBtnConnectNow->setObjectName("QBtnConnectNow");
        QBtnConnectNow->setGeometry(QRect(180, 130, 90, 25));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 20, 255, 100));
        layoutWidget->setMinimumSize(QSize(255, 100));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(137, 16));

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        QLiedLocalDriveName = new QLineEdit(layoutWidget);
        QLiedLocalDriveName->setObjectName("QLiedLocalDriveName");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, QLiedLocalDriveName);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(130, 16));

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        QLiedConctFolderPass = new QLineEdit(layoutWidget);
        QLiedConctFolderPass->setObjectName("QLiedConctFolderPass");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, QLiedConctFolderPass);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(52, 16));

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        QLiedLogon_UserName = new QLineEdit(layoutWidget);
        QLiedLogon_UserName->setObjectName("QLiedLogon_UserName");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, QLiedLogon_UserName);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(47, 16));

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        QLiedLogon_Password = new QLineEdit(layoutWidget);
        QLiedLogon_Password->setObjectName("QLiedLogon_Password");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, QLiedLogon_Password);

        QBtnConnectStart = new QPushButton(centralWidget);
        QBtnConnectStart->setObjectName("QBtnConnectStart");
        QBtnConnectStart->setGeometry(QRect(290, 130, 91, 25));
        NetworkDriveAutoConnectClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NetworkDriveAutoConnectClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 599, 18));
        NetworkDriveAutoConnectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NetworkDriveAutoConnectClass);
        mainToolBar->setObjectName("mainToolBar");
        NetworkDriveAutoConnectClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NetworkDriveAutoConnectClass);
        statusBar->setObjectName("statusBar");
        NetworkDriveAutoConnectClass->setStatusBar(statusBar);

        retranslateUi(NetworkDriveAutoConnectClass);

        QMetaObject::connectSlotsByName(NetworkDriveAutoConnectClass);
    } // setupUi

    void retranslateUi(QMainWindow *NetworkDriveAutoConnectClass)
    {
        NetworkDriveAutoConnectClass->setWindowTitle(QCoreApplication::translate("NetworkDriveAutoConnectClass", "NetworkDriveAutoConnect", nullptr));
        QBtnExitButton->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "Exit", nullptr));
        progressBar->setFormat(QString());
        label_5->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "\343\203\252\343\203\210\343\203\251\343\202\244\351\226\223\351\232\224[ms]", nullptr));
        QLiedRetryTime->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "1000", nullptr));
        QBtnSaveDefault->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "\350\265\267\345\213\225\346\231\202\350\250\255\345\256\232\343\201\270\344\277\235\345\255\230", nullptr));
        label_6->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "\347\212\266\346\205\213 \357\274\232", nullptr));
        QBtnConnectNow->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "\343\201\231\343\201\220\343\201\253\346\216\245\347\266\232", nullptr));
        label->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "\343\203\255\343\203\274\343\202\253\343\203\253\343\203\215\343\203\203\343\203\210\343\203\257\343\203\274\343\202\257\343\203\211\343\203\251\343\202\244\343\203\226\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "\345\205\261\346\234\211\343\203\215\343\203\203\343\203\210\343\203\257\343\203\274\343\202\257\343\203\225\343\202\251\343\203\253\343\203\200\343\203\221\343\202\271", nullptr));
        label_3->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "\343\203\246\343\203\274\343\202\266\343\203\274\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "\343\203\221\343\202\271\343\203\257\343\203\274\343\203\211", nullptr));
        QBtnConnectStart->setText(QCoreApplication::translate("NetworkDriveAutoConnectClass", "\350\207\252\345\213\225\346\216\245\347\266\232\351\226\213\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetworkDriveAutoConnectClass: public Ui_NetworkDriveAutoConnectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKDRIVEAUTOCONNECT_H
