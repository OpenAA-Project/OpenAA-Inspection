/********************************************************************************
** Form generated from reading UI file 'LoadMasterDataWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADMASTERDATAWINDOW_H
#define UI_LOADMASTERDATAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadMasterDataWindowClass
{
public:
    QFrame *frame;
    QLabel *label_4;
    QLineEdit *EditMasterName;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *EditRemark;
    QPushButton *ButtonLoad;
    QPushButton *ButtonCancel;
    QLineEdit *EditMasterCode;
    QFrame *frameCategory;
    QLabel *labelTopView;
    QToolButton *toolButton;
    QFrame *frameGrid;
    QFrame *frame_2;
    QLineEdit *lineEditSearchName;
    QLabel *label_3;
    QPushButton *pushButtonStartSearchByName;
    QLineEdit *lineEditState;
    QFrame *frame_3;
    QLabel *label_5;
    QPushButton *pushButtonStartSearchByID;
    QSpinBox *spinBoxSearchID;
    QLabel *label_6;
    QScrollArea *scrollAreaMachine;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *LoadMasterDataWindowClass)
    {
        if (LoadMasterDataWindowClass->objectName().isEmpty())
            LoadMasterDataWindowClass->setObjectName(QString::fromUtf8("LoadMasterDataWindowClass"));
        LoadMasterDataWindowClass->resize(1020, 656);
        frame = new QFrame(LoadMasterDataWindowClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 1001, 271));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(430, 10, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        EditMasterName = new QLineEdit(frame);
        EditMasterName->setObjectName(QString::fromUtf8("EditMasterName"));
        EditMasterName->setGeometry(QRect(430, 90, 291, 21));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(430, 120, 291, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(430, 70, 291, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        EditRemark = new QLineEdit(frame);
        EditRemark->setObjectName(QString::fromUtf8("EditRemark"));
        EditRemark->setGeometry(QRect(430, 140, 291, 21));
        ButtonLoad = new QPushButton(frame);
        ButtonLoad->setObjectName(QString::fromUtf8("ButtonLoad"));
        ButtonLoad->setGeometry(QRect(430, 210, 91, 41));
        ButtonCancel = new QPushButton(frame);
        ButtonCancel->setObjectName(QString::fromUtf8("ButtonCancel"));
        ButtonCancel->setGeometry(QRect(620, 210, 91, 41));
        EditMasterCode = new QLineEdit(frame);
        EditMasterCode->setObjectName(QString::fromUtf8("EditMasterCode"));
        EditMasterCode->setGeometry(QRect(430, 30, 81, 21));
        EditMasterCode->setReadOnly(true);
        frameCategory = new QFrame(frame);
        frameCategory->setObjectName(QString::fromUtf8("frameCategory"));
        frameCategory->setGeometry(QRect(10, 10, 401, 251));
        frameCategory->setFrameShape(QFrame::StyledPanel);
        frameCategory->setFrameShadow(QFrame::Raised);
        labelTopView = new QLabel(frame);
        labelTopView->setObjectName(QString::fromUtf8("labelTopView"));
        labelTopView->setGeometry(QRect(740, 10, 257, 257));
        labelTopView->setFrameShape(QFrame::Panel);
        labelTopView->setFrameShadow(QFrame::Sunken);
        toolButton = new QToolButton(frame);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(430, 170, 21, 19));
        frameGrid = new QFrame(LoadMasterDataWindowClass);
        frameGrid->setObjectName(QString::fromUtf8("frameGrid"));
        frameGrid->setGeometry(QRect(160, 340, 851, 271));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);
        frame_2 = new QFrame(LoadMasterDataWindowClass);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(450, 290, 261, 51));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        lineEditSearchName = new QLineEdit(frame_2);
        lineEditSearchName->setObjectName(QString::fromUtf8("lineEditSearchName"));
        lineEditSearchName->setGeometry(QRect(10, 20, 161, 20));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(-1, 0, 261, 20));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonStartSearchByName = new QPushButton(frame_2);
        pushButtonStartSearchByName->setObjectName(QString::fromUtf8("pushButtonStartSearchByName"));
        pushButtonStartSearchByName->setGeometry(QRect(180, 20, 75, 23));
        lineEditState = new QLineEdit(LoadMasterDataWindowClass);
        lineEditState->setObjectName(QString::fromUtf8("lineEditState"));
        lineEditState->setGeometry(QRect(160, 620, 251, 20));
        lineEditState->setReadOnly(true);
        frame_3 = new QFrame(LoadMasterDataWindowClass);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(160, 290, 261, 51));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(-1, 0, 261, 20));
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonStartSearchByID = new QPushButton(frame_3);
        pushButtonStartSearchByID->setObjectName(QString::fromUtf8("pushButtonStartSearchByID"));
        pushButtonStartSearchByID->setGeometry(QRect(160, 20, 75, 23));
        spinBoxSearchID = new QSpinBox(frame_3);
        spinBoxSearchID->setObjectName(QString::fromUtf8("spinBoxSearchID"));
        spinBoxSearchID->setGeometry(QRect(20, 20, 111, 22));
        spinBoxSearchID->setMaximum(99999999);
        label_6 = new QLabel(LoadMasterDataWindowClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 290, 141, 20));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        scrollAreaMachine = new QScrollArea(LoadMasterDataWindowClass);
        scrollAreaMachine->setObjectName(QString::fromUtf8("scrollAreaMachine"));
        scrollAreaMachine->setGeometry(QRect(10, 310, 141, 331));
        scrollAreaMachine->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaMachine->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 137, 327));
        scrollAreaMachine->setWidget(scrollAreaWidgetContents);
        QWidget::setTabOrder(scrollAreaMachine, spinBoxSearchID);
        QWidget::setTabOrder(spinBoxSearchID, pushButtonStartSearchByID);
        QWidget::setTabOrder(pushButtonStartSearchByID, lineEditSearchName);
        QWidget::setTabOrder(lineEditSearchName, pushButtonStartSearchByName);
        QWidget::setTabOrder(pushButtonStartSearchByName, ButtonLoad);
        QWidget::setTabOrder(ButtonLoad, ButtonCancel);
        QWidget::setTabOrder(ButtonCancel, EditMasterCode);
        QWidget::setTabOrder(EditMasterCode, EditMasterName);
        QWidget::setTabOrder(EditMasterName, EditRemark);
        QWidget::setTabOrder(EditRemark, toolButton);
        QWidget::setTabOrder(toolButton, lineEditState);

        retranslateUi(LoadMasterDataWindowClass);

        QMetaObject::connectSlotsByName(LoadMasterDataWindowClass);
    } // setupUi

    void retranslateUi(QWidget *LoadMasterDataWindowClass)
    {
        LoadMasterDataWindowClass->setWindowTitle(QCoreApplication::translate("LoadMasterDataWindowClass", "LoadMasterDataWindow", nullptr));
        label_4->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Master Code", nullptr));
        label_2->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Remark", nullptr));
        label->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Master Name", nullptr));
        ButtonLoad->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Load", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Cancel", nullptr));
        toolButton->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "...", nullptr));
        label_3->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Search by Name", nullptr));
        pushButtonStartSearchByName->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Search", nullptr));
        label_5->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Search by ID", nullptr));
        pushButtonStartSearchByID->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Search", nullptr));
        label_6->setText(QCoreApplication::translate("LoadMasterDataWindowClass", "Machine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadMasterDataWindowClass: public Ui_LoadMasterDataWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADMASTERDATAWINDOW_H
