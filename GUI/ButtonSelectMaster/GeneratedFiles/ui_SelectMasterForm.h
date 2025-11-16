/********************************************************************************
** Form generated from reading UI file 'SelectMasterForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMASTERFORM_H
#define UI_SELECTMASTERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectMasterFormClass
{
public:
    QFrame *frameGrid;
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
    QLineEdit *lineEditState;
    QFrame *frame_3;
    QLabel *label_5;
    QPushButton *pushButtonStartSearchByID;
    QSpinBox *spinBoxSearchID;
    QFrame *frame_2;
    QLineEdit *lineEditSearchName;
    QLabel *label_3;
    QPushButton *pushButtonStartSearchByName;

    void setupUi(QWidget *SelectMasterFormClass)
    {
        if (SelectMasterFormClass->objectName().isEmpty())
            SelectMasterFormClass->setObjectName("SelectMasterFormClass");
        SelectMasterFormClass->resize(873, 555);
        frameGrid = new QFrame(SelectMasterFormClass);
        frameGrid->setObjectName("frameGrid");
        frameGrid->setGeometry(QRect(10, 350, 851, 171));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(SelectMasterFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 851, 271));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(380, 10, 81, 20));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        EditMasterName = new QLineEdit(frame);
        EditMasterName->setObjectName("EditMasterName");
        EditMasterName->setGeometry(QRect(380, 90, 201, 21));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(380, 120, 201, 20));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(380, 70, 201, 20));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        EditRemark = new QLineEdit(frame);
        EditRemark->setObjectName("EditRemark");
        EditRemark->setGeometry(QRect(380, 140, 201, 21));
        ButtonLoad = new QPushButton(frame);
        ButtonLoad->setObjectName("ButtonLoad");
        ButtonLoad->setGeometry(QRect(380, 210, 91, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLoad->setIcon(icon);
        ButtonCancel = new QPushButton(frame);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(490, 210, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        EditMasterCode = new QLineEdit(frame);
        EditMasterCode->setObjectName("EditMasterCode");
        EditMasterCode->setGeometry(QRect(380, 30, 81, 21));
        EditMasterCode->setReadOnly(true);
        frameCategory = new QFrame(frame);
        frameCategory->setObjectName("frameCategory");
        frameCategory->setGeometry(QRect(10, 10, 361, 251));
        frameCategory->setFrameShape(QFrame::StyledPanel);
        frameCategory->setFrameShadow(QFrame::Raised);
        labelTopView = new QLabel(frame);
        labelTopView->setObjectName("labelTopView");
        labelTopView->setGeometry(QRect(590, 10, 257, 257));
        labelTopView->setFrameShape(QFrame::Panel);
        labelTopView->setFrameShadow(QFrame::Sunken);
        lineEditState = new QLineEdit(SelectMasterFormClass);
        lineEditState->setObjectName("lineEditState");
        lineEditState->setGeometry(QRect(10, 530, 251, 20));
        lineEditState->setReadOnly(true);
        frame_3 = new QFrame(SelectMasterFormClass);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(10, 290, 261, 51));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(-1, 0, 261, 20));
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonStartSearchByID = new QPushButton(frame_3);
        pushButtonStartSearchByID->setObjectName("pushButtonStartSearchByID");
        pushButtonStartSearchByID->setGeometry(QRect(160, 20, 75, 23));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonStartSearchByID->setIcon(icon2);
        spinBoxSearchID = new QSpinBox(frame_3);
        spinBoxSearchID->setObjectName("spinBoxSearchID");
        spinBoxSearchID->setGeometry(QRect(20, 20, 111, 22));
        spinBoxSearchID->setMaximum(99999999);
        frame_2 = new QFrame(SelectMasterFormClass);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(300, 290, 261, 51));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        lineEditSearchName = new QLineEdit(frame_2);
        lineEditSearchName->setObjectName("lineEditSearchName");
        lineEditSearchName->setGeometry(QRect(10, 20, 161, 20));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(-1, 0, 261, 20));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonStartSearchByName = new QPushButton(frame_2);
        pushButtonStartSearchByName->setObjectName("pushButtonStartSearchByName");
        pushButtonStartSearchByName->setGeometry(QRect(180, 20, 75, 23));
        pushButtonStartSearchByName->setIcon(icon2);

        retranslateUi(SelectMasterFormClass);

        QMetaObject::connectSlotsByName(SelectMasterFormClass);
    } // setupUi

    void retranslateUi(QWidget *SelectMasterFormClass)
    {
        SelectMasterFormClass->setWindowTitle(QCoreApplication::translate("SelectMasterFormClass", "SelectMasterForm", nullptr));
        label_4->setText(QCoreApplication::translate("SelectMasterFormClass", "Master Code", nullptr));
        label_2->setText(QCoreApplication::translate("SelectMasterFormClass", "Remark", nullptr));
        label->setText(QCoreApplication::translate("SelectMasterFormClass", "Master Name", nullptr));
        ButtonLoad->setText(QCoreApplication::translate("SelectMasterFormClass", "Select", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectMasterFormClass", "Cancel", nullptr));
        label_5->setText(QCoreApplication::translate("SelectMasterFormClass", "ID\346\244\234\347\264\242", nullptr));
        pushButtonStartSearchByID->setText(QCoreApplication::translate("SelectMasterFormClass", "\346\244\234\347\264\242", nullptr));
        label_3->setText(QCoreApplication::translate("SelectMasterFormClass", "\345\220\215\347\247\260\346\244\234\347\264\242", nullptr));
        pushButtonStartSearchByName->setText(QCoreApplication::translate("SelectMasterFormClass", "\346\244\234\347\264\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMasterFormClass: public Ui_SelectMasterFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMASTERFORM_H
