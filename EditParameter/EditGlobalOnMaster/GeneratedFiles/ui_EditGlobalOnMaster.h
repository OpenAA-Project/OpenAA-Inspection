/********************************************************************************
** Form generated from reading UI file 'EditGlobalOnMaster.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITGLOBALONMASTER_H
#define UI_EDITGLOBALONMASTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditGlobalOnMasterClass
{
public:
    QWidget *centralWidget;
    QFrame *frameDatabase;
    QPushButton *pushButtonOpenDatabase;
    QLabel *label;
    QLineEdit *lineEditDBFileName;
    QLabel *label_2;
    QSpinBox *spinBoxPortNo;
    QLineEdit *lineEditHostName;
    QLabel *label_3;
    QFrame *frameMasterData;
    QLineEdit *lineEditState;
    QFrame *frameGrid;
    QLabel *labelTopView;
    QFrame *frame;
    QGridLayout *gridLayout;
    QFrame *frameCategory;
    QFrame *frame_3;
    QGridLayout *gridLayout_6;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *spinBoxSearchID;
    QPushButton *pushButtonStartSearchByID;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QFrame *frame_2;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEditSearchName;
    QPushButton *pushButtonStartSearchByName;
    QPushButton *pushButtonClose;

    void setupUi(QMainWindow *EditGlobalOnMasterClass)
    {
        if (EditGlobalOnMasterClass->objectName().isEmpty())
            EditGlobalOnMasterClass->setObjectName("EditGlobalOnMasterClass");
        EditGlobalOnMasterClass->resize(1220, 816);
        centralWidget = new QWidget(EditGlobalOnMasterClass);
        centralWidget->setObjectName("centralWidget");
        frameDatabase = new QFrame(centralWidget);
        frameDatabase->setObjectName("frameDatabase");
        frameDatabase->setGeometry(QRect(10, 10, 821, 81));
        frameDatabase->setFrameShape(QFrame::StyledPanel);
        frameDatabase->setFrameShadow(QFrame::Sunken);
        pushButtonOpenDatabase = new QPushButton(frameDatabase);
        pushButtonOpenDatabase->setObjectName("pushButtonOpenDatabase");
        pushButtonOpenDatabase->setGeometry(QRect(640, 10, 161, 61));
        label = new QLabel(frameDatabase);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 181, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditDBFileName = new QLineEdit(frameDatabase);
        lineEditDBFileName->setObjectName("lineEditDBFileName");
        lineEditDBFileName->setGeometry(QRect(190, 50, 421, 20));
        label_2 = new QLabel(frameDatabase);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 181, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        spinBoxPortNo = new QSpinBox(frameDatabase);
        spinBoxPortNo->setObjectName("spinBoxPortNo");
        spinBoxPortNo->setGeometry(QRect(190, 30, 91, 22));
        spinBoxPortNo->setMaximum(65536);
        spinBoxPortNo->setValue(3051);
        lineEditHostName = new QLineEdit(frameDatabase);
        lineEditHostName->setObjectName("lineEditHostName");
        lineEditHostName->setGeometry(QRect(190, 10, 421, 20));
        label_3 = new QLabel(frameDatabase);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 30, 181, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        frameMasterData = new QFrame(centralWidget);
        frameMasterData->setObjectName("frameMasterData");
        frameMasterData->setGeometry(QRect(10, 100, 1201, 701));
        frameMasterData->setFrameShape(QFrame::Panel);
        frameMasterData->setFrameShadow(QFrame::Sunken);
        lineEditState = new QLineEdit(frameMasterData);
        lineEditState->setObjectName("lineEditState");
        lineEditState->setGeometry(QRect(760, 380, 400, 20));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditState->sizePolicy().hasHeightForWidth());
        lineEditState->setSizePolicy(sizePolicy);
        lineEditState->setMinimumSize(QSize(400, 0));
        lineEditState->setMaximumSize(QSize(16777215, 16777215));
        lineEditState->setReadOnly(true);
        frameGrid = new QFrame(frameMasterData);
        frameGrid->setObjectName("frameGrid");
        frameGrid->setGeometry(QRect(10, 410, 1173, 271));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frameGrid->sizePolicy().hasHeightForWidth());
        frameGrid->setSizePolicy(sizePolicy1);
        frameGrid->setMinimumSize(QSize(0, 200));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);
        labelTopView = new QLabel(frameMasterData);
        labelTopView->setObjectName("labelTopView");
        labelTopView->setGeometry(QRect(770, 20, 257, 257));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelTopView->sizePolicy().hasHeightForWidth());
        labelTopView->setSizePolicy(sizePolicy2);
        labelTopView->setMinimumSize(QSize(257, 257));
        labelTopView->setMaximumSize(QSize(257, 257));
        labelTopView->setFrameShape(QFrame::Panel);
        labelTopView->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(frameMasterData);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 450, 326));
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy3);
        frame->setMinimumSize(QSize(450, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        frameCategory = new QFrame(frame);
        frameCategory->setObjectName("frameCategory");
        sizePolicy3.setHeightForWidth(frameCategory->sizePolicy().hasHeightForWidth());
        frameCategory->setSizePolicy(sizePolicy3);
        frameCategory->setFrameShape(QFrame::StyledPanel);
        frameCategory->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameCategory, 0, 0, 1, 1);

        frame_3 = new QFrame(frameMasterData);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(30, 350, 181, 51));
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        gridLayout_6 = new QGridLayout(frame_3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(4, 4, 4, 0);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy4);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_5, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        spinBoxSearchID = new QSpinBox(frame_3);
        spinBoxSearchID->setObjectName("spinBoxSearchID");
        spinBoxSearchID->setMaximum(99999999);

        horizontalLayout_5->addWidget(spinBoxSearchID);

        pushButtonStartSearchByID = new QPushButton(frame_3);
        pushButtonStartSearchByID->setObjectName("pushButtonStartSearchByID");

        horizontalLayout_5->addWidget(pushButtonStartSearchByID);


        gridLayout_6->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        layoutWidget = new QWidget(frameMasterData);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(237, 350, 501, 53));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget);
        horizontalLayout_7->setSpacing(4);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName("frame_2");
        sizePolicy4.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy4);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        gridLayout_5 = new QGridLayout(frame_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(4, 4, 4, 0);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        sizePolicy4.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy4);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        lineEditSearchName = new QLineEdit(frame_2);
        lineEditSearchName->setObjectName("lineEditSearchName");

        horizontalLayout_4->addWidget(lineEditSearchName);

        pushButtonStartSearchByName = new QPushButton(frame_2);
        pushButtonStartSearchByName->setObjectName("pushButtonStartSearchByName");

        horizontalLayout_4->addWidget(pushButtonStartSearchByName);


        gridLayout_5->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        horizontalLayout_7->addWidget(frame_2);

        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setGeometry(QRect(960, 10, 141, 61));
        EditGlobalOnMasterClass->setCentralWidget(centralWidget);

        retranslateUi(EditGlobalOnMasterClass);

        QMetaObject::connectSlotsByName(EditGlobalOnMasterClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditGlobalOnMasterClass)
    {
        EditGlobalOnMasterClass->setWindowTitle(QCoreApplication::translate("EditGlobalOnMasterClass", "EditGlobalOnMaster", nullptr));
        pushButtonOpenDatabase->setText(QCoreApplication::translate("EditGlobalOnMasterClass", "Open database", nullptr));
        label->setText(QCoreApplication::translate("EditGlobalOnMasterClass", "Host name or IP address", nullptr));
        label_2->setText(QCoreApplication::translate("EditGlobalOnMasterClass", "File path and name", nullptr));
        label_3->setText(QCoreApplication::translate("EditGlobalOnMasterClass", "Port number", nullptr));
        label_5->setText(QCoreApplication::translate("EditGlobalOnMasterClass", "ID\346\244\234\347\264\242", nullptr));
        pushButtonStartSearchByID->setText(QCoreApplication::translate("EditGlobalOnMasterClass", "\346\244\234\347\264\242", nullptr));
        label_4->setText(QCoreApplication::translate("EditGlobalOnMasterClass", "\345\220\215\347\247\260\346\244\234\347\264\242", nullptr));
        pushButtonStartSearchByName->setText(QCoreApplication::translate("EditGlobalOnMasterClass", "\346\244\234\347\264\242", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("EditGlobalOnMasterClass", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditGlobalOnMasterClass: public Ui_EditGlobalOnMasterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITGLOBALONMASTER_H
