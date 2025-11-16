/********************************************************************************
** Form generated from reading UI file 'ManageByDayTime.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEBYDAYTIME_H
#define UI_MANAGEBYDAYTIME_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ManageByDayTime
{
public:
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *progressBarDelete;
    QPushButton *pushButtonClose;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QCalendarWidget *calendarStartDelete;
    QDateTimeEdit *dateTimeEditStartDelete;
    QLabel *label;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEditEndDelete;
    QCalendarWidget *calendarEndDelete;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonExecuteDelete;
    QCheckBox *cbDeleteEmptyDXML;

    void setupUi(QDialog *ManageByDayTime)
    {
        if (ManageByDayTime->objectName().isEmpty())
            ManageByDayTime->setObjectName("ManageByDayTime");
        ManageByDayTime->resize(551, 310);
        gridLayout_4 = new QGridLayout(ManageByDayTime);
        gridLayout_4->setObjectName("gridLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        progressBarDelete = new QProgressBar(ManageByDayTime);
        progressBarDelete->setObjectName("progressBarDelete");
        progressBarDelete->setValue(100);
        progressBarDelete->setInvertedAppearance(false);

        horizontalLayout_3->addWidget(progressBarDelete);

        pushButtonClose = new QPushButton(ManageByDayTime);
        pushButtonClose->setObjectName("pushButtonClose");

        horizontalLayout_3->addWidget(pushButtonClose);


        gridLayout_4->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        frame = new QFrame(ManageByDayTime);
        frame->setObjectName("frame");
        frame->setLocale(QLocale(QLocale::Japanese, QLocale::Japan));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        calendarStartDelete = new QCalendarWidget(frame);
        calendarStartDelete->setObjectName("calendarStartDelete");
        calendarStartDelete->setEnabled(true);
        calendarStartDelete->setFirstDayOfWeek(Qt::Sunday);
        calendarStartDelete->setGridVisible(true);
        calendarStartDelete->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        calendarStartDelete->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        calendarStartDelete->setNavigationBarVisible(true);

        gridLayout->addWidget(calendarStartDelete, 2, 0, 1, 1);

        dateTimeEditStartDelete = new QDateTimeEdit(frame);
        dateTimeEditStartDelete->setObjectName("dateTimeEditStartDelete");
        QFont font;
        font.setPointSize(11);
        dateTimeEditStartDelete->setFont(font);

        gridLayout->addWidget(dateTimeEditStartDelete, 1, 0, 1, 1);

        label = new QLabel(frame);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        dateTimeEditEndDelete = new QDateTimeEdit(frame);
        dateTimeEditEndDelete->setObjectName("dateTimeEditEndDelete");
        dateTimeEditEndDelete->setFont(font);

        gridLayout_2->addWidget(dateTimeEditEndDelete, 1, 0, 1, 1);

        calendarEndDelete = new QCalendarWidget(frame);
        calendarEndDelete->setObjectName("calendarEndDelete");
        calendarEndDelete->setGridVisible(true);
        calendarEndDelete->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        gridLayout_2->addWidget(calendarEndDelete, 2, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButtonExecuteDelete = new QPushButton(frame);
        pushButtonExecuteDelete->setObjectName("pushButtonExecuteDelete");

        verticalLayout->addWidget(pushButtonExecuteDelete);

        cbDeleteEmptyDXML = new QCheckBox(frame);
        cbDeleteEmptyDXML->setObjectName("cbDeleteEmptyDXML");
        cbDeleteEmptyDXML->setChecked(true);

        verticalLayout->addWidget(cbDeleteEmptyDXML);


        gridLayout_3->addLayout(verticalLayout, 1, 2, 1, 1);


        gridLayout_4->addWidget(frame, 0, 0, 1, 1);

        QWidget::setTabOrder(dateTimeEditStartDelete, pushButtonExecuteDelete);
        QWidget::setTabOrder(pushButtonExecuteDelete, pushButtonClose);

        retranslateUi(ManageByDayTime);

        QMetaObject::connectSlotsByName(ManageByDayTime);
    } // setupUi

    void retranslateUi(QDialog *ManageByDayTime)
    {
        ManageByDayTime->setWindowTitle(QCoreApplication::translate("ManageByDayTime", "ResultDataManagement by DayTime", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ManageByDayTime", "\351\226\211\343\201\230\343\202\213", nullptr));
        label->setText(QCoreApplication::translate("ManageByDayTime", "\345\211\212\351\231\244\351\226\213\345\247\213\346\227\245\346\231\202", nullptr));
        label_2->setText(QCoreApplication::translate("ManageByDayTime", "\345\211\212\351\231\244\347\265\202\344\272\206\346\227\245\346\231\202", nullptr));
        pushButtonExecuteDelete->setText(QCoreApplication::translate("ManageByDayTime", "\345\211\212\351\231\244\345\256\237\350\241\214", nullptr));
        cbDeleteEmptyDXML->setText(QCoreApplication::translate("ManageByDayTime", "\347\251\272\343\201\256\343\203\255\343\203\203\343\203\210\343\202\222\346\266\210\343\201\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManageByDayTime: public Ui_ManageByDayTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEBYDAYTIME_H
